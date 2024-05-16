#include <stdio.h>

#ifndef ADDRESS_BOOK_H_INCLUDED
#define ADDRESS_BOOK_H_INCLUDED

struct Person {
	char name[32];
	char surname[32];
	char number[32];
	char email[64];
	struct Person *next;
};

int addresses_add(struct Person **list, struct Person *node);
void addresses_print(struct Person *list);
void addresses_delete_list(struct Person **list);
void addressess_load(FILE *file, struct Person **list);
struct Person *create_node(char *name, char *surname, char *number, char *email);

struct Person *addresses_find_by_position(struct Person *list, int position);
struct Person *addresses_find_by_key(struct Person *list, const char *key);
int addresses_add_by_position(struct Person **list, struct Person *address, int position);
int addresses_delete_by_position(struct Person **list, int position);

#endif
