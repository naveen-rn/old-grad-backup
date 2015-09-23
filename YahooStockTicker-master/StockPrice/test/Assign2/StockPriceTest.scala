package Assign2;

import java.io._

import org.scalatest.Suite
import org.scalatest.junit.JUnitRunner
import org.junit.runner.RunWith
import org.scalautils._
import TripleEquals._
import Tolerance._

@RunWith(classOf[JUnitRunner])
class StockPriceConsoleTest extends Suite {
	val stockPriceConsole = new StockPriceConsole
	val TOLERANCE = 0.001

	def testCanary {
		assert(true)
	}

	def testComputeTotalStockValue() {
		assert(stockPriceConsole.calculateValue(12, 23.12) === 277.44 +- TOLERANCE)
	}

	def testComputeTotalStockValueForPriceZero() {
		assert(stockPriceConsole.calculateValue(12, 0.00) == 0)
	}

	def testComputeTotalStockValueForZeroStocks() {
		assert(stockPriceConsole.calculateValue(0, 23.23) == 0)
	}

	def testComputeNetStockValue() {
		val totalStockValues = List(23.23, 149.24, 250.00)
		assert(stockPriceConsole.calculateNetAssetValue(totalStockValues) === 422.47 +- TOLERANCE)
	}

	def testComputeNetStockValueForZeroStockValues() {
		val totalStockValues = List()
		assert(stockPriceConsole.calculateNetAssetValue(totalStockValues) === 0)
	}

	def testGetPriceForSymbolGOOG() {
		val return500ForPrice = (symbol: String) => 500.05
		val stockPriceConsole = new StockPriceConsole(return500ForPrice)
		assert(stockPriceConsole.getPriceValue("GOOG") === 500.05 +- TOLERANCE)
	}

	val returnNetworkUnavailableFalse = (symbol: String) => 0.0;
	def testNetworkErrorNegative() {
		val stockPriceConsole = new StockPriceConsole(returnNetworkUnavailableFalse)
		stockPriceConsole.getPriceValue("GOOG")
		assert(true)
	}

	val returnNonExistingStockTicketTrue = (symbol: String) => {
		throw new WebserviceNotCompleted
		0
	}: Double;
	def testNonExistingStockTicket() {
		val stockPriceConsole = new StockPriceConsole(returnNonExistingStockTicketTrue)
		intercept[WebserviceNotCompleted] {
			stockPriceConsole.getPriceValue("CANNOT_EXIST_A_STOCK_WITH_THAT_NAME")
		}
	}

	val returnNonExistingStockTicketFalse = (symbol: String) => 12.0;
	def testExistingStockTicket() {
		val stockPriceConsole = new StockPriceConsole(returnNonExistingStockTicketFalse)
		val returnValue = stockPriceConsole.getPriceValue("GOOG")
		assert(true)
	}

	def testGetWorthAndNet() {
		val return500ForPrice = (symbol: String) => 500.05
		val stockPriceConsole = new StockPriceConsole(return500ForPrice)
		val sampleStocks = Map("GOOG" -> 23, "APPL" -> 56, "YAHO" -> 43)
		val sampleStocksReport = (Map("APPL" -> 28002.8, "GOOG" -> 11501.15, "YAHO" -> 21502.15), 61006.1)
		assert((sampleStocksReport) == stockPriceConsole.sharesValueAndNet(sampleStocks))
	}

	def testGetWorthAndNetForZeroStock() {
		val return500ForPrice = (symbol: String) => 500.05
		val stockPriceConsole = new StockPriceConsole(return500ForPrice)
		val sampleStocks = Map("GOOG" -> 0, "APPL" -> 0, "YAHO" -> 0)
		val sampleStocksReport = (Map("APPL" -> 0, "GOOG" -> 0, "YAHO" -> 0), 0)
		assert((sampleStocksReport) == stockPriceConsole.sharesValueAndNet(sampleStocks))
	}

	def testGetWorthAndNetForInvalidStock() {
		val return500ForPrice = (symbol: String) => 0.0
		val stockPriceConsole = new StockPriceConsole(return500ForPrice)
		val sampleStocks = Map("INVALID" -> 123)
		val sampleStocksReport = (Map("INVALID" -> 0.0), 0.0)
		assert((sampleStocksReport) == stockPriceConsole.sharesValueAndNet(sampleStocks))
	}

	def testGetWorthAndNetForNullStock() {
		val return500ForPrice = (symbol: String) => 500.05
		val stockPriceConsole = new StockPriceConsole(return500ForPrice)
		val sampleStocks: Map[String, Int] = Map()
		val sampleStocksReport = (Map(), 0)
		assert((sampleStocksReport) == stockPriceConsole.sharesValueAndNet(sampleStocks))
	}
}