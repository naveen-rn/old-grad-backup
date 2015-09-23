<?php
	include('../template/config.php');
  	$specialEventsData = array(
		array(49.2812668, -123.1035942, "Aarambam Preview Show", "26 E Hastings St, Vancouver" ), 
		array(49.2814064, -123.1025187, "CSK Cricket Match", "71 E Hastings St, Vancouver" ), 
  	);
	$query=mysql_query("SELECT * FROM `specialevents` LIMIT 0,30");
	$num_rows=mysql_num_rows($query);
	while($row=mysql_fetch_array($query)) {
  		echo array_push($specialEventsData, $row);
	}
 	mysql_close($link);
?>

<script src="https://maps.googleapis.com/maps/api/js?v=3.exp&sensor=false&libraries=places"></script>
<script type="Text/javascript">
var specialEvents = <?php echo json_encode($specialEventsData); ?>;
function specialEventsList()
{
	return specialEvents;
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

	    setupClickListener('show-all', ['show-all']);
		setupClickListener('avoid-all', []);

		function setupClickListener(id, types) {
	    	var radioButton = document.getElementById(id);
	    	google.maps.event.addDomListener(radioButton, 'click', function() {
	      		var lanesclosed, image;
	      		if (types == "show-all") {
	      			specialevents = specialEventsList();
	      			image = new google.maps.MarkerImage('../image/blue.png', null, null, null, new google.maps.Size(40, 40));
					for (var i in specialevents)
					{
					    var p = specialevents[i];
					    var latlng = new google.maps.LatLng(p[0], p[1]);
					    bounds.extend(latlng);
					    var marker = new google.maps.Marker({
					        position: latlng,
					        map: map,
					        icon: image,
					    });

					    markers.push(marker);
					}
	      		} else {
	      			infoWindows = [];
	      			markers = [];
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
