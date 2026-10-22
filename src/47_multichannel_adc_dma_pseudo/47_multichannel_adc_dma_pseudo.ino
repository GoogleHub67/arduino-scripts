/*
  47_multichannel_adc_dma_pseudo
  Directly manipulates the ADC multiplexer and status registers (ADMUX/ADCSRA) 
  to run rapid background conversion cycles across multiple analog source pins.
*/

volatile uint16_t analogResultsChannels[2]; // Stores background channel samples
volatile uint8_t activeChannelIndex = 0;

void setup() {
  Serial.begin(9600);
  while(!Serial);
  
  noInterrupts();

  // Clear existing setup registers and map reference to Vcc (AVcc with external capacitor)
  ADMUX = (1 << REFS0); 
  
  // Set ADC clock conversion prescaler to 128 (16MHz / 128 = 125kHz sampling clock)
  ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  
  // Enable the Analog-to-Digital Converter system and turn on its conversion complete Interrupt
  ADCSRA |= (1 << ADEN) | (1 << ADIE);

  interrupts();

  // Kickstart the very first asynchronous hardware conversion loop
  ADCSRA |= (1 << ADSC);
  Serial.println("\n--- Asynchronous Background Multiplexer Engine Engaged ---");
}

// Hardware Interrupt Vector triggered immediately when an analog pin conversion completes
ISR(ADC_vect) {
  // Capture conversion result safely (must read ADCL first, or use convenience ADC combined macro)
  uint16_t convertedValue = ADC;
  analogResultsChannels[activeChannelIndex] = convertedValue;

  // Toggle channel source mapping between A0 (MUX 0000) and A1 (MUX 0001)
  activeChannelIndex = (activeChannelIndex == 0) ? 1 : 0;

  // Clear existing pin channel selection bits inside ADMUX mask
  ADMUX = (ADMUX & 0xF0) | activeChannelIndex;

  // Trigger the next background hardware conversion pipeline pass
  ADCSRA |= (1 << ADSC);
}

void loop() {
  noInterrupts();
  uint16_t sensor1 = analogResultsChannels[0];
  uint16_t sensor2 = analogResultsChannels[1];
  interrupts();

  Serial.print("Async Ch0 (A0): "); Serial.print(sensor1);
  Serial.print("\tAsync Ch1 (A1): "); Serial.println(sensor2);
  
  delay(1000); // The loop runs completely independent of the background ADC conversion speeds
}
