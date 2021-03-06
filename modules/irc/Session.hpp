#ifndef _SQIRC_SESSION_HPP_
#define _SQIRC_SESSION_HPP_

// ------------------------------------------------------------------------------------------------
#include "Common.hpp"

// ------------------------------------------------------------------------------------------------
#include <vector>

// ------------------------------------------------------------------------------------------------
namespace SqMod {

/* ------------------------------------------------------------------------------------------------
 * Manages a single connection to an IRC network.
*/
class Session
{
public:

    // --------------------------------------------------------------------------------------------
    typedef std::vector< Session* > Sessions; /* The type of container to store sessions. */

    /* --------------------------------------------------------------------------------------------
     * Process all sessions.
    */
    static void Process();

    /* --------------------------------------------------------------------------------------------
     * Terminate all sessions and release their resources.
    */
    static void Terminate();

protected:

    /* --------------------------------------------------------------------------------------------
     * Structure that tells the IRC library what functions to call on which events.
    */
    static irc_callbacks_t  s_Callbacks;

    /* --------------------------------------------------------------------------------------------
     * Whether the callbacks structure was initialized or not.
    */
    static bool             s_Initialized;

    /* --------------------------------------------------------------------------------------------
     * The primary session if only a single session was created.
    */
    static Session*         s_Session;

    /* --------------------------------------------------------------------------------------------
     * All the sessions if more than a session was created.
    */
    static Sessions         s_Sessions;

    /* --------------------------------------------------------------------------------------------
     * Retrieve a pre-configured callbacks structure to be assigned to a session.
    */
    static irc_callbacks_t * GetCallbacks();

protected:

    /* --------------------------------------------------------------------------------------------
     * Pool for events on the managed session.
    */
    void Update();

    /* --------------------------------------------------------------------------------------------
     * Release session resources.
    */
    void Release();

    /* --------------------------------------------------------------------------------------------
     * Completely destroy the internal session instance and release resources.
    */
    void Destroy();

    /* --------------------------------------------------------------------------------------------
     * Make sure a valid session exists and throw an error if it doesn't.
    */
    void Validate() const;

    /* --------------------------------------------------------------------------------------------
     * See whether this session is connected to a server and throw an error if not.
    */
    void ValidateConnection() const;

    /* --------------------------------------------------------------------------------------------
     * See whether this session is NOT! connected to a server and throw an error if it is.
    */
    void IsNotConnected() const;

    /* --------------------------------------------------------------------------------------------
     * Validate a session instance used by an event and log an error if it's invalid.
    */
    static bool ValidateEventSession(Session * ptr);

private:

    // --------------------------------------------------------------------------------------------
    irc_session_t*  m_Session; // The managed IRC session structure.

    // --------------------------------------------------------------------------------------------
    String          m_Server; // Server address.
    String          m_Passwd; // Account password.
    String          m_Nick; // Nickname.
    String          m_User; // User name.
    String          m_Name; // Real name.

    // --------------------------------------------------------------------------------------------
    Int32           m_Port; // Server port.

    // --------------------------------------------------------------------------------------------
    Int32           m_LastCode; // Last error code that could not be returned directly.
    Uint32          m_PoolTime; // How much time to wait when pooling for session events.
    Uint32          m_Tries; // How many times to retry connection.
    Uint32          m_Wait; // How many milliseconds to wait between each try.
    Uint32          m_LeftTries; // How many tries are left.
    Int64           m_NextTry; // When should the session attempt to connect again.

    // --------------------------------------------------------------------------------------------
    Int64           m_SessionTime; // The time when the session was created.

    // --------------------------------------------------------------------------------------------
    bool            m_Reconnect; // Whether the session should try to reconnect.

    // --------------------------------------------------------------------------------------------
    bool            m_IPv6; // Whether the session was connected to an ipv6 address.

    // --------------------------------------------------------------------------------------------
    String          m_Tag; // User tag.
    Object          m_Data; // User data.

    /* --------------------------------------------------------------------------------------------
     * Script callbacks.
    */
    Function        m_OnConnect;
    Function        m_OnNick;
    Function        m_OnQuit;
    Function        m_OnJoin;
    Function        m_OnPart;
    Function        m_OnMode;
    Function        m_OnUmode;
    Function        m_OnTopic;
    Function        m_OnKick;
    Function        m_OnChannel;
    Function        m_OnPrivMsg;
    Function        m_OnNotice;
    Function        m_OnChannelNotice;
    Function        m_OnInvite;
    Function        m_OnCtcpReq;
    Function        m_OnCtcpRep;
    Function        m_OnCtcpAction;
    Function        m_OnUnknown;
    Function        m_OnNumeric;
    Function        m_OnDccChatReq;
    Function        m_OnDccSendReq;

public:

