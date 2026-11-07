#define SAMPLE_RATE 4800U
#define BUFFER_SIZE 1024U

int32_t input_buffer[BUFFER_SIZE * 2];
int32_t output_buffer[BUFFER_SIZE * 2];
alignas(4) uint32_t audioBuffer[32];

I2S_InputHandle hi2s2 = {};