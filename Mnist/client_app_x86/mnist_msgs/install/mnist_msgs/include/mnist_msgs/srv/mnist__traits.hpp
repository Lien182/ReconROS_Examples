// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from mnist_msgs:srv/Mnist.idl
// generated code does not contain a copyright notice

#ifndef MNIST_MSGS__SRV__MNIST__TRAITS_HPP_
#define MNIST_MSGS__SRV__MNIST__TRAITS_HPP_

#include "mnist_msgs/srv/mnist__struct.hpp"
#include <rosidl_generator_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

// Include directives for member types
// Member 'rawdigit'
#include "sensor_msgs/msg/image__traits.hpp"

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<mnist_msgs::srv::Mnist_Request>()
{
  return "mnist_msgs::srv::Mnist_Request";
}

template<>
struct has_fixed_size<mnist_msgs::srv::Mnist_Request>
  : std::integral_constant<bool, has_fixed_size<sensor_msgs::msg::Image>::value> {};

template<>
struct has_bounded_size<mnist_msgs::srv::Mnist_Request>
  : std::integral_constant<bool, has_bounded_size<sensor_msgs::msg::Image>::value> {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<mnist_msgs::srv::Mnist_Response>()
{
  return "mnist_msgs::srv::Mnist_Response";
}

template<>
struct has_fixed_size<mnist_msgs::srv::Mnist_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<mnist_msgs::srv::Mnist_Response>
  : std::integral_constant<bool, true> {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<mnist_msgs::srv::Mnist>()
{
  return "mnist_msgs::srv::Mnist";
}

template<>
struct has_fixed_size<mnist_msgs::srv::Mnist>
  : std::integral_constant<
    bool,
    has_fixed_size<mnist_msgs::srv::Mnist_Request>::value &&
    has_fixed_size<mnist_msgs::srv::Mnist_Response>::value
  >
{
};

template<>
struct has_bounded_size<mnist_msgs::srv::Mnist>
  : std::integral_constant<
    bool,
    has_bounded_size<mnist_msgs::srv::Mnist_Request>::value &&
    has_bounded_size<mnist_msgs::srv::Mnist_Response>::value
  >
{
};

}  // namespace rosidl_generator_traits

#endif  // MNIST_MSGS__SRV__MNIST__TRAITS_HPP_
