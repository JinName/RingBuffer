#include <iostream>
using namespace std;
#include <queue>
#include <ctime>

#include "CircularBuffer.h"
#include "RingBuffer.h"
#include "PacketList.h"

int main()
{
	//int _fps = 60;

	//float quoRes = 1000.0f / (float)_fps;

	//float remainRes = quoRes - (int)quoRes;
	//
	//cout << (int)quoRes << endl;
	//cout << remainRes << endl;


	/////////////////////////////// TEST ///////////////////////////////////////


	//std::cout << "SHEAD : " << sizeof(SHEAD) << std::endl;
	//std::cout << "STAIL : " << sizeof(STAIL) << std::endl;
	//std::cout << "SCHAT : " << sizeof(SCHAT) << std::endl;
	//std::cout << "SGAMESTART : " << sizeof(SGAMESTART) << std::endl;
	//std::cout << "SGAMEEND : " << sizeof(SGAMEEND) << std::endl;
	//std::cout << "SCHARACTER : " << sizeof(SCHARACTER) << std::endl;
	//std::cout << "SINITCOMPLETE : " << sizeof(SINITCOMPLETE) << std::endl;
	//std::cout << "SLOGIN : " << sizeof(SLOGIN) << std::endl;
	//std::cout << "SCRASH : " << sizeof(SCRASH) << std::endl;
	//std::cout << "SPLAYERDIE : " << sizeof(SPLAYERDIE) << std::endl;
	//std::cout << "SPLAYERS : " << sizeof(SPLAYERS) << std::endl;

	//struct tm stTime;
	//time_t longTime;

	//time(&longTime);
	//localtime_s(&stTime, &longTime);

	//std::cout << "[before sleep]" << std::endl;
	//std::cout << "time1 : " << stTime.tm_sec << std::endl;

	//Sleep(5000);

	//struct tm stTime2;
	//time_t longTime2;

	//time(&longTime2);
	//localtime_s(&stTime2, &longTime2);

	//std::cout << "time1 : " << stTime.tm_sec << std::endl;
	//std::cout << "time2 : " << stTime2.tm_sec << std::endl;


	/////////////////////////////// TEST ///////////////////////////////////////


	//std::queue<char*> bufferQueue;

	//char* str = new char[16];

	//memset(str, 0, 16);
	//memcpy(str, "12435", 5);

	//bufferQueue.push(str);

	//delete[] str;

	//char* data = bufferQueue.front();
	//bufferQueue.pop();

	//std::cout << data << std::endl;


	/////////////////////////////// TEST ///////////////////////////////////////


	//std::queue<char*> bufferQueue;
	//
	//if (true)
	//{
	//	char temp[8] = "0123456";

	//	bufferQueue.push(temp);
	//}

	//char* p = bufferQueue.front();
	//bufferQueue.pop();

	//std::cout << p << std::endl;

	
	/////////////////////////////// TEST ///////////////////////////////////////


	//char buffer[16] = "012345678901234";

	//char* p = buffer + 4;

	//memset(p, 0, 6);

	//std::cout << buffer << std::endl;

	//char* p2 = buffer + 6;

	//memcpy(p2, "123", 3);


	/////////////////////////////// TEST ///////////////////////////////////////


	CircularBuffer cBuf;
	char temp[16] = "";

	char* p = cBuf.GetWritablePointer();

	memcpy(p, "abcdefghijklmn", 14);
	cBuf.CommitDataSize(14);

	std::cout << p << std::endl;
	std::cout << cBuf.GetAvailableBufferSize() << std::endl;

	cBuf.Pop(temp, 13);
	p = cBuf.GetWritablePointer();
	
	memcpy(p, "qw", 2);
	cBuf.CommitDataSize(2);

	std::cout << cBuf.GetAvailableBufferSize() << std::endl;

	p = cBuf.GetWritablePointer();

	memcpy(p, "tyui", 4);
	cBuf.CommitDataSize(4);
	
	/////////////////////////////// TEST ///////////////////////////////////////


	//CRingBuffer buf;

	//char temp1[] = { "abcd" };
	//char temp2[] = { "efgh" };
	//char temp3[] = { "ijklmn" };

	//char dummy[16] = "";

	//buf.Push(temp1, 4);

	//strcpy_s(temp1, "qwer");

	//buf.Pop(dummy, 3);
	//buf.Pop(dummy, 1);
	//std::cout << dummy << std::endl;

	// 테스트 결과
	// push 후에 temp1 의 내용을 바꿔도 memcpy한 내용은 바뀌지않음.

	//char* p = new char[4];
	//memcpy(p, temp2, 4);

	//std::cout << &p << std::endl;
	//std::cout << &temp2  << std::endl;

	//delete[] p;

	//buf.Push(temp2, 4);
	//buf.Pop(dummy, 2);
	//std::cout << dummy << std::endl;

	//buf.Push(temp3, 6);
	//buf.Pop(dummy, 9);
	//std::cout << dummy << std::endl;

	return 0;
}