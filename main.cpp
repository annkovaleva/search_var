#include <QCoreApplication>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <regex>
#include <QRegExp>
#include "header.h"

int main(int argc, char *argv[])
{
    return 0;
}

void data_output(string file_name, int names_index[], int len_names) {

    ofstream file(file_name);                                                                                     //! Объект, который помогает записывать в файл
    ofstream out;                                                                                                  //! Поток для записи

    //! Открыть файл для записи
    out.open(file_name);

    //! Если файл открылся, то
    if (out.is_open())
    {
        for (int w = 0; w < len_names; w++) {

            //! Если флаг true, то
            if (names_index[w] == 1) {

                //! Записать в файл, что переменная найдена
                out << "True" << endl;
            }

            //! Иначе
            else {

                //! Записать в файл, что переменная не найдена
                out << "False" << endl;
            }
        }

        //! Закрыть файл
        file.close();
    }
    else {

        //! Вывести ошибку №5
        throw 5;
    }

}

int data_input(char name_file[], string arr_text[], int index_erorr) {

    ifstream file(name_file);                                                                                     //! Объект, который помогает читать файл
    int len_text = 0;                                                                                              //! Количество строк в тексте функции

    //! Если файл открылся, то
    if (file.is_open())
    {
        //! Пока не кончился файл записать каждую строчку в массив
        while (getline(file, arr_text[len_text])) {

            //! Инкрементировать длину массива строк
            len_text++;
        }
        //! Закрыть файл
        file.close();

        //! Возвратить длину массива строк
        return len_text;
    }
    //! Иначе, если мы читаем файл с именами переменных, то
    else if (index_erorr==1) {

        //! Вывести ошибку №6
        throw 6;
    }
    //! Иначе
    else {

        //! Вывести ошибку №4
        throw 4;
    }
    return 0;
}
