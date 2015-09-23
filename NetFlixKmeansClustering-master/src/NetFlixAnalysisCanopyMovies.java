package examples;

/*
 * NetFlixAnalysisCanopyMovies is a class which is used for canopy data
 * preparation from the given inputfile to the output file for the
 * canopy clustering. This belongs to step 3 in the process.
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

import java.io.BufferedReader;
import java.io.FileReader;

public class NetFlixAnalysisCanopyMovies
{
    public static class NetFlixAnalysisCanopyMoviesMapper
            extends Mapper < LongWritable, Text, Text, Text >
        {
			String readFile() throws IOException {
			    BufferedReader br = new BufferedReader(new FileReader("output_step2/part-r-00000"));
			    try {
			        StringBuilder sb = new StringBuilder();
			        String line = br.readLine();

			        while (line != null) {
			            sb.append(line);
			            sb.append("\n");
			            line = br.readLine();
			        }
			        return sb.toString();
			    } finally {
			        br.close();
			    }
			}

            @Override
            public void map (LongWritable key, Text value, Context context)
                throws IOException, InterruptedException
            {
				ArrayList<String> canopyCenters = new ArrayList<String>();
				canopyCenters.add(readFile());

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

				ArrayList<String> canopyBuffer = new ArrayList<String>();
				Scanner scanner1 = new Scanner(canopyCenters.get(0).toString());
				scanner1.useDelimiter("\n");
				while (scanner1.hasNext()) {
					canopyBuffer.add(scanner1.next());
				}

				String distanceVector = new String();
				distanceVector = distanceVector.concat("{ ");
				for(i = 0; i < canopyBuffer.size(); i++) {
	                Scanner scanner2 = new Scanner (canopyBuffer.get(i).toString ());
	                scanner2.useDelimiter("	");
	                String[] words1 = new String[2];
	                int j = 0;
	                while (scanner2.hasNext ())
	                {
	                    words1[j++] = scanner2.next ();
	                }
	
					String movie_id1 = words1[0];
					String data1 = words1[1];

					String curr1 = NetflixMovie(movie_id1, data1);

					int matchCount = MatchCount(curr, curr1);
					distanceVector = distanceVector.concat(movie_id1);
					distanceVector = distanceVector.concat(":");
					distanceVector = distanceVector.concat(Integer.toString(matchCount));
					distanceVector = distanceVector.concat(" ,");

				}
				distanceVector = distanceVector.substring(0, distanceVector.length()-1);
				distanceVector = distanceVector.concat(" }");
				data = "{ ".concat(data);
				data = data.concat(" }");
				data = data.concat(" : ");
				data = data.concat(distanceVector); 

				context.write(new Text(movie_id), new Text(data));
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

    public static class NetFlixAnalysisCanopyMoviesReducer
            extends Reducer < Text, Text, Text, Text >
        {
            public void reduce (Text key, Text values,
                    Context context) throws IOException,
                    InterruptedException
            {
            	context.write(key, values);
			}
        }
	
    
    public static void main (String[]args) throws Exception
    {
        Configuration conf = new Configuration ();
        Job job = new Job (conf, "naveen_net_flix_data_aggregation");
        job.setJarByClass (NetFlixAnalysisCanopyMovies.class);

        job.setMapperClass (NetFlixAnalysisCanopyMoviesMapper.class);
        job.setReducerClass (NetFlixAnalysisCanopyMoviesReducer.class);

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