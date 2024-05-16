#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/helper_functions.h"
#include <address_book.h>

int flag = 1;

void sig_handler(int signum)
{
	flag = 0;
}

int main(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);

	struct Person *list = NULL;
	FILE *address_file  = NULL;
	address_file	    = open_address_file("addresses.csv");

	if (address_file != NULL) {
		addressess_load(address_file, &list);
		fclose(address_file);
	}

	wait_for_user();

	int user_id = -1;
	int return_code;
	char *key	      = NULL;
	struct Person *person = NULL;

	while (flag) {
		// system("clear");
		print_select_options();
		int selection = handle_user_select();

		switch (selection) {
		case 0:
			addresses_delete_list(&list);
			exit(0);

		case 1:
			if (list != NULL)
				addresses_print(list);
			else
				printf("list is empty\n");
			wait_for_user();
			break;

		case 2:
			person	    = read_person_fields();
			return_code = addresses_add(&list, person);

			if (return_code == 0)
				printf("address added\n");
			else
				printf("provided list is empty\n");

			wait_for_user();
			break;

		case 3:
			person = read_person_fields();
			printf("select in which position to add \n");
			user_id	    = handle_user_select();
			return_code = addresses_add_by_position(&list, person, user_id);

			if (return_code == 0)
				printf("address added\n");
			else if (return_code == 1)
				printf("memory allocation failed\n");
			else
				printf("index out of range\n");

			wait_for_user();
			break;

		case 4:
			printf("select which user you want to delete.\n");
			user_id	    = handle_user_select();
			return_code = addresses_delete_by_position(&list, user_id);

			if (return_code == 0)
				printf("user deleted\n");
			else if (return_code == -1)
				printf("list is empty\n");
			else
				printf("index out of bounds\n");

			wait_for_user();
			break;

		case 5:
			addresses_delete_list(&list);
			printf("list deleted\n");
			list = NULL;
			wait_for_user();
			break;

		case 6:
			printf("select which user you want to find.\n");
			user_id = handle_user_select();
			person	= addresses_find_by_position(list, user_id);
			if (person != NULL) {
				print_person(person);
			} else {
				printf("person not found\n");
			}
			wait_for_user();
			break;

		case 7:
			printf("select which user you want to find by key \n");
			printf("enter the key: \n");
			key = handle_user_string(64);

			struct Person *matches = NULL;
			matches		       = addresses_find_by_key(list, key);

			if (matches != NULL)
				addresses_print(matches);
			else
				printf("no matches found\n");

			free(key);
			addresses_delete_list(&matches);
			matches = NULL;
			wait_for_user();
			break;

		default:
			printf("Invalid choice.\n");
			wait_for_user();
			break;
		}
	}

	addresses_delete_list(&list);

	return 0;
}
