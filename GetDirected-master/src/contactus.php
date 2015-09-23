<!DOCTYPE html>
<html lang="en">
  <head>
  <?php 
	$title = "GetDirected-ContactUS";
	include ('../template/header.php');
   ?>
  </head>

  <body>
  
  <?php 
	$navigation_label = "contactus";
    include ('../template/body_head.php'); 
    include ('../template/navigate.php');
   ?>

  <div class="inner cover" align ="left">
  <div class="col-md-3">
    <address>
      <strong>Contact Us.</strong><br><br>
      <strong>Some Corporation.</strong><br>
      Houston Technology Center<br>
      410 Pierce St, 
      Houston, TX 77002<br>
      <abbr title="Phone">P:</abbr> (123) 456-7890
    </address>

    <address>
      <strong>Full Name</strong><br>
      <a href="mailto:#">first.last@example.com</a>
    </address>
  </div>
  <div class="col-md-3">
    <strong>Comments.</strong><br><br>
    <form role="form">
    <input type="text" class="form-control" id="text" name="text_name" style="width: 500px; height: 180px;" 
           placeholder="Please provide your comments here" />
  </div>
  </div>
  <!-- Template Footer and Body-Footer Started -->

  <?php 
	include ('../template/footer.php');
	include ('../template/scripts.php');
	include ('../template/body_footer.php');
   ?>

  </body>
</html>

