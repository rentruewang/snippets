// Copyright (c) 2024 RenChu Wang - All Rights Reserved

void main() {
  var b = 0;
  var c = 2;

  // The || operator in dart only works for booleans.
  // var a = b || c;

  // This is the if null operator so it will return 0.
  var a = b ?? c;
  print(a);

  var y = 1;
  var z = y = 2;
  print('$y, $z');
}
