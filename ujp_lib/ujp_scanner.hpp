#ifndef __UJP_SCANNER__
#define __UJP_SCANNER__

#include <istream>
#include <string>

namespace ujp{
    class JSON;
    class Scanner{
        private:
            static int state1(JSON& json, std::istream& input);
            static int state2(JSON& json, std::istream& input, int count);
            static int state3(JSON& json, std::istream& input, int count, std::string& str);
            static int state4(JSON& json, std::istream& input, int count, std::string& str);
            static int state5(JSON& json, std::istream& input, int count, std::string& str);
            static int state6(JSON& json, std::istream& input, int count, std::string& str);
            static int state7(JSON& json, std::istream& input, int count);
            static int state8(JSON& json, std::istream& input, int count);
            static int state9(JSON& json, std::istream& input, int count);
            static int state10(JSON& json, std::istream& input, int count);
            static int state11(JSON& json, std::istream& input, int count);
            static int state12(JSON& json, std::istream& input, int count);
        public:
            static int parse(JSON& json, std::istream& input);
    };
}

#endif