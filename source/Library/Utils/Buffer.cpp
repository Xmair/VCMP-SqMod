// ------------------------------------------------------------------------------------------------
#include "Library/Utils/Buffer.hpp"
#include "Library/Numeric/LongInt.hpp"
#include "Base/AABB.hpp"
#include "Base/Circle.hpp"
#include "Base/Color3.hpp"
#include "Base/Color4.hpp"
#include "Base/Quaternion.hpp"
#include "Base/Sphere.hpp"
#include "Base/Vector2.hpp"
#include "Base/Vector2i.hpp"
#include "Base/Vector3.hpp"
#include "Base/Vector4.hpp"

// ------------------------------------------------------------------------------------------------
#include <cstring>

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
SQMODE_DECL_TYPENAME(Typename, _SC("SqBuffer"))

// ------------------------------------------------------------------------------------------------
void SqBuffer::WriteInt64(const SLongInt & val)
{
    // Validate the managed buffer reference
    Validate();
    // Perform the requested operation
    m_Buffer->Push< Int64 >(val.GetNum());
}

// ------------------------------------------------------------------------------------------------
void SqBuffer::WriteUint64(const ULongInt & val)
{
    // Validate the managed buffer reference
    Validate();
    // Perform the requested operation
    m_Buffer->Push< Uint64 >(val.GetNum());
}

// ------------------------------------------------------------------------------------------------
void SqBuffer::WriteString(CSStr val)
{
    // Validate the managed buffer reference
    Validate();
    // Is the given string value even valid?
    if (!val)
    {
        STHROWF("Invalid string argument: null");
    }
    // Calculate the string length
    Uint16 length = ConvTo< Uint16 >::From(std::strlen(val));
    // Change the size endianness to big endian
    Uint16 size = ((length >> 8) & 0xFF) | ((length & 0xFF) << 8);
    // Write the size and then the string contents
    m_Buffer->Push< Uint16 >(size);
    m_Buffer->AppendS(val, length);
}

// ------------------------------------------------------------------------------------------------
void SqBuffer::WriteRawString(CSStr val)
{
    // Validate the managed buffer reference
    Validate();
    // Is the given string value even valid?
    if (!val)
    {
        STHROWF("Invalid string argument: null");
    }
    // Calculate the string length
    Uint16 length = ConvTo< Uint16 >::From(std::strlen(val));
    // Write the the string contents
    m_Buffer->AppendS(val, length);
}

// ------------------------------------------------------------------------------------------------
void SqBuffer::WriteAABB(const AABB & val)
{
    // Validate the managed buffer reference
    Validate();
    // Perform the requested operation
    m_Buffer->Push< AABB >(val);
}

// ------------------------------------------------------------------------------------------------
void SqBuffer::WriteCircle(const Circle & val)
{
    // Validate the managed buffer reference
    Validate();
    // Perform the requested operation
    m_Buffer->Push< Circle >(val);
}

// ------------------------------------------------------------------------------------------------
void SqBuffer::WriteColor3(const Color3 & val)
{
    // Validate the managed buffer reference
    Validate();
    // Perform the requested operation
    m_Buffer->Push< Color3 >(val);
}

// ------------------------------------------------------------------------------------------------
void SqBuffer::WriteColor4(const Color4 & val)
{
    // Validate the managed buffer reference
    Validate();
    // Perform the requested operation
    m_Buffer->Push< Color4 >(val);
}

// ------------------------------------------------------------------------------------------------
void SqBuffer::WriteQuaternion(const Quaternion & val)
{
    // Validate the managed buffer reference
    Validate();
    // Perform the requested operation
    m_Buffer->Push< Quaternion >(val);
}

// ------------------------------------------------------------------------------------------------
void SqBuffer::WriteSphere(const Sphere &val)
{
    // Validate the managed buffer reference
    Validate();
    // Perform the requested operation
    m_Buffer->Push< Sphere >(val);
}

// ------------------------------------------------------------------------------------------------
void SqBuffer::WriteVector2(const Vector2 & val)
{
    // Validate the managed buffer reference
    Validate();
    // Perform the requested operation
    m_Buffer->Push< Vector2 >(val);
}

// ------------------------------------------------------------------------------------------------
void SqBuffer::WriteVector2i(const Vector2i & val)
{
    // Validate the managed buffer reference
    Validate();
    // Perform the requested operation
    m_Buffer->Push< Vector2i >(val);
}

// ------------------------------------------------------------------------------------------------
void SqBuffer::WriteVector3(const Vector3 & val)
{
    // Validate the managed buffer reference
    Validate();
    // Perform the requested operation
    m_Buffer->Push< Vector3 >(val);
}

