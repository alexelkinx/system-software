#include <stdio.h>
#include "traffic_light.h"
#include "error_codes.h"

int main(void)
{
    ErrorCode error_code;

    error_code = init_traffic_light();
    if (error_code != SUCCESS)
    {
        fprintf(stderr, "Error: Failed to initialize traffic light (Error Code: %d)\n", error_code);
        return error_code;
    }

    error_code = run_traffic_light();
    if (error_code != SUCCESS)
    {
        fprintf(stderr, "Error: Failed to run traffic light (Error Code: %d)\n", error_code);
        return error_code;
    }

    return SUCCESS;
}
