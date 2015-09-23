package example;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.KeyValue;
import org.apache.hadoop.hbase.io.ImmutableBytesWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.hbase.client.Put;
import org.apache.hadoop.hbase.util.Bytes;

public class HBaseKVMapper extends
  Mapper < LongWritable, Text, ImmutableBytesWritable, KeyValue >
{

  final static byte[] SRV_COL_FAM_DATE = "date".getBytes ();
  final static byte[] SRV_COL_FAM_LOC = "location".getBytes ();
  final static byte[] SRV_COL_FAM_DATA = "data".getBytes ();

  final static int NUM_FIELDS = 12;

  String tableName = "";

  ImmutableBytesWritable hKey = new ImmutableBytesWritable ();
  KeyValue kv;

  @Override
  protected void setup (Context context) throws IOException,
    InterruptedException
    {
      Configuration c = context.getConfiguration ();
      tableName = c.get ("hbase.table.name");
    }

  int count = 0;
   @Override
    protected void map (LongWritable key, Text value, Context context)
    throws IOException, InterruptedException
  {
    String[] fields = null;
    fields = (value.toString ()).split (",");
    String dt;
    String rowID = "R" + count++;
    dt = fields[1];
    hKey.set (String.format ("%s:%s", dt, rowID).getBytes ());

    if (!fields[0].equals (""))
      {
	kv = new KeyValue (hKey.get (), SRV_COL_FAM_DATE,
			   HColumnEnum.SRV_COL_YEAR.getColumnName (),
			   fields[0].getBytes ());
	context.write (hKey, kv);
      }

    if (!fields[1].equals (""))
      {
	kv = new KeyValue (hKey.get (), SRV_COL_FAM_DATE,
			   HColumnEnum.SRV_COL_MONTH.getColumnName (),
			   fields[1].getBytes ());
	context.write (hKey, kv);
      }

    if (!fields[2].equals (""))
      {
	kv = new KeyValue (hKey.get (), SRV_COL_FAM_DATE,
			   HColumnEnum.SRV_COL_DAY.getColumnName (),
			   fields[2].getBytes ());
	context.write (hKey, kv);
      }

    if (!fields[3].equals (""))
      {
	kv = new KeyValue (hKey.get (), SRV_COL_FAM_DATE,
			   HColumnEnum.SRV_COL_HOUR.getColumnName (),
			   fields[3].getBytes ());
	context.write (hKey, kv);
      }

    if (!fields[4].equals (""))
      {
	kv = new KeyValue (hKey.get (), SRV_COL_FAM_DATE,
			   HColumnEnum.SRV_COL_MIN.getColumnName (),
			   fields[4].getBytes ());
	context.write (hKey, kv);
      }

    if (!fields[5].equals (""))
      {
	kv = new KeyValue (hKey.get (), SRV_COL_FAM_LOC,
			   HColumnEnum.SRV_COL_REGION.getColumnName (),
			   fields[5].getBytes ());
	context.write (hKey, kv);
      }

    if (!fields[6].equals (""))
      {
	kv = new KeyValue (hKey.get (), SRV_COL_FAM_DATA,
			   HColumnEnum.SRV_COL_PID.getColumnName (),
			   fields[6].getBytes ());
	context.write (hKey, kv);
      }

    if (!fields[7].equals (""))
      {
	kv = new KeyValue (hKey.get (), SRV_COL_FAM_LOC,
			   HColumnEnum.SRV_COL_PIN.getColumnName (),
			   fields[7].getBytes ());
	context.write (hKey, kv);
      }

    if (!fields[8].equals (""))
      {
	kv = new KeyValue (hKey.get (), SRV_COL_FAM_DATA,
			   HColumnEnum.SRV_COL_SITE.getColumnName (),
			   fields[8].getBytes ());
	context.write (hKey, kv);
      }

    if (!fields[9].equals (""))
      {
	kv = new KeyValue (hKey.get (), SRV_COL_FAM_DATA,
			   HColumnEnum.SRV_COL_CAMS.getColumnName (),
			   fields[9].getBytes ());
	context.write (hKey, kv);
      }

    if (!fields[10].equals (""))
      {
	kv = new KeyValue (hKey.get (), SRV_COL_FAM_DATA,
			   HColumnEnum.SRV_COL_VALUE.getColumnName (),
			   fields[10].getBytes ());
	context.write (hKey, kv);
      }

    if (!fields[11].equals (""))
      {
	kv = new KeyValue (hKey.get (), SRV_COL_FAM_DATA,
			   HColumnEnum.SRV_COL_FLAG.getColumnName (),
			   fields[11].getBytes ());
	context.write (hKey, kv);
      }

    context.getCounter ("HBaseKVMapper", "NUM_MSGS").increment (1);
  }
}