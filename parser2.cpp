#include "parser2.hpp"

int main(int argc, char const *argv[])
{
    parser p;

    p.add_arg<std::string>('f',"format","Specify output format, possibly overriding the format specified in the environment variable TIME.");
    p.add_flag('p',"portability", "Use the portable output format.");
    p.add_arg<std::string>('o',"output", "Do not send the results to stderr, but overwrite the specified file.");
    p.add_flag('a',"append", "(Used together with -o.) Do not overwrite but append.");
    p.add_flag('v',"verbose","Give very verbose output about all the program knows about.");

    p.add_flag("help", "Print a usage message on standard output and exit successfully.");
    p.add_flag('V',"version", "Print version information on standard output, then exit successfully.");

    p.parse_args(argc,argv);

    if(p.has('v'))
        printf("version is 1.2.3\n");

    if(p.has("output")) {
        printf("Specified output file is '%s'\n", p.get_arg<std::string>("output").c_str());
    }

    return 0;
}
