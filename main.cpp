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

    //!Блок ловли ошибок
    try {

        string names[100];                                                                                         //! Массив строк с именами переменных
        int names_index[100];                                                                                      //! Массив с индикаторами объявления переменных

        /*! Регулярное выражение для проверки расширения файла с названиями переменных и выходного файла
         *  \code
         *  regex regular_for_names(".+(\\.txt)$")
         *  \endcode
        */
        regex regular_for_names_and_result(".+(\\.txt)$");

        //! Если последняя часть строки названия файла с переменными не подошла под шаблон, то
        cmatch result1;
        if (!regex_search(argv[1], result1, regular_for_names_and_result))
        {
            //! Вывести ошибку №1
            throw 1;
        }

        //! Для каждого названия файлов с текстом функции
        int count_for_arr = 2;                                                                                 //! Счетчик для массива с названиями файлов

        /*! Регулярное выражение для проверки расширения файлов с текстом программы
         *  \code
         *  regex regular_name_next(".+(\\.(txt||h||cpp))$")
         *  \endcode
        */
        regex regular_name_next(".+(\\.(txt||h||cpp))$");
        for (int i = 0; i < (argc - 3); i++) {

            //! Если последняя часть строки названия не подошла под шаблон, то
            cmatch result2;
            if (!regex_search(argv[count_for_arr ], result2, regular_name_next))
            {
                //! Вывести ошибку №2
               throw 2;
            }

            //! Инкрементировать счетчик для массива
            count_for_arr ++;
        }

        //! Если последняя часть строки названия выходного файла не подошла под шаблон, то
        cmatch result3;
        if (!regex_search(argv[argc-1], result3, regular_for_names_and_result))
        {
            //! Вывести ошибку №3
            throw 3;
        }

        //! Поместить названия переменных из файла в массив строк
        int len_names = data_input(argv[1], names, 1);

        //! Проверить корректность названий переменных
        for (int i = 0; i < len_names; i++) {

            int count_indexes = 0;                                                                                             //! Счетчик индекса символов в слове

            //! Пока слово не закончилось
            while (names[i][count_indexes] != '\0') {

                //! Если текущий символ запрещенный символ в названиях переменных, то
                if (!isalnum(names[i][count_indexes]) && names[i][count_indexes] != '_') {

                    //! Вывести ошибку, добавив в неё неопределенный символ
                    cout << "An invalid character was found \"" << names[i][count_indexes] << "\" in a file with variable names." << endl;
                    return 0;
                }

                // Инкрементировать счетчик символов в слове
                count_indexes++;
            }
        }

        //! Заполнить массив с индикаторами отрицательными ответами
        for (int i = 0; i < len_names; i++) {
            names_index[i] = 0;
        }

        //! Для каждого файла с текстом функции искать объявление переменных
        for (int j = 2; j < (argc-1); j++) {

            string text_func[10000];                                                                               //! Массив строк с текстом функции
            string str_with_text;                                                                                  //! Строка со всем слепленным текстом функции

            //! Поместить текст из файла в массив
            int len_text = data_input(argv[j], text_func, 2);

            //! Удалить однострочные комментарии
            remove_line_comments(text_func, len_text);

            //! Поместить текст функции в одну строку
            for (int i = 0; i < len_text; i++) {
                str_with_text.append(text_func[i]);
            }

            //! Удалить *
            remove_char_from_str(str_with_text, "*");

            //! Удалить const
            remove_word_from_str(str_with_text, "const");

            //! Добавить в начале текста символ для работы без вылетов
            str_with_text.insert(0, ";");

            //! Удалить все ненужные пробелы
            remove_spaces(str_with_text);

            //! Проверка всех переменных на объявление во всех файлах
            dump_regex(str_with_text, len_names, names_index, names);
        }

        //! Запись результата поиска в файл
        data_output(argv[argc-1], names_index, len_names);

    } catch (int trouble) {

        switch (trouble) {
        case 1: cout << "Invalid input file extension. The file must have a .txt extension." << endl;
            break;
        case 2: cout << "Invalid input file extension. The file must have the extension .txt, .cpp, .h." << endl;
            break;
        case 3: cout << "The extension of the output file is incorrect. The file must have a .txt extension." << endl;
            break;
        case 4: cout << "The file with the input data containing the text of the program is incorrectly specified. The file may not exist." << endl;
            break;
        case 5: cout << "Invalid output file specified. The file may not exist." << endl;
            break;
        case 6: cout << "Incorrectly specified input file with variable names. The file may not exist." << endl;
            break;
        }

        return 0;
    }

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

void remove_spaces(string& str) {

    int count_char = 1;                                                                                                     //! Счётчик символов в строке

    //! Пока не дошли до конца строки
    while (str[count_char] != '\0') {

        //! Если текущий символ пробел, а перед ним и после него не буквы, то
        if ((   (str[count_char] == ' ' || str[count_char] == '\t') && !isalnum(str[count_char - 1]) &&  isalnum(str[count_char + 1]) && str[count_char - 1] != '_' && str[count_char + 1] != '_')
            || ((str[count_char] == ' ' || str[count_char] == '\t') &&  isalnum(str[count_char - 1]) && !isalnum(str[count_char + 1]) && str[count_char - 1] != '_' && str[count_char + 1] != '_')
            || ((str[count_char] == ' ' || str[count_char] == '\t') && !isalnum(str[count_char - 1]) && !isalnum(str[count_char + 1]) && str[count_char - 1] != '_' && str[count_char + 1] != '_') ) {

            //! Удалить текущий символ
            str.erase(count_char, 1);
        }

        //! Иначе
        else
        {
            //! Инкрементировать счетчик символов
            count_char++;
        }
    }
}

