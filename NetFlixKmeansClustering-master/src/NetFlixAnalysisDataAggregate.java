package examples;

/*
 * NetFlixAnalysisDataAggregate is a class which is used for data
 * preparation from the given inputfile to the output file for the
 * canopy clustering. This belongs to step 1 in the process.
 */

import java.io.*;
import java.util.*;
import java.net.*;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.conf.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapred.*;
import org.apache.hadoop.util.*;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.fs.LocalFileSystem;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.MapWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.WritableComparable;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.input.FileSplit;
import org.apache.hadoop.mapreduce.InputSplit;
import org.apache.hadoop.mapreduce.Mapper;

public class NetFlixAnalysisDataAggregate
{
    public static class NetFlixAnalysisDataAggregateMapper
            extends Mapper < Object, Text, Text, MapWritable >
        {
            private Text word = new Text ();
            private MapWritable mw = new MapWritable();

            String fileName = new String();
            protected void setup(Context context) throws java.io.IOException, java.lang.InterruptedException
            {
                Path fileNameString = ((FileSplit) context.getInputSplit()).getPath();
                fileName = fileNameString.getName();
            }

            @Override
            public void map (Object key, Text value, Context context)
                throws IOException, InterruptedException
            {
                Scanner scanner = new Scanner (value.toString());
                scanner.useDelimiter(",");
                String[] words = new String[3];

                int i = 0;
                while (scanner.hasNext ())
                {
                    words[i++] = scanner.next ();
                }

                if (i > 2) {
                    mw.put(new IntWritable(1), new IntWritable(Integer.parseInt(words[0])));
                    mw.put(new IntWritable(2), new IntWritable(Integer.parseInt(words[1])));

                    word.set(fileName);
                    context.write(word, mw);
                }
            }
        }

    public static class NetFlixAnalysisDataAggregateReducer
            extends Reducer < Text, MapWritable, Text, Text >
        {
            private Text word = new Text ();
            public void reduce (Text key, Iterable < MapWritable > values,
                    Context context) throws IOException,
                    InterruptedException
                {
                    String buffer = new String();
                    for (MapWritable value: values) {
                        int i = ((IntWritable) value.get(new IntWritable(1))).get();
                        int j = ((IntWritable) value.get(new IntWritable(2))).get();
                       
                        String buffer1 = (Integer.toString(i)).concat(":");
                        String buffer2 = buffer1.concat(Integer.toString(j));
                        String buffer3 = buffer2.concat(",");
                        buffer = buffer.concat(buffer3);
                        //word.set(buffer2);
                        //context.write (key, word);
                    }
                    buffer = buffer.substring(0, buffer.length()-1);
                    word.set(buffer);
                    context.write (key, word);
                }
        }

    public static void main (String[]args) throws Exception
    {
        Configuration conf = new Configuration ();
        Job job = new Job (conf, "naveen_net_flix_data_aggregation");
        job.setJarByClass (NetFlixAnalysisDataAggregate.class);

        job.setMapperClass (NetFlixAnalysisDataAggregateMapper.class);
        job.setReducerClass (NetFlixAnalysisDataAggregateReducer.class);

        job.setMapOutputKeyClass(Text.class);
        job.setMapOutputValueClass(MapWritable.class);
        job.setOutputKeyClass (Text.class);
        job.setOutputValueClass (Text.class);

        FileInputFormat.addInputPath (job, new Path (args[0]));
        FileOutputFormat.setOutputPath (job, new Path (args[1]));
        
        job.setNumReduceTasks(1);
        
        System.exit (job.waitForCompletion (true) ? 0 : 1);
    }
}
