<?php

  // Pins to set as output
  $pin1 = "6";
  $pin2 = "7";

  // Create cURL call to init the board
  $curl = curl_init($service_url);
  curl_setopt($curl, CURLOPT_URL,"http://arduino.local/mode/" . $pin1 . "/o");
  curl_setopt($curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4 ); 

  // Send cURL
  $curl_response = curl_exec($curl);
  echo $curl_response;
  curl_close($curl);

  // Create cURL call to init the board
  $curl = curl_init($service_url);
  curl_setopt($curl, CURLOPT_URL,"http://arduino.local/mode/" . $pin2 . "/o");
  curl_setopt($curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4 ); 
   
  // Send cURL
  $curl_response = curl_exec($curl);
  echo $curl_response;
  curl_close($curl);
?>