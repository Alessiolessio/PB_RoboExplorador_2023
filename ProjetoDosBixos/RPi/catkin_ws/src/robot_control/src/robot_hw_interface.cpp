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
    hardware_interface::JointStateHandle jointStateHandle(joint_names[0], &joints_[0].position, &joints_[0].velocity, &joints_[0].effort);
    joint_state_interface_.registerHandle(jointStateHandle);

    // Right JointStateInterface 
    hardware_interface::JointStateHandle jointStateHandle(joint_names[1], &joints_[1].position, &joints_[1].velocity, &joints_[1].effort);
    joint_state_interface_.registerHandle(jointStateHandle);

    // Left JointVellocityInterface
    hardware_interface::JointHandle jointVelocityHandle(jointStateHandle, &joints_[0].velocity_command);
    velocity_joint_interface_.registerHandle(jointVelocityHandle);

    // Right JointVellocityInterface
    hardware_interface::JointHandle jointVelocityHandle(jointStateHandle, &joints_[1].velocity_command);
    velocity_joint_interface_.registerHandle(jointVelocityHandle);

    registerInterface(&joint_state_interface_);
    registerInterface(&velocity_joint_interface_);

}

void RobotHWInterface::encoderCallback(const robot_control::encoder_data::ConstPtr &msg)
{
    double encoder_data[2];
    
    encoder_data[LEFT] = msg->left_encoder_data;
    encoder_data[RIGHT] = msg->right_encoder_data;

    // Implementar
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "robot_hw_node");
    ros::NodeHandle nh;

    ros::MultiThreadedSpinner spinner(4);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    RobotHWInterface robot(nh);

    spinner.spin();

    return 0;
}
