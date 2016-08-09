    const int LAST_PIN = 11;
    const int out_PIN = 13;
    volatile int tick;
    #define Serial Serial1
    bool State=HIGH;

    void ding() {
      tick++;
      State!=State;
      digitalWrite(13,State);
     
    }

    void setup() {
        pinMode(LAST_PIN, INPUT_PULLUP);
        attachInterrupt(LAST_PIN, ding, FALLING);
      pinMode(out_PIN, OUTPUT);
      Serial.begin(9600);
    }

    void loop() {
      Serial.print(" digital read:  ");
      delay(1000);
     
       
          Serial.print(digitalRead(11));
      Serial.print("  ");
      Serial.println(tick);
      tick = 0;
    }
