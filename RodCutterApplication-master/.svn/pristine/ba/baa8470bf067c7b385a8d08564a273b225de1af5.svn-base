package assign4;

import junit.framework.TestCase;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class RodCutterTest extends TestCase{

    private RodCutter _rodCutter;
    private List<Integer> _rodRates = Arrays.asList(1, 1, 2, 3, 4, 5, 5, 9, 9, 10);
    private List<Integer> _cutPiecesLength;

    protected void setUp() {
        _rodCutter = createRodCutter();
        _cutPiecesLength = new ArrayList<Integer>();
    }

    protected RodCutter createRodCutter() {
        return new RodCutter();
    }

    public void testCanary() {
        assertTrue(true);
    }

    public void testMaxRodPriceForLength0() {
        assertEquals(0, _rodCutter.cutRod(0, _rodRates, _cutPiecesLength));
        assertEquals(Arrays.asList(), _cutPiecesLength);
    }

    public void testMaxRodPriceForLength1() {
        assertEquals(1, _rodCutter.cutRod(1, _rodRates, _cutPiecesLength));
        assertEquals(Arrays.asList(1), _cutPiecesLength);
    }

    public void testMaxRodPriceForLength2() {
        assertEquals(2, _rodCutter.cutRod(2, _rodRates, _cutPiecesLength));
        assertEquals(Arrays.asList(1, 1), _cutPiecesLength);
    }

    public void testMaxRodPriceForLength3() {
        assertEquals(3, _rodCutter.cutRod(3, _rodRates, _cutPiecesLength));
        assertEquals(Arrays.asList(1, 1, 1), _cutPiecesLength);
    }

    public void testMaxRodPriceForLength5() {
        assertEquals(5, _rodCutter.cutRod(5, _rodRates, _cutPiecesLength));
        assertEquals(Arrays.asList(1, 1, 1, 1, 1), _cutPiecesLength);
    }

    public void testMaxRodPriceForLength10() {
        assertEquals(11, _rodCutter.cutRod(10, _rodRates, _cutPiecesLength));
        assertEquals(Arrays.asList(1, 1, 8), _cutPiecesLength);
    }

    public void testMaxRodPriceForLength20() {
        assertEquals(22, _rodCutter.cutRod(20, _rodRates, _cutPiecesLength));
        assertEquals(Arrays.asList(1, 1, 1, 1, 8, 8), _cutPiecesLength);
    }
}