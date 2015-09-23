<div class="masthead clearfix">
  <div class="inner">
    <h3 class="masthead-brand">GetDirected</h3>
    <ul class="nav masthead-nav">
      <?php if ($navigation_label == "home") {
      		echo "<li class=\"active\">"; 
      	} else {
      		echo "<li>";
      	}
       ?>
       <?php echo "<a href=\"../src/home.php\">Home</a>"; ?>
       <?php echo"</li>"; ?>
      <?php if ($navigation_label == "navigate") {
      		echo "<li class=\"active\">"; 
      	} else {
      		echo "<li>";
      	}
       ?>
       <?php echo "<a href=\"../src/navigation.php\">Navigate</a>"; ?>
       <?php echo"</li>"; ?>
      <?php if ($navigation_label == "eventsearch") {
      		echo "<li class=\"active\">"; 
      	} else {
      		echo "<li>";
      	}
       ?>
       <?php echo "<a href=\"../src/eventsearch.php\">Event Search</a>"; ?>
       <?php echo"</li>"; ?>
      <?php if ($navigation_label == "contribute") {
      		echo "<li class=\"active\">"; 
      	} else {
      		echo "<li>";
      	}
       ?>
       <?php echo "<a href=\"../src/contribute.php\">Contribute</a>"; ?>
       <?php echo"</li>"; ?>
      <?php if ($navigation_label == "contactus") {
      		echo "<li class=\"active\">"; 
      	} else {
      		echo "<li>";
      	}
       ?>
       <?php echo "<a href=\"../src/contactus.php\">Contact Us</a>"; ?>
       <?php echo"</li>"; ?>
    </ul>
  </div>
</div>

