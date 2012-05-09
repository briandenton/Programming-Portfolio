/**
 * GamePanel.java file.
 *
 * @author Brian Denton
 */

import java.awt.GridLayout;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JOptionPane;
import javax.swing.JPanel;

/**
 * This is the graphical representation of the playing field, which is made up of 
 * height X width squares
 */
public class GamePanel extends JPanel implements MouseListener{ 
  
  private int height, width;
 
 /**
  * A reference to the game master. 
  * This is because the GamePanel uses the data from the game master.
  */
 public GameMaster master;
 
 /**
  * A reference to the mainFrame.
  * This is because the GamePanel needs to set the counter, the status 
  * of the button (with a face).
  */
 private MainFrame mainFrame;
 
    /**
     * Creates a panel of according to the height and width stored in the master.
     * The panel contains height X width squares.
     * And the constructor also saves a reference of mainFrame.
  * @param master  the object stored all the data of the game
  * @param mainFrame the object of the main window of the game.
  */
    public GamePanel(GameMaster master, MainFrame mainFrame){
     
     // TODO 1: Get the height and width from the master.
     
        height = master.getHeight();
        width = master.getWidth();
        
     // TODO 2: Store the master and mainFrame.
     
        this.master = master;
        this.mainFrame = mainFrame;
        
     // TODO 3: Initiate the panel, and use GridLayout.    
        
        JPanel gamePanel = new JPanel( new GridLayout( height, width) );

        setLayout(new GridLayout(height, width));
        
     // TODO 4: Create all the squares and add them into the panel. In
     // addition, for each of them, you should call master.setSquarePos(), so
     // you can get it by the position later.

        for( int i = 0; i < height; i++){

            for( int j = 0; j < width; j++ ){

                Square square = new Square(i,j);
                master.setStateAt( i, j, State.SQUARE_COVERED );
                square.addMouseListener( this );
                add( square );
                master.setSquarePos(i,j,square);           
                
            }

        }

        master.setMines( MainFrame.numMine );
     
     // TODO 5: Finally, you should refresh the panel.

        refreshPanel();

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
 public void mouseClicked(MouseEvent event){
    
        //Nothing to do for this project

 }
 
 /**
  * Nothing to do for this project.
  */
 public void mouseEntered(MouseEvent arg0){
    
        //Nothing to do for this project
    
 }

 /**
  * Nothing to do for this project.
  */
 public void mouseExited(MouseEvent arg0){
    
        //Nothing to do for this project
    
 }

 /**
  * When a mouse pressed event occurs, if the game is STILL in process, the icon of 
  * the button with a face in the mainFrame should be set to Ooo.gif. 
  */
 public void mousePressed(MouseEvent arg0) {
  // TODO: if the game is still in process, call mainFrame.mousePressed().

     if (master.getGameState() == State.INPROCESS){
  
            mainFrame.mousePressed();

     }

 }
 
 /**
  * When this event occurs, if the game is STILL in process, the icon of the button 
  * with a face in the mainFrame should be set to smile.png.
  * If the left/right click event isn't handled in the mouseClicked(), it should be
  * processed here.
  */
     

 public void mouseReleased(MouseEvent event){
  // TODO 1: if the game is still in process, call mainFrame.mouseReleased().

     Square newSquare = (Square)event.getSource();

     if ( master.getGameState() == State.INPROCESS ){

            mainFrame.mouseReleased();

     }
     
  
  // TODO 2: If it is a left click, call master.uncoverSquare(), and catch
  // the possible exceptions. Check the whether the game is over, and if
  // so, pop up a message and refresh the panel to show the final icons.


    if( !event.isMetaDown() ){

        try{

            master.uncoverSquare( newSquare.getRow(), newSquare.getCol() );
         
         
        }catch( InvalidClickException e ){
          
          if( master.getGameState() == State.INPROCESS && master.getStateAt( newSquare.getRow(), newSquare.getCol() ) == State.SQUARE_UNCOVERED ){
           
             JOptionPane.showMessageDialog( null, "You cannot overturn an uncovered square." );
          
          }
          
          else if( master.getGameState() == State.INPROCESS && master.getStateAt( newSquare.getRow(), newSquare.getCol() ) == State.SQUARE_FLAGGED ){
           
             JOptionPane.showMessageDialog( null, "You cannot overturn a flagged square." );
          
          }
          
        }
        
        
        
        
        
        
        if ( master.getGameState() != State.INPROCESS ){

            if( master.getGameState() == State.WIN ){
                
                mainFrame.setWinFace();
                JOptionPane.showMessageDialog(null, "You win!");
                master.gameState = -1;//Don't show dialog again
                    
            }
               
            else if( master.getGameState() == State.LOSE ){
                
                mainFrame.setLoseFace();
                JOptionPane.showMessageDialog(null, "You lose.");
                master.gameState = -1;//Don't show dialog again                
            }

            refreshPanel();
            
            }
        }

     
  
  // TODO 3: If it is a right click, call master.flagSquare, and catch
  // the possible exceptions. And update the counter in the main frame.

    if( event.isMetaDown() ){
    
        try{
        
            master.flagSquare(newSquare.getRow(), newSquare.getCol() );
            refreshPanel();

        }catch( InvalidClickException e ){
          
          if( master.getGameState() == State.INPROCESS && master.getStateAt( newSquare.getRow(), newSquare.getCol() ) == State.SQUARE_UNCOVERED ){
           
             JOptionPane.showMessageDialog( null, "You cannot flag an uncovered square." );
          
          }

        }

        mainFrame.setCounter( master.getToBeFlaggedNum() );
        

     }

  // TODO 4: Refresh the panel.

     refreshPanel();

     }

}
