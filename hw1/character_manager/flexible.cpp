#include "flexible.h"

using namespace std;


// The constructor creates a unique_ptr to a dynamically allocated array of two
// CharacterBlocks using the initialization list syntax. No need to change this
// unless you add fields to the FlexibleCharacterManager.
FlexibleCharacterManager::FlexibleCharacterManager() : blocks(new CharacterBlock[2] {}) {}

char* FlexibleCharacterManager::alloc_chars(size_t n) {
	// TODO: your implementation here
	int j = 0;
	int k = n;
	for (int i = 0; i < 4096; i++)
	{
		if (buffer[i] == '\0')
		{
			j++;
			if (j == k)
			{
				blocks[blocks_in_use].address = buffer + i - k;
				blocks[blocks_in_use].size = n;
				blocks_in_use++;
				return buffer + i - k;
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
	for (int i = 0; i < blocks_in_use - 1; i++)
	{
		for (int m = 0; m < blocks_in_use - i - 1; m++)
		{
			if (blocks[m].address > blocks[m + 1].address)
			{
				char* temp = blocks[m].address;
				blocks[m].address = blocks[m + 1].address;
				blocks[m + 1].address = temp;
			}
		}
	}
}

void FlexibleCharacterManager::free_chars(char* p) {
	// TODO: your implementation here
	int j = 4999;
	for (int i = 0; i < 4095; i++)
	{
		if (p == buffer + i)
		{
			j = i;
			break;
		}
	}
	char* k;
	if (j != 4999)
	{
		for (int i = 0; i < blocks_in_use; i++)
		{
			if (blocks[i].address == p)
			{
				k = p+blocks[i].size;
			}
		}
	}
	
	char* l = p;
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
