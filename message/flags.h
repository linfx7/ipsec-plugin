#ifndef __H_FLAGS__
#define __H_FLAGS__

// message type
#define NOTIFICATION 0x80
#define CONFIGURATION 0x40
#define QUERY 0x20


// notification type
#define STATUS 0x80
#define EVENT 0x40
// event notification type
#define EVENT_PACKET 0x80
#define EVENT_OVERLOAD 0x40
#define EVENT_CRASH 0x20
// status notification type


// configuration element type
#define ELEMENT_RULE 0x80
#define ELEMENT_CONFIGURATION 0x40
#define ELEMENT_SECRET 0x20
// rule action
#define RULE_DISCARD 0x80
#define RULE_BYPASS 0x40
#define RULE_PROTECT 0x20


// response message
#define ACK 0x80
#define SUCCESS 0x40
#define ERROR 0x20

#endif