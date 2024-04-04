#ifndef __UJP__EXCEPTION__
#define __UJP__EXCEPTION__

#include <exception>
#include <string>

namespace ujp {
class badformat_Exception : public std::exception {
public:
  badformat_Exception();
};

class Key_Error : public std::exception {
private:
  std::string message;

public:
  Key_Error();
  const char *what() const noexcept;
};
} // namespace ujp

#endif