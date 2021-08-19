#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#define BSC1_ADDRESS 0xFE804000

//Register offsets
#define C 0x00/4
#define S 0x04/4
#define DLEN 0x08/4
#define ADDR 0x0C/4
#define FIFO 0x10/4
#define DIV 0x14/4
#define DEL 0x18/4
#define CLKT 0x1C/4

struct bsc_struct {
    int32_t addr;
    int32_t *map;
};

int32_t *bsc_init(struct bsc_struct *bsc, int fd, int32_t addr);
void write_address(struct bsc_struct *bsc, int peripheral_addr, char check);
int32_t read_address();
void control();
void clear();
void aknowledge();


