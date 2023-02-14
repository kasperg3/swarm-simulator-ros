#include <cstdio>

#include "Robot.h"
#include "PropertyPanel.h"
#include "SwarmSimulator.h"
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <mutex>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using std::placeholders::_1;
using namespace std::chrono_literals;
class SimulatorNode : public rclcpp::Node
{
public:
    SimulatorNode()
        : Node("swarm_simulator"), count_(0)
    {
        publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
        timer_ = this->create_wall_timer(500ms, std::bind(&SimulatorNode::timer_callback, this));
        simTimer = this->create_wall_timer(100ms, std::bind(&SimulatorNode::simLoop, this));

        robot_state_subscriber = this->create_subscription<std_msgs::msg::String>(
            "topic", 10, std::bind(&SimulatorNode::topic_callback, this, _1));

        // Create robot instances
        std::list<SwarmSim::Robot *> robots;

        // Custom property menu
        std::list<SwarmSim::Widget *> widgetList;
        SwarmSim::Widget *menu = new SwarmSim::PropertyPanel();
        widgetList.push_back(menu);
        simPtr = std::make_shared<SwarmSim::SwarmSimulator>(false, robots, widgetList);
    }

private:
    void timer_callback()
    {
        // TODO Publish simulator state - Maybe?
        auto message = std_msgs::msg::String();
        publisher_->publish(message);
    }

    // TODO Create a subscriber to update the simulator state
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
    {
        // If a new agent is added, then add it to the simulation

        // Else update the robot state vector
        RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
    }

    void simLoop()
    {
        mtx.lock();
        simPtr->loopOnce();
        mtx.unlock();
    }
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr robot_state_subscriber;

    std::mutex mtx;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::TimerBase::SharedPtr simTimer;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    std::shared_ptr<SwarmSim::SwarmSimulator> simPtr;
    size_t count_;
};

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SimulatorNode>());
    rclcpp::shutdown();
    return 0;
}