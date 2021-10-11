# Takeoff
## QGC send TAKEOFF command first, then transmit ARM command.
>**1st. COMMAND_LONG(msgid) : MAV_CMD_NAV_TAKEOFF(command)**
**2nd. COMMAND_LONG(msgid) : MAV_CMD_COMPONENT_ARM_DISARM(command)**

INFO  [mavlink] *********************************************
INFO  [mavlink] Message Info for handle_message_command_long
INFO  [mavlink] magic : 253
INFO  [mavlink] len : 32
INFO  [mavlink] incompat_flags : 0
INFO  [mavlink] compat_flags : 0
INFO  [mavlink] seq : 164
INFO  [mavlink] source_system(sysid) : 255 -> **mavlink system id from MAV_SYS_ID. Generally GCS == 255**
INFO  [mavlink] source_compoment(compid) : 190 -> **mavlink component id from MAV_COMPONENT. 190 = MAV_COMP_ID_MISSIONPLANNER**
INFO  [mavlink] msgid : 76 -> **COMMAND_LONG #76**
INFO  [mavlink] =========payloads=========
INFO  [mavlink] target_system : 1 **mavlink system id from MAV_SYS_ID**
INFO  [mavlink] target_component : 1 **mavlink component id from MAV_COMPONENT. See [MAV_COMPONENT](https://mavlink.io/en/messages/common.html#MAV_COMPONENT)**
INFO  [mavlink] command : 22 -> **MAV_CMD_NAV_TAKEOFF #22 at MAV_CMD**
INFO  [mavlink] confirmation : 0
INFO  [mavlink] param1 : -1.000000 -> **deg**
INFO  [mavlink] param2 : 0.000000 -> **empty**
INFO  [mavlink] param3 : 0.000000 -> **empty**
INFO  [mavlink] param4 : nan -> **yaw angle. If nan, system follows yaw setting**
INFO  [mavlink] param5 : nan -> **takeoff latitude command. If nan, take-off at drone's current latitude**
INFO  [mavlink] param6 : nan -> **takeoff longitude command. If nan, take-off at drone's current longitude**
INFO  [mavlink] param7 : 23.644173 -> **takeoff altitude. param7 = MSL at current location +AGL command**
INFO  [mavlink] *********************************************
INFO  [mavlink] *********************************************
INFO  [mavlink] Message Info for handle_message_command_long
INFO  [mavlink] magic : 253
INFO  [mavlink] len : 32
INFO  [mavlink] incompat_flags : 0
INFO  [mavlink] compat_flags : 0
INFO  [mavlink] seq : 165
INFO  [mavlink] source_system(sysid) : 255 -> **mavlink system id from MAV_SYS_ID. Generally GCS == 255**
INFO  [mavlink] source_compoment(compid) : 190 **mavlink component id from MAV_COMPONENT. See [MAV_COMPONENT](https://mavlink.io/en/messages/common.html#MAV_COMPONENT)**
INFO  [mavlink] msgid : 76 -> **COMMAND_LONG #76**
INFO  [mavlink] =========payloads=========
INFO  [mavlink] target_system : 1 -> **mavlink system id from MAV_SYS_ID**
INFO  [mavlink] target_component : 1 -> **mavlink component id from MAV_COMPONENT. See [MAV_COMPONENT](https://mavlink.io/en/messages/common.html#MAV_COMPONENT)**
INFO  [mavlink] command : 400 -> **MAV_CMD_COMPONENT_ARM_DISARM #400 at MAV_CMD**
INFO  [mavlink] confirmation : 0
INFO  [mavlink] param1 : 1.000000 -> **Disarm : 0, Arm : 1**
INFO  [mavlink] param2 : 0.000000 -> **Force arm/disarm : 0, Force arm/disarm(even in flight) : 21196**
INFO  [mavlink] param3 : 0.000000 -> **empty**
INFO  [mavlink] param4 : 0.000000 -> **empty**
INFO  [mavlink] param5 : 0.000000 -> **empty**
INFO  [mavlink] param6 : 0.000000 -> **empty**
INFO  [mavlink] param7 : 0.000000 -> **empty**
INFO  [mavlink] *********************************************

##Go to location 
###Right click and select "go to location" on the map at QGroundControl
> **COMMAND_INT(msgid) : MAV_CMD_DO_REPOSITION(command)**


INFO  [mavlink] *********************************************
INFO  [mavlink] Message Info for handle_message_command_int
INFO  [mavlink] magic : 253
INFO  [mavlink] len : 32
INFO  [mavlink] incompat_flags : 0
INFO  [mavlink] compat_flags : 0
INFO  [mavlink] seq : 153
INFO  [mavlink] source_system(sysid) : 255
INFO  [mavlink] source_compoment(compid) : 190
INFO  [mavlink] msgid : 75 -> **COMMAND_INT #75**
INFO  [mavlink] =========payloads=========
INFO  [mavlink] target_system : 1
INFO  [mavlink] target_component : 1
INFO  [mavlink] frame : 0 -> **Coordinate system defined in MAV_FRAME. See [MAV_FRAME](https://mavlink.io/en/messages/common.html#MAV_FRAME)**
INFO  [mavlink] command : 192 -> **MAV_CMD_DO_REPOSITION #192 in MAV_CMD. See [MAV_CMD](https://mavlink.io/en/messages/common.html#MAV_CMD)**
INFO  [mavlink] current : 0 -> **Reserved. Set 0**
INFO  [mavlink] autocontinue : 0 -> **Reserved. Set 0**
INFO  [mavlink] param1 : -1.000000 -> **Ground speed. -1 for default ground speed(MPC_XY_CRUISE in PX4). see MAV_CMD_DO_REPOSITION #192 at [MAV_CMD](https://mavlink.io/en/messages/common.html#MAV_CMD)**
INFO  [mavlink] param2 : 1.000000 -> **Move to command simultaneously. Set 1 as default. See MAV_CMD_DO_REPOSITION #192 at [MAV_CMD](https://mavlink.io/en/messages/common.html#MAV_CMD)**
INFO  [mavlink] param3 : 0.000000 -> **Reserved**
INFO  [mavlink] param4 : nan -> **Yaw angle in deg. Nan to system default yaw setting.**
INFO  [mavlink] x : 375687980 -> **command latitude**
INFO  [mavlink] y : 1270084304 -> **command longitude**
INFO  [mavlink] z : 23 -> **command altitude**
INFO  [mavlink] source_compoment : 190
INFO  [mavlink] msgid : 75
INFO  [mavlink] *********************************************

##Land

>Uses three mode sets
>>base_mode  
>>>Related to VEHICLE_MODE_FLAG_CUSTOM_MODE_ENABLED
>>>set 1 as default
>>
>>custom_main_mode
>>>Related to 
>>>>PX4_CUSTOM_MAIN_MODE_MANUAL = 1
>>>>PX4_CUSTOM_MAIN_MODE_ALTCTL = 2
>>>>PX4_CUSTOM_MAIN_MODE_POSCTL = 3
>>>>PX4_CUSTOM_MAIN_MODE_AUTO = 4
>>>>PX4_CUSTOM_MAIN_MODE_ACRO = 5
>>>>PX4_CUSTOM_MAIN_MODE_OFFBOARD = 6
>>>>PX4_CUSTOM_MAIN_MODE_STABILIZED = 7
>>>>PX4_CUSTOM_MAIN_MODE_RATTITUDE = 8
>>>>PX4_CUSTOM_MAIN_MODE_SIMPLE = 9
>>>
>>custom_sub_mode
>>>Related to
>>>>PX4_CUSTOM_SUB_MODE_AUTO_READY = 1
>>>>PX4_CUSTOM_SUB_MODE_AUTO_TAKEOFF = 2
>>>>PX4_CUSTOM_SUB_MODE_AUTO_LOITER = 3
>>>>PX4_CUSTOM_SUB_MODE_AUTO_MISSION = 4
>>>>PX4_CUSTOM_SUB_MODE_AUTO_RTL = 5
>>>>PX4_CUSTOM_SUB_MODE_AUTO_LAND = 6
>>>>PX4_CUSTOM_SUB_MODE_AUTO_RTGS = 7
>>>>PX4_CUSTOM_SUB_MODE_AUTO_FOLLOW_TARGET = 8
>>>>PX4_CUSTOM_SUB_MODE_AUTO_PRECLAND = 8