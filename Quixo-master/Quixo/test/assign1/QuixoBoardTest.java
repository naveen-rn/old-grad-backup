package assign1;

import assign1.QuixoBoard.Direction;
import assign1.QuixoBoard.Face;
import junit.framework.*;

public class QuixoBoardTest extends TestCase {

	private QuixoBoard _board;

	protected void setUp() {
		_board = new QuixoBoard();
	}

	public void testCanary() {
		assertTrue(true);
	}

	public void testCreateBoard() {
		assertFalse(_board.isGameOver());
	}

	public void testPlayerMoveFromPheriphery() {
		assertTrue(_board.isMoveValid(0, 0, Direction.BOTTOM));
	}

	public void testPlayerMoveNotFromPheriphery() {
		assertFalse(_board.isMoveValid(2, 2, Direction.BOTTOM));
	}

	public void testFirstPlayerMoveTopLeftToRight() {
		assertTrue(_board.moveRight(0, 0));
	}

	public void testValidateFirstPlayerMoveTopLeftToRight() {
		_board.moveRight(0, 0);
		assertEquals(Face.X, _board.faceOf(0, 4));
		assertEquals(Face.EMPTY, _board.faceOf(0, 0));
	}

	public void testValidateFirstPlayerMoveTopCenterToRight() {
		_board.moveRight(0, 2);
		assertEquals(Face.X, _board.faceOf(0, 4));
		assertEquals(Face.EMPTY, _board.faceOf(0, 2));
	}

	public void testFirstPlayerMoveTopRightToLeft() {
		assertTrue(_board.moveLeft(0, 4));
	}

	public void testValidateFirstPlayerMoveTopRightToLeft() {
		_board.moveLeft(0, 4);
		assertEquals(Face.X, _board.faceOf(0, 0));
		assertEquals(Face.EMPTY, _board.faceOf(0, 4));
	}

	public void testValidateFirstPlayerMoveTopCenterToLeft() {
		_board.moveLeft(0, 2);
		assertEquals(Face.X, _board.faceOf(0, 0));
		assertEquals(Face.EMPTY, _board.faceOf(0, 2));
	}

	public void testFirstPlayerMoveTopLeftToBottom() {
		assertTrue(_board.moveBottom(0, 0));
	}

	public void testValidateFirstPlayerMoveTopLeftToBottom() {
		_board.moveBottom(0, 0);
		assertEquals(Face.X, _board.faceOf(4, 0));
		assertEquals(Face.EMPTY, _board.faceOf(0, 0));
	}

	public void testValidateFirstPlayerMoveTopCenterToBottom() {
		_board.moveBottom(2, 0);
		assertEquals(Face.X, _board.faceOf(4, 0));
		assertEquals(Face.EMPTY, _board.faceOf(2, 0));
	}

	public void testFirstPlayerMoveBottomLeftToTop() {
		assertTrue(_board.moveTop(4, 0));
	}

	public void testValidateFirstPlayerMoveBottomLeftToTop() {
		_board.moveTop(4, 0);
		assertEquals(Face.X, _board.faceOf(0, 0));
		assertEquals(Face.EMPTY, _board.faceOf(4, 0));
	}

	public void testValidateFirstPlayerMoveBottomCenterToTop() {
		_board.moveTop(2, 0);
		assertEquals(Face.X, _board.faceOf(0, 0));
		assertEquals(Face.EMPTY, _board.faceOf(2, 0));
	}

	public void testFirstPlayerMoveTopRightToRight() {
		assertFalse(_board.moveBlock(0, 4, Direction.RIGHT));
	}

	public void testFirstPlayerMoveTopLeftToLeft() {
		assertFalse(_board.moveBlock(0, 0, Direction.LEFT));
	}

	public void testFirstPlayerMoveBottomLeftToBottom() {
		assertFalse(_board.moveBlock(4, 0, Direction.BOTTOM));
	}

	public void testFirstPlayerMoveTopLeftToTop() {
		assertFalse(_board.moveBlock(0, 0, Direction.TOP));
	}

	public void testMovePlayerBlockOnCornerAlreadyCovered() {
		_board.moveTop(0, 0);
		_board.moveTop(1, 1);
		assertFalse(_board.moveBlock(0, 0, Direction.TOP));
	}

	public void testMovePlayerBlockRight() {
		assertTrue(_board.moveBlock(4, 1, Direction.RIGHT));
	}

	public void testMovePlayerBlockLeft() {
		assertTrue(_board.moveBlock(3, 4, Direction.LEFT));
	}

	public void testMovePlayerBlockTop() {
		assertTrue(_board.moveBlock(4, 1, Direction.TOP));
	}

	public void testMovePlayerBlockBottom() {
		assertTrue(_board.moveBlock(0, 3, Direction.BOTTOM));
	}

	public void testSecondPlayerPositiveMove() {
		_board.moveBlock(0, 0, Direction.BOTTOM);
		assertTrue(_board.moveBlock(0, 0, Direction.BOTTOM));
	}

	public void testvalidateSecondPlayerPositiveMove() {
		_board.moveBlock(0, 0, Direction.BOTTOM);
		_board.moveBlock(0, 0, Direction.BOTTOM);
		assertEquals(Face.EMPTY, _board.faceOf(0, 0));
		assertEquals(Face.X, _board.faceOf(3, 0));
		assertEquals(Face.O, _board.faceOf(4, 0));
	}

