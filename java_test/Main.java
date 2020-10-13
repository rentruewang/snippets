import java.util.List;
import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        System.out.println("hello");

        var array = Arrays.asList(new Integer[] { 1, 2, 3 });

        array.stream().map((var x) -> x + 1).forEach(System.out::print);
    }
}
