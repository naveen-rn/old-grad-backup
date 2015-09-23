package Assign2;

import java.io._
import org.scalatest.Suite
import org.scalatest.junit.JUnitRunner
import org.junit.runner.RunWith
import org.scalautils._
import TripleEquals._
import Tolerance._

@RunWith(classOf[JUnitRunner])
class GetPriceValueTest extends Suite {
	val getPriceVal = new GetPriceValue
	val TOLERANCE = 0.001

	def testCanary {
		assert(true)
	}

	def testToCheckURL() {
		assert(getPriceVal.getURL("GOOG") == "http://ichart.finance.yahoo.com/table.csv?s=GOOG")
	}

	def testToCheckURLForNoStockSymbol() {
		assert(getPriceVal.getURL("") == "http://ichart.finance.yahoo.com/table.csv?s=")
	}

	def testToCheckParseDownloadedString() {
		val dummyWebDataSet: String = "String, StringID, \nS1, 12.32, 123.23, 500.05"
		assert(getPriceVal.parseDownloadStockDetails(dummyWebDataSet) === 500.05 +- TOLERANCE)
	}

	def testToCheckStockPriceReceived() {
		assert(getPriceVal.getPriceForSymbol("GOOG") >= 0.00)
	}

	def testToCheckStockPriceForInvalidSymbolTrue() {
		intercept[WebserviceNotCompleted] {
			getPriceVal.getPriceForSymbol("CANNOT_EXIST_A_STOCK_WITH_THAT_NAME")
		}
	}

	def testToCheckStockPriceForInvalidSymbolFalse() {
		getPriceVal.getPriceForSymbol("GOOG")
		assert(true)
	}
}