// ------------------------------------------------------------------------------------------------
void SqBuffer::WriteVector4(const Vector4 & val)
{
    // Validate the managed buffer reference
    Validate();
    // Perform the requested operation
    m_Buffer->Push< Vector4 >(val);
}

// ------------------------------------------------------------------------------------------------
SLongInt SqBuffer::ReadInt64()
{
    // Validate the managed buffer reference
    ValidateDeeper();
    // Read one element from the buffer
    const Int64 value = m_Buffer->Cursor< Int64 >();
    // Advance the buffer cursor
    m_Buffer->Advance< Int64 >(1);
    // Return the requested information
    return SLongInt(value);
}

// ------------------------------------------------------------------------------------------------
ULongInt SqBuffer::ReadUint64()
{
    // Validate the managed buffer reference
    ValidateDeeper();
    // Read one element from the buffer
    const Uint64 value = m_Buffer->Cursor< Uint64 >();
    // Advance the buffer cursor
    m_Buffer->Advance< Uint64 >(1);
    // Return the requested information
    return ULongInt(value);
}

// ------------------------------------------------------------------------------------------------
Object SqBuffer::ReadString()
{
    // Validate the managed buffer reference
    ValidateDeeper();
    // Read one element from the buffer
    Uint16 length = m_Buffer->Cursor< Uint16 >();
    // Convert the length to little endian
    length = ((length >> 8) & 0xFF) | ((length & 0xFF) << 8);
    // Validate the obtained length
    if ((m_Buffer->Position() + sizeof(Uint16) + length) > m_Buffer->Capacity())
    {
        STHROWF("String of size (%u) starting at (%u) is out of buffer capacity (%u)",
                    length, m_Buffer->Position() + sizeof(Uint16), m_Buffer->Capacity());
    }
    // Advance the buffer to the actual string
    m_Buffer->Advance< Uint16 >(1);
    // Remember the current stack size
    const StackGuard sg;
    // Attempt to create the string as an object
    sq_pushstring(DefaultVM::Get(), &m_Buffer->Cursor(), length);
    // Advance the cursor after the string
    m_Buffer->Advance(length);
    // Return the resulted object
    return Var< Object >(DefaultVM::Get(), -1).value;
}

// ------------------------------------------------------------------------------------------------
Object SqBuffer::ReadRawString(SQInteger length)
{
    // Validate the managed buffer reference
    ValidateDeeper();
    // Start with a length of zero
    Uint32 len = 0;
    // Should we Identify the string length ourselves?
    if (length < 0)
    {
        // Grab the buffer range to search for
        CCStr ptr = &m_Buffer->Cursor(), itr = ptr, end = m_Buffer->End();
        // Attempt to look for a string terminator
        while (itr != end && *itr != '\0')
        {
            ++itr;
        }
        // If nothing was found, consider the remaining buffer part of the requested string
        len = static_cast< Uint32 >(ptr - itr);
    }
    else
    {
        len = ConvTo< Uint32 >::From(length);
    }
    // Validate the obtained length
    if ((m_Buffer->Position() + len) > m_Buffer->Capacity())
    {
        STHROWF("String of size (%u) starting at (%u) is out of buffer capacity (%u)",
                    len, m_Buffer->Position(), m_Buffer->Capacity());
    }
    // Remember the current stack size
    const StackGuard sg;
    // Attempt to create the string as an object
    sq_pushstring(DefaultVM::Get(), &m_Buffer->Cursor(), len);
    // Advance the cursor after the string
    m_Buffer->Advance(len);
    // Return the resulted object
    return Var< Object >(DefaultVM::Get(), -1).value;
}

// ------------------------------------------------------------------------------------------------
AABB SqBuffer::ReadAABB()
{
    // Validate the managed buffer reference
    ValidateDeeper();
    // Read one element from the buffer
    const AABB & value = m_Buffer->Cursor< AABB >();
    // Advance the buffer cursor
    m_Buffer->Advance< AABB >(1);
    // Return the requested information
    return AABB(value);
}

// ------------------------------------------------------------------------------------------------
Circle SqBuffer::ReadCircle()
{
    // Validate the managed buffer reference
    ValidateDeeper();
    // Read one element from the buffer
    const Circle & value = m_Buffer->Cursor< Circle >();
    // Advance the buffer cursor
    m_Buffer->Advance< Circle >(1);
    // Return the requested information
    return Circle(value);
}

// ------------------------------------------------------------------------------------------------
Color3 SqBuffer::ReadColor3()
{
    // Validate the managed buffer reference
    ValidateDeeper();
    // Read one element from the buffer
    const Color3 & value = m_Buffer->Cursor< Color3 >();
    // Advance the buffer cursor
    m_Buffer->Advance< Color3 >(1);
    // Return the requested information
    return Color3(value);
}

