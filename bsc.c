#include "bsc.h"

// Initiates the memory map. Returns bsc->map
int32_t *bsc_init(struct bsc_struct *bsc, int fd, int32_t addr) {
    bsc->map = (int32_t *)mmap(NULL, sysconf(_SC_PAGE_SIZE),
        PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0x0FE804000);
    bsc->addr = addr;
    return bsc->map;
}

//writes address of the peripheral to the A Register. if check is set to non-zero,
//it will perform a check right away to see if the address is valid by sending a test
//packet.
void write_address(struct bsc_struct *bsc, int peripheral_addr, char check) {
    bsc->map[1] = (1 << 8); //this clears the error bit to 0
    usleep(9000);
    if (bsc->map == (int32_t *) -1) return;
    bsc->map[ADDR] = peripheral_addr; 
    if(check) {
        bsc->map[DLEN] = 1;
        bsc->map[C] = 0b1000000010110000;
        usleep(5000);
        bsc->map[FIFO] = 0b1; 
        printf("%d\n", bsc->map[FIFO]);
        bsc->map[C] = 0b1000000000000000;
        usleep(50000);
        char ack = (bsc->map[1] & (1 << 8)) >> 8; 
        bsc->map[C] = 0b1000000000110000;
        usleep(50000);
        if(ack) {
            fprintf(stderr, " coul not find peripheral: %p\n", peripheral_addr);
            exit(-1);
        }
    }
}

void send_command(struct bsc_struct *bsc, char bytes) {
    bsc->map[C] = 0b1000000000110000;
    bsc->map[DLEN] = 1;
    bsc->map[FIFO] = 0b01101001;
    bsc->map[S] |= (1 << 1);
    bsc->map[S] |= (1 << 8);
    bsc->map[C] |= (1 << 7);
    while(((bsc->map[S] & (1 << 0)) >> 0) == 0); //polling
    while(((bsc->map[S] & (1 << 1)) >> 1) == 0); 
    if(((bsc->map[S] & (1 << 8)) >> 8) == 1){printf("error\n"); exit(-1);}//polling
    printf("%d\n", bsc->map[DLEN]);
    bsc->map[C] = 0b1000000000110000;
    while(((bsc->map[S] & (1 << 1)) >> 1) == 0); 
}

int main() {
    struct bsc_struct bsc;
    int fd = open("/dev/mem", O_RDWR|O_SYNC);
    if(fd == - 1) {
        fprintf(stderr, "error opening file\n");
        exit(-1);
    }
    bsc_init(&bsc, fd, BSC1_ADDRESS);
    send_command(&bsc, 0b01001100);
}
