package Assign2

import java.io.IOException

class WebserviceNotCompleted extends Exception

class GetPriceValue {
	def getPriceForSymbol(symbol: String): Double = {
		try {
			parseDownloadStockDetails(getCSV(getURL(symbol)))
		}
		catch {
			case ex: IOException => throw new WebserviceNotCompleted
		}
	}
	
	def getCSV(URL: String): String = {
		io.Source.fromURL(URL).mkString
	}

	def parseDownloadStockDetails(stockList: String): Double = {
		stockList.split("\n")(1).split(",")(3).toDouble
	}

	def getURL(stockID: String): String = {
		"http://ichart.finance.yahoo.com/table.csv?s="+stockID
	}
}
