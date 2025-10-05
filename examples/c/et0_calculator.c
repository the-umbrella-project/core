#include <stdio.h>
#include <math.h>
#include <stdbool.h>


typedef struct {
    double wind_speed;
    double altitude;
    double pressure;
    double gamma;
} ET0Calculator;


void et0_init(ET0Calculator *calc, double wind_speed, double altitude) {
    calc->wind_speed = wind_speed;
    calc->altitude = altitude;
    calc->pressure = 101.3 * pow((293.0 - 0.0065 * altitude) / 293.0, 5.26);
    calc->gamma = 0.000665 * calc->pressure;
}


double saturation_vapor_pressure(double temperature) {
    return 0.6108 * exp((17.27 * temperature) / (temperature + 237.3));
}


double slope_vapor_pressure(double temperature) {
    double es = saturation_vapor_pressure(temperature);
    return (4098 * es) / pow((temperature + 237.3), 2);
}


double actual_vapor_pressure(double temperature, double relative_humidity) {
    return (relative_humidity / 100.0) * saturation_vapor_pressure(temperature);
}


bool validate_inputs(double temp, double humidity, double radiation) {
    if (temp < -10 || temp > 50) return false;
    if (humidity < 0 || humidity > 100) return false;
    if (radiation < 0) return false;
    return true;
}


double calculate_et0(ET0Calculator *calc, double temperature, 
                     double humidity, double radiation) {
    if (!validate_inputs(temperature, humidity, radiation)) {
        return -1;
    }
    
    double delta = slope_vapor_pressure(temperature);
    double es = saturation_vapor_pressure(temperature);
    double ea = actual_vapor_pressure(temperature, humidity);
    
    double numerator = 0.408 * delta * radiation + 
                       calc->gamma * (900 / (temperature + 273.15)) * 
                       calc->wind_speed * (es - ea);
    
    double denominator = delta + calc->gamma * (1 + 0.34 * calc->wind_speed);
    
    if (denominator == 0) {
        return -1;
    }
    
    double et0 = numerator / denominator;
    
    return (et0 >= 0 && et0 <= 15) ? et0 : -1;
}


int main() {
    ET0Calculator calc;
    et0_init(&calc, 1.5, 15.0);
    
    typedef struct {
        double temp;
        double humidity;
        double radiation;
    } TestCase;
    
    TestCase test_cases[] = {
        {25.0, 60.0, 8.0},
        {30.0, 50.0, 10.0},
        {35.0, 40.0, 12.0},
        {20.0, 70.0, 6.0}
    };
    
    int num_cases = sizeof(test_cases) / sizeof(TestCase);
    
    printf("ET0 Calculation Examples\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < num_cases; i++) {
        double et0 = calculate_et0(&calc, 
                                   test_cases[i].temp,
                                   test_cases[i].humidity,
                                   test_cases[i].radiation);
        
        printf("Temp: %.1fC, Humidity: %.1f%%, Radiation: %.1f -> ET0: %.2f mm/day\n",
               test_cases[i].temp,
               test_cases[i].humidity,
               test_cases[i].radiation,
               et0);
    }
    
    return 0;
}
