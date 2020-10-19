package route;

/**
 * Location represents a location on a 2D-grid. Usually in EDA with a grid based
 * architecture a location can be represented by two integers. This class wraps
 * Tuple as a backend.
 */
public final class Location<T> {
    // The backend of a `Location` object.
    private Tuple<T> tuple;

    /**
     * Normal constructor. Parameters are constrained to be the same type.
     * 
     * @param a is the first object stored
     * @param b is the second object stored
     * 
     */
    public Location(T a, T b) {
        tuple = new Tuple<>(a, b);
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
    public <A> Location(A a, A b, Map<T, A> map) {
        tuple = new Tuple<>(map.apply(a), map.apply(b));
    }

    /**
     * @return the first object
     */
    public T a() {
        return tuple.a();
    }

    /**
     * @return the second object
     */
    public T b() {
        return tuple.b();
    }
}
