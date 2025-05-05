#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <stdbool.h>

// Traffic light durations (in seconds)
#define RED_DURATION 10
#define YELLOW_DURATION 2
#define GREEN_DURATION 15
#define RED_YELLOW_DURATION 2

// Transition durations (1 hour in seconds)
#define TRANSITION_DURATION 3600
#define BLINKING_YELLOW_INTERVAL 1

// Night period
#define NIGHT_START 22 // Night starts at 22:00
#define NIGHT_END 6    // Night ends at 06:00

// Enumerated states for traffic lights
typedef enum
{
    RED,
    YELLOW,
    GREEN,
    RED_YELLOW,
    BLINKING_YELLOW,
    OFF
} TrafficLightState;

int init_traffic_light(void);         // Init the traffic light controller
int run_traffic_light(void);          // Run the traffic light controller
const char *get_light_color(void);    // Returns a pointer to a string representing the current light color
int button_press_request(void);       // Handle pedestrian button press
bool is_blinking_yellow_period(void); // Check for transition periods
bool is_night_period(void);           // Check if it's night
void handle_blinking_yellow(void);    // Manage blinking yellow behavior
void handle_night_period(void);       // Manage night OFF state

#endif
