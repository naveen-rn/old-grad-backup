import scala.collection.mutable.ListBuffer

def fibCalcImmutable(position: Int) = position match {
  case 1 => List(1)
  case _ =>  if (position > 1) {
    (2 to position - 1).foldLeft(List(1, 1)) { (fibList, buffer) =>
      fibList ::: List(fibList(buffer - 2) + fibList(buffer - 1))
    }
  }
  else {
    List()
  }
}

def fibCalcRecursive(position: Int) = {
  def fibCalcRecursive(position: Int, fibList: List[Int]): List[Int] = position match{
    case 0 => List()
    case 1 => List(1)
    case 2 => List(1,1)
    case _ if(position < 0 || position <= fibList.length ) => fibList
    case _ =>
        val newList = if (fibList.length < 2) List(1, 1) else fibList
        fibCalcRecursive(position, newList ::: List(newList(newList.length - 1) + newList(newList.length - 2)))
  }
  fibCalcRecursive(position, List())
}

def fibCalcMutable(position: Int) = {
  var fibList = new ListBuffer[Int]
    for (i <- 1 to position) {
      if (i > 2) {
        fibList += fibList(fibList.length - 1) + fibList(fibList.length - 2)
      }
      else {
        fibList += 1
      }
    }
  fibList
}

println(fibCalcImmutable(-1))
println(fibCalcImmutable(0))
println(fibCalcImmutable(1))
println(fibCalcImmutable(2))
println(fibCalcImmutable(4))
println(fibCalcImmutable(6))

println(fibCalcRecursive(-1))
println(fibCalcRecursive(0))
println(fibCalcRecursive(1))
println(fibCalcRecursive(2))
println(fibCalcRecursive(4))
println(fibCalcRecursive(6))

println(fibCalcMutable(-1))
println(fibCalcMutable(0))
println(fibCalcMutable(1))
println(fibCalcMutable(2))
println(fibCalcMutable(4))
println(fibCalcMutable(6))
