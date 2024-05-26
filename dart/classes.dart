// Copyright (c) 2024 RenChu Wang - All Rights Reserved

/// Documentation for SomeClass
class SomeClass {
  int _firstField;
  int _secondField;

  /// Named parameters can't start with an underscore
  // SomeClass({required this._firstField, required this._secondField}) {}

  /// The parameter '_firstField' can't have a value of 'null' because of its type, but the implicit default value is 'null'.
  // SomeClass({this._firstField, this._secondField}) {}

  SomeClass(this._firstField, this._secondField) {}

  SomeClass.someDefaultValues()
      : _firstField = 1,
        _secondField = 2 {}

  int get first => _firstField;
  set first(int value) => _firstField = value;

  int get second => _secondField;

  @override
  String toString() {
    return '$SomeClass(${this.first}, ${this.second})';
  }
}

void main() {
  var sc = SomeClass(1, 0);

  // Failed assertion: line 33 pos 10: '!(sc is SomeClass)': is not true.
  // assert(!(sc is SomeClass));

  // Failed assertion: line 33 pos 10: '!(sc is SomeClass)': This will fail
  // assert(!(sc is SomeClass), 'This will fail');

  print(sc);
}
