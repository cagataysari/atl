module mounting_holes(
    num_holes,
    hole_location_radius,
    hole_diam,
    thickness
)
{
    $fn = 20;
    for(i = [1 : num_holes]) {
        translate([
            hole_location_radius * cos(i * (360 / num_holes)),
            hole_location_radius * sin(i * (360 / num_holes)),
            0
        ])
        cylinder(r = hole_diam / 2.0, h = thickness);
    }
};

module wire_header_cutout()
{
 // TODO
}

module central_hole_cutout(diam, thickness)
{
    $fn = 20;
    cylinder(r = diam /2, h = thickness);
}

module mounting_surface(diam, thickness)
{
    $fn = 50;
    cylinder(r = diam / 2, h = thickness);
}

module mounting_plate(
    plate_diam,
    thickness,
    hole_location_radius,
    hole_diam,
    num_holes,
    central_hole_diam,
    arm_width,
    arm_length
)
{
    r = plate_diam / 2;
    sagitta = r - sqrt(pow(r, 2) - pow(arm_width /2, 2));
    difference()  {
        union() {
            mounting_surface(plate_diam, thickness);
            translate([r - sagitta, -arm_width/2, 0])
            cube([sagitta + arm_length, arm_width, thickness]);
        }
        mounting_holes(num_holes, hole_location_radius, hole_diam, thickness);
        central_hole_cutout(central_hole_diam, thickness);
    }
}

module roll_bracket()
{
    back_plate_diam = 34;
    front_plate_diam = 32;
    thickness = 2.5;
    hole_diam = 1.2;
    num_holes = 3.0;
    arm_width = 20;
    roll_motor_mount_holes_radius = 3;
    roll_motor_mount_central_hole = 2.5;
    roll_motor_arm_length = 10.0 + 15 + thickness;
    pitch_motor_mount_holes_radius = 13;
    pitch_motor_mount_central_hole = 2.0;
    pitch_motor_arm_length = 18;

    union() {
        //roll motor mount
        mounting_plate(
            back_plate_diam,
            thickness,
            roll_motor_mount_holes_radius,
            hole_diam,
            num_holes,
            roll_motor_mount_central_hole,
            arm_width,
            roll_motor_arm_length
        );
        translate([
            roll_motor_arm_length + back_plate_diam / 2,
            0,
            pitch_motor_arm_length + front_plate_diam / 2
        ])
        rotate([0, 90, 180])
        mounting_plate(
            front_plate_diam,
            thickness,
            pitch_motor_mount_holes_radius,
            hole_diam,
            num_holes,
            pitch_motor_mount_central_hole,
            arm_width,
            pitch_motor_arm_length
        );
   }
}


// run
roll_bracket();