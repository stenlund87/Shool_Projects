/*
 * 
 */
package org.w3c.dom;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;




// TODO: Auto-generated Javadoc
/**
 * Class for the GUI window.
 *
 * @author ponste-5-local
 */
public class View extends JFrame 
{
	
	/** The panel. */
	public JPanel panel;
	
	/** The frame. */
	protected JFrame frame;
	
	/** The citybox. */
	public  JComboBox<?> citybox;
	
	/** The time box. */
	public  JComboBox<?> timeBox;
	
	/** The city label. */
	protected  JLabel cityLabel;
	
	/** The time label. */
	protected  JLabel timeLabel;
	
	/** The temp label. */
	protected  JLabel tempLabel;
	
	/** The expiration. */
	protected  JLabel expiration;
	
	/** The button. */
	protected  JButton button;

	/** The selected time. */
	protected  String selectedTime;
	
	/** The expiration time. */
	protected  String expirationTime;
	
	/** The time field. */
	protected  JTextField timeField;; 

	/** The box index. */
	public int boxIndex;
	
	/**
	 * Contructor for View
	 * Sets values to the different GUI elements.
	 */
	public View()
	{
		panel = new JPanel();
		add(panel);

		cityLabel = new JLabel("Stad");
		cityLabel.setSize(5, 100);
		cityLabel.setLocation(0, 350);
			
		timeLabel = new JLabel("Klockslag");
		
		timeField = new JTextField(8);
		timeField.setLocation(10, -250);
				
		button = new JButton("Tryck för update");
		button.setLocation(100, 100);

		tempLabel = new JLabel("");
		tempLabel.setLocation(0, 200);
		
		expiration = new JLabel("Hur länge ska cachen finnas i minuter");
		
	}

	
}
