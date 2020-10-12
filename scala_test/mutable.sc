class Holder[+T] (initialValue: Option[T]) {
    // without [this] it will not compile
    private[this] var value = initialValue

    def getValue = value
    def makeEmpty { value = None }
}

trait Some {
    self => 

    def method() = println("called")

    def call() = self.method()
}
