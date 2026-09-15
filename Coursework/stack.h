#pragma once
#include "acoustic_system.h"

typedef acoustic_system stack_type;

struct node {
    stack_type value;
    node *next;
};
struct stack {
    node *head;
    stack();
    stack(const stack& st);
    stack_type& operator[](size_t index);
};

void stack_push(stack& st, const stack_type& value);
void stack_pop(stack& st, stack_type& out);
void stack_peek(const stack& st, stack_type& out);
void stack_print(stack& st);
size_t stack_size(stack& st);
void stack_clear(stack& st);