    /* --------------------------------------------------------------------------------------------
     * Default constructor.
    */
    Session();

    /* --------------------------------------------------------------------------------------------
     * Copy constructor. (disabled)
    */
    Session(const Session & o) = delete;

    /* --------------------------------------------------------------------------------------------
     * Move constructor. (disabled)
    */
    Session(Session && o) = delete;

    /* --------------------------------------------------------------------------------------------
     * Destructor.
    */
    ~Session();

    /* --------------------------------------------------------------------------------------------
     * Copy assignment operator. (disabled)
    */
    Session & operator = (const Session & o) =  delete;

    /* --------------------------------------------------------------------------------------------
     * Move assignment operator. (disabled)
    */
    Session & operator = (Session && o) =  delete;

    /* --------------------------------------------------------------------------------------------
     * Used by the script engine to compare two instances of this type.
    */
    Int32 Cmp(const Session & o) const
    {
        if (m_Session == o.m_Session)
        {
            return 0;
        }
        else if (m_Session > o.m_Session)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    /* --------------------------------------------------------------------------------------------
     * Used by the script engine to convert an instance of this type to a string.
    */
    CSStr ToString() const
    {
        return m_Server.c_str();
    }

    /* --------------------------------------------------------------------------------------------
     * Used by the script engine to retrieve the name from instances of this type.
    */
    static SQInteger Typename(HSQUIRRELVM vm);

    /* --------------------------------------------------------------------------------------------
     * Retrieve the actual session handle.
    */
    irc_session_t * GetHandle() const
    {
        return m_Session;
    }

    /* --------------------------------------------------------------------------------------------
     * See whether this session is valid.
    */
    bool IsValid() const
    {
        return m_Session;
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve the user tag.
    */
    CSStr GetTag() const
    {
        return m_Tag.c_str();
    }

    /* --------------------------------------------------------------------------------------------
     * Change the user tag.
    */
    void SetTag(CSStr tag)
    {
        m_Tag.assign(tag);
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve the user data.
    */
    Object & GetData()
    {
        // Validate the handle
        Validate();
        // Return the requested information
        return m_Data;
    }

    /* --------------------------------------------------------------------------------------------
     * Change the user data.
    */
    void SetData(Object & data)
    {
        // Validate the handle
        Validate();
        // Perform the requested operation
        m_Data = data;
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve an event supported by this session.
    */
    Function & GetEvent(Int32 evid);

    /* --------------------------------------------------------------------------------------------
     * Bind to an event supported by this session.
    */
    void BindEvent(Int32 evid, Object & env, Function & func);

    /* --------------------------------------------------------------------------------------------
     * Retrieve the server address.
    */
    CSStr GetServer() const
    {
        return m_Server.c_str();
    }

    /* --------------------------------------------------------------------------------------------
     * Modify the server address.
    */
    void SetServer(CSStr server)
    {
        // Validate the handle
        Validate();
        // Make sure we are allowed to change the server
        IsNotConnected();
        // Perform the requested operation
        m_Server.assign(server);
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve the account password.
    */
    CSStr GetPassword() const
    {
        return m_Passwd.c_str();
    }

    /* --------------------------------------------------------------------------------------------
     * Modify the account password.
    */
    void SetPassword(CSStr passwd)
    {        // Validate the handle
        Validate();
        // Make sure we are allowed to change the server
        IsNotConnected();
        // Perform the requested operation
        m_Passwd.assign(passwd);
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve the nickname.
    */
    CSStr GetNick() const
    {
        return m_Nick.c_str();
    }

    /* --------------------------------------------------------------------------------------------
     * Modify the nickname.
    */
    void SetNick(CSStr nick);

    /* --------------------------------------------------------------------------------------------
     * Retrieve the user name.
    */
    CSStr GetUser() const
    {
        return m_User.c_str();
    }

    /* --------------------------------------------------------------------------------------------
     * Modify the user name.
    */
    void SetUser(CSStr user)
    {
        // Validate the handle
        Validate();
        // Make sure we are allowed to change the server
        IsNotConnected();
        // Perform the requested operation
        m_User.assign(user);
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve the real name.
    */
    CSStr GetName() const
    {
        return m_Name.c_str();
    }

    /* --------------------------------------------------------------------------------------------
     * Modify the real name.
    */
    void SetName(CSStr name)
    {
        // Validate the handle
        Validate();
        // Make sure we are allowed to change the server
        IsNotConnected();
        // Perform the requested operation
        m_Name.assign(name);
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve the server port number.
    */
    Uint32 GetPort() const
    {
        return m_Port;
    }

    /* --------------------------------------------------------------------------------------------
     * Modify the server port number.
    */
    void SetPort(Uint32 num);

    /* --------------------------------------------------------------------------------------------
     * Retrieve the amount of time to pool for session events.
    */
    Uint32 GetPoolTime() const
    {
        return m_PoolTime;
    }

    /* --------------------------------------------------------------------------------------------
     * Modify the amount of time to pool for session events.
    */
    void SetPoolTime(Uint32 num)
    {
        m_PoolTime = num;
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve the last error code that could not be returned directly.
    */
    Int32 GetLastCode() const
    {
        return m_LastCode;
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve the amount of connection attempts.
    */
    Uint32 GetTries() const
    {
        return m_Tries;
    }

    /* --------------------------------------------------------------------------------------------
     * Modify the amount of connection attempts.
    */
    void SetTries(Uint32 num)
    {
        m_Tries = num;
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve the amount of time in milliseconds to wait between connection attempts.
    */
    Uint32 GetWait() const
    {
        return m_Wait;
    }

    /* --------------------------------------------------------------------------------------------
     * Modify the amount of time in milliseconds to wait between connection attempts.
    */
    void SetWait(Uint32 ms)
    {
        m_Wait = ms;
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve how many times are left to try to connect.
    */
    Uint32 GetLeftTries() const
    {
        return m_LeftTries;
    }

    /* --------------------------------------------------------------------------------------------
     * Modify how many times are left to try to connect.
    */
    void SetLeftTries(Uint32 num)
    {
        m_LeftTries = num;
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve when the next connection retry should be performed.
    */
    Object GetNextTry() const;

    /* --------------------------------------------------------------------------------------------
     * Modify when the next connection retry should be performed.
    */
    void SetNextTry(Object & tm);

    /* --------------------------------------------------------------------------------------------
     * Retrieve the session uptime.
    */
    Object GetSessionTime() const;

    /* --------------------------------------------------------------------------------------------
     * See whether the session is currently trying to reconnect.
    */
    bool GetReconnect() const
    {
        return m_Reconnect;
    }

    /* --------------------------------------------------------------------------------------------
     * See whether the session is connected to an ipv6 address.
    */
    bool GetIPv6() const
    {
        return m_IPv6;
    }

    /* --------------------------------------------------------------------------------------------
     * Initiates the connection to the IPv4 IRC server.
    */
    Int32 Connect();

    /* --------------------------------------------------------------------------------------------
     * Initiates the connection to the IPv4 IRC server.
    */
    Int32 Connect(CSStr server, Uint32 port, CSStr nick)
    {
        return Connect(server, port, nick, nullptr, nullptr, nullptr);
    }

    /* --------------------------------------------------------------------------------------------
     * Initiates the connection to the IPv4 IRC server.
    */
    Int32 Connect(CSStr server, Uint32 port, CSStr nick, CSStr passwd)
    {
        return Connect(server, port, nick, passwd, nullptr, nullptr);
    }

    /* --------------------------------------------------------------------------------------------
     * Initiates the connection to the IPv4 IRC server.
    */
    Int32 Connect(CSStr server, Uint32 port, CSStr nick, CSStr passwd, CSStr user)
    {
        return Connect(server, port, nick, passwd, user, nullptr);
    }

    /* --------------------------------------------------------------------------------------------
     * Initiates the connection to the IPv4 IRC server.
    */
    Int32 Connect(CSStr server, Uint32 port, CSStr nick, CSStr passwd, CSStr user, CSStr name);

    /* --------------------------------------------------------------------------------------------
     * Initiates the connection to the IPv6 IRC server.
    */
    Int32 Connect6();

    /* --------------------------------------------------------------------------------------------
     * Initiates the connection to the IPv6 IRC server.
    */
    Int32 Connect6(CSStr server, Uint32 port, CSStr nick)
    {
        return Connect(server, port, nick, nullptr, nullptr, nullptr);
    }

    /* --------------------------------------------------------------------------------------------
     * Initiates the connection to the IPv6 IRC server.
    */
    Int32 Connect6(CSStr server, Uint32 port, CSStr nick, CSStr passwd)
    {
        return Connect(server, port, nick, passwd, nullptr, nullptr);
    }

    /* --------------------------------------------------------------------------------------------
     * Initiates the connection to the IPv6 IRC server.
    */
    Int32 Connect6(CSStr server, Uint32 port, CSStr nick, CSStr passwd, CSStr user)
    {
        return Connect(server, port, nick, passwd, user, nullptr);
    }

    /* --------------------------------------------------------------------------------------------
     * Initiates the connection to the IPv6 IRC server.
    */
    Int32 Connect6(CSStr server, Uint32 port, CSStr nick, CSStr passwd, CSStr user, CSStr name);

    /* --------------------------------------------------------------------------------------------
     * Disconnect from the currently connected server.
    */
    void Disconnect();

    /* --------------------------------------------------------------------------------------------
     * See whether this session is connected to a server or not.
    */
    bool IsConnected()
    {
        return (m_Session && irc_is_connected(m_Session));
    }

    /* --------------------------------------------------------------------------------------------
     * Joins a channel on the connected server.
    */
    Int32 CmdJoin(CSStr channel)
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_join(m_Session, channel, nullptr);
    }

    /* --------------------------------------------------------------------------------------------
     * Joins a channel on the connected server using a secret key.
    */
    Int32 CmdJoin(CSStr channel, CSStr key)
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_join(m_Session, channel, key);
    }

    /* --------------------------------------------------------------------------------------------
     * Leave from a certain channel on the connected server.
    */
    Int32 CmdPart(CSStr channel)
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_part(m_Session, channel);
    }

    /* --------------------------------------------------------------------------------------------
     * Invite someone into a channel on the connected server.
    */
    Int32 CmdInvite(CSStr nick, CSStr channel)
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_invite(m_Session, nick, channel);
    }

    /* --------------------------------------------------------------------------------------------
     * Ask the IRC server for the list of the users who are joined the specified channel.
    */
    Int32 CmdNames(CSStr channel)
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_names(m_Session, channel);
    }

    /* --------------------------------------------------------------------------------------------
     * Ask the IRC server for the active (existing) channels list.
    */
    Int32 CmdList()
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_list(m_Session, nullptr);
    }

    /* --------------------------------------------------------------------------------------------
     * Ask the IRC server for the active (existing) channels from a specific list.
    */
    Int32 CmdList(CSStr channel)
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_list(m_Session, channel);
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve the topic (title) of the specified channel on the connected server.
    */
    Int32 CmdTopic(CSStr channel)
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_topic(m_Session, channel, nullptr);
    }

    /* --------------------------------------------------------------------------------------------
     * Change the topic (title) of the specified channel on the connected server.
    */
    Int32 CmdTopic(CSStr channel, CSStr topic)
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_topic(m_Session, channel, topic);
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve the modes of the specified channel on the connected server.
    */
    Int32 CmdChannelMode(CSStr channel)
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_channel_mode(m_Session, channel, nullptr);
    }

    /* --------------------------------------------------------------------------------------------
     * Change the modes of the specified channel on the connected server.
    */
    Int32 CmdChannelMode(CSStr channel, CSStr mode)
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_channel_mode(m_Session, channel, mode);
    }

    /* --------------------------------------------------------------------------------------------
     * Retrieve the modes on the connected server.
    */
    Int32 CmdUserMode()
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_user_mode(m_Session, nullptr);
    }

    /* --------------------------------------------------------------------------------------------
     * Change the modes on the connected server.
    */
    Int32 CmdUserMode(CSStr mode)
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_user_mode(m_Session, mode);
    }

    /* --------------------------------------------------------------------------------------------
     * Kick the specified user from the specified channel on the connected server.
    */
    Int32 CmdKick(CSStr nick, CSStr channel)
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_kick(m_Session, nick, channel, nullptr);
    }

    /* --------------------------------------------------------------------------------------------
     * Kick the specified user from the specified channel on the connected server.
    */
    Int32 CmdKick(CSStr nick, CSStr channel, CSStr reason)
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_kick(m_Session, nick, channel, reason);
    }

