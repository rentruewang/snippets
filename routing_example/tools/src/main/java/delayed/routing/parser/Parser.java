package delayed.routing.parser;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.Iterator;

import lombok.Getter;
import lombok.Setter;

// Parser is actually an interface, but with the benefit of having static
// methods
abstract public class Parser {
    @Getter
    @Setter
    private String[] data;

    public Parser(String path) {
        this(Paths.get(path));
    }

    public Parser(Path path) {
        try {
            String content = Files.readString(path);
            data = content.split("\\s+");
        } catch (IOException ioe) {
            throw new RuntimeException(ioe);
        }
    }

    protected void parseAndThrow(Path path) throws IOException {
        String content = Files.readString(path);

        String[] splitted = content.split("\\s+");
        var iterable = Arrays.asList(splitted);

        parse(iterable);
    }

    public void parse() {
        var list = Arrays.asList(data);

        parse(list);
    }

    abstract protected void parse(Iterable<String> iterable);

    protected void parse(Path path) {
        try {
            parseAndThrow(path);
        } catch (IOException ioe) {
            throw new RuntimeException(ioe);
        }
    }

    protected static int parseInt(Iterator<String> it) {
        return parseInt(it.next());
    }

    protected static int parseInt(String s) {
        try {
            return Integer.parseInt(s);
        } catch (NumberFormatException nfe) {
            throw new RuntimeException(nfe);
        }
    }
}
