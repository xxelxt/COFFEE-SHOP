#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

FILE * inputptr;
FILE * outputptr;

// LIST OF FUNCTIONS

void Login();
void BigMenuQL();
void BigMenuNV();

////////// QUAN LY NHAN VIEN

void menuNV();
void docFileNV(char fileNV[]);
void xemNV(); void xem1NV(int vt);

void themNV();
void xoasuaNV(); void xoaNV(int vt); void suaNV(int vt);
void luuFileNV(char fileSP[]);

////////// QUAN LY SAN PHAM

void menuSP();
void docFileSP(char fileSP[]);
void xemSP(); void xem1SP(int vt);

void themSP();
void xoasuaSP(); void xoaSP(int vt); void suaSP(int vt);
void luuFileSP(char fileSP[]);

#define MAX_BUFFER 100
char fgetsbuffer[MAX_BUFFER] = { 0 };

void readinput(int bufferlen, const char * format, void * ptr){
	if (bufferlen == 0 || bufferlen > MAX_BUFFER) bufferlen = MAX_BUFFER;

	fgets(fgetsbuffer, bufferlen, inputptr);

	if(!strchr(fgetsbuffer, '\n'))
		while(fgetc(inputptr) != '\n');	// Discard everything until newline

	sscanf(fgetsbuffer, format, ptr);
	return;
}

int Confirmed()
{
	int option;
	printf("\t(1. Co / 0. Khong): ");
	readinput(0, " %d", &option);

	while (option != 1 && option != 0)
	{
		printf("\nNhap lai: ");
		readinput(0, " %d", &option);
	} 

	return option;
}

void cls()
{
	system("cls");
}

////////////////////////// QUAN LY NHAN VIEN

#define L_TENNV 30
#define L_GT 5
#define L_DOB 11
#define L_CCCD 13
#define L_SDT 11

struct nv
{
	char ten[L_TENNV];
	char gt[L_GT];
	char dob[L_DOB];
	char cccd[L_CCCD];
	char sdt[L_SDT];
};
typedef struct nv NV;

NV ARRAY_NV[1000];
int DEM_NV;

void docFileNV(char fileNV[])
{
	FILE *f;

	if ((f = fopen(fileNV, "rb")) == NULL)
	{
		f = fopen(fileNV, "wb");
		printf("File nhan vien bi loi/ khong ton tai. He thong tao file moi. \n\n");
	}

	DEM_NV = 0;
	while (fread(&ARRAY_NV[DEM_NV], sizeof(NV), 1, f) == 1) DEM_NV++;

	fclose(f);
	return;
}

void xemNV()	// Chỉ dùng sau khi đọc từ file NV xong
{		
	if (DEM_NV <= 0)
	{
		printf("Khong co nhan vien nao.\n\n");
		return;
	}

	printf("-------DANH SACH NHAN VIEN-------\n\n");
	printf("STT \t Ho va ten \t\t\t Gioi tinh \t Ngay sinh \t\t So CCCD \t\t SDT\n\n");
	for(int i = 0; i < DEM_NV; i++)
	{
		printf("%d.\t", i+1);
		printf("%s \t", ARRAY_NV[i].ten);
		printf("%s \t", ARRAY_NV[i].gt);
		printf("%s \t", ARRAY_NV[i].dob);
		printf("%s \t", ARRAY_NV[i].cccd);
		printf("%s \n", ARRAY_NV[i].sdt);
	}

	printf("\n");
	return;
}

void xem1NV(int vt)
{
	NV * now = &ARRAY_NV[vt];
	printf("Ten: %s\n", now->ten);
	printf("Gioi tinh: %s\n", now->gt);
	printf("Ngay sinh: %s\n", now->dob);
	printf("CCCD: %s\n", now->cccd);
	printf("SDT: %s\n", now->sdt);
}

void luuFileNV(char fileNV[])
{
	FILE *f = fopen(fileNV, "wb");

	for (int i = 0; i < DEM_NV; i++)
		if (strcmp(ARRAY_NV[i].cccd, "-1") != 0)
			fwrite(&ARRAY_NV[i], sizeof(NV), 1, f);

	fclose(f);
	return;
}

