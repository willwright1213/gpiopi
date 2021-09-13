#include <cstdint>

constexpr std::uint32_t BSC0_ADDR = 0x0fe205000;
constexpr std::uint32_t BSC1_ADDR = 0x0fe804000;
constexpr std::uint32_t BSC3_ADDR = 0x0fe205600;
constexpr std::uint32_t BSC4_ADDR = 0x0fe205800;
constexpr std::uint32_t BSC5_ADDR = 0x0fe205a80;
constexpr std::uint32_t BSC6_ADDR = 0x0fe205c00;

//Offset definition
constexpr std::uint8_t C = 0x00; //Control
constexpr std::uint8_t S = 0x01; //Status
constexpr std::uint8_t DLEN = 0x02; // Data length
constexpr std::uint8_t A = 0x03; // Slave Address
constexpr std::uint8_t FIFO = 0x04; // Data FIFO
constexpr std::uint8_t DIV = 0x05; // Clock Divider
constexpr std::uint8_t DEL = 0x06; // Data Delay
constexpr std::uint8_t CLKT = 0x07; // Clock Stretch Timeout

class BSC
{
private:
    std::uint8_t slave_address;
    std::uint32_t * addr;
public:
    BSC(uint8_t sa);
    std::int8_t enable_i2c();
    std::int8_t disable_i2c();
    std::int8_t set_write();
    std::int8_t set_read();
    std::int8_t set_clear();
    std::int8_t start();
    std::int8_t clear_start();
    std::int8_t trans_status();
    std::int8_t done_status();
    std::int8_t clear_done();
    void set_dlen(int16_t len);
    void write_fifo(int32_t data);
    std::uint32_t read_fifo();
    void clear_map();
};



