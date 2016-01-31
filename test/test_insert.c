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

bool test_insert_01()
{
    slist_init(int, my_slist_int, int_cmp);    
    bool res = true;
    unsigned int size = arc4random_uniform(10000);

    for(unsigned int i = 0; i < size; i++)
    {
        int * v = malloc(sizeof(*v));
        *v = arc4random();
        my_slist_int->insert(my_slist_int, v);          
    }

    if(my_slist_int->size != size)
    {
        fprintf(stderr, "[test_insert] slist size is %d, but %d was expected", my_slist_int->size, size);
        res = false;
    }

    // Cleaning the mess
    slist_free(int, my_slist_int);

    return res;
}

bool test_insert_02()
{
    slist_init(int, my_slist_int, int_cmp);    
    bool res = true;
    unsigned int size = arc4random_uniform(10000);
    for(unsigned int i = 0; i < size; i++)
    {
        int * v = malloc(sizeof(*v));
        *v = arc4random();
        my_slist_int->insert(my_slist_int, v);          
    }

    for(unsigned int i = 0; i < my_slist_int->size - 1 ; i++)
    {
        if(my_slist_int->cmp(my_slist_int->at(my_slist_int, i), my_slist_int->at(my_slist_int, i+1)) > 0)
        {
            printf("%d < %d ?", *my_slist_int->at(my_slist_int, i), *my_slist_int->at(my_slist_int, i+1));
            return false;
            break;
        }            
    }

    // Cleaning the mess
    slist_free(int, my_slist_int);

    return res;

}

int main()
{
    if(test_insert_01())
        printf("[OK] test_insert_01 succeed\n");
    else
        printf("[KO] test_insert_01 failed\n");

    if(test_insert_02())
        printf("[OK] test_insert_02 succeed\n");
    else
        printf("[KO] test_inssert_02 failed\n");
}
