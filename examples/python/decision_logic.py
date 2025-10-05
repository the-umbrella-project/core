from enum import Enum
from dataclasses import dataclass
from typing import Tuple


class IrrigationMode(Enum):
    NORMAL = "normal"
    CONSERVATION = "conservation"
    EXTREME = "extreme"


@dataclass
class SystemConditions:
    et0: float
    temperature: float
    humidity: float
    hour: int
    power_available: bool
    water_level: int
    mode: IrrigationMode = IrrigationMode.NORMAL



class IrrigationDecisionEngine:
    
    def __init__(self, min_duration=5, max_duration=60):
        self.min_duration = min_duration
        self.max_duration = max_duration

    
    def should_irrigate(self, conditions: SystemConditions) -> bool:
        if conditions.et0 < 2.0:
            return False
        
        if conditions.water_level < 500:
            return False
        
        if not conditions.power_available and conditions.et0 < 4.0:
            return False
        
        if self._is_optimal_time(conditions.hour):
            return conditions.et0 > 2.5
        
        if conditions.temperature > 35:
            return conditions.et0 > 3.0
        
        if conditions.mode == IrrigationMode.EXTREME:
            return conditions.et0 > 5.0 and self._is_optimal_time(conditions.hour)
        
        return conditions.et0 > 3.5

    
    def calculate_duration(self, conditions: SystemConditions) -> int:
        base_duration = int((conditions.et0 - 2.0) * 10)
        
        if conditions.temperature > 35:
            base_duration = int(base_duration * 1.3)
        
        if conditions.mode == IrrigationMode.CONSERVATION:
            base_duration = int(base_duration * 0.7)
        elif conditions.mode == IrrigationMode.EXTREME:
            base_duration = int(base_duration * 0.5)
        
        if not conditions.power_available:
            base_duration = int(base_duration * 0.8)
        
        if self._is_optimal_time(conditions.hour):
            base_duration = int(base_duration * 1.1)
        
        return max(self.min_duration, min(self.max_duration, base_duration))

    
    def _is_optimal_time(self, hour: int) -> bool:
        return (7 <= hour <= 9) or (17 <= hour <= 19)

    
    def make_decision(self, conditions: SystemConditions) -> Tuple[bool, int]:
        should_water = self.should_irrigate(conditions)
        duration = self.calculate_duration(conditions) if should_water else 0
        
        return should_water, duration



def main():
    engine = IrrigationDecisionEngine()
    
    test_scenarios = [
        SystemConditions(et0=4.5, temperature=28, humidity=60, hour=8, 
                        power_available=True, water_level=3000),
        SystemConditions(et0=6.0, temperature=35, humidity=45, hour=14, 
                        power_available=True, water_level=2000),
        SystemConditions(et0=3.0, temperature=25, humidity=70, hour=18, 
                        power_available=False, water_level=1500),
        SystemConditions(et0=7.5, temperature=38, humidity=40, hour=12, 
                        power_available=True, water_level=4000, 
                        mode=IrrigationMode.EXTREME),
    ]
    
    print("Irrigation Decision Examples")
    print("-" * 70)
    
    for i, scenario in enumerate(test_scenarios, 1):
        should_water, duration = engine.make_decision(scenario)
        
        print(f"\nScenario {i}:")
        print(f"  ET0: {scenario.et0} mm/day, Temp: {scenario.temperature}C, "
              f"Hour: {scenario.hour}:00")
        print(f"  Mode: {scenario.mode.value}, Power: {scenario.power_available}, "
              f"Water: {scenario.water_level}ml")
        print(f"  Decision: {'IRRIGATE' if should_water else 'SKIP'} "
              f"for {duration} seconds")


if __name__ == "__main__":
    main()
