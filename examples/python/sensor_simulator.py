import random
import time
from dataclasses import dataclass
from typing import Optional


@dataclass
class SensorReading:
    temperature: float
    humidity: float
    solar_voltage: float
    timestamp: float
    valid: bool = True



class SensorSimulator:
    
    def __init__(self, base_temp=25.0, base_humidity=60.0):
        self.base_temp = base_temp
        self.base_humidity = base_humidity
        self.last_temp = base_temp
        self.last_humidity = base_humidity
        self.error_rate = 0.02

    
    def read_sensors(self) -> SensorReading:
        if random.random() < self.error_rate:
            return SensorReading(
                temperature=float('nan'),
                humidity=float('nan'),
                solar_voltage=0.0,
                timestamp=time.time(),
                valid=False
            )
        
        hour = time.localtime().tm_hour
        
        temp_variation = random.gauss(0, 1.5)
        humidity_variation = random.gauss(0, 5.0)
        
        time_factor = abs(hour - 12) / 12.0
        
        temperature = self.base_temp + temp_variation + (5 * (1 - time_factor))
        humidity = self.base_humidity + humidity_variation - (10 * (1 - time_factor))
        
        temperature = max(-10, min(50, temperature))
        humidity = max(0, min(100, humidity))
        
        solar_base = max(0, 1 - time_factor) * 4.0
        solar_voltage = solar_base + random.uniform(-0.2, 0.2)
        
        self.last_temp = temperature
        self.last_humidity = humidity
        
        return SensorReading(
            temperature=temperature,
            humidity=humidity,
            solar_voltage=max(0, solar_voltage),
            timestamp=time.time(),
            valid=True
        )

    
    def validate_reading(self, reading: SensorReading, 
                        prev_reading: Optional[SensorReading] = None) -> bool:
        if not reading.valid:
            return False
        
        if reading.temperature < -20 or reading.temperature > 60:
            return False
        if reading.humidity < 0 or reading.humidity > 100:
            return False
        
        if prev_reading and prev_reading.valid:
            temp_change = abs(reading.temperature - prev_reading.temperature)
            humidity_change = abs(reading.humidity - prev_reading.humidity)
            
            if temp_change > 10 or humidity_change > 30:
                return False
        
        return True



def main():
    simulator = SensorSimulator(base_temp=28.0, base_humidity=55.0)
    
    print("Sensor Simulation Example")
    print("-" * 60)
    
    prev_reading = None
    
    for i in range(10):
        reading = simulator.read_sensors()
        is_valid = simulator.validate_reading(reading, prev_reading)
        
        if reading.valid:
            print(f"Reading {i+1}: T={reading.temperature:.1f}C, "
                  f"H={reading.humidity:.1f}%, "
                  f"Solar={reading.solar_voltage:.2f}V "
                  f"[{'VALID' if is_valid else 'INVALID'}]")
        else:
            print(f"Reading {i+1}: SENSOR ERROR")
        
        prev_reading = reading
        time.sleep(0.5)



if __name__ == "__main__":
    main()
