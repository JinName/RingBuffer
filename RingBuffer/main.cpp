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
	buf.Pop(dummy, 3);
	std::cout << dummy << std::endl;

	buf.Push(temp2, 4);
	buf.Pop(dummy, 2);
	std::cout << dummy << std::endl;

	buf.Push(temp3, 6);
	buf.Pop(dummy, 9);
	std::cout << dummy << std::endl;

	return 0;
}