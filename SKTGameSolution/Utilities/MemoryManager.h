#pragma once

const int MAX_ALLOC = 10000;

struct AllocBuffers
{
	void * pAddress;
	unsigned int length;
	char * fileName;
	unsigned long line;
};


class MemoryManager
{
private:
	MemoryManager();
	~MemoryManager();

	static MemoryManager ms_Instance;
	AllocBuffers m_dataBuffers[MAX_ALLOC];
	unsigned int m_noBuffers;

public:
	static MemoryManager * GetInstance() {return &ms_Instance;}
	void * Alloc(unsigned int noBytes, char * fileName, unsigned int line);
	void Free(void * pAddress);
	void Dump() const;
	void SanityCheck(bool bShowStats = false) const;
	static void Error(char * szMessage);
};




