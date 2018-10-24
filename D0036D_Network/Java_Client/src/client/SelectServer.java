package client;
import java.awt.FlowLayout;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import javax.swing.*;


@SuppressWarnings("serial")
public class SelectServer extends JFrame implements ActionListener
{
	public MulticastSocket socket;

	InetAddress group;
	JButton serverButton;
	JButton connectButton;
	JComboBox<String> box;
	
	Boolean connectingToServer = false;
	public String ip = "";
	public int port = 0;
	
	/*Constructor for the SelectServer
	 * Sets up the selection window and adds buttons and ComboBox
	 * */
	public SelectServer() throws IOException, InterruptedException
	{
		group = InetAddress.getByName("239.255.255.250");
		socket = new MulticastSocket(1900);
		socket.joinGroup(group);	
		
		JFrame frame = new JFrame("Server Selection");
		
		frame.setLayout(new FlowLayout());
		frame.setSize(800, 400);

		serverButton = new JButton("Find servers");
		serverButton.addActionListener(this);
		connectButton = new JButton("Connect to Server");
		connectButton.addActionListener(this);

		box = new JComboBox<String>();
		
		frame.add(serverButton);
		frame.add(connectButton);
		frame.add(box);
		frame.setVisible(true);
		frame.setResizable(false);
		frame.setDefaultCloseOperation(EXIT_ON_CLOSE);

		@SuppressWarnings("unused")
		ServerListener serverListener = new ServerListener();

		while(!connectingToServer)	
		{
			Thread.sleep(1);
		}
		
		frame.dispose();
		return;
	}
	
	/*Method that registers button actions
	 * @Param ActionEvent e, the button that was pressed
	 * */
	public void actionPerformed(ActionEvent e)
	{
		if(e.getSource() == serverButton)
		{
			try 
			{
				String msg = "SERVICE QUERY JavaGameServer";
				DatagramPacket pack = new DatagramPacket(msg.getBytes(),msg.length());
				pack.setAddress(group);
				pack.setPort(1900);
				socket.send(pack);
			} 
			catch (IOException e1) 
			{
				e1.printStackTrace();
			}				
		}
		
		if(e.getSource() == connectButton)
		{
			if(box.getItemCount() == 0)
			{
				System.out.println("No server found!");
				return;
			}
			
			String selected = String.valueOf(box.getSelectedItem());
			String[] serverList = selected.split(":");
			ip = serverList[1];
			port = Integer.parseInt(serverList[2]);
			connectingToServer = true;
		}
	}
	
	class ServerListener implements Runnable
	{
		public ServerListener()
		{
			Thread thread = new Thread(this);
			thread.start();
		}

		@Override
		public void run() 
		{
			while(true)
			{
				try 
				{
					byte[] bytepack = new byte[500];
					DatagramPacket data = new DatagramPacket(bytepack, bytepack.length);		
					socket.receive(data);
					String temp = new String(data.getData(),0,data.getLength());
					String[] msg = temp.split(" ");
					if (msg[0].equals("SERVICE") && msg[1].equals("REPLY"))
					{
						if (msg[2].equals("JavaGameServer"))
						{
							System.out.println(msg[3]);
							String server = msg[3] + ":" + msg[4] + ":" + msg[5];
							box.addItem(server);
						}
					}			
				}
				catch (IOException | ArrayIndexOutOfBoundsException e) 
				{
					continue;
				}
			}
		}
		
	}
	
}

