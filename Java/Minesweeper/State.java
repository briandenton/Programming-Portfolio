/**
 * State.java file.
 *
 * @author Brian Denton
 */


public class State {
	/**
	 * The constant indicates the game is won.
	 */
	public static final int WIN = 1;
	/**
	 * The constant indicates the game is lost.
	 */
	public static final int LOSE = 2;
	/**
	 * The constant indicates the game is still in process.
	 */
	public static final int INPROCESS = 3;
	
	/**
	 * The constant indicates the square is covered.
	 */	
	public static final int SQUARE_COVERED = 0;
	/**
	 * The constant indicates the square has been flagged.
	 */
	public static final int SQUARE_FLAGGED = 2;
	/**
	 * The constant indicates the square has been uncovered.
	 */	
	public static final int SQUARE_UNCOVERED = 1;
	
	/**
	 * The constant indicates the square contains a mine.
	 */
	public static final int MINE = -1;

}
