#include <stdlib.h>
#include <string.h>

#include "address_book.h"
#include "helper_functions.h"

FILE *open_address_file(char *filename)
{
	char *home_path = NULL;
	home_path	= getenv("HOME");

	char *address_file_name = filename;
	char address_file_path[128];
	sprintf(address_file_path, "%s/%s", home_path, address_file_name);

	FILE *address_file = NULL;

	address_file = fopen(address_file_path, "r");

	if (address_file == NULL) {
		printf("Unable to open file from home\n");

		address_file = fopen(address_file_name, "r");

		if (address_file == NULL) {
			printf("Unable to open file from local dir\n");
			return NULL;
		}
		printf("loaded from local dir\n");

	} else {
		printf("loaded from home dir\n");
	}

	return address_file;
}

void print_select_options()
{
	char *options[] = {
		"print address list",	      "add new address",     "add new address to specific position",
		"delete address by position", "delete address list", "find address by position",
		"find address by key"

	};
	int options_num = sizeof(options) / sizeof(options[0]);

	for (int i = 0; i < options_num; i++) {
		printf("%d. %s\n", i + 1, options[i]);
	}

	printf("0. exit\n");
}

int handle_user_select()
{
	int value = 0;

	while (value >= 0) {
		int rtn;

		printf("Enter a number: ");
		rtn = scanf("%d", &value);
		if (rtn == EOF) {
			fputs("user canceled input.\n", stderr);
			break;
		} else if (rtn == 0) {
			fputs("error: invalid input\n", stderr);
			empty_stdin();
		} else {
			// without this clear '\n' from users input is left in stdin
			empty_stdin();
			break;
		}
	}

	return value;
}

/** remove all characters that remain in stdin */
void empty_stdin(void)
{
	int c = getchar();

	while (c != '\n' && c != EOF)
		c = getchar();
}

// Read characters until Enter key (newline) is encountered
void wait_for_user()
{
	printf("Press Enter to continue...\n");

	while (getchar() != '\n')
		;
}

char *handle_user_string(int str_len)
{
	char input[str_len];

	while (1) {
		if (fgets(input, sizeof(input), stdin) != NULL) {
			if (input[0] == '\n')
				continue;

			// Remove newline character, if present
			if (input[strlen(input) - 1] == '\n') {
				input[strlen(input) - 1] = '\0';
			} else {
				empty_stdin();
			}

			// +1 because strlen() does not count '\0'
			char *result = malloc(strlen(input) + 1);
			if (result != NULL) {
				strcpy(result, input);
				return result;
			} else {
				printf("Memory allocation failed.\n");
				return NULL;
			}
		} else {
			printf("Error reading input.\n");
			return NULL;
		}
	}
}

void print_person(struct Person *person)
{
	printf("%s %s %s %s\n", person->name, person->surname, person->number, person->email);
}

struct Person *read_person_fields()
{
	int size_of_name    = sizeof(((struct Person *)0)->name);
	int size_of_surname = sizeof(((struct Person *)0)->surname);
	int size_of_number  = sizeof(((struct Person *)0)->number);
	int size_of_email   = sizeof(((struct Person *)0)->email);

	struct Person *person = NULL;
	printf("Enter address name: \n");
	char *name = handle_user_string(size_of_name);

	printf("Enter address surname: \n");
	char *surname = handle_user_string(size_of_surname);

	printf("Enter address number: \n");
	char *number = handle_user_string(size_of_number);

	printf("Enter address email: \n");
	char *email = handle_user_string(size_of_email);

	person = create_node(name, surname, number, email);

	free(name);
	free(surname);
	free(number);
	free(email);
	// print_person(person);

	return person;
}