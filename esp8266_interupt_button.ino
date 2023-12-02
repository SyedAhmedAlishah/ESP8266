struct Button {
    const uint8_t PIN;
    uint32_t numberKeyPresses;
    bool pressed;
};

Button button1 = {D6, 0, false};

//variables to keep track of the timing of recent interrupts
unsigned long button_time = 0;  
unsigned long last_button_time = 0; 

void ICACHE_RAM_ATTR isr() { // for just esp interrupt add ICACHE_RAM_ATTR before isr function
    button_time = millis();
if (button_time - last_button_time > 250)
{
        button1.numberKeyPresses++;
        button1.pressed = true;
       last_button_time = button_time;
}
}

void setup() {
    Serial.begin(115200);
    pinMode(button1.PIN, INPUT_PULLUP);
    pinMode(D8, OUTPUT);
    attachInterrupt(button1.PIN, isr, FALLING);
}

void loop() {
    digitalWrite(D8,HIGH);
    delay(100);
    digitalWrite(D8,LOW);
    delay(100);
    if (button1.pressed) {
        Serial.printf("Button has been pressed %u times\n", button1.numberKeyPresses);
        button1.pressed = false;
    }
}