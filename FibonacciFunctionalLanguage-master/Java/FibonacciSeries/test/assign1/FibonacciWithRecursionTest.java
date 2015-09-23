package assign1;

import java.util.List;

public class FibonacciWithRecursionTest extends FibonacciTest {
    @Override
    protected List<Integer> createFibonacci(int position) {
        return new Fibonacci().fibCalcRecursive(position);
    }
}
