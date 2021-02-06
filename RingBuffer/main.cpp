#include <iostream>

#include "RingBuffer.h"

int main()
{
	CRingBuffer buf;

	char temp1[] = { "abcd" };
	char temp2[] = { "efgh" };
	char temp3[] = { "ijklmn" };

	char dummy[16] = "";

	buf.Push(temp1, 4);

	strcpy_s(temp1, "qwer");

	buf.Pop(dummy, 3);
	buf.Pop(dummy, 1);
	std::cout << dummy << std::endl;

	// �׽�Ʈ ���
	// push �Ŀ� temp1 �� ������ �ٲ㵵 memcpy�� ������ �ٲ�������.

	char* p = new char[4];
	memcpy(p, temp2, 4);

	std::cout << &p << std::endl;
	std::cout << &temp2  << std::endl;

	//buf.Push(temp2, 4);
	//buf.Pop(dummy, 2);
	//std::cout << dummy << std::endl;

	//buf.Push(temp3, 6);
	//buf.Pop(dummy, 9);
	//std::cout << dummy << std::endl;

	return 0;
}