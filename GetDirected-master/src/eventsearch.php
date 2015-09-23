<!DOCTYPE html>
<html lang="en">
  <head>
  <title>GetDirected-EventSearch</title>

  <?php 
    include('../css/navigationdesign.php'); 
    include('../scripts/specialeventscipt.php'); 
   ?>

  </head>
  <br>
    <div class="cover-container" align="middle">
      <?php 
        $navigation_label = "eventsearch";
  	    include ('../template/navigate.php');
      ?>  	
    </div>
  
    <br>

    <input id="pac-input" class="controls" type="text" placeholder="Search Box">  
    <div id="type-selector" class="controls">
      <input type="radio" name="type" id="show-all" checked="checked">
      <label for="show-all">Show All Special Events</label>

      <input type="radio" name="type" id="avoid-all">
      <label for="avoid-all">Avoid All Events</label>

      &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
      <label text-align="left"> Shows all the available events in the locality </label>

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


