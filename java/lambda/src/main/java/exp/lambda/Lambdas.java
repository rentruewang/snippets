package exp.lambda;

public class Lambdas {
    public static void main(String[] args) {
        var lambdas = new Lambdas();

        accept1((Integer i) -> String.valueOf(i), 18);
        accept2((Integer i) -> String.valueOf(i), 29);
    }

    public static <T, E> void accept1(FunctionalInterface1<T, E> fi1, E arg) {
        System.out.println(fi1.apply(arg) + "_1");
    }

    public static <T, E> void accept2(FunctionalInterface2<T, E> fi2, E arg) {
        System.out.println(fi2.do_something(arg) + "_2");
    }

}

interface FunctionalInterface1<T, E> {
    T apply(E arg);
}

interface FunctionalInterface2<T, E> {
    T do_something(E arg);
}
