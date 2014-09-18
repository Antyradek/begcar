#ifndef FILENOTFOUNDEXCEPTION_H
#define FILENOTFOUNDEXCEPTION_H

#include <exception>
using namespace std;

class FileNotFoundException : public exception
{
    public:
        const char* what() const noexcept;
};

#endif // FILENOTFOUNDEXCEPTION_H
