#include <iostream>
#include "as_io.h"

using namespace std;

bool get_int(int& param)
{
    int value;
    cin >> value;
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail());
        return false;
    } else if (cin.peek() != '\n')
    {
        cin.ignore(cin.rdbuf()->in_avail());
        return false;
    }
    param = value;
    return true;
}
bool get_bool(bool& param)
{
    string value;
    cin >> value;
    if(value == "true" || value == "есть" || value == "+")
    {
        param = true;
        return true;
    } else if(value == "false" || value == "нет" || value == "нету" || value == "-")
    {
        param = false;
        return true;
    }
    return false;
}   
bool get_interface(input_interface& param)
{
    string interface;
    cin >> interface;
    for(int i = 0; i < interface.size(); i++)
        interface[i] = tolower(interface[i]);
        
    if(interface == "aux")
    {
        param = aux;
        return true;
    } else if(interface == "rca")
    {
        param = rca;
        return true;        
    } else if(interface == "optical" || interface == "opt")
    {
        param = optical;
        return true;        
    } else if(interface == "coaxial" || interface == "coax")
    {
        param = coaxial;
        return true;        
    } else if(interface == "bluetooth" || interface == "bt")
    {
        param = bluetooth;
        return true;        
    } else if(interface == "hdmi")
    {
        param = hdmi;
        return true;        
    }  else if(interface == "xlr")
    {
        param = xlr;
        return true;        
    }  
    return false;
}

