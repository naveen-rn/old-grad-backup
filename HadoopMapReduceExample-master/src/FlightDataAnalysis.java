package examples;

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
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.WritableComparable;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class FlightDataAnalysis
{
  public static class FlightDataAnalysisMapper
    extends Mapper < Object, Text, Text, IntWritable >
  {
    private final static IntWritable one = new IntWritable (1);
    private Text word = new Text ();

    public void map (Object key, Text value, Context context)
      throws IOException, InterruptedException
    {
      Scanner scanner = new Scanner (value.toString ());
        scanner.useDelimiter (",");
        String[] words = new String[30];
      int i = 0;
      while (scanner.hasNext ())
	{
	  words[i++] = scanner.next ();
	}
      if (!words[15].equals ("NA"))	//checking for data miss
	if (!words[15].equals ("DepDelay"))	//checking to avoid header
	  {
	    if (Integer.parseInt (words[15]) > 0)
	      {
		String strBuffer1 = words[16].concat ("-");
		String strBuffer = strBuffer1.concat (callMonth(words[1]));
		  word.set (strBuffer);
		  one.set (1);	//delay
		  context.write (word, one);
	      }
	    else
	      {
		String strBuffer1 = words[16].concat ("-");
		String strBuffer = strBuffer1.concat (callMonth(words[1]));
		  word.set (strBuffer);
		  one.set (0);	//no delay 
		  context.write (word, one);
	      }
	  }
	else
	  {
	    String strBuffer1 = words[16].concat ("-");
	    String strBuffer = strBuffer1.concat (callMonth(words[1]));
	    word.set (strBuffer);
	    one.set (0);	//no delay
	    context.write (word, one);
	  }
    }

    private String callMonth (String monthID)
    {
      int imonthID = Integer.parseInt( monthID );
      switch (imonthID)
	{
	case 1:
	  {
	    return "Jan";
	  }
	case 2:
	  {
	    return "Feb";
	  }
	case 3:
	  {
	    return "Mar";
	  }
	case 4:
	  {
	    return "Apr";
	  }
	case 5:
	  {
	    return "May";
	  }
	case 6:
	  {
	    return "Jun";
	  }
	case 7:
	  {
	    return "Jul";
	  }
	case 8:
	  {
	    return "Aug";
	  }
	case 9:
	  {
	    return "Sep";
	  }
	case 10:
	  {
	    return "Oct";
	  }
	case 11:
	  {
	    return "Nov";
	  }
	case 12:
	  {
	    return "Dec";
	  }
	default:
	  return "NA";
	}
    }
  }

  public static class FlightDataAnalysisReducer
    extends Reducer < Text, IntWritable, Text, IntWritable >
  {
    public void reduce (Text key, Iterable < IntWritable > values,
			Context context) throws IOException,
      InterruptedException
    {
      RawComparator < IntWritable > comparator =
	WritableComparator.get (IntWritable.class);
      int total = 0;
      int totalDelay = 0;
      int delayPercentage;
      final IntWritable delayBuffer = new IntWritable (1);
      for (IntWritable val:values)
	{
	  int cmp = val.compareTo (delayBuffer);
	  if (cmp == 0)
	    totalDelay++;
	    total++;
	}
      delayPercentage = (totalDelay * 100 / total);
        context.write (key, new IntWritable (delayPercentage));
    }
  }

  public static void main (String[]args) throws Exception
  {
    Configuration conf = new Configuration ();
    Job job = new Job (conf, "word count");
      job.setJarByClass (FlightDataAnalysis.class);
      job.setMapperClass (FlightDataAnalysisMapper.class);
      job.setReducerClass (FlightDataAnalysisReducer.class);
      job.setOutputKeyClass (Text.class);
      job.setOutputValueClass (IntWritable.class);
      FileInputFormat.addInputPath (job, new Path (args[0]));
      FileOutputFormat.setOutputPath (job, new Path (args[1]));
      System.exit (job.waitForCompletion (true) ? 0 : 1);
  }
}
