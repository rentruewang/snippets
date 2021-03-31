package delayed.routing;

import java.nio.file.Files;
import java.nio.file.Paths;

import delayed.routing.parser.*;

public class App {
    public static void main(String[] args) {
        // TODO: Add argument parser
        String fname = args[0];

        Parser parser = new IccadParser(fname);

        parser.parse();
    }
}
