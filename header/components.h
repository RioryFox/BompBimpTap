#define LED_PIN PG7

class LED_pin {
        public:
                LED_pin(LedPin){
                        this->LedPin = LedPin;
                        pinMode(LedPin, OUTPIN);
                };

                void TurnOn(){
                        digitalWrite(LedPin, HIGH);
                }

                void TurnOff(){
                        digitalWrite(LedPin, LOW);
                }
        private:
                LedPin = LED_PIN;
};

class InputAudioPlate {
        public:
                InputAudioPlate(){

                };
};