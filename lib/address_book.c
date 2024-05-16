#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DELIMETER ","

#include <address_book.h>

static struct Person *create_address_node(char *address_line);

void addressess_load(FILE *file, struct Person **list)
{
	char line[256];

	while (fgets(line, sizeof(line), file)) {
		struct Person *person = NULL;

		if (line[0] == '\n')
			continue;

		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';

		person = create_address_node(line);
		if (person != NULL) {
			addresses_add(list, person);
		}
	}
}

static struct Person *create_address_node(char *address_line)
{
	struct Person *person = NULL;
	char *name;
	char *surname;
	char *number;
	char *email;

	name	= strtok(address_line, DELIMETER);
	surname = strtok(NULL, DELIMETER);
	number	= strtok(NULL, DELIMETER);
	email	= strtok(NULL, DELIMETER);

	person = create_node(name, surname, number, email);

	return person;
}

struct Person *create_node(char *name, char *surname, char *number, char *email)
{
	struct Person *person = NULL;
	person		      = (struct Person *)malloc(sizeof(struct Person));
	if (person == NULL) {
		return NULL;
	}
	strncpy(person->name, name, sizeof(person->name));
	strncpy(person->surname, surname, sizeof(person->surname));
	strncpy(person->number, number, sizeof(person->number));
	strncpy(person->email, email, sizeof(person->email));
	person->next = NULL;
	return person;
}

int addresses_add(struct Person **list, struct Person *person)
{
	struct Person *temp = *list;
	if (temp == NULL) {
		*list = person;
		return 1;
	}

	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = person;
	return 0;
}

void addresses_print(struct Person *list)
{
	struct Person *temp = list;
	int i		    = 1;
	while (temp != NULL) {
		printf("%3d. %s %s %s %s\n", i, temp->name, temp->surname, temp->number, temp->email);
		temp = temp->next;
		i++;
	}
	printf("\n");
}

void addresses_delete_list(struct Person **list)
{
	struct Person *to_delete = *list;
	while (*list != NULL) {
		*list = (*(list))->next;
		free(to_delete);
		to_delete = *list;
	}
}

struct Person *addresses_find_by_position(struct Person *list, int position)
{
	if (list == NULL)
		return NULL;

	int index	       = 1;
	struct Person *current = list;

	while (current != NULL && index < position) {
		current = current->next;
		index++;
	}

	// Position out of range
	if (index != position || current == NULL) {
		return NULL;
	}

	return current;
}

// Function to find a address's address by name, surname, email, or phone number
struct Person *addresses_find_by_key(struct Person *list, const char *key)
{
	if (list == NULL)
		return NULL;

	struct Person *current = list;

	struct Person *matches	  = NULL;
	struct Person *last_match = NULL;

	while (current != NULL) {
		// Compare the search criteria with each field
		if (strstr(current->name, key) != NULL || strstr(current->surname, key) != NULL ||
		    strstr(current->email, key) != NULL || strstr(current->number, key) != NULL) {
			struct Person *match =
				create_node(current->name, current->surname, current->email, current->number);
			if (match != NULL) {
				if (matches == NULL) {
					matches	   = match;
					last_match = match;
				} else {
					last_match->next = match;
					last_match	 = match;
				}

			} else {
				// Handle memory allocation failure (e.g., by freeing previously allocated memory)
				addresses_delete_list(&matches);
				return NULL;
			}
		}
		current = current->next;
	}

	return matches;
}

// Function to add a address to the linked list at a specific position
int addresses_add_by_position(struct Person **list, struct Person *address, int position)
{
	struct Person *temp = address;

	if (position == 1) {
		// Insert at the beginning
		temp->next = *list;
		*list	   = temp;
		return 0;
	}

	struct Person *current = *list;
	int index	       = 1;

	// Traverse the list to find the node at position - 1
	while (current != NULL && index < position - 1) {
		current = current->next;
		index++;
	}

	// If position is out of range
	if (current == NULL) {
		free(temp);
		return 2;
	}

	// Insert new address after current node
	temp->next    = current->next;
	current->next = temp;

	return 0;
}

int addresses_delete_by_position(struct Person **list, int position)
{
	if (*list == NULL) {
		return -1;
	}

	struct Person *current	= *list;
	struct Person *previous = NULL;
	int index		= 1;

	// Traverse the list to find the node at position
	while (current != NULL && index < position) {
		previous = current;
		current	 = current->next;
		index++;
	}

	// If position is out of range
	if (current == NULL) {
		return 1;
	}

	// If the node to be deleted is the first node
	if (previous == NULL) {
		*list = current->next;
	} else {
		previous->next = current->next;
	}

	free(current);
	return 0;
}