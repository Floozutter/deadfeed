#ifndef ARGS_HPP
#define ARGS_HPP

#include <string>

namespace args {
    class Args {
    public:
        std::string filename;
        bool ansi;
        Args() = delete;
        Args(int argc, char const * const argv[]);
    };
}

#endif
