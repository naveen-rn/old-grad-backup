package assign3;

import java.util.*;
import java.util.List;
import java.util.function.*;
import java.util.stream.Stream;

class BackgroundCheck
{
    private Function<String, List<String>>[] _criterion;

    public BackgroundCheck(Function<String, List<String>>... criterion) {
        _criterion = criterion;
    }

    public final HashMap<String, Object> evaluate(String SSN, String FirstName, String LastName) {
        HashMap<String, Object> _checkedResult = new HashMap<String, Object> ();
        List<String> Reason = new ArrayList<String> ();
        _checkedResult.put("SSN", SSN);
        _checkedResult.put("FirstName", FirstName);
        _checkedResult.put("LastName", LastName);

        Stream.of(_criterion)
            .map(loopMap -> Reason.add(loopMap.apply(SSN).get(1)))
            .distinct()
            .count();

        if(_criterion.length == 0) {
            _checkedResult.put("Result", "NoCriterionsProvidedToBeChecked");
        } else {
          _checkedResult.put("Result", 
            Stream.of(_criterion)
                  .map(criterion -> criterion.apply(SSN).get(0))
                  .filter(result -> result  == "Rejected")
                  .findFirst()
                  .orElse("Approved"));          
        }
                        
        _checkedResult.put("Reason", Reason);
        return _checkedResult;
    }
}
