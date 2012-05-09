/**
 * InvalidClickException.java file.
 *
 * @author Brian Denton
 */

public class InvalidClickException extends Exception {

    public int gameState;
    public int squareState;
    public String msg;

 public InvalidClickException(String msg, int squareState, int gameState) {
 
    super();

        this.msg = msg;
        this.squareState = squareState;
        this.gameState = gameState;
        
 }
    
    public int squareState( int row, int col ){

        return this.squareState;
    
    }

    
    public int gameState(){
    
        return this.gameState;
    
    }
    
}
