package example;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.KeyValue;
import org.apache.hadoop.hbase.io.ImmutableBytesWritable;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.hbase.client.Put;
import org.apache.hadoop.hbase.mapreduce.TableMapReduceUtil;
import org.apache.hadoop.hbase.util.Bytes;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.joda.time.DateTime;
import org.joda.time.DateTimeZone;
import org.joda.time.format.DateTimeFormat;
import org.joda.time.format.DateTimeFormatter;

import java.io.IOException;
import java.util.Locale;

public class AirDataProcess
{
  public static int count = 0;
  static class Map extends Mapper < LongWritable, Text, Text, Put >
  {
    protected void map (LongWritable key, Text value, Context context)
      throws IOException, InterruptedException
    {
      String fcount = "R" + count++;
      String messageStr = value.toString ();
      Put put = new Put (Bytes.toBytes (fcount));
      if (messageStr.contains (","))
	{
	  String[]logRecvArr = messageStr.split (",");
	  if (logRecvArr.length >= 12)
	    {
	      put.add (Bytes.toBytes ("date"), Bytes.toBytes ("year"),
		       Bytes.toBytes (logRecvArr[0]));
	      put.add (Bytes.toBytes ("date"), Bytes.toBytes ("month"),
		       Bytes.toBytes (logRecvArr[1]));
	      put.add (Bytes.toBytes ("date"), Bytes.toBytes ("day"),
		       Bytes.toBytes (logRecvArr[2]));
	      put.add (Bytes.toBytes ("date"), Bytes.toBytes ("hour"),
		       Bytes.toBytes (logRecvArr[4]));
	      put.add (Bytes.toBytes ("date"), Bytes.toBytes ("min"),
		       Bytes.toBytes (logRecvArr[5]));
	      put.add (Bytes.toBytes ("location"), Bytes.toBytes ("region"),
		       Bytes.toBytes (logRecvArr[6]));
	      put.add (Bytes.toBytes ("data"), Bytes.toBytes ("pid"),
		       Bytes.toBytes (logRecvArr[7]));
	      put.add (Bytes.toBytes ("location"), Bytes.toBytes ("site"),
		       Bytes.toBytes (logRecvArr[8]));
	      put.add (Bytes.toBytes ("data"), Bytes.toBytes ("cams"),
		       Bytes.toBytes (logRecvArr[9]));
	      put.add (Bytes.toBytes ("data"), Bytes.toBytes ("value"),
		       Bytes.toBytes (logRecvArr[10]));
	      put.add (Bytes.toBytes ("data"), Bytes.toBytes ("flag"),
		       Bytes.toBytes (logRecvArr[11]));
	    }
	}
      else
	{
	  System.out.println ("Log is in incorrect format");
	}
      context.write (new Text ("1"), put);
    }
  }

  public static void main (String[]args) throws Exception
  {
    Configuration conf = HBaseConfiguration.create ();
    Job job = new Job (conf, "sample test run");
      job.setJarByClass (AirDataProcess.class);
      job.setOutputKeyClass (Text.class);
      job.setOutputValueClass (Text.class);
      job.setMapOutputKeyClass (Text.class);
      job.setMapOutputValueClass (Text.class);
      job.setInputFormatClass (TextInputFormat.class);
      job.setOutputFormatClass (TextOutputFormat.class);
      FileInputFormat.setInputPaths (job, new Path (args[0]));
      job.setMapperClass (Map.class);
      TableMapReduceUtil.initTableReducerJob (args[1], null, job);
      job.setNumReduceTasks (0);
      System.out.println ("Hello Hadoop Job Completed!!" +
			  job.waitForCompletion (true));
  }
}
