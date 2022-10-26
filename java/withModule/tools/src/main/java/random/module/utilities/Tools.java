package random.module.utilities;

public class Tools {
    private Tools() {}

    public static void containedFunc() {}

    public static void callsContained() {
        containedFunc();
    }
}
