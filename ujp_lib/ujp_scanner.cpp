#include "ujp_scanner.hpp"
#include "ujp_exception.hpp"
#include "ujp_json.hpp"
#include "ujp_utils.hpp"
#include <iostream>

#include <cmath>

using namespace ujp;
parserStates Scanner::parse(JSON &json, std::istream &input) {
  char c;
  input >> c;

  // std::cout << c;

  parserStates ps;
  std::stack<JSON *> stack;

  if (c == '{') {
    stack.emplace(&json);
    ps = Scanner::state1(stack, input);
    if (ps != CORRECT_PARSER)
      json.flush();

    // std::cout << std::endl;

    return ps;
  } else if (input.eof())
    return CORRECT_PARSER;
  return UNEXPECTED_CHAR;
}

parserStates Scanner::state1(std::stack<JSON *> &stack, std::istream &input) {
  char car;
  input >> car;

  // std::cout << car;

  if (car == '\"')
    return Scanner::state2(stack, input);
  else if (input.eof())
    return NO_BRACES_CLOSED;
  return UNEXPECTED_CHAR;
}

parserStates Scanner::state2(std::stack<JSON *> &stack, std::istream &input) {
  std::string key;
  char c;
  input.get(c);

  // std::cout << c;

  while (c != '\"' && !input.eof()) {
    key.push_back(c);
    input.get(c);

    // std::cout << c;
  }
  if (c == '\"')
    return Scanner::state3(stack, input, key);
  return UNCOMPLETED_JSON;
}

parserStates Scanner::state3(std::stack<JSON *> &stack, std::istream &input, std::string &key) {
  JSON &json = *stack.top();
  if (json.map.count(key) > 0)
    return DUPLICATED_KEY;
  char c;
  input >> c;

  // std::cout << c;

  if (c == ':')
    return Scanner::state4(stack, input, key);
  else if (input.eof())
    return UNCOMPLETED_JSON;
  return UNEXPECTED_CHAR;
}

parserStates Scanner::state4(std::stack<JSON *> &stack, std::istream &input, std::string &key) {
  JSON &json = *stack.top();
  char c;
  input >> c;

  // std::cout << c;

  if (c == '\"') {
    std::string my_str;
    json.map.insert(std::make_pair(key, std::make_pair(UJP_STRING, json.strings.size())));
    json.strings.push_back(my_str);
    return Scanner::state6(stack, input, key);
  } else if (is_digit(c)) {
    json.map.insert(std::make_pair(key, std::make_pair(UJP_NUMBER, json.numbers.size())));
    json.numbers.push_back(c - 48);
    return Scanner::state7(stack, input, key);
  } else if (c == '{') {
    json.map.insert(std::make_pair(key, std::make_pair(UJP_JSON, json.objects.size())));
    json.objects.push_back(JSON());
    stack.emplace(&json.objects[json.objects.size() - 1]);
    return Scanner::state1(stack, input);
  }

  return UNEXPECTED_CHAR;
}

parserStates Scanner::state6(std::stack<JSON *> &stack, std::istream &input, std::string &key) {
  JSON &json = *stack.top();
  char c;
  int pos = json.map[key].second;
  input.get(c);

  // std::cout << c;

  while (c != '\"' && !input.eof()) {
    json.strings[pos].push_back(c);
    input.get(c);

    // std::cout << c;
  }

  if (c == '\"')
    return Scanner::state8(stack, input);
  return UNCOMPLETED_JSON;
}

parserStates Scanner::state7(std::stack<JSON *> &stack, std::istream &input, std::string &key) {
  JSON &json = *stack.top();
  char my_numb;
  int pos = json.map[key].second;
  input.get(my_numb);

  // std::cout << my_numb;

  while (is_digit(my_numb)) {
    json.numbers[pos] = 10 * json.numbers[pos] + my_numb - 48;
    input.get(my_numb);

    // std::cout << my_numb;
  }

  if (my_numb == '.')
    return Scanner::state9(stack, input, key);

  if (is_delimiter(my_numb))
    input >> my_numb;
  // std::cout << my_numb;

  if (my_numb == '}') {
    if (stack.empty())
      return EXCESSIVE_RIGHT_BRACES;
    else
      stack.pop();
    return Scanner::state12(stack, input);
  } else if (my_numb == ',')
    return Scanner::state11(stack, input);
  return UNEXPECTED_CHAR;
}

parserStates Scanner::state8(std::stack<JSON *> &stack, std::istream &input) {
  char c;
  input >> c;

  // std::cout << c;

  if (c == '}') {
    if (stack.empty())
      return EXCESSIVE_RIGHT_BRACES;
    else
      stack.pop();
    return Scanner::state12(stack, input);
  } else if (c == ',')
    return Scanner::state11(stack, input);

  return UNEXPECTED_CHAR;
}

parserStates Scanner::state9(std::stack<JSON *> &stack, std::istream &input, std::string &key) {
  JSON &json = *stack.top();
  char c;
  input.get(c);

  // std::cout << c;

  if (is_digit(c)) {
    json.numbers[json.map[key].second] = json.numbers[json.map[key].second] + (c - 48) * 0.1;
    return Scanner::state10(stack, input, key);
  }
  return UNEXPECTED_CHAR;
}

parserStates Scanner::state10(std::stack<JSON *> &stack, std::istream &input, std::string &key) {
  JSON &json = *stack.top();
  char c;
  int pos = json.map[key].second;
  input.get(c);

  // std::cout << c;

  for (int i = -2; is_digit(c); i--) {
    json.numbers[pos] = json.numbers[pos] + pow(10, i) * (c - 48);
    input.get(c);

    // std::cout << c;
  }

  if (is_delimiter(c))
    input >> c;
  // std::cout << c;

  if (c == '}') {
    if (stack.empty())
      return EXCESSIVE_RIGHT_BRACES;
    else
      stack.pop();
    return Scanner::state12(stack, input);
  } else if (c == ',')
    return Scanner::state11(stack, input);

  return UNEXPECTED_CHAR;
}

parserStates Scanner::state11(std::stack<JSON *> &stack, std::istream &input) {
  char c;
  input >> c;

  // std::cout << c;

  if (c == '\"')
    return Scanner::state2(stack, input);
  return UNEXPECTED_CHAR;
}

parserStates Scanner::state12(std::stack<JSON *> &stack, std::istream &input) {
  char c;
  input >> c;

  // if (!input.eof())
  //  std::cout << c;

  if (c == ',')
    return Scanner::state1(stack, input);
  else if (c == '}') {
    if (stack.empty())
      return EXCESSIVE_RIGHT_BRACES;
    else
      stack.pop();
    return Scanner::state12(stack, input);
  }
  return CORRECT_PARSER;
}