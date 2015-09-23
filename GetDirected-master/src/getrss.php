<?php
//get the q parameter from URL
$q=$_GET["q"];

//find out which feed was selected
if($q=="RI") {
  $xml=("http://traffic.houstontranstar.org/data/rss/incidents_rss.xml");
} elseif($q=="FT") {
  $xml=("http://traffic.houstontranstar.org/data/rss/laneclosures_rss.xml");
}  elseif($q=="45NT") {
  $xml=("http://traffic.houstontranstar.org/data/rss/traveltimes_rss.xml");
}  elseif($q=="45GI") {
  $xml=("http://traffic.houstontranstar.org/data/rss/traffic_rss_ih-45_north.xml");
}  elseif($q=="10KI") {
  $xml=("http://traffic.houstontranstar.org/data/rss/traffic_rss_ih-45_gulf.xml");
}  elseif($q=="10EI") {
  $xml=("http://traffic.houstontranstar.org/data/rss/traffic_rss_ih-10_katy.xml");
}  elseif($q=="59SI") {
  $xml=("http://traffic.houstontranstar.org/data/rss/traffic_rss_ih-10_east.xml");
}  elseif($q=="59EI") {
  $xml=("http://traffic.houstontranstar.org/data/rss/traffic_rss_us-59_southwest.xml");
}  elseif($q=="290NI") {
  $xml=("http://traffic.houstontranstar.org/data/rss/traffic_rss_us-59_eastex.xml");
}  elseif($q=="288I") {
  $xml=("http://traffic.houstontranstar.org/data/rss/traffic_rss_us-290_northwest.xml");
}  elseif($q=="249I") {
  $xml=("http://traffic.houstontranstar.org/data/rss/traffic_rss_sh-249.xml");
}  elseif($q=="255I") {
  $xml=("http://traffic.houstontranstar.org/data/rss/traffic_rss_sh-225.xml");
} else {
}

$xmlDoc = new DOMDocument();
$xmlDoc->load($xml);

//get elements from "<channel>"
$channel=$xmlDoc->getElementsByTagName('channel')->item(0);
$channel_title = $channel->getElementsByTagName('title')
->item(0)->childNodes->item(0)->nodeValue;
$channel_link = $channel->getElementsByTagName('link')
->item(0)->childNodes->item(0)->nodeValue;
$channel_desc = $channel->getElementsByTagName('description')
->item(0)->childNodes->item(0)->nodeValue;

//output elements from "<channel>"
echo("<p><a href='" . $channel_link
  . "'>" . $channel_title . "</a>");
echo("<br>");
echo($channel_desc . "</p>");

//get and output "<item>" elements
$x=$xmlDoc->getElementsByTagName('item');
for ($i=0; $i<=2; $i++) {
  $item_title=$x->item($i)->getElementsByTagName('title')
  ->item(0)->childNodes->item(0)->nodeValue;
  $item_link=$x->item($i)->getElementsByTagName('link')
  ->item(0)->childNodes->item(0)->nodeValue;
  $item_desc=$x->item($i)->getElementsByTagName('description')
  ->item(0)->childNodes->item(0)->nodeValue;
  echo ("<p><a href='" . $item_link
  . "'>" . $item_title . "</a>");
  echo ("<br>");
  echo ($item_desc . "</p>");
}
?>