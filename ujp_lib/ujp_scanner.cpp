#include "ujp_scanner.hpp"
#include <iostream>
#include "ujp_exception.hpp"
#include "ujp_utils.hpp"

using namespace ujp;
bool Scanner::parse(JSON& json, std::istream& input){
    try
    {
        Scanner::state1(json, input);
    }
    catch(const badformat_Exception& excep)
    {
        std::cerr << "WOW except happened";
        return false;
    }
    return true;
}

void Scanner::state1(JSON& json, std::istream& input){
    throw badformat_Exception();
}