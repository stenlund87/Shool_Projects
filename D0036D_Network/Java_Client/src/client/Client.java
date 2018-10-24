package client;
import java.net.*;
import java.util.HashMap;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.KeyEvent;
import java.awt.event.WindowEvent;
import java.io.*;


public class Client 
{
    public Player thisPlayer;
    public HashMap<Integer,Player> playerList = new HashMap<Integer,Player>();
    DataOutputStream out;
    DataInputStream in;
    Socket clientSocket;
    MulticastSocket multicastSocket;
    InetAddress group;
    ClientListener listener;
	InputStream input;
	int port;
	
	/*Contructor for the Client.
	 * Creates a socket connected to server and starts to listen for data
	 * @Param string ip, the ip for the server
	 * @Param int s_port, the server port 
	 * */
	public Client(String ip, int s_port) throws UnknownHostException
	{
		
		String serverIP = CheckForIPv6(ip);
		port = s_port;
		try
		{
			System.out.println("connecting to " + serverIP + "on port" + port);
			clientSocket = new Socket(serverIP,port);
			System.out.println("Connected to " + clientSocket.getRemoteSocketAddress());
			
			OutputStream outToServer = clientSocket.getOutputStream();
			out = new DataOutputStream(outToServer);
			
			out.writeUTF("Connect:");
			System.out.println("Sent join message");
			input = clientSocket.getInputStream();
			in = new DataInputStream(input);
			String data = in.readUTF();
			System.out.println("Server accepted");
			System.out.println(data);
			String[] holder = data.split(":");
			
			if (holder[0].equals("NewPlayer"))
			{
				System.out.println("Inializing....");
				thisPlayer = new Player("Player_right.png", Integer.parseInt(holder[1]));
				thisPlayer.SetPosition(Integer.parseInt(holder[2]), Integer.parseInt(holder[3]));
			}
			
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
		listener = new ClientListener();
		listener.start();
	}
	
	
	
	
    /*ActionListener for when a key is pressed
     * @Param KeyEvent e, the key that was pressed
     * */
    public void keyPressed(KeyEvent e) throws IOException 
    {

        int key = e.getKeyCode();

        if (key == KeyEvent.VK_A) 
        {
            out.writeUTF(thisPlayer.ID+":Move:Left");
        }

        if (key == KeyEvent.VK_D) 
        {
            out.writeUTF(thisPlayer.ID+":Move:Right");
        }

        if (key == KeyEvent.VK_W) 
        {
            out.writeUTF(thisPlayer.ID+":Move:Up");
        }

        if (key == KeyEvent.VK_S)
        {
            out.writeUTF(thisPlayer.ID+":Move:Down");
        }
        if(key == KeyEvent.VK_ESCAPE)
        {
        	Exit();
        }
    }
    
    /*ActionListener for when a key is released
     * @Param KeyEvent e, the key that was released
     * */
    public void keyReleased(KeyEvent e) throws IOException 
    {
        int key = e.getKeyCode();

        if (key == KeyEvent.VK_A) 
        {
            out.writeUTF(thisPlayer.ID+":Stop:Left");
        }

        if (key == KeyEvent.VK_D) 
        {
            out.writeUTF(thisPlayer.ID+":Stop:Right");
        }

        if (key == KeyEvent.VK_W) 
        {
            out.writeUTF(thisPlayer.ID+":Stop:Up");
        }

        if (key == KeyEvent.VK_S) 
        {
            out.writeUTF(thisPlayer.ID+":Stop:Down");
        }
    }
    
    public void Exit() throws IOException
    {
    	out.writeUTF(thisPlayer.ID+":Leave:Game");
    	clientSocket.close();
    }

    /*Method that checks if there is a IPv6 for given IP
     * @Param String ip, the ip that will be checked
     * @Return String IPv6 address if found, otherwise the given IPv4 address
     * */
    public String CheckForIPv6(String ip) throws UnknownHostException
    {
    	String IPv6;
        boolean isIPv6 = false;
        InetAddress[] AllIp = InetAddress.getAllByName(ip);
        for(int i = 0; i<AllIp.length; i++)
        {
            System.out.println("Ip is "+AllIp[i]);
            isIPv6 = AllIp[i] instanceof Inet6Address;
            if(isIPv6)
            {
            	IPv6 = AllIp[i].getHostAddress();
                System.out.println("IPv6 address is "+ ip);
                return IPv6;
            }
        }
        System.out.println("Unable to use IPv6, IPv4 is " + ip);
        return ip;
    }
    
    /*Method that draws the images on the screen
     * @Param Graphics g
     * @Param Board b, the board that will be drawn on
     * */
    void doDrawing(Graphics g, Board b) 
    {
        Graphics2D g2d = (Graphics2D) g;
        for(Integer key : playerList.keySet())
        {
        	g2d.drawImage(playerList.get(key).GetPlayerIcon(), playerList.get(key).GetX(), playerList.get(key).GetY(), b);
        }
        g2d.drawImage(thisPlayer.GetPlayerIcon(), thisPlayer.GetX(), thisPlayer.GetY(), b);  
    }
    
  //Listening class. Receives data from server and depending on what the data is performs certain operations
  	public class ClientListener extends Thread
  	{
  	    public void run()
  	    {
  	    	try
  	    	{
  	    		InetAddress group = InetAddress.getByName("229.15.15.15");
  	    		multicastSocket = new MulticastSocket(7778);
  	    		multicastSocket.joinGroup(group);

  		    	while(true)
  		    	{	    	
  		    		byte[] bytepack = new byte[500];
  		    		DatagramPacket msreceive = new DatagramPacket(bytepack, bytepack.length);
  		    		multicastSocket.receive(msreceive);
  		    		String temp = new String(msreceive.getData(),0,msreceive.getLength());
  		    		System.out.println(temp);
  					String[] holder = temp.split(":");
  					int playerID = Integer.parseInt(holder[0]);
  					
  					if(holder[1].equals("Leave") && thisPlayer.ID != playerID)
  					{
  						playerList.remove(Integer.parseInt(holder[0]));
  					}
  					else if(holder[1].equals("Leave") && thisPlayer.ID == playerID)
  					{
  						System.exit(1);
  					}
  					
  					else if(thisPlayer.ID == Integer.parseInt(holder[0])) //<< This player receives a new position from the player
  					{
  						thisPlayer.SetPosition(Integer.parseInt(holder[1]), Integer.parseInt(holder[2]));
  						continue;
  					}
  					else if (!playerList.containsKey(playerID)) //<< If we get an update from a player we don't have in our list
  					{
  						Player enemy = new Player("Enemy_player_right.png", playerID);
  						enemy.SetEnemyPosition(Integer.parseInt(holder[1]), Integer.parseInt(holder[2]));
  						playerList.put(playerID, enemy);			
  					}		
  					else if (playerList.containsKey(playerID))  //<< If we get an update from an already known player
  					{
  						playerList.get(playerID).SetEnemyPosition(Integer.parseInt(holder[1]), Integer.parseInt(holder[2]));	
  					}
  			    }
  	    	}
  		    catch (IOException e) {} 	 
  	    }
  	}
}
