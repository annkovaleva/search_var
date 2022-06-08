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





