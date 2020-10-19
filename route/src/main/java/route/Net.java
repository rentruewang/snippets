package route;

import java.util.ArrayList;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

/**
 * A Net is A simple wrapper for locations. How to define a net in 2D routing
 * problem. Simple.
 */
public final class Net {
    public static ArrayList<Net> loadFromFile(String filename) throws IOException {

        var path = Paths.get(filename);
        var contents = Files.readAllLines(path);

        // TODO somehow parse the contents of the file
        // TODO temporary hack to pass compiler checks
        return new ArrayList<>();
    }
}
