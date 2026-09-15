#pragma once
#include "acoustic_system.h"
#include "stack.h"

#define INPUT_ERROR_MESSAGE "ќшибка ввода! ¬ведите значение заново!"

bool get_int(int& param);
bool get_bool(bool& param);
bool get_interface(input_interface& param);

void print_acoustic_system(const acoustic_system& as);
void print_acoustic_system_table(stack& st);
void input_acoustic_system(acoustic_system& as);