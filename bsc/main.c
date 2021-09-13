#include "lcd.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <string>

// LCD Logic

int main()
{
    try {
        BSC i2C{0x27};
        LCD lcd{&i2C};
        std::string mess;
        while(std::cin >> mess) {
            lcd.send_message(mess);
        }
    }
    catch(int e) {
        std::cout << std::strerror(errno) << '\n';
    }
}

