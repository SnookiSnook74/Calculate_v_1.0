#include "parser.h"

char* is_number(const char* expression, int* i) {
  char number[32];
  int j = 0;
  // Собираем все цифры числа и символы точки
  while (isdigit(expression[*i]) || expression[*i] == '.') {
    number[j++] = expression[(*i)++];
  }
  (*i)--;  // Возвращаемся на последний символ, который не является цифрой или
           // точкой
  number[j] = '\0';
  char* token = malloc(strlen(number) + 1);
  if (token != NULL) {
    strcpy(token, number);
  }
  return token;
}

char* is_operation(const char* expression, int* i, char last_token) {
  char* token = NULL;
  const char* functions[] = {"sin",  "cos",  "tan", "asin", "acos",
                             "atan", "sqrt", "ln",  "log",  NULL};
  const char function_symbols[] = {'s', 'c', 't', 'i', 'o', 'n', 'q', 'l', 'g'};

  for (int f = 0; functions[f] != NULL && token == NULL; f++) {
    int func_length = strlen(functions[f]);
    if (strncmp(expression + *i, functions[f], func_length) == 0) {
      token = malloc(2);
      if (token != NULL) {
        token[0] = function_symbols[f];
        token[1] = '\0';
        *i += func_length - 1;
      }
    }
  }

  if (token == NULL) {
    char operation[2] = {expression[*i], '\0'};
    token = malloc(2);
    if (token != NULL) {
      if (operation[0] == '-' &&
          (last_token == '(' || last_token == '+' || last_token == '-' ||
           last_token == '*' || last_token == '/' || last_token == '^')) {
        operation[0] = 'u';
        strcpy(token, operation);
      } else if (operation[0] == '+' &&
                 (last_token == '(' || last_token == '+' || last_token == '-' ||
                  last_token == '*' || last_token == '/' ||
                  last_token == '^')) {
        free(token);
        token = NULL;
      } else {
        strcpy(token, operation);
      }
    }
  }
  return token;
}

char** parse_expression(const char* expression) {
  int length = strlen(expression);
  char** tokens = malloc(sizeof(char*) *
                         (length * 2 + 1));  // Максимальное количество токенов
  if (tokens == NULL) {
    return NULL;
  }
  char last_token =
      0;  // Инициализация переменной для хранения последнего токена
  int token_index = 0;

  // Добавление унарного минуса, если выражение начинается с минуса
  if (expression[0] == '-') {
    tokens[token_index] = malloc(2);
    if (tokens[token_index] != NULL) {
      tokens[token_index][0] = 'u';
      tokens[token_index][1] = '\0';
      token_index++;
    }
  }

  // Начало цикла со второго символа, если первый символ - унарный минус
  for (int i = (expression[0] == '-' ? 1 : 0); i < length; i++) {
    if (isdigit(expression[i]) ||
        expression[i] == '.') {  // Если текущий символ - цифра или точка
      tokens[token_index] = is_number(expression, &i);
      last_token = 'n';  // Обновляем значение последнего токена на 'n' (число)
    } else if (isspace(expression[i])) {  // Пропускаем пробелы
      continue;
    } else {  // Если текущий символ - операция, скобка или функция
      tokens[token_index] = is_operation(expression, &i, last_token);
      last_token = expression[i];  // Обновляем значение последнего токена на
                                   // текущий символ
    }
    if (tokens[token_index] != NULL) {
      token_index++;  // Переходим к следующему токену только если текущий токен
                      // не равен NULL
    }
  }
  tokens[token_index] = NULL;  // Завершающий NULL-указатель
  return tokens;
}

void free_tokens(char** tokens) {
  for (int i = 0; tokens[i] != NULL; i++) {
    free(tokens[i]);
  }
  free(tokens);
}

bool is_known_function(const char* word) {
  const char* functions[] = {"sin",  "cos",  "tan", "asin", "acos",
                             "atan", "sqrt", "ln",  "log",  NULL};
  for (int f = 0; functions[f] != NULL; f++) {
    if (strcmp(word, functions[f]) == 0) {
      return true;
    }
  }
  return false;
}

