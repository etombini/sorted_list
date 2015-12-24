

#include "slist.h"

#include <stdlib.h> //arc4random

slist(int); // provide a struct slist_int;


int int_cmp(int * a, int *b)
{
    if(*a == *b)
        return 0;
    if(*a > *b)
        return 1;
    else
        return -1;
}

bool test_at()
{
    struct slist_int * my_slist_int;
    my_slist_int = malloc(sizeof(*my_slist_int));
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

    int * garbage;
    for(int i = 0; i < 10; i ++)
    {
        garbage = my_slist_int->remove_at(my_slist_int, 0);
        free(garbage);
    }
    free(my_slist_int);

    return true;
}



bool test_remove_at()
{
    struct slist_int * my_slist_int;
    my_slist_int = malloc(sizeof(*my_slist_int));
    slist_init(int, my_slist_int, int_cmp);    

    int * tmp1;
    unsigned int index;
    bool res;

    unsigned int size = arc4random_uniform(1000);

    for(int i = 0; i < size; i++)
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
 
     int * garbage;
     for(int i = 0; i < size - 1; i ++)
     {
         garbage = my_slist_int->remove_at(my_slist_int, 0);
         free(garbage);
     }
     free(my_slist_int);
 
     return res;
}

bool test_insert()
{
    struct slist_int * my_slist_int;
    my_slist_int = malloc(sizeof(*my_slist_int));
    slist_init(int, my_slist_int, int_cmp);    

    unsigned int size = arc4random_uniform(10000);

    for(int i = 0; i < size; i++)
    {
        int * v = malloc(sizeof(*v));
        *v = arc4random();
        my_slist_int->insert(my_slist_int, v);          
    }

    for(int i = 0; i < my_slist_int->size -1 ; i++)
    {
        if(my_slist_int->cmp(my_slist_int->at(my_slist_int, i), my_slist_int->at(my_slist_int, i+1)) > 0)
        {
            printf("%d < %d ?", *my_slist_int->at(my_slist_int, i), *my_slist_int->at(my_slist_int, i+1));
            return false;
        }            
    }

    // Cleaning the mess
    int * garbage;
    for(int i = 0; i < size; i ++)
    {
        garbage = my_slist_int->remove_at(my_slist_int, 0);
        free(garbage);
    }
    free(my_slist_int);
    return true;
}



int main(int argc, char ** argv)
{
    if(test_at())
        printf("[OK] test_at succeed\n");
    else
        printf("[KO] test_at failed\n");
 
    if(test_remove_at())
        printf("[OK] test_remove_at succeed\n");
    else
        printf("[KO] test_remove_at failed\n");

    if(test_insert())
        printf("[OK] test_insert succeed\n");
    else
        printf("[KO] test_inssert failed\n");

    struct slist_int * my_slist_int;
    my_slist_int = malloc(sizeof(*my_slist_int));
    slist_init(int, my_slist_int, int_cmp);    

    int * list_int[10];
    for(int i = 0; i<10; i++)
        list_int[i] = malloc(sizeof(list_int[i]));

    printf("02\n");

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
    
    printf("03\n");

    for(int i = 0; i<10; i++)
        my_slist_int->insert(my_slist_int, list_int[i]);

    printf("04\n");

    for(int i = 0; i<my_slist_int->size; i++)
        printf("%d: %d\n", i, * my_slist_int->at(my_slist_int, i));

    printf("05\n");

    my_slist_int->remove_at(my_slist_int, 5);

    printf("05\n");
    for(int i = 0; i<my_slist_int->size; i++)
        printf("%d: %d\n", i, * my_slist_int->at(my_slist_int, i));


}
