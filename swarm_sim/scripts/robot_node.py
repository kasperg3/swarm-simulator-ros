#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
import uuid
from std_msgs.msg import String
from swarm_sim_interfaces.msg import RobotState
from geometry_msgs.msg import Point32


class Robot(Node):
    def __init__(self):
        super().__init__("robot")
        # make a UUID based on the host ID and current time
        self.id = str(uuid.uuid1())
        # TODO
        # define a map of robots and store it locally
        # publish this robots current state on topic robot_state
        self.publisher_ = self.create_publisher(RobotState, "robot_state", 10)
        timer_period = 0.02  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)

        self.subscription = self.create_subscription(
            RobotState, "robot_state", self.listener_callback, 10
        )
        self.subscription  # prevent unused variable warning

    def timer_callback(self):
        msg = RobotState()
        #         geometry_msgs/Point32[] position
        # string id
        msg.id = self.id
        msg.position = Point32(x=0.0, y=0.0, z=0.0)
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