void themNV()
{
	NV * now = &ARRAY_NV[DEM_NV];
	printf("Them thong tin nhan vien: \n");

	printf("Ten: ");
	readinput(L_TENNV, " %[^\n]", now->ten);

	printf("Gioi tinh: ");
	readinput(L_GT, " %s", now->gt);

	printf("Ngay sinh: ");
	readinput(L_DOB, " %s", now->dob);

	printf("CCCD: ");
	readinput(L_CCCD, " %s", now->cccd);

	printf("SDT: ");
	readinput(L_SDT, " %s", now->sdt);

	for (int i = 0; i < DEM_NV; i++)
		if ((stricmp (ARRAY_NV[i].ten, now->ten) == 0) &&
			(stricmp (ARRAY_NV[i].gt, now->gt) == 0) &&
			(stricmp (ARRAY_NV[i].dob, now->dob) == 0) &&
			(stricmp (ARRAY_NV[i].cccd, now->cccd) == 0) &&
			(stricmp (ARRAY_NV[i].sdt, now->sdt) == 0))
		{
			printf("\nNhan vien da ton tai. Tiep tuc them?");
			if (Confirmed())	printf("\nThem nhan vien thanh cong.\n");
			else DEM_NV--;
			break;
		}

	DEM_NV++; // Thêm slot cho NV tiếp theo 
	return;
}

void xoasuaNV()
{
	if (DEM_NV <= 0){
		printf("Khong co nhan vien nao de xoa.\n");
		return;
	}
	int vt = 0;

	printf("0. Quay lai\n");
	printf("Nhap vi tri nhan vien muon xoa: ");
	readinput(0, " %d", &vt);

	while (vt < 0 || vt > DEM_NV)
	{
		printf("\nKhong ton tai vi tri. Nhap lai: ");
		readinput(0, " %d", &vt);
	}
	if (vt == 0) return menuNV();

	cls();
	xem1NV(vt-1);

	int option;
	printf("\n1. Xoa nhan vien");
	printf("\n2. Sua thong tin nhan vien");
	printf("\n0. Quay lai");
	printf("\n\nChon chuc nang: ");
	readinput(0, " %d", &option);

	while (option < 0 || option > 2)
	{
		printf("\nKhong ton tai chuc nang. Nhap lai: ");
		readinput(0, " %d", &option);
	}
	if (option == 0) return menuNV();

	switch(option)
	{
		case 1: xoaNV(vt); break;

		case 2: suaNV(vt); break;
	}
	return;
}

void xoaNV(int vt)
{
	NV * now = &ARRAY_NV[vt - 1];

	printf("\nXoa nhan vien?");
	if (Confirmed())
		strcpy(now->cccd, "-1");
	return;
}

void suaNV(int vt)
{
	int option = 0;
	printf("\n1. Ten");
	printf("\n2. Gioi tinh");
	printf("\n3. Ngay sinh");
	printf("\n4. CCCD");
	printf("\n5. SDT");
	printf("\n0. Quay lai");
	printf("\n\nLua chon thong tin can sua: ");
	readinput(0, " %d", &option);

	while (option < 0 || option > 5)
	{
		printf("\nKhong ton tai chuc nang. Nhap lai: ");
		readinput(0, " %d", &option);
	}
	if (option == 0) return menuNV();

	printf("\n");
	NV * now = &ARRAY_NV[vt - 1];

	#define L_INPUT 30
	#define L_TEMP 30
	char input[L_INPUT];
	char temp[L_TEMP];

	printf("\nNhap thong tin sua lai: ");
	readinput(L_INPUT, " %[^\n]", input);

	cls();

	switch(option)
	{
		case 1: 
			strcpy(temp, now->ten);
			strcpy(now->ten, input);
			break;

		case 2:
			strcpy(temp, now->gt);
			strcpy(now->gt, input);
			break;
			
		case 3:
			strcpy(temp, now->dob);
			strcpy(now->dob, input);
			break;

		case 4:
			strcpy(temp, now->cccd);
			strcpy(now->cccd, input);
			break;

		case 5:
			strcpy(temp, now->sdt);
			strcpy(now->sdt, input);
			break;
	};

	xem1NV(vt - 1);

	printf("\nLuu thong tin?");
	if (Confirmed()) return;
	else
		switch(option)
		{
			case 1: strcpy(now->ten, temp); break;

			case 2: strcpy(now->gt, temp); break;

			case 3: strcpy(now->dob, temp); break;

			case 4: strcpy(now->cccd, temp); break;

			case 5: strcpy(now->sdt, temp); break;
		};

	return;
}

