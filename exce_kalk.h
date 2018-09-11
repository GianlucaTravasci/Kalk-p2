#ifndef EXCE_KALK_H
#define EXCE_KALK_H

#include <iostream>
#include <stdexcept>

class exce_kalk: public std::runtime_error {
public:
    explicit exce_kalk(const char* err): std::runtime_error(err) {};
    explicit exce_kalk(const std::string& err): std::runtime_error(err) {};
};

#endif // EXCE_KALK_H
