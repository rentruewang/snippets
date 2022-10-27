package exp.features;

public class Generics<T, L extends T> {
    int function() {
        new Generics<A, B>();
        return 0;
    }
}

class A {
};

class B extends A {
}
