# C Examples - Smart Irrigation Concepts

This folder contains educational C examples demonstrating core concepts used in smart irrigation systems. These examples are provided for learning purposes and do not contain proprietary implementation details.

## Overview

These examples demonstrate:

1. Penman-Monteith ET0 calculation methodology
2. Sensor data simulation and validation patterns
3. Basic irrigation decision logic concepts

## Requirements

- C compiler (GCC, Clang, MSVC, or similar)
- Standard C library (math.h for mathematical functions)

## Compilation

See `BUILD.md` for detailed compilation instructions for different platforms.

### Quick Start (Linux/macOS)

```bash
gcc -o et0_calculator et0_calculator.c -lm
gcc -o sensor_simulator sensor_simulator.c -lm
gcc -o decision_logic decision_logic.c -lm
```

### Quick Start (Windows with MinGW)

```bash
gcc -o et0_calculator.exe et0_calculator.c -lm
gcc -o sensor_simulator.exe sensor_simulator.c -lm
gcc -o decision_logic.exe decision_logic.c -lm
```

## Examples

### 1. ET0 Calculator (`et0_calculator.c`)

Demonstrates the calculation of reference evapotranspiration using the Penman-Monteith equation.

**Concepts demonstrated:**
- Saturation vapor pressure calculation
- Slope of vapor pressure curve
- Basic ET0 calculation framework
- Input validation patterns
- C structure-based design

**Usage:**
```bash
./et0_calculator
```

**Example output:**
```
ET0 Calculation Examples
--------------------------------------------------
Temp: 25.0C, Humidity: 60.0%, Radiation: 8.0 -> ET0: 4.23 mm/day
Temp: 30.0C, Humidity: 50.0%, Radiation: 10.0 -> ET0: 5.67 mm/day
```

### 2. Sensor Simulator (`sensor_simulator.c`)

Demonstrates sensor reading patterns, data validation, and error handling concepts.

**Concepts demonstrated:**
- Realistic sensor data simulation
- Gaussian random number generation
- Data validation techniques
- Anomaly detection patterns
- Time-based variations

**Usage:**
```bash
./sensor_simulator
```

**Example output:**
```
Sensor Simulation Example
------------------------------------------------------------
Reading 1: T=28.3C, H=54.2%, Solar=3.45V [VALID]
Reading 2: T=29.1C, H=56.8%, Solar=3.67V [VALID]
Reading 3: SENSOR ERROR
```

### 3. Decision Logic (`decision_logic.c`)

Demonstrates basic patterns for making irrigation decisions based on environmental conditions.

**Concepts demonstrated:**
- Multi-factor decision making
- Operating mode patterns (normal, conservation, extreme)
- Time-based optimization
- Resource-aware scheduling
- Enumeration-based state management

**Usage:**
```bash
./decision_logic
```

**Example output:**
```
Irrigation Decision Examples
----------------------------------------------------------------------

Scenario 1:
  ET0: 4.5 mm/day, Temp: 28C, Hour: 8:00
  Mode: normal, Power: true, Water: 3000ml
  Decision: IRRIGATE for 35 seconds
```

## Code Structure

All examples follow similar patterns:

1. Type definitions (structs, enums)
2. Initialization functions
3. Core calculation/logic functions
4. Validation functions
5. Main demonstration function

This structure makes the code easy to understand and adapt.

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

## Embedded System Integration

These examples can be adapted for embedded systems:

- All examples use standard C (C99)
- No dynamic memory allocation
- Minimal external dependencies
- Structure-based design suitable for microcontrollers

For Arduino or similar platforms, you would need to:

1. Replace `printf` with `Serial.print`
2. Replace `time.h` functions with RTC libraries
3. Adapt random number generation for your platform
4. Add appropriate hardware interfaces

## Memory Considerations

For resource-constrained systems:

- ET0Calculator struct: ~32 bytes
- SensorReading struct: ~32 bytes
- SystemConditions struct: ~48 bytes
- DecisionEngine struct: ~8 bytes

All examples avoid dynamic allocation and use stack-based variables.

## Limitations

These examples are educational and simplified. They do not include:

- Proprietary optimization algorithms
- Advanced pattern recognition
- Production-grade error handling
- Hardware-specific implementations
- Real-time system integration
- EEPROM/flash storage patterns
- Advanced power management

## License

These examples are provided under the MIT License as part of the Umbrella Project.

See the LICENSE file in the root directory for full license text.

## Development Status

These examples are provided as educational reference material for the Umbrella Project, which is currently in active development. The main project is not yet stable and should not be used in production environments.

For more information about the full project, see the root README.
