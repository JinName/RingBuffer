#pragma once

#define MAX_PACKET_SIZE 2
#define THREAD_COUNT 2
#define	RINGBUF_SIZE 16

class CircularBuffer
{
public:
	CircularBuffer();
	~CircularBuffer();

	// ���� ���ۿ� ��� ������ ���� ��ȯ
	size_t GetAvailableBufferSize();

	// ���� ���ۿ� ���� ������ ������ �����ͷ� ��ȯ
	char* GetWritablePointer();

	// ���ۿ� ����ִ� �� ������ ����
	size_t GetWritedDataSize();

	// �Ű������� �Էµ� ���̸�ŭ �����͸� �̵�
	void CommitDataSize(size_t _len);

	// �����͸� �������� �ʰ� ���̸�ŭ�� ��ȯ�Ͽ� Ȯ����
	bool Peek(char* _outBuffer, size_t _len);

	// �����͸� ���� + ����
	bool Pop(char* _outBuffer, size_t _len);

private:
	char m_cBuffer[RINGBUF_SIZE];
	char* m_cpBufferEnd;

	// ���۸� �����͸� �ڷ� �и鼭 ����ϴٰ�
	// ���� ���� ������ MAX_PACKET_SIZE ���� ������,
	// SecondPointer �� ������ ù �������� �ٽ� �����͸� �޴´�.
	char* m_cpPrimaryPointer;
	size_t m_dwPrimarySize;

	char* m_cpSecondPointer;
	size_t m_dwSecondSize;

	// ù��° �ι�° ������ ����� ���
	size_t getAvailablePrimaryBufferSize();
	size_t getAvailableSecondBufferSize();

	// �ι�° �����͸� ���� ù ������ �Ҵ�
	void allocateSecondPointer();
};