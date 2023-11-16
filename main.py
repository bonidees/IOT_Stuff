'''In this script:
#We define a function connect_wifi() to handle Wi-Fi connection setup.
The send_to_ifttt() function generates a random digit and sends it to the configured IFTTT webhook URL.
Inside the main() function, we establish a Wi-Fi connection and then call send_to_ifttt() to send the random number.
Before running this script on your Raspberry Pi Pico W, make sure that:

You've updated the placeholders (your_wifi_ssid, your_wifi_password, your_event_name, and your_ifttt_key) with your actual Wi-Fi and IFTTT information.


http://maker.ifttt.com/trigger/test_event/with/key/cq0GyOhwJUh3cBXk4O0Gm6

'''

import network
import urequests
import urandom
import time
import machine



# Update these with your details
SSID = 'Capt. Benson'
PASSWORD = 'Dick Wolf'
IFTTT_WEBHOOK_URL = 'https://maker.ifttt.com/trigger/{event_name}/with/key/{your_ifttt_key}'
EVENT_NAME = 'test_event'
YOUR_IFTTT_KEY = 'cq0GyOhwJUh3cBXk4O0Gm6'


#setup LED
led = machine.Pin("LED", machine.Pin.OUT)



# Connect to Wi-Fi
def connect_wifi(ssid, password):
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    if not wlan.isconnected():
        print('Connecting to network...')
        wlan.connect(ssid, password)
        while not wlan.isconnected():
            pass
    print('Network connected!')
    print('IP Address:', wlan.ifconfig()[0])

# Send a random digit to the IFTTT webhook
def send_to_ifttt():
    led.on()
    random_digit = str(urandom.randint(0, 9))
    url = IFTTT_WEBHOOK_URL.replace('{event_name}', EVENT_NAME).replace('{your_ifttt_key}', YOUR_IFTTT_KEY)
    data = {"value1": random_digit}
    response = urequests.post(url, json=data)
    print('Random digit sent:', random_digit)
    print('Response:', response.text)
    led.off()


# Main program
def main():
    connect_wifi(SSID, PASSWORD)
    send_to_ifttt()
    
# Infinite loop to continuously run main() after 5 minutes sleep
while True:
    main()
    print('Sleeping for 5 minutes...')
    time.sleep(300)  # sleep for 5 minutes (300 seconds)



