#ifndef OMEGA_UTIL_ERROR_H
#define OMEGA_UTIL_ERROR_H

#include <exception>
#include <string>

namespace omega::util {

class Error : public std::exception {
  public:
    Error(const std::string &s) : s(s) {}

    virtual const char *what() const throw() {
        return s.c_str();
    }

  private:
    std::string s;
};
} // namespace omega::util

#endif // OMEGA_UTIL_ERROR_H