    /* --------------------------------------------------------------------------------------------
     * Send a message to a specific channel or privately to another nick.
    */
    Int32 CmdMsg(CSStr nch, CSStr text)
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_msg(m_Session, nch, text);
    }

    /* --------------------------------------------------------------------------------------------
     * Send a /me message (CTCP ACTION) to a specific channel or privately to another nick.
    */
    Int32 CmdMe(CSStr nch, CSStr text)
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_me(m_Session, nch, text);
    }

    /* --------------------------------------------------------------------------------------------
     * Send a notice to a specific channel or privately to another nick.
    */
    Int32 CmdNotice(CSStr nch, CSStr text)
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_notice(m_Session, nch, text);
    }

    /* --------------------------------------------------------------------------------------------
     * Send a message to a specific channel or privately to another nick.
    */
    Int32 CmdColoredMsg(CSStr nch, CSStr text)
    {
        // Validate the connection status
        ValidateConnection();
        // Attempt to scan the specified message for color formatting
        char * cmsg = irc_color_convert_to_mirc(text, IrcAllocMem);
        // Validate the message
        if (!cmsg)
        {
            STHROWF("Failed to convert the message colors");
        }
        // Send the resulted message and grab the result code
        const int ret = irc_cmd_msg(m_Session, nch, cmsg);
        // Free the memory used to convert the message
        IrcFreeMem(cmsg);
        // Return the resulted code
        return ret;
    }

    /* --------------------------------------------------------------------------------------------
     * Send a /me message (CTCP ACTION) to a specific channel or privately to another nick.
    */
    Int32 CmdColoredMe(CSStr nch, CSStr text)
    {
        // Validate the connection status
        ValidateConnection();
        // Attempt to scan the specified message for color formatting
        char * cmsg = irc_color_convert_to_mirc(text, IrcAllocMem);
        // Validate the message
        if (!cmsg)
        {
            STHROWF("Failed to convert the message colors");
        }
        // Send the resulted message and grab the result code
        const int ret = irc_cmd_me(m_Session, nch, cmsg);
        // Free the memory used to convert the message
        IrcFreeMem(cmsg);
        // Return the resulted code
        return ret;
    }

    /* --------------------------------------------------------------------------------------------
     * Send a notice to a specific channel or privately to another nick.
    */
    Int32 CmdColoredNotice(CSStr nch, CSStr text)
    {
        // Validate the connection status
        ValidateConnection();
        // Attempt to scan the specified message for color formatting
        char * cmsg = irc_color_convert_to_mirc(text, IrcAllocMem);
        // Validate the message
        if (!cmsg)
        {
            STHROWF("Failed to convert the message colors");
        }
        // Send the resulted message and grab the result code
        const int ret = irc_cmd_notice(m_Session, nch, cmsg);
        // Free the memory used to convert the message
        IrcFreeMem(cmsg);
        // Return the resulted code
        return ret;
    }

    /* --------------------------------------------------------------------------------------------
     * Send a CTCP request to the specified user on the connected server.
    */
    Int32 CmdCtcpRequest(CSStr nick, CSStr request)
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_ctcp_request(m_Session, nick, request);
    }

    /* --------------------------------------------------------------------------------------------
     * Send a CTCP reply to the specified user on the connected server.
    */
    Int32 CmdCtcpReply(CSStr nick, CSStr reply)
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_ctcp_reply(m_Session, nick, reply);
    }

    /* --------------------------------------------------------------------------------------------
     * Change the currently used nick on the connected server.
    */
    Int32 CmdNick(CSStr nick);

    /* --------------------------------------------------------------------------------------------
     * Query various information about the specified user.
    */
    Int32 CmdWhois(CSStr nick)
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_whois(m_Session, nick);
    }

    /* --------------------------------------------------------------------------------------------
     * Quit from the connected server and close the connection.
    */
    Int32 CmdQuit()
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_quit(m_Session, nullptr);
    }

    /* --------------------------------------------------------------------------------------------
     * Quit from the connected server and close the connection.
    */
    Int32 CmdQuit(CSStr reason)
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_cmd_quit(m_Session, reason);
    }

    /* --------------------------------------------------------------------------------------------
     * Sends the specified raw data as-is to the connected IRC server.
    */
    Int32 SendRaw(CSStr str)
    {
        // Validate the connection status
        ValidateConnection();
        // Send the specified command and return the result
        return irc_send_raw(m_Session, str);
    }

    /* --------------------------------------------------------------------------------------------
     * Close the specified DCC connection (if available), and destroys the DCC session,
     * freeing the used resources.
    */
    Int32 DestroyDcc(Uint32 dccid)
    {
        // Validate the connection status
        ValidateConnection();
        // Perform the requested operation and return the result
        return irc_dcc_destroy(m_Session, dccid);
    }

    /* --------------------------------------------------------------------------------------------
     * Set the internal CTCP VERSION.
    */
    void SetCtcpVersion(CSStr version)
    {
        // Validate the connection status
        ValidateConnection();
        // Perform the requested operation
        irc_set_ctcp_version(m_Session, version);
    }

    /* --------------------------------------------------------------------------------------------
     * Returns the last error code associated with last operation of this IRC session.
    */
    Int32 GetErrNo()
    {
        // Validate the handle
        Validate();
        // Return the requested information
        return irc_errno(m_Session);
    }

    /* --------------------------------------------------------------------------------------------
     * Returns the last error code associated with last operation of this IRC session as a string.
    */
    CSStr GetErrStr()
    {
        // Validate the handle
        Validate();
        // Return the requested information
        return irc_strerror(irc_errno(m_Session));
    }

    /* --------------------------------------------------------------------------------------------
     * Set the specified option for the managed session to change its behavior.
    */
    void SetOption(Uint32 option)
    {
        // Validate the handle
        Validate();
        // Perform the requested operation and return the result
        return irc_option_set(m_Session, option);
    }

    /* --------------------------------------------------------------------------------------------
     * Reset the specified option for the managed session to restore its behavior.
    */
    void ResetOption(Uint32 option)
    {
        // Validate the handle
        Validate();
        // Perform the requested operation and return the result
        return irc_option_set(m_Session, option);
    }

    /* --------------------------------------------------------------------------------------------
     * Send a message to a specific channel or privately to another nick.
    */
    static SQInteger CmdMsgF(HSQUIRRELVM vm);

    /* --------------------------------------------------------------------------------------------
     * Send a /me message (CTCP ACTION) to a specific channel or privately to another nick.
    */
    static SQInteger CmdMeF(HSQUIRRELVM vm);

    /* --------------------------------------------------------------------------------------------
     * Send a notice to a specific channel or privately to another nick.
    */
    static SQInteger CmdNoticeF(HSQUIRRELVM vm);

    /* --------------------------------------------------------------------------------------------
     * Send a colored message to a specific channel or privately to another nick.
    */
    static SQInteger CmdColoredMsgF(HSQUIRRELVM vm);

    /* --------------------------------------------------------------------------------------------
     * Send a colored /me message (CTCP ACTION) to a specific channel or privately to another nick.
    */
    static SQInteger CmdColoredMeF(HSQUIRRELVM vm);

    /* --------------------------------------------------------------------------------------------
     * Send a colored notice to a specific channel or privately to another nick.
    */
    static SQInteger CmdColoredNoticeF(HSQUIRRELVM vm);

