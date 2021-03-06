#include "bsc.h"
#include <string>

class LCD 
{
private:
    BSC *device;
    void send_byte(std::int32_t data);
    void send_command(std::int8_t d1, std::int8_t d2);
    std::int32_t read_addr_counter();
    std::int8_t poll_busy();

public:
    LCD(BSC *d);
    void send_message(const std::string message);
};
