import java.util.List;
import java.util.stream.Collectors;
import java.util.Arrays;

record SomeRecord(int x, long y) {}

public class Main {
    public static void main(String[] args) {
        System.out.println("hello");

        var array = Arrays.asList(new Integer[] { 1, 2, 3 });

        // Java does not have the 'inference by return type' that Rust has.
        // Which is the reason collect takes an argument rather than overloading (static
        // dispatch).
        var list = array.stream().map((var x) -> x + 1).collect(Collectors.toList());
        System.out.println(list);
    }
}
