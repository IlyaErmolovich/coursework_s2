#include <iostream>
#include <Windows.h>
#include "as_io.h"
#include "as_db.h"
#include "menu.h"
#include "as_finding.h"
#include "as_sorting.h"
#include "stack.h"

using namespace std;

bool get_approval()
{
    while(true)
    {
        string approval;
        std::cin >> approval;
        for(int i = 0; i < approval.size(); i++)
            approval[i] = tolower(approval[i]);
        
        if(approval == "да" || approval == "+")
            return true;
        else if(approval == "нет" || approval == "-")
            return false;
        else
        {
            cout << endl
                << INPUT_ERROR_MESSAGE << endl
                << ">>>";
        }
    }
}
void add_record(stack& st)
{
    system("cls");
    
    cout << "         Добавить запись?             " << endl
         << "            [Да]/[Нет]                " << endl
         << ">>>";

    if (!get_approval())
        return;

    cout << endl
         << "Введите данные: " << endl
         << endl;
    
    acoustic_system as;
    input_acoustic_system(as);
    stack_push(st, as);
    
    cout << endl
         << "Данные успешно записаны!" << endl
         << endl;

    system("pause");         
}
void print_record(stack& st)
{
    system("cls");
    
    if(stack_size(st) == 0)
        cout << "Данных нет!" << endl;
    else if(stack_size(st) == 1)
    {
        acoustic_system as;
        stack_peek(st, as);
        print_acoustic_system(as);
    }
    else
    {

        cout << "      Вывести запись на экран?        " << endl
             << "            [Да]/[Нет]                " << endl
             << ">>>";

        if (!get_approval())
            return;

        cout << endl
             << "Записей в памяти: " << stack_size(st) <<endl;
        int number;
        bool error;

        cout << "Выберите запись для вывода на экран: " << endl
            << ">>>";

        do
        {
            error = !get_int(number);
            if (error) {
                cout << endl << INPUT_ERROR_MESSAGE << endl
                     << ">>>";
                continue;
            }

            if (number <= 0 || number > stack_size(st))
            {
                cout << endl
                     << "Такой записи не существует! Введите номер повторно!" << endl
                     << ">>>";
                error = true;
            }
        } while (error);

        cout << endl;
  
        print_acoustic_system(st[number - 1]);
    }
    cout << endl;
    
    system("pause");
}
void print_all_records(stack& st)
{
    system("cls");
    
    if(stack_size(st) != 0)
        print_acoustic_system_table(st);
    else
        cout << "Данных нет!" << endl;

    cout << endl;

    system("pause");
}
void clear_records(stack& st)
{
    system("cls");
    
    if(stack_size(st) == 0)
    {
        cout << "Данных нет!" << endl
             << endl;
    } else
    {
        cout << "         Удалить все данные?          " << endl
             << "              [Да]/[Нет]              " << endl
             << ">>>";

        if (!get_approval())
            return;

        clear(st);
        cout << endl
             << "Все данные удалены!" << endl
             << endl;
    }
    system("pause");
}
void edit_record(stack& st) {
    system("cls");

    if (stack_size(st) == 0)
    {
        cout << "Данных нет!" << endl
            << endl;
    }
    else
    {
        cout << "       Редактировать запись?          " << endl
             << "            [Да]/[Нет]                " << endl
             << ">>>";

        if (!get_approval())
            return;

        cout << endl
             << "Записей в памяти: " << stack_size(st) << endl;
        int number;
        bool error;

        cout << "Выберите запись для редактирования: " << endl
            << ">>>";

        do
        {
            error = !get_int(number);
            if (error) {
                cout << endl << INPUT_ERROR_MESSAGE << endl
                    << ">>>";
                continue;
            }

            if (number <= 0 || number > stack_size(st))
            {
                cout << endl
                    << "Такой записи не существует! Введите номер повторно!" << endl
                    << ">>>";
                error = true;
            }
        } while (error);

        cout << endl
            << "Редактировать:                       " << endl
            << "Модель                          [1]   " << endl
            << "Производителя                   [2]   " << endl
            << "Мощность                        [3]   " << endl
            << "Мин. частоту                    [4]   " << endl
            << "Макс. частоту                   [5]   " << endl
            << "Кол-во полос                    [6]   " << endl
            << "Кол-во каналов                  [7]   " << endl
            << "Наличие сабвуфера               [8]   " << endl
            << "Поддерживаемые интерфейсы       [9]   " << endl
            << ">>>";

        int choice;
        do
        {
            do
            {
                error = !get_int(choice);
                if (error) {
                    cout << endl << INPUT_ERROR_MESSAGE << endl
                        << ">>>";
                }
            } while (error);

            switch (choice)
            {
            case 1:
            {
                cin.ignore(cin.rdbuf()->in_avail());
                cout << endl
                    << "Введите новое значение:" << endl
                    << ">>>";
                string model;
                bool err;
                do
                {
                    getline(cin, model);
                    if (model == "")
                        err = true;
                    else
                    {
                        err = false;
                        for (size_t i = 0; i < model.size(); i++)
                        {
                            char c = model[i];
                            if (!(c == 32 ||
                                c > 64 && c < 91 ||
                                c > 96 && c < 123 ||
                                c > -65 && c < 0 ||
                                c > 47 && c < 58))
                            {
                                err = true;
                            }
                        }
                    }

                    if (err)
                    {
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                            << ">>>";
                    }
                } while (err);
                st[number - 1].model = model;
            }
                break;
            case 2:
            {
                cin.ignore(cin.rdbuf()->in_avail());
                cout << endl
                    << "Введите новое значение:" << endl
                    << ">>>";
                string manufacturer;
                bool err;
                do
                {
                    getline(cin, manufacturer);
                    if (manufacturer == "")
                        err = true;
                    else
                    {
                        err = false;
                        for (size_t i = 0; i < manufacturer.size(); i++)
                        {
                            char c = manufacturer[i];
                            if (!(c == 32 ||
                                c > 64 && c < 91 ||
                                c > 96 && c < 123 ||
                                c > -65 && c < 0 ||
                                c > 47 && c < 58))
                            {
                                err = true;
                            }
                        }
                    }

                    if (err)
                    {
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                            << ">>>";
                    }
                } while (err);
                st[number - 1].manufacturer = manufacturer;
            }                
                break;
            case 3:
            {
                cout << endl
                    << "Введите новое значение:" << endl
                    << ">>>";
                int power;
                bool err;
                do
                {
                    err = !get_int(power);
                    if (err) {
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                            << ">>>";
                    }
                    else if (power < 1)
                    {
                        err = true;
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                            << ">>>";
                    }
                } while (err);
                st[number - 1].power = power;
            }                
                break;
            case 4:
            {
                cout << endl
                    << "Введите новое значение:" << endl
                    << ">>>";
                int min_fr;
                bool err;
                do
                {
                    err = !get_int(min_fr);
                    if (err) {
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                            << ">>>";
                    }
                    else if (min_fr < 1)
                    {
                        err = true;
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                            << ">>>";
                    }
                } while (err);
                st[number - 1].min_frequency = min_fr;
            }                
                break;
            case 5:
            {
                cout << endl
                    << "Введите новое значение:" << endl
                    << ">>>";
                int max_fr;
                bool err;
                do
                {
                    err = !get_int(max_fr);
                    if (err) {
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                            << ">>>";
                    }
                    else if (max_fr < 1)
                    {
                        err = true;
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                            << ">>>";
                    }
                } while (err);
                st[number - 1].max_frequency = max_fr;
            }
                break;
            case 6:
            {
                cout << endl
                    << "Введите новое значение:" << endl
                    << ">>>";
                int speakers_count;
                bool err;
                do
                {
                    err = !get_int(speakers_count);
                    if (err) {
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                            << ">>>";
                    }
                    else if (speakers_count < 1)
                    {
                        err = true;
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                            << ">>>";
                    }
                } while (err);
                st[number - 1].speakers_count = speakers_count;
            }
                break;
            case 7:
            {
                cout << endl
                    << "Введите новое значение:" << endl
                    << ">>>";
                int channels_count;
                bool err;
                do
                {
                    err = !get_int(channels_count);
                    if (err) {
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                            << ">>>";
                    }
                    else if (channels_count < 1)
                    {
                        err = true;
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                            << ">>>";
                    }
                } while (err);
                st[number - 1].channels_count = channels_count;
            }
                break;
            case 8:
            {
                cout << endl
                    << "Введите новое значение:" << endl
                    << ">>>";
                bool has_subwoofer;
                bool err;
                do
                {
                    err = !get_bool(has_subwoofer);
                    if (err) {
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                            << ">>>";
                    }
                } while (err);
                st[number - 1].has_subwoofer = has_subwoofer;
            }
                break;
            case 9:
            {
                cout << endl
                    << "Введите новое значение (XLR, AUX, RCA, Bluetooth, Optical, Coaxial через пробел):" << endl
                    << ">>>";

                int interfaces_count = 0;
                input_interface* interfaces = NULL;
                bool err;
                do
                {
                    do {
                        input_interface intfc;
                        error = !get_interface(intfc);
                        if (error)
                        {
                            cout << endl << INPUT_ERROR_MESSAGE << endl
                                << ">>>";
                            cin.ignore(cin.rdbuf()->in_avail());
                            delete[] interfaces;
                            interfaces = NULL;
                            interfaces_count = 0;
                            break;
                        }
                        else
                        {
                            for (size_t i = 0; i < interfaces_count; i++) {
                                if (interfaces[i] == intfc) {
                                    error = true;
                                    cout << endl << INPUT_ERROR_MESSAGE << endl
                                        << ">>>";
                                    cin.ignore(cin.rdbuf()->in_avail());
                                    delete[] interfaces;
                                    interfaces = NULL;
                                    interfaces_count = 0;
                                    break;
                                }
                            }
                            if (error)
                                break;

                            input_interface* temp = new input_interface[interfaces_count + 1];
                            for (size_t i = 0; i < interfaces_count; i++)
                                temp[i] = interfaces[i];
                            delete[] interfaces;

                            temp[interfaces_count] = intfc;
                            interfaces = temp;
                            interfaces_count++;
                        }
                    } while (cin.peek() != '\n');
                } while (error);
                delete[] st[number - 1].interfaces;
                st[number - 1].interfaces_count = interfaces_count;
                st[number - 1].interfaces = interfaces;
            }
                break;
            default:
                cout << endl << INPUT_ERROR_MESSAGE << endl
                     << ">>>";
                error = true;
                break;
            }
        } while (error);

        cout << endl
             << "Запись отредактирована!" << endl
             << endl;
    }

    system("pause");
}
void delete_record(stack& st) {
    system("cls");

    if (stack_size(st) == 0)
    {
        cout << "Данных нет!" << endl
            << endl;
    }
    else
    {
        cout << "          Удалить запись?             " << endl
             << "            [Да]/[Нет]                " << endl
             << ">>>";


        if (!get_approval())
            return;

        cout << endl
             << "Записей в памяти: " << stack_size(st) << endl;
        int number;
        bool error;

        cout << "Выберите запись для удаления: " << endl
             << ">>>";

        do
        {
            error = !get_int(number);
            if (error) {
                cout << endl << INPUT_ERROR_MESSAGE << endl
                    << ">>>";
                continue;
            }

            if (number <= 0 || number > stack_size(st))
            {
                cout << endl
                    << "Такой записи не существует! Введите номер повторно!" << endl
                    << ">>>";
                error = true;
            }
        } while (error);

        stack tmp_st;
        stack_type tmp;

        for (size_t i = 0; i < number - 1; i++)
        {
            stack_pop(st, tmp);
            stack_push(tmp_st, tmp);
        }
        stack_pop(st, tmp);
        while (tmp_st.head != NULL)
        {
            stack_pop(tmp_st, tmp);
            stack_push(st, tmp);
        }

        cout << endl
             << "Запись удалена!"
             << endl;
    }
    cout << endl;

    system("pause");
}
void create_file()
{
    system("cls");

    cout << "          Создать файл?               " << endl
         << "            [Да]/[Нет]                " << endl
         << ">>>";

    
    if (!get_approval())
        return;

    cout << endl
         << "Введите имя файла:" << endl
         << ">>>";

    string file_name;
    std::cin >> file_name;
    file_name += ".txt";

    if (file_exist(file_name))
    {
        cout << endl
             << "Файл с таким именем уже существует. Перезаписать его?" << endl
             << "                    [Да]/[Нет]                       " << endl
             << ">>>";

        if (!get_approval())
            return;
    }

    ofstream fout = new_db(file_name);
    if (fout.is_open())
    {
        cout << endl
             << "Файл успешно создан!" << endl
             << endl;
    }
    else
    {
        cout << endl
             << "Произошла ошибка при открытии файла!" << endl
             << endl;
    }

    fout.close();

    system("pause");
}
void remove_file()
{
    system("cls");
    
    cout << "          Удалить файл?               " << endl
         << "            [Да]/[Нет]                " << endl
         << ">>>";

    if (!get_approval())
        return;

    cout << endl
         << "Введите имя файла:" << endl
         << ">>>";

    string file_name;
    std::cin >> file_name;
    file_name += ".txt";

    if (file_exist(file_name))
    {
        if (remove_db(file_name)) 
        {
            cout << endl
                 << "Файл удалён!" << endl
                 << endl;
        }
        else
        {
            cout << endl 
                 << "Произошла ошибка при удалении файла!" << endl
                 << endl;
        }
    }
    else
    {
        cout << endl 
             << "Такого файла не существует!" << endl
             << endl;
    }

    system("pause");
}
void save_file(stack& st)
{
    system("cls");
    
    if(stack_size(st) == 0)
    {
        cout << "Данных нет!" << endl
             << endl;
    } 
    else
    {
        cout << "          Сохранить данные?           " << endl
             << "              [Да]/[Нет]              " << endl
             << ">>>";

        if (!get_approval())
            return;

        cout << endl
             << "Введите имя файла:" << endl
             << ">>>";

        string file_name;
        std::cin >> file_name;
        file_name += ".txt";

        if (!file_exist(file_name))
        {
            cout << endl
                 << "Такого файла не существует!" << endl
                 << endl;

            system("pause");
            return;
        }

        if (save_db(file_name, st)) {
            cout << endl
                 << "Данные успешно сохранены!" << endl
                 << endl;
        }
        else 
        {
            cout << endl
                 << "Произошла ошибка при сохранении!" << endl
                 << endl;
        }
    }

    system("pause");
}
void load_file(stack& st)
{
    system("cls");
    
    cout << "          Загрузить данные?           " << endl
         << "              [Да]/[Нет]              " << endl
         << ">>>";
            
    if (!get_approval())
        return;

    cout << endl
         << "Введите имя файла:" << endl
         << ">>>";

    string file_name;
    std::cin >> file_name;
    file_name += ".txt";

    if (!file_exist(file_name))
    {
        cout << endl
             << "Такого файла не существует!" << endl
             << endl;
    }
    else
    {
        if (load_db(file_name, st)) {
            cout << endl
                 << "Данные успешно загружены!" << endl
                 << endl;
        }
        else
        {
            cout << endl
                 << "Произошла ошибка при загрузке данных!" << endl
                 << endl;

            stack_clear(st);
        }
    }

    system("pause");
}
void sort(stack& st)
{
    system("cls");

    if (stack_size(st) == 0)
    {
        cout << endl
            << "Данных нет!" << endl
            << endl;
    }
    else
    {
        cout << "          Сортировать данные?         " << endl
            << "              [Да]/[Нет]              " << endl
            << ">>>";

        if (!get_approval())
            return;

        bool error;
        int choice;
        mode md;

        cout << endl
             << "Сортировать по:                       " << endl
             << "Возрастанию/алфавиту            [1]   " << endl
             << "Убыванию/против алфавита        [2]   " << endl
             << ">>>";

        do
        {
            do
            {
                error = !get_int(choice);
                if (error) {
                    cout << endl << INPUT_ERROR_MESSAGE << endl
                         << ">>>";
                }
            } while (error);
            
            switch (choice) {
            case 1:
                md = increasing;
                break;
            case 2:
                md = decreasing;
                break;
            default:
                cout << endl << INPUT_ERROR_MESSAGE << endl
                     << ">>>";
                error = true;
                break;
            }
        }while(error);
       
        cout << endl
            << "Сортировать по:                       " << endl
            << "Модели                          [1]   " << endl
            << "Производителю                   [2]   " << endl
            << "Мощности                        [3]   " << endl
            << "Мин. частоте                    [4]   " << endl
            << "Макс. частоте                   [5]   " << endl
            << "Кол-ву полос                    [6]   " << endl
            << "Кол-ву каналов                  [7]   " << endl
            << "Наличию сабвуфера               [8]   " << endl
            << ">>>";

        do
        {
            do
            {
                error = !get_int(choice);
                if (error) {
                    cout << endl << INPUT_ERROR_MESSAGE << endl
                         << ">>>";
                }
            } while (error);

            switch(choice)
            {
            case 1:
                model_sort(st, md);
                break;
            case 2:
                manufacturer_sort(st, md);
                break;
            case 3:
                power_sort(st, md);
                break;
            case 4:
                min_fr_sort(st, md);
                break;
            case 5:
                max_fr_sort(st, md);
                break;
            case 6:
                speakers_sort(st, md);
                break;
            case 7:
                channels_sort(st, md);
                break;
            case 8:
                sabwoofer_sort(st, md);
                break;
            default:
                cout << endl << INPUT_ERROR_MESSAGE << endl;
                error = true;
                break;
            }
        }while(error);

        cout << endl 
             << "Сортировка прошла успешно!" << endl 
             << endl;
    }

    system("pause");
}
void find(stack& st) {
    system("cls");

    if (stack_size(st) == 0)
    {
        cout << endl
             << "Данных нет!" << endl
             << endl;
    }
    else
    {
        cout << "             Найти данные?            " << endl
            << "              [Да]/[Нет]              " << endl
            << ">>>";

        if (!get_approval())
            return;

        int choice;
        bool error;
        stack result;

        cout << endl
             << "Поиск по:                       " << endl
             << "Модели                          [1]   " << endl
             << "Производителю                   [2]   " << endl
             << "Мощности                        [3]   " << endl
             << "Мин. частоте                    [4]   " << endl
             << "Макс. частоте                   [5]   " << endl
             << "Кол-ву полос                    [6]   " << endl
             << "Кол-ву каналов                  [7]   " << endl
             << "Наличию сабвуфера               [8]   " << endl
             << "Поддерживаемым интерфейсам      [9]   " << endl
             << ">>>";

        do {
            do
            {
                error = !get_int(choice);
                if (error) {
                    cout << endl << INPUT_ERROR_MESSAGE << endl
                         << ">>>";
                }
            } while (error);

            switch (choice)
            {
            case 1:
            {
                cin.ignore(cin.rdbuf()->in_avail());
                cout << endl
                     << "Введите значение для поиска:" << endl
                     << ">>>";
                stack temp(st);
                bool err;
                model_sort(temp, increasing);
                string model;
                do
                {
                    getline(cin, model);
                    if (model == "")
                        err = true;
                    else
                    {
                        err = false;
                        for (size_t i = 0; i < model.size(); i++)
                        {
                            char c = model[i];
                            if (!(c == 32 ||
                                c > 64 && c < 91 ||
                                c > 96 && c < 123 ||
                                c > -65 && c < 0 ||
                                c > 47 && c < 58))
                            {
                                err = true;
                            }
                        }
                    }

                    if (err)
                    {
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                             << ">>>";
                    }
                } while (err);
                result = find_model(model, temp);
            }
            break;
            case 2:
            {
                cin.ignore(cin.rdbuf()->in_avail());
                cout << endl
                     << "Введите значение для поиска:" << endl
                     << ">>>";
                stack temp(st);
                bool err;
                manufacturer_sort(temp, increasing);
                string manufacturer;
                do
                {
                    getline(cin, manufacturer);
                    if (manufacturer == "")
                        err = true;
                    else
                    {
                        err = false;
                        for (size_t i = 0; i < manufacturer.size(); i++)
                        {
                            char c = manufacturer[i];
                            if (!(c == 32 ||
                                c > 64 && c < 91 ||
                                c > 96 && c < 123 ||
                                c > -65 && c < 0 ||
                                c > 47 && c < 58))
                            {
                                err = true;
                            }
                        }
                    }

                    if (err)
                    {
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                             << ">>>";
                    }
                } while (err);
                result = find_manufacturer(manufacturer, temp);
            }
            break;
            case 3:
            {
                cout << endl
                     << "Введите значение для поиска:" << endl
                     << ">>>";
                int power;
                bool err;
                do
                {
                    err = !get_int(power);
                    if (err) {
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                             << ">>>";
                    }
                    else if (power < 1)
                    {
                        err = true;
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                             << ">>>";
                    }
                } while (err);
                result = find_power(power, st);
            }
            break;
            case 4:
            {
                cout << endl
                     << "Введите значение для поиска:" << endl
                     << ">>>";
                int min_fr;
                bool err;
                do
                {
                    err = !get_int(min_fr);
                    if (err) {
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                             << ">>>";
                    }
                    else if (min_fr < 1)
                    {
                        err = true;
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                             << ">>>";
                    }
                } while (err);
                result = find_min_fr(min_fr, st);
            }
            break;
            case 5:
            {
                cout << endl
                     << "Введите значение для поиска:" << endl
                     << ">>>";
                int max_fr;
                bool err;
                do
                {
                    err = !get_int(max_fr);
                    if (err) {
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                             << ">>>";
                    }
                    else if (max_fr < 1)
                    {
                        err = true;
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                             << ">>>";
                    }
                } while (err);
                result = find_max_fr(max_fr, st);
            }
            break;
            case 6:
            {
                cout << endl
                     << "Введите значение для поиска:" << endl
                     << ">>>";
                int speakers_count;
                bool err;
                do
                {
                    err = !get_int(speakers_count);
                    if (err) {
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                             << ">>>";
                    }
                    else if (speakers_count < 1)
                    {
                        err = true;
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                             << ">>>";
                    }
                } while (err);
                result = find_speakers_count(speakers_count, st);
            }
            break;
            case 7:
            {
                cout << endl
                     << "Введите значение для поиска:" << endl
                     << ">>>";
                int channels_count;
                bool err;
                do
                {
                    err = !get_int(channels_count);
                    if (err) {
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                             << ">>>";
                    }
                    else if (channels_count < 1)
                    {
                        err = true;
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                             << ">>>";
                    }
                } while (err);
                result = find_channels_count(channels_count, st);
            }
            break;
            case 8:
            {
                cout << endl
                    << "Введите значение для поиска:" << endl
                    << ">>>";
                bool has_subwoofer;
                bool err;
                do
                {
                    err = !get_bool(has_subwoofer);
                    if (err) {
                        cout << endl << INPUT_ERROR_MESSAGE << endl
                            << ">>>";
                    }
                } while (err);
                result = find_has_subwoofer(has_subwoofer, st);
            }
                break;
            case 9:
            {
                cout << endl
                    << "Введите значение для поиска (XLR, AUX, RCA, Bluetooth, Optical, Coaxial через пробел):" << endl
                    << ">>>";

                int interfaces_count = 0;
                input_interface* interfaces = NULL;
                bool err;
                do
                {
                    do {
                        input_interface intfc;
                        err = !get_interface(intfc);
                        if (err)
                        {
                            cout << endl << INPUT_ERROR_MESSAGE << endl
                                << ">>>";
                            cin.ignore(cin.rdbuf()->in_avail());
                            delete[] interfaces;
                            interfaces = NULL;
                            interfaces_count = 0;
                            break;
                        }
                        else
                        {
                            for (size_t i = 0; i < interfaces_count; i++) {
                                if (interfaces[i] == intfc) {
                                    err = true;
                                    cout << endl << INPUT_ERROR_MESSAGE << endl
                                        << ">>>";
                                    cin.ignore(cin.rdbuf()->in_avail());
                                    delete[] interfaces;
                                    interfaces = NULL;
                                    interfaces_count = 0;
                                    break;
                                }
                            }
                            if (err)
                                break;

                            input_interface* temp = new input_interface[interfaces_count + 1];
                            for (size_t i = 0; i < interfaces_count; i++)
                                temp[i] = interfaces[i];
                            delete[] interfaces;

                            temp[interfaces_count] = intfc;
                            interfaces = temp;
                            interfaces_count++;
                        }
                    } while (cin.peek() != '\n');
                } while (err);
                result = find_interfaces(interfaces, interfaces_count, st);
            }
                break;
            default:
                cout << endl << INPUT_ERROR_MESSAGE << endl
                     << ">>>";
                error = true;
                break;
            }
        } while (error);

        if (stack_size(result) == 0) {
            cout << endl
                << "Данные не найдены!" << endl
                << endl;
        }
        else
        {
            cout << endl 
                 << "Найденные данные: " << endl;
            stack_print(result);
        }
    }

    system("pause");
}

