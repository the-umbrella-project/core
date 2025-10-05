# Python Examples - Smart Irrigation Concepts

This folder contains educational Python examples demonstrating core concepts used in smart irrigation systems. These examples are provided for learning purposes and do not contain proprietary implementation details.

## Overview

These examples demonstrate:

1. Penman-Monteith ET0 calculation methodology
2. Sensor data simulation and validation patterns
3. Basic irrigation decision logic concepts

## Requirements

Python 3.7 or higher

No external dependencies required - all examples use Python standard library only.

## Installation

No installation needed. The examples are standalone Python scripts.

## Examples

### 1. ET0 Calculator (`et0_calculator.py`)

Demonstrates the calculation of reference evapotranspiration using the Penman-Monteith equation.

**Concepts demonstrated:**
- Saturation vapor pressure calculation
- Slope of vapor pressure curve
- Basic ET0 calculation framework
- Input validation patterns

**Usage:**
```bash
python et0_calculator.py
```

**Example output:**
```
ET0 Calculation Examples
--------------------------------------------------
Temp: 25.0C, Humidity: 60.0%, Radiation: 8.0 -> ET0: 4.23 mm/day
Temp: 30.0C, Humidity: 50.0%, Radiation: 10.0 -> ET0: 5.67 mm/day
```

### 2. Sensor Simulator (`sensor_simulator.py`)

Demonstrates sensor reading patterns, data validation, and error handling concepts.

**Concepts demonstrated:**
- Realistic sensor data simulation
- Data validation techniques
- Anomaly detection patterns
- Error handling strategies

**Usage:**
```bash
python sensor_simulator.py
```

**Example output:**
```
Sensor Simulation Example
------------------------------------------------------------
Reading 1: T=28.3C, H=54.2%, Solar=3.45V [VALID]
Reading 2: T=29.1C, H=56.8%, Solar=3.67V [VALID]
Reading 3: SENSOR ERROR
```

### 3. Decision Logic (`decision_logic.py`)

Demonstrates basic patterns for making irrigation decisions based on environmental conditions.

**Concepts demonstrated:**
- Multi-factor decision making
- Operating mode patterns (normal, conservation, extreme)
- Time-based optimization
- Resource-aware scheduling

**Usage:**
```bash
python decision_logic.py
```

**Example output:**
```
Irrigation Decision Examples
----------------------------------------------------------------------

Scenario 1:
  ET0: 4.5 mm/day, Temp: 28C, Hour: 8:00
  Mode: normal, Power: True, Water: 3000ml
  Decision: IRRIGATE for 35 seconds
```

## Educational Notes

### About ET0 Calculations

The Penman-Monteith equation is a standardized method for calculating reference evapotranspiration. The examples show the basic structure but actual implementations may require:

- Site-specific calibration
- Additional environmental factors
- Historical data analysis
- Crop coefficients

### About Decision Logic

The decision logic examples demonstrate basic patterns. Production systems typically include:

- Machine learning for pattern recognition
- Historical trend analysis
- Predictive modeling
- Multi-sensor fusion

### About Sensor Management

Real-world sensor systems require:

- Calibration procedures
- Drift compensation
- Multi-point validation
- Redundancy strategies

## Integration Concepts

These examples can be combined to create a basic irrigation monitoring system:

```python
from et0_calculator import ET0Calculator
from sensor_simulator import SensorSimulator
from decision_logic import IrrigationDecisionEngine, SystemConditions, IrrigationMode

calculator = ET0Calculator(wind_speed=1.5, altitude=15.0)
simulator = SensorSimulator()
engine = IrrigationDecisionEngine()

reading = simulator.read_sensors()
if simulator.validate_reading(reading):
    et0 = calculator.calculate(
        reading.temperature,
        reading.humidity,
        reading.solar_voltage
    )
    
    conditions = SystemConditions(
        et0=et0,
        temperature=reading.temperature,
        humidity=reading.humidity,
        hour=12,
        power_available=True,
        water_level=3000
    )
    
    should_water, duration = engine.make_decision(conditions)
```

## Limitations

These examples are educational and simplified. They do not include:

- Proprietary optimization algorithms
- Advanced pattern recognition
- Production-grade error handling
- Hardware-specific implementations
- Real-time system integration

## License

These examples are provided under the MIT License as part of the Umbrella Project.

See the LICENSE file in the root directory for full license text.

## Development Status

These examples are provided as educational reference material for the Umbrella Project, which is currently in active development. The main project is not yet stable and should not be used in production environments.

For more information about the full project, see the root README.
