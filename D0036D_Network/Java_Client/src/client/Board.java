package client;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.io.IOException;
import java.net.UnknownHostException;

import javax.swing.JPanel;
import javax.swing.Timer;


@SuppressWarnings("serial")
public class Board extends JPanel implements ActionListener 
{

	private Timer timer;
    private Client client;
    private final int DELAY = 10;

    /*Constructor for Board. 
     * Adds a key listener,set background color of the board and creates a new Client object
     * @Param String ip, the server ip. Needed to create Client object
     * @Param int port, the server port. Needed to create Client object 
     * */
    public Board(String ip, int port) throws UnknownHostException 
    {
        addKeyListener(new TAdapter());
        setFocusable(true);
        setBackground(Color.GRAY);
        timer = new Timer(DELAY, this);
        timer.start();  
        client = new Client(ip, port);        
    }

    public void OnExit() throws IOException
    {
    	client.Exit();
    }
    
    @Override
    public void paintComponent(Graphics g) 
    {
        super.paintComponent(g);
        client.doDrawing(g,this);
        Toolkit.getDefaultToolkit().sync();
    }


    @Override
    public void actionPerformed(ActionEvent e) 
    {
        repaint();  
    }

    private class TAdapter extends KeyAdapter 
    {
        @Override
        public void keyReleased(KeyEvent e) 
        {
        	try 
        	{
				client.keyReleased(e);
			} 
        	catch (IOException e1)
        	{
				e1.printStackTrace();
			}
        }

        @Override
        public void keyPressed(KeyEvent e) 
        {
        	try 
        	{
				client.keyPressed(e);
			} 
        	catch (IOException e1)
        	{
				e1.printStackTrace();
			}
        }
    }
}