void menu()
{
    stack st;
    while (true)
    {
        system("cls");

        cout << "                Меню                 |" << endl
            << "                                     |" << endl
            << "-------------------------------------|" << endl
            << "           РАБОТА С ДАННЫМИ          |" << endl
            << "Ввод данных                     [1]  |" << endl
            << "Вывод данных                    [2]  |" << endl
            << "Вывод данных в виде таблицы     [3]  |" << endl
            << "Редактирование данных на выбор  [4]  |" << endl
            << "Удаление данных на выбор        [5]  |" << endl
            << "Полная очистка данных           [6]  |" << endl
            << "Сортировка                      [7]  |" << endl
            << "Поиск                           [8]  |" << endl
            << "-------------------------------------|" << endl
            << "           РАБОТА С ФАЙЛАМИ          |" << endl
            << "Создание файла                  [9]  |" << endl
            << "Удаление файла                  [10] |" << endl
            << "Сохранение данных в файл        [11] |" << endl
            << "Загрузка данных из файла        [12] |" << endl
            << "                                     |" << endl
            << "             ВЫХОД [0]               |" << endl
            << "                                     |" << endl
            << "-------------------------------------|" << endl
            << "                                      " << endl
            << ">>>";

        bool error;

        do
        {
            int choice;
            error = false;
            bool err;
            do
            {
                err = !get_int(choice);
                if (err) {
                    cout << endl << INPUT_ERROR_MESSAGE << endl
                        << ">>>";
                }
            } while (err);

            switch (choice)
            {
            case 1:
                add_record(st);
                break;
            case 2:
                print_record(st);
                break;
            case 3:
                print_all_records(st);
                break;
            case 4:
                edit_record(st);
                break;
            case 5:
                delete_record(st);
                break;
            case 6:
                clear_records(st);
                break;
            case 7:
                sort(st);
                break;
            case 8:
                find(st);
                break;
            case 9:
                create_file();
                break;
            case 10:
                remove_file();
                break;
            case 11:
                save_file(st);
                break;
            case 12:
                load_file(st);
                break;
            case 0:
                exit(0);
                break;
            default:
                cout << endl << INPUT_ERROR_MESSAGE << endl
                     << ">>>";
                error = true;
                break;
            }
        } while (error);
    }
}