<!DOCTYPE html>
<html lang="en">
  <head>
  <title>GetDirected-Navigation</title>

  <?php 
    include('../css/navigationdesign.php'); 
    include('../scripts/navigationscript.php'); 
   ?>

  </head>
  <body onload="test1('<?php echo $lat;?>'">
  <br>
    <div class="cover-container" align="middle">
      <?php 
        $navigation_label = "navigate";
  	    include ('../template/navigate.php');
      ?>  	
    </div>
  
    <br>

    <input id="pac-input" class="controls" type="text" placeholder="Search Box">  
    <div id="type-selector" class="controls">
      <input type="radio" name="type" id="avoid-all"  checked="checked">
      <label for="avoid-all">Avoid All Incidents</label>

      <input type="radio" name="type" id="show-all">
      <label for="show-all">Show All Incidents</label>

      <input type="radio" name="type" id="show-freeway">
      <label for="show-freeway">Show Freeway Incidents</label>

      <input type="radio" name="type" id="show-street">
      <label for="show-street">Show Street Incidents</label>

      <input type="radio" name="type" id="show-other">
      <label for="show-other">Show Other Incidents</label>

      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
      <label text-align="left"> Please select the proper lane closure incidents or select 'ALL' to avoid all types of lane closures </label>

    </div>
    <div id="map-canvas"></div>
    <br>
    <br>    
    <div class="cover-container" align="middle">
      <?php 
        include ('../template/footer.php');
      ?>    
    </div>
  </body>
</html>


