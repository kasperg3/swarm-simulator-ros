#include <cstdio>

#include "Robot.h"
#include "PropertyPanel.h"
#include "SwarmSimulator.h"
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <mutex>
#include "Random.h"

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "swarm_sim_interfaces/msg/robot_state.hpp"
#include "glm/glm.hpp"
#include "swarm_sim/RosRobot.h"

using std::placeholders::_1;
using namespace std::chrono_literals;
class SimulatorNode : public rclcpp::Node
{
public:
    SimulatorNode()
        : Node("simulator"), count_(0)
    {
        publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
        timer_ = this->create_wall_timer(500ms, std::bind(&SimulatorNode::timer_callback, this));
        // 20ms is 50 update per second / 50fps sim
        simTimer = this->create_wall_timer(16ms, std::bind(&SimulatorNode::simLoop, this));

        robot_state_subscriber = this->create_subscription<swarm_sim_interfaces::msg::RobotState>("robot_state", 10, std::bind(&SimulatorNode::topic_callback, this, _1));

        // Custom property menu
        std::list<SwarmSim::Widget *> widgetList;
        // TODO create your own propertypanel, the original might be a good example to start with
        // SwarmSim::Widget *menu = new SwarmSim::PropertyPanel();
        // widgetList.push_back(menu);
        simPtr = std::make_shared<SwarmSim::SwarmSimulator>(false, robots, widgetList);
    }

private:
    void timer_callback()
    {
        // TODO update the sim state with the local copy of robot states
        auto message = std_msgs::msg::String();
        publisher_->publish(message);
    }

    void topic_callback(const swarm_sim_interfaces::msg::RobotState::SharedPtr msg)
    {
        std::string robotId = msg->id;
        glm::dvec3 pos(msg->position.x, msg->position.z, msg->position.y);

        // If a new agent is added, then add it to the simulation
        if (simPtr->hasRobot(robotId))
        {
            // Update the local robot position
            RCLCPP_INFO_STREAM(this->get_logger(), "Setting robot " << msg->id << " position to: " << pos.x << ", " << pos.y << ", " << pos.z);
            simPtr->setRobotPosition(robotId, pos);
        }
        else
        {
            // add the robot to the sim
            SwarmSim::Robot *robot = new RosRobot(msg->id, pos);
            simPtr->addRobot(robot);
            RCLCPP_INFO_STREAM(this->get_logger(), "Added new robot with id: " << msg->id);
        }
    }

    void simLoop()
    {
        simPtr->loopOnce();
    }
    rclcpp::Subscription<swarm_sim_interfaces::msg::RobotState>::SharedPtr robot_state_subscriber;
    std::map<std::string, SwarmSim::Robot *> robots;
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