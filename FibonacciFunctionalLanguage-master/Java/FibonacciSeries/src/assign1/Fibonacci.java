package assign1;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Fibonacci {

    public List<Integer> fibCalcMutable(int position) {
        List<Integer> fibList = new ArrayList<>();
        for (int i = 0; i < position; i++) {
            if (i == 0 || i == 1) {
                fibList.add(1);
            } else {
                fibList.add(fibList.get(i - 1) + fibList.get(i - 2));
            }
        }
        return fibList;
    }

    public List<Integer> fibCalcRecursive(List<Integer> fibList,
                                          int position) {
        if (position > 0 && fibList.size() != position) {
            int newElement = (fibList.size() < 2) ? 1 : 
                 fibList.get(fibList.size() - 1) + 
                 fibList.get(fibList.size() - 2);
            List<Integer> tempList = Stream.concat(fibList.stream(),
                Arrays.asList(newElement).stream())
                      .collect(Collectors.toList());
	        return fibCalcRecursive(tempList, position);
        }
        return fibList;
    }

    public List<Integer> fibCalcRecursive(int position) {
        if (position > 0) {
            List<Integer> fibList = new ArrayList<>();
            fibList = fibCalcRecursive(fibList, position);
            return fibList;
        }
        return Collections.emptyList();
    }

    public List<Integer> fibCalcImmutable(int position) {
        if (position > 0) {
            List<Integer> temp    = Arrays.asList(1);
            List<Integer> fibList = 
                Stream.iterate(1, x -> x + 1)
                      .limit(position - 1)
                      .reduce(temp,
                        (base, index) -> fibCalcHelper(base),
                        (a, b) -> null);
            return fibList;
        }
        return Collections.emptyList();
    }

    public List<Integer> fibCalcHelper(List<Integer> base) {
        List<Integer> t1 = new ArrayList<>();
        t1.addAll(base);
        if ((t1.size() < 2) ? t1.add(1) : 
            t1.add(t1.get(t1.size() - 1) + t1.get(t1.size() - 2)));
        return t1;
    }

}
