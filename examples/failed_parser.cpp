#include "ujp_exception.hpp"
#include "ujp_json.hpp"
#include <fstream>
#include <iostream>
int main() {
  // try to parse an incorrect json file
  std::ifstream iff("json_files/");
  ujp::JSON json(iff);

  // we check if the data_one key was stored inside the json object
  try {
    std::cout << json.getNumber("data_one") << std::endl;
  } catch (const ujp::Key_Error &ke) {
    // because of the json file being incorrect there is no "data_one" key inside json object.
    std::cout << "a Key_Error exception occured due to an incorrect parser" << std::endl;
  }

  // we show the parserReturn of the constructor method
  std::cout << json.getParserReturn() << std::endl;
  return 0;
}