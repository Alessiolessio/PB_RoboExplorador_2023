#include "robot_hw_interface.hpp"

RobotHWInterface::RobotHWInterface(ros::NodeHandle &nh) : nh_(nh)
{
    init();
    controller_manager_.reset(new controller_manager::ControllerManager(this, nh_));
    controller_manager_->update(ros::Time::now(), elapsed_time_);
}

void RobotHWInterface::init()
{

    publisher_ = nh_.advertise<robot_control::velocity_data>("/velocity_command", 10);
    subscriber_ = nh_.subscribe("/encoder_data", 10, &RobotHWInterface::encoderCallback, this);

    // Inicializa as interfaces de estado e comando para as rodas direita e esquerda
    hardware_interface::JointStateHandle state_handle_right_wheel("wheel_right_joint", &pos[0], &vel[0], &eff[0]);
    jnt_state_interface.registerHandle(state_handle_right_wheel);

    hardware_interface::JointHandle vel_handle_right_wheel(jnt_state_interface.getHandle("wheel_right_joint"), &cmd[0]);
    jnt_vel_interface.registerHandle(vel_handle_right_wheel);

    hardware_interface::JointStateHandle state_handle_left_wheel("wheel_left_joint", &pos[1], &vel[1], &eff[1]);
    jnt_state_interface.registerHandle(state_handle_left_wheel);

    hardware_interface::JointHandle vel_handle_left_wheel(jnt_state_interface.getHandle("wheel_left_joint"), &cmd[1]);
    jnt_vel_interface.registerHandle(vel_handle_left_wheel);

    registerInterface(&jnt_state_interface);
    registerInterface(&jnt_vel_interface);

    pos[0] = 0;
    pos[1] = 0;

    vel[0] = 0;
    vel[1] = 0;

    cmd[0] = 0;
    cmd[1] = 0;

    eff[0] = 0;
    eff[1] = 0;

    current_real = ros::Time::now();
    last_real = ros::Time::now();

}

void RobotHWInterface::read()
{
  // Atualiza os estados das juntas (posição, velocidade, esforço)

  // Atualiza o tempo
  current_real = ros::Time::now();
  elapsed_time_ = current_real - last_real;

  // Posição (radianos) = (Pulse count / Resolução)
  pos[0] += (right_encoder_data * elapsed_time_.toSec());
  pos[1] += (left_encoder_data * elapsed_time_.toSec());

  std::cout << "\nTime: " << elapsed_time_.toSec() << std::endl;

  std::cout << "\n[POSICAO]" << std::endl;
  std::cout << "Left: " << pos[0] << std::endl;
  std::cout << "Right: " << pos[1] << std::endl;

  // Velocidade = Posição / Tempo
  vel[0] = right_encoder_data;
  vel[1] = left_encoder_data;

  std::cout << "\n[VELOCIDADE]" << std::endl;
  std::cout << "Left Vel.: " << vel[0] << std::endl;
  std::cout << "Right Vel.: " << vel[1] << std::endl;
}

void RobotHWInterface::write()
{
  // Envia comandos de controle para as juntas

  // std::cout << "\n[COMMAND]" << std::endl;
  // std::cout << "Left: " << cmd[0] << std::endl;
  // std::cout << "Right: " << cmd[1] << std::endl;

  double right_wheel_command = cmd[0];
  double left_wheel_command = cmd[1];

  robot_control::velocity_data velocity_msg;

  velocity_msg.left_wheel_velocity = right_wheel_command;
  velocity_msg.right_wheel_velocity = left_wheel_command;

  publisher_.publish(velocity_msg);

  last_real = ros::Time::now();

  // Atualiza o controlador com o tempo atual e a diferença de tempo desde a última chamada
  controller_manager_->update(ros::Time::now(), elapsed_time_);
}

void RobotHWInterface::encoderCallback(const robot_control::encoder_data::ConstPtr &msg)
{
  left_encoder_data = msg->left_encoder_data * K; // Recebe o pulse count da roda esquerda
  right_encoder_data = msg->right_encoder_data * K; // Recebe o pulse count da roda direita

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "robot_hw_interface");
  ros::NodeHandle nh;

  RobotHWInterface robot_hw(nh);

  ros::Rate rate(10);
  ros::AsyncSpinner spinner(4);
  spinner.start();

  while (ros::ok())
  {
    robot_hw.read();
    robot_hw.write();
    rate.sleep();
  }

  return 0;
}
