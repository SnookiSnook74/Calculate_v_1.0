#include "stack.h"

stack_operators* push_operator(stack_operators* head, char a) {
  stack_operators* ptr = malloc(sizeof(stack_operators));
  ptr->symbol = a;
  ptr->next = head;
  return ptr;
}

char pop_operator(stack_operators** head) {
  char a;
  if (*head == NULL) {
    a = '\0';
  } else {
    stack_operators* ptr = *head;
    a = ptr->symbol;
    *head = ptr->next;
    free(ptr);
  }
  return a;
}

char peek_operator(stack_operators* head) {
  if (head != NULL) {
    return head->symbol;
  } else {
    return '\0';
  }
}

stack_operands* push_operand(stack_operands* head, double a) {
  stack_operands* ptr = malloc(sizeof(stack_operands));
  ptr->digit = a;
  ptr->next = head;
  return ptr;
}

// Функция для извлечения элемента из стека операндов
double pop_operand(stack_operands** head) {
  stack_operands* ptr = *head;
  double a = ptr->digit;
  *head = ptr->next;
  free(ptr);
  return a;
}

double peek_operand(stack_operands* head) {
  if (head != NULL) {
    return head->digit;
  } else {
    return 0.0;
  }
}

void clear_stack_operators(stack_operators** head) {
  while (*head != NULL) {
    pop_operator(head);
  }
}

void clear_stack_operands(stack_operands** head) {
  while (*head != NULL) {
    pop_operand(head);
  }
}

void print_operators_stack(stack_operators* head) {
  stack_operators* current = head;
  while (current != NULL) {
    printf("%c\n", current->symbol);
    current = current->next;
  }
}

void print_operands_stack(stack_operands* head) {
  stack_operands* current = head;
  while (current != NULL) {
    printf("%lf\n", current->digit);
    current = current->next;
  }
}
