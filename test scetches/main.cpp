int main (void) {
        //char input[64] = {0};
        //uart_init(115200);

        //while (1){
        //        uart_write("\r\n Bimp!\r\n");
        //        aurt_input(input, sizeof(input));
        //        uart_write("\r\n");
        //        uart_write(input);
        //};

        Serial.begin(115200);
        Serial.println("Hello");
        delay(1500);
};