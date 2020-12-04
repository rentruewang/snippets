class C {
  int _val;
  int get val => _val;
  set val(int c) => _val = c;

  C(this._val);
}

class Player {
  String name;
  final String color;

  Player(this.name, this.color);

  Player.con1(Player another)
      : color = another.color,
        name = another.name {}

  Player.con2(Player another)
      : color = another.color,
        name = another.name;

  Player.con3(Player another) : color = another.color {
    this.name = another.name;
  }

  Player.con4(Player another) : this(another.name, another.color);
}

void main() {
  C c = C(null);
  print(c.val);
  c.val = 8;
  print(c.val);
}
