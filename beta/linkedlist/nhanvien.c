#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE * inputptr;
FILE * outputptr;


typedef struct s_sp {
	char ten[20];
	int gia, stt;

	struct s_sp * next;
} SP;


SP * HEAD_SP;
SP * LAST_SP;
int SP_COUNT;

// Basic functions
SP * createNode(SP * current){
	SP * new = malloc(sizeof * new);
	new->next = NULL;

	if (current != NULL)
		current->next = new;

	return new;
}

void addNode(SP ** head, SP ** last){
	// *item_head = HEAD_DRINK
	// *item_last = LAST_DRINK
	// *item_count = DRINK_COUNT  
	*last = createNode(*last);

	// Khi head chua dc khoi tao
	if (*head == NULL)
		*head = *last;

	return;
}

void removeNode(SP ** head, int pos){
	int count = 1;
	SP * now = (*head);
	SP * prev;

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



void inputAddSP(SP ** head, SP ** last, int * item_count){
	addNode(head, last);
	SP * now = (*last);

/*
	printf("Ten: ");
	fscanf(inputptr, " %[^\n]", now->ten);

	printf("Gioi tinh: ");
	fscanf(inputptr, " %[^\n]", now->gt);

	printf("Ngay sinh: ");
	fscanf(inputptr, " %[^\n]", now->ngaysinh);

	printf("CCCD: ");
	fscanf(inputptr, " %d", &now->cccd);

	printf("SDT: ");
	fscanf(inputptr, " %d", &now->sdt);
*/
	printf("Ten: ");
	fscanf(inputptr, " %[^\n]", now->ten);

	printf("Gia SP: ");
	fscanf(inputptr, " %d", &now->gia);

	(*item_count)++;
	return;
}

void inputRemoveSP(SP ** head, SP ** last, int * item_count){
	int pos;

	if (*head == NULL){
		return;					// Node ko co gi ca
	}

	fscanf(inputptr, " %d", &pos);
	while (pos > *item_count || pos < 1){
		printf("Khong co. Nhap lai: ");
		fscanf(inputptr, " %d", &pos);
	}

	removeNode(head, pos);
	(*item_count)--;
	// Khi xoa het menu
	if (*item_count == 0){
		*head = NULL;
		*last = NULL;
	}

	return;
}


void printNode(SP * now){		// A copy of actual head pointer
	int count = 0;

	printf("--------------------\n");
	while (now != NULL) {
		count++;

/*
		printf("[ %s", now->ten);
		printf(" %s", now->gt);
		printf(" %s", now->ngaysinh);
		printf(" %d", now->cccd);
		printf(" %d ] -\n", now->sdt); */
		printf("%d.", count);
		printf(" %s", now->ten);
		printf(" %d\n", now->gia);

		now = now->next;
	}

	if (count == 0)
		printf("Node ko co gi ca.\n");

	return;
}



void readFileSP(char * readfile, SP ** head, SP ** last, int * item_count){
	FILE * fptr = fopen(readfile, "rb");
	if (fptr == NULL){
		printf("FILE %s khong mo dc.\n", readfile);
		return;
	}

	(*head) = NULL;
	(*last) = NULL;
	SP * prevlast;
	SP * now;

	do{
		prevlast = now;
		addNode(head, last);
		now = (*last);

		(*item_count)++;
	} while(fread(now, sizeof(SP), 1, fptr) != 0);			// Check for number of item read

	(*last) = prevlast;
	(*last)->next = NULL;
	free(now);

	fclose(fptr);
	return;
}

void writeFileSP(char * writefile, SP ** head){
	FILE * fptr = fopen(writefile, "wb");

	SP * writing = (*head);

	while (writing != NULL) {
		fwrite(writing, sizeof(SP), 1, fptr);

		writing = writing->next;
	}

	fclose(fptr);
	return;
}



int main()
{
	inputptr = stdin;
	outputptr = stdout;
	char tenfile[] = "binary.bin"; 

	int num;
	char buffer[50];
	char lc;

	// File input 
	/*
	inputptr = fopen("autoinput.txt", "r");
	if (inputptr == NULL){
		printf("file doesn't exist\n");
		inputptr = stdin;
	} */


	while(1)
	{
		printNode(HEAD_SP);

		printf("\t\tPROG");
		printf("\n1. Add");
		printf("\n2. Remove.");
		printf("\n3. Doc File Binary.");
		printf("\n4. Luu File Binary.");
		printf("\n= ");
		fscanf(inputptr, " %c", &lc);


		switch(lc)
		{

			case '1':
			{
				int option;
				do {
					inputAddSP(&HEAD_SP, &LAST_SP, &SP_COUNT);
					printf("TIEP TUC? 1.Co\t2.Khong\n");
					scanf("%d", &option);
				} while(option == 1);

				printf("Luu du lieu?  1.Co\t2.Khong\n");
				scanf("%d", &option);
				if(option == 1)
					writeFileSP(tenfile, &HEAD_SP);

				break;
			}
			case '2':
			{

				inputRemoveSP(&HEAD_SP, &LAST_SP, &SP_COUNT);
				break;
			}
			case '3':
			{

				readFileSP(tenfile, &HEAD_SP, &LAST_SP, &SP_COUNT);
				break;
			}
			case '4':
			{

				writeFileSP(tenfile, &HEAD_SP);
				break;
			}
			case '0': exit(1); return 0;
			default:
			{
				printf("\nNhap lai.");
				fscanf(inputptr, " %c", &lc);
			}
		}
	}

	return 0;
}
