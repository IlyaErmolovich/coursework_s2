#pragma once
#include "stack.h"

stack find_model(const std::string& model, stack& st);
stack find_manufacturer(const std::string& manufacturer, stack& st);
stack find_power(const int power, stack& st);
stack find_min_fr(const int min_fr, stack& st);
stack find_max_fr(const int max_fr, stack& st);
stack find_speakers_count(const int speakers_count, stack& st);
stack find_channels_count(const int channels_count, stack& st);
stack find_has_subwoofer(const bool has_subwoofer, stack& st);
stack find_interfaces(input_interface* interfaces, size_t interfaces_count, stack& st);