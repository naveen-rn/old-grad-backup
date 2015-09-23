<?php
	$mysql_database = "a1825197_lanelis";
	$mysql_user = "a1825197_root";
	$mysql_password = "ethan123#";

	//connect to the database
	$link=mysql_connect("mysql6.000webhost.com", $mysql_user, $mysql_password);
	if(!$link) die("Connection Failure");
	mysql_select_db($mysql_database, $link) or die("Couldn't open $db:".mysql_error());
?> 