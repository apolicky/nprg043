#include "parser.hpp"

// template <typename T>
parser::parser(/* args */)
{
}

parser::~parser()
{
}

int main(int argc, char const *argv[])
{
    parser p;

    p.add_argument<std::string>("c", "clocks", "gsldgkhsl");

    std::cout << "\"" << p.get<int>("c") << "\""<< std::endl;

    return 0;
}
