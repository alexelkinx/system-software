# Traffic Light Controller

## Table of Contents

- [Project Overview](#project-overview)
- [Directory Structure](#directory-structure)
- [Source Files](#source-files)
- [Getting Started](#getting-started)
- [Building the Project](#building-the-project)
- [Using the Program](#using-the-program)
- [Cleaning Up](#cleaning-up)
- [Error Handling](#error-handling)

## Project Overview

This project simulates the operation of a traffic light system. The program controls the traffic light’s state transitions—such as RED, YELLOW, GREEN, and special periods like BLINKING YELLOW during transitions and OFF during the night. It also includes pedestrian request handling, where pressing a button triggers a switch to the GREEN light for pedestrian crossing.

The project uses CMake for building and follows a modular structure with separate source and header files. The logic for controlling traffic light states is implemented in C, with error handling and clear feedback for debugging.

The program runs in an infinite loop, managing transitions and responding to button presses, while respecting the defined time durations for each light state. During the night period, the light goes into the OFF state, and during the transition period, it blinks yellow.

## Directory Structure

```
lab-03-traffic-light-controller/
│
├── include/                # Header files
│ ├── error_codes.h         # Error code definitions
│ └── traffic_light.h       # Function declarations for traffic light operations
│
├── src/                    # Source files
│ ├── main.c                # Main program logic and execution flow
│ └── traffic_light.c       # Traffic light functionality
│
├── CMakeLists.txt          # Build configuration file for CMake
└── README.md               # Project overview, setup, and usage instructions
```

## Source Files

### main.c

The entry point for the traffic light program. It initializes and runs the traffic light system, handling errors by printing error codes and exiting if necessary.

### traffic_light.c

This file contains the logic for initializing and running the traffic light system. It simulates traffic light operation with support for different states (e.g., RED, GREEN, YELLOW), pedestrian requests, and night-time/off periods.

Key functions:

- **`init_traffic_light()`**: Initializes the traffic light system, setting the initial state to RED.
- **`run_traffic_light()`**: Main loop that simulates the traffic light's state transitions and handles pedestrian requests.
- **`handle_blinking_yellow()`**: Manages the blinking yellow period before night and after night ends.
- **`handle_night_period()`**: Puts the traffic light into an OFF state during night time.
- **`get_light_color()`**: Returns a string representation of the current light color.
- **`button_press_request()`**: Simulates checking for a button press to request a pedestrian crossing.
- **`is_blinking_yellow_period()`**: Checks if the current time falls within the blinking yellow period before and after night.
- **`is_night_period()`**: Determines if the current time falls within the night period where the traffic light is OFF.

### traffic_light.h

This header file defines the constants, types, and function declarations used for managing the traffic light system. It includes the traffic light states, durations, and functions related to the operation and transitions of the traffic light.

Key components:

- **Traffic Light Durations**: Defines the durations for each traffic light color and transition.

  - `RED_DURATION`: Duration for red light (10 seconds)
  - `YELLOW_DURATION`: Duration for yellow light (2 seconds)
  - `GREEN_DURATION`: Duration for green light (15 seconds)
  - `RED_YELLOW_DURATION`: Duration for red+yellow light (2 seconds)
  - `TRANSITION_DURATION`: Duration of transition periods (1 hour in seconds)
  - `BLINKING_YELLOW_INTERVAL`: Interval between yellow blinks during transition

- **Night Period**: Defines the night period start and end times.

  - `NIGHT_START`: Night starts at 22:00 (10 PM)
  - `NIGHT_END`: Night ends at 06:00 (6 AM)

- **TrafficLightState Enum**: An enumerated type representing the possible states of the traffic light system.

  - `RED`: The red light state
  - `YELLOW`: The yellow light state
  - `GREEN`: The green light state
  - `RED_YELLOW`: The red+yellow transition state
  - `BLINKING_YELLOW`: The blinking yellow state during transition
  - `OFF`: The off state during the night period

- **Function Declarations**:

  - `int init_traffic_light(void)`: Initializes the traffic light system.
  - `int run_traffic_light(void)`: Runs the traffic light controller, simulating state transitions and handling requests.
  - `const char *get_light_color(void)`: Returns a string representing the current traffic light color.
  - `int button_press_request(void)`: Simulates checking for a pedestrian button press request.
  - `bool is_blinking_yellow_period(void)`: Checks if it's the transition period (blinking yellow).
  - `bool is_night_period(void)`: Checks if it's currently within the night period.
  - `void handle_blinking_yellow(void)`: Manages the blinking yellow transition state.
  - `void handle_night_period(void)`: Manages the night period (turns off the traffic light).

### error_codes.h

Defines error codes used by the program to signal specific problems or issues during execution. This helps improve error reporting and debugging.

## Getting Started

### Prerequisites

Before building and running the program, make sure the following tools are installed:

- **CMake** (version 3.10 or higher)
- **A C Compiler** (e.g., GCC or Clang)

You can verify their installation with the following commands:

```bash
cmake --version
gcc --version
```

## Building the Project

### 1. Create a `build` directory and navigate into it:

```bash
mkdir build && cd build
```

### 2. Run CMake to configure the project:

```bash
cmake ..
```

This generates the necessary build files based on the CMakeLists.txt.

### 3. Compile the project:

```bash
make
```

This command will compile the project and create the executable for the traffic light program.

## Using the Program

To run the traffic light simulation, use the custom run target:

```bash
make run
```

This will start the traffic light simulation, cycling through the light states. You can adjust the behavior and timing of each state in the traffic_light.h file if needed.

### Custom Execution

Alternatively, to run the compiled executable directly, use:

```bash
./traffic_light
```

## Cleaning Up

To clean up the build files and executables, run the following command from the build directory:

```bash
make clean_all
```

This will remove all generated files, except for the Makefile, which will remain for future builds.

## Error Handling

The program uses error codes from error_codes.h to indicate issues like invalid configurations or runtime problems. Clear error messages are displayed, making it easier to debug and fix any problems.
