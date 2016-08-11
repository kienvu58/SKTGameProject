#pragma once

#include <string>

enum MessageType
{
	MSG_MINION_INSIDE_VISION_RANGE,
	MSG_CLEAN_UP,
	MSG_MINION_TAKE_DAMAGE,
	MSG_PLAYER_TAKE_DAMAGE,
	MSG_EXPLODE
};

inline std::string MessageToString(MessageType message)
{
	switch (message)
	{
	case MSG_MINION_INSIDE_VISION_RANGE:
		return "MSG_MINION_INSIDE_VISION_RANGE";
	case MSG_CLEAN_UP: 
		return "MSG_CLEAN_UP";
	case MSG_MINION_TAKE_DAMAGE: 
		return "MSG_MINION_TAKE_DAMAGE";
	case MSG_PLAYER_TAKE_DAMAGE:
		return "MSG_PLAYER_TAKE_DAMAGE";
	case MSG_EXPLODE:
		return "MSG_EXPLODE";
	default:
		return "Not recognized";
	}
}
