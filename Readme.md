
* `slist(type)` declares all data structure to handle a sorted list composed of items. 
The type of item is user defined but must be a single word.
```c
struct my_struct {
	/* some declaration */
};
typedef struct my_struct my_struct;

slist(my_struct);
```

* `slist_init(type, name, cmp)` instanciates a pointer to a sorted list named `name`. 
Memory allocation is done within this macro. `cmp` is a comparison function 
the user must provide. `cmp` prototype must be `int cmp(type *, type *)` where
`type` is the type used in `slist(type)`.
```
slist(int); // sorted list of int

int int_cmp(int * a, int *b)
{
    if(*a == *b)
        return 0;
    if(*a > *b)
        return 1;
    else
        return -1;
}

int main(int argc, char ** argv)
{
    slist_init(int, my_slist, int_cmp);
	
	/* my_slist is available */
}

```
