import 'dart:async';
import 'dart:io';

import 'package:image/image.dart' as image;

Future<void> slow() => Future.delayed(Duration(seconds: 1), () {
      print('hi');
    });

void sslow() async {
  print('stream');
  Stream.fromFuture(slow()).drain();
}

void main(List<String> args) {
  var arr = List.generate(2000 * 1000 * 3, (index) => 0);

  var img = image.Image.fromBytes(2000, 1000, arr, format: image.Format.rgb);
  // print('${img.width}, ${img.height}');

  for (int i = 0; i < 2000 * 1000; ++i) {
    img.setPixelRgba(i ~/ 1000, i % 1000, 0xff, 0xff, 0xff);
    if (i % 1000 == 0) {
      stdout.write('$i $img\r');
    }
  }
  File('file.png').writeAsBytesSync(image.encodePng(img));
  print('');
  slow();
  sslow();
  print('finished');
}
