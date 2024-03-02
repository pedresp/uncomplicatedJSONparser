#include "ujp_json.hpp"
#include "ujp_scanner.hpp"
#include "ujp_utils.hpp"

#define N_SPACES 4

ujp::JSON::JSON(std::istream &stream) { this->parseReturn = Scanner::parse(*this, stream); }
ujp::JSON::JSON() { this->parseReturn = NO_PREV_PARSER; }

void ujp::JSON::flush() {
  this->map.clear();
  this->numbers.clear();
  this->strings.clear();
  this->objects.clear();

  this->parseReturn = NO_PREV_PARSER;
}

std::vector<std::string> ujp::JSON::getString() { return strings; }

std::map<std::string, std::pair<ujp::types, int>> ujp::JSON::getMap() { return map; }

std::vector<double> ujp::JSON::getNumber() { return numbers; }

std::vector<ujp::JSON> ujp::JSON::getJSON() { return objects; }

std::string ujp::JSON::to_string() {
  std::string str = "{";
  bool elem = false;

  for (auto it = this->map.begin(); it != this->map.end(); it++) {
    elem = true;
    if (it->second.first == UJP_JSON) {
      str.append("\n\"" + it->first + "\" : ");
      this->objects[it->second.second].to_string(str, 1);
      str.append(",");
    } else if (it->second.first == UJP_NUMBER) {
      str.append("\n\"" + it->first + "\" : " + std::to_string(this->numbers[it->second.second]) + ",");
    } else if (it->second.first == UJP_STRING) {
      str.append("\n");
      str.append("\n\"" + it->first + "\" : \"" + this->strings[it->second.second] + "\",");
    }
  }
  if (elem)
    str.erase(str.end() - 1);
  str.append("\n}");
  return str;
}

void ujp::JSON::to_string(std::string &str, int count) {
  str.append("{\n");
  bool elem = false;

  for (auto it = this->map.begin(); it != this->map.end(); it++) {
    elem = true;
    if (it->second.first == UJP_JSON) {
      str.append("\n");
      ujp::insert_nSpaces(str, 4 * count);
      str.append("\"" + it->first);
      str.append("\" : ");
      this->objects[it->second.second].to_string(str, count + 1);
      str.append(",");
    } else if (it->second.first == UJP_NUMBER) {
      str.append("\n");
      ujp::insert_nSpaces(str, 4 * count);
      str.append("\"" + it->first + "\" : " + std::to_string(this->numbers[it->second.second]) + ",");
    } else if (it->second.first == UJP_STRING) {
      str.append("\n");
      ujp::insert_nSpaces(str, 4 * count);
      str.append("\"" + it->first + "\" : \"" + this->strings[it->second.second] + "\",");
    }
  }
  if (elem)
    str.erase(str.end() - 1);
  str.append("\n");
  ujp::insert_nSpaces(str, 4 * count);
  str.append("}");
}

std::ostream &ujp::operator<<(std::ostream &co, const ujp::JSON &json) {
  co << "\n---------- JSON START ----------" << std::endl;
  for (auto it = json.map.begin(); it != json.map.end(); it++) {
    if (it->second.first == UJP_JSON)
      co << "key: " << it->first << " value: " << json.objects[it->second.second] << std::endl;
    else if (it->second.first == UJP_NUMBER)
      co << "key: " << it->first << " value: " << json.numbers[it->second.second] << std::endl;
    else if (it->second.first == UJP_STRING)
      co << "key: " << it->first << " value: " << json.strings[it->second.second] << std::endl;
  }
  co << "---------- JSON END ----------" << std::endl;
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