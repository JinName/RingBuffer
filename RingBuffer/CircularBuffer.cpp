#include <string.h>
#include "CircularBuffer.h"

CircularBuffer::CircularBuffer()
{
	memset(m_cBuffer, 0, RINGBUF_SIZE);

	m_cpBufferEnd = m_cBuffer + RINGBUF_SIZE;

	m_cpPrimaryPointer = m_cBuffer;
	m_dwPrimarySize = 0;

	m_cpSecondPointer = nullptr;
	m_dwSecondSize = 0;
}

CircularBuffer::~CircularBuffer()
{
}

/// private functions ////////////////////////////////////////////////////////
void CircularBuffer::allocateSecondPointer()
{
	m_cpSecondPointer = m_cBuffer;
}

size_t CircularBuffer::getAvailablePrimaryBufferSize()
{
	return (m_cpBufferEnd - (m_cpPrimaryPointer + m_dwPrimarySize));
}

size_t CircularBuffer::getAvailableSecondBufferSize()
{
	if (m_cpSecondPointer == nullptr)
	{
		return 0;
	}
	else
	{
		return (m_cpPrimaryPointer - (m_cpSecondPointer + m_dwSecondSize));
	}
}

size_t CircularBuffer::getBeforePrimaryBufferSize()
{
	return m_cpPrimaryPointer - m_cBuffer;
}
//////////////////////////////////////////////////////////////////////////////////

size_t CircularBuffer::GetAvailableBufferSize()
{
	if (m_cpSecondPointer != nullptr)
	{
		return getAvailableSecondBufferSize();
	}
	else
	{
		if (getBeforePrimaryBufferSize() > getAvailablePrimaryBufferSize())
		{
			allocateSecondPointer();
			return getAvailableSecondBufferSize();
		}
		else
		{
			return getAvailablePrimaryBufferSize();
		}
	}
}

char* CircularBuffer::GetWritablePointer()
{
	if (m_cpSecondPointer != nullptr)
	{
		return m_cpSecondPointer + m_dwSecondSize;
	}
	else
	{
		return m_cpPrimaryPointer + m_dwPrimarySize;
	}
}

void CircularBuffer::CommitDataSize(size_t _len)
{
	if (m_cpSecondPointer != nullptr)
	{
		m_dwSecondSize += _len;
	}
	else
	{
		m_dwPrimarySize += _len;
	}
}

void CircularBuffer::RemoveData(size_t _len)
{
	size_t cnt = _len;

	// Primary Buffer 에서 삭제하는 경우
	if (m_dwPrimarySize > 0)
	{
		size_t removeSize = (cnt > m_dwPrimarySize) ? m_dwPrimarySize : cnt;
		m_dwPrimarySize -= removeSize;
		m_cpPrimaryPointer += removeSize;
		cnt -= removeSize;
	}

	// Primary Buffer 에서 삭제 후 Second Buffer 에서 마저 삭제해야 하는 경우
	if (cnt > 0 && m_dwSecondSize > 0)
	{
		size_t removeSize = (cnt > m_dwSecondSize) ? m_dwSecondSize : cnt;
		m_dwSecondSize -= removeSize;
		m_cpSecondPointer += removeSize;
		cnt -= removeSize;
	}

	// 삭제 후 Primary Buffer 는 비어있고, Second Buffer 에 데이터가 남아있을 경우
	// Second Buffer Data -> Primary Buffer
	if (m_dwPrimarySize == 0)
	{
		if (m_dwSecondSize > 0)
		{
			if (m_cpSecondPointer != m_cBuffer)
				memmove(m_cBuffer, m_cpSecondPointer, m_dwSecondSize);

			m_cpPrimaryPointer = m_cBuffer;
			m_dwPrimarySize = m_dwSecondSize;

			m_cpSecondPointer = nullptr;
			m_dwSecondSize = 0;
		}
		else
		{
			m_cpSecondPointer = nullptr;
			m_dwSecondSize = 0;

			m_cpPrimaryPointer = m_cBuffer;
			m_dwPrimarySize = 0;
		}
	}
}