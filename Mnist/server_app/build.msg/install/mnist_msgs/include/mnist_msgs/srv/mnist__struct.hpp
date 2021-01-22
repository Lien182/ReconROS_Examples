// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from mnist_msgs:srv/Mnist.idl
// generated code does not contain a copyright notice

#ifndef MNIST_MSGS__SRV__MNIST__STRUCT_HPP_
#define MNIST_MSGS__SRV__MNIST__STRUCT_HPP_

#include <rosidl_generator_cpp/bounded_vector.hpp>
#include <rosidl_generator_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

// Protect against ERROR being predefined on Windows, in case somebody defines a
// constant by that name.
#if defined(_WIN32)
  #if defined(ERROR)
    #undef ERROR
  #endif
  #if defined(NO_ERROR)
    #undef NO_ERROR
  #endif
#endif

// Include directives for member types
// Member 'rawdigit'
#include "sensor_msgs/msg/image__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__mnist_msgs__srv__Mnist_Request __attribute__((deprecated))
#else
# define DEPRECATED__mnist_msgs__srv__Mnist_Request __declspec(deprecated)
#endif

namespace mnist_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Mnist_Request_
{
  using Type = Mnist_Request_<ContainerAllocator>;

  explicit Mnist_Request_(rosidl_generator_cpp::MessageInitialization _init = rosidl_generator_cpp::MessageInitialization::ALL)
  : rawdigit(_init)
  {
    (void)_init;
  }

  explicit Mnist_Request_(const ContainerAllocator & _alloc, rosidl_generator_cpp::MessageInitialization _init = rosidl_generator_cpp::MessageInitialization::ALL)
  : rawdigit(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _rawdigit_type =
    sensor_msgs::msg::Image_<ContainerAllocator>;
  _rawdigit_type rawdigit;

  // setters for named parameter idiom
  Type & set__rawdigit(
    const sensor_msgs::msg::Image_<ContainerAllocator> & _arg)
  {
    this->rawdigit = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    mnist_msgs::srv::Mnist_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const mnist_msgs::srv::Mnist_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<mnist_msgs::srv::Mnist_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<mnist_msgs::srv::Mnist_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      mnist_msgs::srv::Mnist_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<mnist_msgs::srv::Mnist_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      mnist_msgs::srv::Mnist_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<mnist_msgs::srv::Mnist_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<mnist_msgs::srv::Mnist_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<mnist_msgs::srv::Mnist_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__mnist_msgs__srv__Mnist_Request
    std::shared_ptr<mnist_msgs::srv::Mnist_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__mnist_msgs__srv__Mnist_Request
    std::shared_ptr<mnist_msgs::srv::Mnist_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Mnist_Request_ & other) const
  {
    if (this->rawdigit != other.rawdigit) {
      return false;
    }
    return true;
  }
  bool operator!=(const Mnist_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Mnist_Request_

// alias to use template instance with default allocator
using Mnist_Request =
  mnist_msgs::srv::Mnist_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace mnist_msgs

// Protect against ERROR being predefined on Windows, in case somebody defines a
// constant by that name.
#if defined(_WIN32)
  #if defined(ERROR)
    #undef ERROR
  #endif
  #if defined(NO_ERROR)
    #undef NO_ERROR
  #endif
#endif

#ifndef _WIN32
# define DEPRECATED__mnist_msgs__srv__Mnist_Response __attribute__((deprecated))
#else
# define DEPRECATED__mnist_msgs__srv__Mnist_Response __declspec(deprecated)
#endif

namespace mnist_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Mnist_Response_
{
  using Type = Mnist_Response_<ContainerAllocator>;

  explicit Mnist_Response_(rosidl_generator_cpp::MessageInitialization _init = rosidl_generator_cpp::MessageInitialization::ALL)
  {
    if (rosidl_generator_cpp::MessageInitialization::ALL == _init ||
      rosidl_generator_cpp::MessageInitialization::ZERO == _init)
    {
      this->digit = 0ul;
    }
  }

  explicit Mnist_Response_(const ContainerAllocator & _alloc, rosidl_generator_cpp::MessageInitialization _init = rosidl_generator_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_generator_cpp::MessageInitialization::ALL == _init ||
      rosidl_generator_cpp::MessageInitialization::ZERO == _init)
    {
      this->digit = 0ul;
    }
  }

  // field types and members
  using _digit_type =
    uint32_t;
  _digit_type digit;

  // setters for named parameter idiom
  Type & set__digit(
    const uint32_t & _arg)
  {
    this->digit = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    mnist_msgs::srv::Mnist_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const mnist_msgs::srv::Mnist_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<mnist_msgs::srv::Mnist_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<mnist_msgs::srv::Mnist_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      mnist_msgs::srv::Mnist_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<mnist_msgs::srv::Mnist_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      mnist_msgs::srv::Mnist_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<mnist_msgs::srv::Mnist_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<mnist_msgs::srv::Mnist_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<mnist_msgs::srv::Mnist_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__mnist_msgs__srv__Mnist_Response
    std::shared_ptr<mnist_msgs::srv::Mnist_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__mnist_msgs__srv__Mnist_Response
    std::shared_ptr<mnist_msgs::srv::Mnist_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Mnist_Response_ & other) const
  {
    if (this->digit != other.digit) {
      return false;
    }
    return true;
  }
  bool operator!=(const Mnist_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Mnist_Response_

// alias to use template instance with default allocator
using Mnist_Response =
  mnist_msgs::srv::Mnist_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace mnist_msgs

namespace mnist_msgs
{

namespace srv
{

struct Mnist
{
  using Request = mnist_msgs::srv::Mnist_Request;
  using Response = mnist_msgs::srv::Mnist_Response;
};

}  // namespace srv

}  // namespace mnist_msgs

#endif  // MNIST_MSGS__SRV__MNIST__STRUCT_HPP_
