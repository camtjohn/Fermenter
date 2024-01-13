#ifndef MAIN_H
#define MAIN_H

#define ADC_NUM_READINGS            100
#define ADJUST_MV_READING           11
#define PIN_RELAY_PUMP              4       //GPIO adjacent to A2D
#define PIN_RELAY_HEATER            5       //GPIO adjacent to pump
#define UPPER_THRESH                80    // Turn on cooling pump when temp gets above this
#define LOWER_THRESH                69    // Turn on heater when temp gets below this
#define POLL_TIME_PUMP_ON           60000   // 30000 =30 sec
#define POLL_TIME_HEATER_ON         60000   // 30000 =30 sec
#define POLL_TIME_STANDBY           120000  // 120000=2 min
#define MAX_ITER_NO_PUBLISH         30      // max 1hr between publish events

// Run cooling pump for some iterations, stop for an iteration and read temp
#define NUM_ITERATIONS_RUN_PUMP     5       // (5x)1min= run for 5min

const static char *TAG = "FERMENTER";

typedef enum {
    STANDBY,
    COOLING_PUMP_ENABLED,
    HEATER_ENABLED
} FERMENTER_STATE;

float get_temp(void);
void enable_pump(void);
void disable_pump(void);

#endif