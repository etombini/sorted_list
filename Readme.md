
* `slist(type)` declares all data structure to handle a sorted list composed of items. 
The type of item is user defined but must be a single word.
```c
struct something {
	/* some declaration */
};
typedef struct something new_type;

slist(new_type); // declares a struct slist_new_type
```

* `slist_init(type, name, cmp)` instanciates a pointer to a sorted list named `name`. 
Memory allocation is done within this macro. `cmp` is a comparison function 
the user must provide. `cmp` prototype must be `int cmp(type * a1, type * a1)` where
`type` is the type used in `slist(type)`.
 `cmp` must return an integer greater than, equal to, or less than 0, according as 
 `a1` is greater than, equal to, or less than `a2`.

* `slist_free(type, name)` free all memory used by the sorted list, including each item. 
Note that a simple call to `free()` is done on each item. If your item data structure is
complex and requires nested calls to `free()` you must empty the sorted list before freeing 
it using iterative calls to the `remove_at()` method.
```c
slist(int); // sorted list of int

int int_cmp(int * a, int * b)
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

    slist_free(int, my_slist);
}
```

All functions are included in the slist structure as pointers to function for ease of use 
(my optinion, but you can use macro-generated function if preferred).

```c
slist(int); // sorted list of int

int int_cmp(int * a, int * b)
{
        return -1;
}

int main(int argc, char ** argv)
{
    slist_init(int, my_slist, int_cmp);
	int * i = malloc(sizeof(*i));
    *i = 42;

    my_slist->insert(my_slist, i);

    slist_free(int, my_slist);
}
```


* `void slist_name->insert(slist_type * slist_name, type * value)`

* `type * slist_name->remove(slist_type * slist_name, type * value)`

* `type * slist_name->remove_at(slist_type * slist_name, unsigned int index)`

* `slist_type_pos slist_name->is_in(slist_type * slist_name, type * value)`

* `type * slist_name->at(slist_type * slist_name, unsigned int index)`

* `type ** slist_name->as_array(slist_type * slist_name)`

* `unsigned int slist_name->size`

* `int slist_name->cmp_slist(slist_type * slist_name, slist_type * other_slist)`

