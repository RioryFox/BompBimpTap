#include <Arduino.h>
#include "stm32h7xx_hal.h"

I2S_HandleTypeDef hi2s2 = {};
alignas(4) uint32_t audioBuffer[32] = {};

bool i2sReady = false;

void setup() {
    Serial.begin(115200);
    delay(1000);

    // Включаем тактирование портов и SPI2
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_SPI2_CLK_ENABLE();

    // PB12 = LRCK, PB13 = BICK, PB14 = DATA
    GPIO_InitTypeDef gpioB = {};
    gpioB.Pin = GPIO_PIN_12 |
                GPIO_PIN_13 |
                GPIO_PIN_14;
    gpioB.Mode = GPIO_MODE_AF_PP;
    gpioB.Pull = GPIO_NOPULL;
    gpioB.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpioB.Alternate = GPIO_AF5_SPI2;

    HAL_GPIO_Init(GPIOB, &gpioB);

    // PC6 = I2S2_MCK (MCLK output)
    GPIO_InitTypeDef gpioC = {};
    gpioC.Pin = GPIO_PIN_6;
    gpioC.Mode = GPIO_MODE_AF_PP;
    gpioC.Pull = GPIO_NOPULL;
    gpioC.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpioC.Alternate = GPIO_AF5_SPI2;

    HAL_GPIO_Init(GPIOC, &gpioC);

    // Диагностика входного тактирования I2S2
    uint32_t clockHz =
        HAL_RCCEx_GetPeriphCLKFreq(
            RCC_PERIPHCLK_SPI123
        );

    Serial.print("SPI123 clock: ");
    Serial.println(clockHz);

    if (clockHz == 0) {
        Serial.println("ERROR: No SPI123 kernel clock");
        return;
    }

    // STM32 генерирует такты и принимает аудио
    hi2s2.Instance = SPI2;
    hi2s2.Init.Mode = I2S_MODE_MASTER_RX;
    hi2s2.Init.Standard = I2S_STANDARD_PHILIPS;
    hi2s2.Init.DataFormat = I2S_DATAFORMAT_24B;
    hi2s2.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
    hi2s2.Init.AudioFreq = I2S_AUDIOFREQ_96K;
    hi2s2.Init.CPOL = I2S_CPOL_LOW;

    HAL_StatusTypeDef status = HAL_I2S_Init(&hi2s2);

    if (status != HAL_OK) {
        Serial.print("I2S INIT ERROR: ");
        Serial.println((int)status);

        Serial.print("HAL error: 0x");
        Serial.println(HAL_I2S_GetError(&hi2s2), HEX);
        return;
    }

    i2sReady = true;
    Serial.println("I2S MASTER RX INITIALIZED");
}

void loop() {
    if (!i2sReady) {
        delay(1000);
        return;
    }

    HAL_StatusTypeDef status = HAL_I2S_Receive(
        &hi2s2,
        reinterpret_cast<uint16_t*>(audioBuffer),
        32,
        100
    );

    if (status == HAL_OK) {
        Serial.print("Raw: ");
        Serial.print(audioBuffer[0], HEX);
        Serial.print(" ");
        Serial.println(audioBuffer[1], HEX);
    } else {
        Serial.print("RX error: ");
        Serial.println((int)status);

        Serial.print("HAL error: 0x");
        Serial.println(HAL_I2S_GetError(&hi2s2), HEX);

        Serial.print("RX remaining: ");
        Serial.println(hi2s2.RxXferCount);

        Serial.print("SPI2 status: 0x");
        Serial.println(SPI2->SR, HEX);
    }

    delay(100);
}
