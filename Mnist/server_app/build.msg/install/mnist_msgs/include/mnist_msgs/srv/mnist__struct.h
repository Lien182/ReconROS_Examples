// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from mnist_msgs:srv/Mnist.idl
// generated code does not contain a copyright notice

#ifndef MNIST_MSGS__SRV__MNIST__STRUCT_H_
#define MNIST_MSGS__SRV__MNIST__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'rawdigit'
#include "sensor_msgs/msg/image__struct.h"

// Struct defined in srv/Mnist in the package mnist_msgs.
typedef struct mnist_msgs__srv__Mnist_Request
{
  sensor_msgs__msg__Image rawdigit;
} mnist_msgs__srv__Mnist_Request;

// Struct for a sequence of mnist_msgs__srv__Mnist_Request.
typedef struct mnist_msgs__srv__Mnist_Request__Sequence
{
  mnist_msgs__srv__Mnist_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mnist_msgs__srv__Mnist_Request__Sequence;


// Constants defined in the message

// Struct defined in srv/Mnist in the package mnist_msgs.
typedef struct mnist_msgs__srv__Mnist_Response
{
  uint32_t digit;
} mnist_msgs__srv__Mnist_Response;

// Struct for a sequence of mnist_msgs__srv__Mnist_Response.
typedef struct mnist_msgs__srv__Mnist_Response__Sequence
{
  mnist_msgs__srv__Mnist_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mnist_msgs__srv__Mnist_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MNIST_MSGS__SRV__MNIST__STRUCT_H_
