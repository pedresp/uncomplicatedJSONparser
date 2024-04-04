#include "ujp_exception.hpp"

namespace ujp {
badformat_Exception::badformat_Exception() : std::exception() {}

Key_Error::Key_Error() : message("Wrong key introduced, that key does not exist or has other type\n") {}
const char *Key_Error::what() const noexcept { return message.c_str(); }
} // namespace ujp