// ------------------------------------------------------------------------------------------------
Color4 SqBuffer::ReadColor4()
{
    // Validate the managed buffer reference
    ValidateDeeper();
    // Read one element from the buffer
    const Color4 & value = m_Buffer->Cursor< Color4 >();
    // Advance the buffer cursor
    m_Buffer->Advance< Color4 >(1);
    // Return the requested information
    return Color4(value);
}

// ------------------------------------------------------------------------------------------------
Quaternion SqBuffer::ReadQuaternion()
{
    // Validate the managed buffer reference
    ValidateDeeper();
    // Read one element from the buffer
    const Quaternion & value = m_Buffer->Cursor< Quaternion >();
    // Advance the buffer cursor
    m_Buffer->Advance< Quaternion >(1);
    // Return the requested information
    return Quaternion(value);
}

// ------------------------------------------------------------------------------------------------
Sphere SqBuffer::ReadSphere()
{
    // Validate the managed buffer reference
    ValidateDeeper();
    // Read one element from the buffer
    const Sphere & value = m_Buffer->Cursor< Sphere >();
    // Advance the buffer cursor
    m_Buffer->Advance< Sphere >(1);
    // Return the requested information
    return Sphere(value);
}

// ------------------------------------------------------------------------------------------------
Vector2 SqBuffer::ReadVector2()
{
    // Validate the managed buffer reference
    ValidateDeeper();
    // Read one element from the buffer
    const Vector2 & value = m_Buffer->Cursor< Vector2 >();
    // Advance the buffer cursor
    m_Buffer->Advance< Vector2 >(1);
    // Return the requested information
    return Vector2(value);
}

// ------------------------------------------------------------------------------------------------
Vector2i SqBuffer::ReadVector2i()
{
    // Validate the managed buffer reference
    ValidateDeeper();
    // Read one element from the buffer
    const Vector2i & value = m_Buffer->Cursor< Vector2i >();
    // Advance the buffer cursor
    m_Buffer->Advance< Vector2i >(1);
    // Return the requested information
    return Vector2i(value);
}

// ------------------------------------------------------------------------------------------------
Vector3 SqBuffer::ReadVector3()
{
    // Validate the managed buffer reference
    ValidateDeeper();
    // Read one element from the buffer
    const Vector3 & value = m_Buffer->Cursor< Vector3 >();
    // Advance the buffer cursor
    m_Buffer->Advance< Vector3 >(1);
    // Return the requested information
    return Vector3(value);
}

// ------------------------------------------------------------------------------------------------
Vector4 SqBuffer::ReadVector4()
{
    // Validate the managed buffer reference
    ValidateDeeper();
    // Read one element from the buffer
    const Vector4 & value = m_Buffer->Cursor< Vector4 >();
    // Advance the buffer cursor
    m_Buffer->Advance< Vector4 >(1);
    // Return the requested information
    return Vector4(value);
}

