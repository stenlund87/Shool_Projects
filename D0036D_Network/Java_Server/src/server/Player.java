package server;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;

class Player implements Runnable
{
	public int xPos;
	public int yPos;
	
	public int deltaX;
	public int deltaY;
	
	public int ID;
	private	DataInputStream in;
	private DataOutputStream out;
	private DatagramSocket playerDatagramSocket;
	private Socket socket;
	private Thread playerThread;
	Server server;
	
	public Player(int clientID, Socket socket, DatagramSocket datagramSocket, Server server)
	{
		ID = clientID;
		this.socket = socket;
		this.server = server;
		playerDatagramSocket = datagramSocket;
		
		playerThread = new Thread(this);
		playerThread.start();
	}	


	@Override
	public void run() 
	{
		try
		{
			in = new DataInputStream(socket.getInputStream());
			out = new DataOutputStream(socket.getOutputStream());
			while(true)
			{
				String inData = in.readUTF();
				String[] holder = inData.split(":");
				if (holder[0].equals("Connect")) 
				{
					System.out.println("New player joined the game");
					xPos = 10;
					yPos = 10;
					out.writeUTF("NewPlayer:" + ID+":"+ xPos + ":" + yPos +":");
					
					for(int i = 0; i< server.playerList.size(); i++)
					{
						Thread.sleep(10);
						String dataString;
						dataString = server.playerList.get(i).ID + ":" + server.playerList.get(i).xPos + ":" + server.playerList.get(i).yPos + ":";
						DatagramPacket dataPackage = new DatagramPacket(dataString.getBytes(), dataString.length());
						dataPackage.setAddress(InetAddress.getByName("229.15.15.15"));
						dataPackage.setPort(7778);
						playerDatagramSocket.send(dataPackage);
						System.out.println("Sending players");
					}
				}
				else 
				{
					if (holder[1].equals("Move"))
					{
						if(ID == Integer.parseInt(holder[0]))
						{
							if(holder[2].equals("Up"))
							{
								deltaY = -10;
							}
							else if(holder[2].equals("Down"))
							{
								deltaY = 10;
							}
							else if(holder[2].equals("Left"))
							{
								deltaX = -10;
							}
							else if(holder[2].equals("Right"))
							{
								deltaX = 10;
							}
						}
					}
					else if (holder[1].equals("Stop"))
					{

						if(ID == Integer.parseInt(holder[0]))
						{
							deltaY = 0;
							deltaX = 0;
						}
					}
					else if(holder[1].equals("Leave"))
					{
						System.out.println("Client wants to exit!");
						String data = ID + ":Leave:Game:";
						DatagramPacket dataPackage = new DatagramPacket(data.getBytes(), data.length());
						dataPackage.setAddress(InetAddress.getByName("229.15.15.15"));
						dataPackage.setPort(7778);
						playerDatagramSocket.send(dataPackage);
						server.RemovePlayer(ID);
						playerThread.join();
						return;
					}
				}
				server.MovePlayers();
				String dataString;
				dataString = ID + ":" + xPos + ":" + yPos + ":";
				System.out.println(dataString);
				DatagramPacket dataPackage = new DatagramPacket(dataString.getBytes(), dataString.length());
				dataPackage.setAddress(InetAddress.getByName("229.15.15.15"));
				dataPackage.setPort(7778);
				playerDatagramSocket.send(dataPackage);
				System.out.println("Package sent");

			}
		}
		catch(IOException e)
		{
			return;
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}			
	}	
}
