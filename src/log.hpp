#ifndef LOG_HPP
#define LOG_HPP

#include <string>

std::string header(std::string const & text);
std::string item(unsigned int depth, std::string const & text);
std::string item(std::string const & text);
std::string result(std::string const & text);
std::string warning(std::string const & text);
std::string error(std::string const & text);

#endif
