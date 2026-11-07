#define SAMPLE_RATE 4800U
#define BUFFER_SIZE 1024U

int32_t input_buffer[BUFFER_SIZE * 2];
int32_t output_buffer[BUFFER_SIZE * 2];
uint16_t audioBuffer[64];

I2S_InputHandle hi2s2 = {};