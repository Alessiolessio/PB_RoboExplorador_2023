#include "robot_hw_interface.hpp"

RobotHWInterface::RobotHWInterface(ros::NodeHandle &nh) : nh_(nh)
{
    init();
    controller_manager_.reset(new controller_manager::ControllerManager(this, nh_));
    controller_manager_->update(ros::Time::now(), elapsed_time_);
}

void RobotHWInterface::init()
{

    publisher_ = nh_.advertise<robot_control::velocity_data>("velocity_command", 10);
    subscriber_ = nh_.subscribe("/encoder_data", 1000, &RobotHWInterface::encoderCallback, this);

    current_real = ros::Time::now();
    last_real = ros::Time::now();

    // Left JointStateInterface 
    hardware_interface::JointStateHandle jointStateHandleLeft(joint_names[0], &joints_[0].position, &joints_[0].velocity, &joints_[0].effort);
    joint_state_interface_.registerHandle(jointStateHandleLeft);

    // Right JointStateInterface 
    hardware_interface::JointStateHandle jointStateHandleRight(joint_names[1], &joints_[1].position, &joints_[1].velocity, &joints_[1].effort);
    joint_state_interface_.registerHandle(jointStateHandleRight);

    // Left JointVelocityInterface
    hardware_interface::JointHandle jointVelocityHandleLeft(jointStateHandleLeft, &joints_[0].velocity_command);
    velocity_joint_interface_.registerHandle(jointVelocityHandleLeft);

    // Right JointVelocityInterface
    hardware_interface::JointHandle jointVelocityHandleRight(jointStateHandleRight, &joints_[1].velocity_command);
    velocity_joint_interface_.registerHandle(jointVelocityHandleRight);

    registerInterface(&joint_state_interface_);
    registerInterface(&velocity_joint_interface_);

}

void RobotHWInterface::encoderCallback(const robot_control::encoder_data::ConstPtr &msg)
{
    double encoder_data[2];
    
    encoder_data[LEFT] = msg->left_encoder_data;
    encoder_data[RIGHT] = msg->right_encoder_data;

    //Encoders data convertions into angular velocity values
        for (uint8_t i = 0; i < 2; i++)
    {
        encoder_data[i] *= (ENC_RES * MU);
    }
    
    std::cout << "Right: " << encoder_data[RIGHT] << std::endl;
    std::cout << "Left: " << encoder_data[LEFT] << std::endl;

    //Updates joints position
    joints_[LEFT].position += (encoder_data[LEFT]/2);
    joints_[RIGHT].position += (encoder_data[RIGHT]/2);

    std::cout << "Right joint position: " << joints_[LEFT].position  << std::endl;
    std::cout << "Left joint position: " << joints_[RIGHT].position << std::endl;

    //Updates ROS time
    current_real = ros::Time::now();
    elapsed_time_ = ros::Duration(current_real - last_real);

    //Updates joints velocity
    joints_[LEFT].velocity = encoder_data[LEFT] / elapsed_time_.toSec();
    joints_[RIGHT].velocity  = encoder_data[RIGHT] / elapsed_time_.toSec();

    //Publishes the velocity values
    robot_control::velocity_data velocity_msg;

    velocity_msg.left_wheel_velocity = joints_[LEFT].velocity_command;
    velocity_msg.right_wheel_velocity = joints_[RIGHT].velocity_command;

    publisher_.publish(velocity_msg);

    last_real = ros::Time::now();

    controller_manager_->update(ros::Time::now(), elapsed_time_);

}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "robot_hw_interface_node");
    ros::NodeHandle nh;

    ros::MultiThreadedSpinner spinner(4);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    RobotHWInterface robot(nh);

    spinner.spin();

    return 0;
}