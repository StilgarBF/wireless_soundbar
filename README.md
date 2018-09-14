# wireless_soundbar

esp2866 based soundbar that triggers sounds to play on a raspberry pi

The pi should provide an REST-Endpoint where individual sounds are played.

## Hardware

* ESP2866 
* 2x WaveSHare PCF8574 I2C expander - To be able to connect more (8each) buttons to the ESP. This board supports cascading by simply plugging multiple together.
