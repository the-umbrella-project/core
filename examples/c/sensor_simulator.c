#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>


typedef struct {
    double temperature;
    double humidity;
    double solar_voltage;
    time_t timestamp;
    bool valid;
} SensorReading;


typedef struct {
    double base_temp;
    double base_humidity;
    double last_temp;
    double last_humidity;
    double error_rate;
} SensorSimulator;


void sensor_init(SensorSimulator *sim, double base_temp, double base_humidity) {
    sim->base_temp = base_temp;
    sim->base_humidity = base_humidity;
    sim->last_temp = base_temp;
    sim->last_humidity = base_humidity;
    sim->error_rate = 0.02;
}


double random_gaussian(double mean, double stddev) {
    static double n2 = 0.0;
    static int n2_cached = 0;
    
    if (!n2_cached) {
        double x, y, r;
        do {
            x = 2.0 * rand() / RAND_MAX - 1;
            y = 2.0 * rand() / RAND_MAX - 1;
            r = x * x + y * y;
        } while (r == 0.0 || r > 1.0);
        
        double d = sqrt(-2.0 * log(r) / r);
        double n1 = x * d;
        n2 = y * d;
        
        n2_cached = 1;
        return n1 * stddev + mean;
    } else {
        n2_cached = 0;
        return n2 * stddev + mean;
    }
}


SensorReading read_sensors(SensorSimulator *sim) {
    SensorReading reading;
    reading.timestamp = time(NULL);
    
    if ((double)rand() / RAND_MAX < sim->error_rate) {
        reading.temperature = NAN;
        reading.humidity = NAN;
        reading.solar_voltage = 0.0;
        reading.valid = false;
        return reading;
    }
    
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    int hour = local->tm_hour;
    
    double temp_variation = random_gaussian(0, 1.5);
    double humidity_variation = random_gaussian(0, 5.0);
    
    double time_factor = fabs(hour - 12) / 12.0;
    
    double temperature = sim->base_temp + temp_variation + (5 * (1 - time_factor));
    double humidity = sim->base_humidity + humidity_variation - (10 * (1 - time_factor));
    
    temperature = fmax(-10, fmin(50, temperature));
    humidity = fmax(0, fmin(100, humidity));
    
    double solar_base = fmax(0, 1 - time_factor) * 4.0;
    double solar_voltage = solar_base + ((double)rand() / RAND_MAX * 0.4 - 0.2);
    
    sim->last_temp = temperature;
    sim->last_humidity = humidity;
    
    reading.temperature = temperature;
    reading.humidity = humidity;
    reading.solar_voltage = fmax(0, solar_voltage);
    reading.valid = true;
    
    return reading;
}

bool validate_reading(SensorReading *current, SensorReading *previous) {
    if (!current->valid) {
        return false;
    }
    
    if (current->temperature < -20 || current->temperature > 60) {
        return false;
    }
    if (current->humidity < 0 || current->humidity > 100) {
        return false;
    }
    
    if (previous != NULL && previous->valid) {
        double temp_change = fabs(current->temperature - previous->temperature);
        double humidity_change = fabs(current->humidity - previous->humidity);
        
        if (temp_change > 10 || humidity_change > 30) {
            return false;
        }
    }
    
    return true;
}

int main() {
    srand(time(NULL));
    
    SensorSimulator sim;
    sensor_init(&sim, 28.0, 55.0);
    
    printf("Sensor Simulation Example\n");
    printf("------------------------------------------------------------\n");
    
    SensorReading prev_reading = {0};
    prev_reading.valid = false;
    
    for (int i = 0; i < 10; i++) {
        SensorReading reading = read_sensors(&sim);
        bool is_valid = validate_reading(&reading, prev_reading.valid ? &prev_reading : NULL);
        
        if (reading.valid) {
            printf("Reading %d: T=%.1fC, H=%.1f%%, Solar=%.2fV [%s]\n",
                   i + 1,
                   reading.temperature,
                   reading.humidity,
                   reading.solar_voltage,
                   is_valid ? "VALID" : "INVALID");
        } else {
            printf("Reading %d: SENSOR ERROR\n", i + 1);
        }
        
        prev_reading = reading;
    }
    
    return 0;
}
