#pragma once

#include <string>

enum MessageType
{
	MSG_CELLJR_INSIDE_ATTACK_RANGE,
	MSG_CLEAN_UP,
	MSG_MINION_TAKE_DAMAGE,
	MSG_PLAYER_TAKE_DAMAGE,
	MSG_MINION_HIT_PLAYER,
	MSG_EXPLODE
};

inline std::string MessageToString(int message)
{
	switch (message)
	{
	default:
		return "Not recognized";
	}
}