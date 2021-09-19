#include "lcd.h"
#include <unistd.h>
#include <iostream>

void LCD::send_byte(std::int32_t data)
{
    device->clear_done();
    device->set_clear();
    device->set_write();
    device->set_dlen(2);
    device->start();
    device->write_fifo(data); 
    device->write_fifo(0b00001000);
    while(device->trans_status() == 1); 
    while(device->done_status() == 0);
    usleep(1500);
}


// This command will send the 2 bytes of data necessary then block until
// the busy flag is set to 0. 
void LCD::send_command(std::int8_t d1, std::int8_t d2)
{
    send_byte(d1);
    send_byte(d2);
    while(poll_busy() == 1);
}

std::int32_t LCD::read_addr_counter()
{
    device->clear_done();
    device->set_clear();
    usleep(500);
    device->set_dlen(1);
    device->set_read();
    device->start();
    while(device->trans_status() == 1);
    while(device->done_status() == 0);
    return device->read_fifo(); 
}
std::int8_t LCD::poll_busy()
{
    usleep(500);
    return (read_addr_counter() >> 7)&1;
}

LCD::LCD(BSC *d)
{
    device = d;
    device->enable_i2c();
    usleep(60000);
    send_byte(0b00101100);
    while(poll_busy() == 1);
    send_command(0b00101100, 0b00001100);
    send_command(0b00001100, 0b11101100);
    send_command(0b00001100, 0b01101100);
    send_command(0b10001100, 0b00001100);
}

void LCD::send_message(const std::string message)
{
    send_command(0b00001100, 0b00011100);
    int32_t data = 0b00001101;
    for(char c: message)
    {
        int32_t upper = (c&0xF0) | data;
        int32_t lower = (c << 4) | data;
        send_command(upper, lower); 
    }
}
