#include "stdafx.h"
#include "CustomBuffer.h"


bool CustomBuffer::Peek(OUT char* destbuf, size_t bytes) const
{
	_ASSERT(m_Buffer != nullptr);
	if(GetAvailableSize() > bytes)
	{

	}
	memcpy(destbuf, m_StartPointer, bytes);

	return true;

}

bool CustomBuffer::Read(OUT char* destbuf, size_t bytes)
{
	
	return true;
}




bool CustomBuffer::Write(const char* data, size_t bytes)
{
	
		return true;
}



void CustomBuffer::Remove(size_t len)
{

}

size_t CustomBuffer::GetAvailableSize()
{
	return (size_t)(m_EndPointer - m_Buffer);
}


