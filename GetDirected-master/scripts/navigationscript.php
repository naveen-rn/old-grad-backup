<?php
	include('../template/config.php');
  	$freewayData = array(
		array(49.2812668, -123.1035942, "26 E Hastings St, Vancouver" ), 
		array(49.2814064, -123.1025187, "71 E Hastings St, Vancouver" ), 
  	);
	$query=mysql_query("SELECT * FROM `freewaylist` LIMIT 0,30");
	$num_rows=mysql_num_rows($query);
	while($row=mysql_fetch_array($query)) {
  		echo array_push($freewayData, $row);
	}
  	mysql_close($link);
?>

<?php
	include('../template/config.php');
  	$streetData = array(
		array(49.2812336, -123.1020622, "122 E Hastings St, Vancouver" ), 
  	);
	$query=mysql_query("SELECT * FROM `streetlist` LIMIT 0,30");
	$num_rows=mysql_num_rows($query);
	while($row=mysql_fetch_array($query)) {
  		echo array_push($streetData, $row);
	}
  	mysql_close($link);
?>

<?php
	include('../template/config.php');
  	$otherData = array(
		array(49.2813564, -123.1012253, "138 E Hastings St, Vancouver" ), 
		array(49.2811625, -123.0985032, "242 E Hastings St, Vancouver" )
  	);
	$query=mysql_query("SELECT * FROM `otherlist` LIMIT 0,30");
	$num_rows=mysql_num_rows($query);
	while($row=mysql_fetch_array($query)) {
  		echo array_push($otherData, $row);
	}
  	mysql_close($link);
?>

<script src="https://maps.googleapis.com/maps/api/js?v=3.exp&sensor=false&libraries=places"></script>
<script type="Text/javascript">
var freewayData = <?php echo json_encode($freewayData); ?>;
function freewayList()
{
	return freewayData;
}

var streetData = <?php echo json_encode($streetData); ?>;
function streetList()
{
	return streetData;
}

var otherData = <?php echo json_encode($otherData); ?>;
function otherList()
{
	return otherData;
}

function initialize() 
{
  	var markers = [];
  	var input = document.getElementById('pac-input');
  	var bounds = new google.maps.LatLngBounds();
  	var autocomplete = new google.maps.places.Autocomplete(input);

  	var map = new google.maps.Map(document.getElementById('map-canvas'), {
    	center: new google.maps.LatLng(29.796559, -95.367036),
    	zoom: 10
  	});

  	map.controls[google.maps.ControlPosition.TOP_LEFT].push(input);
  	autocomplete.bindTo('bounds', map);

  	var searchBox = new google.maps.places.SearchBox((input));

  	google.maps.event.addListener(searchBox, 'places_changed', function() {
    
    	var places = searchBox.getPlaces();
    	var bounds = new google.maps.LatLngBounds();
    	markers = [];

	    setupClickListener('show-all', []);
		setupClickListener('show-freeway', ['show-freeway']);
		setupClickListener('show-street', ['show-street']);
		setupClickListener('show-other', ['show-other']);
		setupClickListener('avoid-all', ['avoid-all']);

		function setupClickListener(id, types) {
	    	var radioButton = document.getElementById(id);
	    	google.maps.event.addDomListener(radioButton, 'click', function() {
	      		var lanesclosed, image;
	      		if (types == "show-other") {
	      			lanesclosed = otherList();
	      			image = new google.maps.MarkerImage('../image/red.png', null, null, null, new google.maps.Size(40, 40));
					for (var i in lanesclosed)
					{
					    var p = lanesclosed[i];
					    var latlng = new google.maps.LatLng(p[0], p[1]);
					    bounds.extend(latlng);
					    var marker = new google.maps.Marker({
					        position: latlng,
					        map: map,
					        icon: image,
					    });
					    markers.push(marker);
					}
	      		} else if (types == "show-freeway") {
	      			lanesclosed = freewayList();
	      			image = new google.maps.MarkerImage('../image/pink.png', null, null, null, new google.maps.Size(40, 40));
					for (var i in lanesclosed)
					{
					    var p = lanesclosed[i];
					    var latlng = new google.maps.LatLng(p[0], p[1]);
					    bounds.extend(latlng);
					    var marker = new google.maps.Marker({
					        position: latlng,
					        map: map,
					        icon: image,
					    });
					    markers.push(marker);
					}
	      		} else if (types == "show-street") {
	      			lanesclosed = streetList();
	      			image = new google.maps.MarkerImage('../image/orange.png', null, null, null, new google.maps.Size(40, 40));
					for (var i in lanesclosed)
					{
					    var p = lanesclosed[i];
					    var latlng = new google.maps.LatLng(p[0], p[1]);
					    bounds.extend(latlng);
					    var marker = new google.maps.Marker({
					        position: latlng,
					        map: map,
					        icon: image,
					    });
					    markers.push(marker);
					}
	      		} else if (types == "avoid-all") {
	      			markers = [];
	      		} else {
	      			lanesclosed = otherList();
	      			image = new google.maps.MarkerImage('../image/red.png', null, null, null, new google.maps.Size(40, 40));
					for (var i in lanesclosed)
					{
					    var p = lanesclosed[i];
					    var latlng = new google.maps.LatLng(p[0], p[1]);
					    bounds.extend(latlng);
					    var marker = new google.maps.Marker({
					        position: latlng,
					        map: map,
					        icon: image,
					    });
					    markers.push(marker);
					}
	      			lanesclosed = freewayList();
	      			image = new google.maps.MarkerImage('../image/pink.png', null, null, null, new google.maps.Size(40, 40));
					for (var i in lanesclosed)
					{
					    var p = lanesclosed[i];
					    var latlng = new google.maps.LatLng(p[0], p[1]);
					    bounds.extend(latlng);
					    var marker = new google.maps.Marker({
					        position: latlng,
					        map: map,
					        icon: image,
					    });
					    markers.push(marker);
					}
	      			lanesclosed = streetList();
	      			image = new google.maps.MarkerImage('../image/orange.png', null, null, null, new google.maps.Size(40, 40));
					for (var i in lanesclosed)
					{
					    var p = lanesclosed[i];
					    var latlng = new google.maps.LatLng(p[0], p[1]);
					    bounds.extend(latlng);
					    var marker = new google.maps.Marker({
					        position: latlng,
					        map: map,
					        icon: image,
					    });
					    markers.push(marker);
					}
	      		}
			});
		}


	    for (var i = 0, place; place = places[i]; i++) {
	      var marker = new google.maps.Marker({
	        map: map,
	        position: place.geometry.location
	      });

  		  map.setZoom(15);
          map.setCenter(marker.getPosition());
	      markers.push(marker);
	      bounds.extend(place.geometry.location);
	    }

	map.fitBounds(bounds);
	});
}

google.maps.event.addDomListener(window, 'load', initialize);
google.maps.event.addDomListener(window, 'unload', google.maps.Unload);
</script>
