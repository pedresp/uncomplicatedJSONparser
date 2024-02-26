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

std::ostream& ujp::operator<<(std::ostream& co, const ujp::JSON& json){
    co << "\n---------- JSON START ----------" << std::endl;
    for (auto it = json.map.begin(); it != json.map.end(); it++){
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

std::ostream& ujp::operator<<(std::ostream& co, ujp::parserStates ps){
    switch (ps)
    {
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