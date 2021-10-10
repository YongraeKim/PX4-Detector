#pragma once

#define MAVPACKED( __Declaration__ ) __Declaration__ __attribute__((packed))

#define MAVLINK_MSG_ID_PING 4
#define MAVLINK_MSG_ID_HEARTBEAT 0


#define MAVLINK_MAX_PAYLOAD_LEN 255 ///< Maximum payload length
#define MAVLINK_NUM_CHECKSUM_BYTES 2
#define MAVLINK_SIGNATURE_BLOCK_LEN 13
MAVPACKED(
typedef struct __mavlink_message {
	uint16_t checksum;      ///< sent at end of packet
	uint8_t magic;          ///< protocol magic marker
	uint8_t len;            ///< Length of payload
	uint8_t incompat_flags; ///< flags that must be understood
	uint8_t compat_flags;   ///< flags that can be ignored if not understood
	uint8_t seq;            ///< Sequence of packet
	uint8_t sysid;          ///< ID of message sender system/aircraft
	uint8_t compid;         ///< ID of the message sender component
	uint32_t msgid:24;      ///< ID of message in payload
	uint64_t payload64[(MAVLINK_MAX_PAYLOAD_LEN+MAVLINK_NUM_CHECKSUM_BYTES+7)/8];
	uint8_t ck[2];          ///< incoming checksum bytes
	uint8_t signature[MAVLINK_SIGNATURE_BLOCK_LEN];
}) mavlink_message_t;

MAVPACKED(
typedef struct __mavlink_ping_t {
 uint64_t time_usec; /*< [us] Timestamp (UNIX Epoch time or time since system boot). The receiving end can infer timestamp format (since 1.1.1970 or since system boot) by checking for the magnitude the number.*/
 uint32_t seq; /*<  PING sequence*/
 uint8_t target_system; /*<  0: request ping from all receiving systems. If greater than 0: message is a ping response and number is the system id of the requesting system*/
 uint8_t target_component; /*<  0: request ping from all receiving components. If greater than 0: message is a ping response and number is the component id of the requesting component.*/
}) mavlink_ping_t;

MAVPACKED(
typedef struct __mavlink_heartbeat_t {
 uint32_t custom_mode; /*<  A bitfield for use for autopilot-specific flags*/
 uint8_t type; /*<  Vehicle or component type. For a flight controller component the vehicle type (quadrotor, helicopter, etc.). For other components the component type (e.g. camera, gimbal, etc.). This should be used in preference to component id for identifying the component type.*/
 uint8_t autopilot; /*<  Autopilot type / class. Use MAV_AUTOPILOT_INVALID for components that are not flight controllers.*/
 uint8_t base_mode; /*<  System mode bitmap.*/
 uint8_t system_status; /*<  System status flag.*/
 uint8_t mavlink_version; /*<  MAVLink version, not writable by user, gets added by protocol because of magic data type: uint8_t_mavlink_version*/
}) mavlink_heartbeat_t;


//************************************************************************
//************************************************************************
//************************************************************************
//*****************************goto location. orbit***********************
#define MAVLINK_MSG_ID_COMMAND_INT 75
MAVPACKED(
typedef struct __mavlink_command_int_t {
 float param1; /*<  PARAM1, see MAV_CMD enum*/
 float param2; /*<  PARAM2, see MAV_CMD enum*/
 float param3; /*<  PARAM3, see MAV_CMD enum*/
 float param4; /*<  PARAM4, see MAV_CMD enum*/
 int32_t x; /*<  PARAM5 / local: x position in meters * 1e4, global: latitude in degrees * 10^7*/
 int32_t y; /*<  PARAM6 / local: y position in meters * 1e4, global: longitude in degrees * 10^7*/
 float z; /*<  PARAM7 / z position: global: altitude in meters (relative or absolute, depending on frame).*/
 uint16_t command; /*<  The scheduled action for the mission item.*/
 uint8_t target_system; /*<  System ID*/
 uint8_t target_component; /*<  Component ID*/
 uint8_t frame; /*<  The coordinate system of the COMMAND.*/
 uint8_t current; /*<  false:0, true:1*/
 uint8_t autocontinue; /*<  autocontinue to next wp*/
}) mavlink_command_int_t;


//************************************************************************
//************************************************************************
//************************************************************************
//*****************************Take off***********************************
#define MAVLINK_MSG_ID_COMMAND_LONG 76
MAVPACKED(
typedef struct __mavlink_command_long_t {
 float param1; /*<  Parameter 1 (for the specific command).*/
 float param2; /*<  Parameter 2 (for the specific command).*/
 float param3; /*<  Parameter 3 (for the specific command).*/
 float param4; /*<  Parameter 4 (for the specific command).*/
 float param5; /*<  Parameter 5 (for the specific command).*/
 float param6; /*<  Parameter 6 (for the specific command).*/
 float param7; /*<  Parameter 7 (for the specific command).*/
 uint16_t command; /*<  Command ID (of command to send).*/
 uint8_t target_system; /*<  System which should execute the command*/
 uint8_t target_component; /*<  Component which should execute the command, 0 for all components*/
 uint8_t confirmation; /*<  0: First transmission of this command. 1-255: Confirmation transmissions (e.g. for kill command)*/
}) mavlink_command_long_t;



//************************************************************************
//************************************************************************
//************************************************************************
//*****************************Land, RTL**********************************
#define MAVLINK_MSG_ID_SET_MODE 11

MAVPACKED(
typedef struct __mavlink_set_mode_t {
 uint32_t custom_mode; /*<  The new autopilot-specific mode. This field can be ignored by an autopilot.*/
 uint8_t target_system; /*<  The system setting the mode*/
 uint8_t base_mode; /*<  The new base mode.*/
}) mavlink_set_mode_t;