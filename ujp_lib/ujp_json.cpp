#include "ujp_json.hpp"
#include "ujp_scanner.hpp"

ujp::JSON::JSON(std::istream& stream){
    this->parsed = Scanner::parse(*this, stream);
}
ujp::JSON::JSON(){
    this->parsed = false;
}