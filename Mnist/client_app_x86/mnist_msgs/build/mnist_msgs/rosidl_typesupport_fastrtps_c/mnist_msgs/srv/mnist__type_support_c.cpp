// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from mnist_msgs:srv/Mnist.idl
// generated code does not contain a copyright notice
#include "mnist_msgs/srv/mnist__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "mnist_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "mnist_msgs/srv/mnist__struct.h"
#include "mnist_msgs/srv/mnist__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "sensor_msgs/msg/image__functions.h"  // rawdigit

// forward declare type support functions
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_mnist_msgs
size_t get_serialized_size_sensor_msgs__msg__Image(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_mnist_msgs
size_t max_serialized_size_sensor_msgs__msg__Image(
  bool & full_bounded,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_mnist_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, sensor_msgs, msg, Image)();


using _Mnist_Request__ros_msg_type = mnist_msgs__srv__Mnist_Request;

static bool _Mnist_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _Mnist_Request__ros_msg_type * ros_message = static_cast<const _Mnist_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: rawdigit
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, sensor_msgs, msg, Image
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->rawdigit, cdr))
    {
      return false;
    }
  }

  return true;
}

static bool _Mnist_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _Mnist_Request__ros_msg_type * ros_message = static_cast<_Mnist_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: rawdigit
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, sensor_msgs, msg, Image
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->rawdigit))
    {
      return false;
    }
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mnist_msgs
size_t get_serialized_size_mnist_msgs__srv__Mnist_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _Mnist_Request__ros_msg_type * ros_message = static_cast<const _Mnist_Request__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name rawdigit

  current_alignment += get_serialized_size_sensor_msgs__msg__Image(
    &(ros_message->rawdigit), current_alignment);

  return current_alignment - initial_alignment;
}

static uint32_t _Mnist_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_mnist_msgs__srv__Mnist_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mnist_msgs
size_t max_serialized_size_mnist_msgs__srv__Mnist_Request(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: rawdigit
  {
    size_t array_size = 1;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_sensor_msgs__msg__Image(
        full_bounded, current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}

static size_t _Mnist_Request__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_mnist_msgs__srv__Mnist_Request(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_Mnist_Request = {
  "mnist_msgs::srv",
  "Mnist_Request",
  _Mnist_Request__cdr_serialize,
  _Mnist_Request__cdr_deserialize,
  _Mnist_Request__get_serialized_size,
  _Mnist_Request__max_serialized_size
};

static rosidl_message_type_support_t _Mnist_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_Mnist_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, mnist_msgs, srv, Mnist_Request)() {
  return &_Mnist_Request__type_support;
}

#if defined(__cplusplus)
}
#endif

// already included above
// #include <cassert>
// already included above
// #include <limits>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "mnist_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
// already included above
// #include "mnist_msgs/srv/mnist__struct.h"
// already included above
// #include "mnist_msgs/srv/mnist__functions.h"
// already included above
// #include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _Mnist_Response__ros_msg_type = mnist_msgs__srv__Mnist_Response;

static bool _Mnist_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _Mnist_Response__ros_msg_type * ros_message = static_cast<const _Mnist_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: digit
  {
    cdr << ros_message->digit;
  }

  return true;
}

static bool _Mnist_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _Mnist_Response__ros_msg_type * ros_message = static_cast<_Mnist_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: digit
  {
    cdr >> ros_message->digit;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mnist_msgs
size_t get_serialized_size_mnist_msgs__srv__Mnist_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _Mnist_Response__ros_msg_type * ros_message = static_cast<const _Mnist_Response__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name digit
  {
    size_t item_size = sizeof(ros_message->digit);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _Mnist_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_mnist_msgs__srv__Mnist_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_mnist_msgs
size_t max_serialized_size_mnist_msgs__srv__Mnist_Response(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: digit
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  return current_alignment - initial_alignment;
}

static size_t _Mnist_Response__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_mnist_msgs__srv__Mnist_Response(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_Mnist_Response = {
  "mnist_msgs::srv",
  "Mnist_Response",
  _Mnist_Response__cdr_serialize,
  _Mnist_Response__cdr_deserialize,
  _Mnist_Response__get_serialized_size,
  _Mnist_Response__max_serialized_size
};

static rosidl_message_type_support_t _Mnist_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_Mnist_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, mnist_msgs, srv, Mnist_Response)() {
  return &_Mnist_Response__type_support;
}

#if defined(__cplusplus)
}
#endif

#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "mnist_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "mnist_msgs/srv/mnist.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t Mnist__callbacks = {
  "mnist_msgs::srv",
  "Mnist",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, mnist_msgs, srv, Mnist_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, mnist_msgs, srv, Mnist_Response)(),
};

static rosidl_service_type_support_t Mnist__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &Mnist__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, mnist_msgs, srv, Mnist)() {
  return &Mnist__handle;
}

#if defined(__cplusplus)
}
#endif
