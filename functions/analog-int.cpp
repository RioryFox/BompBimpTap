int main (void) {
        uart_init(115200);

        uart_write("\r\n Bimp!\r\n");
        aurt_input(input, sizeof(input));
        uart_write("\r\n", input)
}