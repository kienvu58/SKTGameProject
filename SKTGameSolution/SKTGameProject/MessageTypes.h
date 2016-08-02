#pragma once

#include <string>

enum MessageType
{
	MSG_SPAWN_KI_BLAST,
	MSG_CELLJR_INSIDE_ATTACK_RANGE,
	MSG_SPAWN_KAMEHAMEHA,
	MSG_MINION_OUT_OF_WALL,
	MSG_SPAWN_TRUE_KAMEHAMEHA
};

inline std::string MessageToString(int message)
{
	switch (message)
	{
	default:
		return "Not recognized";
	}
}