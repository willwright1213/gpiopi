#define GPFSEL0 0x00 //for pin 0-9
#define GPSET0 0x1c //for pin 0-31
#define GPCLR0 0x28 //for pin 0-31
#define GPLEV0 0x34 //for pin 0-31

#define OUT 0x01
#define IN  0x00
#define ALT0 0x04
#define ALT1 0x05
#define ALT2 0x06
#define ALT3 0x07
#define ALT4 0x03
#define ALT5 0x02

#define SIZE_OF_REGISTER 0x38 //up to GPLEV0 only. We are not using anything after

void gpio_init(void);
void gpio_write(unsigned char pin, unsigned char value);
char gpio_read(unsigned char pin);
void gpio_setMode(unsigned char pin, unsigned char mode); 