void menuNV()
{
	char fileNV[] = "nhanvien.txt";
	int option;
	do
	{
		cls();
		docFileNV(fileNV);	// Đọc trước khi chọn chức năng
		xemNV();
		printf("Quan ly nhan vien\n");
		printf("\n1. Them nhan vien");
		printf("\n2. Xoa/sua nhan vien");
		printf("\n0. Quay lai");
		printf("\nChon chuc nang: ");
		readinput(0, " %d", &option);

		while (option < 0 || option > 2)
		{
			printf("\nKhong ton tai chuc nang. Nhap lai: ");
			readinput(0, " %d", &option);
		}
		if (option == 0) break;

		switch(option)
		{
			case 1: cls(); themNV(); break;

			case 2: cls(); xemNV(); xoasuaNV(); break;
		}
		luuFileNV(fileNV);	// Lưu lại file sau mỗi lần thực hiện xong chức năng

	} while (option != 0);

	return;
}

////////////////////////// QUAN LY SAN PHAM

#define L_TENSP 20

struct sp
{
	char ten[L_TENSP];
	int gia;
};
typedef struct sp SP;

SP ARRAY_SP[1000];
int DEM_SP;		// Chỉ dùng ở trong docFileSP và themSP

void docFileSP(char fileSP[])
{
	FILE *f;

	if ((f = fopen(fileSP, "rb")) == NULL)
	{
		f = fopen(fileSP, "wb");
		printf("File san pham bi loi/ khong ton tai. He thong tao file moi. \n\n");
	}

	DEM_SP = 0;
	while (fread(&ARRAY_SP[DEM_SP], sizeof(SP), 1, f) == 1) DEM_SP++;

	fclose(f);
	return;
}

void xemSP()	// Chỉ dùng sau khi đọc từ file SP xong
{		
	if (DEM_SP <= 0)
	{
		printf("Khong co san pham nao.\n\n");
		return;
	}

	printf("-------DANH SACH SAN PHAM-------\n\n");
	printf("STT \t Ten SP \t\t Gia \n\n");
	for(int i = 0; i < DEM_SP; i++)
	{
		printf("%d.\t", i+1);
		printf("%s \t", ARRAY_SP[i].ten);
		printf("%d.000d\n", ARRAY_SP[i].gia);
	}

	printf("\n");
	return;
}

void xem1SP(int vt)
{
	SP * now = &ARRAY_SP[vt];
	printf("Ten: %s\n", now->ten);
	printf("Gia: %d.000\n", now->gia);
}

void luuFileSP(char fileSP[])
{
	FILE *f = fopen(fileSP, "wb");

	for (int i = 0; i < DEM_SP; i++)
		if (ARRAY_SP[i].gia != -1)
			fwrite(&ARRAY_SP[i], sizeof(SP), 1, f);

	fclose(f);
	return;
}

void themSP()
{
	SP * now = &ARRAY_SP[DEM_SP];
	printf("Them thong tin san pham: \n");

	printf("Ten: ");
	readinput(L_TENSP, " %[^\n]", now->ten);

	printf("Gia (don vi: .000d): ");
	readinput(0, " %d", &now->gia);

	while (now->gia < 0)
	{
		printf("Nhap lai gia (>=0): ");
		readinput(0, " %d", &now->gia);
	}

	for (int i = 0; i < DEM_SP; i++)
		if (stricmp (ARRAY_SP[i].ten, now->ten) == 0)
		{
			printf("\nSan pham da ton tai. Tiep tuc them?");
			if (Confirmed())	printf("\nThem san pham thanh cong.\n");
			else DEM_SP--;
			break;
		}

	DEM_SP++; // Thêm slot cho SP tiếp theo 
	return;
}

