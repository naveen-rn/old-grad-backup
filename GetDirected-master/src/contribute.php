<!DOCTYPE html>
<html lang="en">
  <head>
  <?php 
	$title = "GetDirected-Contribute";
	include ('../template/header.php');
   ?>
	<script>
	function showRSS(str) {
	  if (str.length==0) { 
	    document.getElementById("rssOutput").innerHTML="";
	    return;
	  }

	  if (window.XMLHttpRequest) {
	    xmlhttp=new XMLHttpRequest();
	  } else {
	    xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	  }

	  xmlhttp.onreadystatechange=function() {
	    if (xmlhttp.readyState==4 && xmlhttp.status==200) {
	      document.getElementById("rssOutput").innerHTML=xmlhttp.responseText;
	    }
	  }

	  xmlhttp.open("GET","getrss.php?q="+str,true);
	  
	  xmlhttp.send();
	}
	</script>  
  </head>

  <body>

  <br>
    <div class="cover-container" align="middle">
      <?php 
        $navigation_label = "navigate";
  	    include ('../template/navigate.php');
      ?>  	
    </div>
    
    <br><br><br><br>
	
	<div class="col-md-3">
	<form>
		<select onchange="showRSS(this.value)" >
			<option value="">Select a feed:</option>
			<option value="RI">All Monitored Road Incidents</option>
			<option value="FT">Freeway Travel Times</option>
			<option value="45NT">45 North Information</option>
			<option value="45GI">45 Gulf Information</option>
			<option value="10KI">10 Katy Information</option>
			<option value="10EI">10 East Information</option>
			<option value="59SI">59 Southwest Information</option>
			<option value="59EI">59 Eastex Information</option>
			<option value="290NI">290 Northwest Information</option>
			<option value="288I">288 Information</option>
			<option value="249I">249 Information</option>
			<option value="255I">225 Information</option>
		</select>
	</form>
    </div>

   	<div class="col-md-8" align="left" color="#fff">
	    <div id="rssOutput" color="#fff">
	    	<h3>RSS Feed on the lane closure and other details</h3>
	    	<h6>Please select the appropriate settings for the details</h6>
	    </div>
	</div>

    <br>    
    <div class="cover-container" align="middle">
      <?php 
        include ('../template/footer.php');
      ?>    
    </div>

  </body>
</html>

