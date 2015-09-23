package example;

import java.io.*;
import java.util.*;
import java.net.*;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.conf.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapred.*;
import org.apache.hadoop.util.*;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.LocalFileSystem;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.WritableComparable;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.KeyValue;
import org.apache.hadoop.hbase.io.ImmutableBytesWritable;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.hbase.client.Put;
import org.apache.hadoop.hbase.client.Result;
import org.apache.hadoop.hbase.client.Scan;
import org.apache.hadoop.hbase.mapreduce.TableMapReduceUtil;
import org.apache.hadoop.hbase.util.Bytes;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.joda.time.DateTime;
import org.joda.time.DateTimeZone;
import org.joda.time.format.DateTimeFormat;
import org.joda.time.format.DateTimeFormatter;
import org.apache.hadoop.hbase.io.ImmutableBytesWritable;
import org.apache.hadoop.hbase.mapreduce.TableInputFormat;
import org.apache.hadoop.hbase.mapreduce.TableMapReduceUtil;
import org.apache.hadoop.hbase.mapreduce.TableMapper;
import org.apache.hadoop.hbase.util.Bytes;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.SequenceFileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import java.io.IOException;
import java.util.Locale;

public class AirqualityRolling
{
    public static class MyMapper extends TableMapper<Text, IntWritable> {
        public static final byte[] DATA = "data".getBytes();
        public static final byte[] DATE = "date".getBytes();
        public static final byte[] LOCATION = "location".getBytes();

        public static final byte[] YEAR = "year".getBytes();
        public static final byte[] MONTH = "month".getBytes();
        public static final byte[] DAY = "day".getBytes();
        public static final byte[] HOUR = "hour".getBytes();
        public static final byte[] MINUTE = "minute".getBytes();
        public static final byte[] REGION = "region".getBytes();
        public static final byte[] SITE = "site".getBytes();
        public static final byte[] CAMS = "cams".getBytes();
        public static final byte[] FLAG = "flag".getBytes();
        public static final byte[] PID = "param_id".getBytes();
        public static final byte[] PIN = "param_name".getBytes();
        public static final byte[] VALU = "value".getBytes();
        
        private IntWritable ONE;
        private Text text = new Text();

        public void map(ImmutableBytesWritable row, Result value, Context context) throws IOException, InterruptedException
        {
            String year = new String(value.getValue(DATE, YEAR));
            String month = new String(value.getValue(DATE, MONTH));
            String day = new String(value.getValue(DATE, DAY));
            String hour = new String(value.getValue(DATE, HOUR));
            String minute = new String(value.getValue(DATE, MINUTE));
            String region = new String(value.getValue(LOCATION, REGION));
            String site = new String(value.getValue(LOCATION, SITE));
            String cams = new String(value.getValue(DATA, CAMS));
            String flag = new String(value.getValue(DATA, FLAG));
            String pid = new String(value.getValue(DATA, PID));
            String pin = new String(value.getValue(DATA, PIN));
            String val = new String(value.getValue(DATA, VALU));
            double val2;
            try {
                val2 = Double.parseDouble(val.trim());
            }
            catch (NumberFormatException e) {
                val2 = 0;
            }

            ONE = new IntWritable ((int)val2);

            if(checkHoustonSite(site) && checkO3(pid) && flag.equals("\"\""))
            {
                String key = year. concat(month);
                key = key. concat(day). concat(":");
                key = key. concat(region). concat(":");
                key = key. concat(site). concat(":");
                key = key. concat(hour);
                text.set(key);
                context.write(text, ONE);
            }
        }

        public boolean checkO3(String pid)
        {
            if(pid.equals("44201"))
                return true;
            else
                return false;
        }

        public boolean checkHoustonSite(String site)
        {
            ArrayList siteList = new ArrayList();
            siteList.add("1");
            siteList.add("8");
            siteList.add("18");
            siteList.add("22");
            siteList.add("26");
            siteList.add("35");
            siteList.add("48");
            siteList.add("51");
            siteList.add("53");
            siteList.add("81");
            siteList.add("108");
            siteList.add("110");
            siteList.add("139");
            siteList.add("146");
            siteList.add("150");
            siteList.add("154");
            siteList.add("169");
            siteList.add("181");
            siteList.add("235");
            siteList.add("240");
            siteList.add("404");
            siteList.add("405");
            siteList.add("406");
            siteList.add("407");
            siteList.add("409");
            siteList.add("410");
            siteList.add("411");
            siteList.add("671");
            siteList.add("673");
            siteList.add("695");
            siteList.add("697");
            siteList.add("698");
            siteList.add("699");
            siteList.add("1001");

            if(siteList.contains(site))
                return true;
            else
                return false;
        }
    }



    public static class MyReducer extends Reducer<Text, IntWritable, Text, IntWritable>  
    {
        public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException 
        {
             int i = 0;
             for (IntWritable val : values) {
                 i += val.get();
             }
             context.write(key, new IntWritable (i));
        }
     }

    public static void main (String[] args) throws Exception
    {
        Configuration config = HBaseConfiguration.create();
        Job job = new Job(config, "AirqualityHBasetoHFile");
        job.setJarByClass(AirqualityRolling.class);

        Scan scan = new Scan();
        scan.setCaching(500);
        scan.setCacheBlocks(false);

        TableMapReduceUtil.initTableMapperJob(
                args[0],
                scan,
                MyMapper.class,
                Text.class,
                IntWritable.class,
                job);
        job.setReducerClass(MyReducer.class);
        job.setNumReduceTasks(1);

        FileOutputFormat.setOutputPath(job, new Path(args[1]));

        boolean b = job.waitForCompletion(true);
        if(!b) {
            throw new IOException("Error with the Job!");
        }
    }
}
