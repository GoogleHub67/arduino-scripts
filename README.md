# 🤖 Master Arduino Basics Collection

A professional, production-ready framework repository containing **70 essential Arduino firmware templates**. This collection scales from basic digital I/O structures up to advanced bare-metal register optimizations, low-level timing controls, and memory diagnostic tracking.

---

## 📁 Repository Directory Architecture
The codebase is cleanly split into two core divisions to maintain industry standards:
* **`src/`**: Houses all 70 functional sketches. Each `.ino` file is kept inside its mandatory matching folder block to ensure flawless compilation.
* **`docs/`**: Holds helper manuals, error references, and architecture documentation.

```text
basic-arduino-scripts/
├── .gitignore
├── LICENSE
├── README.md
├── docs/
│   └── troubleshooting.md
└── src/
    ├── 01_blink/
    ├── 02_button_led/
    └── ... (all 26 folder modules)
```

---

## 🚀 Getting Started & Deployment

1. **Install Software**: Download and install the latest [Arduino IDE](https://arduino.cc).
2. **Download Repository**: Clone this workspace to your desktop machine:
   ```bash
   git clone https://github.com/GoogleHub67/arduino-scripts
   ```
3. **Open Sketches**: Open the `src/` directory, choose any target project folder, and double-click the inner `.ino` file to auto-launch the IDE environment workspace.
4. **Fix Missing Dependencies**: If a script throws a compilation warning, consult the guide inside [docs/troubleshooting.md](docs/troubleshooting.md).

---

## 📊 Master Template Index

| Directory / Folder Name | Level | Primary Concepts & Protocols Covered |
| :--- | :--- | :--- |
| **`01_blink`** | 🟢 Level 1 | Digital Pin Output, `digitalWrite()`, Standard Time Delays |
| **`02_button_led`** | 🟢 Level 1 | Digital Inputs, Hardware Pull-up Resistors (`INPUT_PULLUP`) |
| **`03_serial_print`** | 🟢 Level 1 | UART Serial Diagnostics, Data Logs, Baud Rate Configurations |
| **`04_analog_read`** | 🟢 Level 1 | Analog-to-Digital Conversion (ADC), Potentiometers, Voltage Math |
| **`05_pwm_fade`** | 🟢 Level 1 | Pulse Width Modulation (PWM) Dimming, `analogWrite()`, Loop Arrays |
| **`06_servo_sweep`** | 🟡 Level 2 | Servo Hardware Control, Library Integrations (`<Servo.h>`) |
| **`07_ultrasonic_ranger`**| 🟡 Level 2 | Distance Math, High-Speed Pulse In Timing, Acoustic Telemetry |
| **`08_dht_temp_humidity`**| 🟡 Level 2 | Environmental Telemetry Sensors, External Core Drivers |
| **`11_i2c_lcd`** | 🟡 Level 2 | Inter-Integrated Circuit (I2C) Communication Bus, Display Matrices |
| **`09_millis_no_delay`** | 🔵 Level 3 | Non-blocking Concurrency Systems, Time Deltas via `millis()` |
| **`10_state_machine`** | 🔵 Level 3 | Finite State Machine (FSM) Architectures, System Control Engines |
| **`15_string_parsing`** | 🔵 Level 3 | Data Stream Parsing, Data Extraction, Input Buffer Filtering |
| **`19_array_moving_average`**| 🔵 Level 3 | Digital Signal Smoothing Filters, Circular Shift Arrays |
| **`23_circular_buffer`** | 🔵 Level 3 | Memory-Safe Data Buffering, Prevention of Buffer Overflows |
| **`12_eeprom_save`** | 🎛️ Level 4 | Non-Volatile Memory (EEPROM), Preserving State Across Reboots |
| **`13_software_serial`** | 🎛️ Level 4 | Emulating Virtual Serial UART Lines via Generic Software Pins |
| **`14_interrupt_button`**| 🎛️ Level 4 | Hardware-Level Pin Interrupt Handling, Instant Task Preemption |
| **`16_low_power_sleep`** | 🎛️ Level 4 | Low-Power Battery Management Modes, System Standby Control |
| **`17_analog_write_pseudo`**| 🎛️ Level 4 | Manual Microsecond Signal Modulation Without Software Libraries |
| **`18_spi_eeprom_external`**| 🎛️ Level 4 | Serial Peripheral Interface (SPI) High-Speed Hardware Buses |
| **`20_watchdog_timer`** | 🎛️ Level 4 | Hardware Watchdog Safeties, Anti-Freeze / Automatic Recovery |
| **`21_pid_controller`** | 🎛️ Level 4 | Proportional-Integral-Derivative Real-Time Math Feedback Loops |
| **`22_rotary_encoder`** | 🎛️ Level 4 | Rotational Dials, Quad-State Logic Tracking, Phase Changes |
| **`24_direct_port_manipulation`**| 🎛️ Level 4 | Bare-Metal Port Registry Override, 1-Clock Cycle Pin Switching |
| **`25_timer_interrupts`**| 🎛️ Level 4 | Precision Internal Clock Register Configurations (Timer1 CTC) |
| **`26_heap_fragmentation_check`**| 🎛️ Level 4 | SRAM Heap Integrity Monitoring, Run-Time Memory Leak Auditing |
| **`27_i2c_scanner`** | 🎛️ Level 4 | Bus scanning, hex mapping, error handle diagnostics |
| **`28_spi_hardware_max7219`** | 🎛️ Level 4 | Raw register configuration over SPI, latch parameters |
| **`29_eeprom_struct_save`** | 🎛️ Level 4 | Memory offset handling, structural multi-variable byte mapping |
| **`30_ultrasonic_non_blocking`**| 🔥 Level 5 | Non-blocking timing, Interrupt Service Routines (ISRs) |
| **`31_adc_oversampling`** | 🔥 Level 5 | Bitwise decimation (`>> 2`), signal resolution enhancement |
| **`32_custom_pwm_software`** | 🎛️ Level 4 | Manual waveform generation without hardware timer dependency |
| **`33_debounced_button_millis`**| 🔵 Level 3 | State machine logic, mechanical chatter filtration via `millis()` |
| **`34_ring_buffer_uart`** | 🔥 Level 5 | Object-Oriented memory design, FIFO data stream pipelines |
| **`35_runtime_uptime_counter`**| 🔵 Level 3 | Delta timeline arithmetic, 49.7-day rollover parity management |
| **`36_hardware_timer_ctc`** | 🔥 Level 5 | Bare-metal Timer1 CTC registers, clock prescaling formula |
| **`37_low_power_external_interrupt`**| 🔥 Level 5 | Deep sleep modes (`SLEEP_MODE_PWR_DOWN`), INT0 wakeup triggers |
| **`38_watchdog_timer_wakeup`**| 🔥 Level 5 | Standalone WDT configuration, cyclic low-power interrupt logging |
| **`39_direct_port_manipulation_speed`**| 🔥 Level 5 | DDRB/PORTB register overrides, 62.5ns hardware toggle trick |
| **`40_function_pointers_scheduler`**| 🔥 Level 5 | Event-driven task frameworks, function pointer arrays |
| **`41_runtime_stack_heap_sniffer`**| 🔥 Level 5 | Low-level pointer auditing, dynamic memory collision checks |
| **`42_assembly_inline_timing`**| 🔥 Level 5 | Inline assembly syntax injection (`asm volatile`), cycle-accurate `nop` |
| **`43_i2c_software_bit_bang`**| 🔥 Level 5 | Emulating SDA/SCL lines manually, ACK/NACK bus handshakes |
| **`44_raw_pointer_register_access`**| 🔥 Level 5 | Bare-metal address parsing, raw C++ casting, un-defined memory hacks |
| **`45_eeprom_wear_leveling`**| 🔥 Level 5 | Sector rotation algorithms, extending flash write endurance limits |
| **`46_blackbox_crash_logger`**| 🔥 Level 5 | Uninitialized RAM allocation (`.noinit`), post-crash trace tracking |
| **`47_multichannel_adc_dma_pseudo`**| 🔥 Level 5 | Asynchronous interrupt-driven multiplexing via ADMUX registers |
| **`48_binary_serialization_struct`**| 🔥 Level 5 | Preprocessor directives (`#pragma pack`), raw pointer stream casting |
| **`49_timer_input_capture`** | 🔥 Level 5 | Sub-hardware signal routing, pulse period capture registers (ICP1) |
| **`50_software_reboot_watchdog`**| 🔥 Level 5 | Safe watchdog-driven hardware resets, preventing infinite loops |
| **`51_eeprom_circular_log`** | 🎛️ Level 4 | FIFO non-volatile ring logs, absolute index boundary tracking |
| **`52_i2c_multi_byte_handshake`**| 🔥 Level 5 | Sequence validation checking, structural multi-byte bus requests |
| **`53_software_interrupt_simulation`**| 🔥 Level 5 | Pin change interrupt manipulation (PCMSK0/PCICR), soft-vector triggers |
| **`54_fixed_point_math`** | 📐 Level 6 | Q16.16 fractional bitwise math scaling, high-speed calculation |
| **`55_lookup_table_sinewave`**| 📐 Level 6 | Pre-calculated program flash memory tables (`PROGMEM`), zero-CPU math |
| **`56_safe_dynamic_allocation`**| 🔥 Level 5 | Intercepting pointer assignments, dynamic array stack reserve shields |
| **`57_atomic_operations`** | 🔥 Level 5 | Multithreaded safety, isolating registers via `ATOMIC_BLOCK` blocks |
| **`58_nested_interrupt_vectors`**| 🔥 Level 5 | Enabling global gates (`sei()`) inside active ISR handlers for priorities |
| **`59_crc8_packet_verification`**| 📐 Level 6 | Polynomial bitwise division (`0x07`), validating data bus integrity |
| **`60_custom_hal_gpio`** | 🔥 Level 5 | Zero-overhead Hardware Abstraction Layers, inline class methods |
| **`61_spi_dma_ping_pong`** | 🔥 Level 5 | Dual-buffer swap arrays, isolating foreground loops from active SPI |
| **`62_pid_antivindup`** | 📐 Level 6 | Feedback clamping tracking, integral windup saturation mitigation |
| **`63_canbus_extended_mask`**| 🔥 Level 5 | Extended 29-bit CAN identifiers, masking matrices, acceptance filters |
| **`64_software_uart_parity`**| 🔥 Level 5 | Manual software serial transmission, bitwise even parity calculation |
| **`65_dynamic_array_reindexing`**| 🔵 Level 3 | Real-time shift-and-insert data buffers, sliding layout matrices |
| **`66_flash_string_array_progmem`**| 🔥 Level 5 | Two-tiered double pointer maps in Flash, protecting working SRAM |
| **`67_dsp_fir_filter`** | 📐 Level 6 | Finite Impulse Response filters, convolution computation loops |
| **`68_fixed_point_matrix_vector`**| 📐 Level 6 | 2x2 coordinate transformation dot products via Q16.16 fixed arrays |
| **`69_numerical_integration_trapezoidal`**| 📐 Level 6 | Real-time calculus integration loop, trapezoidal curve approximations |
| **`70_baremetal_pseudo_rand_lcg`**| 📐 Level 6 | Linear Congruential Generator formulas, library-free random metrics |

---

## 🛠️ Recommended Core Hardware Inventory
To test all applications within this master collection successfully, the following elements are recommended:
* **Microcontroller**: Arduino Uno R3, Nano, or fully compatible ATmega328P development board.
* **Input Elements**: Push-Buttons, 10k-ohm Potentiometers, Rotary Encoders.
* **Actuators & Displays**: Standard LEDs, 5V Hobby Servos, 16x2 I2C Character LCD Modules.
* **Sensor Nodes**: HC-SR04 Ultrasonic modules, DHT11 or DHT22 Temperature modules.
* **Passive Kit**: Solderless Breadboards, Jumper Wires, 220-ohm and 10k-ohm current-limiting resistors.

---

## 📜 Open Source Licensing
This repository is licensed under the terms of the open-source **MIT License**. You are free to copy, modify, distribute, and apply these scripts within personal, academic, or commercial embedded firmware environments. See the `LICENSE` file for details.
