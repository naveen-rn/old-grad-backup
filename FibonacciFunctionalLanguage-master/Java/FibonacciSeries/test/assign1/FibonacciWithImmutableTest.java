package assign1;

import java.util.List;

public class FibonacciWithImmutableTest extends FibonacciTest {
    @Override
    protected List<Integer> createFibonacci(int position) {
        return new Fibonacci().fibCalcImmutable(position);
    }
}
