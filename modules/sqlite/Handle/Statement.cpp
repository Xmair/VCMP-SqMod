// ------------------------------------------------------------------------------------------------
#include "Handle/Statement.hpp"
#include "Handle/Connection.hpp"

// ------------------------------------------------------------------------------------------------
#include <cstring>

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
StmtHnd::StmtHnd(const ConnRef & conn)
    : mPtr(nullptr)
    , mStatus(SQLITE_OK)
    , mConn(conn)
    , mQuery()
    , mColumns(0)
    , mParameters(0)
    , mIndexes()
    , mGood(false)
    , mDone(false)
{
    /* ... */
}

// ------------------------------------------------------------------------------------------------
StmtHnd::~StmtHnd()
{
    // Is there anything to finalize?
    if (mPtr != nullptr)
    {
        // Attempt to finalize the statement
        if ((sqlite3_finalize(mPtr)) != SQLITE_OK)
        {
            SqMod_LogErr("Unable to finalize SQLite statement [%s]", mConn->ErrMsg());
        }
    }
}

// ------------------------------------------------------------------------------------------------
void StmtHnd::Create(CSStr query, SQInteger length)
{
    // Make sure a previous statement doesn't exist
    if (mPtr)
    {
        STHROWF("Unable to prepare statement. Statement already prepared");
    }
    // Is the specified database connection is valid?
    else if (!mConn)
    {
        STHROWF("Unable to prepare statement. Invalid connection handle");
    }
    // Is the specified query string valid?
    else if (!query || !length || *query == '\0')
    {
        STHROWF("Unable to prepare statement. Invalid or empty query string");
    }
    // Save the query string
    mQuery.assign(query, length);
    // Attempt to prepare a statement with the specified query string
    if ((mStatus = sqlite3_prepare_v2(mConn->mPtr, mQuery.c_str(), ConvTo< Int32 >::From(mQuery.size()),
                                            &mPtr, nullptr)) != SQLITE_OK)
    {
        // Clear the query string since it failed
        mQuery.clear();
        // Explicitly make sure the handle is null
        mPtr = nullptr;
        // Now it's safe to throw the error
        STHROWF("Unable to prepare statement [%s]", mConn->ErrMsg());
    }
    else
    {
        // Obtain the number of available columns
        mColumns = sqlite3_column_count(mPtr);
        // Obtain the number of available parameters
        mParameters = sqlite3_bind_parameter_count(mPtr);
    }
}

// ------------------------------------------------------------------------------------------------
Int32 StmtHnd::GetColumnIndex(CSStr name, SQInteger length)
{
    // Validate the handle
    if (!mPtr)
    {
        STHROWF("Invalid SQLite statement");
    }
    // Are the names cached?
    else if (mIndexes.empty())
    {
        for (Int32 i = 0; i < mColumns; ++i)
        {
            // Get the column name at the current index
            CSStr name = static_cast< CSStr >(sqlite3_column_name(mPtr, i));
            // Validate the name
            if (!name)
            {
                STHROWF("Unable to retrieve column name for index (%d)", i);
            }
            // Save it to guarantee the same lifetime as this instance
            else
            {
                mIndexes[name] = i;
            }
        }
    }
    const String str(name, length < 0 ? std::strlen(name) : length);
    // Attempt to find the specified column
    const Indexes::iterator itr = mIndexes.find(str);
    // Was there a column with the specified name?
    if (itr != mIndexes.end())
    {
        return itr->second;
    }
    // No such column exists (expecting the invoker to validate the result)
    return -1;
}

// ------------------------------------------------------------------------------------------------
CCStr StmtHnd::ErrStr() const
{
    return mConn ? sqlite3_errstr(sqlite3_errcode(mConn->mPtr)) : _SC("");
}

// ------------------------------------------------------------------------------------------------
CCStr StmtHnd::ErrMsg() const
{
    return mConn ? sqlite3_errmsg(mConn->mPtr) : _SC("");
}

// ------------------------------------------------------------------------------------------------
Int32 StmtHnd::ErrNo() const
{
    return mConn ? sqlite3_errcode(mConn->mPtr) : SQLITE_NOMEM;
}

// ------------------------------------------------------------------------------------------------
Int32 StmtHnd::ExErrNo() const
{
    return mConn ? sqlite3_extended_errcode(mConn->mPtr) : SQLITE_NOMEM;
}

} // Namespace:: SqMod
