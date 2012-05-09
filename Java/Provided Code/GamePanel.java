import java.awt.GridLayout;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JOptionPane;
import javax.swing.JPanel;

/**
 * This is the graphical representation of the playing field, which is made up of 
 * height X width squares
 */
public class GamePanel extends JPanel implements MouseListener {
	
	private int height, width;
	
	/**
	 * A reference to the game master. 
	 * This is because the GamePanel uses the data from the game master.
	 */
	private GameMaster master;
	
	/**
	 * A reference to the mainFrame.
	 * This is because the GamePanel needs to set the counter, the status 
	 * of the button (with a face).
	 */
	private MainFrame mainFrame;	
	
    /**
     * Creates a panel of according to the height and width stored in the gameMaster.
     * The panel contains height X width squares.
     * And the constructor also saves a reference of mainFrame.
	 * @param gameMaster  the object stored all the data of the game
	 * @param mainFrame the object of the main window of the game.
	 */
    public GamePanel(GameMaster gameMaster, MainFrame mainFrame) {
    	
    	// TODO 1: Get the height and width from the gameMaster.
    	
    	// TODO 2: Store the gameMaster and mainFrame.
    	
    	// TODO 3: Initiate the panel, and use GridLayout.
    	
    	// TODO 4: Create all the squares and add them into the panel. In
		// addition, for each of them, you should call master.setSquarePos(), so
		// you can get it by the postion later.
    	
    	// TODO 5: Finally, you should refresh the panel.
    }
    
    /**
     * Refresh the display of all the squares.
     * This method is called after the state of any square changed, 
     * or the state of the game changed.
     */
    public void refreshPanel()
    {
    	for (int row = 0; row < height; row++)
    	{
    		for (int col = 0; col < width; col++)
    		{
    			Square square = master.getSquareAt(row, col);
    			if (master.getGameState() == State.INPROCESS)
    				square.setIcon(master.getDigitAt(row, col), master.getStateAt(row, col));
    			else
    				square.setFinalIcon(master.getDigitAt(row, col), master.getStateAt(row, col));
    		}
    	}
    }
    
    /**
     * The left/right click event can be processed here. But it is recommended to be processed 
     * in the mouseReleased().
     */
	public void mouseClicked(MouseEvent event) {

	}
	
	/**
	 * Nothing to do for this project.
	 */
	public void mouseEntered(MouseEvent arg0) {
	}

	/**
	 * Nothing to do for this project.
	 */
	public void mouseExited(MouseEvent arg0) {
	}
	
	/**
	 * When a mouse pressed event occurs, if the game is STILL in process, the icon of 
	 * the button with a face in the mainFrame should be set to Ooo.png. 
	 */
	public void mousePressed(MouseEvent arg0) {
		// TODO: if the game is still in process, call mainFrame.mousePressed().
	}
	
	/**
	 * When this event occurs, if the game is STILL in process, the icon of the button 
	 * with a face in the mainFrame should be set to smile.png.
	 * If the left/right click event isn't handled in the mouseClicked(), it should be
	 * processed here.
	 */
	public void mouseReleased(MouseEvent event) {
		// TODO 1: if the game is still in process, call mainFrame.mouseReleased().
		
		// TODO 2: If it is a left click, call master.uncoverSquare(), and catch
		// the possible exceptions. Check the whether the game is over, and if
		// so, pop up a message and refresh the panel to show the final icons.
		
		// TODO 3: If it is a right click, call mater.flagSquare, and catch
		// the possible exceptions. And update the counter in the main frame.
		
		// TODO 4: Refresh the panel.
	}
}
