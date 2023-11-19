// This block ensures that the content of this header file is included only once
#ifndef HW_INTERFACE_HPP
#define HW_INTERFACE_HPP

// Standard ROS hardware interface includes
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/robot_hw.h>
#include <controller_manager/controller_manager.h>
#include <ros/ros.h>

// Standard C++ includes
#include <chrono>
#include <thread>
#include <iostream>

// Boost assign library for simplified list initialization
#include <boost/assign/list_of.hpp>

#define HW_IF_UPDATE_FREQ 50

#define MU 1
#define PI 3.14159
#define RES 1150.0 //Convertions constant
#define ENC_RES 2 * PI / RES

// Custom message includes
#include "robot_control/encoder_data.h"
#include "robot_control/velocity_data.h" 


enum MotorPosition
{
    LEFT = 0,
    RIGHT = 1
};

// Define the hardware interface class
class RobotHWInterface : public hardware_interface::RobotHW
{
public:
    // Constructor that takes a NodeHandle as a parameter
    RobotHWInterface(ros::NodeHandle &nh);

    // Destructor
    virtual ~RobotHWInterface() {};

    // Initialization method
    void init();

    // Callback method for processing encoder data
    void encoderCallback(const robot_control::encoder_data::ConstPtr &msg);

protected:
    // Joint state and velocity interfaces for hardware communication
    hardware_interface::JointStateInterface joint_state_interface_;
    hardware_interface::VelocityJointInterface velocity_joint_interface_;

    // Struct to represent a joint with position, velocity, effort, and velocity command
    struct Joint
    {
        double position;
        double velocity;
        double effort;
        double velocity_command;
        Joint() : position(0), velocity(0), effort(0), velocity_command(0) {}
    };

    // Array of Joint structures representing the robot's joints
    Joint joints_[2] = {
        Joint(), // Joint for the left wheel
        Joint()  // Joint for the right wheel
    };

    // Array of joint names
    ros::V_string joint_names = boost::assign::list_of("wheel_left_joint")("wheel_right_joint");

    // ROS NodeHandle for this class
    ros::NodeHandle nh_;

    // ROS Subscriber for receiving encoder data
    ros::Subscriber subscriber_;

    // ROS Publisher for sending velocity commands
    ros::Publisher publisher_;

    // ROS Duration for tracking elapsed time
    ros::Duration elapsed_time_;

    // ROS Time variables for tracking current and last real time
    ros::Time current_real;
    ros::Time last_real;

    // Desired loop frequency for hardware interface updates
    double loop_hz_ = HW_IF_UPDATE_FREQ;

    // Controller manager for handling controllers
    boost::shared_ptr<controller_manager::ControllerManager> controller_manager_;

};

#endif // HW_INTERFACE_HPP
