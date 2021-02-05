#include <string.h>
#include "RingBuffer.h"

CRingBuffer::CRingBuffer()
{
	memset(m_cBuffer, 0, RINGBUF_SIZE);

	m_iFrontPos = 0;
	m_iRearPos = 0;

	m_dwCurrDataSize = 0;
}

CRingBuffer::~CRingBuffer()
{

}

bool CRingBuffer::isEmpty()
{
	return (m_dwCurrDataSize == 0);
}

bool CRingBuffer::isFull()
{
	return (m_dwCurrDataSize == RINGBUF_SIZE - 1);
}

bool CRingBuffer::Push(char* _cpData, int _iDataSize)
{
	// 남아있는 공간이 푸쉬할 데이터사이즈보다 작을때
	if (RINGBUF_SIZE - m_dwCurrDataSize < _iDataSize)
	{
		return false;
	}

	// 푸쉬할 지점으로 포지션 이동
	m_iRearPos = (m_iRearPos + 1) % RINGBUF_SIZE;

	char* p = m_cBuffer + m_iRearPos;
	
	if (_iDataSize > RINGBUF_SIZE - m_iRearPos)
	{
		// rear~ end 까지 복사
		int tempSize = RINGBUF_SIZE - m_iRearPos;
		memcpy(p, _cpData, tempSize);

		// start~ 남은 데이터 복사
		p = m_cBuffer;
		memcpy(p, _cpData + tempSize, _iDataSize - tempSize);
	}
	else
	{
		memcpy(p, _cpData, _iDataSize);
	}

	m_iRearPos = ((m_iRearPos - 1 + _iDataSize) % RINGBUF_SIZE);

	m_dwCurrDataSize += _iDataSize;

	return true;
}

bool CRingBuffer::Pop(char* _cpData, int _iDataSize)
{
	// pop 하려는 데이터사이즈가 들어있는 데이터사이즈보다 클때
	if (_iDataSize > m_dwCurrDataSize)
	{
		return false;
	}

	m_iFrontPos = (m_iFrontPos + 1) % RINGBUF_SIZE;

	char* p = m_cBuffer + m_iFrontPos;

	if (_iDataSize > RINGBUF_SIZE - m_iFrontPos)
	{
		int tempSize = RINGBUF_SIZE - m_iFrontPos;
		memcpy(_cpData, p, tempSize);

		p = m_cBuffer;
		memcpy(_cpData + tempSize, p, _iDataSize - tempSize);
	}
	else
	{
		memcpy(_cpData, p, _iDataSize);
	}
	
	m_iFrontPos = ((m_iFrontPos - 1 + _iDataSize) % RINGBUF_SIZE);

	return true;
}