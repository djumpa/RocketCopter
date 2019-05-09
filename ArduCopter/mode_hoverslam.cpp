#include "Copter.h"
#include <string>
#include <vector>

#define CSV_BUFFER_SIZE 64384
/*
 * Init and run calls for stabilize flight mode
 */

uint vector_num = 0;

std::vector<float> vector_thrust;
std::vector<float> vector_pitch;
std::vector<float> vector_roll;

// stabilize_run - runs the main stabilize controller
// called at 400Hz
bool Copter::ModeHoverSlam::init(bool ignore_checks)
{
    vector_thrust.clear();
    vector_pitch.clear();
    vector_roll.clear();

    vector_num = 0;

    const char *file_path = "hoverslam.csv";
    int fd;
    char buffer[CSV_BUFFER_SIZE];

    fd = ::open(file_path, O_RDONLY | O_CLOEXEC);

    if (fd == -1)
    {
        hal.console->printf("Opening file %s failed!\n", file_path);
        return false;
    }
    ssize_t ret = ::read(fd, buffer, sizeof(buffer));

    char line[CSV_BUFFER_SIZE];
    char num[CSV_BUFFER_SIZE];
    ssize_t line_index = 0;

    ssize_t total_elements = 0;

    for (ssize_t i = 0; i < ret; i++)
    {
        if (buffer[i] == '\n')
        {
            ssize_t line_size = i - line_index;
            memset(line, 0, sizeof(line));
            memcpy(line, buffer + line_index, line_size);
            line_index = i + 1;

            //hal.console->printf("Line: %s", line);

            ssize_t num_index = 0;
            ssize_t col_num = 0;

            for (ssize_t j = 0; j < line_size; j++)
            {
                if (line[j] == ',' || j == line_size - 1)
                {
                    ssize_t num_size;
                    if (line[j] == ',') {
                        num_size = j - num_index;
                    } else {
                        //in case of last number, we need to add extra char
                        num_size = j - num_index + 1;
                    }
                    

                    memset(num, 0, sizeof(num));
                    memcpy(num, line + num_index, num_size);
                    num_index = j + 1;

                    switch (col_num)
                    {
                    case 0:   
                        vector_thrust.push_back(atof(num));
                        break;
                    case 1:
                        total_elements++;
                        vector_pitch.push_back(atof(num)*100.0f);
                        break;
                    case 2:   
                        vector_roll.push_back(atof(num));
                        break;
                    default:
                        break;
                    }

                    col_num++;

                    //hal.console->printf("Thrust: %.2f", atof(num));
                }

            }
        }
    }

    //hal.console->printf("Vector size: %ld", total_elements);
    hal.console->printf("vector_thrust: %lu\n", vector_thrust.size());
    hal.console->printf("vector_pitch: %lu\n", vector_pitch.size());
    hal.console->printf("vector_roll: %lu\n", vector_roll.size());



    return true;
}

void Copter::ModeHoverSlam::run()
{
    if (vector_num<(uint)vector_thrust.size()) {
    // call attitude controller
    attitude_control->input_euler_angle_roll_pitch_yaw(0.0f,vector_pitch[vector_num], 0.0f, false);

    // output throttle
    attitude_control->set_throttle_out(vector_thrust[vector_num],
                                       true,
                                       g.throttle_filt);
    
    vector_num++;
    } else {
           // call attitude controller
    attitude_control->input_euler_angle_roll_pitch_yaw(0.0f, 0.0f, 0.0f, false);

    // output throttle
    attitude_control->set_throttle_out(0.0f,
                                       true,
                                       g.throttle_filt); 
    }
}
