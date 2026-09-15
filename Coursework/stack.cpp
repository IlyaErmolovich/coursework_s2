#include <iostream>
#include "stack.h"
#include "as_io.h"

using namespace  std;

stack::stack()  
{
    head = NULL;
}
stack::stack(const stack& st)
{
    head = NULL;
    stack temp_st;
    node* temp_nd = st.head;
    while(temp_nd != NULL)
    {
        stack_push(temp_st, temp_nd->value);
        temp_nd = temp_nd->next;
    }
    while(temp_st.head != NULL)
    {
        stack_type tmp;
        stack_pop(temp_st, tmp);
        stack_push(*this, tmp);
    }
}
void stack_push(stack& st, const stack_type& value)
{
    node* nd = new node();
    nd->next = st.head;
    nd->value = value;
    st.head = nd;
}
void stack_pop(stack& st, stack_type& out)
{
    if(st.head == NULL)
        return;
    
    node* nd = st.head;
    st.head = st.head->next;

    out = nd->value;
    delete nd;
}
void stack_peek(const stack& st, stack_type& out)
{
    if(st.head == NULL)
        return;
    
    out = st.head->value;
}
void stack_print(stack& st)
{
    stack tmp_stack;
    stack_type tmp;
    while(st.head != NULL)
    {
        stack_pop(st, tmp);
        print_acoustic_system(tmp);
        cout << endl;
        stack_push(tmp_stack, tmp);
    }
    while(tmp_stack.head != NULL)
    {
        stack_pop(tmp_stack, tmp);
        stack_push(st, tmp);
    }
}
size_t stack_size(stack& st)
{
    if(st.head == NULL)
        return 0;

    stack tmp_stack;
    stack_type tmp;
    size_t size = 0;
    while(st.head != NULL)
    {
        stack_pop(st, tmp);
        size++;
        stack_push(tmp_stack, tmp);
    }
    while(tmp_stack.head != NULL)
    {
        stack_pop(tmp_stack, tmp);
        stack_push(st, tmp);
    }
    return size;
}
void stack_clear(stack& st)
{
    stack_type tmp;
    while(st.head != NULL)
        stack_pop(st, tmp);
}
stack_type& stack::operator[](const size_t index)
{
    node* temp = head;
    
    for(size_t i = 0; i < index && temp != NULL; i++)
    {
        temp = temp->next;
    }
    return temp->value;
}

/*stack_type& stack::operator[](const size_t index)
{
    stack tmp_st;
    stack_type tmp;
    stack_type* result = NULL;
    
    for(size_t i = 0; i < index; i++)
    {
        stack_pop(*this, tmp);
        stack_push(tmp_st, tmp);
    }
    result = &(this->head->value);
    while(tmp_st.head != NULL)
    {
        stack_pop(tmp_st, tmp);
        stack_push(*this, tmp);
    }
    return *result;
}*/