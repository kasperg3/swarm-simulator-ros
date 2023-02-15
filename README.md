<h1 align="center">Welcome to swarm-simulator-ros 👋</h1>
<p>
  <img alt="Version" src="https://img.shields.io/badge/version-0.0.1-blue.svg?cacheSeconds=2592000" />
  <a href=" " target="_blank">
    <img alt="Documentation" src="https://img.shields.io/badge/documentation-yes-brightgreen.svg" />
  </a>
  <a href="https://github.com/kefranabg/readme-md-generator/graphs/commit-activity" target="_blank">
    <img alt="Maintenance" src="https://img.shields.io/badge/Maintained%3F-yes-green.svg" />
  </a>
  <a href="https://github.com/kasperg3/swarm-simulator/blob/79fbc5c29036169ec56d4c07bd64e2df01b3bf38/LICENCE" target="_blank">
    <img alt="License: MIT" src="https://img.shields.io/github/license/kasperg3/swarm-simulator" />
  </a>
  <a href=" " target="_blank">
    <img alt="Build" src="https://github.com/kasperg3/swarm-simulator/actions/workflows/build.yml/badge.svg" />
  </a>
  
</p>

![Simple Boids example](https://github.com/kasperg3/swarm-simulator-ros/blob/main/assets/swarm-sim-ros.gif)

A simple implementation of a ros agent using https://github.com/kasperg3/swarm-simulator.git simulation.

## Install

### Dependencies

```sh
sudo apt update && sudo apt install build-essential libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev libglm-dev libglfw3-dev libgsl-dev

```


### Build

```
colcon build && source install/setup.zsh
```

## Run
To run the simulator, execute the following command:
```
ros2 run swarm_sim simulator
```

Followed by the creation of the agents: 
```
ros2 run swarm_sim robot_node.py
```


# Usage
For a detailed explanation on usage, please take a look at the [GETTING_STARTED.md](https://github.com/kasperg3/swarm-simulator/blob/main/getting_started.md) file or check out the writeup on my site: https://blog.grontved.dk/blog/swarm-simulator/ 

# Author

👤 **Kasper Rømer Grøntved**

* Website: https://blog.grontved.dk
* GitHub: [@kasperg3](https://github.com/kasperg3)

# 🤝 Contributing

Contributions, issues and feature requests are welcome!<br />Feel free to check [issues page](https://github.com/kasperg3/swarm-simulator/issues). You can also take a look at the [contributing guide](https://github.com/kasperg3/swarm-simulator/blob/main/CONTRIBUTING.md).

# Show your support

Give a ⭐️ if this project helped you!

# 📝 License

Copyright © 2022 [Kasper Rømer Grøntved](https://github.com/kasperg3).<br />
This project is [MIT](https://github.com/kasperg3/swarm-simulator/blob/main/LICENCE) licensed.
