import rclpy
from rclpy.node import Node
from rclpy.client import Client
from rclpy.qos import QoSDurabilityPolicy, QoSHistoryPolicy, QoSReliabilityPolicy
from rclpy.qos import QoSProfile

import random
import numpy as np
import matplotlib.pyplot as plt
import time
import struct
import random

from tensorflow import keras
from tensorflow.keras.datasets import mnist
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout, Flatten
from tensorflow.keras.layers import Conv2D, MaxPooling2D
from tensorflow.keras import backend as K
from keras.models import model_from_json
import os

from cv_bridge import CvBridge
from sensor_msgs.msg import Image
import cv2
from cv_bridge import CvBridge

from mnist_msgs.srv import Mnist

class MinimalClientAsync(Node):

    def __init__(self):
        super().__init__('mnist_service_client')
        self.cli = self.create_client(Mnist, 'Mnist')
        while not self.cli.wait_for_service(timeout_sec=4.0):
            self.get_logger().info('service not available, waiting again...')
        self.req = Mnist.Request()
        self.bridge = CvBridge()
        self.tstart = 0
        self.tend = 0

        self.img_rows, self.img_cols = 28, 28
        (self.x_train, self.y_train), (self.x_test, self.y_test) = mnist.load_data()




    def send_request(self):

        if K.image_data_format() == 'channels_first':
            self.x_test = self.x_test.reshape(self.x_test.shape[0], 1, self.img_rows, self.img_cols)
        else:
            self.x_test = self.x_test.reshape(self.x_test.shape[0], self.img_rows, self.img_cols , 1)

        self.req.rawdigit = self.bridge.cv2_to_imgmsg(np.array(self.x_test[random.randint(0,100)]), "mono8")

        self.tstart = time.time()
        self.future = self.cli.call_async(self.req)

            
def main(args=None):
    rclpy.init(args=args)

    minimal_client = MinimalClientAsync()


    for i in range(0,1000):

        minimal_client.send_request()

        while rclpy.ok():
            rclpy.spin_once(minimal_client)
            if minimal_client.future.done():
                try:
                    response = minimal_client.future.result()
                except Exception as e:
                    minimal_client.get_logger().info(
                        'Service call failed %r' % (e,))
                else:
                    minimal_client.tend = time.time()
                    print('%f' % (minimal_client.tend - minimal_client.tstart))
                break

        time.sleep(0.1)                    

    minimal_client.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
