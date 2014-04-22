<?php

  $command = $_GET['command'];

  // Create cURL call
  $service_url = 'http://arduino.local'. $command;
  $curl = curl_init($service_url);
   
  // Send cURL to Yun board
  curl_setopt($curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4 ); 
  //curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
  $curl_response = curl_exec($curl);
  curl_close($curl);

?>