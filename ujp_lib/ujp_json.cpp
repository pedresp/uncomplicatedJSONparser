#include "ujp_json.hpp"
#include "ujp_scanner.hpp"

ujp::JSON::JSON(std::istream& stream){
    this->parseReturn = Scanner::parse(*this, stream);
}
ujp::JSON::JSON(){
    this->parseReturn = NO_PREV_PARSER;
}

void ujp::JSON::flush(){
    this->map.clear();
    this->numbers.clear();
    this->strings.clear();
    this->objects.clear();

    this->parseReturn = NO_PREV_PARSER;
}

std::vector<std::string> ujp::JSON::getString(){
    return strings;
}

std::map<std::string, std::pair<ujp::types, int>> ujp::JSON::getMap(){
    return map;
}

std::vector<double> ujp::JSON::getNumber(){
    return numbers;
}

std::ostream& ujp::operator<<(std::ostream& co, ujp::types type){
    switch (type)
        {
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