#ifndef BOIDS_H
#define BOIDS_H
#include "Robot.h"
#pragma once

class RosRobot : public SwarmSim::Robot
{
public:
    RosRobot(std::string id, glm::dvec3 pos)
    {
        setPosition(pos);
        this->uuid = id;
    };

    ~RosRobot(){};

    void sense(std::shared_ptr<SwarmSim::EnvironmentState>) override{};
    void act() override{};
    void reset() override{};

private:
};

#endif