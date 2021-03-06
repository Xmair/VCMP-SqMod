// ------------------------------------------------------------------------------------------------
#include "Library/IO.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
extern void Register_INI(HSQUIRRELVM vm);

// ================================================================================================
void Register_IO(HSQUIRRELVM vm)
{
    Register_INI(vm);
}

} // Namespace:: SqMod
