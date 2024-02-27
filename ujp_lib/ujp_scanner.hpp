#ifndef __UJP_SCANNER__
#define __UJP_SCANNER__

#include "ujp_json.hpp"
#include <istream>
#include <string>

#include <stack>

namespace ujp {
class JSON;
class Scanner {
private:
  static parserStates state1(std::stack<JSON *> &stack, std::istream &input);
  static parserStates state2(std::stack<JSON *> &stack, std::istream &input);
  static parserStates state3(std::stack<JSON *> &stack, std::istream &input, std::string &str);
  static parserStates state4(std::stack<JSON *> &stack, std::istream &input, std::string &str);
  static parserStates state5(std::stack<JSON *> &stack, std::istream &input, std::string &str);
  static parserStates state6(std::stack<JSON *> &stack, std::istream &input, std::string &str);
  static parserStates state7(std::stack<JSON *> &stack, std::istream &input, std::string &str);
  static parserStates state8(std::stack<JSON *> &stack, std::istream &input);
  static parserStates state9(std::stack<JSON *> &stack, std::istream &input, std::string &str);
  static parserStates state10(std::stack<JSON *> &stack, std::istream &input, std::string &str);
  static parserStates state11(std::stack<JSON *> &stack, std::istream &input);
  static parserStates state12(std::stack<JSON *> &stack, std::istream &input);

public:
  static parserStates parse(JSON &json, std::istream &input);
};
} // namespace ujp

#endif