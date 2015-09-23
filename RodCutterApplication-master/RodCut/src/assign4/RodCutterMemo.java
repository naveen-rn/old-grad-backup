package assign4;

import java.util.AbstractMap.SimpleEntry;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class RodCutterMemo extends RodCutter{

    private Map<Integer, SimpleEntry<Integer, List<Integer>>> rodPriceAndCutList = new HashMap<>();

    @Override
    public int cutRod(int length, List<Integer> rodRates, List<Integer> cutRodLength) {
        List<Integer> rodPiecesTemp = new ArrayList<Integer>();
        if(rodPriceAndCutList.get(length) == null) {
            rodPriceAndCutList.put(length, new SimpleEntry<Integer, List<Integer>>(super.cutRod(length, rodRates, rodPiecesTemp), rodPiecesTemp));
        }
        cutRodLength.addAll(rodPriceAndCutList.get(length).getValue());
        return rodPriceAndCutList.get(length).getKey();
    }
}