void xoasuaSP()
{
	if (DEM_SP <= 0){
		printf("Khong co san pham nao de xoa.\n");
		return;
	}
	int vt = 0;

	printf("0. Quay lai\n");
	printf("Nhap vi tri san pham muon xoa: ");
	readinput(0, " %d", &vt);

	while (vt < 0 || vt > DEM_SP)
	{
		printf("\nKhong ton tai vi tri. Nhap lai: ");
		readinput(0, " %d", &vt);
	}
	if (vt == 0) return menuSP();

	cls();
	xem1SP(vt - 1);

	int option;
	printf("\n1. Xoa san pham");
	printf("\n2. Sua thong tin san pham");
	printf("\n0. Quay lai");
	printf("\n\nChon chuc nang: ");
	readinput(0, " %d", &option);

	while (option < 0 || option > 2)
	{
		printf("\nKhong ton tai chuc nang. Nhap lai: ");
		readinput(0, " %d", &option);
	}
	if (option == 0) return menuSP();

	switch(option)
	{
		case 1: xoaSP(vt); break;

		case 2: suaSP(vt); break;
	}
	return;
}

void xoaSP(int vt)
{
	printf("\nXoa san pham?");
	if (Confirmed()) ARRAY_SP[vt - 1].gia = -1;
	return;
}

void suaSP(int vt)
{
	int option = 0;
	printf("\n1. Ten");
	printf("\n2. Gia");
	printf("\n0. Quay lai");
	printf("\n\nLua chon thong tin can sua: ");
	readinput(0, " %d", &option);

	while (option < 0 || option > 2)
	{
		printf("\nKhong ton tai chuc nang. Nhap lai: ");
		readinput(0, " %d", &option);
	}
	if (option == 0) return menuSP();

	printf("\n");
	SP * now = &ARRAY_SP[vt - 1];

	#define L_INPUT 30
	#define L_TEMP 30
	char input[L_INPUT];
	char temp[L_TEMP];
	int inputgia, tempgia;

	switch(option)
	{
		case 1:
			printf("Ten: ");
			readinput(L_INPUT, " %[^\n]", input);
			strcpy(temp, now->ten);
			strcpy(now->ten, input);
			break;

		case 2:
			printf("Gia (don vi: .000d): ");
			readinput(0, " %d", &inputgia);

			while (inputgia < 0)
			{
				printf("Nhap lai gia (>=0): ");
				readinput(0, " %d", &inputgia);
			}

			tempgia = now->gia;
			now->gia = inputgia;
			break;
	};

	xem1SP(vt - 1);

	printf("\nLuu thong tin?");
	if (Confirmed()) return;
	else
		switch(option)
		{
			case 1: strcpy(now->ten, temp); break;

			case 2: now->gia = tempgia; break;
		};

	return;
}

void sapxepSP()
{
	int ARRAY_SXXP[DEM_SP];
	SP BCKUP_ARRAY[DEM_SP];

	for (int i = 0; i < DEM_SP; i++)
	{
		ARRAY_SXXP[i] = i;
		BCKUP_ARRAY[i] = ARRAY_SP[i];
	}

	for (int i = 0; i < DEM_SP - 1; i++)
	{
		for (int j = i + 1; j < DEM_SP; j++)
		{
			if (stricmp(ARRAY_SP[i].ten, ARRAY_SP[j].ten) > 0)
			{
				int temp = i;
				ARRAY_SXXP[i] = j;
				ARRAY_SXXP[j] = temp;
			}	
		}
		
	}

	for (int i = 0; i < DEM_SP; i++)
		ARRAY_SP[i] = BCKUP_ARRAY[ARRAY_SXXP[i]];

	return;

}

void menuSP()
{
	char fileSP[] = "sanpham.txt";
	int option;
	do
	{
		cls();
		docFileSP(fileSP);	// Đọc trước khi chọn chức năng
		xemSP();
		printf("Quan ly san pham\n");
		printf("\n1. Them san pham");
		printf("\n2. Xoa/sua san pham");
		printf("\n0. Quay lai");
		printf("\nChon chuc nang: ");
		readinput(0, " %d", &option);

		while (option < 0 || option > 2)
		{
			printf("\nKhong ton tai chuc nang. Nhap lai: ");
			readinput(0, " %d", &option);
		}
		if (option == 0) break;

		switch(option)
		{
			case 1: cls(); themSP(); break;

			case 2: cls(); xemSP(); xoasuaSP(); break;
		}
		sapxepSP();
		luuFileSP(fileSP);	// Lưu lại file sau mỗi lần thực hiện xong chức năng

	} while (option != 0);

	return;
}



