#include "slist.h"

#include <stdlib.h> //arc4random

slist(int) // provide struct slist_int;

// comparison function
int int_cmp(int * a, int *b)
{
    if(*a == *b)
        return 0;
    if(*a > *b)
        return 1;
    else
        return -1;
}

bool test_is_in_01()
{
    slist_init(int, my_slist_int, int_cmp);    
    struct slist_int_pos pos;
    bool res = true;
    unsigned int size = arc4random_uniform(10000);
    int canary = arc4random_uniform(size);

    for(unsigned int i = 0; i < size; i++)
    {
        int * v = malloc(sizeof(*v));
        *v = i;
        my_slist_int->insert(my_slist_int, v);          
    }

    pos = my_slist_int->is_in(my_slist_int, &canary);

    if(pos.is_in == false)
    {
        fprintf(stderr, "DEBUG - test_is_in - Canary %d not found in slist of size %d\n", canary, size);
        res = false;
    }

    if(pos.pos != (unsigned int)canary)
    {
        fprintf(stderr, "DEBUG - test_is_in - Canary %d found at position %d\n", canary, pos.pos);
        res =  false;
    }

    if(*pos.value != canary)
    {
        fprintf(stderr, "DEBUG - test_is_in - Value at position %d is %d, canary is %d\n", *pos.value, pos.pos, canary);
        res = false;
    }

    // Cleaning the mess
    slist_free(int, my_slist_int);

    return res;
}

bool test_is_in_02()
{
    slist_init(int, my_slist_int, int_cmp);    
    struct slist_int_pos pos;
    bool res = true;
    unsigned int size = arc4random_uniform(10000);
    int canary = size;

    for(unsigned int i = 0; i < size; i++)
    {
        int * v = malloc(sizeof(*v));
        *v = i;
        my_slist_int->insert(my_slist_int, v);          
    }

    pos = my_slist_int->is_in(my_slist_int, &canary);

    if(pos.is_in == true)
    {
        fprintf(stderr, "DEBUG - test_is_in - Canary %d found in slist of size %d\n", canary, size);
        res = false;
    }

    // Cleaning the mess
    slist_free(int, my_slist_int);

    return res;
}

int main()
{
    if(test_is_in_01())
        printf("[OK] test_is_in_01 succeed\n");
    else
        printf("[KO] test_is_in_01 failed\n");
    if(test_is_in_02())
        printf("[OK] test_is_in_02 succeed\n");
    else
        printf("[KO] test_is_in_02 failed\n");
}
