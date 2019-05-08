#include "Copter.h"

/*
 * Init and run calls for stabilize flight mode
 */

// stabilize_run - runs the main stabilize controller
// called at 400Hz
bool Copter::ModeHoverSlam::init(bool ignore_checks)
{

    return true;
}

void Copter::ModeHoverSlam::run()
{

    // call attitude controller
    attitude_control->input_euler_angle_roll_pitch_yaw(1500.0f, 0.0f, 0.0f,false);

    // output throttle
    attitude_control->set_throttle_out(0.5f,
                                       true,
                                       g.throttle_filt);
}
