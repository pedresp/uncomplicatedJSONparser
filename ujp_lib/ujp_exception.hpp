#ifndef __UJP__EXCEPTION__
#define __UJP__EXCEPTION__

#include <exception>

namespace ujp{
    class badformat_Exception : public std::exception{
        public:
            badformat_Exception(){}
    };
}

#endif