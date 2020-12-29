import 'package:flutter/material.dart';
import 'package:personal_page/pages/homepage.dart';

// Main function that creates a webpage
void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    var theme = ThemeData(
      primarySwatch: Colors.black,
    );
    var home = HomePage();
    return MaterialApp(
      title: "RenChu Wang",
      theme: theme,
      home: home,
    );
  }
}
