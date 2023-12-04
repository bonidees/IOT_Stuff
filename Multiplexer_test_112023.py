from machine import Pin, ADC
import utime

# Define the multiplexer control pins
s0 = Pin(10, Pin.OUT)  # Select bit 0
s1 = Pin(11, Pin.OUT)  # Select bit 1
s2 = Pin(12, Pin.OUT)  # Select bit 2

# Define the ADC pin (analog input) where the multiplexer's output is connected
adc_pin = ADC(26)  # ADC0 on GP26

# Function to select the channel on the multiplexer
def select_channel(channel):
    assert 0 <= channel <= 7, "Channel must be in the range 0-7"
    
    # Set the control pins to select the given channel
    s0.value(channel & 0x01)
    s1.value((channel >> 1) & 0x01)
    s2.value((channel >> 2) & 0x01)
    utime.sleep_ms(1)  # Small delay to let the multiplexer switch

# Function to read the value from the selected ADC channel
def read_soil_moisture(channel):
    select_channel(channel)  # Select the multiplexer channel
    adc_value = adc_pin.read_u16()  # Read the ADC value (16-bit)
    return adc_value

# Main loop
while True:
    for i in range(8):  # Now iterating over 8 sensors
        moisture_level = read_soil_moisture(i)
        print(f"Moisture level at sensor {i}: {moisture_level}")
    utime.sleep(2)  # Wait for 2 seconds before reading again