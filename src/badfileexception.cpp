#include "badfileexception.h"

const char* BadFileException::what() const noexcept
{
    return "Error while reading simulation file!\n";
}
