/*
  60_custom_hal_gpio
  Implements a custom zero-overhead Hardware Abstraction Layer (HAL) for GPIO pins.
  Combines bare-metal register speeds with clean, readable object-oriented code.
*/

#include <avr/io.h>

// Enumerate the internal hardware controller microchip ports
enum TargetPort {
  PORT_B,
  PORT_C,
  PORT_D
};

class FastGPIO {
  private:
    volatile uint8_t* _portRegister;
    volatile uint8_t* _ddrRegister;
    volatile uint8_t* _pinRegister;
    uint8_t _pinMask;

  public:
    // Constructor maps abstract ports straight to absolute hardware memory locations
    FastGPIO(TargetPort target, uint8_t pinNumber) {
      _pinMask = (1 << pinNumber);
      
      switch(target) {
        case PORT_B:
          _portRegister = &PORTB;
          _ddrRegister  = &DDRB;
          _pinRegister  = &PINB;
          break;
        case PORT_C:
          _portRegister = &PORTC;
          _ddrRegister  = &DDRC;
          _pinRegister  = &PINC;
          break;
        case PORT_D:
          _portRegister = &PORTD;
          _ddrRegister  = &DDRD;
          _pinRegister  = &PIND;
          break;
      }
    }

    // Inline tells the compiler to replace the function call with direct assembly,
    // achieving absolute maximum execution speed with no function call overhead.
    inline void setAsOutput() { *_ddrRegister |= _pinMask; }
    inline void setAsInput()  { *_ddrRegister &= ~_pinMask; }
    inline void writeHigh()   { *_portRegister |= _pinMask; }
    inline void writeLow()    { *_portRegister &= ~_pinMask; }
    inline void toggle()      { *_pinRegister = _pinMask; } // Fast AVR pin-toggle exploit
    inline bool readState()   { return (*_pinRegister & _pinMask); }
};

// Instantiates a custom pin map profile object for Digital Pin 13 (Port B, Bit 5)
FastGPIO statusLED(PORT_B, 5);

void setup() {
  // Configures the pin direction via the custom abstraction interface layer
  statusLED.setAsOutput();
}

void loop() {
  // Executes absolute bare-metal speed state flips via a clean object layout
  while(true) {
    statusLED.writeHigh();
    for (volatile uint32_t i = 0; i < 50000; i++); // Direct clock cycle delay hold
    
    statusLED.writeLow();
    for (volatile uint32_t i = 0; i < 50000; i++);
  }
}
