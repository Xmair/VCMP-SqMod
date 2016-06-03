#ifndef _SQMYSQL_HANDLE_CONNECTION_HPP_
#define _SQMYSQL_HANDLE_CONNECTION_HPP_

// ------------------------------------------------------------------------------------------------
#include "Common.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

/* ------------------------------------------------------------------------------------------------
 * Manages a reference counted database connection handle.
*/
class ConnHnd
{
    // --------------------------------------------------------------------------------------------
    friend class Connection;
    friend class Statement;

public:

    // --------------------------------------------------------------------------------------------
    typedef MYSQL           Type; // The managed type.

    // --------------------------------------------------------------------------------------------
    typedef Type*           Pointer; // Pointer to the managed type.
    typedef const Type*     ConstPtr; // Constant pointer to the managed type.

    // --------------------------------------------------------------------------------------------
    typedef Type&           Reference; // Reference to the managed type.
    typedef const Type&     ConstRef; // Constant reference to the managed type.

    // --------------------------------------------------------------------------------------------
    typedef unsigned int    Counter; // Reference counter type.

    // --------------------------------------------------------------------------------------------
    typedef MYSQL_RES       ResType; // Database result type.

    /* --------------------------------------------------------------------------------------------
     * Validate the connection handle and throw an error if invalid.
    */
    void Validate() const;

protected:

    /* --------------------------------------------------------------------------------------------
     * The structure that holds the data associated with a certain connection.
    */
    struct Handle
    {
        // ----------------------------------------------------------------------------------------
        Pointer     mPtr; // The connection handle resource.
        Counter     mRef; // Reference count to the managed handle.

        // ----------------------------------------------------------------------------------------
        Uint32      mErrNo; // Last received error string.
        String      mErrStr; // Last received error message.

        // ----------------------------------------------------------------------------------------
        Uint16      mPort; // Server port.
        String      mHost; // Host address.
        String      mUser; // User name user.
        String      mPass; // User password.
        String      mName; // Database name.
        String      mSocket; // Unix socket.
        Ulong       mFlags; // Client flags.

        // ----------------------------------------------------------------------------------------
        String      mSSL_Key; // SSL key.
        String      mSSL_Cert; // SSL certificate.
        String      mSSL_CA; // SSL certificate authority.
        String      mSSL_CA_Path; // SSL certificate authority path.
        String      mSSL_Cipher; // SSL Cipher.

        // ----------------------------------------------------------------------------------------
        String      mCharset; // Default connection character set.

        // ----------------------------------------------------------------------------------------
        bool        mAutoCommit; // Whether autocommit is enabled on this connection.
        bool        mInTransaction; // Whether the connection is in the middle of a transaction.

        /* ----------------------------------------------------------------------------------------
         * Base constructor.
        */
        Handle(const Account & acc);

        /* ----------------------------------------------------------------------------------------
         * Destructor.
        */
        ~Handle();

        /* ----------------------------------------------------------------------------------------
         * Grab the current error in the connection handle and throw it.
        */
#if defined(_DEBUG) || defined(SQMOD_EXCEPTLOC)
        void ThrowCurrent(CCStr act, CCStr file, Int32 line);
#else
        void ThrowCurrent(CCStr act);
#endif // _DEBUG

        /* ----------------------------------------------------------------------------------------
         * Disconnect the managed connection handle.
        */
        void Disconnect();

        /* ----------------------------------------------------------------------------------------
         * Execute a query on the server.
        */
        Uint64 Execute(CSStr query, Ulong size = 0UL);
    };

private:

    // --------------------------------------------------------------------------------------------
    Handle * m_Hnd; // The managed handle instance.

    /* --------------------------------------------------------------------------------------------
     * Grab a strong reference to a connection handle.
    */
    void Grab()
    {
        if (m_Hnd)
        {
            ++(m_Hnd->mRef);
        }
    }

    /* --------------------------------------------------------------------------------------------
     * Drop a strong reference to a connection handle.
    */
    void Drop()
    {
        if (m_Hnd && --(m_Hnd->mRef) == 0)
        {
            delete m_Hnd; // Let the destructor take care of cleaning up (if necessary)
        }
    }

    /* --------------------------------------------------------------------------------------------
     * Base constructor.
    */
    ConnHnd(const Account & acc)
        : m_Hnd(new Handle(acc))
    {
        /* ... */
    }

public:

    /* --------------------------------------------------------------------------------------------
     * Default constructor (null).
    */
    ConnHnd()
        : m_Hnd(nullptr)
    {
        /* ... */
    }

    /* --------------------------------------------------------------------------------------------
     * Copy constructor.
    */
    ConnHnd(const ConnHnd & o)
        : m_Hnd(o.m_Hnd)
    {
        Grab();
    }

