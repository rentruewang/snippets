package route;

import com.google.gson.Gson;

public class Loader {
    private final Gson gson;
    private String data;


    {
        gson = new Gson();
    }

    public Loader () {
        data = new String();
    }

    public Loader(String file) {}
}
