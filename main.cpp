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
