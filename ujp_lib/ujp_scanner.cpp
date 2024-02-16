#include "ujp_scanner.hpp"
#include <iostream>
#include "ujp_exception.hpp"
#include "ujp_utils.hpp"
#include "ujp_json.hpp"

using namespace ujp;
bool Scanner::parse(JSON& json, std::istream& input){
    try
    {
        char c;
        do
            input >> c;
        while (is_delimiter(c) && !input.eof());
        
        if (c == '{')
            Scanner::state1(json, input);
        else if (!input.eof())
            throw badformat_Exception();
    }
    catch(const badformat_Exception& excep)
    {
        std::cerr << "WOW except happened";
        return false;
    }
    return true;
}

void Scanner::state1(JSON& json, std::istream& input){
    std::cout << "good" << std::endl;
}