///////////////////////////
/* DON HANG  LINKED LIST */
///////////////////////////
struct dh
{
	SP sanpham;
	int sl, sugarstatus, icestatus;

	struct dh * next;
};
typedef struct dh DH;

#define HDTIMESIZE 25

struct HoaDon
{
	DH * head;
	DH * last;
	int totalcost;
	int totalpaid;
	int countnode;

	char timestr[HDTIMESIZE];	// "2015-05-15 22:55:13"
};

struct HoaDon DonHangHienTai;
void lammoiDonHangHienTai(){
	DonHangHienTai = (struct HoaDon){
		.head = NULL,
		.last = NULL,
		.countnode = 0,
		.totalcost = 0,
		.totalpaid = -1
	};
	return;
}


// BASIC FUNCTIONS
DH * createNode(DH * current){
	DH * newMon = (DH *)malloc(sizeof * newMon);
	newMon->next = NULL;

	if (current != NULL)
		current->next = newMon;

	newMon->sl = 0;
	newMon->sugarstatus = 0;
	newMon->icestatus = 0;

	return newMon;
}
void addItem(){ 
	DonHangHienTai.last = createNode(DonHangHienTai.last);

	// Khi head chua dc khoi tao
	if (DonHangHienTai.head == NULL)
		DonHangHienTai.head = DonHangHienTai.last;

	return;
}
void removeItem(int pos){
	int count = 1;
	DH * now = (DonHangHienTai.head);
	DH * prev;

	// Head case
	if (pos == 1) {
		(DonHangHienTai.head) = (DonHangHienTai.head)->next;	// Change the original pointer
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
				if (now == (DonHangHienTai.last))
				DonHangHienTai.last = prev;

				prev->next = now->next;
				free(now);
				break;
			}
		}
	}

	return;
}


// INPUT FUNCTIONS
void inputAddItem(){
	addItem();
	DH * now = DonHangHienTai.last;

/*	struct sp * sanpham;
	int sl, sugarstatus, icestatus;
	long gia; */

	int vt = 0;
	xemSP();
	printf("Chon do uong: ");
	readinput(0, " %d", &vt);

	// Check input vi tri
	while (vt < 0 || vt > DEM_SP)
	{
		printf("Khong ton tai vi tri. Nhap lai: ");
		readinput(0, " %d", &vt);
	}

	now->sanpham = ARRAY_SP[vt - 1];

	printf("So luong: ");
	readinput(0, " %d", &now->sl);
	printf("Luong duong: ");
	readinput(0, " %d", &now->sugarstatus);
	printf("Luong da: ");
	readinput(0, " %d", &now->icestatus);

	(DonHangHienTai.countnode)++;
	return;
}

void inputRemoveItem(){
	if (DonHangHienTai.head == NULL){
		return;					// Node ko co gi ca
	}

	int pos = 0;
	printf("Xoa vi tri: ");
	readinput(0, " %d", &pos);

	// Check input vi tri
	while (pos > DonHangHienTai.countnode || pos < 1)
	{
		printf("Khong co. Nhap lai: ");
		readinput(0, " %d", &pos);
	}

	removeItem(pos);
	(DonHangHienTai.countnode)--;
	// Khi xoa het menu
	if (DonHangHienTai.countnode == 0){
		DonHangHienTai.head = NULL;
		DonHangHienTai.last = NULL;
	}

	return;
}

void printThousand(int num){
	if (num < 1000) {
		printf("%d", num);
		return;
	}

	printThousand(num / 1000);
	printf(",%03d", num % 1000);
}

void printCostVND(int space, int num){ // In giá
	char str[20];
	sprintf(str, "%d", num); // Biến đổi số thành string
	int numlen = strlen(str);
	space = space - numlen - (numlen - 1)/3;
	// Minus the length of number & the comma ,
	for(int i = 0; i < space; i++) printf(" ");

	printThousand(num);
	printf(",000d");
}

int billPaid(){
	if (DonHangHienTai.totalpaid > -1)
		return 1;
	else
		return 0;
}

