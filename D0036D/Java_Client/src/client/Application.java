package client;
import java.awt.EventQueue;
import java.io.IOException;
import java.net.UnknownHostException;

import javax.swing.JFrame;


@SuppressWarnings("serial")
public class Application extends JFrame 
{
	Board board;
	/*Constructor for Application, creates the playing board
	 * @Param String ip, the ip for the server
	 * @Param int port, the server port
	 * */
    public Application(String ip, int port) throws UnknownHostException 
    {
    	board = new Board(ip, port);
        add(board);
        setSize(800, 795);
        setResizable(false);
        setTitle("Canon Battle");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        addWindowListener(new java.awt.event.WindowAdapter() 
        {
            @Override
            public void windowClosing(java.awt.event.WindowEvent windowEvent) //<< When the window is closed we want to close the client socket
            {
            	System.out.println("ByeBye");
            	try 
            	{
					board.OnExit();
				} 
            	catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
            }
        });
    }
    

    
    //Main function
    public static void main(String[] args) throws IOException, InterruptedException 
    {
    	SelectServer serv = new SelectServer();
        EventQueue.invokeLater(new Runnable() 
        {
            @Override
            public void run() 
            {
                Application ex;
				try 
				{
					ex = new Application(serv.ip, serv.port);
					ex.setVisible(true);
				} 
				catch (UnknownHostException e) 
				{
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
                
            }
        });
    }
}
