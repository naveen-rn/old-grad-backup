package assign1;

import junit.framework.TestCase;
import java.util.Arrays;
import java.util.List;

public class FibonacciTest extends TestCase {
    protected List<Integer> createFibonacci(int position) {
        return new Fibonacci().fibCalcMutable(position);
    }

    public void testCanary() {
        assertTrue(true);
    }

    public void testFibonacciSeriesForPostion0() {
        assertEquals(Arrays.asList(), createFibonacci(0));
    }

    public void testFibonacciSeriesForPostion1() {
        assertEquals(Arrays.asList(1), createFibonacci(1));
    }

    public void testFibonacciSeriesForPostion2() {
        assertEquals(Arrays.asList(1, 1), createFibonacci(2));
    }

    public void testFibonacciSeriesForPostion4() {
        assertEquals(Arrays.asList(1, 1, 2, 3), createFibonacci(4));
    }

    public void testFibonacciSeriesForPostion6() {
        assertEquals(Arrays.asList(1, 1, 2, 3, 5, 8), createFibonacci(6));
    }

    public void testFibonacciSeriesForNegativePostion() {
        assertEquals(Arrays.asList(), createFibonacci(-1));
    }
}