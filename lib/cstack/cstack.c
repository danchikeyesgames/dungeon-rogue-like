#include <stdlib.h>
#include <string.h>

#include "cstack.h"

static void* cstack_malloc();
static void cstack_free_node(cstack_node* nd);
static void cstack_free_Item(cstack_Item* nd);
static void _cstack_free(cstack_t st);

void sf_cstack_cpush(cstack_t cstack, void* object, void* args, size_t object_size) {
    cstack_constructor_t constr = cstack->constructor;
    cstack_node* tmp = (cstack_node *) malloc(sizeof(cstack_node));
    tmp->mem = (cstack_Item *) malloc(sizeof(cstack_Item));
    tmp->mem->data = malloc(object_size);
    tmp->mem->size_object = object_size;

    constr(object, tmp->mem->data, args);
}

void _sf_cstack_create(cstack_t* header, cstack_constructor_t c, cstack_destructor_t d, size_t type_size) {
    (*header) = (cstack_t) cstack_malloc();
    (*header)->constructor = c;
    (*header)->destructor = d;
    (*header)->bytes = type_size;
    (*header)->head = NULL;
    (*header)->size = 0;
}

void _sf_cstack_pop(cstack_t cs) {
    cstack_destructor_t destructor = cs->destructor;
    cstack_node* tmp = cstack_unpack(cs);

    if (tmp) {
        cs->head = cs->head->next;
        --cs->size;
        
        if (destructor) {
            destructor(tmp->mem->data);
        }
        free(tmp->mem->data);
        cstack_free_Item(tmp->mem);
        cstack_free_node(tmp);
    }
}

void cstack_set_constructor(cstack_t cstack, cstack_constructor_t constructor) {
    cstack->constructor = constructor;
}

void cstack_set_destructor(cstack_t cstack, cstack_destructor_t destructor) {
    cstack->destructor = destructor;
}

cstack_node* sf_cstack_peek(cstack_t stack, size_t count) {
    cstack_node* tmp = stack->head;
    size_t i = 1;

    while (i++ < count) {
        tmp = tmp->next;
    }

    return tmp;
}

void sf_cstack_destroy(cstack_t st) {
    cstack_node* current_node = cstack_unpack(st);
    cstack_node* next_node = NULL;
    cstack_destructor_t destructor = st->destructor;

    while (current_node != NULL) {
        next_node = current_node->next;

        if (destructor) {
            destructor(current_node->mem->data);
        }
        free(current_node->mem->data);
        cstack_free_Item(current_node->mem);
        cstack_free_node(current_node);

        current_node = next_node;
    }
}

void sf_cstack_free(cstack_t st) {
    _cstack_free(st);
}

/*
    ****************************** STATIC FUNCTION *******************************
*/

static void* cstack_malloc() {
    return malloc(sizeof(cstack_header));
}

static void cstack_free_node(cstack_node* nd) {
    free(nd);
}

static void cstack_free_Item(cstack_Item* nd) {
    free(nd);
}

static void _cstack_free(cstack_t st) {
    free(st);
}