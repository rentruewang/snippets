trait Node[+B] {
  def prepend[E >: B](elem: E): Node[E]
}

case class ListNode[+B](h: B, t: Node[B]) extends Node[B] {
  def prepend[E >: B](elem: E): ListNode[E] = ListNode(elem, this)
  def head: B = h
  def tail: Node[B] = t
}

case class Nil[+B]() extends Node[B] {
  def prepend[E >: B](elem: E): ListNode[E] = ListNode(elem, this)
}
