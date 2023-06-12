package exp.collections;

import java.util.*;
import java.util.stream.Collectors;

public class Lists {
    public static void main(String[] args) {
        var list = List.of(1, 2, 3);
        list.forEach(System.out::print);
        System.out.println();
        list.stream().forEach(System.out::print);
        System.out.println();
        System.out.println();
        // This is how you write static generic functions in java.
        List<String> aList = List.<String>of("1", "324", "99");
        var result = aList.stream().map((String s) -> s + "~~~").collect(Collectors.toList());
        System.out.println(result);

        // This will not work.
        // list.forEach(System.out.println);
    }
}
