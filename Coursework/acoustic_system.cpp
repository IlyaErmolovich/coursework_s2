#include "acoustic_system.h"

acoustic_system::acoustic_system()
{
    model = "";
    manufacturer = "";
    power = 0;
    min_frequency = 0;
    max_frequency = 0;
    speakers_count = 0;
    channels_count = 0;
    has_subwoofer = false;
    interfaces_count = 0;
    interfaces = NULL;
}
acoustic_system::acoustic_system(const acoustic_system& as)
{
    this->model = as.model;
    this->manufacturer = as.manufacturer;
    this->power = as.power;
    this->min_frequency = as.min_frequency;
    this->max_frequency = as.max_frequency;
    this->speakers_count = as.speakers_count;
    this->channels_count = as.channels_count;
    this->has_subwoofer = as.has_subwoofer;
    this->interfaces_count = as.interfaces_count;
    this->interfaces = new input_interface[interfaces_count];
    for (int i = 0; i < interfaces_count; i++)
        this->interfaces[i] = as.interfaces[i];

}
acoustic_system::~acoustic_system(){
    if(interfaces_count > 0)
        delete[] interfaces;
}
acoustic_system& acoustic_system::operator=(const acoustic_system& as)
{
    if (this->interfaces_count > 0)
        delete[] this->interfaces;

    this->model = as.model;
    this->manufacturer = as.manufacturer;
    this->power = as.power;
    this->min_frequency = as.min_frequency;
    this->max_frequency = as.max_frequency;
    this->speakers_count = as.speakers_count;
    this->channels_count = as.channels_count;
    this->has_subwoofer = as.has_subwoofer;
    this->interfaces_count = as.interfaces_count;
    this->interfaces = new input_interface[interfaces_count];
    for(int i = 0; i < interfaces_count; i++)
        this->interfaces[i] = as.interfaces[i];

    return *this;
}
bool acoustic_system::operator==(const acoustic_system& as)
{
    if(this->interfaces_count != as.interfaces_count)
        return false;

    for(size_t i = 0; i < interfaces_count; i++)
    {
        if(this->interfaces[i] != as.interfaces[i])
            return false;
    }

    return this->model == as.model &&
           this->manufacturer == as.manufacturer &&
           this->power == as.power &&
           this->min_frequency == as.min_frequency &&
           this->max_frequency == as.max_frequency &&
           this->speakers_count == as.speakers_count &&  
           this->channels_count == as.channels_count &&
           this->has_subwoofer == as.has_subwoofer;
}