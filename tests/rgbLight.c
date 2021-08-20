#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <stdint.h>
#include <semaphore.h>

#include "../gpio.h"

#define  C0 0x84
#define  C1 0xC4
#define  C2 0x94

int readADC(char channel);
void *color_thread_fun(void *arg);
void *potentio_thread_fun(void *arg);


struct color_control {
    uint8_t value;
    unsigned char channel;
};

struct potentio_meter {
    char channel;
    struct color_control *assigned_color;
};

sem_t m1, m2;
char *filename = "/dev/i2c-1";
void main() {

    gpio_init();
    gpio_setMode(17, OUT);
    gpio_setMode(13, OUT);
    gpio_setMode(19, OUT);
    struct color_control color_red = {0, 17};
    struct color_control color_green = {0, 13};
    struct color_control color_blue = {0, 19};

    struct potentio_meter meter_1 = {C0, &color_red};
    struct potentio_meter meter_2 = {C1, &color_green};
    struct potentio_meter meter_3 = {C2, &color_blue};

    sem_init(&m1, 0 , 1);
    sem_init(&m2, 0 , 1);
    pthread_t rt, bt, gt;
    pthread_t pt1, pt2, pt3;

    pthread_create(&pt1, NULL, potentio_thread_fun, (void *)&meter_1);
    pthread_create(&pt2, NULL, potentio_thread_fun, (void *)&meter_2);
    pthread_create(&pt3, NULL, potentio_thread_fun, (void *)&meter_3);
    pthread_create(&rt, NULL, color_thread_fun, (void *)&color_red);
    pthread_create(&bt, NULL, color_thread_fun, (void *)&color_blue);
    pthread_create(&gt, NULL, color_thread_fun, (void *)&color_green);

    //join them all
    pthread_join(pt1, NULL);
}


void *color_thread_fun(void *arg) {
    struct color_control *color = (struct color_control *) arg;
    struct timespec tim;
    tim.tv_sec = 0;
    while(1) {
        if(color->value == 0) {continue; }
        gpio_write(color->channel, 0);
        tim.tv_nsec = color->value * 10000;
        nanosleep(&tim, NULL);
        gpio_write(color->channel, 1);
        tim.tv_nsec = 2540000 - (color->value * 10000);
        nanosleep(&tim, NULL);
    }
}
void *potentio_thread_fun(void *arg) {
    struct potentio_meter *meter = (struct potentio_meter *) arg;
    struct timespec tim;
    tim.tv_nsec = 3000000;
    tim.tv_sec = 0;
    char reader[1] = {0};
    char data[1];
    data[0] = meter->channel;
    int fd = open(filename, O_RDWR);
    if(fd < 0) {
        exit(-1);
    }
    if(ioctl(fd, I2C_SLAVE, 0x4b) < 0) {
        exit(-1);
    }
    while(1) {
        sem_wait(&m2);
        write(fd, data, 1);
        read(fd, reader, 1);
        int adc = reader[0];
        meter->assigned_color->value = adc;
        sem_post(&m2);
        usleep(20000);
    }
}
