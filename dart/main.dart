class C {
  int _val;
  int get val => _val;
  set val(int c) => _val = c;

  C(this._val);
}

Future<void> printasync(String s, int delay) async {
  await Future.delayed(Duration(seconds: delay), () => print(s));
}

function() {
  return 3;
}

class Quote {
  final String author;
  final String text;

  Quote({this.author, this.text});

  @override
  String toString() => '$text --- $author';
}

void longRunning() {
  Future.delayed(Duration(seconds: 1)).then((_) => print('future finished'));
  print('long running end');
}

void parent() {
  longRunning();
  print('parent end');
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

void main() async {
  parent();
  print(function());

  // C c = C(null);
  // print(c.val);
  // c.val = 8;
  // print(c.val);

  // var quote = Quote(author: 'Me', text: 'Hello, world.');

  // print(quote);

  // // https://dart.dev/codelabs/async-await#execution-flow-with-async-and-await
  // // An async function runs synchronously until the first await keyword. This means that within an async function body, all synchronous code before the first await keyword executes immediately.
  // // Which in plain English means,
  // //! `async` functions are synchronous without `await`!
  // printasync('d', 5);
  // await printasync('a', 2);
  // printasync('c', 2);
  // await printasync('b', 1);
}
