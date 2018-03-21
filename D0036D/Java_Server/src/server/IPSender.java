package server;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;

class IPSender implements Runnable
{	
	Thread thread;
	String tempo = "";
	public MulticastSocket socket;
	
	public IPSender()
	{
		thread = new Thread(this);
		thread.start();
	}
	
	
	@Override
	public void run()
	{
		try 
		{
			String port = "7777";
			InetAddress serverIP = InetAddress.getLocalHost();
			String ip = serverIP.toString();
			System.out.println(ip);
			String[] iplist = ip.split("/");
			byte[] bytePackage = new byte[500];
			DatagramPacket holder = new DatagramPacket(bytePackage, bytePackage.length);
			InetAddress group = InetAddress.getByName("239.255.255.250");
			socket = new MulticastSocket(1900);
			socket.joinGroup(group);
			String check = "";
			while(true)
			{
				
				byte[] bp = new byte[500];
				DatagramPacket data = new DatagramPacket(bp, bp.length);		
				socket.receive(data);
				String temp = new String(data.getData(),0,data.getLength());
				check = new String(holder.getData(),0,holder.getLength());
				if (temp.equals(check))
				{
					continue;
				}
				String[] templist = temp.split(" ");
				if (templist[0].equals("SERVICE") && templist[1].equals("QUERY") && templist[2].equals("JavaGameServer"))
				{
					tempo = "SERVICE REPLY JavaGameServer BattleOfCanons " + iplist[1] + " " + port; 
					DatagramPacket pack = new DatagramPacket(tempo.getBytes(),tempo.length());
					pack.setAddress(group);
					pack.setPort(1900);
					socket.send(pack);
					holder = pack;
				}
			}
		} 
		catch (IOException e ) 
		{
			e.printStackTrace();
		}
	}
}