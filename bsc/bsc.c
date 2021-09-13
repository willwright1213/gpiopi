#include "bsc.h"
#include <sys/mman.h>
#include <cerrno>
#include <fcntl.h>
#include <cstddef>
#include <unistd.h>

BSC::BSC(std::uint8_t sa)
{
    int fd;
    fd = open("/dev/mem", O_RDWR); 
    addr = (std::uint32_t *) mmap(nullptr, 32, PROT_READ | PROT_WRITE, MAP_SHARED_VALIDATE, fd, BSC1_ADDR);
    if ((int) addr == -1) throw errno;
    addr[S] |= (1 << 8); //clear ACK Err
    addr[A] = sa;
    addr[C] |= (1 << 15); //enable BSC
    addr[DIV] = 556;
    addr[DEL] = (10 << 16);
    close(fd);
}

std::int8_t BSC::enable_i2c()
{
    addr[C] |= (1 << 15);
    return msync(addr, 32, MS_SYNC);
}

std::int8_t BSC::disable_i2c()
{
    addr[C] &= ~(1 << 15);
    return msync(addr, 32, MS_SYNC);
}

// Set the Control register to writing mode
std::int8_t BSC::set_write()
{
    addr[C] &= ~(1); //set writing mode
    return msync(addr, 32, MS_SYNC);
}

// Set the Control register to reading mode
std::int8_t BSC::set_read()
{
    addr[C] |= (1 << 0);
    return msync(addr, 32, MS_SYNC);
}

// Set the Control regiser to clear.
// One-shot operation will automatically execute if i2c is enabled
std::int8_t BSC::set_clear()
{
    addr[C] |= (1 << 4);
    return msync(addr, 32, MS_SYNC);
}

// Will start the transfer if i2c is enabled or wait if disabled.
// One-shot operation that will always read back as 0.
std::int8_t BSC::start()
{
    addr[C] |= (1 << 7);
    return msync(addr, 32, MS_SYNC);
}

// Clear and start can be set at the same time.
// The FIFO will be cleared before the transfer starts.
// Does nothing and return 0 is i2c is enabled.
std::int8_t BSC::clear_start()
{
    if((addr[C] >> 15)&1 == 1) return 0;
    addr[C] |= (1 << 4);
    addr[C] |= (1 << 7);
    return msync(addr, 32, MS_SYNC);
}

std::int8_t BSC::done_status() { return (addr[S] >> 1)&1; }

std::int8_t BSC::clear_done()
{
    addr[S] |= (1 << 1);
    return msync(addr, 32, MS_SYNC);
}

std::int8_t BSC::trans_status() { return addr[S] & 1;}

void BSC::set_dlen(int16_t len) { addr[DLEN] = len; msync(addr, 32, MS_SYNC);}
void BSC::write_fifo(int32_t data) { addr[FIFO] = data; msync(addr, 32, MS_SYNC);}
uint32_t BSC::read_fifo() { return addr[FIFO]; }

void BSC::clear_map() { munmap(addr, 32); }