void printDonHangHienTai(){
	DH * now = DonHangHienTai.head;		// A copy of actual head pointer
	int count = 0;
	int tongthanhtoan = 0;
	int tongdh = 0;

	printf("--------------------\n");
	while (now != NULL) {
		count++;
		tongdh = now->sanpham.gia * now->sl;
		tongthanhtoan += tongdh;

		printf("%d.", count);
		printf("\t%-5d", now->sl);
		printf("\t%-20s   ", now->sanpham.ten);
		printCostVND(10, tongdh);
		printf(" | Duong: %-10d", now->sugarstatus);
		printf(" | Da:    %-5d\n", now->icestatus);

		now = now->next;
	}
	DonHangHienTai.totalcost = tongthanhtoan;

	if (count == 0)
	{
		printf("Ko co do uong gi ca.\n");
		printf("--------------------\n");
	}
	else
	{
		printf("--------------------\t\tTong = ");
		printCostVND(10, tongthanhtoan); printf("\n");

		if (billPaid()) {
			printf("%27sKhach tra = ", "");
			printCostVND(10, DonHangHienTai.totalpaid); printf("\n");

			printf("%27sTien thua = ", "");
			printCostVND(10, DonHangHienTai.totalpaid - tongthanhtoan); printf("\n");
		}
	}

	return;
}

void inputThanhToan(){
	int inputpaid = -1;
	printf("\nKhach tra: ");
	readinput(0, " %d", &inputpaid);

	DonHangHienTai.totalpaid = inputpaid;

	return;
}

void inHoaDon();

void mainDH()
{
	int option;
	docFileSP("sanpham.txt");
	lammoiDonHangHienTai();
	do
	{
		cls();
		// Read before function
		printDonHangHienTai();
		printf("\n1. Them do uong");
		printf("\n2. Xoa do uong");
		printf("\n3. Thanh toan");
		if (billPaid()) printf("\n4. In hoa don");
		printf("\n0. Quay lai");
		printf("\nChon chuc nang: ");
		readinput(0, " %d", &option);

		// Check option trong khoang 0-3
		while (option < 0 || option > (3 + billPaid()))
		{
			printf("\nKhong ton tai chuc nang. Nhap lai: ");
			readinput(0, " %d", &option);
		}
		if (option == 0) break;

		// Options case
		switch(option)
		{
			case 1: inputAddItem(); break;

			case 2:  inputRemoveItem(); break;

			case 3: inputThanhToan(); break;

			case 4: if (billPaid()) { inHoaDon(); } else { printf("Chua thanh toan."); } break;

			case 0: break;
		}

	} while (option != 0);

	return;
}



struct HoaDon HDarray[200];	// Monthly
int HDcount = 0;			// Hoa don count
int HDdoanhthu = 0;

void luuHoaDonHienTai(FILE * f){
	fwrite(&DonHangHienTai, sizeof(struct HoaDon), 1, f);
	DH * now = DonHangHienTai.head;

	for(int i = 0; i < DonHangHienTai.countnode; i++){
		fwrite(now, sizeof(DH), 1, f);
		now = now->next;
	}

	return;
}
void docHoaDonHienTai(FILE * f){
	fread(&DonHangHienTai, sizeof(struct HoaDon), 1, f);
	DH * now = NULL;
	DonHangHienTai.head = NULL;
	DonHangHienTai.last = NULL;

	for(int i = 0; i < DonHangHienTai.countnode; i++){
		addItem();	// Auto next
		now = DonHangHienTai.last;
		fread(now, sizeof(DH), 1, f);
	}
}

/*
void luuAllHoaDon(FILE * fileinfo, FILE * filedata){
	fwrite(&HDcount, sizeof(int), 1, fileinfo);

	for(int i = 0; i < HDcount; i++) {
		// Trc khi luu
		DonHangHienTai = HDarray[i];

		// Luu tung hoa don mot
		luuHoaDonHienTai(filedata);
	}

	return;
} */

void docAllHoaDon(FILE * fileinfo, FILE * filedata){
	fread(&HDcount, sizeof(int), 1, fileinfo);
	fread(&HDdoanhthu, sizeof(int), 1, fileinfo);

	for(int i = 0; i < HDcount; i++) {
		// Doc tung hoa don mot
		docHoaDonHienTai(filedata);

		// Sau khi doc
		HDarray[i] = DonHangHienTai;
	}

	return;
}

