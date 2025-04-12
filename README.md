# 🕵️ Kidnapped Robot Retrieval Bot
This is a real-world autonomous robot designed to explore and navigate an N×N grid environment to locate and retrieve a target object (representing a "kidnapped" entity). It intelligently avoids obstacles using ultrasonic sensors and creates a dynamic internal map to plan the optimal path in real-time.

## 🚀 Features
- Autonomous navigation across an N×N grid with configurable size
- Real-time obstacle detection using three ultrasonic sensors (left, front, right)
- Dynamic pathfinding and memory mapping to explore unknown areas
- Wall-following and decision-making using simple spatial awareness
- Modular and expandable logic for different grid sizes and complexities

## ⚙️ Hardware Used
- ESP32 microcontroller

- 3x HC-SR04 Ultrasonic Sensors

- 2x DC Motors with Motor Driver (L298N or similar)
  - Will be changed to N20 motors

- Power supply (LiPo or battery pack)

- Custom PCB or breadboard with jumper wires

## 📁 File Structure
### /kidnapped-robot
### ├── robot_control.ino      # Main Arduino/ESP32 control code
### ├── README.md              # Project overview and documentation
### ├── /images                # Pictures of robot or schematics
### ├── /docs                  # Optional detailed documentation
### └── LICENSE                # Optional license file

## 🧠 How It Works
- Initializes an N×N grid, with boundary walls and unexplored inner spaces.
- Begins at a starting cell and scans surroundings using ultrasonic sensors.
- Marks explored and blocked paths in its internal matrix.
- Makes decisions to turn or move forward based on open directions.
- If stuck or looped, searches for the nearest unexplored (zero) grid cell and reroutes.
- Continues until all reachable areas are explored or target is found.

## 📌 Pin Configuration
### ESP32 Pin Configuration
- Left Trigger	26
- Left Echo	25
- Right Trigger	14
- Right Echo	27
- Front Trigger	13
- Front Echo	12
- Motor A (PWM)	5, 18
- Motor B (PWM)	19, 21
- Motor Speed	22, 23

## 📸 To-Do
- Add configuration option for grid size (N)

- Include robot pictures and environment

- Upload video demo of real-world test

- Improve path selection with shortest-path logic
