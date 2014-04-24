<?php

// Get commands
$command = $_GET['command'];

// Includes
include "php_serial.class.php";

// Get configuration data
$serial_port = "/dev/cu.usbserial-A702LF8B";

$serial = new phpSerial;
$serial->deviceSet($serial_port);
$serial->confBaudRate(9600);
$serial->confParity("none");
$serial->confCharacterLength(8);
$serial->confStopBits(1);

$h = popen('nohup sleep 5 < '. $serial_port . ' &', 'r');
pclose($h);
exec('stty -F '. $serial_port .' -hupcl');
usleep(100000);

$serial->deviceOpen();

// Send command
$serial->sendMessage($command . "\r");
$answer = $serial->readPort();
$serial->sendMessage($command . "\r");
$answer = $answer . $serial->readPort();
$serial->deviceClose();

// Return JSON
$first_part = strstr($answer, '{');
$answer = strstr($first_part, '}', true);
if ($answer != "") {
	echo $answer;	
}
else {
	echo "{\"connected\": false}";
}

?>