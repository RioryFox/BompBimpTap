#include "../../header/profiles.h"
#include "../../header/components.h"
#include <Arduino.h>
#include "stm32f4xx_hal.h"

I2S_HandleTypeDef hi2s2 = {};
uint16_t audioBuffer[64];

void setup() {
    Serial.begin(115200);

    // Включаем тактирование GPIOB и SPI2
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_SPI2_CLK_ENABLE();

    // PB12 = LRCK, PB13 = BICK, PB15 = DATA
    GPIO_InitTypeDef gpio = {};
    gpio.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_15;
    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio.Alternate = GPIO_AF5_SPI2;

    HAL_GPIO_Init(GPIOB, &gpio);

    // Настройка I2S2 на приём
    hi2s2.Instance = SPI2;
    hi2s2.Init.Mode = I2S_MODE_SLAVE_RX;
    hi2s2.Init.Standard = I2S_STANDARD_PHILIPS;
    hi2s2.Init.DataFormat = I2S_DATAFORMAT_24B;
    hi2s2.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
    hi2s2.Init.AudioFreq = I2S_AUDIOFREQ_96K;
    hi2s2.Init.CPOL = I2S_CPOL_LOW;
    hi2s2.Init.ClockSource = I2S_CLOCK_PLL;
    hi2s2.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;

    if (HAL_I2S_Init(&hi2s2) != HAL_OK) {
        Serial.println("I2S INIT ERROR");
    }
}


void loop() {
    HAL_StatusTypeDef status = HAL_I2S_Receive(
        &hi2s2,
        audioBuffer,
        32,
        100
    );

    if (status == HAL_OK) {
        Serial.print("Raw: ");
        Serial.print(audioBuffer[0]);
        Serial.print(" ");
        Serial.println(audioBuffer[1]);
    } else {
        Serial.print("RX error: ");
        Serial.println((int)status);
    }

    delay(100);
}