// ================================================================================================
void Register_Buffer(HSQUIRRELVM vm)
{
    RootTable(vm).Bind(Typename::Str,
        Class< SqBuffer >(vm, Typename::Str)
        // Constructors
        .Ctor()
        .Ctor< SQInteger >()
        // Core Meta-methods
        .SquirrelFunc(_SC("_typename"), &Typename::Fn)
        // Properties
        .Prop(_SC("Front"), &SqBuffer::GetFront, &SqBuffer::SetFront)
        .Prop(_SC("Next"), &SqBuffer::GetNext, &SqBuffer::SetNext)
        .Prop(_SC("Back"), &SqBuffer::GetBack, &SqBuffer::SetBack)
        .Prop(_SC("Prev"), &SqBuffer::GetPrev, &SqBuffer::SetPrev)
        .Prop(_SC("Cursor"), &SqBuffer::GetCursor, &SqBuffer::SetCursor)
        .Prop(_SC("Before"), &SqBuffer::GetBefore, &SqBuffer::SetBefore)
        .Prop(_SC("After"), &SqBuffer::GetAfter, &SqBuffer::SetAfter)
        .Prop(_SC("Max"), &SqBuffer::GetMax)
        .Prop(_SC("Size"), &SqBuffer::GetSize, &SqBuffer::Adjust)
        .Prop(_SC("Capacity"), &SqBuffer::GetCapacity, &SqBuffer::Adjust)
        .Prop(_SC("Position"), &SqBuffer::GetPosition, &SqBuffer::Move)
        .Prop(_SC("Remaining"), &SqBuffer::GetRemaining)
        // Member Methods
        .Func(_SC("Get"), &SqBuffer::Get)
        .Func(_SC("Set"), &SqBuffer::Set)
        .Func(_SC("Move"), &SqBuffer::Move)
        .Func(_SC("Advance"), &SqBuffer::Advance)
        .Func(_SC("Retreat"), &SqBuffer::Retreat)
        .Func(_SC("Push"), &SqBuffer::Push)
        .Func(_SC("Grow"), &SqBuffer::Grow)
        .Func(_SC("Adjust"), &SqBuffer::Adjust)
        .Func(_SC("WriteByte"), &SqBuffer::WriteUint8)
        .Func(_SC("WriteShort"), &SqBuffer::WriteInt16)
        .Func(_SC("WriteInt"), &SqBuffer::WriteInt32)
        .Func(_SC("WriteFloat"), &SqBuffer::WriteFloat32)
        .Func(_SC("WriteInt8"), &SqBuffer::WriteInt8)
        .Func(_SC("WriteUint8"), &SqBuffer::WriteUint8)
        .Func(_SC("WriteInt16"), &SqBuffer::WriteInt16)
        .Func(_SC("WriteUint16"), &SqBuffer::WriteUint16)
        .Func(_SC("WriteInt32"), &SqBuffer::WriteInt32)
        .Func(_SC("WriteUint32"), &SqBuffer::WriteUint32)
        .Func(_SC("WriteInt64"), &SqBuffer::WriteInt64)
        .Func(_SC("WriteUint64"), &SqBuffer::WriteUint64)
        .Func(_SC("WriteFloat32"), &SqBuffer::WriteFloat32)
        .Func(_SC("WriteFloat64"), &SqBuffer::WriteFloat64)
        .Func(_SC("WriteString"), &SqBuffer::WriteString)
        .Func(_SC("WriteRawString"), &SqBuffer::WriteRawString)
        .Func(_SC("WriteAABB"), &SqBuffer::WriteAABB)
        .Func(_SC("WriteCircle"), &SqBuffer::WriteCircle)
        .Func(_SC("WriteColor3"), &SqBuffer::WriteColor3)
        .Func(_SC("WriteColor4"), &SqBuffer::WriteColor4)
        .Func(_SC("WriteQuaternion"), &SqBuffer::WriteQuaternion)
        .Func(_SC("WriteSphere"), &SqBuffer::WriteSphere)
        .Func(_SC("WriteVector2"), &SqBuffer::WriteVector2)
        .Func(_SC("WriteVector2i"), &SqBuffer::WriteVector2i)
        .Func(_SC("WriteVector3"), &SqBuffer::WriteVector3)
        .Func(_SC("WriteVector4"), &SqBuffer::WriteVector4)
        .Func(_SC("ReadByte"), &SqBuffer::ReadUint8)
        .Func(_SC("ReadShort"), &SqBuffer::ReadInt16)
        .Func(_SC("ReadInt"), &SqBuffer::ReadInt32)
        .Func(_SC("ReadFloat"), &SqBuffer::ReadFloat32)
        .Func(_SC("ReadInt8"), &SqBuffer::ReadInt8)
        .Func(_SC("ReadUint8"), &SqBuffer::ReadUint8)
        .Func(_SC("ReadInt16"), &SqBuffer::ReadInt16)
        .Func(_SC("ReadUint16"), &SqBuffer::ReadUint16)
        .Func(_SC("ReadInt32"), &SqBuffer::ReadInt32)
        .Func(_SC("ReadUint32"), &SqBuffer::ReadUint32)
        .Func(_SC("ReadInt64"), &SqBuffer::ReadInt64)
        .Func(_SC("ReadUint64"), &SqBuffer::ReadUint64)
        .Func(_SC("ReadFloat32"), &SqBuffer::ReadFloat32)
        .Func(_SC("ReadFloat64"), &SqBuffer::ReadFloat64)
        .Func(_SC("ReadString"), &SqBuffer::ReadString)
        .Func(_SC("ReadRawString"), &SqBuffer::ReadRawString)
        .Func(_SC("ReadAABB"), &SqBuffer::ReadAABB)
        .Func(_SC("ReadCircle"), &SqBuffer::ReadCircle)
        .Func(_SC("ReadColor3"), &SqBuffer::ReadColor3)
        .Func(_SC("ReadColor4"), &SqBuffer::ReadColor4)
        .Func(_SC("ReadQuaternion"), &SqBuffer::ReadQuaternion)
        .Func(_SC("ReadSphere"), &SqBuffer::ReadSphere)
        .Func(_SC("ReadVector2"), &SqBuffer::ReadVector2)
        .Func(_SC("ReadVector2i"), &SqBuffer::ReadVector2i)
        .Func(_SC("ReadVector3"), &SqBuffer::ReadVector3)
        .Func(_SC("ReadVector4"), &SqBuffer::ReadVector4)
    );
}

} // Namespace:: SqMod
