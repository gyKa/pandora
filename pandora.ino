const unsigned int PIN_LED_BLUE = 9;
const unsigned int PIN_LED_RED = 10;

const unsigned int MAX_BRIGHT = 255;
const unsigned int MIN_BRIGHT = 0;

const unsigned int SECOND = 1000; // miliseconds
const unsigned int MINUTE = SECOND * 60;
const unsigned long HOUR = MINUTE * 60L;

const unsigned int DELAY_INTERVAL = SECOND;

const unsigned long WATER_INTERVAL = HOUR * 2L;
const unsigned long WATER_INTERVAL_PRE = WATER_INTERVAL - MINUTE * 5L;
const unsigned long WATER_INTERVAL_PRE_DIFF = WATER_INTERVAL - WATER_INTERVAL_PRE;
const unsigned long WATER_INTERVAL_POST = WATER_INTERVAL + MINUTE * 5L;
const unsigned long WATER_INTERVAL_POST_DIFF = WATER_INTERVAL + WATER_INTERVAL_POST;

boolean is_led_blue_on = false;

void verbose() {
    unsigned long current_time = millis();
    
    unsigned int hours = current_time / HOUR;
    unsigned int minutes = (current_time % HOUR) / MINUTE;
    unsigned int seconds = ((current_time % HOUR) % MINUTE) / SECOND;
    
    Serial.print(hours, DEC);
    Serial.print(":");
    Serial.print(minutes, DEC);
    Serial.print(":");
    Serial.print(seconds, DEC);
    Serial.println();
}

int get_led_blue_bright() {
    unsigned long current_time = millis();
    unsigned int led_blue_bright = MIN_BRIGHT;
    
    if (current_time > WATER_INTERVAL_PRE && current_time < WATER_INTERVAL) {
        led_blue_bright = (current_time - WATER_INTERVAL_PRE) * MAX_BRIGHT / WATER_INTERVAL_PRE_DIFF;
    } else if (current_time > WATER_INTERVAL && current_time < WATER_INTERVAL_POST) {
        led_blue_bright = MAX_BRIGHT;
    } else if (current_time > WATER_INTERVAL_POST) {
        if (is_led_blue_on) {
            led_blue_bright = MAX_BRIGHT;
            is_led_blue_on = false;
        } else {
            led_blue_bright = MIN_BRIGHT;
            is_led_blue_on = true;
        }
    }
    
    return led_blue_bright;
}

// The setup function runs once when you press reset or power the board.
void setup() {
    Serial.begin(9600);
    
    pinMode(PIN_LED_BLUE, OUTPUT);
    pinMode(PIN_LED_RED, OUTPUT);
}

// The loop function runs over and over again forever.
void loop() {
    verbose();
    analogWrite(PIN_LED_BLUE, get_led_blue_bright());
    analogWrite(PIN_LED_RED, MAX_BRIGHT);
    delay(DELAY_INTERVAL);
}

