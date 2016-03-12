#ifndef _ENTITY_SPRITE_HPP_
#define _ENTITY_SPRITE_HPP_

// ------------------------------------------------------------------------------------------------
#include "Base/Shared.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

/* ------------------------------------------------------------------------------------------------
 * Manages a single sprite entity.
*/
class CSprite
{
    // --------------------------------------------------------------------------------------------
    friend class Core;

private:

    /* --------------------------------------------------------------------------------------------
     * Identifier of the managed entity.
    */
    Int32   m_ID;

    /* --------------------------------------------------------------------------------------------
     * User tag associated with this instance.
    */
    String  m_Tag;

    /* --------------------------------------------------------------------------------------------
     * User data associated with this instance.
    */
    Object  m_Data;

    /* --------------------------------------------------------------------------------------------
     * Base constructor.
    */
    CSprite(Int32 id);

public:

    /* --------------------------------------------------------------------------------------------
     * Maximum possible number that could represent an identifier for this entity type.
    */
    static const Int32 Max;

    /* --------------------------------------------------------------------------------------------
     * Copy constructor. (disabled)
    */
    CSprite(const CSprite &) = delete;

    /* --------------------------------------------------------------------------------------------
     * Move constructor. (disabled)
    */
    CSprite(CSprite &&) = delete;

    /* --------------------------------------------------------------------------------------------
     * Destructor.
    */
    ~CSprite();

    /* --------------------------------------------------------------------------------------------
     * Copy assignment operator. (disabled)
    */
    CSprite & operator = (const CSprite &) = delete;

    /* --------------------------------------------------------------------------------------------
     * Move assignment operator. (disabled)
    */
    CSprite & operator = (CSprite &&) = delete;

    /* --------------------------------------------------------------------------------------------
     * See whether this instance manages a valid entity.
    */
    void Validate() const
    {
        if (INVALID_ENTITY(m_ID))
        {
            SqThrowF("Invalid sprite reference [%s]", m_Tag.c_str());
        }
    }

    /* --------------------------------------------------------------------------------------------
     * Used by the script engine to compare two instances of this type.
    */
    Int32 Cmp(const CSprite & o) const;

    /* --------------------------------------------------------------------------------------------
     * Used by the script engine to convert an instance of this type to a string.
    */
    const String & ToString() const;

    /* --------------------------------------------------------------------------------------------
     * Used by the script engine to retrieve the name from instances of this type.
    */
    static SQInteger Typename(HSQUIRRELVM vm);

    /* --------------------------------------------------------------------------------------------
     * Retrieve the identifier of the entity managed by this instance.
    */
    Int32 GetID() const
    {
        return m_ID;
    }

