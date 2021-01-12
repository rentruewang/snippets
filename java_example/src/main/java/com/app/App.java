package com.app;

public class App {
    public static void main(String[] args) {
        var o = new Outer();

        o.outerPublic();
        // o.outerPrivate();

        o.new Inner().innerPublic();
    }
}

class Outer {

    public void outerPublic() {
        System.out.println("public");
    }

    private void outerPrivate() {
        System.out.println("private");
    }

    class Inner {

        public void innerPublic() {
            outerPrivate();
        }
    }
}
