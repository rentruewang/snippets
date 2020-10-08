trait Iterator[A] {
  def hasNext: Boolean
  def next(): A
}

class IntIterator(to: Int) extends Iterator[Int] {
  private var current = 0
  override def hasNext: Boolean = current < to
  override def next(): Int = {
    if (hasNext) {
      val t = current
      current += 1
      t
    } else 0
  }
}



object Main {
    def main(args: Array[String]) {
        val iterator = new IntIterator(10)
        val f = iterator.next()  // returns 0
        val s = iterator.next()  // returns 1
        println(f, s)

    }
}
