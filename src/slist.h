#ifndef SLIST_H
#define SLIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define slist(type)                                                                         \
    struct slist_ ## type;                                                                  \
    struct slist_ ## type ## _node;                                                         \
                                                                                            \
    struct slist_ ##  type ## _node {                                                       \
        type * value;                                                                       \
        struct slist_ ##  type ## _node * next;                                             \
    };                                                                                      \
                                                                                            \
    struct slist_ ## type {                                                                 \
        struct slist_ ##  type ## _node * root;                                             \
        unsigned int size;                                                                  \
                                                                                            \
        int (*cmp)(type *, type *);                                                         \
        void (*insert)(struct slist_ ## type *, type *);                                    \
        type * (*remove)(struct slist_ ## type *, type *);                                  \
        type * (*remove_at)(struct slist_ ## type *, unsigned int);                         \
        int (*is_in)(struct slist_ ## type *, type *);                                      \
        type * (*at)(struct slist_ ## type *, type *);                                      \
    };                                                                                      \
                                                                                            \
    void slist_ ## type ## _insert(struct slist_ ## type * l, type * value)                 \
    {                                                                                       \
        struct slist_ ## type ## _node * current;                                           \
        struct slist_ ## type ## _node * new_node;                                          \
                                                                                            \
        struct slist_ ## type * nodes[l->size];                                             \
        int i_inf, i_sup;                                                                   \
                                                                                            \
        new_node = malloc(sizeof(*new_node));                                               \
        if(new_node == NULL)                                                                \
        {                                                                                   \
            fprintf(stderr, "Can not allocate memory for new node");                        \
            exit(EXIT_FAILURE);                                                             \
        }                                                                                   \
                                                                                            \
        new_node->value = value;                                                            \
        new_node->next = NULL;                                                              \
                                                                                            \
        if(l->root == NULL)                                                                 \
        {                                                                                   \
            l->root = new_node;                                                             \
            l->size++;                                                                      \
            return;                                                                         \
        }                                                                                   \
                                                                                            \
        current = l->root;                                                                  \
                                                                                            \
        if(l->cmp(current->value, new_node->value) > 0)                                     \
        {                                                                                   \
            new_node->next = current;                                                       \
            l->root = new_node;                                                             \
            l->size++;                                                                      \
            return;                                                                         \
        }                                                                                   \
                                                                                            \
        for(int i = 0; i<l->size; i++)                                                      \
        {                                                                                   \
            nodes[i] = current;                                                             \
            current = current->next;                                                        \
        }                                                                                   \
                                                                                            \
        i_inf = 0;                                                                          \
        i_sup = l->size - 1;                                                                \
                                                                                            \
        if(l->cmp(new_node->value, nodes[i_sup]->value) > 0)                                \
        {                                                                                   \
            nodes[i_sup]->next = new_node;                                                  \
            l->size++;                                                                      \
            return;                                                                         \
        }                                                                                   \
                                                                                            \
        while(i_sup - i_inf > 1)                                                            \
        {                                                                                   \
            i_mid = (i_inf + i_sup)/2;                                                      \
            if(l->cmp(new_node->value, nodes[i_mid]->value) > 0)                            \
                i_inf = i_mid;                                                              \
            else                                                                            \
                i_sup = i_mid;                                                              \
        }                                                                                   \
                                                                                            \
        nodes[i_inf]->next = new_node;                                                      \
        new_node->next = nodes[i_sup];                                                      \
        l->size++;                                                                          \
        return;                                                                             \
    }                                                                                       \
                                                                                            \
    type * slist_ ## type ## _remove(struct slist_ ## type * l, type * value)               \
    {                                                                                       \
        struct slist_ ## type ## _node * current;                                           \
        struct slist_ ## type * nodes[l->size];                                             \
        int i_inf, i_sup;                                                                   \
                                                                                            \
        type * v;                                                                           \
        v = NULL;                                                                           \
                                                                                            \
        if(l->root == NULL)                                                                 \
            return v;                                                                       \
                                                                                            \
        current = l->root;                                                                  \
                                                                                            \
        if(l->cmp(current->value, value) > 0)                                               \
            return v;                                                                       \
                                                                                            \
        if(l->cmp(current->value, value) == 0)                                              \
        {                                                                                   \
            l->root = current->next;                                                        \
            v = current->value;                                                             \
            free(current);                                                                  \
            l->size--;                                                                      \
            return v;                                                                       \
        }                                                                                   \
                                                                                            \
        for(int i = 0; i<l->size; i++)                                                      \
        {                                                                                   \
            nodes[i] = current;                                                             \
            current = current->next;                                                        \
        }                                                                                   \
                                                                                            \
        i_inf = 0;                                                                          \
        i_sup = l->size - 1;                                                                \
                                                                                            \
        if(l->cmp(value, nodes[i_sup]->value) > 0)                                          \
        {                                                                                   \
            return v;                                                                       \
        }                                                                                   \
                                                                                            \
        while(i_sup - i_inf > 1)                                                            \
        {                                                                                   \
            i_mid = (i_inf + i_sup)/2;                                                      \
            if(l->cmp(new_node->value, nodes[i_mid]->value) > 0)                            \
                i_inf = i_mid;                                                              \
            else                                                                            \
                i_sup = i_mid;                                                              \
        }                                                                                   \
        if(l->cmp(value, nodes[i_sup]->value) == 0)                                         \
        {                                                                                   \
            v = nodes[i_sup]->value;                                                        \
            current = nodes[i_sup];                                                         \
            nodes[i_inf]->next = nodes[i_sup]->next;                                        \
            free(current);                                                                  \
            l->size--;                                                                      \
            return v;                                                                       \
        }                                                                                   \
        else                                                                                \
            return v;                                                                       \
    }                                                                                       \
                                                                                            \
    type * remove_at(struct slist_ ## type * l, unsigned int index)                         \
    {                                                                                       \
        struct slist_ ## type * current;                                                    \
        struct slist_ ## type * nodes[l->size];                                             \
        type * v = NULL;                                                                    \
                                                                                            \
        if(index > l->size -1)                                                              \
            return v;                                                                       \
                                                                                            \
        if(index == 0)                                                                      \
        {                                                                                   \
            current = l->root;                                                              \
            l->root == current->next;                                                       \
            v = current->value;                                                             \
            free(current);                                                                  \
            l->size--;                                                                      \
            return v;                                                                       \
        }                                                                                   \
                                                                                            \
        for(int i = 0; i<l->size; i++)                                                      \
        {                                                                                   \
            nodes[i] = current;                                                             \
            current = current->next;                                                        \
        }                                                                                   \
                                                                                            \
        current = nodes[index];                                                             \
        nodes[index - 1]->next = nodes[index]->next;                                        \
        v = current->value;                                                                 \
        free(current);                                                                      \
        l->size--;                                                                          \
        return v;                                                                           \
    }                                                                                       \
                                                                                            \
    int (*is_in)(struct slist_ ## type * l, type * value)                                   \
    {                                                                                       \
        struct slist_ ## type ## _node * current;                                           \
        struct slist_ ## type * nodes[l->size];                                             \
        int i_inf, i_sup;                                                                   \
                                                                                            \
        type * v;                                                                           \
        v = NULL;                                                                           \
                                                                                            \
        if(l->root == NULL)                                                                 \
            return -1;                                                                      \
                                                                                            \
        if(l->cmp(l->root->value, value) > 0)                                               \
            return -1;                                                                      \
                                                                                            \
        for(int i = 0; i<l->size; i++)                                                      \
        {                                                                                   \
            nodes[i] = current;                                                             \
            current = current->next;                                                        \
        }                                                                                   \
                                                                                            \
        i_inf = 0;                                                                          \
        i_sup = l->size - 1;                                                                \
                                                                                            \
        if(l->cmp(value, nodes[i_sup]->value) > 0)                                          \
        {                                                                                   \
            return -1;                                                                      \
        }                                                                                   \
                                                                                            \
        while(i_sup - i_inf > 1)                                                            \
        {                                                                                   \
            i_mid = (i_inf + i_sup)/2;                                                      \
            if(l->cmp(new_node->value, nodes[i_mid]->value) > 0)                            \
                i_inf = i_mid;                                                              \
            else                                                                            \
                i_sup = i_mid;                                                              \
        }                                                                                   \
                                                                                            \
        if(l->cmp(value, nodes[i_sup]->value) == 0)                                         \
        {                                                                                   \
            return i_sup;                                                                   \
        }                                                                                   \
        else                                                                                \
            return -1;                                                                      \
    }
#endif
