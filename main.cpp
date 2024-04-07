#include "ujp_exception.hpp"
#include "ujp_json.hpp"
#include "ujp_scanner.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

int main() {
  // parse a json from std::cin
  ujp::JSON json(std::cin);

  // print the object
  std::cout << "json: -> " << json << std::endl;

  // parse a json from a file
  std::ifstream iff("json_files/file0.json");
  ujp::JSON o_json(iff);

  std::cout << "file json -> " << o_json.to_string() << std::endl;

  // parse a json from a existing string
  std::string str =
      "{ \"pokemon_name\": \"Quagsire\", \"HP\": 95, \"Attack\": 85, \"Sp Atk\": 65, \"Sp Def\": 65, \"Speed\": 35}";
  std::istringstream iss(str);

  ujp::JSON j_json(iss);
  std::cout << str << std::endl << "poke json -> " << j_json << std::endl;

  // get the value of an element of the json
  std::string poke_name = j_json.getString("pokemon_name");

  // add a new element to the json
  j_json.setNumber("Defense", 85);

  // add a json objecto to another json
  json.setJSON("The best pokemon", j_json);

  // show the new json
  std::cout << "new json -> " << json << std::endl;

  // empty a json object
  json.flush();
  std::cout << "flush json -> " << json << std::endl;

  return 0;
}
