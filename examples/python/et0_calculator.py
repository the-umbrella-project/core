import math


class ET0Calculator:
    
    def __init__(self, wind_speed=2.0, altitude=0.0):
        self.wind_speed = wind_speed
        self.altitude = altitude
        self.pressure = self._calculate_pressure()
        self.gamma = 0.000665 * self.pressure

    
    def _calculate_pressure(self):
        return 101.3 * pow((293.0 - 0.0065 * self.altitude) / 293.0, 5.26)

    
    def saturation_vapor_pressure(self, temperature):
        return 0.6108 * math.exp((17.27 * temperature) / (temperature + 237.3))

    
    def slope_vapor_pressure(self, temperature):
        es = self.saturation_vapor_pressure(temperature)
        return (4098 * es) / pow((temperature + 237.3), 2)

    
    def actual_vapor_pressure(self, temperature, relative_humidity):
        return (relative_humidity / 100.0) * self.saturation_vapor_pressure(temperature)

    
    def calculate(self, temperature, humidity, radiation):
        if not self._validate_inputs(temperature, humidity, radiation):
            return -1
        
        delta = self.slope_vapor_pressure(temperature)
        es = self.saturation_vapor_pressure(temperature)
        ea = self.actual_vapor_pressure(temperature, humidity)
        
        numerator = (0.408 * delta * radiation + 
                    self.gamma * (900 / (temperature + 273.15)) * 
                    self.wind_speed * (es - ea))
        
        denominator = delta + self.gamma * (1 + 0.34 * self.wind_speed)
        
        if denominator == 0:
            return -1
        
        et0 = numerator / denominator
        
        return et0 if 0 <= et0 <= 15 else -1

    
    def _validate_inputs(self, temp, humidity, radiation):
        if temp < -10 or temp > 50:
            return False
        if humidity < 0 or humidity > 100:
            return False
        if radiation < 0:
            return False
        return True



def main():
    calculator = ET0Calculator(wind_speed=1.5, altitude=15.0)
    
    test_cases = [
        {"temp": 25.0, "humidity": 60.0, "radiation": 8.0},
        {"temp": 30.0, "humidity": 50.0, "radiation": 10.0},
        {"temp": 35.0, "humidity": 40.0, "radiation": 12.0},
        {"temp": 20.0, "humidity": 70.0, "radiation": 6.0},
    ]
    
    print("ET0 Calculation Examples")
    print("-" * 50)
    
    for case in test_cases:
        et0 = calculator.calculate(
            case["temp"], 
            case["humidity"], 
            case["radiation"]
        )
        
        print(f"Temp: {case['temp']}C, Humidity: {case['humidity']}%, "
              f"Radiation: {case['radiation']} -> ET0: {et0:.2f} mm/day")



if __name__ == "__main__":
    main()
