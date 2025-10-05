# The Umbrella Project - Core

Smart irrigation system using advanced environmental intelligence and Penman-Monteith evapotranspiration modeling.

## Development Status

**This repository contains work-in-progress code and is NOT a stable release.**

The code and documentation may change rapidly and may be incomplete, unstable, or otherwise unsuitable for production use. Please see the Development Notice in the LICENSE file for important information about using and sharing this code.

## Project Overview

The Umbrella Project is developing an intelligent irrigation system that uses environmental sensors and advanced algorithms to optimize water usage. The system calculates reference evapotranspiration (ET0) using the Penman-Monteith equation and makes intelligent irrigation decisions based on multiple environmental factors.

## Repository Structure

```
core/
├── LICENSE                    Development notice and MIT license
├── README.md                  This file
├── examples/                  Educational code examples
│   ├── python/               Python implementations
│   │   ├── README.md         Python examples documentation
│   │   ├── et0_calculator.py ET0 calculation example
│   │   ├── sensor_simulator.py Sensor patterns example
│   │   └── decision_logic.py  Decision logic example
│   └── c/                    C implementations
│       ├── README.md         C examples documentation
│       ├── BUILD.md          Compilation instructions
│       ├── et0_calculator.c  ET0 calculation example
│       ├── sensor_simulator.c Sensor patterns example
│       └── decision_logic.c   Decision logic example
└── main_backup-2.ino         Original Arduino implementation (private)
```

## Getting Started

### For Python Users

Navigate to the `examples/python` directory and follow the README instructions there.

```bash
cd examples/python
python et0_calculator.py
python sensor_simulator.py
python decision_logic.py
```

Requirements: Python 3.7 or higher

### For C Users

Navigate to the `examples/c` directory and follow the README and BUILD instructions there.

```bash
cd examples/c
gcc -o et0_calculator et0_calculator.c -lm
./et0_calculator
```

Requirements: C compiler with standard library

## What's Included

The `examples` folder contains educational implementations demonstrating:

1. **ET0 Calculation**: Penman-Monteith equation implementation for calculating reference evapotranspiration
2. **Sensor Patterns**: Data simulation, validation, and error handling concepts
3. **Decision Logic**: Basic irrigation decision-making based on environmental conditions

These examples are provided as learning resources and demonstrate core concepts without revealing proprietary implementation details.

## What's NOT Included

The examples do NOT include:

- Proprietary optimization algorithms
- Advanced pattern recognition systems
- Production hardware integration code
- Complete system architecture
- Real-time control systems
- Data logging and visualization
- Advanced power management
- Machine learning components

## Key Concepts

### Penman-Monteith ET0

Reference evapotranspiration is calculated using environmental parameters:
- Air temperature
- Relative humidity
- Solar radiation
- Wind speed
- Atmospheric pressure (altitude-adjusted)

### Intelligent Decision Making

The system considers multiple factors:
- Current ET0 values
- Time of day optimization
- Power availability
- Water resource levels
- Operating modes (normal, conservation, extreme)

### Sensor Management

Robust sensor handling includes:
- Data validation
- Anomaly detection
- Error recovery
- Historical averaging

## Hardware Platform

The full system (not included in examples) is designed for:
- Arduino-based microcontrollers
- DHT11/DHT22 temperature and humidity sensors
- RTC (Real-Time Clock) modules
- Solar power monitoring
- LCD display output
- Servo-controlled valve systems

## Contributing

This project is currently in private development. Contributions are not being accepted at this time.

## Roadmap

- [ ] Complete core algorithm development
- [ ] Extensive field testing
- [ ] Power optimization
- [ ] Data visualization tools
- [ ] Mobile app integration
- [ ] Public stable release

## License

This project is licensed under the MIT License - see the LICENSE file for details.

**IMPORTANT**: Please read the Development Notice in the LICENSE file before using or sharing any code from this repository.

## Contact

For questions about the Umbrella Project, please refer to the project documentation or contact the maintainers through official channels (to be announced).

## Acknowledgments

- Penman-Monteith equation standardization by FAO
- Arduino community for hardware platforms
- Open source sensor libraries

## Disclaimer

This is experimental software under active development. Use at your own risk. The developers are not responsible for any damage to crops, equipment, or property resulting from the use of this software.

For production agriculture or critical applications, please consult with professional irrigation specialists and use certified commercial systems.