    /* --------------------------------------------------------------------------------------------
     * Move constructor.
    */
    ConnHnd(ConnHnd && o)
        : m_Hnd(o.m_Hnd)
    {
        o.m_Hnd = nullptr;
    }

    /* --------------------------------------------------------------------------------------------
     * Destructor.
    */
    ~ConnHnd()
    {
        Drop();
    }

    /* --------------------------------------------------------------------------------------------
     * Copy assignment operator.
    */
    ConnHnd & operator = (const ConnHnd & o)
    {
        if (m_Hnd != o.m_Hnd)
        {
            Drop();
            m_Hnd = o.m_Hnd;
            Grab();
        }
        return *this;
    }

    /* --------------------------------------------------------------------------------------------
     * Move assignment operator.
    */
    ConnHnd & operator = (ConnHnd && o)
    {
        if (m_Hnd != o.m_Hnd)
        {
            m_Hnd = o.m_Hnd;
            o.m_Hnd = nullptr;
        }

        return *this;
    }

    /* --------------------------------------------------------------------------------------------
     * Status assignment operator.
    */
    ConnHnd & operator = (Uint32 status)
    {
        if (m_Hnd)
        {
            m_Hnd->mErrNo = status;
        }
        return *this;
    }

    /* --------------------------------------------------------------------------------------------
     * Perform an equality comparison between two connection handles.
    */
    bool operator == (const ConnHnd & o) const
    {
        return (m_Hnd == o.m_Hnd);
    }

    /* --------------------------------------------------------------------------------------------
     * Perform an inequality comparison between two connection handles.
    */
    bool operator != (const ConnHnd & o) const
    {
        return (m_Hnd != o.m_Hnd);
    }

    /* --------------------------------------------------------------------------------------------
     * Perform an equality comparison with an integer value status.
    */
    bool operator == (Uint32 status) const
    {
        if (m_Hnd)
        {
            return (m_Hnd->mErrNo == status);
        }
        return false;
    }

    /* --------------------------------------------------------------------------------------------
     * Perform an inequality comparison with an integer value status.
    */
    bool operator != (Uint32 status) const
    {
        if (m_Hnd)
        {
            return (m_Hnd->mErrNo != status);
        }
        return false;
    }

    /* --------------------------------------------------------------------------------------------
     * Implicit conversion to boolean for use in boolean operations.
    */
    operator bool () const
    {
        return (m_Hnd != nullptr) && (m_Hnd->mPtr != nullptr);
    }

    /* --------------------------------------------------------------------------------------------
     * Implicit conversion to the managed instance.
    */
    operator Pointer ()
    {
        return (m_Hnd != nullptr) ? m_Hnd->mPtr : nullptr;
    }

    /* --------------------------------------------------------------------------------------------
     * Implicit conversion to the managed instance.
    */
    operator Pointer () const
    {
        return (m_Hnd != nullptr) ? m_Hnd->mPtr : nullptr;
    }

    /* --------------------------------------------------------------------------------------------
     * Implicit conversion to the managed instance.
    */
    operator Reference ()
    {
        assert((m_Hnd != nullptr) && (m_Hnd->mPtr != nullptr));
        return *(m_Hnd->mPtr);
    }

    /* --------------------------------------------------------------------------------------------
     * Implicit conversion to the managed instance.
    */
    operator ConstRef () const
    {
        assert((m_Hnd != nullptr) && (m_Hnd->mPtr != nullptr));
        return *(m_Hnd->mPtr);
    }

    /* --------------------------------------------------------------------------------------------
     * Member operator for dereferencing the managed pointer.
    */
    Handle * operator -> () const
    {
        assert(m_Hnd != nullptr);
        return m_Hnd;
    }

    /* --------------------------------------------------------------------------------------------
     * Indirection operator for obtaining a reference of the managed pointer.
    */
    Handle & operator * () const
    {
        assert(m_Hnd != nullptr);
        return *m_Hnd;
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve the raw handle structure pointer.
    */
    Handle * HndPtr()
    {
        return m_Hnd;
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve the raw handle structure pointer.
    */
    Handle * HndPtr() const
    {
        return m_Hnd;
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve the number of active references to the managed instance.
    */
    Counter Count() const
    {
        return (m_Hnd != nullptr) ? m_Hnd->mRef : 0;
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve the handle reference but only if valid.
    */
    Handle & GetHnd()
    {
        // Validate the managed handle
        Validate();
        // Return the requesed information
        return *m_Hnd;
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve the handle reference but only if valid.
    */
    const Handle & GetHnd() const
    {
        // Validate the managed handle
        Validate();
        // Return the requesed information
        return *m_Hnd;
    }
};

} // Namespace:: SqMod

#endif // _SQMYSQL_HANDLE_CONNECTION_HPP_
