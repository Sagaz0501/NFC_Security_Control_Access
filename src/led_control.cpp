#include <led_control.h>

/*
    Led pins:
    D6 - Red Led
    D7 - Green Led
    D8 - White Led
*/

void led_setup() {

    // Initialize LED pins

    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(LED_GREEN_PIN, OUTPUT);
    pinMode(LED_WHITE_PIN, OUTPUT);

    // Turn off all LEDs initially
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_WHITE_PIN, LOW);
}

void led_booting(){
    // booting sequence: All leds blink and white stays on
    for(int i = 0; i < 3; i++){
        digitalWrite(LED_RED_PIN, HIGH);
        digitalWrite(LED_GREEN_PIN, HIGH);
        digitalWrite(LED_WHITE_PIN, HIGH);
        delay(300);
        digitalWrite(LED_RED_PIN, LOW);
        digitalWrite(LED_GREEN_PIN, LOW);
        digitalWrite(LED_WHITE_PIN, LOW);
        delay(300);
    }
    digitalWrite(LED_WHITE_PIN, HIGH); // White LED stays on
    Serial.println("LED: Booting sequence completed.");
    Serial.println("================= White led ON =================");
}

void led_detection(){
    // Detection sequence: Green led blinks 3 times
    for(int i = 0; i < 3; i++){
        digitalWrite(LED_GREEN_PIN, HIGH);
        delay(200);
        digitalWrite(LED_GREEN_PIN, LOW);
        delay(200);
    }
    Serial.println("LED: Detection sequence completed.");
}

void led_denied(){
    // Denied sequence: Red led blinks 3 times
    for(int i = 0; i < 3; i++){
        digitalWrite(LED_RED_PIN, HIGH);
        delay(200);
        digitalWrite(LED_RED_PIN, LOW);
        delay(200);
    }
    Serial.println("LED: Denied sequence completed.");
}

void led_granted(){
    // Granted sequence: Green led stays on for 3 seconds
    digitalWrite(LED_GREEN_PIN, HIGH);
    Serial.println("LED: Granted sequence started - Green led ON for 3 seconds.");
    delay(3000);
    digitalWrite(LED_GREEN_PIN, LOW);
    Serial.println("LED: Granted sequence completed - Green led OFF.");
}

// Future possible implementations:
// void led_warning(){
//     // Warning sequence: Red and Green leds blink
// }
// void led_reboot(){
//     // Reboot sequence: All leds blink continuously
// }
