#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
#include <conio.h>
#include <windows.h>

FILE * inputptr;
FILE * outputptr;

/// FUNCTION LIST ///

void Login();
void BigMenuQL();
void BigMenuNV();

/// Thêm ô nhớ vào dynamic array

void create_LIST_NV();
void addsizeLIST_NV(int n); void add_1_LIST_NV();

void create_LIST_SP();
void addsizeLIST_SP(int n); void add_1_LIST_SP();

/// Quản lý nhân viên ///

void menuNV();

void docFileNV(char fileNV[]);
void xemNV();
void xem1NV(int vt);

void themNV();
void xoasuaNV(); void xoaNV(int vt); void suaNV(int vt);

void luuFileNV(char fileSP[]);

/// Quản lý sản phẩm ///

void menuSP();

void docFileSP(char fileSP[]);
void xemSP();
void xem1SP(int vt);

void themSP();
void xoasuaSP(); void xoaSP(int vt); void suaSP(int vt);

int sosanhSP(const void * SP1, const void * SP2);
void sapxepSP();

void luuFileSP(char fileSP[]);

/// Quản lý doanh thu & hoá đơn ///

/// Đổi mật khẩu ///

/// Tạo đơn hàng ///

/// Các hàm khác ///

/// Kiểm soát nhập đầu vào

#define MAX_LENGTH 100
char buffer[MAX_LENGTH] = { 0 };

void ReadInput(int length, const char * format, void * ptr){
	if (length == 0 || length > MAX_LENGTH) length = MAX_LENGTH;

	fgets(buffer, length, inputptr);

	if(!strchr(buffer, '\n'))
		while(fgetc(inputptr) != '\n');

	sscanf(buffer, format, ptr);
	return;
}

/// Xác nhận

int Confirmed()
{
	int option;
	printf("\t(1. Co / 0. Khong): ");
	ReadInput(0, " %d", &option);

	while (option != 1 && option != 0)
	{
		printf("\nNhap lai: ");
		ReadInput(0, " %d", &option);
	} 

	return option;
}

void cls()
{
	system("cls");
}

#define L_INPUT 30
#define L_TEMP 30

#define L_TENNV 30
#define L_GT 5
#define L_DOB 11
#define L_CCCD 13
#define L_SDT 11

/// QUẢN LÝ NHÂN VIÊN ///

struct nv
{
	char ten[L_TENNV];
	char gt[L_GT];
	char dob[L_DOB];
	char cccd[L_CCCD];
	char sdt[L_SDT];
};
typedef struct nv NV;

NV * LIST_NV;
int DEM_NV;

NV * LIST_NV;
int DEM_NV; // Chỉ dùng ở trong docFileNV và themNV

void addSizeLIST_NV(int n) // Thêm n ô nhớ vào mảng NV
{
	LIST_NV = (NV *) realloc (LIST_NV, sizeof(NV) * (DEM_NV + 1 + n));
	return;
}

void add_1_LIST_NV() // Thêm 1 ô nhớ vào mảng NV
{
	addSizeLIST_NV(1);
	DEM_NV++;
	return;
}

void create_LIST_NV() // Khởi tạo mảng NV
{
	addSizeLIST_NV(0);
	return;
}

void docFileNV(char fileNV[])
{
	FILE * f;

	if ((f = fopen(fileNV, "rb")) == NULL)
	{
		f = fopen(fileNV, "wb");
		printf("File nhan vien bi loi/ khong ton tai. He thong tao file moi.\n\n");
	}

	create_LIST_NV();
	DEM_NV = 0;
	while (fread(LIST_NV + DEM_NV, sizeof(NV), 1, f) == 1) add_1_LIST_NV();

	fclose(f);
	return;
}

void xemNV() // Chỉ dùng sau khi đọc từ file NV xong
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
		printf("%s \t", (LIST_NV + i)->ten);
		printf("%s \t", (LIST_NV + i)->gt);
		printf("%s \t", (LIST_NV + i)->dob);
		printf("%s \t", (LIST_NV + i)->cccd);
		printf("%s \n", (LIST_NV + i)->sdt);
	}

	printf("\n");
	return;
}

