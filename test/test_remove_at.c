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

bool test_remove_at_01()
{
    slist_init(int, my_slist_int, int_cmp);    

    int * tmp1;
    unsigned int index;
    bool res;

    unsigned int size = arc4random_uniform(1000);

    for(unsigned int i = 0; i < size; i++)
    {
        int * v = malloc(sizeof(*v));
        *v = arc4random();
        my_slist_int->insert(my_slist_int, v);          
    }

    index = arc4random_uniform(size - 1);
    tmp1 = my_slist_int->at(my_slist_int, index);
    my_slist_int->remove_at(my_slist_int, index);
   
    if(*tmp1 == *my_slist_int->at(my_slist_int, index))
        res = false;
    else
        res = true;
 
    if(res && my_slist_int->size == size - 1)
        res = true;
    else
        res = false;
 
    // Cleaning the mess
    free(tmp1);
    slist_free(int, my_slist_int); 
 
    return res;
}

int main()
{
    if(test_remove_at_01())
        printf("[OK] test_remove_at_01 succeed\n");
    else
        printf("[KO] test_remove_at_01 failed\n");
}
