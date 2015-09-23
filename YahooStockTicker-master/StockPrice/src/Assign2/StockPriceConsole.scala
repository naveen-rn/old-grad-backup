package Assign2

class StockPriceConsole(getPriceFromService: String => Double) {
	protected[Assign2] def this() = {
		this(symbol => 0.0)
	}

	def calculateValue(numberOfStocksOwned: Int, adjClose: Double): Double = {
		numberOfStocksOwned * adjClose
	}

	def calculateNetAssetValue(stockValue: List[Double]): Double = {
		stockValue.sum
	}

	def getPriceValue(symbol: String): Double = {
		try {
		  getPriceFromService(symbol)
		} catch {
		  case ex: RuntimeException => 0.0
		}
	}

	def sharesValueAndNet(stockList: Map[String, Int]) = {
		val worths = stockList.map { stockQuantity =>
			stockQuantity._1 -> calculateValue(stockQuantity._2, getPriceValue(stockQuantity._1))
		}
		val netAsset = calculateNetAssetValue(worths.values.toList)
		(worths, netAsset)
	}
}