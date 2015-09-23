package Console

import Assign2.StockPriceConsole
import Assign2.GetPriceValue

object StockPriceIOConsole {
	def main(args: Array[String]): Unit = {
		val symbolList = Map("GOOG"->23, "AAPL"->124, "YHOO"->234)
		displayResult(symbolList)
	}

	def displayResult(symbolList: Map[String, Int]): Unit = {
		val theService = new GetPriceValue()
		val getPriceFunction = (symbol: String) => theService.getPriceForSymbol(symbol);
		val stockResults = new StockPriceConsole(getPriceFunction).sharesValueAndNet(symbolList)
		print("------------------------------------")
		print("\nSTOCKID   NUMBEROFSTOCKS  STOCKPRICE")
		print("\n------------------------------------")
		stockResults._1.foreach{
		  stockValues => print("\n"+stockValues._1+"        "+symbolList(stockValues._1)+"              "+stockValues._2)
		}
		print("\n------------------------------------")
		print("\nNET STOCK VALUE:  "+stockResults._2)
		print("\n------------------------------------")
	}
}
