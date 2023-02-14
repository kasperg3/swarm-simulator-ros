#ifndef BOIDS_H
#define BOIDS_H
#include "Robot.h"
#pragma once

class RosRobot : public Robot
{
public:
    RosRobot(){};
    ~RosRobot(){};

    void sense(std::shared_ptr<SwarmSim::EnvironmentState>) override{
        // TODO set the

    };
    void act() override{};
    void draw() override{};
    void reset() override{};

private:
};
