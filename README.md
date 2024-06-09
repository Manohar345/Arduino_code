# Arduino_code

This project is written in Arduino Sketch and is deployed on an Arduino board. As this project is IoT-based, it requires several hardware components, including:

1. Arduino
2. Node module
3. Transformer
4. GSM modem
5. Indicator
6. Interface circuit
7. Ultrasonic sensor
8. Motor
9. MQ2 (methane) sensor

## Project Overview

This project addresses a common issue in many areas and streets: uncleaned garbage bins. Our system aims to mitigate this problem by using the following approach:

  **Ultrasonic Sensors**: We install ultrasonic sensors both outside and inside the garbage bin. 
  **External Sensor**: Detects the presence of a person approaching the bin. When detected, the bin opens automatically using a motor.
  **Internal Sensor**: Monitors the fill level of the garbage inside the bin. When the garbage reaches a certain level, an alert message is sent to the garbage collector.

  **GSM Modem**: Used to send the alert message to the garbage collector, whose number is pre-programmed into the system.

  **MQ2 Sensor**: Detects the level of poisonous gases around the garbage bin area. This information is crucial as the vicinity of garbage bins can often contain hazardous gases. The gas level is displayed so that the garbage collector can take necessary precautions, such as wearing masks and gloves.

By implementing this system, we aim to ensure cleaner streets and a safer environment around garbage bins. Our project provides a practical solution to the prevalent issue of uncleaned garbage waste in many areas.
