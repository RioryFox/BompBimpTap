#include <Arduino.h>
#include "stm32h7xx_hal.h"

void setup() {
    Serial.begin(115200);
    delay(1000);

    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef gpio = {};
    gpio.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
    gpio.Mode = GPIO_MODE_INPUT;
    gpio.Pull = GPIO_PULLUP;

    HAL_GPIO_Init(GPIOB, &gpio);

    Serial.println("GPIO TEST STARTED");
}

void loop() {
    Serial.print("PB12: ");
    Serial.print(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12));

    Serial.print(" | PB13: ");
    Serial.print(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13));

    Serial.print(" | PB14: ");
    Serial.println(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14));

    delay(500);
}

