// Copyright (c) 2024 RenChu Wang - All Rights Reserved

import 'dart:async';
import 'dart:io';
import 'dart:typed_data';

import 'package:image/image.dart';

Future<void> slow() => Future.delayed(Duration(seconds: 1), () {
      print('hi');
    });

void sslow() async {
  print('stream');
  Stream.fromFuture(slow()).drain();
}

void main(List<String> args) {
  var arr = Uint8List.fromList(List.generate(2000 * 1000 * 3, (index) => 0));

  var img = Image.fromBytes(width: 2000, height: 1000, bytes: arr.buffer);
  // print('${img.width}, ${img.height}');

  for (int i = 0; i < 2000 * 1000; ++i) {
    img.setPixelRgb(i ~/ 1000, i % 1000, 0xff, 0xff, 0xff);
    if (i % 1000 == 0) {
      stdout.write('$i $img\r');
    }
  }
  File('file.png').writeAsBytesSync(encodePng(img));
  print('');
  slow();
  sslow();
  print('finished');
}
