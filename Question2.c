//  * Created: 16/05/2022 21:00:00
//  *  Author: Kaique Ferreira
//  */
/**
 *  QUESTION 2: Imagine a situation where you have an electronic board with a microcontroller and a button. You
    are required to if the button is pressed or not and for how long the button is pressed. If the button
    gets pressed, you also need to have a clear state definition ranging from ON, OFF and
    PROTECTED. The protected state is defined as an intermediate stage between ON and OFF, so
    that the button state becomes PROTECTED for 10 seconds each time the button is released.
    Implement this logic in a generic way (low-level methods can be abstracted) using the C language
    and share this code through a public repository on GitHub.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

#define DEBUG_ON

#define GPIO_BUTTON_INTERRUPT 4
#define ESP_INR_FLAG_DEFAULT 0

#define ESP_CORE_0 0

#define BUTTON_DEBUG_DELAY 500
#define BUTTON_PROTECT_DELAY 10000

#define BUTTON_DEBUG_PRIORITY 2
#define PROTECT_BUTTON_PRIORITY 10

TaskHandle_t button_handler = NULL;
TaskHandle_t protect_button_handler = NULL;

enum button
{
    OFF,
    ON,
    PROTECTED
};

#ifdef DEBUG_ON
const char *buttonEnumString[] = {"OFF", "ON", "PROTECTED"};
#endif

bool isButtonProtected = false;

static void protect_button() {
    isButtonProtected = true;
    vTaskDelay(pdMS_TO_TICKS(BUTTON_PROTECT_DELAY));
    isButtonProtected = false;
    vTaskDelete(NULL);
}

static void button_status() {
    int i = 0;
    enum button currentButtonStatus;
    enum button lastButtonStatus = OFF;

    for(;;){
        currentButtonStatus = isButtonProtected ? PROTECTED : gpio_get_level(GPIO_BUTTON_INTERRUPT);
    
        if(currentButtonStatus == OFF && lastButtonStatus == ON){
            currentButtonStatus = PROTECTED;
            xTaskCreatePinnedToCore(protect_button, "protect_button", 2048, NULL, PROTECT_BUTTON_PRIORITY, &protect_button_handler, ESP_CORE_0);
        }
        #ifdef DEBUG_ON
        printf("The button is %s - %i\n", buttonEnumString[currentButtonStatus], i++);
        #endif

        vTaskDelay(pdMS_TO_TICKS(BUTTON_DEBUG_DELAY));
        lastButtonStatus = currentButtonStatus;
    }
}

void app_main(void)
{
    gpio_config_t io_conf;
    // disable interrupt
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    // set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    // bit mask of the pins that you want to set,e.g.GPIO18/19
    // disable pull-down mode
    io_conf.pull_down_en = 0;
    // disable pull-up mode
    io_conf.pull_up_en = 0;
    // configure GPIO with the given settings
    gpio_config(&io_conf);

    gpio_install_isr_service(ESP_INR_FLAG_DEFAULT);

    xTaskCreatePinnedToCore(button_status, "button_status", 2048, NULL, BUTTON_DEBUG_PRIORITY, &button_handler, ESP_CORE_0);
}