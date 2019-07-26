#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#include "lora.h"
#include <wiringPi.h>

/**
 * 初始化操作
 */
void init()
{
    printf("Start Init");
    wiringPiSetup();

    printf("Start Pin Init");
    pinMode(PIN_RESET, OUTPUT);
    pinMode(PIN_MOSI, OUTPUT);
    pinMode(PIN_MISO, INPUT);
    pinMode(PIN_CLK, OUTPUT);
    pinMode(PIN_CS, OUTPUT);

    printf("Finish Pin Init");

    printf("Start Reset");
    //重置复位
    digitalWrite(PIN_RESET, HIGH);
    delay(1000);
    digitalWrite(PIN_RESET, LOW);
    printf('Finish Reset')
}
/**
 * 时钟信号
 */
void SCK_LOW()
{
    digitalWrite(PIN_CLK, LOW);
}
void SCK_HIGH()
{
    digitalWrite(PIN_CLK, HIGH);
}
/**
 * 片选信号
 */
void SSN_LOW()
{
    digitalWrite(PIN_CS, LOW);
}
/**
 * 片选信号
 */
void SSN_HIGH()
{
    digitalWrite(PIN_CS, HIGH);
}

void MOSI_LOW()
{
    digitalWrite(PIN_MOSI, LOW);
}
void MOSI_HIGH()
{
    digitalWrite(PIN_MOSI, HIGH);
}

/**
 * 发送SPI数据
 */
void SPI_Send(unsigned char dat)
{
    unsigned char n;
    for (n = 0; n < 8; n++)
    {
        SCK_LOW();
        if (dat & 0x80)
            MOSI_HIGH();
        else
            MOSI_LOW();
        dat <<= 1;
        SCK_HIGH();
    }
    SCK_LOW();
}
/**
 * 接收SPI数据
 */
unsigned char SPI_Rec()
{
    unsigned char n, dat;
    for (n = 0; n < 8; n++)
    {
        SCK_LOW();
        dat <<= 1;
        if (digitalRead(PIN_MISO) == 1) //需要修改为系统读取IO口函数
            dat |= 0x01;
        else
            dat &= 0xfe;
        SCK_HIGH();
    }
    SCK_LOW();
    return (dat);
}
/**
 * 发送数据
 */
void LoraWrite(uint8_t addr, uint8_t data, uint8_t size)
{
    uint8_t i;

    SSN_LOW();

    SPI_Send(addr | 0x80);
    for (i = 0; i < size; i++)
    {
        SPI_Send(buffer[i]);
    }

    SSN_HIGH();
}
/**
 * 读取数据
 */
void LoraRead(uint8_t addr, uint8_t *dat, uint8_t size)
{

    uint8_t i;

    SSN_LOW();

    SPI_Send(addr & 0x7F);
    for (i = 0; i < size; i++)
    {
        buffer[i] = SPI_Rec(); // Store data from last data RX
    }

    SSN_HIGH();
}