#include "Copter.h"
#include <string>
#include <vector>

#define CSV_BUFFER_SIZE 64
/*
 * Init and run calls for stabilize flight mode
 */

// stabilize_run - runs the main stabilize controller
// called at 400Hz
bool Copter::ModeHoverSlam::init(bool ignore_checks)
{
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

    std::vector<float> vector_thrust;
    std::vector<float> vector_pitch;
    std::vector<float> vector_roll;

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
                    col_num++;

                    memset(num, 0, sizeof(num));
                    memcpy(num, line + num_index, num_size);
                    num_index = j + 1;

                    switch (col_num)
                    {
                    case 0:
                        vector_thrust.push_back(atof(num));
                        break;
                    case 1:
                        vector_pitch.push_back(atof(num));
                        break;
                    case 2:
                        vector_roll.push_back(atof(num));
                        break;

                    default:
                        break;
                    }
                    

                    //hal.console->printf("Num: %.2f", atof(num));
                }

            }
        }
    }

    return true;
}

void Copter::ModeHoverSlam::run()
{

    // call attitude controller
    attitude_control->input_euler_angle_roll_pitch_yaw(1500.0f, 0.0f, 0.0f, false);

    // output throttle
    attitude_control->set_throttle_out(0.5f,
                                       true,
                                       g.throttle_filt);
}
