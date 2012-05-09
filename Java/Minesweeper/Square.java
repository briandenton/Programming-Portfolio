/**
 * This class handles the interface portion of the Minsweeper game.
 *
 * @author Brian Denton
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Square extends JPanel  {

    private int row;
    private int col;

    private JLabel content;
    public ImageIcon contentImage;

  /**
     * Construct a cell with a given position
     *
     * @param pt the position of this cell on the board
     */
    public Square( int row, int col ) {
    
        this.row = row;
        this.col = col;

        setLayout(new BorderLayout());
        setBorder( BorderFactory.createLineBorder( Color.black ) );
        content = new JLabel();
        add(content);

    }

 /**
     * Returns its location.
     *
     * @return this cell's location in the board
     */

    public int getRow(){

        return this.row;

    }

    public int getCol(){

        return this.col;

    }

    public void setIcon( int mine, int state ){
    
      if( state == State.SQUARE_COVERED ){contentImage = new ImageIcon( "BLANK.PNG" );}
    
        else if( state == State.SQUARE_UNCOVERED ){
    
            if ( mine == 0 ){ contentImage = new ImageIcon( "0.PNG" ); }
                else if ( mine == 1 ){ contentImage = new ImageIcon( "1.PNG" ); }
                else if ( mine == 2 ){ contentImage = new ImageIcon( "2.PNG" ); }
                else if ( mine == 3 ){ contentImage = new ImageIcon( "3.PNG" ); }
                else if ( mine == 4 ){ contentImage = new ImageIcon( "4.PNG" ); }
                else if ( mine == 5 ){ contentImage = new ImageIcon( "5.PNG" ); }
                else if ( mine == 6 ){ contentImage = new ImageIcon( "6.PNG" ); }
                else if ( mine == 7 ){ contentImage = new ImageIcon( "7.PNG" ); }
                else if ( mine == 8 ){ contentImage = new ImageIcon( "8.PNG" ); }
                
        }
        
       else if( state == State.SQUARE_FLAGGED ){
          
            contentImage = new ImageIcon( "FLAG.PNG" );
        
        }
 
        content.setIcon( contentImage );
        
    }

    public void setFinalIcon( int mine, int state ){
    
        if ( mine == 0 ){ contentImage = new ImageIcon( "0.PNG" ); }
            else if ( mine == 1 ){ contentImage = new ImageIcon( "1.PNG" ); }
            else if ( mine == 2 ){ contentImage = new ImageIcon( "2.PNG" ); }
            else if ( mine == 3 ){ contentImage = new ImageIcon( "3.PNG" ); }
            else if ( mine == 4 ){ contentImage = new ImageIcon( "4.PNG" ); }
            else if ( mine == 5 ){ contentImage = new ImageIcon( "5.PNG" ); }
            else if ( mine == 6 ){ contentImage = new ImageIcon( "6.PNG" ); }
            else if ( mine == 7 ){ contentImage = new ImageIcon( "7.PNG" ); }
            else if ( mine == 8 ){ contentImage = new ImageIcon( "8.PNG" ); }

        else if( mine == -1 && state == State.SQUARE_COVERED ){
        
            contentImage = new ImageIcon( "MINE.PNG" );
            
        }
        
        else if( mine == -1 && state == State.SQUARE_UNCOVERED ){
        
            contentImage = new ImageIcon( "BOMB.PNG" );
            
        }
        
        else if( mine == -1 && state == State.SQUARE_FLAGGED ){
          
            contentImage = new ImageIcon( "correctflag.png" );
        
        }

        else if( mine != -1 && state == State.SQUARE_FLAGGED ){

            contentImage = new ImageIcon( "wrongmine.png" );
        
        }
        
        content.setIcon( contentImage );
        
    }


}
