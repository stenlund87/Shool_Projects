
package org.w3c.dom;


import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;


import javax.swing.JComboBox;
import javax.swing.JFrame;


import java.lang.Object;
import java.text.ParseException;



/**
 * The Class Controller.
 */
public class Controler implements WindowListener
{
	
	private View gui;
	private Model model;
	
	/** The event. */
	public Event event;
	
	//private Window window;

	/**
	 * Class for controlling data flow.
	 */
	public Controler()
	{
		event = new Event();
	}
	
	/**
	 * A sub-class so stuff happens when the user click the button.
	 */
	public class Event implements ActionListener
	{
		
		/**
		 * Instantiates a new event.
		 */
		public Event()
		{

		}
		
		/**
		 * Method to update the weather when the button is pressed.
		 * @param e the e
		 */
		public void actionPerformed(ActionEvent e)
		{
			String time = "";
			gui.selectedTime = gui.timeField.getText();
			String expiration = model.expirationArr[gui.timeBox.getSelectedIndex()];
			int index = gui.citybox.getSelectedIndex();
			//System.out.println("first "+index);
			/**
			 * Used for getting how long the cache will exist
			 */
			if(expiration == "1" && model.expiredArr[index])
			{
				model.timeToLive[index] = 60000;
			}
			
			else if(expiration == "5" &&  model.expiredArr[index])
			{
				model.timeToLive[index] = 5*60000;
			}
			
			else if(expiration == "10" &&  model.expiredArr[index])
			{
				model.timeToLive[index] = 10*60000;
			}
			
			else if(expiration == "60" &&  model.expiredArr[index])
			{
				model.timeToLive[index] = 60*60000;
			}
			
			/**
			 * Used to build a string which will be used to search the weather for the given time
			 */
			if(gui.selectedTime.length() == 1)
			{
				time = "0"+gui.selectedTime+":00";
			}
			else if(gui.selectedTime.length() == 2)
			{
				time = gui.selectedTime + ":00";
				if(time.equals("24:00"))
				{
					time = "00:00";
				}
			}
			else if(gui.selectedTime.length() == 0)
			{
				time = "";
			}
			
			/**
			 * Calls Models UpdateWeather() to get a string wich will be used to update the weather
			 */
			String temperature = null;
			try 
			{
				temperature = model.UpdateWeather(model.cityArr[gui.citybox.getSelectedIndex()].toString(),gui.citybox.getSelectedIndex(), time);
			} 
			catch (ParseException e1) 
			{
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			
			/**
			 * Updates the e.gui with the given weather
			 */
			gui.tempLabel.setText(temperature);
		}	

	}
	
	/**
	 * main method to start the program.
	 *
	 * @param args the arguments
	 * @throws ParseException 
	 */
	public static void main(String[] args) throws ParseException
	{
		Controler e = new Controler();
		e.model = new Model();
		e.model.GetLocation();

		for(int i = 0; i< e.model.expiredArr.length; i++)
		{
			e.model.IsExpired(i);
		}
		
		e.gui = new View();
		e.gui.citybox = new JComboBox<Object>(e.model.cityArr);
		e.gui.panel.add(e.gui.cityLabel);
		e.gui.panel.add(e.gui.citybox);
		e.gui.panel.add(e.gui.timeLabel);
		e.gui.panel.add(e.gui.timeField);
		e.gui.panel.add(e.gui.expiration);
		e.gui.timeBox = new JComboBox<Object>(e.model.expirationArr);
		e.gui.panel.add(e.gui.timeBox);
		e.gui.panel.add(e.gui.button);
		e.gui.button.addActionListener(e.event);
		e.gui.panel.add(e.gui.tempLabel);
		e.gui.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		e.gui.setSize(400, 300);
		e.gui.addWindowListener(e);
		e.gui.setTitle("Weather Checker");

		e.gui.setResizable(false);
		e.gui.setVisible(true);

	}

	@Override
	public void windowActivated(WindowEvent e) 
	{
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowClosing(WindowEvent e) 
	{
		System.out.println(model.expirationDateArr[0]);
		model.SetCacheToFile();
		System.out.println("Hejdå");
		
	}

	@Override
	public void windowDeactivated(WindowEvent e) 
	{
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowDeiconified(WindowEvent e) 
	{
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowIconified(WindowEvent e) 
	{
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowOpened(WindowEvent e) 
	{
		// TODO Auto-generated method stub
		
	}

	@Override
	public void windowClosed(WindowEvent arg0) {
		// TODO Auto-generated method stub
		
	}

}