void xem1NV(int vt)
{
	NV * now = LIST_NV + vt;
	printf("Ten: %s\n", now->ten);
	printf("Gioi tinh: %s\n", now->gt);
	printf("Ngay sinh: %s\n", now->dob);
	printf("CCCD: %s\n", now->cccd);
	printf("SDT: %s\n", now->sdt);
}

void luuFileNV(char fileNV[])
{
	FILE * f = fopen(fileNV, "wb");

	for (int i = 0; i < DEM_NV; i++)
		if (strcmp((LIST_NV + i)->cccd, "-1") != 0)
			fwrite(LIST_NV + i, sizeof(NV), 1, f);

	fclose(f);
	return;
}

void themNV()
{
	NV * now = LIST_NV + DEM_NV;
	now->ten[0] = '\0';

	printf("Them thong tin nhan vien: \n");

	printf("Ten: ");
	ReadInput(L_TENNV, " %[^\n]", now->ten);

	while (now->ten[0] == '\0')
	{
		printf("\nNhap lai ten: ");
		ReadInput(L_TENNV, " %[^\n]", now->ten);
	}

	printf("Gioi tinh: ");
	ReadInput(L_GT, " %s", now->gt);

	printf("Ngay sinh: ");
	ReadInput(L_DOB, " %s", now->dob);

	printf("CCCD: ");
	ReadInput(L_CCCD, " %s", now->cccd);

	printf("SDT: ");
	ReadInput(L_SDT, " %s", now->sdt);

	for (int i = 0; i < DEM_NV; i++)
		if ((stricmp ((LIST_NV + i)->ten, now->ten) == 0) &&
			(stricmp ((LIST_NV + i)->gt, now->gt) == 0) &&
			(stricmp ((LIST_NV + i)->dob, now->dob) == 0) &&
			(stricmp ((LIST_NV + i)->cccd, now->cccd) == 0) &&
			(stricmp ((LIST_NV + i)->sdt, now->sdt) == 0))
		{
			printf("\nNhan vien da ton tai. Tiep tuc them?");
			if (Confirmed()) printf("\nThem nhan vien thanh cong.\n");
			else DEM_NV--;
			break;
		}

	add_1_LIST_NV(); // Thêm 1 ô nhớ cho NV tiếp theo 
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
	printf("Nhap vi tri nhan vien: ");
	ReadInput(0, " %d", &vt);

	while (vt < 0 || vt > DEM_NV)
	{
		printf("\nKhong ton tai vi tri. Nhap lai: ");
		ReadInput(0, " %d", &vt);
	}
	if (vt == 0) return menuNV();

	cls();
	xem1NV(vt-1);

	int option;
	printf("\n1. Xoa nhan vien");
	printf("\n2. Sua thong tin nhan vien");
	printf("\n0. Quay lai");
	printf("\n\nChon chuc nang: ");
	ReadInput(0, " %d", &option);

	while (option < 0 || option > 2)
	{
		printf("\nKhong ton tai chuc nang. Nhap lai: ");
		ReadInput(0, " %d", &option);
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
	NV * now = LIST_NV + vt - 1;

	printf("\nXoa nhan vien?");
	if (Confirmed()) strcpy(now->cccd, "-1");

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
	ReadInput(0, " %d", &option);

	while (option < 0 || option > 5)
	{
		printf("\nKhong ton tai chuc nang. Nhap lai: ");
		ReadInput(0, " %d", &option);
	}
	if (option == 0) return menuNV();

	printf("\n");
	NV * now = LIST_NV + vt - 1;

	char input[L_INPUT];
	char temp[L_TEMP];

	printf("\nNhap thong tin sua lai: ");
	ReadInput(L_INPUT, " %[^\n]", input);

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
		docFileNV(fileNV);
		
		xemNV();
		printf("Quan ly nhan vien\n");
		printf("\n1. Them nhan vien");
		printf("\n2. Xoa/sua nhan vien");
		printf("\n0. Quay lai");
		printf("\nChon chuc nang: ");
		ReadInput(0, " %d", &option);

		while (option < 0 || option > 2)
		{
			printf("\nKhong ton tai chuc nang. Nhap lai: ");
			ReadInput(0, " %d", &option);
		}
		if (option == 0) break;

		cls();
		switch(option)
		{
			case 1: themNV(); break;

			case 2: xemNV(); xoasuaNV(); break;
		}
		luuFileNV(fileNV); // Lưu lại file sau mỗi lần thực hiện xong chức năng

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

SP * ARRAY_SP;
int DEM_SP;		// Chỉ dùng ở trong docFileSP và themSP

void addSizeARRAY_SP(int n){
	ARRAY_SP = (SP *)realloc(ARRAY_SP, sizeof(SP) * (DEM_SP + n + 1));
	return;
}

void add_1_ARRAY_SP(){
	addSizeARRAY_SP(1);
	DEM_SP++;
	return;
}

void init_ARRAY_SP(){
	addSizeARRAY_SP(0);
	return;
}

void docFileSP(char fileSP[])
{
	FILE *f;

	if ((f = fopen(fileSP, "rb")) == NULL)
	{
		f = fopen(fileSP, "wb");
		printf("File san pham bi loi/ khong ton tai. He thong tao file moi. \n\n");
	}

	init_ARRAY_SP();
	DEM_SP = 0;
	while (fread(&ARRAY_SP[DEM_SP], sizeof(SP), 1, f) == 1) add_1_ARRAY_SP();

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
	now->ten[0] = '\0';
	now->gia = -1;

	printf("Them thong tin san pham: \n");

	printf("Ten: ");
	readinput(L_TENSP, " %[^\n]", now->ten);
	while (now->ten[0] == '\0')
	{
		printf("Nhap lai ten: ");
		readinput(L_TENSP, " %[^\n]", now->ten);
	}

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

	add_1_ARRAY_SP(); // Thêm slot cho SP tiếp theo 
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
	if (vt == 0) return;

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
	if (option == 0) return;

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

#define L_INPUT 30
#define L_TEMP 30

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
	if (option == 0) return;

	printf("\n");
	SP * now = &ARRAY_SP[vt - 1];


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

int compareSP(const void * sp1, const void * sp2)
{
	/*
	int cmp = strcmp(((SP *)sp1)->ten, ((SP *)sp2)->ten);

	if (cmp == 0) return strcmp(((SP *)sp1)->ho, ((SP *)sp2)->ho);
	else return cmp; */
	return strcmp(((SP *)sp1)->ten, ((SP *)sp2)->ten);
}
void sapxepSP()
{
	qsort(ARRAY_SP, DEM_SP, sizeof(SP), compareSP);
	return;
}


void menuSP()
{
	char fileSP[] = "sanpham.txt";
	// init_ARRAY_SP(); docFileSP2
	int option;
	do
	{
		cls();
		docFileSP(fileSP);	// Đọc trước khi chọn chức năng
		xemSP();
		printf("Quan ly san pham\n");
		printf("\n1. Them san pham");
		printf("\n2. Xoa/sua san pham");
		printf("\n3. Sap xep lai san pham");
		printf("\n0. Quay lai");
		printf("\nChon chuc nang: ");
		readinput(0, " %d", &option);

		while (option < 0 || option > 3)
		{
			printf("\nKhong ton tai chuc nang. Nhap lai: ");
			readinput(0, " %d", &option);
		}
		if (option == 0) break;

		switch(option)
		{
			case 1: cls(); themSP(); break;

			case 2: cls(); xemSP(); xoasuaSP(); break;

			case 3: cls(); sapxepSP(); break;
		}
		//sapxepSP();
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
	while (now->sl < 1)
	{
		printf("Phai > 0. Nhap lai: ");
		readinput(0, " %d", &now->sl);
	}
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
	int isneg = num < 0;
	num = abs(num);

	sprintf(str, "%d", num); // Biến đổi số thành string
	int numlen = strlen(str);
	space = space - numlen - (numlen - 1)/3 - isneg;
	// Minus the length of number & the comma ,
	for(int i = 0; i < space; i++) printf(" ");
	if (isneg) printf("-");

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
		printf("\n3. Thanh toan & In hoa don");
		printf("\n0. Quay lai");
		printf("\nChon chuc nang: ");
		readinput(0, " %d", &option);

		// Check option trong khoang 0-3
		while (option < 0 || option > 3)
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

			case 3: inputThanhToan(); cls(); printDonHangHienTai(); inHoaDon(); option = 0; break;

			case 0: break;
		}

	} while (option != 0);

	return;
}

//


struct HoaDon * HDarray;	// Monthly
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

	HDarray = (struct HoaDon *)realloc(HDarray, sizeof(struct HoaDon) * (HDcount + 1));

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
	printf("\nTruoc do: ");
	printf("\nHoa don = %d", HDfilecount);
	printf("\nDoanh thu = %d", HDfiledoanhthu);

	rewind(fileinfo);
	HDfilecount++;		// +1
	HDfiledoanhthu += DonHangHienTai.totalcost;
	fwrite(&HDfilecount, sizeof(int), 1, fileinfo);
	fwrite(&HDfiledoanhthu, sizeof(int), 1, fileinfo);
	printf("\nHien tai: ");
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

void getCurrentMonthYear(int * pmonth, int * pyear){
	time_t t = time(NULL);
	struct tm *current_time = localtime(&t);

	(*pmonth) = current_time->tm_mon + 1;
	(*pyear) = current_time->tm_year;
	return; 
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

void getTenDanhSachHoaDonThangNay(char * fileHDinfo, char * fileHDdata){
	int month, year;
	getCurrentMonthYear(&month, &year);
	getTenDanhSachHoaDon(fileHDinfo, fileHDdata, month, year);
	return;
}

void saveTimeHoaDon(struct HoaDon * hoa_don){
	time_t t = time(NULL);
	struct tm *current_time = localtime(&t);
	strftime(hoa_don->timestr, HDTIMESIZE, "%d-%m-%Y %H:%M:%S", current_time);

	return;
}

void inHoaDon(){
	saveTimeHoaDon(&DonHangHienTai);

	char fileHDinfo[20];
	char fileHDdata[20];

	getTenDanhSachHoaDonThangNay(fileHDinfo, fileHDdata);
	luuThemFileHoaDon(fileHDinfo, fileHDdata);

	printf("\n\nDA IN HOA DON");
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

	year -= 1900;
	printf("year = %d", year);

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

	printf("\n----------------------------------------");

	for(int i = 0; i < HDcount; i++) {
		DonHangHienTai = HDarray[i];
		printf("\nHoa don #%d: %s\n", i+1, DonHangHienTai.timestr);
		printDonHangHienTai();
	}

	printf("\nTong so hoa don = %d", HDcount);
	printf("\nTong doanh thu = "); printCostVND(10, HDdoanhthu);

	scanf("%*c");

	return;
}

// info: lưu thêm thông tin khác của tất cả hoá đơn

// Menu lon

///////////////////////////
//// QUAN LI DOANH THU ////
///////////////////////////


void tinhdoanhthu(){
	char fileHDinfo[20];
	char fileHDdata[20];

	getTenDanhSachHoaDonThangNay(fileHDinfo, fileHDdata);
	docFileHoaDon(fileHDinfo, fileHDdata);

	int tienDien, tienNuoc, tienNguyenLieu;

	printf("Nhap tien dien: ");
	readinput(0, " %d", &tienDien);
	while (tienDien < 0)
	{
		printf("Nhap lai tien dien (>= 0): ");
		readinput(0, " %d", &tienDien);
	}

	printf("Nhap tien nuoc: ");
	readinput(0, " %d", &tienNuoc);
	while (tienNuoc < 0)
	{
		printf("Nhap lai tien nuoc (>= 0): ");
		readinput(0, " %d", &tienNuoc);
	}

	printf("Nhap tien nguyen lieu: ");
	readinput(0, " %d", &tienNguyenLieu);
	while (tienNguyenLieu < 0)
	{
		printf("Nhap lai tien nguyen lieu (>= 0): ");
		readinput(0, " %d", &tienNguyenLieu);
	}

	int temp = 0 - tienDien - tienNuoc - tienNguyenLieu;
	printf("\nTong chi phi\t= "); printCostVND(10, temp);
	printf("\nTong thu\t= "); printCostVND(10, HDdoanhthu);
	temp += HDdoanhthu;
	printf("\nDoanh thu thang\t= "); printCostVND(10, temp);

	scanf("%*c");

	return;
}





//////////////////////////
//// QUAN LI MAT KHAU ////
//////////////////////////

#define USER_LEN 8
#define PASS_LEN 10
char filePS[] = "p.bin";
char ua[] = "admin";	char pa[PASS_LEN] = "123456";	// Default
char uu[] = "user";		char pu[PASS_LEN] = "000000";
						char hashp[PASS_LEN];

void hashpass(char * hashedstr, char * normalstr){
	int nlen = strlen(normalstr);
	for (int i = 0; i < nlen; i++) {
		hashedstr[i] = 255 - normalstr[i];
	}
	return;
}
void unhashpass(char * hashedstr, char * normalstr){
	int nlen = strlen(normalstr);
	for (int i = 0; i < nlen; i++) {
		normalstr[i] = 255 - hashedstr[i];
	}
	return;
}

void luuFilePass(){
	FILE * f = fopen(filePS, "wb");

	hashpass(hashp, pa); fwrite(hashp, PASS_LEN, 1, f);
	hashpass(hashp, pu); fwrite(hashp, PASS_LEN, 1, f);

	fclose(f);
	return;
}
void docFilePass(){
	FILE * f;
	if ((f = fopen(filePS, "rb")) == NULL)
	{
		printf("File password not found. Default password set. \n\n");
		luuFilePass(filePS);
		return;
	}

	// If successfully read
	fread(hashp, PASS_LEN, 1, f); unhashpass(hashp, pa);
	fread(hashp, PASS_LEN, 1, f); unhashpass(hashp, pu);

	fclose(f);
	return;
}
void inputMatKhau(char ten[], char * passptr){
	char tempass[PASS_LEN];
	char tempcheck[PASS_LEN];	

	while(1) {
		printf("\nNhap mat khau %s moi (%d ki tu): ", ten, PASS_LEN);
		readinput(PASS_LEN, " %s", tempass);
		printf("Nhap lai mat khau: ");
		readinput(PASS_LEN, " %s", tempcheck);
		if (strcmp(tempass, tempcheck) == 0)
			break;
		else
			printf("Mat khau khong khop. Nhap lai.\n");
	}

	strcpy(passptr, tempcheck);
	luuFilePass();
	printf("Doi mat khau thanh cong.");
	return;
}

void doiMatKhau(){
	cls();
	printf("\n1. Quan li (admin)");
	printf("\n2. Nhan vien (user)");
	printf("\nTai khoan? ");

	int option = 0;
	readinput(0, " %d", &option);
	// Check option
	while (option < 1 || option > 2)
	{
		printf("\nKhong ton tai. Nhap lai: ");
		readinput(0, " %d", &option);
	}

	switch(option){
		case 1: inputMatKhau("admin", pa); break;
		case 2: inputMatKhau("user", pu); break;
	}

	return;
}

//////////////////////////
//// QUAN LI MAT KHAU ////
//////////////////////////



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
		printf("\n5. Doi mat khau");
		printf("\n0: Thoat\n");
		printf("\nChon chuc nang: ");
		readinput(0, " %d", &option);

		// Check option
		while (option < 0 || option > 5)
		{
			printf("\nKhong ton tai chuc nang. Nhap lai: ");
			readinput(0, " %d", &option);
		}

		cls();
		switch(option)
		{
			case 1: menuNV(fileNV); break;

			case 2: menuSP(); break;
			
			case 3: tinhdoanhthu(); break;

			case 4: quanlidocHoaDon(); break;

			case 5: doiMatKhau(); break;

			case 0: printf("\nDang xuat thanh cong. Nhan bat ki de thoat."); getch(); Login();
		}
	} while (option != 0);
}
	
void BigMenuNV()
{	
	char fileSP[] = "sanpham.txt";
	int option;

	do {
		cls();
		docFileSP(fileSP);	// Đọc trước khi chọn chức năng
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



///////////////////
//// DANG NHAP ////
///////////////////

int LoginStatus(char user[], char pass[])
{
	if ((strcmp(user, ua) == 0) && (strcmp(pass, pa) ==0 )) return 1;
	else if ((strcmp(user, uu) == 0) && (strcmp(pass, pu) == 0)) return 2;
	else return 0;
}

void Login()
{
	char user[20], pass[20];
	char filePass[] = "p.bin";
	docFilePass(filePass);
	do
	{
		// cls();
		printf("DANG NHAP HE THONG\n");
		printf("\nNhap ten nguoi dung: ");
		readinput(USER_LEN, " %s", user);
		printf("\nNhap mat khau: ");
		readinput(PASS_LEN, " %s", pass);
		
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