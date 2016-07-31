#pragma once

#include <string>

enum MessageType
{
	MSG_SPAWN_KI_BLAST
};

inline std::string MessageToString(int message)
{
	switch (message)
	{
	default:
		return "Not recognized";
	}
}