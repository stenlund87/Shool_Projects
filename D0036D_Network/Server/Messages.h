#define MAXNAMELEN 32

/* Structs & enumerators for sending/recieving messages */
enum ObjectDesc
{
Human,
NonHuman,
Vehicle,
StaticObject
};

enum ObjectForm
{
Cube,
Sphere,
Pyramid,
Con
};

/* Struct that contains x,y pos for the player */
struct Coordinate
{
int x;
int y;
};

/* What type of message we send to server and what type of message we get from server */
enum MsgType
{
Join, // Client joining game at server
Leave, // Client leaving game
Change, // Information to clients
Event, // Information from clients to server
TextMessage // Send text messages to one or all
};

/* MessageHead */
struct MsgHead
{
unsigned int length; // Total length for whole message
unsigned int seq_no; // Sequence number
unsigned int id; // Client ID or 0;
MsgType type; // Type of message
};

/* Predefined message for join */
struct JoinMsg
{
MsgHead head;
ObjectDesc desc;
ObjectForm form;
char name[MAXNAMELEN];
};

/* Use for leaving the server, set LeaveMsg.head->type to Leave */
struct LeaveMsg
{
MsgHead head;
};

/* Events that can happen in the game */
enum EventType
{
Move
};

/* Message to/from server with a event */
struct EventMsg
{
MsgHead head;
EventType type;
};

/* MoveEvent  */
struct MoveEvent
{
EventMsg event;
Coordinate pos;
Coordinate dir;
};

struct TextMessageMsg
{
MsgHead head;
char text[1];
};

enum ChangeType
{
NewPlayer,
PlayerLeave,
NewPlayerPosition
};

// Included first in all Change messages struct ChangeMsg
struct ChangeMsg
{
MsgHead head;
ChangeType type;
};

struct NewPlayerMsg
{
ChangeMsg msg; //Change message header with new client id
ObjectDesc desc;
ObjectForm form;
char name[MAXNAMELEN]; // nullterminated!, or empty
};
struct PlayerLeaveMsg
{
ChangeMsg msg; //Change message header with new client id
};
struct NewPlayerPositionMsg
{
ChangeMsg msg; //Change message header
Coordinate pos; //New object position
Coordinate dir; //New object direction
};
