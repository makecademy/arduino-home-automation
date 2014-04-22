// Init board when the interface is opened
window.onload=function (){ 
    $.get( "init.php", {} );
}

// Function to control relays
function relayClick(clicked_id){

    if (clicked_id == "1"){
        $.get( "update_relay.php", {
        command: "/digital/6/1"} );  
    } 

    if (clicked_id == "2"){
        $.get( "update_relay.php", {
        ommand: "/digital/6/0"} );  
    } 

    if (clicked_id == "3"){
        $.get( "update_relay.php", {
        command: "/digital/7/1"} );  
    } 

    if (clicked_id == "4"){
        $.get( "update_relay.php", {
        command: "/digital/7/0"} );  
    }    
}