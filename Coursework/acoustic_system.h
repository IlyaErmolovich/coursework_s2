#pragma once
#include <string>

enum input_interface
{
    aux,
    rca,
    optical,
    coaxial,
    bluetooth,
    hdmi,
    xlr
};

struct acoustic_system
{
    std::string model;
    std::string manufacturer;
    int power;
    int min_frequency;
    int max_frequency;
    int speakers_count;
    int channels_count;
    bool has_subwoofer;
    size_t interfaces_count;
    input_interface* interfaces;

    acoustic_system();
    acoustic_system(const acoustic_system& as);
    ~acoustic_system();
    acoustic_system& operator=(const acoustic_system& as);
    bool operator== (const acoustic_system& as);
};