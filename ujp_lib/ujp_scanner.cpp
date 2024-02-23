#include "ujp_scanner.hpp"
#include <iostream>
#include "ujp_exception.hpp"
#include "ujp_utils.hpp"
#include "ujp_json.hpp"

#include <cmath>

using namespace ujp;
parserStates Scanner::parse(JSON& json, std::istream& input){
    char c;
    omit_delimiters(input, c);
    parserStates ps;
    std::stack<JSON*> stack;

    if (c == '{'){
        stack.emplace(&json);
        ps = Scanner::state1(stack, input);
        if (ps != CORRECT_PARSER)
            json.flush();
        return ps;        
    }
    else if (input.eof())
        return CORRECT_PARSER;
    return UNEXPECTED_CHAR;
}

parserStates Scanner::state1(std::stack<JSON*>& stack, std::istream& input){
    char car;
    omit_delimiters(input, car);

    if (car == '\"')
        return Scanner::state2(stack, input);
    else if (input.eof())
        return NO_BRACES_CLOSED;
    return UNEXPECTED_CHAR;
}

parserStates Scanner::state2(std::stack<JSON*>& stack, std::istream& input){
    std::string key;
    char c;
    input >> c;
    while (c != '\"' && !input.eof()){
        key.push_back(c);
        input >> c;
    }
    if (c == '\"')
        return Scanner::state3(stack, input, key);            
    return UNCOMPLETED_JSON;
}

parserStates Scanner::state3(std::stack<JSON*>& stack, std::istream& input, std::string& key){
    JSON& json = *stack.top();
    if (json.map.count(key) > 0)
        return DUPLICATED_KEY;
    char c;
    omit_delimiters(input, c);

    if (c == ':')
        return Scanner::state4(stack, input, key);
    else if (input.eof())
        return UNCOMPLETED_JSON;     
    return UNEXPECTED_CHAR;
}

parserStates Scanner::state4(std::stack<JSON*>& stack, std::istream& input, std::string& key){
    JSON& json = *stack.top();
    char c;
    omit_delimiters(input, c);

    if (c == '\"'){
        std::string my_str;
        json.map.insert(std::make_pair(key, std::make_pair(UJP_STRING, json.strings.size())));
        json.strings.push_back(my_str);
        return Scanner::state6(stack, input, key);    
    } else if (is_digit(c))
    {
        json.map.insert(std::make_pair(key, std::make_pair(UJP_NUMBER, json.numbers.size())));
        json.numbers.push_back(c-48);
        return Scanner::state7(stack, input, key);
    }
    
    return UNEXPECTED_CHAR;
}

parserStates Scanner::state6(std::stack<JSON*>& stack, std::istream& input, std::string& key){
    JSON& json = *stack.top();
    char c;
    int pos = json.map[key].second;
    input >> c;
    while (c != '\"' && !input.eof())
    {
        json.strings[pos].push_back(c);
        input >> c;
    }
    
    if (c == '\"')
        return Scanner::state8(stack, input);
    return UNCOMPLETED_JSON;    
}

parserStates Scanner::state7(std::stack<JSON*>& stack, std::istream& input, std::string& key){
    JSON& json = *stack.top();
    char my_numb;
    int pos = json.map[key].second;
    input >> my_numb;
    while (is_digit(my_numb))
    {
        json.numbers[pos] = 10*json.numbers[pos] + my_numb-48;
        input >> my_numb;
    }

    if (my_numb == '}')
        return Scanner::state12(stack, input);
    else if (my_numb == ',')
        return Scanner::state11(stack, input);
    else if (my_numb == '.')
        return Scanner::state9(stack, input, key);
    return UNEXPECTED_CHAR;
    
}

parserStates Scanner::state8(std::stack<JSON*>& stack, std::istream& input){
    char c;
    omit_delimiters(input, c);

    if (c == '}')
        return Scanner::state12(stack, input);
    else if (c == ',')
        return Scanner::state11(stack, input);
        
    return UNEXPECTED_CHAR;
}

parserStates Scanner::state9(std::stack<JSON*>& stack, std::istream& input, std::string& key){
    JSON& json = *stack.top();
    char c;
    input >> c;
    if (is_digit(c))
    {
        json.numbers[json.map[key].second] = json.numbers[json.map[key].second] + (c-48)*0.1;
        return Scanner::state10(stack, input, key);
    }
    return UNEXPECTED_CHAR;
}

parserStates Scanner::state10(std::stack<JSON*>& stack, std::istream& input, std::string& key){
    JSON& json = *stack.top();
    char c;
    int pos = json.map[key].second;
    input >> c;
    for (int i = -2; is_digit(c); i--){
        json.numbers[pos] = json.numbers[pos] + pow(10, i)*(c-48);
        input >> c;
    }
    
    if (c == '}')
        return Scanner::state12(stack, input);
    else if (c == ',')
        return Scanner::state11(stack, input);
    
    return UNEXPECTED_CHAR;        
}

parserStates Scanner::state11(std::stack<JSON*>& stack, std::istream& input){
    char c;
    omit_delimiters(input, c);

    if (c == '\"')
        return Scanner::state2(stack, input);
    return UNEXPECTED_CHAR;    
}

parserStates Scanner::state12(std::stack<JSON*>& stack, std::istream& input){
    return CORRECT_PARSER;
}