#pragma once
#include "stack.h"

enum mode
{
    increasing,
    decreasing
};

void model_sort(stack& st, const mode md);
void manufacturer_sort(stack& st, const mode md);
void power_sort(stack& st, const mode md);
void min_fr_sort(stack& st, const mode md);
void max_fr_sort(stack& st, const mode md);
void speakers_sort(stack& st, const mode md);
void channels_sort(stack& st, const mode md);
void sabwoofer_sort(stack& st, const mode md);
