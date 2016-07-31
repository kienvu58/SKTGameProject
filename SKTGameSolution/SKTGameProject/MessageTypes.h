#pragma once

#include <string>

enum MessageType
{
	MSG_SPAWN_KI_BLAST,
	MSG_MINION_OUT_OF_WALL
};

inline std::string MessageToString(int message)
{
	switch (message)
	{
	default:
		return "Not recognized";
	}
}