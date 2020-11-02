package nativ;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map.Entry;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

final class Common {
    static final String date = "/Mar/2004:";

    static void handleException(Exception e) {
        System.out.println("Mapper: " + e.toString());
        System.exit(1);
    }
}

class MyMapper extends Mapper<LongWritable, Text, IntWritable, Text> {

    @Override
    public void map(LongWritable _lc, Text line, Context context) {
        var lineStr = line.toString().trim();
        var index = lineStr.indexOf(Common.date) + Common.date.length();

        try {
            var hour = Integer.parseInt(lineStr.substring(index, index + 2));
            var writable = new IntWritable(hour);
            context.write(writable, line);
        } catch (Exception e) {
            Common.handleException(e);
        }
    }
}

class MyReducer extends Reducer<IntWritable, Text, Text, IntWritable> {
    private static String reduced(String input) {
        var index = input.indexOf(Common.date);
        return input.substring(index - 2, index + Common.date.length() + 2) + ":00:00";
    }

    private static void ctxWrite(Entry<String, HashSet<String>> et, Context context) {
        try {
            var str = new Text(et.getKey());
            var cnt = new IntWritable(et.getValue().size());
            context.write(str, cnt);
        } catch (Exception ex) {
            Common.handleException(ex);
        }
    }

    @Override
    public void reduce(IntWritable _k, Iterable<Text> values, Context context) {
        var map = new HashMap<String, HashSet<String>>();
        for (var log : values) {
            var logStr = log.toString().trim();
            var set = map.computeIfAbsent(MyReducer.reduced(logStr), s -> new HashSet<String>());
            set.add(logStr);
        }
        for (var entry : map.entrySet()) {
            MyReducer.ctxWrite(entry, context);
        }

    }
}

public class App {

    // main throws Exception because I'm a lazy person
    public static void main(String[] args) {
        var conf = new Configuration();
        try {
            var job = Job.getInstance(conf, "word count");
            job.setJarByClass(Common.class);
            job.setMapperClass(MyMapper.class);
            job.setCombinerClass(Reducer.class);
            job.setReducerClass(MyReducer.class);
            job.setMapOutputKeyClass(IntWritable.class);
            job.setMapOutputValueClass(Text.class);
            job.setOutputKeyClass(Text.class);
            job.setOutputValueClass(IntWritable.class);
            FileInputFormat.addInputPath(job, new Path(args[0]));
            FileOutputFormat.setOutputPath(job, new Path(args[1]));
            System.exit(job.waitForCompletion(true) ? 0 : 1);
        } catch (Exception e) {
            Common.handleException(e);
        }
    }
}