void luuThem1HoaDon(FILE * fileinfo, FILE * filedata){
	int HDfilecount = 0;
	int HDfiledoanhthu = 0;
	if (fread(&HDfilecount, sizeof(int), 1, fileinfo) == 0) printf("Fail to read file count. ");
	if (fread(&HDfiledoanhthu, sizeof(int), 1, fileinfo) == 0) printf("Fail to read file doanh thu. ");
	printf("\nTong so hoa don = %d", HDfilecount);
	printf("\nTong doanh thu = %d", HDfiledoanhthu);

	rewind(fileinfo);
	HDfilecount++;		// +1
	HDfiledoanhthu += DonHangHienTai.totalcost;
	fwrite(&HDfilecount, sizeof(int), 1, fileinfo);
	fwrite(&HDfiledoanhthu, sizeof(int), 1, fileinfo);
	printf("\nTong so hoa don = %d", HDfilecount);
	printf("\nTong doanh thu = %d", HDfiledoanhthu);

	// Luu them 1 hoa don
	luuHoaDonHienTai(filedata);

	return;
}

void luuThemFileHoaDon(char fileHDinfo[], char fileHDdata[]){
	FILE * f1;
	FILE * f2 = fopen(fileHDdata, "ab");
	if ((f1 = fopen(fileHDinfo, "rb+")) == NULL)
	{
		f1 = fopen(fileHDinfo, "wb+");
		printf("File info bi loi / khong ton tai. He thong tao file moi. \n\n");
	}

	luuThem1HoaDon(f1, f2);

	fclose(f1);
	fclose(f2);
	return;
}

void docFileHoaDon(char fileHDinfo[], char fileHDdata[]){
	FILE * f1;
	FILE * f2;

	if ((f1 = fopen(fileHDinfo, "rb")) == NULL)
	{
		f1 = fopen(fileHDinfo, "wb");
		printf("File info bi loi / khong ton tai. He thong tao file moi. \n\n");
		return;
	}

	if ((f2 = fopen(fileHDdata, "rb")) == NULL)
	{
		f2 = fopen(fileHDdata, "wb");
		printf("File data bi loi / khong ton tai. He thong tao file moi. \n\n");
		return;
	}

	docAllHoaDon(f1, f2);

	fclose(f1);
	fclose(f2);
	return;
}


/*
Nhan vien
>> initDanhSachHoaDon
> Don Hang
> inHoaDon
>> luuThemFileHoaDon

Quan li
>> docAllHoaDon
> Display
*/

int getCurrentMonth(){
	time_t t = time(NULL);
	struct tm *current_time = localtime(&t);
	return current_time->tm_mon + 1;
}

int getCurrentYear()
{
	time_t t = time(NULL);
	struct tm *current_time = localtime(&t);
	return current_time->tm_year;
}

void getTenDanhSachHoaDon(char * fileHDinfo, char * fileHDdata, int month, int year){
	char filename[20];

	sprintf(filename, "hoadon%d%d.txt", month, year);
	strcpy(fileHDdata, filename);

	sprintf(filename, "info%d%d.txt", month, year);
	strcpy(fileHDinfo, filename);

	return;

	/*
	struct HoaDon HDArray[200];	// Monthly
	int HDCount = 0;
	int HDMonth;
	*/
}

void saveTimeHoaDon(struct HoaDon * hoa_don){
	time_t t = time(NULL);
	struct tm *current_time = localtime(&t);
	strftime(hoa_don->timestr, HDTIMESIZE, "%d-%m-%Y %H:%M:%S", current_time);

	return;
}

void inHoaDon(){
	saveTimeHoaDon(&DonHangHienTai);
	// HDarray[HDcount] = DonHangHienTai;
	// HDcount++;

	char fileHDinfo[20];
	char fileHDdata[20];
	getTenDanhSachHoaDon(fileHDinfo, fileHDdata, getCurrentMonth(), getCurrentYear());
	luuThemFileHoaDon(fileHDinfo, fileHDdata);

	printf("\nDA IN HOA DON");
	scanf("%*c");
	return;
}


