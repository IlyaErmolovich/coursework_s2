#include "as_finding.h"
#include "as_sorting.h"
#include <Windows.h>

stack find_model(const std::string& model, stack& st)
{
    size_t size = stack_size(st);
    stack finds;
    for (size_t i = 0; i < size; i++)
    {
        if (st[i].model == model)
            stack_push(finds, st[i]);
    }
    return finds;
}
stack find_manufacturer(const std::string& manufacturer, stack& st)
{
    size_t size = stack_size(st);
    stack finds;
    for (size_t i = 0; i < size; i++)
    {
        if (st[i].manufacturer == manufacturer)
            stack_push(finds, st[i]);
    }
    return finds;
}
stack find_power(const int power, stack& st)
{
    size_t size = stack_size(st);
    stack finds;
    for(size_t i = 0; i < size; i++)
    {
        if(st[i].power == power)
            stack_push(finds, st[i]);
    }
    return finds;
}
stack find_min_fr(const int min_fr, stack& st)
{
    size_t size = stack_size(st);
    stack finds;
    for(size_t i = 0; i < size; i++)
    {
        if(st[i].min_frequency == min_fr)
            stack_push(finds, st[i]);
    }
    return finds;
}
stack find_max_fr(const int max_fr, stack& st)
{
    size_t size = stack_size(st);
    stack finds;
    for(size_t i = 0; i < size; i++)
    {
        if(st[i].max_frequency == max_fr)
            stack_push(finds, st[i]);
    }
    return finds;
}
stack find_speakers_count(const int speakers_count, stack& st)
{
    size_t size = stack_size(st);
    stack finds;
    for(size_t i = 0; i < size; i++)
    {
        if(st[i].speakers_count == speakers_count)
            stack_push(finds, st[i]);
    }
    return finds;
}
stack find_channels_count(const int channels_count, stack& st)
{
    size_t size = stack_size(st);
    stack finds;
    for(size_t i = 0; i < size; i++)
    {
        if(st[i].channels_count == channels_count)
            stack_push(finds, st[i]);
    }
    return finds;
}
stack find_has_subwoofer(const bool has_subwoofer, stack& st) 
{
    size_t size = stack_size(st);
    stack finds;
    for (size_t i = 0; i < size; i++)
    {
        if (st[i].has_subwoofer == has_subwoofer)
            stack_push(finds, st[i]);
    }
    return finds;
}
stack find_interfaces(input_interface* interfaces, size_t interfaces_count, stack& st) 
{
    size_t size = stack_size(st);
    stack finds;
    for (size_t i = 0; i < size; i++)
    {
        int c = 0;
        for (size_t j = 0; j < st[i].interfaces_count; j++)
        {
            for (size_t k = 0; k < interfaces_count; k++)
            {
                if (st[i].interfaces[j] == interfaces[k])
                {
                    c++;
                    break;
                }
            }
            if (c == interfaces_count) {
                stack_push(finds, st[i]);
                break;
            }
        }
    }
    return finds;
}