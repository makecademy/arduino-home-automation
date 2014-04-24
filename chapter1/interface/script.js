setInterval(function() {

  // Read from sensors
  $.get( "xbee.php", {command: "/digital/8/r"}, function( data ) {

    // Transform to JSON
    json_data = jQuery.parseJSON(data);

    // Get sensor ID
    var sensorID = json_data.id;
    if (json_data.return_value == 0){
      $("#display_" + sensorID).css("background-color","gray");    
    }
    else {
      $("#display_" + sensorID).css("background-color","orange");  
    }
        
  });

}, 50);