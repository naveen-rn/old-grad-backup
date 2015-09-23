package assign1;

import javax.swing.*;
import javax.swing.plaf.basic.*;

import assign1.QuixoBoard.Direction;
import assign1.QuixoBoard.Face;

import java.awt.event.*;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.Toolkit;
import java.util.*;

public class QuixoBoardFrame extends JFrame {
	public QuixoBoardFrame() {
		initialize();
	}

	public void initialize() {
		setLayout(new GridLayout(1, 2));
		QuixoBoardPanel boardFrame = new QuixoBoardPanel();
		QuixoArrowsPanel arrowFrame = new QuixoArrowsPanel();

		arrowFrame.setVisible(true);
		boardFrame.setVisible(true);

		add(arrowFrame);
		add(boardFrame);

		setTitle("Quixo");
		setMinimumSize(new Dimension(600, 400));
		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	}

	public static void main(String[] args) {
		QuixoBoardFrame mainFrame = new QuixoBoardFrame();
		mainFrame.setVisible(true);
	}
}

class QuixoBoardPanel extends JPanel implements ActionListener {
	private Integer previousButtonsRow = -1;
	private Integer previousButtonsColumn = -1;
	private boolean isPreviousButtonSet = false;

	private QuixoBoard _board = new QuixoBoard();
	private HashMap<String, JButton> 
		_nameToButton = new HashMap<String, JButton>();
	private HashMap<QuixoBoard.Face, String> 
		_faceToRepresentation = new HashMap<QuixoBoard.Face, String>() {
		{
			put(QuixoBoard.Face.X, "X");
	put(QuixoBoard.Face.O, "O");
	put(QuixoBoard.Face.EMPTY, " ");
	}
};

QuixoBoardPanel() {
	setLayout(new GridLayout(_board._boardSize, _board._boardSize));
	for (int row = 0; row < _board._boardSize; ++row) {
		for (int column = 0; column < _board._boardSize; ++column) {
			JButton button = new JButton();
			button.setName(row + "_" + column);
		button.addActionListener(this);
		button.setVisible(true);
		add(button);
		_nameToButton.put(button.getName(), button);
	}
}
setName("QuixoBoardPanel");
	drawAllComponents();
}

public void drawAllComponents() {
	for (int row = 0; row < _board._boardSize; row++) {
		for (int column = 0; column < _board._boardSize; ++column) {
			JButton currentButton = _nameToButton.get(row + "_" + column);
				QuixoBoard.Face currentFace = _board.faceOf(row, column);
				String representation = _faceToRepresentation.get(currentFace);
				currentButton.setText(representation);
			}
		}
	}

	public void actionPerformed(ActionEvent e) {
		JButton eventButton = (JButton) e.getSource();
		String rawCoordinates = eventButton.getName();

		int row = Integer
				.parseInt(Character.toString(rawCoordinates.charAt(0)));
		int column = Integer.parseInt(Character.toString(rawCoordinates
				.charAt(2)));

		previousButtonsRow = row;
		previousButtonsColumn = column;
		isPreviousButtonSet = true;
		drawAllComponents();
	}

	Integer getPreviousRow() {
		return previousButtonsRow;
	}

	Integer getPreviousColumn() {
		return previousButtonsColumn;
	}

	boolean getIsPreviousButtonSet() {
		return isPreviousButtonSet;
	}

	void setIsPreviousButtonSet(boolean setValue) {
		isPreviousButtonSet = setValue;
	}

	QuixoBoard getQuixoBoard() {
		return _board;
	}
}

class QuixoArrowsPanel extends JPanel implements ActionListener {
	private HashMap<Integer, BasicArrowButton> 
		_directions = new HashMap<Integer, BasicArrowButton>();

	private HashMap<Integer, Direction> 
		_intToDirection = new HashMap<Integer, Direction>() {
		{
			put(BasicArrowButton.EAST, Direction.RIGHT);
			put(BasicArrowButton.WEST, Direction.LEFT);
			put(BasicArrowButton.NORTH, Direction.TOP);
			put(BasicArrowButton.SOUTH, Direction.BOTTOM);
		}
	};

