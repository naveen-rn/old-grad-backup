package assign4;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Stream;

public class RodCutter {
    public int cutRod(int length, List<Integer> rodRates, List<Integer> cutRodLength) {
        int maxRodPrice = 0;
        if (length > 0) {
            if(length <= rodRates.size()) {
                maxRodPrice = rodRates.get(length - 1);
                cutRodLength.add(length);
            }

            List<Integer> initialForLength = Arrays.asList(maxRodPrice, length);
            
            List<Integer> maxRevenues = 
              Stream.iterate(1, next -> next + 1)
                    .limit(length - 1)
                    .map(number -> {List<Integer> index = Arrays.asList(number); return index;})
                    .reduce(initialForLength, (base, indexWrapped) -> {

                        List<Integer> cutPieceLengthPart1 = new ArrayList<Integer>();
                        List<Integer> cutPieceLengthPart2 = new ArrayList<Integer>();

                        int index = indexWrapped.get(0);

                        int tempMaxPrice = 
                          cutRod(index, rodRates, cutPieceLengthPart1) + 
                          cutRod(length - index, rodRates, cutPieceLengthPart2);

                        if (base.get(0) > tempMaxPrice) 
                          return base;
                          
                        List<Integer> result = new ArrayList<>();
                        result.add(tempMaxPrice);
                        result.addAll(cutPieceLengthPart2);
                        result.addAll(cutPieceLengthPart1);
                        return result;
                    });
              
              maxRodPrice = maxRevenues.get(0);
              cutRodLength.clear();
              cutRodLength.addAll(maxRevenues.subList(1, maxRevenues.size()));
        }
        return maxRodPrice;
    }
}