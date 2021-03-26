#ifndef COM_LINE_PARSER2
#define COM_LINE_PARSER2

#include <string>
#include <vector>
// #include <iostream>

// --- PUBLIC API -------------------------------

template <typename T>
using is_numeric_t = typename std::enable_if<
    std::is_same<double, T>::value ||
    std::is_same<float, T>::value ||
    std::is_same<int, T>::value ||
    std::is_same<long, T>::value, T>::type;

template <typename T>
using cmd_parser_supported_non_bool_t = typename std::enable_if<
    std::is_same<std::string, T>::value ||
    std::is_same<double, T>::value ||
    std::is_same<float, T>::value ||
    std::is_same<int, T>::value ||
    std::is_same<long, T>::value, T>::type;

template <typename T>
using cmd_parser_supported_t = typename std::enable_if<
    std::is_same<bool, T>::value ||
    std::is_same<std::string, T>::value ||
    std::is_same<double, T>::value ||
    std::is_same<float, T>::value ||
    std::is_same<int, T>::value ||
    std::is_same<long, T>::value, T>::type;

class parser final {
private:
    std::vector<std::string> _plain_args = {"hey", "hi", "hello"};
public:

    void add_flag(
        char short_name,
        const std::string& long_name, 
        const std::string& help = "", 
        bool required = false) {}

    void add_flag(
        const std::string& long_name, 
        const std::string& help = "", 
        bool required = false) {}

    // can be bool, int, float, double, string
    template <typename T, typename = cmd_parser_supported_non_bool_t<T>>
    void add_arg(
        char short_name,
        const std::string& long_name, 
        const std::string& help = "", 
        bool required = false) {}

    // can be bool, int, float, double, string
    template <typename T, typename = cmd_parser_supported_non_bool_t<T>>
    void add_arg(
        const std::string& long_name, 
        const std::string& help = "", 
        bool required = false) {}
    
    // can be int, float, double, string
    template <typename T, typename = cmd_parser_supported_non_bool_t<T>>
    void add_arg(
        char short_name,
        const std::string& long_name, 
        const std::string& help,
        const std::vector<T>& choices, 
        bool required = false) {}
    
    // can be int, float, double, string
    template <typename T, typename = cmd_parser_supported_non_bool_t<T>>
    void add_arg(
        const std::string& long_name, 
        const std::string& help,
        const std::vector<T>& choices, 
        bool required = false) {}

    // can be int, float, double
    template <typename T, typename = is_numeric_t<T>>
    void add_arg(
        const std::string& long_name, 
        T upper_bound,
        T lower_bound,
        const std::string& help = "",
        bool required = false) {}
        
    // can be int, float, double
    template <typename T, typename = is_numeric_t<T>>
    void add_arg(
        char short_name,
        const std::string& long_name, 
        T upper_bound,
        T lower_bound,
        const std::string& help = "",
        bool required = false) {}

    // can be bool, int, float, double, string
    // returns the value of command line argument 'arg_name' if present, else throws an exception
    template <typename T, typename = cmd_parser_supported_t<T>>
    T get_arg(const std::string& long_name) { return T{}; }

    // can be bool, int, float, double, string
    // returns the value of command line argument 'arg_name' if present, else throws an exception
    template <typename T, typename = cmd_parser_supported_t<T>>
    T get_arg(char short_name) { return T{}; }

    // can be bool, int, float, double, string
    // true if arg_name was specified in argv
    bool has(const std::string& long_name);

    // can be bool, int, float, double, string
    // true if arg_name was specified in argv
    bool has(char short_name);

    // parses arguments by given rules
    void parse_args(int argc, char const *argv[]);

    // returns plain command line arguments (specified after two dashes)
    const std::vector<std::string>& plain_args();

    // returns the size of plain command line arguments
    size_t plain_args_count();

};

bool parser::has(const std::string& long_name){
    return true;
}

// true if arg_name was specified in argv
bool parser::has(char short_name){
    return true;
}

void parser::parse_args(int argc, char const *argv[]){
    return;
}

const std::vector<std::string>& parser::plain_args(){
    return _plain_args;
}

// returns the size of plain command line arguments
size_t parser::plain_args_count(){
    return _plain_args.size();
}


#endif
