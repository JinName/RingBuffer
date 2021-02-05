#pragma once
#define MAX_PACKET_SIZE 4
#define THREAD_COUNT 4

#define	RINGBUF_SIZE 17

class CRingBuffer
{
private:
	char			m_cBuffer[RINGBUF_SIZE];		// ����

	int				m_iFrontPos;
	int				m_iRearPos;

	unsigned int	m_dwCurrDataSize;				// ����ִ� ������ ������

public:
	CRingBuffer();
	~CRingBuffer();

	bool	isEmpty();
	bool	isFull();

	bool	Push(char* _cpData, int _iDataSize);
	bool	Pop(char* _cpData, int _iDataSize);

};

