// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from mnist_msgs:srv/Mnist.idl
// generated code does not contain a copyright notice
#include "mnist_msgs/srv/mnist__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Include directives for member types
// Member `rawdigit`
#include "sensor_msgs/msg/image__functions.h"

bool
mnist_msgs__srv__Mnist_Request__init(mnist_msgs__srv__Mnist_Request * msg)
{
  if (!msg) {
    return false;
  }
  // rawdigit
  if (!sensor_msgs__msg__Image__init(&msg->rawdigit)) {
    mnist_msgs__srv__Mnist_Request__fini(msg);
    return false;
  }
  return true;
}

void
mnist_msgs__srv__Mnist_Request__fini(mnist_msgs__srv__Mnist_Request * msg)
{
  if (!msg) {
    return;
  }
  // rawdigit
  sensor_msgs__msg__Image__fini(&msg->rawdigit);
}

mnist_msgs__srv__Mnist_Request *
mnist_msgs__srv__Mnist_Request__create()
{
  mnist_msgs__srv__Mnist_Request * msg = (mnist_msgs__srv__Mnist_Request *)malloc(sizeof(mnist_msgs__srv__Mnist_Request));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(mnist_msgs__srv__Mnist_Request));
  bool success = mnist_msgs__srv__Mnist_Request__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
mnist_msgs__srv__Mnist_Request__destroy(mnist_msgs__srv__Mnist_Request * msg)
{
  if (msg) {
    mnist_msgs__srv__Mnist_Request__fini(msg);
  }
  free(msg);
}


bool
mnist_msgs__srv__Mnist_Request__Sequence__init(mnist_msgs__srv__Mnist_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  mnist_msgs__srv__Mnist_Request * data = NULL;
  if (size) {
    data = (mnist_msgs__srv__Mnist_Request *)calloc(size, sizeof(mnist_msgs__srv__Mnist_Request));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = mnist_msgs__srv__Mnist_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        mnist_msgs__srv__Mnist_Request__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
mnist_msgs__srv__Mnist_Request__Sequence__fini(mnist_msgs__srv__Mnist_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      mnist_msgs__srv__Mnist_Request__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

mnist_msgs__srv__Mnist_Request__Sequence *
mnist_msgs__srv__Mnist_Request__Sequence__create(size_t size)
{
  mnist_msgs__srv__Mnist_Request__Sequence * array = (mnist_msgs__srv__Mnist_Request__Sequence *)malloc(sizeof(mnist_msgs__srv__Mnist_Request__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = mnist_msgs__srv__Mnist_Request__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
mnist_msgs__srv__Mnist_Request__Sequence__destroy(mnist_msgs__srv__Mnist_Request__Sequence * array)
{
  if (array) {
    mnist_msgs__srv__Mnist_Request__Sequence__fini(array);
  }
  free(array);
}


bool
mnist_msgs__srv__Mnist_Response__init(mnist_msgs__srv__Mnist_Response * msg)
{
  if (!msg) {
    return false;
  }
  // digit
  return true;
}

void
mnist_msgs__srv__Mnist_Response__fini(mnist_msgs__srv__Mnist_Response * msg)
{
  if (!msg) {
    return;
  }
  // digit
}

mnist_msgs__srv__Mnist_Response *
mnist_msgs__srv__Mnist_Response__create()
{
  mnist_msgs__srv__Mnist_Response * msg = (mnist_msgs__srv__Mnist_Response *)malloc(sizeof(mnist_msgs__srv__Mnist_Response));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(mnist_msgs__srv__Mnist_Response));
  bool success = mnist_msgs__srv__Mnist_Response__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
mnist_msgs__srv__Mnist_Response__destroy(mnist_msgs__srv__Mnist_Response * msg)
{
  if (msg) {
    mnist_msgs__srv__Mnist_Response__fini(msg);
  }
  free(msg);
}


bool
mnist_msgs__srv__Mnist_Response__Sequence__init(mnist_msgs__srv__Mnist_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  mnist_msgs__srv__Mnist_Response * data = NULL;
  if (size) {
    data = (mnist_msgs__srv__Mnist_Response *)calloc(size, sizeof(mnist_msgs__srv__Mnist_Response));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = mnist_msgs__srv__Mnist_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        mnist_msgs__srv__Mnist_Response__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
mnist_msgs__srv__Mnist_Response__Sequence__fini(mnist_msgs__srv__Mnist_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      mnist_msgs__srv__Mnist_Response__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

mnist_msgs__srv__Mnist_Response__Sequence *
mnist_msgs__srv__Mnist_Response__Sequence__create(size_t size)
{
  mnist_msgs__srv__Mnist_Response__Sequence * array = (mnist_msgs__srv__Mnist_Response__Sequence *)malloc(sizeof(mnist_msgs__srv__Mnist_Response__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = mnist_msgs__srv__Mnist_Response__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
mnist_msgs__srv__Mnist_Response__Sequence__destroy(mnist_msgs__srv__Mnist_Response__Sequence * array)
{
  if (array) {
    mnist_msgs__srv__Mnist_Response__Sequence__fini(array);
  }
  free(array);
}
