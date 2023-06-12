package random.module;

import random.module.utilities.OneParserImpl;
import random.module.utilities.Parser;
import random.module.utilities.Tools;

public class App {
    public static void main(String[] args) {
        Parser parser = new OneParserImpl();
        parser.parse();

        Tools.callsContained();

        var exec = new Executor(0);

        assert exec.getStatus() == 0;

        System.out.println(exec.toString());
    }
}
