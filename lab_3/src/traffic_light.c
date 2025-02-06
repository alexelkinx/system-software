#include <stdio.h>
#include <unistd.h> // For sleep function
#include <stdbool.h>
#include <sys/select.h> // For non-blocking input check
#include <time.h>       // For checking the time
#include "traffic_light.h"
#include "error_codes.h"

static TrafficLightState current_state = RED; // Current state of the traffic light
static bool pedestrian_request = false;       // Pedestrian light status (off by default)

int init_traffic_light(void)
{
    current_state = RED;        // Initialize to RED state
    pedestrian_request = false; // No pedestrian request initially

    return SUCCESS;
}

int run_traffic_light(void)
{
    while (1) // Infinite loop
    {

        if (is_blinking_yellow_period())
        {
            handle_blinking_yellow();
        }

        if (is_night_period())
        {
            handle_night_period();
            continue; // Recheck the current time after night
        }

        if (button_press_request())
        {
            pedestrian_request = true;
        }

        if (pedestrian_request)
        {
            printf("Pedestrian requested green light. Switching to GREEN for pedestrian.\n");
            current_state = GREEN;
            printf("Traffic Light: %s\n", get_light_color());
            sleep(GREEN_DURATION);
            pedestrian_request = false; // Reset the request after serving
            current_state = YELLOW;     // Continue to the next state
            continue;                   // Skip the normal state cycle this iteration
        }

        printf("Traffic Light: %s\n", get_light_color());

        // Transition logic for normal day cycle
        switch (current_state)
        {
        case RED:
            sleep(RED_DURATION);
            current_state = RED_YELLOW;
            break;

        case RED_YELLOW:
            sleep(RED_YELLOW_DURATION);
            current_state = GREEN;
            break;

        case GREEN:
            sleep(GREEN_DURATION);
            current_state = YELLOW;
            break;

        case YELLOW:
            sleep(YELLOW_DURATION);
            current_state = RED;
            break;

        default:
            return INVALID_STATE;
        }
    }

    return SUCCESS;
}

// Handle the blinking yellow period (1 hour before night and morning)
void handle_blinking_yellow(void)
{
    printf("Transition Period: Switching to BLINKING YELLOW.\n");
    current_state = BLINKING_YELLOW;

    for (int i = 0; i < TRANSITION_DURATION / BLINKING_YELLOW_INTERVAL; i++)
    {
        printf("Traffic Light: %s\n", get_light_color());
        sleep(BLINKING_YELLOW_INTERVAL);
    }
}

// Manage the night period (OFF state)
void handle_night_period(void)
{
    printf("Night Period: Traffic Light is OFF.\n");
    current_state = OFF;

    while (is_night_period())
    {
        printf("Traffic Light: %s\n", get_light_color());
        sleep(10);
    }

    // Transition to morning blinking yellow
    handle_blinking_yellow();
}

// Function to get the string representation of the current light color
const char *get_light_color(void)
{
    switch (current_state)
    {
    case RED:
        return "RED";
    case YELLOW:
        return "YELLOW";
    case GREEN:
        return "GREEN";
    case RED_YELLOW:
        return "RED+YELLOW";
    case BLINKING_YELLOW:
        return "BLINKING YELLOW";
    case OFF:
        return "OFF";
    default:
        return "UNKNOWN";
    }
}

int button_press_request(void)
{
    fd_set read_fds; // Declare a set of file descriptors to monitor for input activity

    struct timeval timeout = {0, 0}; // Set a timeout for non-blocking behavior (0 seconds, 0 microseconds)

    FD_ZERO(&read_fds);              // Initialize the file descriptor set to be empty
    FD_SET(STDIN_FILENO, &read_fds); // Add standard input (stdin) to the file descriptor set

    // Use select to check if there's activity (input) on stdin without blocking
    // Parameters:
    //   - STDIN_FILENO + 1: Range of file descriptors to monitor
    //   - &read_fds: Set of file descriptors to monitor for readability
    //   - NULL: No file descriptors monitored for writing
    //   - NULL: No file descriptors monitored for exceptional conditions
    //   - &timeout: Maximum time to wait for input (0 seconds here)
    int activity = select(STDIN_FILENO + 1, &read_fds, NULL, NULL, &timeout);

    // Check if there was activity and if stdin is ready for reading
    if (activity > 0 && FD_ISSET(STDIN_FILENO, &read_fds))
    {
        char input = getchar(); // Read a single character from stdin

        return (input == 'b' || input == 'B'); // Return 1 (true) if the character is 'b' or 'B'; otherwise, return 0
    }

    return 0;
}

// Check if we're in a blinking yellow period
bool is_blinking_yellow_period(void)
{

    time_t now = time(NULL); // Get the current time as a `time_t` value (seconds since epoch)
    // Example output: now = 1700875800 (represents 2024-11-25 05:30:00 UTC)

    struct tm *local_time = localtime(&now); // Convert the time to a `tm` structure representing the local time
    // Example output: local_time = { tm_hour = 5, tm_min = 30, tm_sec = 0, ... }

    int hour = local_time->tm_hour; // Extract the hour field from the `tm` structure
    // Example output: hour = 5

    return (hour == NIGHT_START - 1 || hour == NIGHT_END - 1); // NIGHT_START = 22, NIGHT_END = 6
    // Example output: (hour >= 22 || hour < 6) -> true
}

// Check if it's the night period
bool is_night_period(void)
{
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);
    int hour = local_time->tm_hour;

    return (hour >= NIGHT_START || hour < NIGHT_END);
}
