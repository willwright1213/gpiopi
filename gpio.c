#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdint.h>

#include "gpio.h"

int32_t *gpio = (int32_t *) -1;

void gpio_init(void) {
    int fd = open("/dev/gpiomem", O_RDWR);
    if(fd < 0) return;
    gpio = (int32_t *) mmap(0, SIZE_OF_REGISTER,
            PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
}

char gpio_read(unsigned char pin) {
    if (gpio == (int32_t *) -1) return -1;
    if(pin > 57) return -1;
    return (gpio[GPLEV0/4 + pin/32] & (1 << pin)) >> pin ;    
}

/* Nothing will happen if pin is not OUT mode and value is not 0 or 1 */
void gpio_write(unsigned char pin, unsigned char value) {
    if (gpio == (int32_t *) -1) return;
    if (pin > 57) return;
    if(value == 0) {
        gpio[GPCLR0/4 + pin/32] = 1 << (pin % 32);
        msync(&gpio[GPCLR0/4 + pin/32], sizeof(uint32_t), MS_ASYNC);
        return;
    }
    else if(value == 1) {
        gpio[GPSET0/4 + pin/32] = 1 << (pin % 32);
        msync(&gpio[GPSET0/4 + pin/32], sizeof(uint32_t), MS_ASYNC);
        return;
    }
}

void gpio_setMode(unsigned char pin, unsigned char mode) {
    if(mode > 0x07) return;
    if(pin > 57) return;
    if(gpio == (int32_t *) -1) return; 
    for(int i = 0; i < 3; i++) {
        if((mode & (1 << i)) >> i == 1) {
            gpio[GPFSEL0/4 + pin/10] |= (1 << ((pin % 10) * 3 + i));
        }
        else {
            gpio[GPFSEL0/4 + pin/10] &= ~(1 << ((pin % 10) * 3 + i));
        }
    }
    msync(&gpio[GPFSEL0/4 + pin/10], sizeof(uint32_t), MS_ASYNC);
}
