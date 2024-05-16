#include <stdio.h>
#include "address_book.h"

#ifndef HELPER_FUNCTIONS_H_INCLUDED
#define HELPER_FUNCTIONS_H_INCLUDED

FILE *open_address_file(char *filename);
void print_select_options();
int handle_user_select();
void empty_stdin(void);
void wait_for_user();
char *handle_user_string(int str_len);
void print_person(struct Person *person);
struct Person *read_person_fields();

#endif