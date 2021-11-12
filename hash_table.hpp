struct HashTable
{
    void** _arr;
    int len;
    HashTable();
    ~HashTable();
    void _realloc_arr();
    int _hash(const char* str) const;
    void add(const char* name, void* content);
    void remove(const char* name);
    void* get(const char* name) const;
};


char* get_str();