//  * Created: 16/05/2022 21:00:00
//  *  Author: Kaique Ferreira
//  */
/**
 *  QUESTION 4: Imagine that you have a microcontroller that communicates to a generic system that may
    consist of several other boards via UART. How do you guarantee each message you send is
    delivered correctly?
    Now imagine that you receive a message and an interruption is triggered every time a new
    information is received. Inside every message you have a different command, and for every
    command you have different payloads, receiving positive and negative values.
    Implement the interrupt and the parser functions in a generic way (low-level methods can be
    abstracted) using the C language and share this code through a public repository on GitHub.
 */

/**
 * R:Implement an Cyclic Redundance Code (CRC) checker and ask to resend the message when the CRC is broken.
 */ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define UART_PORT UART_NUM_2

struct message_protocol_struct
{
    uint16_t flag;
    uint16_t msg_size;
    uint16_t board_id;
    uint16_t command;
    char payload_string[256];
    uint16_t end_flag;
    uint16_t CRC;
};

uint16_t generateCrc(uint8_t *uart_buffer)
{
    /**
     * Function to generate CRC based on buffer received by the UART
    **/
    return crc;
}
uint16_t retrieveCrc(uint8_t *uart_buffer)
{
    /**
     * Function to separate CRC from the rest of the message received by the UART
    **/
    return crc;
}

bool isMessageValid(uint8_t *uart_buffer)
{
    uint16_t calculatedCrc = generateCrc((uint8_t *)uart_buffer);
    uint16_t receivedCrc = retrieveCrc((uint8_t *)uart_buffer);

    return calculatedCrc == receivedCrc ? true : false;
}

struct message_protocol_struct separateReceivedMessageFromUart(uint8_t *data)
{
    int payload_size = 0;
    struct message_protocol_struct message;
    uint8_t bytesBeforePayload = 8;
    uint8_t bytesAfterPayload = 4;
    message.flag = data[1] + (data[0] << 8);
    message.msg_size = data[3] + (data[2] << 8);
    message.board_id = data[5] + (data[4] << 8);
    message.command = data[7] + (data[5] << 8);
    for (int i = bytesBeforePayload; i < message.msg_size - bytesAfterPayload; i++)
    {
        message.payload_string[i - bytesBeforePayload] = data[i];
        payload_size++;
    }
    message.end_flag = data[message.msg_size - 3] + (data[message.msg_size - 4] << 8);
    message.CRC = data[message.msg_size - 1] + (data[message.msg_size - 2] << 8);

    return message;
}

void uartReadError() {
    //
}

void processReceivedMessageFromUart(struct message_protocol_struct message) {
    swith(message.command){
        case 1:
        //Something
        break;
        case 2:
        //Something else
        // ...
        break;
        default:
            ESP_LOGE(ESP_HOST_PROTOCOL_TAG, "NOT A VALID COMMAND CODE!");
    }

}

void uartReadAndProcess()
{
    uint8_t *uart_buffer = (uint8_t *)malloc(BUF_SIZE);

    int messageLength = uart_read_bytes(UART_PORT, uart_buffer, BUF_SIZE, 20 / portTICK_RATE_MS);
    if (messageLength > 1 && messageLength < MAX_RECEIVED_UART_BUFFER_SIZE) {
        if (!isMessageValid(uart_buffer)) {
            uartReadError();
            return;
        }

        struct message_protocol_struct message_received_from_uart = separateReceivedMessageFromUart(uart_buffer);            
        processReceivedMessageFromUart(message_received_from_uart);
        vTaskDelete(NULL);
    } 
    uartReadError()

    vTaskDelete(NULL);
}

static void IRAM_ATTR isr_function(void *arg)
{
    xTaskCreate(uartReadAndProcess, "uartReadAndProcess", 8192, NULL, 2, NULL); // Create task that will Read and process every buffer received.
}
