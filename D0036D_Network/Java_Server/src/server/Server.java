package server;

import java.net.*;
import java.util.Vector;
import java.io.*;

//Server class
public class Server extends Thread
{
	private ServerSocket serverSocket;
	Socket socket;
	MulticastSocket msSocket;
	DatagramSocket datagramSocket;
	int clientID = 1;
	Vector<Player> playerList = new Vector<Player>();
	
	/*Constructor for server. Binds the server and datagram socket to port
	*@Param int port, the server port that will be bound
	*/
	public Server(int port) throws IOException
	{
		serverSocket = new ServerSocket(port);
		datagramSocket = new DatagramSocket(port);
	}
	
	public void run()
	{
		@SuppressWarnings("unused")
		IPSender sender = new IPSender();
		System.out.println("Port " + serverSocket.getLocalPort() + " bound. Waiting for clients..." );
		while(true)
		{	
			try
			{
				socket = serverSocket.accept();
				System.out.println("New connection accepted");
				Player newPlayer = new Player(clientID, socket, datagramSocket, this);
				clientID += 1;
				playerList.add(newPlayer);
				System.out.println("Player added");

			}
			catch (IOException e)
			{
				e.printStackTrace();
				break;
			}
		}
	}
	
	public void MovePlayers()
    {
    	for(int i=0;i<playerList.size();i++)
    	{
    		if((playerList.get(i).xPos + playerList.get(i).deltaX) > 0 && (playerList.get(i).xPos + playerList.get(i).deltaX) < 760) //<< Limits the player X movement inside the map
    		{
        		playerList.get(i).xPos += playerList.get(i).deltaX;
    		}
    		if((playerList.get(i).yPos + playerList.get(i).deltaY) > 0 && (playerList.get(i).yPos + playerList.get(i).deltaY) < 730) //<< Limits the player Y movement inside the map
    		{
        		playerList.get(i).yPos += playerList.get(i).deltaY;
    		}

    	}
    }
	
	public void RemovePlayer(int id)
	{
		int index = 0;
		for(int i=0;i<playerList.size();i++)
		{
			if(playerList.get(i).ID == id)
			{
				index = i;
				break;
			}
		}
		playerList.remove(index);
	}
	
    public static void main(String[] args) 
    {
    	int port = 7777;
    	try
    	{
    		Thread thread = new Server(port);
    		thread.start();
    	}
    	catch(IOException e)
    	{
    		e.printStackTrace();
    	}
    }
    
}








