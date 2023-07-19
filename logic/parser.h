#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "stack.h"

typedef struct {
  double result;
  int error_code;
} result;

// Проверка на число
char* is_number(const char* expression, int* i);
// Проверка на функцию или оператор
char* in_operation(const char* expression, int* i);
// Основаня функция разбития строки
char** parse_expression(const char* expression);
// Освобождение памяти
void free_tokens(char** tokens);
// Вспомогательная функция для проверки, является ли данное слово известной
// функцией
bool is_known_function(const char* word);
// Проверка строки на валидность
bool validate_expression(const char* expression);
// Определение приоритета операций
int get_priority(char op);
// Преобразование в польскую запись
char** infix_to_postfix(char** tokens);
// Вычесления
result compute_postfix(char** postfix);
// Результат
double calculate(char* line);

#ifdef __cplusplus
}
#endif
