#ifndef __UJP_JSON__
#define __UJP_JSON__

#include <map>
#include <vector>
#include <istream>

namespace ujp {
    class Scanner;
    enum types {UJP_STRING = 1, UJP_NUMBER = 2, UJP_JSON = 3};

    class JSON{

        private:
            bool parsed;
            std::vector<double> numbers;
            std::vector<std::string> strings;
            std::vector<JSON> objects;
            std::map<std::string, std::pair<types, int>> map;
        
        public:
            JSON();
            JSON(std::istream& stream);
            friend Scanner;
    };
}

#endif