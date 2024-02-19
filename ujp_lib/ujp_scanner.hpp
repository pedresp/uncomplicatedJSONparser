#ifndef __UJP_SCANNER__
#define __UJP_SCANNER__

#include <istream>
#include <string>
#include "ujp_json.hpp"

namespace ujp{
    class JSON;
    class Scanner{
        private:
            static parserStates state1(JSON& json, std::istream& input);
            static parserStates state2(JSON& json, std::istream& input, int count);
            static parserStates state3(JSON& json, std::istream& input, int count, std::string& str);
            static parserStates state4(JSON& json, std::istream& input, int count, std::string& str);
            static parserStates state5(JSON& json, std::istream& input, int count, std::string& str);
            static parserStates state6(JSON& json, std::istream& input, int count, std::string& str);
            static parserStates state7(JSON& json, std::istream& input, int count);
            static parserStates state8(JSON& json, std::istream& input, int count);
            static parserStates state9(JSON& json, std::istream& input, int count);
            static parserStates state10(JSON& json, std::istream& input, int count);
            static parserStates state11(JSON& json, std::istream& input, int count);
            static parserStates state12(JSON& json, std::istream& input, int count);
        public:
            static parserStates parse(JSON& json, std::istream& input);
    };
}

#endif