#ifndef COM_LINE_PARSER
#define COM_LINE_PARSER

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>


class ArgumentB {
public:
    virtual ~ArgumentB() {} //;
};

template <typename T>
class Argument : public ArgumentB {
private:
    
    std::string short_name, long_name, help;
    bool required;

    T val;
    std::vector<T> vals;

public:
    Argument() {}
    Argument(std::string short_name, std::string long_name,std::string help = "",bool required = true);
    Argument(std::string short_name, std::string long_name,std::vector<T>& choices /*optional*/,std::string help = "",bool required = true) {
        this->vals = std::move(choices);
    }
    ~Argument() {}

    T get(std::string arg_name) {
        return T();
    }
};


class parser {
private:
    std::map<std::string, std::shared_ptr<ArgumentB>> args;
    
public:
    parser(/* args */);
    ~parser();

    template <typename T>
    void add_argument(
        const std::string& short_name,
        const std::string& long_name, 
        const std::string& help = "", 
        bool required = true);
    
    template <typename T>
    void add_argument(
        const std::string& short_name,
        const std::string& long_name, 
        const std::vector<T>& choices, 
        const std::string& help = "",
        bool required = true);

    template <typename T>
    T get(const std::string& arg_name);

    // 0 -> not specified in 'argv', else number of výskytů
    size_t count(const std::string& arg_name);

    void parse_args(int argc, char** argv);

    const std::vector<std::string>& get_plain();
    size_t plain_count();

};

template <typename T>
T parser::get(const std::string& arg_name) {
    auto ret_ptr =  std::dynamic_pointer_cast<Argument<T>>(this->args[arg_name]);
    return ret_ptr->get(arg_name);
}

template <typename T>
void parser::add_argument(
    const std::string & sn,
    const std::string & ln, 
    const std::string & help, 
    bool req
) {
    if (!this->args.count(sn)) {
        // this->args[sn] = std::make_shared<Argument<T>>(sn,ln,help,req);
        this->args[sn] = std::make_shared<Argument<T>>();
    }
    else {
        std::cout << "ARGUMENT " << ln << " ALREADY DEFINED" << std::endl;
    }
}

template <typename T>
void parser::add_argument(
    const std::string& sn,
    const std::string& ln,
    const std::vector<T>& choices,
    const std::string& help,
    bool req
) {
    this->args[sn] = std::move(Argument<T>(sn,ln,choices,help,req));
}



#endif
