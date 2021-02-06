#pragma once

#define MAX_PACKET_SIZE 4
#define THREAD_COUNT 4

#define	RINGBUF_SIZE 16

class CircularBuffer
{
public:
	CircularBuffer();
	~CircularBuffer();

	// �ι�° �����͸� ���� ù ������ �Ҵ�
	void allocateSecondPointer();

	// ���� ���ۿ� ��� ������ ���� ��ȯ
	size_t GetAvailableBufferSize();

	// ���� ���ۿ� ���� ������ ������ �����ͷ� ��ȯ
	char* GetWritablePointer();

	// �Ű������� �Էµ� ���̸�ŭ �����͸� �̵�
	void CommitDataSize(size_t _len);

	// ����� ���� �����͸� ����
	void RemoveData(size_t _len);

private:
	char m_cBuffer[RINGBUF_SIZE];
	char* m_cpBufferEnd;

	// ���۸� �����͸� �ڷ� �и鼭 ����ϴٰ�
	// ���� ���� �̻��� �Ѿ��,
	// SecondPointer �� ������ ù �������� �ٽ� �����͸� �����Ѵ�.
	char* m_cpPrimaryPointer;
	size_t m_dwPrimarySize;

	char* m_cpSecondPointer;
	size_t m_dwSecondSize;

	// ù��° �ι�° ������ ����� ���
	size_t getAvailablePrimaryBufferSize();
	size_t getAvailableSecondBufferSize();

	// ���� / ���� �� ���� �ڷ� �и� �������� ��ġ�� ���� ���������κ��� ���
	size_t getBeforePrimaryBufferSize();
};

