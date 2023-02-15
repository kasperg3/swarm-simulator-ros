#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
import uuid
from std_msgs.msg import String
from swarm_sim_interfaces.msg import RobotState
from geometry_msgs.msg import Point32
import numpy as np


class Robot(Node):
    def __init__(self):
        super().__init__("robot")
        # make a UUID based on the host ID and current time
        self.id = str(uuid.uuid1())
        # TODO
        # define a map of robots and store it locally
        # publish this robots current state on topic robot_state
        self.publisher_ = self.create_publisher(RobotState, "robot_state", 100)
        self.timer_period = 0.05  # seconds
        self.timer = self.create_timer(self.timer_period, self.timer_callback)

        # self.subscription = self.create_subscription(
        #     RobotState, "robot_state", self.listener_callback, 10
        # )
        # self.subscription  # prevent unused variable warning

        # Control parameters
        self.theta = 0.0
        self.radius = 10.0
        self.omega = 0.5
        self.arming_state = 0.0

        self.counter = 0

    def timer_callback(self):
        msg = RobotState()
        #         geometry_msgs/Point32[] position
        # string id
        msg.id = self.id
        msg.position = Point32(x=0.0, y=0.0, z=0.0)

        msg.position.x = self.radius * np.cos(self.theta)
        msg.position.y = self.radius * np.sin(self.theta)
        msg.position.z = 5.0
        self.theta = self.theta + self.omega * self.timer_period

        self.publisher_.publish(msg)
        self.get_logger().info('Publishing: "%s"' % msg.id)

    def listener_callback(self, msg):
        self.get_logger().info('I heard: "%s"' % msg.id)


def main(args=None):
    rclpy.init(args=args)

    robotNode = Robot()

    rclpy.spin(robotNode)

    robotNode.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
