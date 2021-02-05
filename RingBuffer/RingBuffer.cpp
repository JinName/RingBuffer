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
	// �����ִ� ������ Ǫ���� �����ͻ������ ������
	if (RINGBUF_SIZE - m_dwCurrDataSize < _iDataSize)
	{
		return false;
	}

	// Ǫ���� �������� ������ �̵�
	m_iRearPos = (m_iRearPos + 1) % RINGBUF_SIZE;

	char* p = m_cBuffer + m_iRearPos;
	
	if (_iDataSize > RINGBUF_SIZE - m_iRearPos)
	{
		// rear~ end ���� ����
		int tempSize = RINGBUF_SIZE - m_iRearPos;
		memcpy(p, _cpData, tempSize);

		// start~ ���� ������ ����
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
	// pop �Ϸ��� �����ͻ���� ����ִ� �����ͻ������ Ŭ��
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