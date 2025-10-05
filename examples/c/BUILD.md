# C Examples Compilation

## Compilation Commands

### Linux/macOS
```bash
gcc -o et0_calculator et0_calculator.c -lm
gcc -o sensor_simulator sensor_simulator.c -lm
gcc -o decision_logic decision_logic.c -lm
```

### Windows (MinGW)
```bash
gcc -o et0_calculator.exe et0_calculator.c -lm
gcc -o sensor_simulator.exe sensor_simulator.c -lm
gcc -o decision_logic.exe decision_logic.c -lm
```

### Windows (MSVC)
```bash
cl et0_calculator.c
cl sensor_simulator.c
cl decision_logic.c
```

## Running Examples

### Linux/macOS
```bash
./et0_calculator
./sensor_simulator
./decision_logic
```

### Windows
```bash
et0_calculator.exe
sensor_simulator.exe
decision_logic.exe
```