	public void testSecondPlayerMoveOnFirstPlayersBlock() {
		_board.moveBlock(0, 0, Direction.BOTTOM);
		assertFalse(_board.moveBlock(4, 0, Direction.TOP));
	}

	public void testWinByColumnByPlayer1() {
		_board.moveBlock(0, 0, Direction.RIGHT);
		_board.moveBlock(4, 0, Direction.RIGHT);
		_board.moveBlock(0, 0, Direction.RIGHT);
		_board.moveBlock(4, 0, Direction.RIGHT);
		_board.moveBlock(0, 0, Direction.RIGHT);
		_board.moveBlock(4, 0, Direction.RIGHT);
		_board.moveBlock(0, 0, Direction.RIGHT);
		_board.moveBlock(4, 0, Direction.RIGHT);
		_board.moveBlock(0, 0, Direction.RIGHT);
		assertEquals(Face.X, _board.whoWon());
	}

	public void testWinByColumnByPlayer2() {
		_board.moveBlock(0, 0, Direction.RIGHT);
		_board.moveBlock(4, 0, Direction.RIGHT);
		_board.moveBlock(0, 0, Direction.RIGHT);
		_board.moveBlock(4, 0, Direction.RIGHT);
		_board.moveBlock(0, 0, Direction.RIGHT);
		_board.moveBlock(4, 0, Direction.RIGHT);
		_board.moveBlock(0, 0, Direction.RIGHT);
		_board.moveBlock(4, 0, Direction.RIGHT);
		_board.moveBlock(3, 0, Direction.RIGHT);
		_board.moveBlock(4, 0, Direction.RIGHT);
		assertEquals(Face.O, _board.whoWon());
	}

	public void testWinByRowByPlayer1() {
		_board.moveBlock(0, 0, Direction.BOTTOM);
		_board.moveBlock(0, 4, Direction.BOTTOM);
		_board.moveBlock(0, 0, Direction.BOTTOM);
		_board.moveBlock(0, 4, Direction.BOTTOM);
		_board.moveBlock(0, 0, Direction.BOTTOM);
		_board.moveBlock(0, 4, Direction.BOTTOM);
		_board.moveBlock(0, 0, Direction.BOTTOM);
		_board.moveBlock(0, 4, Direction.BOTTOM);
		_board.moveBlock(0, 0, Direction.BOTTOM);
		assertEquals(Face.X, _board.whoWon());
	}

	public void testWinByRowByPlayer2() {
		_board.moveBlock(0, 0, Direction.BOTTOM);
		_board.moveBlock(0, 4, Direction.BOTTOM);
		_board.moveBlock(0, 0, Direction.BOTTOM);
		_board.moveBlock(0, 4, Direction.BOTTOM);
		_board.moveBlock(0, 0, Direction.BOTTOM);
		_board.moveBlock(0, 4, Direction.BOTTOM);
		_board.moveBlock(0, 0, Direction.BOTTOM);
		_board.moveBlock(0, 4, Direction.BOTTOM);
		_board.moveBlock(0, 2, Direction.BOTTOM);
		_board.moveBlock(0, 4, Direction.BOTTOM);
		assertEquals(Face.O, _board.whoWon());
	}

	public void testWinByMainDiagonalByPlayer1() {
		_board.moveBlock(0, 4, Direction.LEFT);
		_board.moveBlock(4, 4, Direction.LEFT);
		_board.moveBlock(1, 4, Direction.LEFT);
		_board.moveBlock(1, 4, Direction.LEFT);
		_board.moveBlock(0, 4, Direction.BOTTOM);
		_board.moveBlock(3, 0, Direction.RIGHT);
		_board.moveBlock(0, 3, Direction.BOTTOM);
		_board.moveBlock(0, 3, Direction.BOTTOM);
		_board.moveBlock(0, 2, Direction.BOTTOM);
		_board.moveBlock(0, 2, Direction.BOTTOM);
		_board.moveBlock(0, 2, Direction.BOTTOM);
		assertEquals(Face.X, _board.whoWon());
	}

	public void testWinByMainDiagonalByPlayer2() {
		_board.moveBlock(0, 4, Direction.LEFT);
		_board.moveBlock(0, 4, Direction.LEFT);
		_board.moveBlock(4, 4, Direction.LEFT);
		_board.moveBlock(1, 4, Direction.LEFT);
		_board.moveBlock(1, 4, Direction.LEFT);
		_board.moveBlock(0, 4, Direction.BOTTOM);
		_board.moveBlock(3, 0, Direction.RIGHT);
		_board.moveBlock(0, 3, Direction.BOTTOM);
		_board.moveBlock(0, 3, Direction.BOTTOM);
		_board.moveBlock(0, 2, Direction.BOTTOM);
		_board.moveBlock(0, 2, Direction.BOTTOM);
		_board.moveBlock(0, 2, Direction.BOTTOM);
		assertEquals(Face.O, _board.whoWon());
	}

	public void testWhoWonWithoutAWinner() {
		_board.moveBlock(0, 0, Direction.RIGHT);
		_board.moveBlock(4, 0, Direction.RIGHT);
		_board.moveBlock(0, 0, Direction.RIGHT);
		_board.moveBlock(4, 0, Direction.RIGHT);
		assertFalse(_board.isGameOver());
	}
}