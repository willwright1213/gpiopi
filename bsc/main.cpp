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
        std::string buffer;
        std::string mess;
        char c;
        while(std::cin >> buffer) {
            mess += buffer + ' ';
            while(c = std::cin.get()) {
                if(c == '\n')
                {
                    if(mess.size() > 1) mess.pop_back(); 
                    lcd.send_message(mess);
                    mess = "";
                    break;
                }
                else if (c != ' '){
                    std::cin.putback(c);
                    break;
                }
            }
        }
    }
    catch(int e) {
        std::cout << std::strerror(errno) << '\n';
    }
}

