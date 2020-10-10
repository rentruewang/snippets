import scala.math
import scala.collection.mutable.ArrayBuffer 
import logs.logging.Logger

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
        return t
    } else {
        return 0
    }
  }
}

class Construct(a: Int) {
  println("Hello", a)
}

case class Message(sender: String, recipient: String, body: String)

class Circle(var radius: Double) {
  def calculateArea(radius: Double): Double = 
        math.Pi * math.pow(radius, 2.0)
  def area(): Double = calculateArea(radius)
}

case class User(name: String, age: Int)

abstract class Animal {
    def name: String
}

abstract class Pet extends Animal {}

class Cat extends Pet {
    override def name: String = "Cat"
}

class Dog extends Pet {
    override def name: String = "Dog"
}

class Lion extends Animal {
    override def name: String = "Lion"
}

class PetContainer[P <: Pet](p: P) {
    def pet: P = p
}

object Main {
    def main(args: Array[String]) {
        val iterator = new IntIterator(10)
        val f = iterator.next()  // returns 0
        val s = iterator.next()  // returns 1
        println(f, s)
        val planets =
        List(("Mercury", 57.9), ("Venus", 108.2), ("Earth", 149.6),
            ("Mars", 227.9), ("Jupiter", 778.3))
        planets.foreach{
        case ("Earth", distance) =>
            println(s"Our planet is $distance million kilometers from the sun")
        case _ =>
        }

        new Construct(3)

        val msg = Message(sender="a", recipient="b", body="c")
        println(msg)

        def matchTest(x: Int) = x match {
            case 1 => println("one")
            case 2 => println("two")
            case _ => println("three")
        }
        matchTest(3)  // prints other
        matchTest(1)  // prints one

        Logger.info("1234567890") // prints

        val c = new Circle(3)
        println(c.radius, c.area)
        c.radius = 1
        println(c.radius, c.area)

        val userBase = List(
          User("Travis", 28),
          User("Kelly", 33),
          User("Jennifer", 44),
          User("Dennis", 23))

        val twentySomethings =
            for (user <- userBase if user.age >=20 && user.age < 30)
                yield println(user.name)  // i.e. add this to a list

        twentySomethings.foreach(name => println(name))  // prints Travis Dennis

        implicit def z(a: String):Int = 2

        val x: String = "1"

        val y: Int = x // compiler will use z here like val y:Int=z(x)

        println(y) // result 2  & no error!

        @deprecated("deprecation message", "release # which deprecates method")
        def hello = "hola"
    }
}
