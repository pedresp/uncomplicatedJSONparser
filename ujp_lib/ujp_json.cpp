#include "ujp_json.hpp"
#include "ujp_exception.hpp"
#include "ujp_scanner.hpp"
#include "ujp_utils.hpp"

ujp::JSON::JSON(std::istream &stream) { this->parseReturn = Scanner::parse(*this, stream); }
ujp::JSON::JSON() { this->parseReturn = NO_PREV_PARSER; }

void ujp::JSON::flush() {
  this->map.clear();
  this->numbers.clear();
  this->strings.clear();
  this->objects.clear();

  this->parseReturn = NO_PREV_PARSER;
}

double ujp::JSON::getNumber(std::string s) const {
  if (!this->map.count(s) || this->map.at(s).first != ujp::types::UJP_NUMBER)
    throw Key_Error();
  return this->numbers[this->map.at(s).second];
}

std::string ujp::JSON::getString(std::string s) const {
  if (!this->map.count(s) || this->map.at(s).first != ujp::types::UJP_STRING)
    throw Key_Error();
  return this->strings[this->map.at(s).second];
}

ujp::JSON &ujp::JSON::getJSON(std::string s) {
  if (!this->map.count(s) || this->map.at(s).first != ujp::types::UJP_JSON)
    throw Key_Error();
  return this->objects[this->map.at(s).second];
}

bool ujp::JSON::setNumber(std::string s, double num) {
  if (this->map.count(s) && this->map.at(s).first == UJP_NUMBER) {
    this->numbers[this->map.at(s).second] = num;
  } else if (this->map.count(s) == 0) {
    this->map.insert(std::make_pair(s, std::make_pair(ujp::UJP_NUMBER, this->numbers.size())));
    this->numbers.push_back(num);
  } else
    return false;

  return true;
}

bool ujp::JSON::setString(std::string s, std::string str) {
  if (this->map.count(s) && this->map.at(s).first == UJP_STRING) {
    this->strings[this->map.at(s).second] = str;
  } else if (this->map.count(s) == 0) {
    this->map.insert(std::make_pair(s, std::make_pair(ujp::UJP_STRING, this->strings.size())));
    this->strings.push_back(str);
  } else
    return false;
  return true;
}

bool ujp::JSON::setJSON(std::string s, ujp::JSON &json) {
  if (this->map.count(s) && this->map.at(s).first == UJP_JSON) {
    this->objects[this->map.at(s).second] = json;
  } else if (this->map.count(s) == 0) {
    this->map.insert(std::make_pair(s, std::make_pair(ujp::UJP_JSON, this->objects.size())));
    this->objects.push_back(json);
  } else
    return false;
  return true;
}

ujp::parserStates ujp::JSON::getParserReturn() { return this->parseReturn; }

std::string ujp::JSON::to_string(int ident) const {
  std::string str = "";
  this->to_string(ident, str, 0);
  return str;
}

void ujp::JSON::to_string(int ident, std::string &str, int count) const {
  str.append("{");
  bool elem = false;

  for (auto it = this->map.begin(); it != this->map.end(); it++) {
    elem = true;
    if (it->second.first == UJP_JSON) {
      str.append("\n");
      ujp::insert_nSpaces(str, ident * count);
      str.append("\"" + it->first);
      str.append("\" : ");
      this->objects[it->second.second].to_string(ident, str, count + 1);
      str.append(",");
    } else if (it->second.first == UJP_NUMBER) {
      str.append("\n");
      ujp::insert_nSpaces(str, ident * count);
      str.append("\"" + it->first + "\" : " + std::to_string(this->numbers[it->second.second]) + ",");
    } else if (it->second.first == UJP_STRING) {
      str.append("\n");
      ujp::insert_nSpaces(str, ident * count);
      str.append("\"" + it->first + "\" : \"" + this->strings[it->second.second] + "\",");
    }
  }
  if (elem)
    str.erase(str.end() - 1);
  str.append("\n");
  ujp::insert_nSpaces(str, 4 * (count - 1));
  str.append("}");
}

std::ostream &ujp::operator<<(std::ostream &co, const ujp::JSON &json) {
  co << json.to_string();
  return co;
}

std::ostream &ujp::operator<<(std::ostream &co, ujp::types type) {
  switch (type) {
  case UJP_STRING:
    co << "UJP_STRING";
    break;
  case UJP_NUMBER:
    co << "UJP_NUMBER";
    break;
  case UJP_JSON:
    co << "UJP_JSON";
    break;
  default:
    break;
  }
  return co;
}

std::ostream &ujp::operator<<(std::ostream &co, ujp::parserStates ps) {
  switch (ps) {
  case NO_PREV_PARSER:
    co << "NO_PREV_PARSER";
    break;
  case CORRECT_PARSER:
    co << "CORRECT_PARSER";
    break;
  case NO_BRACES_CLOSED:
    co << "NO_BRACES_CLOSED";
    break;
  case UNEXPECTED_CHAR:
    co << "UNEXPECTED_CHAR";
    break;
  case UNCOMPLETED_JSON:
    co << "UNCOMPLETED_JSON";
    break;
  case DUPLICATED_KEY:
    co << "DUPLICATED_KEY";
    break;
  case EXCESSIVE_RIGHT_BRACES:
    co << "EXECESSIVE_RIGHT_BRACES";
    break;
  default:
    break;
  }
  return co;
}