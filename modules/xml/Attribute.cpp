// ------------------------------------------------------------------------------------------------
#include "Attribute.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
SQInteger Attribute::Typename(HSQUIRRELVM vm)
{
    static const SQChar name[] = _SC("SqXmlAttribute");
    sq_pushstring(vm, name, sizeof(name));
    return 1;
}

// ------------------------------------------------------------------------------------------------
Object Attribute::AsLong(Object & def) const
{
    // Obtain the initial stack size
    const StackGuard sg;
    // Push the specified object onto the stack
    Var< Object >::push(DefaultVM::Get(), def);
    // The resulted long integer value
    Int64 longint = 0;
    // Attempt to get the numeric value inside the specified object
    if (SQ_FAILED(SqMod_GetSLongValue(DefaultVM::Get(), -1, &longint)))
    {
        STHROWF("Invalid long integer specified");
    }
    // Push a long integer instance with the requested value on the stack
    SqMod_PushSLongObject(DefaultVM::Get(), m_Attr.as_llong(longint));
    // Obtain the object from the stack and return it
    return Var< Object >(DefaultVM::Get(), -1).value;
}

// ------------------------------------------------------------------------------------------------
Object Attribute::AsUlong(Object & def) const
{
    // Obtain the initial stack size
    const StackGuard sg;
    // Push the specified object onto the stack
    Var< Object >::push(DefaultVM::Get(), def);
    // The resulted long integer value
    Uint64 longint = 0;
    // Attempt to get the numeric value inside the specified object
    if (SQ_FAILED(SqMod_GetULongValue(DefaultVM::Get(), -1, &longint)))
    {
        STHROWF("Invalid long integer specified");
    }
    // Push a long integer instance with the requested value on the stack
    SqMod_PushULongObject(DefaultVM::Get(), m_Attr.as_ullong(longint));
    // Obtain the object from the stack and return it
    return Var< Object >(DefaultVM::Get(), -1).value;
}

// ------------------------------------------------------------------------------------------------
bool Attribute::ApplyLong(Object & value)
{
    // Obtain the initial stack size
    const StackGuard sg;
    // Push the specified object onto the stack
    Var< Object & >::push(DefaultVM::Get(), value);
    // The resulted long integer value
    Int64 longint = 0;
    // Attempt to get the numeric value inside the specified object
    if (SQ_FAILED(SqMod_GetSLongValue(DefaultVM::Get(), -1, &longint)))
    {
        STHROWF("Invalid long integer specified");
    }
    // Assign the obtained value and return the result
    return m_Attr.set_value(longint);
}

// ------------------------------------------------------------------------------------------------
bool Attribute::ApplyUlong(Object & value)
{
    // Obtain the initial stack size
    const StackGuard sg;
    // Push the specified object onto the stack
    Var< Object & >::push(DefaultVM::Get(), value);
    // The resulted long integer value
    Uint64 longint = 0;
    // Attempt to get the numeric value inside the specified object
    if (SQ_FAILED(SqMod_GetULongValue(DefaultVM::Get(), -1, &longint)))
    {
        STHROWF("Invalid long integer specified");
    }
    // Assign the obtained value and return the result
    return m_Attr.set_value(longint);
}

// ------------------------------------------------------------------------------------------------
Object Attribute::GetLong() const
{
    // Obtain the initial stack size
    const StackGuard sg;
    // Push a long integer instance with the requested value on the stack
    SqMod_PushSLongObject(DefaultVM::Get(), m_Attr.as_llong());
    // Obtain the object from the stack and return it
    return Var< Object >(DefaultVM::Get(), -1).value;
}

// ------------------------------------------------------------------------------------------------
void Attribute::SetLong(Object & value)
{
    // Obtain the initial stack size
    const StackGuard sg;
    // Push the specified object onto the stack
    Var< Object & >::push(DefaultVM::Get(), value);
    // The resulted long integer value
    Int64 longint = 0;
    // Attempt to get the numeric value inside the specified object
    if (SQ_FAILED(SqMod_GetSLongValue(DefaultVM::Get(), -1, &longint)))
    {
        STHROWF("Invalid long integer specified");
    }
    // Assign the obtained value
    m_Attr = longint;
}

// ------------------------------------------------------------------------------------------------
Object Attribute::GetUlong() const
{
    // Obtain the initial stack size
    const StackGuard sg;
    // Push a long integer instance with the requested value on the stack
    SqMod_PushULongObject(DefaultVM::Get(), m_Attr.as_ullong());
    // Obtain the object from the stack and return it
    return Var< Object >(DefaultVM::Get(), -1).value;
}

// ------------------------------------------------------------------------------------------------
void Attribute::SetUlong(Object & value)
{
    // Obtain the initial stack size
    const StackGuard sg;
    // Push the specified object onto the stack
    Var< Object & >::push(DefaultVM::Get(), value);
    // The resulted long integer value
    Uint64 longint = 0;
    // Attempt to get the numeric value inside the specified object
    if (SQ_FAILED(SqMod_GetULongValue(DefaultVM::Get(), -1, &longint)))
    {
        STHROWF("Invalid long integer specified");
    }
    // Assign the obtained value
    m_Attr = longint;
}

} // Namespace:: SqMod
