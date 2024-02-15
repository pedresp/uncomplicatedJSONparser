#ifndef __UJP__UTILS__
#define __UJP__UTILS__

namespace ujp{
    bool is_digit(char car){
        return car >= 48 && car <= 58;
    }
    bool is_delimiter(char car){
        return car == ' ' || car == '\n' || car == '\t'; 
    }
}

#endif