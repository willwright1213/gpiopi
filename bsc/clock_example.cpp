#include "lcd.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
// LCD Logic

int main()
{
    try {
        BSC i2C{0x27};
        LCD lcd{&i2C};
        std::time_t t = std::time(nullptr);
        std::string time;
        while(1)
        {
            std::stringstream buffer;
            t = std::time(nullptr);
            buffer << std::put_time(std::localtime(&t), "%T");
            lcd.send_message(buffer.str());
            buffer.flush();
            usleep(1000000);
        }
    }
    catch(int e) {
        std::cout << std::strerror(errno) << '\n';
    }
}

