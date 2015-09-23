<!DOCTYPE html>
<html lang="en">
  <head>
  <?php 
	$title = "GetDirected-Cover";
	include ('../template/header.php');
   ?>
  </head>

  <body>
  
  <?php 
	$navigation_label = "home";
    include ('../template/body_head.php'); 
    include ('../template/navigate.php');
   ?>

  <div class="inner cover">
    <h1 class="cover-heading">Get Directed.</h1>
  	<p class="lead">
  	A web Application to get you directed on the right track. Check the special events on 
  	your way and get directed with the most updated lane closures details.  
  	</p>
  	<p class="lead">
    	<a href="learnmore.php" class="btn btn-lg btn-default">Learn More</a>
  	</p>
  </div>
  <!-- Template Footer and Body-Footer Started -->

  <?php 
	include ('../template/footer.php');
	include ('../template/scripts.php');
	include ('../template/body_footer.php');
   ?>

  </body>
</html>

