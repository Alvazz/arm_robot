# arm_robot
STM32 project for control board of double 7-DOF mobile robot from HUST AC

- MCU: STM32F103RCT6
- Board: Customized (as described in `arm_robot.ioc`)
- Develop environment: STM32CubeMX + SW4STM32 (or MDK5) + J-Link

# Peripherals
- PWM
  - [x] Camera servo pitch (LD-1501MG)
  - [x] Camera servo yaw (LD-3015MG)
  - [ ] Lifter (customized)
- UART
  - [x] PC Debug
  - [x] rosserial
- RS-485
  - [ ] left arm (7-DOF customized from zeda-tech.com)
  - [ ] right arm (7-DOF customized from zeda-tech.com)
- I2C
  - [x] IMU beside camera (BMX055)
  - [ ] IMU top (BMX055)
  - [ ] IMU bottom (BMX055)
- CAN
  - [ ] Left front wheel (C620 Brushless DC Motor Speed Controller)
  - [ ] Left back wheel (C620 Brushless DC Motor Speed Controller)
  - [ ] Right back wheel (C620 Brushless DC Motor Speed Controller)
  - [ ] Right front wheel (C620 Brushless DC Motor Speed Controller)
- GPIO
  - [x] Button
  - [ ] LED