void dump_regex(string& str_with_text, int len_names, int names_index[], string names[]) {

    QString str = QString::fromUtf8(str_with_text.c_str());

    //! Для каждой переменной искать её объявление
    for (int l = 0; l < len_names; l++) {

        /*! Генерирование регулярного выражения для поиска объявления переменных базовых типов
         *  \code
         *  string regul1 = "(int|char|float|double|short|long|unsigned|signed)[^;^(]*[\\s,](";
         *  string regul2 = ")[^A-Z^a-z^0-9^_^(]";
         *  regul1 = regul1 + names[l] + regul2;
         *  \endcode
         */
        string regul_bas_1 = "(int|char|float|double|short|long|unsigned|signed)[^;^(]*[\\s,](";
        string regul_bas_2 = ")[^A-Z^a-z^0-9^_^(]";
        regul_bas_1 = regul_bas_1 + names[l] + regul_bas_2;
        QString regul_bas_3 = QString::fromUtf8(regul_bas_1.c_str());
        QRegExp regul_basic(regul_bas_3);

        //! Поиск объявления переменной базового типа в строке с помощью шаблона
        int pos_basic = regul_basic.indexIn(str);
        QStringList list_basic = regul_basic.capturedTexts();

        //! Если позиция найдена, то
        if(pos_basic!=-1) {

            //! Считаем, что переменная найдена
            names_index[l]=1;
        }

        /*! Генерирование регулярного выражения для поиска объявления переменной пользовательских типов данных
         *  \code
         *  string regul4 = "(\\w+)[^;^(]*[\\s,](";
         *  string regul5 = ")[^A-Z^a-z^0-9^_^(]";
         *  regul4 = regul4 + names[l] + regul5;
         *  \endcode
         */
        string regul_custom_1 = "(\\w+)[^;^(]*[\\s,](";
        string regulregul_custom_2 = ")[^A-Z^a-z^0-9^_^(]";
        regul_custom_1 = regul_custom_1 + names[l] + regulregul_custom_2;
        QString regul_custom_3 = QString::fromUtf8(regul_custom_1.c_str());
        QRegExp regul_custom(regul_custom_3);

        //! Поиск объявления переменной пользовательского типа в строке с помощью шаблона
        int pos_custom = regul_custom.indexIn(str);
        QStringList list_custom = regul_custom.capturedTexts();

        //! Если часть строки подошла под шаблон, то
        if(pos_custom!=-1) {

            /*! Генерирование регулярного выражения для поиска объявления пользовательского типа данных
            *  \code
            *  QString name_custom = list2[1];
            *  QString regul7 = "(struct||union|enum)\\s(";
            *  QString regul8 = ")";
            *  \endcode
            */
            QString name_custom = list_custom[1];
            QString regul_cus1 = "(struct||union|enum)\\s(";
            QString regul_cus2 = ")";
            regul_cus1 = regul_cus1 + name_custom + regul_cus2;
            QRegExp regul_custom_seu(regul_cus1);

            //! Поиск объявления пользовательского типа данных в строке с помощью шаблона
            QStringList list_cus = regul_custom_seu.capturedTexts();
            int pos_cus = regul_custom_seu.indexIn(str);

            //! Если позиция найдена, то
            if(pos_cus!=-1) {

                //! Считаем, что переменная найдена
                names_index[l]=1;
            }
        }

        /*! Генерирование регулярного выражения для поиска объявления особого случая пользовательского типа данных
        *  \code
        *  string regul7 = "(struct||enum||union)(\\s)(\\w+)(\\{.*\\})(";
        *  string regul8 = ")[^A-Z^a-z^0-9^_^(]";
        *  regul7 = regul7 + names[l] + regul8;
        *  \endcode
        */
        string regul_super_custom1 = "(struct||enum||union)(\\s)(\\w+)(\\{.*\\})(";
        string regul_super_custom2 = ")[^A-Z^a-z^0-9^_^(]";
        regul_super_custom1 = regul_super_custom1 + names[l] + regul_super_custom2;
        QString regul_super_custom3 = QString::fromUtf8(regul_super_custom1.c_str());
        QRegExp regul_super_custom(regul_super_custom3);

        //! Поиск объявления особого случая пользовательского типа данных в строке с помощью шаблона
        int pos_super_custom = regul_super_custom.indexIn(str);
        QStringList list_super_custom = regul_super_custom.capturedTexts();

        //! Если позиция найдена, то
        if(pos_super_custom!=-1) {

            //! Считаем, что переменная найдена
            names_index[l]=1;
        }

        /*! Генерирование регулярного выражения для поиска define
        *  \code
        *  string regul10 = "(#define)\\s(";
        *  string regul11 = ")[^A-Z^a-z^0-9]";
        *  regul10 = regul10 + names[l] + regul11;
        *  \endcode
        */
        string regul_define1 = "(#define)\\s(";
        string regul_define2 = ")[^A-Z^a-z^0-9]";
        regul_define1 = regul_define1 + names[l] + regul_define2;
        QString regul_define3 = QString::fromUtf8(regul_define1.c_str());
        QRegExp regul_for_defline(regul_define3);

        //! Поиск объявления особого случая пользовательского типа данных в строке с помощью шаблона
        int pos_define = regul_for_defline.indexIn(str);
        QStringList list_define = regul_for_defline.capturedTexts();

        //! Если позиция найдена, то
        if(pos_define!=-1) {

            //! Считаем, что переменная найдена
            names_index[l]=1;
        }
    }
}
