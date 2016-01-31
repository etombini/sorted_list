#ifndef SLIST_H
#define SLIST_H

#include <stdio.h> // fprintf() 
#include <string.h>
#include <stdlib.h> // exit()
#include <stdbool.h>
#include<pthread.h> // mutex

#define slist(type)                                                                                     \
    struct slist_ ## type;                                                                              \
    struct slist_ ## type ## _node;                                                                     \
    struct slist_ ## type ## _pos;                                                                      \
                                                                                                        \
    struct slist_ ##  type ## _node {                                                                   \
        type * value;                                                                                   \
        struct slist_ ##  type ## _node * next;                                                         \
    };                                                                                                  \
                                                                                                        \
    struct slist_ ## type {                                                                             \
        struct slist_ ##  type ## _node * root;                                                         \
        unsigned int size;                                                                              \
        pthread_mutex_t slist_lock;                                                                     \
                                                                                                        \
        int (*cmp)(type *, type *);                                                                     \
        void (*insert)(struct slist_ ## type *, type *);                                                \
        type * (*remove)(struct slist_ ## type *, type *);                                              \
        type * (*remove_at)(struct slist_ ## type *, unsigned int);                                     \
        struct slist_ ## type ## _pos (*is_in)(struct slist_ ## type *, type *);                        \
        type * (*at)(struct slist_ ## type *, unsigned int index);                                      \
        struct slist_ ##  type ## _node ** (*as_node_array)(struct slist_ ## type *);                   \
        type ** (*as_array)(struct slist_ ## type *);                                                   \
        int (*cmp_slist)(struct slist_ ## type *, struct slist_ ## type *);                             \
        int (*lock)(struct slist_ ## type *);                                                           \
        int (*unlock)(struct slist_ ## type *);                                                         \
    };                                                                                                  \
                                                                                                        \
    struct slist_ ## type ## _pos {                                                                     \
        bool is_in;                                                                                     \
        unsigned int pos;                                                                               \
        type * value;                                                                                   \
    };                                                                                                  \
                                                                                                        \
    void slist_ ## type ## _insert(struct slist_ ## type * l, type * value)                             \
    {                                                                                                   \
        l->lock(l);                                                                                     \
        struct slist_ ## type ## _node ** nodes;                                                        \
        struct slist_ ## type ## _node * new_node;                                                      \
                                                                                                        \
        int i_inf, i_sup, i_mid;                                                                        \
                                                                                                        \
        new_node = malloc(sizeof(*new_node));                                                           \
        if(new_node == NULL)                                                                            \
        {                                                                                               \
            fprintf(stderr, "Can not allocate memory for new node");                                    \
            exit(EXIT_FAILURE);                                                                         \
        }                                                                                               \
                                                                                                        \
        new_node->value = value;                                                                        \
        new_node->next = NULL;                                                                          \
                                                                                                        \
        if(l->root == NULL)                                                                             \
        {                                                                                               \
            l->root = new_node;                                                                         \
            l->size++;                                                                                  \
            l->unlock(l);                                                                               \
            return;                                                                                     \
        }                                                                                               \
                                                                                                        \
        if(l->cmp(l->root->value, new_node->value) > 0)                                                 \
        {                                                                                               \
            new_node->next = l->root;                                                                   \
            l->root = new_node;                                                                         \
            l->size++;                                                                                  \
            l->unlock(l);                                                                               \
            return;                                                                                     \
        }                                                                                               \
                                                                                                        \
        nodes = l->as_node_array(l);                                                                    \
                                                                                                        \
        i_inf = 0;                                                                                      \
        i_sup = l->size - 1;                                                                            \
                                                                                                        \
        if(l->cmp(new_node->value, nodes[i_sup]->value) > 0)                                            \
        {                                                                                               \
            nodes[i_sup]->next = new_node;                                                              \
            l->size++;                                                                                  \
            free(nodes);                                                                                \
            l->unlock(l);                                                                               \
            return;                                                                                     \
        }                                                                                               \
                                                                                                        \
        while(i_sup - i_inf > 1)                                                                        \
        {                                                                                               \
            i_mid = (i_inf + i_sup)/2;                                                                  \
            if(l->cmp(new_node->value, nodes[i_mid]->value) > 0)                                        \
                i_inf = i_mid;                                                                          \
            else                                                                                        \
                i_sup = i_mid;                                                                          \
        }                                                                                               \
                                                                                                        \
        nodes[i_inf]->next = new_node;                                                                  \
        new_node->next = nodes[i_sup];                                                                  \
        l->size++;                                                                                      \
        free(nodes);                                                                                    \
        l->unlock(l);                                                                                   \
        return;                                                                                         \
    }                                                                                                   \
                                                                                                        \
    type * slist_ ## type ## _remove(struct slist_ ## type * l, type * value)                           \
    {                                                                                                   \
        l->lock(l);                                                                                     \
        struct slist_ ## type ## _node * current;                                                       \
        struct slist_ ## type ## _node ** nodes;                                                        \
        int i_inf, i_sup, i_mid;                                                                        \
                                                                                                        \
        type * v;                                                                                       \
        v = NULL;                                                                                       \
                                                                                                        \
        if(l->root == NULL)                                                                             \
        {                                                                                               \
            l->unlock(l);                                                                               \
            return v;                                                                                   \
        }                                                                                               \
                                                                                                        \
        current = l->root;                                                                              \
                                                                                                        \
        if(l->cmp(current->value, value) > 0)                                                           \
        {                                                                                               \
            l->unlock(l);                                                                               \
            return v;                                                                                   \
        }                                                                                               \
                                                                                                        \
        if(l->cmp(current->value, value) == 0)                                                          \
        {                                                                                               \
            l->root = current->next;                                                                    \
            v = current->value;                                                                         \
            free(current);                                                                              \
            l->size--;                                                                                  \
            l->unlock(l);                                                                               \
            return v;                                                                                   \
        }                                                                                               \
                                                                                                        \
        nodes = l->as_node_array(l);                                                                    \
        i_inf = 0;                                                                                      \
        i_sup = l->size - 1;                                                                            \
                                                                                                        \
        if(l->cmp(value, nodes[i_sup]->value) > 0)                                                      \
        {                                                                                               \
            free(nodes);                                                                                \
            l->unlock(l);                                                                               \
            return v;                                                                                   \
        }                                                                                               \
                                                                                                        \
        while(i_sup - i_inf > 1)                                                                        \
        {                                                                                               \
            i_mid = (i_inf + i_sup)/2;                                                                  \
            if(l->cmp(value, nodes[i_mid]->value) > 0)                                                  \
                i_inf = i_mid;                                                                          \
            else                                                                                        \
                i_sup = i_mid;                                                                          \
        }                                                                                               \
                                                                                                        \
        if(l->cmp(value, nodes[i_sup]->value) == 0)                                                     \
        {                                                                                               \
            v = nodes[i_sup]->value;                                                                    \
            nodes[i_inf]->next = nodes[i_sup]->next;                                                    \
            free(nodes[i_sup]);                                                                         \
            l->size--;                                                                                  \
            free(nodes);                                                                                \
            l->unlock(l);                                                                               \
            return v;                                                                                   \
        }                                                                                               \
        else                                                                                            \
        {                                                                                               \
            free(nodes);                                                                                \
            l->unlock(l);                                                                               \
            return v;                                                                                   \
        }                                                                                               \
    }                                                                                                   \
                                                                                                        \
    type * slist_ ## type ## _remove_at(struct slist_ ## type * l, unsigned int index)                  \
    {                                                                                                   \
        l->lock(l);                                                                                     \
        struct slist_ ## type ## _node * current;                                                       \
        struct slist_ ## type ## _node ** nodes;                                                        \
        type * v = NULL;                                                                                \
                                                                                                        \
        if(index + 1 > l->size) /* handle the case when l is empty (size = 0) and nodes is NULL */      \
        {                                                                                               \
            l->unlock(l);                                                                               \
            return v;                                                                                   \
        }                                                                                               \
                                                                                                        \
        if(index == 0)                                                                                  \
        {                                                                                               \
            current = l->root;                                                                          \
            l->root = l->root->next;                                                                    \
            v = current->value;                                                                         \
            free(current);                                                                              \
            l->size--;                                                                                  \
            l->unlock(l);                                                                               \
            return v;                                                                                   \
        }                                                                                               \
                                                                                                        \
        nodes = l->as_node_array(l);                                                                    \
        if(nodes == NULL)                                                                               \
        {                                                                                               \
            fprintf(stderr, "DEBUG - remove_at[%d]: nodes is not supposed to be NULL\n", index);        \
            exit(EXIT_FAILURE);                                                                         \
        }                                                                                               \
        nodes[index - 1]->next = nodes[index]->next;                                                    \
        v = nodes[index]->value;                                                                        \
        free(nodes[index]);                                                                             \
        l->size--;                                                                                      \
        free(nodes);                                                                                    \
        l->unlock(l);                                                                                   \
        return v;                                                                                       \
    }                                                                                                   \
                                                                                                        \
    struct slist_ ## type ## _pos  slist_ ## type ## _is_in(struct slist_ ## type * l, type * value)    \
    {                                                                                                   \
        l->lock(l);                                                                                     \
        struct slist_ ## type ## _node ** nodes;                                                        \
        struct slist_ ## type ## _pos pos;                                                              \
        unsigned int i_inf, i_sup, i_mid;                                                               \
                                                                                                        \
        pos.is_in = false;                                                                              \
        pos.pos = 0;                                                                                    \
        pos.value = NULL;                                                                               \
                                                                                                        \
        if(l->root == NULL)                                                                             \
        {                                                                                               \
            l->unlock(l);                                                                               \
            return pos;                                                                                 \
        }                                                                                               \
                                                                                                        \
        if(l->cmp(l->root->value, value) > 0)                                                           \
        {                                                                                               \
            l->unlock(l);                                                                               \
            return pos;                                                                                 \
        }                                                                                               \
                                                                                                        \
        nodes = l->as_node_array(l);                                                                    \
                                                                                                        \
        i_inf = 0;                                                                                      \
        i_sup = l->size - 1;                                                                            \
                                                                                                        \
        if(l->cmp(value, nodes[i_sup]->value) > 0)                                                      \
        {                                                                                               \
            free(nodes);                                                                                \
            l->unlock(l);                                                                               \
            return pos;                                                                                 \
        }                                                                                               \
                                                                                                        \
        while(i_sup - i_inf > 1)                                                                        \
        {                                                                                               \
            i_mid = (i_inf + i_sup)/2;                                                                  \
            if(l->cmp(value, nodes[i_mid]->value) > 0)                                                  \
                i_inf = i_mid;                                                                          \
            else                                                                                        \
                i_sup = i_mid;                                                                          \
        }                                                                                               \
                                                                                                        \
        if(l->cmp(value, nodes[i_sup]->value) == 0)                                                     \
        {                                                                                               \
            pos.is_in = true;                                                                           \
            pos.pos = i_sup;                                                                            \
            pos.value = nodes[i_sup]->value;                                                            \
        }                                                                                               \
        free(nodes);                                                                                    \
        l->unlock(l);                                                                                   \
        return pos;                                                                                     \
    }                                                                                                   \
                                                                                                        \
    type * slist_ ## type ## _at(struct slist_ ## type * l, unsigned int index)                         \
    {                                                                                                   \
        l->lock(l);                                                                                     \
        struct slist_ ## type ## _node * current;                                                       \
        type * v;                                                                                       \
        v = NULL;                                                                                       \
                                                                                                        \
        if(index > l->size - 1 || l->root == NULL)                                                      \
        {                                                                                               \
            l->unlock(l);                                                                               \
            return v;                                                                                   \
        }                                                                                               \
                                                                                                        \
        current = l->root;                                                                              \
        for(unsigned int i = 0; i < index; i++)                                                         \
            current = current->next;                                                                    \
                                                                                                        \
        v = current->value;                                                                             \
        l->unlock(l);                                                                                   \
        return v;                                                                                       \
    }                                                                                                   \
                                                                                                        \
    struct slist_ ##  type ## _node ** slist_ ## type ## _as_node_array(struct slist_ ## type * l)      \
    {                                                                                                   \
        struct slist_ ## type ## _node * current;                                                       \
        struct slist_ ## type ## _node ** nodes;                                                        \
                                                                                                        \
        if(l->size == 0)                                                                                \
            return NULL;                                                                                \
                                                                                                        \
        nodes = calloc(l->size, sizeof(*nodes));                                                        \
        if(nodes == NULL)                                                                               \
        {                                                                                               \
            fprintf(stderr, "Can not allocate memory for slist nodes array");                           \
            exit(EXIT_FAILURE);                                                                         \
        }                                                                                               \
                                                                                                        \
        current = l->root;                                                                              \
        for(unsigned int i = 0; i < l->size; i++)                                                       \
        {                                                                                               \
            *(nodes + i) = current;                                                                     \
            current = current->next;                                                                    \
        }                                                                                               \
        return nodes;                                                                                   \
    }                                                                                                   \
                                                                                                        \
    type ** slist_ ## type ## _as_array(struct slist_ ## type * l)                                      \
    {                                                                                                   \
        l->lock(l);                                                                                     \
        struct slist_ ## type ## _node * current;                                                       \
        type ** values;                                                                                 \
                                                                                                        \
        if(l->size == 0)                                                                                \
        {                                                                                               \
            l->unlock(l);                                                                               \
            return NULL;                                                                                \
        }                                                                                               \
                                                                                                        \
        values = calloc(l->size, sizeof(*values));                                                      \
        if(values == NULL)                                                                              \
        {                                                                                               \
            fprintf(stderr, "Can not allocate memory for slist values array");                          \
            exit(EXIT_FAILURE);                                                                         \
        }                                                                                               \
                                                                                                        \
        current = l->root;                                                                              \
        for(unsigned int i = 0; i < l->size; i++)                                                       \
        {                                                                                               \
            *(values + i) = current->value;                                                             \
            current = current->next;                                                                    \
        }                                                                                               \
        l->unlock(l);                                                                                   \
        return values;                                                                                  \
    }                                                                                                   \
                                                                                                        \
    int slist_ ## type ## _cmp_slist(struct slist_ ## type * sl1, struct slist_ ## type * sl2)          \
    {                                                                                                   \
        struct slist_ ## type ## _node * current_node_sl1;                                              \
        struct slist_ ## type ## _node * current_node_sl2;                                              \
        int cmp = 0;                                                                                    \
        unsigned int size;                                                                              \
                                                                                                        \
        if(sl1->size > sl2->size)                                                                       \
            size = sl2->size;                                                                           \
        else                                                                                            \
            size = sl1->size;                                                                           \
                                                                                                        \
        current_node_sl1 = sl1->root;                                                                   \
        current_node_sl2 = sl2->root;                                                                   \
                                                                                                        \
        for(unsigned int i = 0; i < size; i++)                                                          \
        {                                                                                               \
            cmp = sl1->cmp(current_node_sl1->value, current_node_sl2->value);                           \
            if(cmp != 0)                                                                                \
                return cmp;                                                                             \
            current_node_sl1 = current_node_sl1->next;                                                  \
            current_node_sl2 = current_node_sl2->next;                                                  \
        }                                                                                               \
                                                                                                        \
        if(sl1->size > sl2->size)                                                                       \
            return 1;                                                                                   \
        if(sl1->size < sl2->size)                                                                       \
            return -1;                                                                                  \
        else                                                                                            \
            return 0;                                                                                   \
    }                                                                                                   \
                                                                                                        \
    int slist_ ## type ## _lock(struct slist_ ## type * l)                                              \
    {                                                                                                   \
        return pthread_mutex_lock(&l->slist_lock);                                                      \
    }                                                                                                   \
                                                                                                        \
    int slist_ ## type ## _unlock(struct slist_ ## type * l)                                            \
    {                                                                                                   \
        return pthread_mutex_unlock(&l->slist_lock);                                                    \
    }                                                                                                   \


#define slist_init(type, name, _cmp)                                                                    \
    struct slist_ ## type * name;                                                                       \
    name = malloc(sizeof(* name));                                                                      \
    if(name == NULL)                                                                                    \
    {                                                                                                   \
        fprintf(stderr, "Can not allocate memory for sorted_list");                                     \
        exit(EXIT_FAILURE);                                                                             \
    }                                                                                                   \
    if (pthread_mutex_init(&name->slist_lock, NULL) != 0)                                               \
    {                                                                                                   \
        fprintf(stderr, "Can not initialize mutex for sorted_list");                                    \
        exit(EXIT_FAILURE);                                                                             \
    }                                                                                                   \
    name->size = 0;                                                                                     \
    name->root = NULL;                                                                                  \
    name->cmp = &_cmp;                                                                                  \
    name->insert = &slist_ ## type ## _insert;                                                          \
    name->remove = &slist_ ## type ## _remove;                                                          \
    name->remove_at = &slist_ ## type ## _remove_at;                                                    \
    name->is_in = &slist_ ## type ## _is_in;                                                            \
    name->at = &slist_ ## type ## _at;                                                                  \
    name->as_array = &slist_ ## type ## _as_array;                                                      \
    name->as_node_array = &slist_ ## type ## _as_node_array;                                            \
    name->cmp_slist = &slist_ ## type ## _cmp_slist;                                                    \
    name->lock = &slist_ ## type ## _lock;                                                              \
    name->unlock = &slist_ ## type ## _unlock;                                                          \
    

#define slist_free(type, name)                                                                          \
    while(name->size > 0)                                                                               \
    {                                                                                                   \
        type * garbage = name->remove_at(name, 0);                                                      \
        free(garbage);                                                                                  \
    }                                                                                                   \
    pthread_mutex_destroy(&name->slist_lock);                                                           \
    free(name);                                                                                         \


#endif
