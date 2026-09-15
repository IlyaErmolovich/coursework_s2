#include "as_sorting.h"
#include "as_io.h"
void model_sort(stack& st, const mode md)
{
    size_t size = stack_size(st);
    for (int i = 0; i < size - 1; i++) {
        int index = i;
        for (int j = i + 1; j < size; j++) {
            int min_size = st[j].model.size();
            if (st[index].model.size() < st[j].model.size())
                min_size = st[index].model.size();

            int k = 0;
            while ((k < min_size) && (st[j].model[k] == st[index].model[k]))
                k++;

            if ((md == increasing && st[j].model[k] < st[index].model[k]) ||
                (md == decreasing && st[j].model[k] > st[index].model[k])) {
                index = j;
            }
        }
        stack_type temporary = st[i];
        st[i] = st[index];
        st[index] = temporary;
    }
}
void manufacturer_sort(stack& st, const mode md)
{
    size_t size = stack_size(st);
    for (int i = 0; i < size - 1; i++) {
        int index = i;
        for (int j = i + 1; j < size; j++) {
            int min_size = st[j].manufacturer.size();
            if (st[index].manufacturer.size() < st[j].manufacturer.size())
                min_size = st[index].manufacturer.size();

            int k = 0;
            while ((k < min_size) && (st[j].manufacturer[k] == st[index].manufacturer[k]))
                k++;

            if ((md == increasing && st[j].manufacturer[k] < st[index].manufacturer[k]) ||
                (md == decreasing && st[j].manufacturer[k] > st[index].manufacturer[k])) {
                index = j;
            }
        }
        stack_type temporary = st[i];
        st[i] = st[index];
        st[index] = temporary;
    }
}
void power_sort(stack& st, const mode md) 
{
    size_t size = stack_size(st);
    for (int i = 0; i < size - 1; i++) {
        int index = i;
        for (int j = i + 1; j < size; j++) {
            if ((md == increasing && st[j].power < st[index].power) ||
                (md == decreasing && st[j].power > st[index].power)) {
                index = j;
            }
        }
        stack_type temporary = st[i];
        st[i] = st[index];
        st[index] = temporary;
    }
}
void min_fr_sort(stack& st, const mode md) 
{
    size_t size = stack_size(st);
    for (int i = 0; i < size - 1; i++) {
        int index = i;
        for (int j = i + 1; j < size; j++) {
            if ((md == increasing && st[j].min_frequency < st[index].min_frequency) ||
                (md == decreasing && st[j].min_frequency > st[index].min_frequency)) {
                index = j;
            }
        }
        stack_type temporary = st[i];
        st[i] = st[index];
        st[index] = temporary;
    }
}
void max_fr_sort(stack& st, const mode md) 
{
    size_t size = stack_size(st);
    for (int i = 0; i < size - 1; i++) {
        int index = i;
        for (int j = i + 1; j < size; j++) {
            if ((md == increasing && st[j].max_frequency < st[index].max_frequency) ||
                (md == decreasing && st[j].max_frequency > st[index].max_frequency)) {
                index = j;
            }
        }
        stack_type temporary = st[i];
        st[i] = st[index];
        st[index] = temporary;
    }
}
void speakers_sort(stack& st, const mode md) 
{
    size_t size = stack_size(st);
    for (int i = 0; i < size - 1; i++) {
        int index = i;
        for (int j = i + 1; j < size; j++) {
            if ((md == increasing && st[j].speakers_count < st[index].speakers_count) ||
                (md == decreasing && st[j].speakers_count > st[index].speakers_count)) {
                index = j;
            }
        }
        stack_type temporary = st[i];
        st[i] = st[index];
        st[index] = temporary;
    }
}
void channels_sort(stack& st, const mode md) 
{
    size_t size = stack_size(st);
    for (int i = 0; i < size - 1; i++) {
        int index = i;
        for (int j = i + 1; j < size; j++) {
            if ((md == increasing && st[j].channels_count < st[index].channels_count) ||
                (md == decreasing && st[j].channels_count > st[index].channels_count)) {
                index = j;
            }
        }
        stack_type temporary = st[i];
        st[i] = st[index];
        st[index] = temporary;
    }
}
void sabwoofer_sort(stack& st, const mode md) {
    size_t size = stack_size(st);
    for (int i = 0; i < size - 1; i++) {
        int index = i;
        for (int j = i + 1; j < size; j++) {
            if ((md == increasing && st[j].has_subwoofer == true && st[index].has_subwoofer == false) ||
                (md == decreasing && st[j].has_subwoofer == false && st[index].has_subwoofer == true)) {
                index = j;
            }
        }
        stack_type temporary = st[i];
        st[i] = st[index];
        st[index] = temporary;
    }
}