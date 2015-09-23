package example;

public enum HColumnEnum
{
  SRV_COL_YEAR ("year".getBytes ()),
  SRV_COL_MONTH ("month".getBytes ()),
  SRV_COL_DAY ("day".getBytes ()),
  SRV_COL_HOUR ("hour".getBytes ()),
  SRV_COL_MIN ("min".getBytes ()),
  SRV_COL_REGION ("region".getBytes ()),
  SRV_COL_PID ("pid".getBytes ()),
  SRV_COL_PIN ("pin".getBytes ()),
  SRV_COL_SITE ("site".getBytes ()),
  SRV_COL_CAMS ("cams".getBytes ()),
  SRV_COL_VALUE ("value".getBytes ()),
  SRV_COL_FLAG ("flag".getBytes ());

  private final byte[] columnName;

    HColumnEnum (byte[]column)
  {
    this.columnName = column;
  }

  public byte[] getColumnName ()
  {
    return this.columnName;
  }
}