from machine import I2C, ADC, Pin
import network
import urequests
import utime
import bme280
import tsl2591

# Initialize I2C interfaces using software I2C
temp_h_i2c = I2C(0, scl=Pin(21), sda=Pin(20))  # Example pin numbers for Temp/Humidity sensor
lux_i2c = I2C(1, scl=Pin(27), sda=Pin(26))     # Example pin numbers for Lux sensor

# Initialize BME280 sensor
bme = bme280.BME280(i2c=temp_h_i2c)

# Initialize TSL2591 lux sensor
tsl = tsl2591.TSL2591(i2c=lux_i2c)

# Initialize ADC for Soil Moisture Sensors
adc_pins = [28, 29, 30, 31, 32]  # Example pins for analog sensors
soil_sensors = [ADC(Pin(pin)) for pin in adc_pins]

def read_sensors():
    # Read from BME280 sensor
    temperature, pressure, humidity = bme.read_compensated_data()
    # Read from TSL2591 light sensor
    full, ir = tsl.get_full_luminosity()  # full spectrum and infrared
    lux = tsl.calculate_lux(full, ir)
    # Read from soil moisture sensors
    soil_moisture_values = [sensor.read_u16() for sensor in soil_sensors]
    
    # Bundle sensor data in a dictionary
    sensor_data = {
        'temperature': temperature,
        'pressure': pressure,
        'humidity': humidity,
        'lux': lux,
        'soil_moisture': soil_moisture_values
    }
    return sensor_data

# Placeholder for API endpoint
API_ENDPOINT = "http://example.com/api/sensor-data"

def send_sensor_data(sensor_data):
    # This function should handle POST request to your API endpoint with sensor data
    response = urequests.post(API_ENDPOINT, json=sensor_data)
    print(response.text)

# Example usage
while True:
    sensor_data = read_sensors()
    print(sensor_data)  # Print sensor data for testing
    
    # Placeholder for sending data to an API
    # Uncomment the line below when the actual API endpoint is set
    # send_sensor_data(sensor_data)
    
    utime.sleep(60)  # Delay for 60 seconds before reading again