#include <stdio.h>
#include <stdbool.h>


typedef enum {
    MODE_NORMAL,
    MODE_CONSERVATION,
    MODE_EXTREME
} IrrigationMode;


typedef struct {
    double et0;
    double temperature;
    double humidity;
    int hour;
    bool power_available;
    int water_level;
    IrrigationMode mode;
} SystemConditions;


typedef struct {
    int min_duration;
    int max_duration;
} DecisionEngine;


void engine_init(DecisionEngine *engine, int min_duration, int max_duration) {
    engine->min_duration = min_duration;
    engine->max_duration = max_duration;
}


bool is_optimal_time(int hour) {
    return (hour >= 7 && hour <= 9) || (hour >= 17 && hour <= 19);
}


bool should_irrigate(DecisionEngine *engine, SystemConditions *cond) {
    if (cond->et0 < 2.0) {
        return false;
    }
    
    if (cond->water_level < 500) {
        return false;
    }
    
    if (!cond->power_available && cond->et0 < 4.0) {
        return false;
    }
    
    if (is_optimal_time(cond->hour)) {
        return cond->et0 > 2.5;
    }
    
    if (cond->temperature > 35) {
        return cond->et0 > 3.0;
    }
    
    if (cond->mode == MODE_EXTREME) {
        return cond->et0 > 5.0 && is_optimal_time(cond->hour);
    }
    
    return cond->et0 > 3.5;
}

int calculate_duration(DecisionEngine *engine, SystemConditions *cond) {
    int base_duration = (int)((cond->et0 - 2.0) * 10);
    
    if (cond->temperature > 35) {
        base_duration = (int)(base_duration * 1.3);
    }
    
    if (cond->mode == MODE_CONSERVATION) {
        base_duration = (int)(base_duration * 0.7);
    } else if (cond->mode == MODE_EXTREME) {
        base_duration = (int)(base_duration * 0.5);
    }
    
    if (!cond->power_available) {
        base_duration = (int)(base_duration * 0.8);
    }
    
    if (is_optimal_time(cond->hour)) {
        base_duration = (int)(base_duration * 1.1);
    }
    
    if (base_duration < engine->min_duration) {
        return engine->min_duration;
    }
    if (base_duration > engine->max_duration) {
        return engine->max_duration;
    }
    return base_duration;
}

void make_decision(DecisionEngine *engine, SystemConditions *cond,
                   bool *should_water, int *duration) {
    *should_water = should_irrigate(engine, cond);
    *duration = *should_water ? calculate_duration(engine, cond) : 0;
}

const char* mode_to_string(IrrigationMode mode) {
    switch (mode) {
        case MODE_NORMAL: return "normal";
        case MODE_CONSERVATION: return "conservation";
        case MODE_EXTREME: return "extreme";
        default: return "unknown";
    }
}

int main() {
    DecisionEngine engine;
    engine_init(&engine, 5, 60);
    
    SystemConditions scenarios[] = {
        {4.5, 28, 60, 8, true, 3000, MODE_NORMAL},
        {6.0, 35, 45, 14, true, 2000, MODE_NORMAL},
        {3.0, 25, 70, 18, false, 1500, MODE_NORMAL},
        {7.5, 38, 40, 12, true, 4000, MODE_EXTREME}
    };
    
    int num_scenarios = sizeof(scenarios) / sizeof(SystemConditions);
    
    printf("Irrigation Decision Examples\n");
    printf("----------------------------------------------------------------------\n");
    
    for (int i = 0; i < num_scenarios; i++) {
        bool should_water;
        int duration;
        
        make_decision(&engine, &scenarios[i], &should_water, &duration);
        
        printf("\nScenario %d:\n", i + 1);
        printf("  ET0: %.1f mm/day, Temp: %.0fC, Hour: %d:00\n",
               scenarios[i].et0,
               scenarios[i].temperature,
               scenarios[i].hour);
        printf("  Mode: %s, Power: %s, Water: %dml\n",
               mode_to_string(scenarios[i].mode),
               scenarios[i].power_available ? "true" : "false",
               scenarios[i].water_level);
        printf("  Decision: %s for %d seconds\n",
               should_water ? "IRRIGATE" : "SKIP",
               duration);
    }
    
    return 0;
}
