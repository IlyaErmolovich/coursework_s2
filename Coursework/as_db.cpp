#include <iostream>
#include "as_db.h"

using namespace std;

bool string_to_int(const string& str, int& param)
{
    for(int i = 0; i < str.size(); i++)
    {
        if(str[i] < '0' || str[i] > '9')
            return false;
    }

    param = stoi(str);
    return true;
}
bool file_exist(const string& file_path)
{
    ifstream fin(file_path);
    bool is_exist = fin.is_open();
    fin.close();
    return is_exist;
}

std::ofstream new_db(const string& file_path)
{
    return ofstream(file_path, ios_base::out | ios_base::trunc);  
}
bool remove_db(const std::string& file_path)
{
    return !remove(file_path.c_str());
}
void clear(stack& st)
{
    stack_clear(st);
}
bool save_db(const std::string& file_path, stack& st)
{
    ofstream fout(file_path, ios_base::out|ios_base::trunc);
    if(!fout.is_open())
        return false;

    for(int i = stack_size(st) - 1; i >= 0; i--)
    {
        fout << "Модель: " << st[i].model << endl;
        fout << "Производитель: " << st[i].manufacturer << endl;
        fout << "Мощность: " << st[i].power << endl;
        fout << "Минимальная частота: " << st[i].min_frequency << endl;
        fout << "Максимальная частота: " << st[i].max_frequency << endl;
        fout << "Количество полос: " << st[i].speakers_count << endl;
        fout << "Количество каналов: " << st[i].channels_count << endl;
        fout << "Сабвуфер: ";
        if (st[i].has_subwoofer)
            fout << "есть" << endl;
        else
            fout << "нет" << endl;

        fout << "Поддерживаемые интерфейсы:";
        for (int j = 0; j < st[i].interfaces_count; j++)
        {
            fout << ' ';
            switch (st[i].interfaces[j])
            {
            case aux:
                fout << "AUX";
                break;
            case rca:
                fout << "RCA";
                break;
            case optical:
                fout << "Optical";
                break;
            case coaxial:
                fout << "Coaxial";
                break;
            case bluetooth:
                fout << "Bluetooth";
                break;
            case hdmi:
                fout << "HDMI";
                break;
            case xlr:
                fout << "XLR";
                break;
            }
        }
        fout << endl << endl;
    }
    
    fout.close();
    return true;
}
bool load_db(const std::string& file_path, stack& st)
{
    ifstream fin(file_path, ios_base::in);
    if(!fin.is_open())
        return false;

    while(true)
    {
        string line;
        getline(fin, line);

        if(line == "")
            break;      //конец списка в файле

        acoustic_system as;
        
        size_t index = line.find(':') + 2; //+2 для пропуска ": " в файле и перехода сразу к подстроке
        if(index != std::string::npos)
            as.model = line.substr(index);
        else
            return false;

        getline(fin, line);
        index = line.find(':') + 2;
        if(index != std::string::npos)
            as.manufacturer = line.substr(index);
        else
            return false;

        getline(fin, line);
        index = line.find(':') + 2;
        if(index != std::string::npos)
        {
            if(!string_to_int(line.substr(index), as.power))
                return false;
        } else
            return false;
        
        getline(fin, line);
        index = line.find(':') + 2;
        if(index != std::string::npos)
        {
            if(!string_to_int(line.substr(index), as.min_frequency))
                return false;
        } else
            return false;

        getline(fin, line);
        index = line.find(':') + 2;
        if(index != std::string::npos)
        {
            if(!string_to_int(line.substr(index), as.max_frequency))
                return false;
        } else
            return false;

        getline(fin, line);
        index = line.find(':') + 2;
        if(index != std::string::npos)
        {
            if(!string_to_int(line.substr(index), as.speakers_count))
                return false;
        } else
            return false;

        getline(fin, line);
        index = line.find(':') + 2;
        if(index != std::string::npos)
        {
            if(!string_to_int(line.substr(index), as.channels_count))
                return false;
        } else
            return false;

        getline(fin, line);
        index = line.find(':') + 2;
        if(index != std::string::npos)
        {
            if(line.substr(index) == "есть")
                as.has_subwoofer = true;
            else if(line.substr(index) == "нет")
                as.has_subwoofer = false;
            else
                return false;
        }  else
            return false;
        
        getline(fin, line);
        index = line.find(':') + 1;
        do
        {
            string s = line.substr(index + 1,  line.find(' ', index + 1) - (index + 1));
            index = line.find(' ', index  + 1);
            input_interface intfc;
            if(s == "AUX")
            {
                intfc = aux;
            } else if(s == "RCA")
            {
                intfc = rca;
            } else if(s == "Optical")
            {
                intfc = optical;
            } else if(s == "Coaxial")
            {
                intfc = coaxial;
            } else if(s == "Bluetooth")
            {
                intfc = bluetooth;
            } else if(s == "HDMI")
            {
                intfc = hdmi;
            }  else if(s == "XLR")
            {
                intfc = xlr;
            } else
                return false;

             input_interface* temp = new input_interface[as.interfaces_count + 1];
                for (size_t i = 0; i < as.interfaces_count; i++)
                    temp[i] = as.interfaces[i];
                delete[] as.interfaces;
                
                temp[as.interfaces_count] = intfc;
                as.interfaces = temp;
                as.interfaces_count++;
        }while(index != std::string::npos);
        getline(fin, line);
        
        stack_push(st, as);
    }
    
    fin.close();
    return true;
}