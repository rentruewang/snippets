package route;

/**
 * Tuple represents a pair of the same type. Usually in EDA with a grid based
 * architecture a Tuple can be represented by two integers. This class wraps
 * Tuple as a backend.
 */
public record Tuple<T> (T a, T b) {
    /**
     * Normal constructor. Parameters are constrained to be the same type.
     * 
     * @param a is the first object stored
     * @param b is the second object stored
     * 
     */
    public Tuple {
    }

    /**
     * This is a special version of the constructor. A lambda is allowed to be
     * passed to transform the arguments.
     * 
     * @param <A> is the type of the objects passed in
     * @param a   is the first argument passed in
     * @param b   is the second argument passed in
     * @param map maps `a` and `b`. The results are then stored by the object.
     */
    public <A> Tuple(A a, A b, Map<T, A> map) {
        this(map.apply(a), map.apply(b));
    }
}