void quanlidocHoaDon(){
	char fileHDinfo[20];
	char fileHDdata[20];
	int month = 0, year = 0;

	printf("\nXem hoa don nam: ");
	readinput(0, " %d", &year);
	while (year < 1900)
	{
		printf("Nhap lai nam: ");
		readinput(0, " %d", &year);
	}

	printf("\nXem hoa don thang: ");
	readinput(0, " %d", &month);

	// Check input thang
	while (month < 1 || month > 12)
	{
		printf("Nhap lai thang: ");
		readinput(0, " %d", &month);
	}

	getTenDanhSachHoaDon(fileHDinfo, fileHDdata, month, year);
	docFileHoaDon(fileHDinfo, fileHDdata);

	for(int i = 0; i < HDcount; i++) {
		DonHangHienTai = HDarray[i];
		printf("%s\n", DonHangHienTai.timestr);
		printDonHangHienTai();
	}
	printf("\nTong so hoa don = %d", HDcount);
	printf("\nTong doanh thu = %d", HDdoanhthu);

	scanf("%*c");

	return;
}

// info: lưu thêm thông tin khác của tất cả hoá đơn

// Menu lon

void BigMenuQL()
{
	char fileNV[] = "nhanvien.txt";
	char fileSP[] = "sanpham.txt";
	char fileDT[] = "doanhthu.txt";
	int option;

	do {
		cls();
		printf("TAI KHOAN QUAN LY\n");
		printf("\n1. Quan ly nhan vien");
		printf("\n2. Quan ly san pham");
		printf("\n3. Quan ly doanh thu");
		printf("\n4. Xem hoa don");
		printf("\n0: Thoat\n");
		printf("\nChon chuc nang: ");
		readinput(0, " %d", &option);

		// Check option
		while (option < 0 || option > 4)
		{
			printf("\nKhong ton tai chuc nang. Nhap lai: ");
			readinput(0, " %d", &option);
		}

		cls();
		switch(option)
		{
			case 1:  menuNV(fileNV); break;

			case 2: menuSP(); break;
			
			case 3: quanlidocHoaDon(); break;

			case 4: break;

			case 0: printf("\nDang xuat thanh cong. Nhan bat ki de thoat."); getch(); Login();
		}
	} while (option != 0);
}
	
void BigMenuNV()
{	
	int option;

	do {
		cls();
		printf("TAI KHOAN NHAN VIEN\n");
		printf("\n1. Tao don hang moi");
		printf("\n0: Thoat & luu tat ca don hang\n");
		printf("\nChon chuc nang: ");
		readinput(0, " %d", &option);

		// Check option
		while (option < 0 || option > 4)
		{
			printf("\nKhong ton tai chuc nang. Nhap lai: ");
			readinput(0, " %d", &option);
		}

		switch(option)
		{
			case 1: cls(); mainDH(); break;
				
			case 0: printf("\nDang xuat thanh cong. Nhan bat ki de thoat."); getch(); cls(); Login();
		};
	} while (option != 0);


}

// Dang nhap

int LoginStatus(char user[], char pass[])
{
	char ua[] = "admin", pa[] = "123456";
	char uu[] = "user", pu[] = "000000";

	if ((strcmp(user, ua) == 0) && (strcmp(pass, pa) ==0 )) return 1;
	else if ((strcmp(user, uu) == 0) && (strcmp(pass, pu) == 0)) return 2;
	else return 0;
}

void Login()
{
	char user[20], pass[20];
	do
	{
		// cls();
		printf("DANG NHAP HE THONG\n");
		printf("\nNhap ten nguoi dung: ");
		readinput(0, " %s", user);
		printf("\nNhap mat khau: ");
		readinput(0, " %s", pass);
		
		if (LoginStatus(user, pass) == 1) BigMenuQL();
		else if (LoginStatus(user, pass) == 2) BigMenuNV();
		else
		{
			printf("\nThong tin khong dung. Moi nhap lai.");
			getch();
		}

	} while ((LoginStatus(user, pass) == 0));
}

int main()
{
	system("title PHAN MEM QUAN LY QUAN CAFE");
	inputptr = stdin;
	outputptr = stdout;
	
	while (1)
	{
		Login();
		// getch();
	}
}