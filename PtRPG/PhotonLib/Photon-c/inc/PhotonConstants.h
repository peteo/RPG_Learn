/* Exit Games Photon - C Client Lib
 * Copyright (C) 2004-2011 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#ifndef __PHOTON_CONSTANTS_H
#define __PHOTON_CONSTANTS_H

#include "Constants.h"

// please start your own photon server, if possible, as these servers are not guaranteed to be available or compatible to your client
#define URL_PHOTON_SERVER		L"udp.exitgames.com:5055"
#define URL_PHOTON_SERVER_DEV	L"dev.udp.exitgames.com:5055"

//All builtin parameters for operations.
#define P_ERR				((nByte) 0)
#define P_DBG				((nByte) 1)
#define P_GAMEID			((nByte) 4)
#define P_ACTORNR			((nByte) 9)
#define P_TARGET_ACTORNR	((nByte)10)
#define P_ACTORS			((nByte)11)
#define P_PROPERTIES		((nByte)12)
#define P_BROADCAST			((nByte)13)
#define P_ACTOR_PROPERTIES	((nByte)14)
#define P_GAME_PROPERTIES	((nByte)15)
#define P_CLIENT_KEY		((nByte)16)
#define P_SERVER_KEY		((nByte)17)
#define P_EVENTS			((nByte)30)
#define P_DATA				((nByte)42)
#define P_CODE				((nByte)60)

typedef enum
{
	DEBUG_LEVEL_OFF = 0,
	DEBUG_LEVEL_ERRORS = 1,
	DEBUG_LEVEL_WARNINGS = 2,
	DEBUG_LEVEL_INFO = 3,
	DEBUG_LEVEL_ALL = 4
} PhotonPeer_DebugLevel;

// operation codes
#define OPC_RT_JOIN							 90
#define OPC_RT_LEAVE						 91
#define OPC_RT_RAISE_EV						 92
#define OPC_RT_SETPROPERTIES				 93
#define OPC_RT_GETPROPERTIES				 94
#define OPC_RT_EXCHANGEKEYSFORENCRYPTION	 95

// event codes
#define EV_RT_JOIN					90
#define EV_RT_LEAVE					91
#define EV_RT_SETPROPERTIES			92

// event keys
#define EV_RT_KEY_ACTORNR			 9
#define EV_RT_KEY_TARGET_ACTORNR	10
#define EV_RT_KEY_ACTORLIST			11
#define EV_RT_KEY_PROPERTIES		12
#define EV_RT_KEY_ACTORPROPERTIES	14
#define EV_RT_KEY_GAMEPROPERTIES	15
#define EV_RT_KEY_CODE				60
#define EV_RT_KEY_DATA				42

// status codes
#define SC_CONNECT								1024 // the PhotonPeer is connected.
#define SC_DISCONNECT							1025 // the PhotonPeer just disconnected.
#define SC_EXCEPTION							1026 // the PhotonPeer encountered an exception and will disconnect, too.
#define SC_EXCEPTION_CONNECT					1023 // the PhotonPeer encountered an exception while opening the incoming connection to the server. The server could be down / not running.
#define SC_QUEUE_OUTGOING_RELIABLE_WARNING		1027 // PhotonPeer outgoing queue is filling up. send more often.
#define SC_QUEUE_OUTGOING_UNRELIABLE_WARNING	1029 // PhotonPeer outgoing queue is filling up. send more often.
#define SC_SEND_ERROR							1030 // Sending command failed. Either not connected, or the requested channel is bigger than the number of initialized channels.
#define SC_QUEUE_OUTGOING_ACKS_WARNING			1031 // PhotonPeer outgoing queue is filling up. send more often.
#define SC_QUEUE_INCOMING_WARNING				1033 // PhotonPeer incoming queue is filling up. Dispatch more often.
#define SC_QUEUE_SENT_WARNING					1037 // PhotonPeer incoming queue is filling up. Dispatch more often.
#define SC_INTERNAL_RECEIVE_EXCEPTION			1039 // Exception, if a server cannot be connected. Most likely, the server is not responding. Ask user to try again later.
#define SC_TIMEOUT_DISCONNECT					1040 // Disconnection due to a timeout (client did no longer receive ACKs from server).
#define SC_DISCONNECT_BY_SERVER					1041 // Disconnect by server due to timeout (received a disconnect command, cause server misses ACKs of client).
#define SC_DISCONNECT_BY_SERVER_USER_LIMIT		1042 // Disconnect by server due to concurrent user limit reached (received a disconnect command).
#define SC_DISCONNECT_BY_SERVER_LOGIC			1043 // Disconnect by server due to server's logic (received a disconnect command).

// Photon library error codes
// can be returned as operationcode in callback, if the returncode indicates an error
typedef enum
{
    UL_SUCCESS			=     0, // No error
    UL_EFAILED			=     1, // General failure
    UL_ENOMEMORY		=     2, // Out of memory
    UL_EBADCLASS		=    10, // NULL class object
    UL_EBADPARM			=    14, // Invalid parameter
    UL_EITEMBUSY		=    32, // Context (system, interface, etc.) is busy

    UL_NET_SUCCESS		=     0, // No network error, successful operation  
    UL_NET_ERROR		=    -1, // Unsuccessful operation
    UL_NET_ENETNONET	= 0x216, // Network subsystem unavailable
    UL_NET_MSGSIZE		= 0x21B // Message too long. A message sent on a datagram socket was larger than the internal message buffer or some other network limit, or the buffer used to receive a datagram was smaller than the datagram itself.                                      
} PhotonLIB_ErrorCodes;

// More Photon library error codes
// can be returned as return-value of an API-function
#define  SUCCESS			 0 // No error
#define  EFAILED			 1 // General failure
#define  ENOMEMORY			 2 // Out of memory
#define  ECLASSNOTSUPPORT	 3 // Class not supported
#define  EBADCLASS			10 // NULL class object
#define  EBADPARM			14 // Invalid parameter
#define  EITEMBUSY			32 // Context (system, interface, etc.) is busy

#define EG_PORT    5055



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// INTERNAL CONSTANTS
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define INIT_BYTES_LENGTH 13+32
#define EG_OPT_MTU_SIZE 1200

// Lite - Flags for "types of properties", being used as filter in OpGetProperties.
#define PROP_NONE 0x00
#define PROP_GAME 0x01                 
#define PROP_ACTOR 0x02
#define PROP_GAME_AND_ACTOR PROP_GAME|PROP_ACTOR

#define WARNING_THRESHOLD_QUEUE_OUTGOING_RELIABLE_DEFAULT	75
#define WARNING_THRESHOLD_QUEUE_OUTGOING_UNRELIABLE_DEFAULT	75
#define WARNING_THRESHOLD_QUEUE_OUTGOING_ACKS_DEFAULT		75
#define WARNING_THRESHOLD_QUEUE_INCOMING_DEFAULT			75
#define WARNING_THRESHOLD_QUEUE_SENT_DEFAULT				75

// To print out the callbacks, requests and other server interaction use the debugger.
//#define EG_DEBUGGER 
//#define EG_DEBUGGER_FILE

// Peer state
typedef enum
{
    PS_DISCONNECTED = 0,
    PS_CONNECTING = 1,
    PS_ACKNOWLEDGING_CONNECT = 2,
    PS_CONNECTED = 3,
    PS_DISCONNECTING = 4,
    PS_ACKNOWLEDGING_DISCONNECT = 5,
    PS_ZOMBIE = 6
}    PeerState;


// Constants from PhotonPeer

#define SENTCOUNTALLOWANCE			    5	// number of re-send retries before a peer is considered lost/disconnected
#define SENTTIMEALLOWANCE			10000	// max time interval in ms for re-send retries before a peer is considered lost/disconnected
#define TIMEPINGINTERVAL			 2000	// ms without reliable command, before ping will be sent
#define CHANNEL_COMMAND_BUFFER_SIZE	  100	// maximum number of PhotonCommands per channel
#define CHANNEL_COUNT_DEFAULT		    2	// default number of channels per peer
#define WINDOW_SIZE					(4*32)
#define DEBUG_IN_COMMANDS			false
#define DEBUG_IN_QUEUE_COMMANDS		false
#define DEBUG_OUT_COMMANDS			false
#define DEBUG_ACK_COMMANDS			false
#define DEBUG_NEW_IN_COMMANDS		false
#define DEBUG_DISPATCH_COMMANDS		false
#define DEBUG_RING_COUNT			false


// Constants from PhotonConnect

#define MSGT_INIT     0 // not used at the moment
#define MSGT_INIT_RES 1
#define MSGT_OP       2 // the return-values for an operation is incoming
#define MSGT_OP_RES   3
#define MSGT_EV       4 // an event is coming in


// Constants from PhotonCommand

#define FLAG_RELIABLE				1
#define FLAG_UNSEQUENCED			2
#define FV_UNRELIABLE				0
#define FV_RELIABLE					1
#define FV_UNRELIABLE_UNSEQUENCED	2 

#define CT_NONE				 0
#define CT_ACK				 1
#define CT_CONNECT			 2
#define CT_VERIFYCONNECT	 3
#define CT_DISCONNECT		 4
#define CT_PING				 5
#define CT_SENDRELIABLE		 6
#define CT_SENDUNRELIABLE	 7
#define CT_SENDFRAGMENT		 8
// bandwidth limit			 9
// throttle config			10
// unsequenced				11
#define CT_EG_SERVERTIME	12 //immediately acknowledged (ack sent without any other commands)

// Commands buffer max length.
#define COMMANDS_BUF_LEN 20

#endif // __PHOTON_CONSTANTS_H__