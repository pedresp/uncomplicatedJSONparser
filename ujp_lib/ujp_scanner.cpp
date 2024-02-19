#include "ujp_scanner.hpp"
#include <iostream>
#include "ujp_exception.hpp"
#include "ujp_utils.hpp"
#include "ujp_json.hpp"

using namespace ujp;
int Scanner::parse(JSON& json, std::istream& input){
    char c;
    omit_delimiters(input, c);
        
    if (c == '{')
        return Scanner::state1(json, input);
    else if (input.eof())
        return 1;
    return 2;
}

int Scanner::state1(JSON& json, std::istream& input){
    char car;
    omit_delimiters(input, car);

    if (car == '\"')
        return Scanner::state2(json, input, 1);
    else if (input.eof())
        return 1;
    return 2;
}

int Scanner::state2(JSON& json, std::istream& input, int count){
    std::string key;
    char c;
    input >> c;
    while (c != '\"' && !input.eof()){
        key.push_back(c);
        input >> c;
    }
    if (c == '\"')
        return Scanner::state3(json, input, count, key);            
    return 3;
}

int Scanner::state3(JSON& json, std::istream& input, int count, std::string& key){
    if (json.map.count(key) > 0)
        return 4;
    char c;
    omit_delimiters(input, c);

    if (c == ':')
        return Scanner::state4(json, input, count, key);
    else if (input.eof())
        return 3;        
    return 2;
}

int Scanner::state4(JSON& json, std::istream& input, int count, std::string& key){
    char c;
    omit_delimiters(input, c);

    if (c == '\"'){
        std::string my_str;
        json.map.insert(std::make_pair(key, std::make_pair(UJP_STRING, json.strings.size())));
        json.strings.push_back(my_str);
        return Scanner::state6(json, input, count, key);    
    }
    return 2;
}

int Scanner::state6(JSON& json, std::istream& input, int count, std::string& key){
    char c;
    int pos = json.map[key].second;
    input >> c;
    while (c != '\"' && !input.eof())
    {
        json.strings[pos].push_back(c);
        input >> c;
    }
    
    if (c == '\"')
        return Scanner::state8(json, input, count);
    return 3;    
}

int Scanner::state8(JSON& json, std::istream& input, int count){
    char c;
    omit_delimiters(input, c);

    if (c == '}')
        return Scanner::state12(json, input, count);
    else if (c == ',')
        return Scanner::state11(json, input, count);
        
    return 2;
}

int Scanner::state11(JSON& json, std::istream& input, int count){
    char c;
    omit_delimiters(input, c);

    if (c == '\"')
        return Scanner::state2(json, input, count);
    return 2;    
}

int Scanner::state12(JSON& json, std::istream& input, int count){
    return 0;
}