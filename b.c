#include <stdio.h>
#include <malloc.h>

#define ERROR -1
#define OK 1

#define HASHSIZE 12
#define NULLKEY -32768

typedef struct
{
    int *elem;          //数据元素的地址，动态分配数组
    int count;          //当前数据元素的个数
}HashTable;

int InitHashTable(HashTable *H)
{
    H -> count = HASHSIZE;
    H -> elem = (int*)malloc(HASHSIZE * sizeof(int));
    if( !H -> elem)
    {
        return -1;
    }
    for(int i = 0;i < HASHSIZE;i++)
    {
        H -> elem[i] = NULLKEY;
    }
    return 0;
}

//使用残留余数法
int Hash(int key){
    return key % HASHSIZE;
}

//插入关键字到散列表
void InsertHash(HashTable *H,int key)
{
    int addr;

    addr = Hash(key);
    while(H -> elem[addr] != NULLKEY)       //如果不为空，则冲突出现
    {
        addr = (addr + 1) % HASHSIZE;
    }

    H -> elem[addr] = key;
}

//散列表查找关键字
int SearchHash(HashTable H,int key,int *addr)
{
    *addr = Hash(key);

    while(H.elem[*addr] != key)
    {
        *addr = (*addr + 1) % HASHSIZE;
        if(H.elem[*addr] == NULLKEY || *addr == Hash(key))
        {
            return ERROR;
        }
    }

    return 0;
}