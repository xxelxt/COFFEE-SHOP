#include <stdio.h>		// printf scanf
#include <stdlib.h>		// malloc
#include <string.h>		// strcpy

// TODO: Work on file input

#define STR2(x) #x
#define STR(X) STR2(X)

#define MAX_DRINK 99
#define MAX_TOPPING 99
#define DRINK_TOPPING_NAME_LENGTH 255


void clear_screen(){
#ifdef WINDOWS
	system("cls");
#else
    // Assume POSIX
	system("clear");
#endif
}

FILE * inputptr;
FILE * ouputptr;	// TODO: replace printf with fprintf

// DSLK cho DRINK MENU + TOPPING MENU
// ARRAY cho Don hang
typedef struct s_item {
	char name[DRINK_TOPPING_NAME_LENGTH + 1];
	int cost;

	struct s_item * next;
} ITEM;

ITEM * HEAD_DRINK;
ITEM * LAST_DRINK;
ITEM * HEAD_TOPPING;
ITEM * LAST_TOPPING;
int DRINK_COUNT, TOPPING_COUNT;

// Basic functions
ITEM * addMenu(ITEM * current, char * name, int cost){
	ITEM * new = malloc(sizeof * new);
	
	strcpy(new->name,name);
	new->cost = cost;
	new->next = NULL;

	if (current != NULL)
		current->next = new;

	return new;
}

void removeMenu(ITEM ** head, int pos){
	int count = 1;
	ITEM * now = (*head);
	ITEM * prev;

	// Head case
	if (pos == 1) {
		(*head) = (*head)->next;	// Change the original pointer
		free(now);
	} 
	else {
		// Everywhere else case
		while (now->next != NULL)
		{
			prev = now;
			now = now->next;
			count++;

			if (count == pos) {
				prev->next = prev->next->next;
				free(now);
				break;
			}
		}
	}

	return;
}

void printMenu(ITEM * now){		// A copy of actual head pointer
	int count = 0;

	while (now != NULL) {
		count++;

		printf("%d. ", count);
		printf("%-20s", now->name);
		printf(" %d.000 VND\n", now->cost);

		now = now->next;
	}

	if (count == 0)
		printf("Menu ko co gi ca.\n");

	return;
}



void addMenuInput(ITEM ** item_head, ITEM ** item_last, int * item_count){
	char namebuf[DRINK_TOPPING_NAME_LENGTH + 1];
	int cost = -1;

	printf("Ten: ");
	/*fgets(namebuf, sizeof namebuf, inputptr);
	namebuf[strcspn(namebuf, "\n")] = 0;		// Remove trailing \n from fgets */
	fscanf(inputptr, " %" STR(DRINK_TOPPING_NAME_LENGTH) "[^\n]", namebuf);

	printf("Gia (.000 VND): ");
	fscanf(inputptr, " %d", &cost);
	printf("\t%d.000 VND\n", cost);

	// *item_head = HEAD_DRINK
	// *item_last = LAST_DRINK
	// *item_count = DRINK_COUNT  
	*item_last = addMenu(*item_last, namebuf, cost);
	(*item_count)++;


	// Khi head chua dc khoi tao
	if (*item_head == NULL)
		*item_head = *item_last;

	return;
}

void addDrink(){
	addMenuInput(&HEAD_DRINK, &LAST_DRINK, &DRINK_COUNT);
	return;
}
void addTopping(){
	addMenuInput(&HEAD_TOPPING, &LAST_TOPPING, &TOPPING_COUNT);
	return;
}




void removeMenuInput(ITEM ** item_head, ITEM ** item_last, int * item_count){
	int option = 0;
	// *item_head = HEAD_DRINK
	// *item_last = LAST_DRINK
	// *item_count = DRINK_COUNT 
	printMenu(*item_head);
	if (*item_head == NULL){
		return;					// Menu ko co gi ca
	}

	fscanf(inputptr, " %d", &option);
	while (option > *item_count || option < 1){
		printf("Khong co. Nhap lai: ");
		fscanf(inputptr, " %d", &option);

						if (feof(inputptr)){
					fclose(inputptr);
					inputptr = stdin;
					break;	// Not sure about this
				}
	}

	removeMenu(item_head, option);
	(*item_count)--;

	// Khi xoa het menu
	if (*item_count == 0){
		*item_head = NULL;
		*item_last = NULL;
	}

	return;
}

void removeDrink(){
	removeMenuInput(&HEAD_DRINK, &LAST_DRINK, &DRINK_COUNT);
	return;
}
void removeTopping(){
	removeMenuInput(&HEAD_TOPPING, &LAST_TOPPING, &TOPPING_COUNT);
	return;
}



int main()
{
	inputptr = stdin;
	ouputptr = stdout;

	char lc = 0;
	int menuup = 0;

	// File input 
	/*
	inputptr = fopen("autoinput.txt", "r");
	if (inputptr == NULL){
		printf("file doesn't exist\n");
		inputptr = stdin;
	} */


	clear_screen();
	while(1)
	{
		if (menuup & 1){ printf("\tDO UONG\n"); printMenu(HEAD_DRINK); }
		if (menuup & 2){ printf("\tTOPPING\n"); printMenu(HEAD_TOPPING); }

		printf("\t\tPROG");
		printf("\n1. Hien/An Danh Sach do uong.");
		printf("\n2. Hien/An Danh Sach topping.");
		printf("\n3. Them do uong.");
		printf("\n4. Them topping");
		printf("\n5. Xoa do uong");
		printf("\n6. Xoa topping");
		printf("\n0. Thoat");
		printf("\nChon chuc nang: ");
		fscanf(inputptr, " %c", &lc);

		switch(lc)
		{
			case '1':
			{
				menuup = menuup ^ 1;
				clear_screen();
				break;
			}
			case '2':
			{
				menuup = menuup ^ 2;
				clear_screen();
				break;
			}
			case '3':
			{
				printf("\t\tTHEM DO UONG\n");
				addDrink();
				clear_screen();
				break;
			}
			case '4':
			{
				printf("\t\tTHEM TOPPING\n");
				addTopping();
				clear_screen();
				break;
			}
			case '5':
			{
				printf("\t\tXOA DO UONG\n");
				removeDrink();
				clear_screen();
				break;
			}
			case '6':
			{
				printf("\t\tXOA TOPPING\n");
				removeTopping();
				clear_screen();
				break;
			}
			case '0': exit(1); return 0;
			default:
			{
				printf("\nNhap lai.");
				fscanf(inputptr, " %c", &lc);
			}
		}


		if (feof(inputptr)){
			fclose(inputptr);
			inputptr = stdin;
			printf("File successfully read, press ENTER to continue");
			scanf(" %*c");
			continue;	// Not sure about this
		}
	}

	return 0;
}
