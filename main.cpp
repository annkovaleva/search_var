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


void remove_line_comments(string arr_text[], int len_text) {

    //! Для каждой строчки текста
    for (int i = 0; i < len_text; i++) {

        //! Искать позицию специального символа начала комментария
        int position = arr_text[i].find("//");

        //! Если символ найден, то
        if (position != -1) {

            //! Удалить всё, начиная со специального символа до конца строки
            arr_text[i].erase(position);
        }
    }
}

void remove_char_from_str(string &str, string rem_str) {

    int position = 0;                                                                                              //! Индекс позиции

    //! Пока позиция символа может быть найдена
    while (position != -1) {

        //! Искать позицию символа в строке
        position = str.find(rem_str);

        //! Если нашли позицию, то
        if (position != -1) {

            //! Удалить символ
            str.erase(position, 1);
        }
    }
}

void remove_word_from_str(string &str, string rem_str) {

    str.insert(0, ";");
    int position = 0;                                                                                              //! Индекс позиции
    int len = rem_str.length();                                                                                    //! Длина слова

    //! Пока позиция может быть найдена
    while (position != -1) {

        //! Искать позицию начала слова в строке
        position = str.find(rem_str, position+1);

        //! Если нашли позицию и проверили, что это не часть слова, то
        if (position != -1 && !isalnum(str[position + len]) && !isalnum(str[position - 1]) && str[position + len]!='_' && str[position - 1]!='_') {

            //! Удалить слово
            str.erase(position, len);
        }
    }

    str.erase(0,1);
}

