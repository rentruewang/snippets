package route;

/**
 * Map is akin to `map` in haskell that does a tranformation on its inputs. It
 * is used in a higher order function context as a parameter to pass around.
 */
public interface Map<R, A> {
    /**
     * The only method to implement since `Map` is a generic interface to represent
     * a lambda type.
     * 
     * @param arg is a function argument to transform
     * @return the result of the transformation
     */
    R apply(A arg);
}
