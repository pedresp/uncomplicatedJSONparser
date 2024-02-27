#ifndef __UJP__EXCEPTION__
#define __UJP__EXCEPTION__

#include "ujp_exception.hpp"
#include <string>
namespace ujp {
class badformat_Exception : public std::exception {
public:
  badformat_Exception() : std::exception() {}
};
} // namespace ujp

#endif