bool validate_expression(const char* expression) {
  int open_parentheses = 0;
  int close_parentheses = 0;
  char word[10];  // Буфер для слова (например, имени функции)
  int j = 0;  // Индекс в буфере для слова
  // Есть ли что-то внутри скобок
  bool inside_parenthesis = false;
  // Пустые скобки
  bool empty_parenthesis = true;
  bool valid = true;  // Переменная для отслеживания состояния проверки
  for (int i = 0; expression[i] != '\0' && valid; i++) {
    if (expression[i] == '(') {
      open_parentheses++;
      inside_parenthesis = true;
      empty_parenthesis = true;
      if (j > 0) {
        word[j] = '\0';
        if (!is_known_function(word)) {
          valid = false;  // Неизвестное имя функции
        }
        j = 0;
      }
    } else if (expression[i] == ')') {
      close_parentheses++;
      inside_parenthesis = false;
      if (empty_parenthesis) {
        valid = false;  // Ошибка: пустые скобки
      }
    } else if (isalpha(expression[i]) || isdigit(expression[i]) ||
               expression[i] == '.') {
      word[j++] = expression[i];
      if (inside_parenthesis) {
        empty_parenthesis = false;
      }
    } else {
      if (j > 0) {
        j = 0;
      }
    }
  }
  if (open_parentheses != close_parentheses) {
    valid = false;  // Некорректное количество скобок
  }
  return valid;  // Возвращаем результат проверки
}

int get_priority(char op) {
  int priority;
  switch (op) {
    case 'u':
      priority = 4;
      break;
    case '^':
      priority = 3;
      break;
    case '*':
    case '/':
    case '%':
      priority = 2;
      break;
    case '+':
    case '-':
      priority = 1;
      break;
    case '(':
    case ')':
      priority = 0;
      break;
    case 's':  // sin
    case 'c':  // cos
    case 't':  // tan
    case 'i':  // asin
    case 'o':  // acos
    case 'n':  // atan
    case 'q':  // sqrt
    case 'l':  // ln
    case 'g':  // log
      priority = 5;
      break;
    default:
      priority = -1;
  }
  return priority;
}

char** infix_to_postfix(char** tokens) {
  // Создаем стек для хранения операторов
  stack_operators* operators = NULL;
  // Определяем количество токенов
  int num_tokens = 0;
  while (tokens[num_tokens] != NULL) {
    num_tokens++;
  }
  // Выделяем память под массив для хранения постфиксного выражения
  char** postfix = malloc(sizeof(char*) * (num_tokens + 1));
  if (postfix == NULL) {
    return NULL;  // В случае ошибки выделения памяти возвращаем NULL
  }
  int token_index = 0;
  int postfix_index = 0;
  // Обрабатываем каждый токен
  while (tokens[token_index] != NULL) {
    char* token = tokens[token_index];
    // Если встретили открывающую скобку, помещаем ее в стек операторов
    if (strcmp(token, "(") == 0) {
      operators = push_operator(operators, *token);
      // Если встретили закрывающую скобку, переносим все операторы из стека в
      // постфиксное выражение до тех пор, пока не встретим открывающую скобку
    } else if (strcmp(token, ")") == 0) {
      while (peek_operator(operators) != '(') {
        char operator= pop_operator(&operators);
        char* operator_str = malloc(2);
        operator_str[0] = operator;
        operator_str[1] = '\0';
        postfix[postfix_index++] = operator_str;
      }
      pop_operator(&operators);  // Удаляем открывающую скобку из стека
      // Если встретили оператор, переносим операторы из стека в постфиксное
      // выражение, пока их приоритет не меньше, чем у текущего оператора
    } else if (get_priority(*token) > 0) {
      while (operators != NULL &&
             get_priority(peek_operator(operators)) >= get_priority(*token)) {
        char operator= pop_operator(&operators);
        char* operator_str = malloc(2);
        operator_str[0] = operator;
        operator_str[1] = '\0';
        postfix[postfix_index++] = operator_str;
      }
      // После этого кладем текущий оператор в стек
      operators = push_operator(operators, *token);
      // Если встретили операнд, добавляем его в постфиксное выражение
    } else {
      char* operand_str = malloc(strlen(token) + 1);
      strcpy(operand_str, token);
      postfix[postfix_index++] = operand_str;
    }
    // Переходим к следующему токену
    token_index++;
  }
  // После обработки всех токенов, переносим оставшиеся операторы из стека в
  // постфиксное выражение
  while (operators != NULL) {
    char operator= pop_operator(&operators);
    char* operator_str = malloc(2);
    operator_str[0] = operator;
    operator_str[1] = '\0';
    postfix[postfix_index++] = operator_str;
  }
  // Окончание массива обозначается NULL
  postfix[postfix_index] = NULL;
  return postfix;  // Возвращаем постфиксное выражение
}

