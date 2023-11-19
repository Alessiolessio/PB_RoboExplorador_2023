// Generated by gencpp from file robot_control/velocity_data.msg
// DO NOT EDIT!


#ifndef ROBOT_CONTROL_MESSAGE_VELOCITY_DATA_H
#define ROBOT_CONTROL_MESSAGE_VELOCITY_DATA_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace robot_control
{
template <class ContainerAllocator>
struct velocity_data_
{
  typedef velocity_data_<ContainerAllocator> Type;

  velocity_data_()
    : left_wheel_velocity(0)
    , right_wheel_velocity(0)  {
    }
  velocity_data_(const ContainerAllocator& _alloc)
    : left_wheel_velocity(0)
    , right_wheel_velocity(0)  {
  (void)_alloc;
    }



   typedef int64_t _left_wheel_velocity_type;
  _left_wheel_velocity_type left_wheel_velocity;

   typedef int64_t _right_wheel_velocity_type;
  _right_wheel_velocity_type right_wheel_velocity;





  typedef boost::shared_ptr< ::robot_control::velocity_data_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::robot_control::velocity_data_<ContainerAllocator> const> ConstPtr;

}; // struct velocity_data_

typedef ::robot_control::velocity_data_<std::allocator<void> > velocity_data;

typedef boost::shared_ptr< ::robot_control::velocity_data > velocity_dataPtr;
typedef boost::shared_ptr< ::robot_control::velocity_data const> velocity_dataConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::robot_control::velocity_data_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::robot_control::velocity_data_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::robot_control::velocity_data_<ContainerAllocator1> & lhs, const ::robot_control::velocity_data_<ContainerAllocator2> & rhs)
{
  return lhs.left_wheel_velocity == rhs.left_wheel_velocity &&
    lhs.right_wheel_velocity == rhs.right_wheel_velocity;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::robot_control::velocity_data_<ContainerAllocator1> & lhs, const ::robot_control::velocity_data_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace robot_control

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::robot_control::velocity_data_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::robot_control::velocity_data_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::robot_control::velocity_data_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::robot_control::velocity_data_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robot_control::velocity_data_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robot_control::velocity_data_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::robot_control::velocity_data_<ContainerAllocator> >
{
  static const char* value()
  {
    return "b981a5e037792122a688d27bcc9ce412";
  }

  static const char* value(const ::robot_control::velocity_data_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xb981a5e037792122ULL;
  static const uint64_t static_value2 = 0xa688d27bcc9ce412ULL;
};

template<class ContainerAllocator>
struct DataType< ::robot_control::velocity_data_<ContainerAllocator> >
{
  static const char* value()
  {
    return "robot_control/velocity_data";
  }

  static const char* value(const ::robot_control::velocity_data_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::robot_control::velocity_data_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# velocity_data.msg\n"
"\n"
"int64 left_wheel_velocity\n"
"int64 right_wheel_velocity\n"
;
  }

  static const char* value(const ::robot_control::velocity_data_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::robot_control::velocity_data_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.left_wheel_velocity);
      stream.next(m.right_wheel_velocity);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct velocity_data_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::robot_control::velocity_data_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::robot_control::velocity_data_<ContainerAllocator>& v)
  {
    s << indent << "left_wheel_velocity: ";
    Printer<int64_t>::stream(s, indent + "  ", v.left_wheel_velocity);
    s << indent << "right_wheel_velocity: ";
    Printer<int64_t>::stream(s, indent + "  ", v.right_wheel_velocity);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROBOT_CONTROL_MESSAGE_VELOCITY_DATA_H