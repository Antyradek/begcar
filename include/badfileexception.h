#ifndef BADFILEEXCEPTION_H
#define BADFILEEXCEPTION_H

#include <exception>
using namespace std;

class BadFileException : public exception
{
    public:
        const char* what() const noexcept;
};

#endif // BADFILEEXCEPTION_H
