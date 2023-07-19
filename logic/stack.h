#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

// Операторы
typedef struct stack_operators {
  char symbol;
  struct stack_operators* next;
} stack_operators;

// Числа
typedef struct stack_operands {
  double digit;
  struct stack_operands* next;
} stack_operands;

// Функция для добавления элемента в стек операторов
stack_operators* push_operator(stack_operators* head, char a);
// Функция для извлечения элемента из стека операторов
char pop_operator(stack_operators** head);
// Функция, которая возвращает верхний элемент стека операторов, не удаляя его
char peek_operator(stack_operators* head);
// Отчистка стека
void clear_stack_operators(stack_operators** head);
// Функция для добавления элемента в стек операндов
stack_operands* push_operand(stack_operands* head, double a);
// Функция для извлечения элемента из стека операндов
double pop_operand(stack_operands** head);
// верхний элемент стека
double peek_operand(stack_operands* head);
void clear_stack_operands(stack_operands** head);
void print_operators_stack(stack_operators* head);
void print_operands_stack(stack_operands* head);

#ifdef __cplusplus
}
#endif

#endif  // STACK_H