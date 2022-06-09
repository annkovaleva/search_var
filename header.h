#ifndef HEADER_H
#define HEADER_H

#endif // HEADER_H

#pragma once
#include <string>

using namespace std;

/*!
 Запись полученных ответов в файл
 * \param[in] file_name имя файла
 * \param[in] names_index[] массив с ответами, объявлена ли переменная
 * \param[in] len_names длина массива
 * \warning Перезапишет файл, если там что-то хранилось безвозвратно!
 */
void data_output(string file_name, int names_index[], int len_names);

/*!
 Запись текста из файла в массив строк
 * \param[in] name_file[] имя файла
 * \param[in,out] arr_text[] массив, в который помещаем информацию из текста
 * \param[in] index_erorr указатель на ошибку в определенном файле
 * \return длина массива
 */
int data_input(char name_file[], string arr_text[], int index_erorr);

/*!
 Удаление однострочных комментариев
 * \param[in,out] arr_text[] массив строк с текстом функции
 * \param[in] len_text длина массива
 */
void remove_line_comments(string arr_text[], int len_text);

/*!
 Удаление определенного символа из строки
 * \param[in,out] str строка с текстом функции
 * \param[in] rem_str символ, который нужно удалить
 */
void remove_char_from_str(string &str, string rem_str);

/*!
 Удаление определенного слова из строки
 * \param[in,out] str строка с текстом функции
 * \param[in] rem_str слово, которое нужно удалить
 */
void remove_word_from_str(string &str, string rem_str);

/*!
 Удаление ненужных пробелов
 * \param[in,out] str строка с текстом функции
 */
void remove_spaces(string& str);
