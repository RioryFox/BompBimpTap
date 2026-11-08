#include <Arduino.h>
#include "stm32h7xx_hal.h"

// STM32H723 / SPI2 (I2S2) master receiver.
// Hardware passthrough: WM8782 DOUT -> CS4344 SDIN via purple bus.
// SPI2 receives a copy; it does NOT transmit to the DAC.
I2S_HandleTypeDef hi2s2 = {};
alignas(4) uint32_t audioBuffer[32] = {};
bool i2sReady = false;

void setup() {
    Serial.begin(115200);
    delay(1000);

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_SPI2_CLK_ENABLE();

    // PB12 = LRCLK (yellow), PB13 = BCLK (green), PB14 = DATA (purple)
    GPIO_InitTypeDef gpioB = {};
    gpioB.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
    gpioB.Mode = GPIO_MODE_AF_PP;
    gpioB.Pull = GPIO_NOPULL;
    gpioB.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpioB.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOB, &gpioB);

    // PC6 = MCLK (black)
    GPIO_InitTypeDef gpioC = {};
    gpioC.Pin = GPIO_PIN_6;
    gpioC.Mode = GPIO_MODE_AF_PP;
    gpioC.Pull = GPIO_NOPULL;
    gpioC.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpioC.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOC, &gpioC);

    uint32_t clockHz = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI123);
    Serial.print("SPI123 clock: ");
    Serial.println(clockHz);
    if (clockHz == 0) {
        Serial.println("ERROR: No SPI123 kernel clock");
        return;
    }

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
    Serial.println("Passthrough: WM8782 DOUT to CS4344 SDIN (hardware bus)");
}

void loop() {
    if (!i2sReady) {
        delay(1000);
        return;
    }

    // On STM32H7 master RX, MCLK/BCLK/LRCLK run continuously
    // once HAL_I2S_Receive starts I2S, including between calls.
    HAL_StatusTypeDef status = HAL_I2S_Receive(
        &hi2s2,
        reinterpret_cast<uint16_t*>(audioBuffer),
        32,
        100
    );

    // Log once per second. No 100 ms pause in the reception loop.
    static uint32_t lastPrint = 0;
    uint32_t now = millis();
    if (now - lastPrint >= 1000) {
        lastPrint = now;
        Serial.print("RX status: ");
        Serial.print((int)status);
        Serial.print(" | HAL error: 0x");
        Serial.print(HAL_I2S_GetError(&hi2s2), HEX);
        Serial.print(" | raw: 0x");
        Serial.print(audioBuffer[0], HEX);
        Serial.print(" 0x");
        Serial.println(audioBuffer[1], HEX);
    }
}

