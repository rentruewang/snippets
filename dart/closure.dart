void main(List<String> args) {
  var data = '';

  var closure = (String s) => data = s;

  closure('s');

  print(data);

  print([1, 2, 3].expand((e) => [e, e + 1]));
}
