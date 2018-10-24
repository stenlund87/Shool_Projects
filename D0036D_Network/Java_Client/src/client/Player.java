package client;

import java.awt.Image;
import javax.swing.ImageIcon;

public class Player 
{
	 private int x;
	 private int y;
	 int ID;
	 private Image playerImage;
	 
	 /*Constructor for the player
	  * @Param String playerIcon, the path to the icon the player is gonna be
	  * */
	 public Player(String playerIcon, int playerID) 
	 {
        ImageIcon ii = new ImageIcon(playerIcon);
        playerImage = ii.getImage();
        x = 0;
        y = 0;
        ID = playerID;
	 }

	 /*Method to get player x position
	  * @Return int x, the X position of the player
	  * */
    public int GetX() 
    {
        return x;
    }

    /*Method to get player y position
     * @Return int y, the Y position of the player
    */
    public int GetY()
    {
        return y;
    }
    
    /*Method to get player icon
     * @Return Image playerImage
     * */
    public Image GetPlayerIcon() 
    {
       return playerImage;
    }
    
    /*Method to set player position and change its icon
     * @Param xPos, the X position we want set
     * @Param yPos, the Y position we want set
    */
    public void SetPosition(int xPos, int yPos)
    {
    	int dX = x - xPos;
    	int dY = y - yPos;
    	if(dX > 0)
    	{
    		ImageIcon imageIcon = new ImageIcon("Player_left.png");
    		playerImage = imageIcon.getImage();
    	}
    	else if(dX < 0)
    	{
    		ImageIcon imageIcon = new ImageIcon("Player_right.png");
    		playerImage = imageIcon.getImage();
    	}
    	if(dY > 0)
    	{
    		ImageIcon imageIcon = new ImageIcon("Player_up.png");
    		playerImage = imageIcon.getImage();
    	}
    	else if(dY < 0)
    	{
    		ImageIcon imageIcon = new ImageIcon("Player_down.png");
    		playerImage = imageIcon.getImage();
    	}
    	x = xPos;
    	y = yPos;
    }
    
    /*Method to set enemy player position and changes it's icon
     * @Param xPos, the X position we want to set
     * @Param yPos, the Y position we want to set
    */
    public void SetEnemyPosition(int xPos, int yPos)
    {
    	int dX = x - xPos;
    	int dY = y - yPos;
    	if(dX > 0)
    	{
    		ImageIcon imageIcon = new ImageIcon("Enemy_player_left.png");
    		playerImage = imageIcon.getImage();
    	}
    	else if(dX < 0)
    	{
    		ImageIcon imageIcon = new ImageIcon("Enemy_player_right.png");
    		playerImage = imageIcon.getImage();
    	}
    	if(dY > 0)
    	{
    		ImageIcon imageIcon = new ImageIcon("Enemy_player_up.png");
    		playerImage = imageIcon.getImage();
    	}
    	else if(dY < 0)
    	{
    		ImageIcon imageIcon = new ImageIcon("Enemy_player_down.png");
    		playerImage = imageIcon.getImage();
    	}
    	x = xPos;
    	y = yPos;
    }
    




}
