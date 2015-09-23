package examples;

/*
 * NetFlixAnalysisCanopyData is a class which is used for canopy data
 * preparation from the given inputfile to the output file for the
 * canopy clustering. This belongs to step 2 in the process.
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
import org.apache.hadoop.io.LongWritable;
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

public class NetFlixAnalysisCanopyData
{
    public static class NetFlixAnalysisCanopyDataMapper
            extends Mapper < LongWritable, Text, Text, Text >
        {
			private ArrayList<String> canopyCenters = new ArrayList<String>();

            @Override
            public void map (LongWritable key, Text value, Context context)
                throws IOException, InterruptedException
            {
                Scanner scanner = new Scanner (value.toString ());
                scanner.useDelimiter("	");
                String[] words = new String[2];

                int i = 0;
                while (scanner.hasNext ())
                {
                    words[i++] = scanner.next ();
                }

				String movie_id = words[0];
				String data = words[1];

				String curr = NetflixMovie(movie_id, data);

				boolean too_close = false;
			
				for(i = 0; i < canopyCenters.size(); i++) {
					if(MatchCount(curr, canopyCenters.get(i).toString()) > 10) {
						too_close = true;
						break;
					}
				}
			
				if(!too_close) {
					context.write(new Text(movie_id), new Text(data));
					canopyCenters.add(curr);
				} 
			}
        
			public String NetflixMovie(String id, String data) {
				id = id.concat("-");
				return id.concat(data);
			}

			public int MatchCount(String current, String canopy) {
                int matchCount = 0;

                Scanner scanner1 = new Scanner (current.toString ());
                scanner1.useDelimiter("-");
             	Scanner scanner2 = new Scanner (canopy.toString ());
                scanner2.useDelimiter("-");
                String[] curr = new String[2];
                String[] cano = new String[2];

                int i = 0;
                while (scanner1.hasNext())
                {
                    curr[i++] = scanner1.next ();
                }
                i = 0;
                while (scanner2.hasNext())
                {
                    cano[i++] = scanner2.next ();
                }

                if(curr[0] != cano[0]) {
	                Scanner scanner3 = new Scanner (curr[1]);
	                Scanner scanner4 = new Scanner (cano[1]);
	                scanner3.useDelimiter(",");
	                scanner4.useDelimiter(",");

	                ArrayList<String> temp1 = new ArrayList<String>();
	                ArrayList<String> temp2 = new ArrayList<String>();

	                i = 0;
	                while(scanner3.hasNext()) {
	                	temp1.add(scanner3.next());
	                }
	                i = 0;
	                while(scanner4.hasNext()) {
	                	temp2.add(scanner4.next());
	                }

	                int j;
	                for(i = 0; i < temp1.size(); i++) {
	                	for (j = 0; j < temp2.size(); j++) {
	                		if (temp1.get(i).toString().equals(temp2.get(j).toString())) {
	                			matchCount++;
	                		}
	                	}
	                }

                }

                return matchCount;
			}

        }

    public static class NetFlixAnalysisCanopyDataReducer
            extends Reducer < Text, Text, Text, Text >
        {
			private int count = 0;
			private ArrayList<String> canopyCenters = new ArrayList<String>();

            public void reduce (Text key, Text values,
                    Context context) throws IOException,
                    InterruptedException
            {
				String movie_id = key.toString();
				String data = values.toString();

				String curr = NetflixMovie(movie_id, data);

				boolean too_close = false;

				int i;			
				for(i = 0; i < canopyCenters.size(); i++) {
					if(MatchCount(curr, canopyCenters.get(i).toString()) > 10) {
						too_close = true;
						break;
					}
				}
			
				if(!too_close) {
					context.write(new Text(movie_id), new Text(data));
					canopyCenters.add(curr);
				} 
			}
        
			public String NetflixMovie(String id, String data) {
				id = id.concat("-");
				return id.concat(data);
			}

			public int MatchCount(String current, String canopy) {
                int matchCount = 0;

                Scanner scanner1 = new Scanner (current.toString ());
                scanner1.useDelimiter("-");
             	Scanner scanner2 = new Scanner (canopy.toString ());
                scanner2.useDelimiter("-");
                String[] curr = new String[2];
                String[] cano = new String[2];

                int i = 0;
                while (scanner1.hasNext())
                {
                    curr[i++] = scanner1.next ();
                }
                i = 0;
                while (scanner2.hasNext())
                {
                    cano[i++] = scanner2.next ();
                }

                if(curr[0] != cano[0]) {
	                Scanner scanner3 = new Scanner (curr[1]);
	                Scanner scanner4 = new Scanner (cano[1]);
	                scanner3.useDelimiter(",");
	                scanner4.useDelimiter(",");

	                ArrayList<String> temp1 = new ArrayList<String>();
	                ArrayList<String> temp2 = new ArrayList<String>();

	                i = 0;
	                while(scanner3.hasNext()) {
	                	temp1.add(scanner3.next());
	                }
	                i = 0;
	                while(scanner4.hasNext()) {
	                	temp2.add(scanner4.next());
	                }

	                int j;
	                for(i = 0; i < temp1.size(); i++) {
	                	for (j = 0; j < temp2.size(); j++) {
	                		if (temp1.get(i).toString().equals(temp2.get(j).toString())) {
	                			matchCount++;
	                		}
	                	}
	                }

                }

                return matchCount;
			}

        }
	
    
    public static void main (String[]args) throws Exception
    {
        Configuration conf = new Configuration ();
        Job job = new Job (conf, "naveen_net_flix_data_aggregation");
        job.setJarByClass (NetFlixAnalysisCanopyData.class);

        job.setMapperClass (NetFlixAnalysisCanopyDataMapper.class);
        job.setReducerClass (NetFlixAnalysisCanopyDataReducer.class);

        job.setMapOutputKeyClass(Text.class);
        job.setMapOutputValueClass(Text.class);

        job.setOutputKeyClass (Text.class);
        job.setOutputValueClass (Text.class);

        FileInputFormat.addInputPath (job, new Path (args[0]));
        FileOutputFormat.setOutputPath (job, new Path (args[1]));
        
        job.setNumReduceTasks(1);
        
        System.exit (job.waitForCompletion (true) ? 0 : 1);
    }
}