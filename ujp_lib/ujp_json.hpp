#ifndef __UJP_JSON__
#define __UJP_JSON__

#include <map>
#include <vector>
#include <istream>

namespace ujp
{
    class Scanner;
    class JSON;
    enum types
    {
        UJP_STRING = 1,
        UJP_NUMBER = 2,
        UJP_JSON = 3
    };
    enum parserStates
    {
        NO_PREV_PARSER = -1,
        CORRECT_PARSER = 0,
        NO_BRACES_CLOSED = 1,
        UNEXPECTED_CHAR = 2,
        UNCOMPLETED_JSON = 3,
        DUPLICATED_KEY = 4,
        EXCESSIVE_RIGHT_BRACES = 5
    };

    std::ostream& operator<<(std::ostream &co, const JSON& json);

    class JSON
    {

    private:
        parserStates parseReturn;
        std::vector<double> numbers;
        std::vector<std::string> strings;
        std::vector<JSON> objects;
        std::map<std::string, std::pair<types, int>> map;

    public:
        JSON();
        JSON(std::istream &stream);
        std::vector<std::string> getString();
        std::vector<double> getNumber();
        std::map<std::string, std::pair<types, int>> getMap();
        friend Scanner;
        void flush();
        friend std::ostream& operator<<(std::ostream &co, const JSON& json);
    };

    std::ostream &operator<<(std::ostream &co, types type);
    std::ostream &operator<<(std::ostream &co, parserStates ps);
}

#endif