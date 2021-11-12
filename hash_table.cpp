#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.hpp"

//such memory leak potential in here
void HashTable::add(const char* name, void* content)
{
	if (!this->get(name))
	{
		int index = this->_hash(name);
		if (index >= this->len)
		{
			this->len++;
			this->_realloc_arr();
			if (!this->_arr)
			{
				return;
			}
		}
		this->_arr[this->_hash(name)] = content;
	}
}

void HashTable::remove(const char* name)
{
	//deletion must be done by caller
    this->_arr[this->_hash(name)] = nullptr;
}

void* HashTable::get(const char* name) const
{
	int index = this->_hash(name);
	if (index >= this->len)
	{
		return nullptr;
	}
    return this->_arr[index];
}

HashTable::HashTable()
{
    this->len = 50;
    this->_arr = (void**)malloc(sizeof(void*)*this->len);
    for (int i = 0; i < this->len; i++)
    {
        this->_arr[i] = nullptr;
    }
}

HashTable::~HashTable()
{
	//deletion of array elements must be done by caller
    free(this->_arr);
}

void HashTable::_realloc_arr()
{
    this->_arr = (void**)realloc(this->_arr, sizeof(void*)*this->len);
}

int HashTable::_hash(const char* str) const
{
    int p = 31;
    int m = 1e9 + 9;
    int power_of_p = 1;
    int index = 0;
    int len = strlen(str); //O(n) squared...
    for (int i = 0; i < len; i++)
    {
        index = (index + (str[i] - 'a' + 1) * power_of_p);
        power_of_p = (power_of_p * p) % m; 
    }
    return ((index + m) % m) % this->len;
}

char* get_str()
{
    char c;
    int len = 0;
    char* str = (char*)malloc(sizeof(char) * len);
    for (c = fgetc(stdin); c != '\n' && c != EOF; c = fgetc(stdin))
    {
        len++;
        str = (char*)realloc(str, sizeof(char) * len);
        str[len-1] = c;
    }
    return str;
}