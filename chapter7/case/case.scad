// Variables

// Box
length = 50;
width = 25;
height = 10;
thickness = 1;
tolerance = 1;

// Attaches
hole_radius = 1.1;
attaches_height = 5;

distance_wall_left_attach_1 = 8.9;
distance_wall_top_attach_1 = 2.54;

distance_wall_right_attach_2 = 2.54;
distance_wall_bottom_attach_2 = 7.62;

// Hole
hole_width = 10; 
hole_height = 5;

// Main box
difference() {
  cube([length+2*thickness+tolerance,width+2*thickness+tolerance,height+2*thickness],center = true);
  translate([0,0,2*thickness]){
    cube([length+tolerance,width+tolerance,height],center = true);
  }	
  translate([-length/2,0,height/2-hole_height/2+thickness*2]){
    cube([10,hole_width,hole_height],center=true);
  }
}

// Attaches
translate([-length/2+distance_wall_left_attach_1,width/2-distance_wall_top_attach_1,0]){
  cylinder(r = board_hole_radius, h = attaches_height, $fn=20, center = true);
}

translate([length/2-distance_wall_right_attach_2,-width/2+distance_wall_bottom_attach_2,0]){
  cylinder(r = board_hole_radius, h = attaches_height, $fn=20, center = true);
}


