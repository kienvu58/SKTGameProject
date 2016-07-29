#pragma once

#include <string>

enum MessageType
{
};

inline std::string MessageToString(int message)
{
	switch (message)
	{
	default:
		return "Not recognized";
	}
}