void print_acoustic_system(const acoustic_system& as)
{
    cout << "Модель: " << as.model << endl;
    cout << "Производитель: " << as.manufacturer << endl;
    cout << "Мощность: " << as.power << endl;
    cout << "Минимальная частота: " << as.min_frequency << endl;
    cout << "Максимальная частота: " << as.max_frequency << endl;
    cout << "Количество полос: " << as.speakers_count << endl;
    cout << "Количество каналов: " << as.channels_count << endl;
    cout << "Сабвуфер: ";
    if(as.has_subwoofer)
        cout << "есть" << endl;
    else
        cout << "нет" << endl;
    
    cout << "Поддерживаемые интерфейсы:";
    for (int i = 0; i < as.interfaces_count; i++)
    {
        cout << ' ';
        switch(as.interfaces[i])
        {
        case aux:
            cout << "AUX";
            break;
        case rca:
            cout << "RCA";
            break;
        case optical:
            cout << "Optical";
            break;
        case coaxial:
            cout << "Coaxial";
            break;
        case bluetooth:
            cout << "Bluetooth";
            break;
        case hdmi:
            cout << "HDMI";
            break;
        case xlr:
            cout << "XLR";
            break;
        }
    }
    cout << endl;
}
void print_acoustic_system_table(stack& st)
{
    const size_t columns_count = 10;
    string name_columns[columns_count] = {"Номер", "Модель", "Производитель",
                                          "Мощность", "Мин. частота", "Макс. частота",
                                          "Кол-во полос", "Кол-во каналов", "Сабвуфер", "Интерфейсы"};
    size_t columns_size[columns_count] = {name_columns[0].size(), name_columns[1].size(),
                                          name_columns[2].size(), name_columns[3].size(),
                                          name_columns[4].size(), name_columns[5].size(),
                                          name_columns[6].size(), name_columns[7].size(),
                                          name_columns[8].size(), name_columns[9].size()};
    size_t offset = 4; //отступ между колонками
    
    if(to_string(stack_size(st)).size() > columns_size[0])
        columns_size[0] = to_string(stack_size(st)).size();

    for (size_t i = 0; i < stack_size(st); i++)
    {
        if(columns_size[1] < st[i].model.size())
            columns_size[1] = st[i].model.size();
        
        if(columns_size[2] < st[i].manufacturer.size())
            columns_size[2] = st[i].manufacturer.size();

        if(columns_size[3] < to_string(st[i].power).size())
            columns_size[3] = to_string(st[i].power).size();

        if(columns_size[4] < to_string(st[i].min_frequency).size())
            columns_size[4] = to_string(st[i].min_frequency).size();

        if(columns_size[5] < to_string(st[i].max_frequency).size())
            columns_size[5] = to_string(st[i].max_frequency).size();

        if(columns_size[6] < to_string(st[i].speakers_count).size())
            columns_size[6] = to_string(st[i].speakers_count).size();

        if(columns_size[7] < to_string(st[i].channels_count).size())
            columns_size[7] = to_string(st[i].channels_count).size();

        size_t interface_column_size = st[i].interfaces_count - 1; //as[i].interfaces_count - 1 : для пробелов между интерфейсами
        for (size_t j = 0; j < st[i].interfaces_count; j++)
        {
            switch(st[i].interfaces[j])
            {
            case aux:
                interface_column_size += 3; // 3 = "AUX" string size
                break;
            case rca:
                interface_column_size += 3; // 3 = "RCA" string size
                break;
            case optical:
                interface_column_size += 7; // 7 = "Optical" string size 
                break;
            case coaxial:
                interface_column_size += 7; // 7 = "Coaxial" string size 
                break;
            case bluetooth:
                interface_column_size += 9; // 9 = "Bluetooth" string size 
                break;
            case hdmi:
                interface_column_size += 4; // 4 = "HDMI" string size
                break;
            case xlr:
                interface_column_size += 3; // 3 = "XLR" string size
                break;
            }
        }
        
        if(columns_size[9] < interface_column_size)
            columns_size[9] = interface_column_size;
    }

    size_t table_width_size = columns_count + 1;// +1 : для символов | слева; + columns_count : для символа | после каждой колонки
    for(size_t i = 0; i < columns_count; i++)
    {
        columns_size[i] += offset;           //добавление отступа к каждой колонке
        table_width_size += columns_size[i]; //сумма длин всвех столбцов
    }
    size_t table_height_size = (stack_size(st) * 2) + 3;  // +3 : для cтроки с названием колонок и символов '-' сверху и снизу от неё; * 2 : для символов '-' под каждой строкой информации
    
    int as_number = 0;  
    for(size_t i = 0; i < table_height_size; i++)
    {
        if(i % 2 == 0)
        {
            for(size_t j = 0; j < table_width_size; j++)
                cout << '-';
            
            cout << endl;
            continue;
        } else if(i == 1)
        {
            for(size_t j = 0; j < columns_count; j++)
            {
                cout << '|' << name_columns[j];
                for(size_t k = name_columns[j].size(); k < columns_size[j]; k++)
                    cout << ' ';
            }
            cout << '|' << endl;
            continue;
        }
        
        cout << '|' << as_number + 1;
        for(size_t j = to_string(as_number + 1).size(); j < columns_size[0]; j++)
            cout << ' ';
        
        cout << '|' << st[as_number].model;
        for(size_t j = st[as_number].model.size(); j < columns_size[1]; j++)
            cout << ' ';
        
        cout << '|' << st[as_number].manufacturer;
        for(size_t j = st[as_number].manufacturer.size(); j < columns_size[2]; j++)
            cout << ' ';

        cout << '|' << st[as_number].power;
        for(size_t j = to_string(st[as_number].power).size(); j < columns_size[3]; j++)
            cout << ' ';

        cout << '|' << st[as_number].min_frequency;
        for(size_t j = to_string(st[as_number].min_frequency).size(); j < columns_size[4]; j++)
            cout << ' ';

        cout << '|' << st[as_number].max_frequency;
        for(size_t j = to_string(st[as_number].max_frequency).size(); j < columns_size[5]; j++)
            cout << ' ';

        cout << '|' << st[as_number].speakers_count;
        for(size_t j = to_string(st[as_number].speakers_count).size(); j < columns_size[6]; j++)
            cout << ' ';

        cout << '|' << st[as_number].channels_count;
        for(size_t j = to_string(st[as_number].channels_count).size(); j < columns_size[7]; j++)
            cout << ' ';
        
        if(st[as_number].has_subwoofer)
        {
            cout << "|есть";
            for(size_t j = 4; j < columns_size[8]; j++)
                cout << ' ';
        } else
        {
            cout << "|нет";
            for(size_t j = 3; j < columns_size[8]; j++)
                cout << ' ';
        }
        
        cout << '|';
        size_t column_intfc_size = 0;
        for(size_t j = 0; j < st[as_number].interfaces_count; j++)
        {
            switch(st[as_number].interfaces[j])
            {
            case aux:
                cout << "AUX";
                column_intfc_size += 3;
                break;
            case rca:
                cout << "RCA";
                column_intfc_size += 3;
                break;
            case optical:
                cout << "Optical";
                column_intfc_size += 7;
                break;
            case coaxial:
                cout << "Coaxial";
                column_intfc_size += 7;
                break;
            case bluetooth:
                cout << "Bluetooth";
                column_intfc_size += 9;
                break;
            case hdmi:
                cout << "HDMI";
                column_intfc_size += 4;
                break;
            case xlr:
                cout << "XLR";
                column_intfc_size += 3;
                break;
            }
            cout << ' ';
            column_intfc_size++;
        }
        for(size_t j = column_intfc_size; j < columns_size[9]; j++)
            cout << ' ';
        
        cout << '|' << endl;
        as_number++;
    }
}
void input_acoustic_system(acoustic_system& as)  
{
    cin.ignore(cin.rdbuf()->in_avail());
    bool error;
    
    cout << "Модель: ";
    do
    {
        getline(cin, as.model);
        if (as.model == "")
            error = true;
        else
        {
            error = false;
            for (size_t i = 0; i < as.model.size(); i++)
            {
                char c = as.model[i];
                if (!(c == 32 ||
                    c > 64 && c < 91 ||
                    c > 96 && c < 123 ||
                    c > -65 && c < 0 ||
                    c > 47 && c < 58))
                {
                    error = true;
                }
            }
        }

        if (error)
        {
            cout << endl << INPUT_ERROR_MESSAGE << endl
                << ">>>";
        }
    } while (error);
    
    cout << "Производитель: ";
    do
    {
        getline(cin, as.manufacturer);
        if (as.manufacturer == "")
            error = true;
        else
        {
            error = false;
            for (size_t i = 0; i < as.manufacturer.size(); i++)
            {
                char c = as.manufacturer[i];
                if (!(c == 32 ||
                    c > 64 && c < 91 ||
                    c > 96 && c < 123 ||
                    c > -65 && c < 0 ||
                    c > 47 && c < 58))
                {
                    error = true;
                }
            }
        }

        if (error)
        {
            cout << endl << INPUT_ERROR_MESSAGE << endl
                << ">>>";
        }
    } while (error);

    cout << "Мощность: ";
    do
    {
        error = !get_int(as.power);
        if (error) 
        {
            cout << endl << INPUT_ERROR_MESSAGE << endl
                 << ">>>";
        }
        else if (as.power < 1) 
        {
            error = true;
            cout << endl << INPUT_ERROR_MESSAGE << endl
                 << ">>>";
        }
    }while(error);

    cout << "Минимальная частота: ";
    do
    {
        error = !get_int(as.min_frequency);
        if (error) 
        {
            cout << endl << INPUT_ERROR_MESSAGE << endl
                 << ">>>";
        }
        else if (as.min_frequency < 1)
        {
            error = true;
            cout << endl << INPUT_ERROR_MESSAGE << endl
                 << ">>>";
        }
    }while(error);

    cout << "Максимальная частота: ";
    do
    {
        error = !get_int(as.max_frequency);
        if (error)
        {
            cout << endl << INPUT_ERROR_MESSAGE << endl
                 << ">>>";
        }
        else if (as.max_frequency < 1)
        {
            error = true;
            cout << endl << INPUT_ERROR_MESSAGE << endl
                 << ">>>";
        }
    }while(error);
    
    cout << "Количество полос: ";
    do
    {
        error = !get_int(as.speakers_count);
        if (error)
        {
            cout << endl << INPUT_ERROR_MESSAGE << endl
                 << ">>>";
        }
        else if (as.speakers_count < 1)
        {
            error = true;
            cout << endl << INPUT_ERROR_MESSAGE << endl
                 << ">>>";
        }
    }while(error);
    
    cout << "Количество каналов: ";
    do
    {
        error = !get_int(as.channels_count);
        if (error)
        {
            cout << endl << INPUT_ERROR_MESSAGE << endl
                 << ">>>";
        }
        else if (as.channels_count < 1)
        {
            error = true;
            cout << endl << INPUT_ERROR_MESSAGE << endl
                 << ">>>";
        }
    }while(error);
    
    cout << "Сабвуфер: ";
    do
    {
        error = !get_bool(as.has_subwoofer);
        if (error)
        {
            cout << endl << INPUT_ERROR_MESSAGE << endl
                 << ">>>";
        }
    }while(error);
    
    cout << "Поддерживаемые интерфейсы (XLR, AUX, RCA, Bluetooth, Optical, Coaxial через пробел): ";
    as.interfaces_count = 0;
    as.interfaces = NULL;
    do
    {
        do{
            input_interface intfc;
            error = !get_interface(intfc);
            if(error)
            {
                cout << endl << INPUT_ERROR_MESSAGE << endl
                     << ">>>";
                cin.ignore(cin.rdbuf()->in_avail());
                delete[] as.interfaces;
                as.interfaces = NULL;
                as.interfaces_count = 0;
                break;
            } else
            {
                for (size_t i = 0; i < as.interfaces_count; i++) {
                    if (as.interfaces[i] == intfc) {
                        error = true;
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                             << ">>>";
                        cin.ignore(cin.rdbuf()->in_avail());
                        delete[] as.interfaces;
                        as.interfaces = NULL;
                        as.interfaces_count = 0;
                        break;
                    }
                }
                if (error)
                    break;

                input_interface* temp = new input_interface[as.interfaces_count + 1];
                for (size_t i = 0; i < as.interfaces_count; i++)
                    temp[i] = as.interfaces[i];
                delete[] as.interfaces;

                temp[as.interfaces_count] = intfc;
                as.interfaces = temp;
                as.interfaces_count++;
            }
        }while (cin.peek() != '\n');
    }while(error);
}
