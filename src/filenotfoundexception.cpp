#include "filenotfoundexception.h"

const char* FileNotFoundException::what() const noexcept
{
    return "File with simulation not found!\n";
}
