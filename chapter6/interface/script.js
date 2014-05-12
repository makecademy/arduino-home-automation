var target = '/dev/cu.usbserial-A102JJ6G';
var type = 'serial';

window.onload = function() {
    $.get( "command.php", {target: target, type: type, command: "/mode/7/o"} );
}

// Function to control LEDs
function buttonClick(clicked_id){

    if (clicked_id == "1"){
        $.get( "command.php", {
        target: target, type: type, command: "/digital/7/1"} );  
    } 

    if (clicked_id == "2"){
        $.get( "command.php", {
        target: target, type: type, command: "/digital/7/0"} );  
    } 
}