	QuixoArrowsPanel() {
		BasicArrowButton buttonEast = new BasicArrowButton(
				BasicArrowButton.EAST);
		BasicArrowButton buttonWest = new BasicArrowButton(
				BasicArrowButton.WEST);
		BasicArrowButton buttonNorth = new BasicArrowButton(
				BasicArrowButton.NORTH);
		BasicArrowButton buttonSouth = new BasicArrowButton(
				BasicArrowButton.SOUTH);

		JButton buttonCenter = new JButton("RESTART");
buttonCenter.setName("restartButton");

BasicArrowButton[] buttonUseless = new BasicArrowButton[5];
for (int i = 0; i < buttonUseless.length; ++i) {
	buttonUseless[i] = new BasicArrowButton(BasicArrowButton.CENTER);
	buttonUseless[i].setVisible(false);
}

setLayout(new GridLayout(3, 3));

add(buttonUseless[0]);
add(buttonNorth);
add(buttonUseless[1]);
add(buttonWest);
add(buttonCenter);
add(buttonEast);
add(buttonUseless[2]);
add(buttonSouth);
add(buttonUseless[3]);

_directions.put(BasicArrowButton.EAST, buttonEast);
_directions.put(BasicArrowButton.WEST, buttonWest);
_directions.put(BasicArrowButton.NORTH, buttonNorth);
_directions.put(BasicArrowButton.SOUTH, buttonSouth);

for (Integer direction : _directions.keySet()) {
	_directions.get(direction).addActionListener(this);
	_directions.get(direction).setVisible(true);
}

buttonCenter.setVisible(true);

buttonCenter.addActionListener(new ActionListener() {
	public void actionPerformed(ActionEvent restartPressed) {

		QuixoBoardPanel boardPanel = null;

		for (Component component : getParent().getComponents()) {
			if (component.getName().equalsIgnoreCase("QuixoBoardPanel")) {
				boardPanel = (QuixoBoardPanel) component;
			}
		}
		QuixoBoard actualBoard = boardPanel.getQuixoBoard();

		int answer = new JOptionPane().showConfirmDialog(getParent(),
				"Are you sure you want to restart", "Do not leave",
				JOptionPane.YES_NO_OPTION);
		if (answer == JOptionPane.YES_OPTION) {
			actualBoard.initialize();
			boardPanel.drawAllComponents();

			if (actualBoard.getWhoPlaysNext() == Face.O) {
				actualBoard.togglePlayerSymbol();
			}
		}
	}
});

setName("QuixoArrowsPanel");
	setVisible(true);

}

public void actionPerformed(ActionEvent e) {
	BasicArrowButton buttonPressed = (BasicArrowButton) e.getSource();
	int buttonDirection = buttonPressed.getDirection();

	QuixoBoardPanel boardPanel = null;

	for (Component component : getParent().getComponents()) {
		if (component.getName().equalsIgnoreCase("QuixoBoardPanel")) {
		boardPanel = (QuixoBoardPanel) component;
	}
}

QuixoBoard board = boardPanel.getQuixoBoard();

if (boardPanel.equals(null)) {
	return;
}

boolean isPreviousButtonSet = boardPanel.getIsPreviousButtonSet();
if (isPreviousButtonSet) {
	int prevColumn = boardPanel.getPreviousColumn();
	int prevRow = boardPanel.getPreviousRow();

	if (board.isMoveValid(prevRow, prevColumn,
			_intToDirection.get(buttonDirection))) {
		board.moveBlock(prevRow, prevColumn,
				_intToDirection.get(buttonDirection));
		boardPanel.setIsPreviousButtonSet(false);
	} else {
		Toolkit.getDefaultToolkit().beep();
		boardPanel.setIsPreviousButtonSet(false);
	}
} else {
	Toolkit.getDefaultToolkit().beep();
}

boardPanel.drawAllComponents();

if (board.isGameOver()) {
	int answer = new JOptionPane().showConfirmDialog(getParent(),
			"Player " + board.whoWon()
					+ " won.\nDo you want another round",
			"Do not leave", JOptionPane.YES_NO_OPTION);
			boardPanel.getQuixoBoard().initialize();
			boardPanel.drawAllComponents();

			if (answer == JOptionPane.YES_OPTION) {
				board.initialize();
				boardPanel.drawAllComponents();

				if (board.getWhoPlaysNext() == Face.O) {
					board.togglePlayerSymbol();
				}
			} else if (answer == JOptionPane.NO_OPTION) {
				System.exit(0);
			}
		}
	}
}
