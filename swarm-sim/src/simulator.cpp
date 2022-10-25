#include <cstdio>

#include "Boids.h"
#include "PropertyPanel.h"
#include "SwarmSimulator.h"

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  printf("hello world swarm-sim package\n");
  // Create robot instances
  std::list<SwarmSim::Robot *> robots;
  for (size_t i = 0; i < 250; i++)
  {
    robots.emplace_back(new SwarmSim::Boids());
  }

  // Custom property menu
  std::list<SwarmSim::Widget *> widgetList;
  SwarmSim::Widget *menu = new SwarmSim::PropertyPanel();
  widgetList.push_back(menu);

  SwarmSim::SwarmSimulator sim(false, robots, widgetList);

  sim.loop();
  return 0;
}