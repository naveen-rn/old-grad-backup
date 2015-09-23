package assign1;

public class QuixoBoard {
	enum Face {
		O, X, EMPTY;
		public String toString() {
			switch (this) {
			case X:
				return "X";
	case O:
		return "O";
	default:
		return "EMPTY";
		}
	}
}

enum Direction {
	RIGHT, LEFT, TOP, BOTTOM
};

public final int _boardSize = 5;
private Face[][] _board = new Face[_boardSize][_boardSize];
private Face playerSymbol = Face.X;

private enum WinResult {
	NONE, X, O, BOTH;
	public String toString() {
		switch (this) {
		case BOTH:
			return "BOTH";
	case X:
		return "X";
	case O:
		return "O";
	default:
		return "NONE";
			}
		}
	}

	public QuixoBoard() {
		initialize();
	}

	void initialize() {
		for (int row = 0; row < _boardSize; row++) {
			for (int column = 0; column < _boardSize; column++) {
				_board[row][column] = Face.EMPTY;
			}
		}
	}

	public boolean isGameOver() {
		return (whoWon() != Face.EMPTY);
	}

	public Face whoWon() {
		WinResult resDiagonals = winByDiagonal();
		WinResult resRows = winByRow();
		WinResult resColumns = winByColumn();

		if (resDiagonals == WinResult.BOTH || resRows == WinResult.BOTH
				|| resColumns == WinResult.BOTH) {
			return playerSymbol;
		} else if (resDiagonals == WinResult.X || resRows == WinResult.X
				|| resColumns == WinResult.X) {
			return Face.X;
		} else if (resDiagonals == WinResult.O || resRows == WinResult.O
				|| resColumns == WinResult.O) {
			return Face.O;
		}
		return Face.EMPTY;
	}

	WinResult winByColumn() {
		boolean xWon = false;
		boolean oWon = false;

		for (int row = 0; row < _boardSize; row++) {
			if (faceOf(row, 0) != Face.EMPTY) {
				for (int column = 1; column < _boardSize; column++) {
					if (faceOf(row, column) != faceOf(row, 0)) {
						break;
					}
					if (column == (_boardSize - 1)) {
						if (faceOf(row, 0).equals(Face.X))
							xWon = true;
						else
							oWon = true;
					}
				}
			}
		}

		if (xWon && oWon) {
			return WinResult.BOTH;
		} else if (xWon && !oWon) {
			return WinResult.X;
		} else if (!xWon && oWon) {
			return WinResult.O;
		} else {
			return WinResult.NONE;
		}
	}

	WinResult winByRow() {

		boolean xWon = false;
		boolean oWon = false;
		for (int column = 0; column < _boardSize; column++) {
			if (faceOf(0, column) != Face.EMPTY) {
				for (int row = 1; row < _boardSize; row++) {
					if (faceOf(row, column) != faceOf(0, column)) {
						break;
					}
					if (row == (_boardSize - 1)) {
						if (faceOf(0, column).equals(Face.X))
							xWon = true;
						else
							oWon = true;
					}
				}
			}
		}

		if (xWon && oWon) {
			return WinResult.BOTH;
		} else if (xWon && !oWon) {
			return WinResult.X;
		} else if (!xWon && oWon) {
			return WinResult.O;
		} else {
			return WinResult.NONE;
		}
	}

	WinResult winByDiagonal() {

		boolean xWon = false;
		boolean oWon = false;

		if (faceOf(0, 0) != Face.EMPTY) {
			for (int rowAndCol = 1; rowAndCol < _boardSize; rowAndCol++) {
				if (faceOf(rowAndCol, rowAndCol) != faceOf(0, 0)) {
					break;
				}
				if (rowAndCol == (_boardSize - 1)) {
					if (faceOf(0, 0).equals(Face.X)) {
						xWon = true;
					} else {
						oWon = true;
					}
				}
			}
		}

		if (faceOf(0, _boardSize - 1) != Face.EMPTY) {
			for (int row = 1; row < _boardSize; row++) {
				int column = _boardSize - 1 - row;
				if (faceOf(row, column) != faceOf(0, _boardSize - 1)) {
					break;
				}
				if (row == _boardSize - 1) {
					if (faceOf(row, column).equals(Face.X)) {
						xWon = true;
					} else {
						oWon = true;
					}
				}
			}
		}

		if (xWon && oWon) {
			return WinResult.BOTH;
		} else if (xWon && !oWon) {
			return WinResult.X;
		} else if (!xWon && oWon) {
			return WinResult.O;
		} else {
			return WinResult.NONE;
		}
	}

	public Face faceOf(int row, int column) {
		return _board[row][column];
	}

	void togglePlayerSymbol() {
		if (playerSymbol == Face.X) {
			playerSymbol = Face.O;
		} else if (playerSymbol == Face.O) {
			playerSymbol = Face.X;
		} else {
			playerSymbol = Face.X;
		}
	}

	boolean isMoveValidByLocation(int row, int column) {
		return (row == 0 || row == _boardSize - 1 || column == 0 || column == _boardSize - 1);
	}

	boolean isMoveValidBySymbol(int row, int column, Direction moveDirection) {
		if (faceOf(row, column) == Face.EMPTY
				|| playerSymbol == faceOf(row, column)) {
			return true;
		}
		return false;
	}

	boolean isMoveValid(int row, int column, Direction moveDirection) {
		return (isMoveValidByLocation(row, column) && isMoveValidBySymbol(row,
				column, moveDirection));
	}

	public boolean moveBlock(int row, int column, Direction moveDirection) {
		if (isMoveValid(row, column, moveDirection)) {
			if ((_boardSize - 1) != column && moveDirection == Direction.RIGHT) {
				return (moveRight(row, column));
			}
			if (column != 0 && moveDirection == Direction.LEFT) {
				return (moveLeft(row, column));
			}
			if (row != 0 && moveDirection == Direction.TOP) {
				return (moveTop(row, column));
			}
			if (row != (_boardSize - 1) && moveDirection == Direction.BOTTOM) {
				return (moveBottom(row, column));
			}
		}
		return false;
	}

	boolean moveRight(int row, int column) {
		System.arraycopy(_board[row], column + 1, _board[row], column,
				_boardSize - column - 1);
		_board[row][_boardSize - 1] = playerSymbol;
		togglePlayerSymbol();
		return true;
	}

	boolean moveLeft(int row, int column) {
		System.arraycopy(_board[row], 0, _board[row], 1, _boardSize
				- (_boardSize - column));
		_board[row][0] = playerSymbol;
		togglePlayerSymbol();
		return true;
	}

	boolean moveBottom(int row, int column) {
		for (int count = 0; count < _boardSize - row - 1; count++) {
			System.arraycopy(_board[count + 1], column, _board[count], column,
					1);
		}
		_board[_boardSize - 1][column] = playerSymbol;
		togglePlayerSymbol();
		return true;
	}

	boolean moveTop(int row, int column) {
		for (int count = row - 1; count >= 0; count--) {
			System.arraycopy(_board[count], column, _board[count + 1], column,
					1);
		}
		_board[0][column] = playerSymbol;
		togglePlayerSymbol();
		return true;
	}

	Face getWhoPlaysNext() {
		return playerSymbol;
	}
}
