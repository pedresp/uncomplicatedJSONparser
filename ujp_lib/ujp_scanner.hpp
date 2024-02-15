#ifndef __UJP_SCANNER__
#define __UJP_SCANNER__

#include <istream>

namespace ujp{
    class JSON;
    class Scanner{
        private:
            static void state1(JSON& json, std::istream& input);
            static void state2(JSON& json, std::istream& input);
            static void state3(JSON& json, std::istream& input);
            static void state4(JSON& json, std::istream& input);
            static void state5(JSON& json, std::istream& input);
            static void state6(JSON& json, std::istream& input);
            static void state7(JSON& json, std::istream& input);
            static void state8(JSON& json, std::istream& input);
            static void state9(JSON& json, std::istream& input);
            static void state10(JSON& json, std::istream& input);
            static void state11(JSON& json, std::istream& input);
            static void state12(JSON& json, std::istream& input);
        public:
            static bool parse(JSON& json, std::istream& input);
    };
}

#endif