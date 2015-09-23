package assign3;

import junit.framework.TestCase;
import java.util.Arrays;
import java.util.HashMap;
import java.util.*;

public class BackgroundCheckTest extends TestCase
{
    private BackgroundCheck _bgCheck;
    private HashMap<String, Object> _expectedResult;

    public HashMap<String, Object> createMap(String SSN, String FirstName, String LastName, String Result, String... Reason)
    {
        HashMap<String, Object> _expectedResult = new HashMap<String, Object> ();
        _expectedResult.put("SSN", SSN);
        _expectedResult.put("FirstName", FirstName);
        _expectedResult.put("LastName", LastName);
        _expectedResult.put("Result", Result);
        _expectedResult.put("Reason", Arrays.asList(Reason));
        return _expectedResult;
    }

    public void testCanary() {
        assertTrue(true);
    }

    public List<String> creditApproved(String ssn) {
        return Arrays.asList("Approved", "CreditBalanceAvailable");
    }

    public List<String> creditRejected(String ssn) {
        return Arrays.asList("Rejected", "CreditBalanceNotAvailable");
    }

    public List<String> criminalApproved(String ssn) {
        return Arrays.asList("Approved", "NoCriminalRecord");
    }

    public List<String> criminalRejected(String ssn) {
        return Arrays.asList("Rejected", "HaveCriminalRecord");
    }

    public void testCheckCreditApproved() {
        _bgCheck = new BackgroundCheck(this::creditApproved);
        _expectedResult = createMap("123-45-6789", "Aaron", "Swartz", "Approved", "CreditBalanceAvailable");
        assertEquals(_expectedResult, _bgCheck.evaluate("123-45-6789", "Aaron", "Swartz"));
    }

    public void testCheckCreditRejected() {
        _bgCheck = new BackgroundCheck(this::creditRejected);
        _expectedResult = createMap("123-45-6789", "Aaron", "Swartz", "Rejected", "CreditBalanceNotAvailable");
        assertEquals(_expectedResult, _bgCheck.evaluate("123-45-6789", "Aaron", "Swartz"));
    }

    public void testCheckCreditAndCriminalRecordBothApproved() {
        _bgCheck = new BackgroundCheck(this::creditApproved, this::criminalApproved);
        _expectedResult = createMap("123-45-6789", "Aaron", "Swartz", "Approved", "CreditBalanceAvailable", "NoCriminalRecord");
        assertEquals(_expectedResult, _bgCheck.evaluate("123-45-6789", "Aaron", "Swartz"));
    }

    public void testCheckCreditAndCriminalRecordBothRejected() {
        _bgCheck = new BackgroundCheck(this::creditRejected, this::criminalRejected);
        _expectedResult = createMap("123-45-6789", "Aaron", "Swartz", "Rejected", "CreditBalanceNotAvailable", "HaveCriminalRecord");
        assertEquals(_expectedResult, _bgCheck.evaluate("123-45-6789", "Aaron", "Swartz"));
    }

    public void testCheckCreditRejectedAndCriminalRecordAccepted() {
        _bgCheck = new BackgroundCheck(this::creditRejected, this::criminalApproved);
        _expectedResult = createMap("123-45-6789", "Aaron", "Swartz", "Rejected", "CreditBalanceNotAvailable", "NoCriminalRecord");
        assertEquals(_expectedResult, _bgCheck.evaluate("123-45-6789", "Aaron", "Swartz"));
    }

    public void testCheckCreditApprovedAndCriminalRecordRejected() {
        _bgCheck = new BackgroundCheck(this::creditApproved, this::criminalRejected);
        _expectedResult = createMap("123-45-6789", "Aaron", "Swartz", "Rejected", "CreditBalanceAvailable", "HaveCriminalRecord");
        assertEquals(_expectedResult, _bgCheck.evaluate("123-45-6789", "Aaron", "Swartz"));
    }

    public void testEmptyCriterion() {
        _bgCheck = new BackgroundCheck();
        _expectedResult = createMap("123-45-6789", "Aaron", "Swartz", "NoCriterionsProvidedToBeChecked");
        assertEquals(_expectedResult, _bgCheck.evaluate("123-45-6789", "Aaron", "Swartz"));
    }

}
