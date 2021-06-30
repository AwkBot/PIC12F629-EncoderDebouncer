# PIC12F629 - Encoder Debouncer
Encoder Filter based on PIC12F629.
This process filer the encoder noise, mostly found in cheap encoders. It triggers distinct pulses based on rotation of the encoder stating the if the encoder has been turning clockwise or counter-clockwise. The pulses are active LOW simulating a standard button.

Connections:
  - Pin 2 - GP5 - Connect to Encoder S1/CLK Pin
  - Pin 3 - GP4 - Connect to Encoder S2/DT Pin
  - Pin 7 - GP0 - Output pulse for clockwise rotation
  - Pin 7 - GP1 - Output pulse for counter-clockwise rotation

The HEX files can be found in  the "Packkage"  folder.

Note: The source code is based on something that I found in the Internet, IN case you know the original developer, please, let me know in order to ask to their permission and give them the proper credits.