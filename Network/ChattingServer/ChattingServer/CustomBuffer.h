#pragma once
#include "Util.h"

class CustomBuffer
{
public:

	CustomBuffer(size_t capacity) : m_StartPointer(nullptr), m_EndPointer(nullptr), m_Capacity(capacity)
	{
		m_Buffer = new char[capacity];
	}

	~CustomBuffer()
	{
		SafeDelete<char*>(m_Buffer);
	}

	bool	Peek(OUT char* destbuf, size_t bytes) const;
	bool	Read(OUT char* destbuf, size_t bytes);
	bool	Write(const char* data, size_t bytes);
	void	Remove(size_t len);
	size_t	GetAvailableSize();

private:
	char*	m_Buffer;
	char*	m_StartPointer;
	char*	m_EndPointer;
	size_t	m_Capacity;
};
