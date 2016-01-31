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

bool test_at_01()
{
    slist_init(int, my_slist_int, int_cmp);    
    bool res = true;

    int * list_int[10];
    for(int i = 0; i<10; i++)
    {    
        list_int[i] = malloc(sizeof(list_int[i]));
        if(list_int[i] == NULL)
        {
            fprintf(stderr, "Can not allocate memory for list_int[%d]\n", i);
            exit(EXIT_FAILURE);
        }
    }

    * list_int[0] = 4;
    * list_int[1] = 5;
    * list_int[2] = 3;
    * list_int[3] = 8;
    * list_int[4] = 9;
    * list_int[5] = 7;
    * list_int[6] = 2;
    * list_int[7] = 1;
    * list_int[8] = 0;
    * list_int[9] = 6;
   
    for(int i = 0; i<10; i++)
        my_slist_int->insert(my_slist_int, list_int[i]);

    for(int i = 0; i < 10; i++)
    {
        if(*my_slist_int->at(my_slist_int, i) != i)
        {
            fprintf(stderr, "Hey Houston, we've got a problem, %d is not %d\n", i, *my_slist_int->at(my_slist_int, i));
            res = false;
        }
    }

    // Cleaning the mess
    // list_int[i] are freed in the for loop
    slist_free(int, my_slist_int);

    return true;
}

bool test_at_02()
{
    slist_init(int, sl, int_cmp);

    bool res = false;
    //unsigned int size = arc4random_uniform(1000);
    unsigned int size = 10000; 
    unsigned int middle = size/2;
    unsigned int offset = arc4random_uniform(middle); 
    int * middle_value;
    int * new_middle_value;
    int * v; //tmp pointer

    for(unsigned int i = 0; i < size; i++)
    {
        v = malloc(sizeof(*v));
        //*v = arc4random();
        *v = i;
        sl->insert(sl, v);
    }
    
    // Adding "offset" values that must be lower than middle_value
    // New position for middle value is to be middle+offset
    middle_value = sl->at(sl, middle);
    for(unsigned int i = 0; i < offset; i++)
    {
        v = malloc(sizeof(*v));
        *v = i;
        sl->insert(sl, v);
    }
    
    new_middle_value = sl->at(sl, middle + offset);
    if(*new_middle_value != *middle_value)
        res = false;
    else  
        res = true;

    //Cleaning
    slist_free(int, sl);
    
    return res;
}

int main()
{
    if(test_at_01())
        printf("[OK] test_at_01 succeed\n");
    else
        printf("[KO] test_at_01 failed\n");
 
    if(test_at_02())
        printf("[OK] test_at_02 succeed\n");
    else
        printf("[KO] test_at_02 failed\n");
}