protected:

    /* --------------------------------------------------------------------------------------------
     * Forward session events to a script callback.
    */
    static void ForwardEvent(Function & listener, CCStr event,
                                CCStr origin, CCStr * params, Uint32 count);

    /* --------------------------------------------------------------------------------------------
     * Forward session events to a script callback.
    */
    static void ForwardEvent(Function & listener, Uint32 event,
                                CCStr origin, CCStr * params, Uint32 count);

    /* --------------------------------------------------------------------------------------------
     * Forward session events to a script callback.
    */
    static void ForwardEvent(Function & listener, CCStr nick,
                                CCStr addr, irc_dcc_t dccid);

    /* --------------------------------------------------------------------------------------------
     * Forward session events to a script callback.
    */
    static void ForwardEvent(Function & listener, CCStr nick,
                                CCStr addr, CCStr filename, Ulong size, irc_dcc_t dccid);

    /* --------------------------------------------------------------------------------------------
     * Forward the OnConnect event to the script callback.
    */
    static void OnConnect(irc_session_t * session, CCStr event, CCStr origin, CCStr * params, Uint32 count);

    /* --------------------------------------------------------------------------------------------
     * Forward the OnNick event to the script callback.
    */
    static void OnNick(irc_session_t * session, CCStr event, CCStr origin, CCStr * params, Uint32 count);

    /* --------------------------------------------------------------------------------------------
     * Forward the OnQuit event to the script callback.
    */
    static void OnQuit(irc_session_t * session, CCStr event, CCStr origin, CCStr * params, Uint32 count);

    /* --------------------------------------------------------------------------------------------
     * Forward the OnJoin event to the script callback.
    */
    static void OnJoin(irc_session_t * session, CCStr event, CCStr origin, CCStr * params, Uint32 count);

    /* --------------------------------------------------------------------------------------------
     * Forward the OnPart event to the script callback.
    */
    static void OnPart(irc_session_t * session, CCStr event, CCStr origin, CCStr * params, Uint32 count);

    /* --------------------------------------------------------------------------------------------
     * Forward the OnMode event to the script callback.
    */
    static void OnMode(irc_session_t * session, CCStr event, CCStr origin, CCStr * params, Uint32 count);

    /* --------------------------------------------------------------------------------------------
     * Forward the OnUmode event to the script callback.
    */
    static void OnUmode(irc_session_t * session, CCStr event, CCStr origin, CCStr * params, Uint32 count);

    /* --------------------------------------------------------------------------------------------
     * Forward the OnTopic event to the script callback.
    */
    static void OnTopic(irc_session_t * session, CCStr event, CCStr origin, CCStr * params, Uint32 count);

    /* --------------------------------------------------------------------------------------------
     * Forward the OnKick event to the script callback.
    */
    static void OnKick(irc_session_t * session, CCStr event, CCStr origin, CCStr * params, Uint32 count);

    /* --------------------------------------------------------------------------------------------
     * Forward the OnChannel event to the script callback.
    */
    static void OnChannel(irc_session_t * session, CCStr event, CCStr origin, CCStr * params, Uint32 count);

    /* --------------------------------------------------------------------------------------------
     * Forward the OnPrivMsg event to the script callback.
    */
    static void OnPrivMsg(irc_session_t * session, CCStr event, CCStr origin, CCStr * params, Uint32 count);

    /* --------------------------------------------------------------------------------------------
     * Forward the OnNotice event to the script callback.
    */
    static void OnNotice(irc_session_t * session, CCStr event, CCStr origin, CCStr * params, Uint32 count);

    /* --------------------------------------------------------------------------------------------
     * Forward the OnChannelNotice event to the script callback.
    */
    static void OnChannelNotice(irc_session_t * session, CCStr event, CCStr origin, CCStr * params, Uint32 count);

    /* --------------------------------------------------------------------------------------------
     * Forward the OnInvite event to the script callback.
    */
    static void OnInvite(irc_session_t * session, CCStr event, CCStr origin, CCStr * params, Uint32 count);

    /* --------------------------------------------------------------------------------------------
     * Forward the OnCtcpReq event to the script callback.
    */
    static void OnCtcpReq(irc_session_t * session, CCStr event, CCStr origin, CCStr * params, Uint32 count);

    /* --------------------------------------------------------------------------------------------
     * Forward the OnCtcpRep event to the script callback.
    */
    static void OnCtcpRep(irc_session_t * session, CCStr event, CCStr origin, CCStr * params, Uint32 count);

    /* --------------------------------------------------------------------------------------------
     * Forward the OnCtcpAction event to the script callback.
    */
    static void OnCtcpAction(irc_session_t * session, CCStr event, CCStr origin, CCStr * params, Uint32 count);

    /* --------------------------------------------------------------------------------------------
     * Forward the OnUnknown event to the script callback.
    */
    static void OnUnknown(irc_session_t * session, CCStr event, CCStr origin, CCStr * params, Uint32 count);

    /* --------------------------------------------------------------------------------------------
     * Forward the OnNumeric event to the script callback.
    */
    static void OnNumeric(irc_session_t * session, Uint32 event, CCStr origin, CCStr * params, Uint32 count);

    /* --------------------------------------------------------------------------------------------
     * Forward the OnDccChatReq event to the script callback.
    */
    static void OnDccChatReq(irc_session_t * session, CCStr nick, CCStr addr, irc_dcc_t dccid);

    /* --------------------------------------------------------------------------------------------
     * Forward the OnDccSendReq event to the script callback.
    */
    static void OnDccSendReq(irc_session_t * session, CCStr nick, CCStr addr, CCStr filename, Ulong size, irc_dcc_t dccid);
};

} // Namespace:: SqMod

#endif // _SQIRC_SESSION_HPP_
