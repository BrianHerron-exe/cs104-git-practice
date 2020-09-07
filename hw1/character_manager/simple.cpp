#include "simple.h"
#include <iostream>
using namespace std;


char* SimpleCharacterManager::alloc_chars(size_t size) {
	// TODO: your implementation here
	int j = 0;
	int k = size;
	for (int i = 0; i < 4096; i++)
	{
		if (buffer[i] == '\0')
		{
			j++;
			if (j == size)
			{
				return buffer+i-k;
			}
		}
		else if (i == 4095)
		{
			char* failure;
			*failure = '\0';
			return failure;
		}
		else
		{
			j = 0;
		}
	}
}

void SimpleCharacterManager::free_chars(char* address) {
	// TODO: your implementation here
	int j = 4999;
		for (int i = 0; i < 4095; i++)
		{
			if (address == buffer+i)
			{
				j = i;
				break;
			}
		}
		char* k = buffer+4095;
		char* l = address;
	if (j == 4999)
	{

	}
	else
	{
		for (l; l < k; l++)
		{
			*l = '\0';

		}
	}
}
