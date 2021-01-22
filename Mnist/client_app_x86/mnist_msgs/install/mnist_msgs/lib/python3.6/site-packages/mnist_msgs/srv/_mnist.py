# generated from rosidl_generator_py/resource/_idl.py.em
# with input from mnist_msgs:srv/Mnist.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Mnist_Request(type):
    """Metaclass of message 'Mnist_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('mnist_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'mnist_msgs.srv.Mnist_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__mnist__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__mnist__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__mnist__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__mnist__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__mnist__request

            from sensor_msgs.msg import Image
            if Image.__class__._TYPE_SUPPORT is None:
                Image.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Mnist_Request(metaclass=Metaclass_Mnist_Request):
    """Message class 'Mnist_Request'."""

    __slots__ = [
        '_rawdigit',
    ]

    _fields_and_field_types = {
        'rawdigit': 'sensor_msgs/Image',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['sensor_msgs', 'msg'], 'Image'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from sensor_msgs.msg import Image
        self.rawdigit = kwargs.get('rawdigit', Image())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.rawdigit != other.rawdigit:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def rawdigit(self):
        """Message field 'rawdigit'."""
        return self._rawdigit

    @rawdigit.setter
    def rawdigit(self, value):
        if __debug__:
            from sensor_msgs.msg import Image
            assert \
                isinstance(value, Image), \
                "The 'rawdigit' field must be a sub message of type 'Image'"
        self._rawdigit = value


# Import statements for member types

# already imported above
# import rosidl_parser.definition


class Metaclass_Mnist_Response(type):
    """Metaclass of message 'Mnist_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('mnist_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'mnist_msgs.srv.Mnist_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__mnist__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__mnist__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__mnist__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__mnist__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__mnist__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Mnist_Response(metaclass=Metaclass_Mnist_Response):
    """Message class 'Mnist_Response'."""

    __slots__ = [
        '_digit',
    ]

    _fields_and_field_types = {
        'digit': 'uint32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.digit = kwargs.get('digit', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.digit != other.digit:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def digit(self):
        """Message field 'digit'."""
        return self._digit

    @digit.setter
    def digit(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'digit' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'digit' field must be an unsigned integer in [0, 4294967295]"
        self._digit = value


class Metaclass_Mnist(type):
    """Metaclass of service 'Mnist'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('mnist_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'mnist_msgs.srv.Mnist')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__mnist

            from mnist_msgs.srv import _mnist
            if _mnist.Metaclass_Mnist_Request._TYPE_SUPPORT is None:
                _mnist.Metaclass_Mnist_Request.__import_type_support__()
            if _mnist.Metaclass_Mnist_Response._TYPE_SUPPORT is None:
                _mnist.Metaclass_Mnist_Response.__import_type_support__()


class Mnist(metaclass=Metaclass_Mnist):
    from mnist_msgs.srv._mnist import Mnist_Request as Request
    from mnist_msgs.srv._mnist import Mnist_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
