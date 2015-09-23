<!DOCTYPE html>
<html lang="en">
  <head>
  <?php 
	$title = "GetDirected-LearnMore";
	include ('../template/header.php');
   ?>
  </head>

  <body>
  
  <?php 
	$navigation_label = "home";
    include ('../template/body_head.php'); 
    include ('../template/navigate.php');
   ?>

  
  <div class="row">
  	<div class="col-sm-6 col-md-4">
    	<div class="thumbnail">
      		<img src="../image/navigation.jpg">
      		<div class="caption">
        		<h3>Navigation</h3>
        		<p>The most reliable and easy way to get updated with the lane closure details on you rway. Be it the 
        		street, freeway or any other track, the details are most updated.
        		</p>
        		<p><a href="../src/navigation.php" class="btn btn-primary" role="button">Launch</a></p>
      		</div>
    	</div>
  	</div>
  	<div class="col-sm-6 col-md-4">
    	<div class="thumbnail">
      		<img src="../image/eventlist.jpg">
      		<div class="caption">
        		<h3>Special Events List</h3>
        		<p>Want to know what happens around your neighbourhood ? Or are you planning a quite ride ? 
        		check for the special events, be it a gala or some festive occasion, get a valid piece of information!</p>
        		<p><a href="../src/eventsearch.php" class="btn btn-primary" role="button">Launch</a></p>
      		</div>
    	</div>
  	</div>
  	<div class="col-sm-6 col-md-4">
    	<div class="thumbnail">
      		<img src="../image/connect.jpg">
      		<div class="caption">
        		<h3>Get Connected</h3>
        		<p>This sample page is the projected plan, where the details for your navigation and travel plan can be 
        		made through details collected from your social network details. Be it your friends post or a random 
        		tweet, your social connectivity will help you to plan your trip. 
        		</p>
        		<p><a href="../src/contribute.php" class="btn btn-primary" role="button">Launch</a></p>
      		</div>
    	</div>
  	</div>
  </div>

  <div class="inner cover">

  </div>
  <!-- Template Footer and Body-Footer Started -->

  <?php 
	include ('../template/footer.php');
	include ('../template/scripts.php');
	include ('../template/body_footer.php');
   ?>

  </body>
</html>