result compute_postfix(char** postfix) {
  setlocale(LC_NUMERIC, "C");
  stack_operands* numbers = NULL;
  int i = 0;
  result res;
  res.result = 0.0;
  res.error_code = 0;
  while (postfix[i] != NULL && res.error_code == 0) {
    if (get_priority(*postfix[i]) == -1) {
      double number = atof(postfix[i]);
      numbers = push_operand(numbers, number);
    } else {
      double calculation;
      double number2 = pop_operand(&numbers);
      if (*postfix[i] != 'u' && *postfix[i] != 's' && *postfix[i] != 'c' &&
          *postfix[i] != 't' && *postfix[i] != 'i' && *postfix[i] != 'o' &&
          *postfix[i] != 'n' && *postfix[i] != 'q' && *postfix[i] != 'l' &&
          *postfix[i] != 'g') {
        double number1 = pop_operand(&numbers);
        switch (*postfix[i]) {
          case '+':
            calculation = number1 + number2;
            break;
          case '-':
            calculation = number1 - number2;
            break;
          case '%':
            calculation = fmod(number1, number2);
            break;
          case '*':
            calculation = number1 * number2;
            break;
          case '/':
            if (number2 != 0) {
              calculation = number1 / number2;
            } else {
              res.error_code = 1;
            }
            break;
          case '^':
            calculation = pow(number1, number2);
            break;
          default:
            res.error_code = 1;
        }
      } else {
        switch (*postfix[i]) {
          case 'u':
            calculation = -number2;
            break;
          case 's':
            calculation = sin(number2);
            break;
          case 'c':
            calculation = cos(number2);
            break;
          case 't':
            calculation = tan(number2);
            break;
          case 'i':
            calculation = asin(number2);
            break;
          case 'o':
            calculation = acos(number2);
            break;
          case 'n':
            calculation = atan(number2);
            break;
          case 'q':
            if (number2 >= 0) {
              calculation = sqrt(number2);
            } else {
              res.error_code = 1;
            }
            break;
          case 'l':
            if (number2 > 0) {
              calculation = log(number2);
            } else {
              res.error_code = 1;
            }
            break;
          case 'g':
            if (number2 > 0) {
              calculation = log10(number2);
            } else {
              res.error_code = 1;
            }
            break;
          default:
            res.error_code = 1;
        }
      }
      if (res.error_code == 0) {
        numbers = push_operand(numbers, calculation);
      }
    }
    i++;
  }
  if (res.error_code == 0) {
    res.result = pop_operand(&numbers);
  }
  return res;
}

double calculate(char* line) {
  setlocale(LC_NUMERIC, "C");
  double res = NAN;
  if (strlen(line) <= 255) {
    if (validate_expression(line)) {
      char** parse = parse_expression(line);
      char** infix = infix_to_postfix(parse);
      result final = compute_postfix(infix);
      if (final.error_code == 0) {
        res = final.result;
      }
      free_tokens(parse);
      free_tokens(infix);
    }
  }
  return res;
}