    /* --------------------------------------------------------------------------------------------
     * Check whether this instance manages a valid entity.
    */
    bool IsActive() const
    {
        return VALID_ENTITY(m_ID);
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve the associated user tag.
    */
    const String & GetTag() const;

    /* --------------------------------------------------------------------------------------------
     * Modify the associated user tag.
    */
    void SetTag(CSStr tag);

    /* --------------------------------------------------------------------------------------------
     * Retrieve the associated user data.
    */
    Object & GetData();

    /* --------------------------------------------------------------------------------------------
     * Modify the associated user data.
    */
    void SetData(Object & data);

    /* --------------------------------------------------------------------------------------------
     * Destroy the managed sprite entity.
    */
    bool Destroy()
    {
        return Destroy(0, NullObject());
    }

    /* --------------------------------------------------------------------------------------------
     * Destroy the managed sprite entity.
    */
    bool Destroy(Int32 header)
    {
        return Destroy(header, NullObject());
    }

    /* --------------------------------------------------------------------------------------------
     * Destroy the managed sprite entity.
    */
    bool Destroy(Int32 header, Object & payload);

    /* --------------------------------------------------------------------------------------------
     * Bind to an event supported by this entity type.
    */
    void BindEvent(Int32 evid, Object & env, Function & func) const;

    /* --------------------------------------------------------------------------------------------
     * Show the managed sprite entity to all players on the server.
    */
    void ShowAll() const;

    /* --------------------------------------------------------------------------------------------
     * Show the managed sprite entity to the specified player entity.
    */
    void ShowFor(CPlayer & player) const;

    /* --------------------------------------------------------------------------------------------
     * Show the managed sprite entity to all players in the specified range.
    */
    void ShowRange(Int32 first, Int32 last) const;

    /* --------------------------------------------------------------------------------------------
     * Hide the managed sprite entity from all players on the server.
    */
    void HideAll() const;

    /* --------------------------------------------------------------------------------------------
     * Hide the managed sprite entity from the specified player entity.
    */
    void HideFor(CPlayer & player) const;

    /* --------------------------------------------------------------------------------------------
     * Hide the managed sprite entity from all players in the specified range.
    */
    void HideRange(Int32 first, Int32 last) const;

    /* --------------------------------------------------------------------------------------------
     * Set the position of the managed sprite entity for all players on the server.
    */
    void SetPositionAll(const Vector2i & pos) const;

    /* --------------------------------------------------------------------------------------------
     * Set the position of the managed sprite entity for all players on the server.
    */
    void SetPositionAllEx(Int32 x, Int32 y) const;

    /* --------------------------------------------------------------------------------------------
     * Set the position of the managed sprite entity for the specified player entity.
    */
    void SetPositionFor(CPlayer & player, const Vector2i & pos) const;

    /* --------------------------------------------------------------------------------------------
     * Set the position of the managed sprite entity for the specified player entity.
    */
    void SetPositionForEx(CPlayer & player, Int32 x, Int32 y) const;

    /* --------------------------------------------------------------------------------------------
     * Set the position of the managed sprite entity for all players in the specified range.
    */
    void SetPositionRange(Int32 first, Int32 last, const Vector2i & pos) const;

    /* --------------------------------------------------------------------------------------------
     * Set the center of the managed sprite entity for all players on the server.
    */
    void SetCenterAll(const Vector2i & pos) const;

    /* --------------------------------------------------------------------------------------------
     * Set the center of the managed sprite entity for all players on the server.
    */
    void SetCenterAllEx(Int32 x, Int32 y) const;

    /* --------------------------------------------------------------------------------------------
     * Set the center of the managed sprite entity for the specified player entity.
    */
    void SetCenterFor(CPlayer & player, const Vector2i & pos) const;

    /* --------------------------------------------------------------------------------------------
     * Set the center of the managed sprite entity for the specified player entity.
    */
    void SetCenterForEx(CPlayer & player, Int32 x, Int32 y) const;

    /* --------------------------------------------------------------------------------------------
     * Set the center of the managed sprite entity for all players in the specified range.
    */
    void SetCenterRange(Int32 first, Int32 last, const Vector2i & pos) const;

    /* --------------------------------------------------------------------------------------------
     * Set the rotation of the managed sprite entity for all players on the server.
    */
    void SetRotationAll(Float32 rot) const;

    /* --------------------------------------------------------------------------------------------
     * Set the rotation of the managed sprite entity for the specified player entity.
    */
    void SetRotationFor(CPlayer & player, Float32 rot) const;

    /* --------------------------------------------------------------------------------------------
     * Set the rotation of the managed sprite entity for all players in the specified range.
    */
    void SetRotationRange(Int32 first, Int32 last, Float32 rot) const;

    /* --------------------------------------------------------------------------------------------
     * Set the alpha of the managed sprite entity for all players on the server.
    */
    void SetAlphaAll(Uint8 alpha) const;

    /* --------------------------------------------------------------------------------------------
     * Set the alpha of the managed sprite entity for the specified player entity.
    */
    void SetAlphaFor(CPlayer & player, Uint8 alpha) const;

    /* --------------------------------------------------------------------------------------------
     * Set the alpha of the managed sprite entity for all players in the specified range.
    */
    void SetAlphaRange(Int32 first, Int32 last, Uint8 alpha) const;

    /* --------------------------------------------------------------------------------------------
     * Retrieve the file path of the texture used by the managed sprite entity.
    */
    const String & GetFilePath() const;
};

} // Namespace:: SqMod

#endif // _ENTITY_SPRITE_HPP_