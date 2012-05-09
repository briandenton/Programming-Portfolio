import java.awt.Point;
import java.util.ArrayList;

public class GameMaster {
	private int height, width;
	/**
	 * The total number of mines in the field.
	 */
	private int mineNum;
	/**
	 * The number of flagged squares.
	 */
	private int flaggedNum;

	/**
	 * squareMatrix[i][j] stores the Square object at the (i, j)
	 */
	private Square squareMatrix[][];
	/**
	 * digit[i][j] stores the number of mines in the adjacent squares of (i, j),
	 * if (i, j) doesn't contain a mine; or it is a value State.MINE ( -1) , if
	 * (i, j) contains a mine.
	 */
	private int digit[][];
	/**
	 * state[i][j] stores the state of the square at the (i, j). It can be
	 * State.SQUARE_COVERED, State.SQUARE_FLAGGED, State.SQUARE_UNCOVERED.
	 */
	private int state[][];

	/**
	 * The state of the game: State.WIN, State.LOSE or State.INPROCESS.
	 */
	private int gameState;

	/**
	 * It creates 3 array of height*width.
	 * 
	 * @param height
	 *            the height of the playing field
	 * @param width
	 *            the width of the playing field
	 */
	public GameMaster(int height, int width) {
		// TODO Complete the method.
	}

	/**
	 * It stores the square object to the squareMatrix(row,col).
	 */
	public void setSquarePos(int row, int col, Square square) {
		// TODO Complete the method.
	}

	/**
	 * It returns the square object at the (row,col) of squareMatrix.
	 */
	public Square getSquareAt(int row, int col) {
		// TODO Complete the method.
	}

	/**
	 * It returns the digit at the (row, col)
	 */
	public int getDigitAt(int row, int col) {
		// TODO Complete the method.
	}

	/**
	 * It returns the state at the (row, col)
	 */
	public int getStateAt(int row, int col) {
		// TODO Complete the method.
	}

	/**
	 * It set the state at the (row, col) to s.
	 */
	public void setStateAt(int row, int col, int s) {
		// TODO Complete the method.
	}

	public int getHeight() {
		return height;
	}

	public int getWidth() {
		return width;
	}

	public int getGameState() {
		return gameState;
	}

	/**
	 * It returns the number of squares yet to be flagged, which is shown in the
	 * counter.
	 */
	public int getToBeFlaggedNum() {
		return mineNum - flaggedNum;
	}

	/**
	 * It count the number of mines in the adjacent squares of square (row,
	 * col).
	 */
	private int calcDigits(int row, int col) {
		// TODO Complete the method.
		// Note: Please make sure only count those squares in the playing field.
	}

	/**
	 * Initiate the state and digit for each square. Randomly generate a layout
	 * of mines which contains exactly mineNum mines.
	 */
	public void setMines(int mineNum) {
		// TODO 1: Initiate the state and digit arrays.

		// TODO 2: Randomly put mineNum mines in the field.

		// TODO 3: For each square without a mine, call calcDigits() to
		// calculate the number of mines in adjacent squares, and update 
		// the digit array.

		// NOTE: Please do NOT remove the following lines, otherwise you may
		// fail the test of your project.
		showLayout();
	}

	/**
	 * Uncover a square at (row, col).
	 * 
	 * @return the state of the game.
	 */
	public int uncoverSquare(int row, int col) throws InvalidClickException {
		// TODO 1: If the square cannot be uncovered according to documents,
		// it throws an InvalidClickException exception. And the exception
		// should include a message "Mistaken uncover a square.", the state 
		// of the square at (row, col) and the gameState.

		// TODO 2: If the square contains a mine, users lose the game.

		// TODO 3: If a square doesn't have a mine and the digit is 0, call
		// expandSquare(row, col).

		// TODO 4: Count the left uncovered squares, and if the number of left
		// squares is the same as total number of mines, users win the game.
	}

	/**
	 * Flag or unflag a square at (row, col).
	 */
	public void flagSquare(int row, int col) throws InvalidClickException {
		// TODO 1: If the square cannot be flagged or unflagged according to
		// documents, it throws an InvalidClickException exception. And the 
		// exception should include a message "Mistaken flag a square.", 
		// the state of the square at (row, col) and the gameState.

		// TODO 2: Flag or unflag the square, and update flaggedNum.
	}

	/**
	 * It will expand a square which doesn't contain a mine and doesn't have any
	 * mines around it. For the expansion rule, read the document.
	 */
	private void expandSquare(int row, int col) {
		ArrayList<Point> q = new ArrayList<Point>();
		int x, y;
		if (getDigitAt(row, col) != 0)
			return;
		Point p = new Point(row, col);
		setStateAt(row, col, State.SQUARE_UNCOVERED);
		try {
			q.add(p);
			while (!q.isEmpty()) {
				for (int dx = -1; dx <= 1; dx++)
					for (int dy = -1; dy <= 1; dy++) {
						x = q.get(0).x + dx;
						y = q.get(0).y + dy;
						if (isInField(x, y)) {
							if (getDigitAt(x, y) != State.MINE) {
								if (getStateAt(x, y) == State.SQUARE_COVERED) {
									setStateAt(x, y, State.SQUARE_UNCOVERED);
									if (getDigitAt(x, y) == 0) {
										q.add(new Point(x, y));
									}
								}
							}
						}
					}
				q.remove(0);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * It returns the number of uncovered squares in the field.
	 */
	private int countLeftSquares() {
	}

	/**
	 * Return whether the position (row, col) is in the field.
	 */
	private boolean isInField(int row, int col) {
	}

	/**
	 * Show the layout of the field in the standard output. The 'M' represents
	 * the mine, digit indicate the number of mines around the square. It will
	 * also count and show the number of mines in the field. You can use the
	 * output to check whether the layout is correct.
	 * 
	 * NOTE: Please do NOT modify this method, otherwise you may fail the test
	 * of your project.
	 */
	private void showLayout() {
		int row, col, c = 0;
		System.out.println("Total mines = " + mineNum);
		for (row = 0; row < height; row++) {
			for (col = 0; col < width; col++)
				if (getDigitAt(row, col) == State.MINE) {
					System.out.print("M");
					c++;
				} else
					System.out.print(digit[row][col]);
			System.out.println();
		}
		System.out.println("Total mines in the field = " + c);
	}
}
