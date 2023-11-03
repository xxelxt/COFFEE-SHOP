#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>

FILE * inputptr;
FILE * outputptr;

#define AC_BLACK "\x1b[30m"
#define AC_RED "\x1b[31m"
#define AC_GREEN "\x1b[32m"
#define AC_YELLOW "\x1b[33m"
#define AC_WHITE "\x1b[37m"
#define AC_NORMAL "\x1b[m"

/* PROGRAM MAP */
/* IMPORTANT NOTE: Mở file để đọc và ghi vào array / lưu file rồi đóng luôn. Thao tác trên array. */

void Login(); void BigMenuQL(); void BigMenuNV();

/* DYNAMIC ARRAY FUNCTIONS */

void create_LIST_NV();
void addsizeLIST_NV(int n); void add_1_LIST_NV();

void create_LIST_SP();
void addsizeLIST_SP(int n); void add_1_LIST_SP();

/* QUẢN LÝ NHÂN VIÊN */

void menuNV();

void docFileNV(char fileNV[]);

void titleprintNV(); void printOneNVOnly(int vt); void xemNV();

void luuFileNV(char fileSP[]);

void themNV();
void xoasuaNV(); void xoaNV(int vt); void suaNV(int vt);

void findNoticeNV(int count); void timNV();

void timNVtheoten();
int timNVtheoGT_Choice(char * choice); void timNVtheoGT();
int timNVtheoCCCD_Choice(char * choice); void timNVtheoCCCD();
int timNVtheoSDT_Choice(char * choice); void timNVtheoSDT();

/* QUẢN LÝ SẢN PHẨM */

void menuSP();

void docFileSP(char fileSP[]);

void titleprintSP(); void printOneSPOnly(int vt); void xemSP();

void luuFileSP(char fileSP[]);

void themSP();
void xoasuaSP(); void xoaSP(int vt); void suaSP(int vt);

int sosanhSP(const void * SP1, const void * SP2);
void sapxepSP();

void findNoticeSP(int count);
void timSP(); void timSPtheoten(); void timSPtrengia(); void timSPduoigia();

/* TẠO ĐƠN HÀNG */

void menuDH();

void resetHD();

void addItem(); void removeItem();

void themItem(); void xoaItem();

void inHD(); void inputThanhToan(); void inHDdaTT();

/* QUẢN LÝ HOÁ ĐƠN */

void QLdocHD();

void docHDHienTai(FILE * f);
void docFileHD(char fileHDinfo[], char fileHDdata[]);
void docAllHD(FILE * fileinfo, FILE * filedata);

void luuHDHienTai(FILE * f);
void luuThemFileHD(char fileHDinfo[], char fileHDdata[]);
void luuThem1HD(FILE * fileinfo, FILE * filedata);

void getTenDanhSachHD(char * fileHDinfo, char * fileHDdata, int month, int year);
void getTenDanhSachHDThang(char * fileHDinfo, char * fileHDdata);

void inHDdaTT();

int inputYear(int year); int inputMonth(int month);

/* TÍNH DOANH SỐ */

void tinhDS();

/* MẬT KHẨU */

void hashpass(char * hashedstr, char * normalstr);
void unhashpass(char * hashedstr, char * normalstr);

void luuFilePass(); void docFilePass();

void doiMatKhau(); void inputMatKhau();

/* CÁC HÀM KHÁC */

int billPaid();
void printThousand(int num);
void printCostVND(int space, int num);

void getCurrentMonthYear(int * p_month, int * p_year);

/* KIỂM SOÁT NHẬP ĐẦU VÀO */

#define MAX_LENGTH 100
char buffer[MAX_LENGTH] = { 0 };

void ReadInput(int length, const char * format, void * ptr)
{
	if (length == 0 || length > MAX_LENGTH) length = MAX_LENGTH;

	fgets(buffer, length, inputptr);

	if(!strchr(buffer, '\n'))
		while(fgetc(inputptr) != '\n');

	sscanf(buffer, format, ptr);
	return;
}

/* MẶC ĐỊNH ĐỘ DÀI GIÁ TRỊ NHẬP */

#define L_TENNV 30
#define L_GT 5
#define L_DOB 11
#define L_CCCD 13
#define L_SDT 11

#define L_TENSP 30

#define L_INPUT 30
#define L_TEMP 30

/* KIỂM TRA NHẬP ĐẦU VÀO */

int checkNumInfo(char * c_info, int length)
{
	if (stricmp(c_info, "-") == 0) return 1;

	if (strlen(c_info) != length) return 0;
	else
	{
		for (int i = 0; i < strlen(c_info); i++)
			if (!isdigit(c_info[i])) return 0;

		return 1;
	}
}

int checkNum(char * info, int length)
{	
	for (int i = 0; i < strlen(info); i++)
		if (!isdigit(info[i])) return 0;

	return 1;
}

int checkGT(char * c_gt)
{
	if (stricmp(c_gt, "-") == 0) return 1;

	if ((stricmp(c_gt, "Nam") != 0) && (stricmp(c_gt, "Nu") != 0)) return 0;
		else return 1;
}

/* XÁC NHẬN */

int Confirmed()
{
	int option;
	printf("\t(1. Co / 0. Khong): ");
	ReadInput(0, " %d", &option);

	while (option != 1 && option != 0)
	{
		printf("\n%3s Nhap lai: ", "");
		ReadInput(0, " %d", &option);
	} 

	return option;
}

/* THOÁT CHỨC NĂNG */

int checkOUT(char * c_info)
{
	if (stricmp(c_info, "0") == 0) return 1; else return 0;
}

void printReturn()
{
	printf("%3s Nhan 0 de quay lai.\n", "");
}

void cls()
{
	system("cls");
}

/* QUẢN LÝ NHÂN VIÊN */

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
int DEM_NV; // Chỉ thay đổi ở trong docFileNV và themNV

void init_1_NV(NV * now) // Khởi tạo thông tin mặc định
{
	now->ten[0] = '\0'; // Necessary
	strcpy(now->gt, "-");
	strcpy(now->dob, "-");
	strcpy(now->cccd, "-");
	strcpy(now->sdt, "-");
}

void addSizeLIST_NV(int n) // Thêm n ô nhớ vào mảng NV
{
	LIST_NV = (NV *) realloc (LIST_NV, sizeof(NV) * (DEM_NV + 1 + n)); // Always allocate 1 more than needed
	return;
}

void create_LIST_NV() // Khởi tạo mảng NV gồm 1 ô nhớ đầu tiên
{
	addSizeLIST_NV(0);
	init_1_NV(LIST_NV);

	DEM_NV = 0;
	return;
}

void add_1_LIST_NV() // Thêm 1 ô nhớ vào mảng NV
{
	addSizeLIST_NV(1);
	init_1_NV(LIST_NV + DEM_NV + 1);

	DEM_NV++;
	return;
}

void docFileNV(char fileNV[])
{
	FILE * f;
	if ((f = fopen(fileNV, "rb")) == NULL)

	{
		f = fopen(fileNV, "wb");
		printf("\n%3s%3s [!] %sFile nhan vien bi loi/ khong ton tai. He thong tao file moi.\n", "", AC_RED, AC_NORMAL);
	}

	create_LIST_NV();
	while (fread(LIST_NV + DEM_NV, sizeof(NV), 1, f) == 1) add_1_LIST_NV();

	fclose(f);
	return;
}

void titleprintNV()
{
	printf("\n%3s STT %s | Ho va ten %21s | Gioi tinh %2s | Ngay sinh %4s | So CCCD %6s | SDT\n", "", "", "", "", "", "");
	printf("%3s _____________________________________________________________________________________________________\n\n", "");
	return;
}

void printOneNVLine(int num, NV * chosen) // In thông tin theo bảng
{
	printf("%3s %-3d ", "", num);
	printf(" | %-30s ", chosen->ten);
	printf(" | %-11s ", chosen->gt);
	printf(" | %-13s ", chosen->dob);
	printf(" | %-13s ", chosen->cccd);
	printf(" | %s \n", chosen->sdt);
	return;
}

void printOneNVOnly(int vt) // In thông tin theo dòng, chỉ dùng trong xoá và sửa
{
	NV * now = LIST_NV + vt;
	printf("\n%3s THONG TIN NHAN VIEN\n", "");
	printf("%3s -------------------\n\n", "");
	printf("%3s Ten: %s\n", "", now->ten);
	printf("%3s Gioi tinh: %s\n", "", now->gt);
	printf("%3s Ngay sinh: %s\n", "", now->dob);
	printf("%3s CCCD: %s\n", "", now->cccd);
	printf("%3s SDT: %s", "", now->sdt);

	printf("\n\n%3s -------------------------\n", "");
}

void xemNV() // Chỉ dùng sau khi đọc từ fileNV xong
{		
	printf("\n%40s DANH SACH NHAN VIEN\n", "");
	printf("%40s -------------------\n", "");

	if (DEM_NV <= 0)
	{
		printf("%3s Khong co nhan vien nao.\n\n", "");
		printf("%3s -------------------------\n", "");
		return;
	}

	titleprintNV();
	for (int i = 0; i < DEM_NV; i++)
		printOneNVLine(i+1, LIST_NV + i);

	printf("\n%3s -------------------------\n", "");
	return;
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
	xemNV();

	NV * now = LIST_NV + DEM_NV;

	printf("\n"); printReturn();
	printf("\n%3s Nhan Enter de bo qua thong tin.\n", "");
	printf("\n%3s THEM THONG TIN NHAN VIEN\n", "");

	printf("\n%3s Ten: ", "");
	ReadInput(L_TENNV, " %[^\n]", now->ten);

	while (now->ten[0] == '\0')
	{
		printf("%3s Nhap lai ten: ", "");
		ReadInput(L_TENNV, " %[^\n]", now->ten);
	}

	if (checkOUT(now->ten)) return;

	printf("\n%3s Gioi tinh: ", "");
	ReadInput(L_GT, " %s", now->gt);

	if (checkOUT(now->gt)) return;

	while (!checkGT(now->gt))
	{
		strcpy(now->gt, "-");
		printf("%3s Nhap lai gioi tinh: ", "");
		ReadInput(L_GT, " %s", now->gt);

		if (checkOUT(now->gt)) return;
	}

	printf("\n%3s Ngay sinh: ", "");
	ReadInput(L_DOB, " %s", now->dob);

	if (checkOUT(now->dob)) return;

	printf("\n%3s CCCD: ", "");
	ReadInput(L_CCCD, " %s", now->cccd);

	if (checkOUT(now->cccd)) return;

	while (!checkNumInfo(now->cccd, L_CCCD - 1))
	{
		strcpy(now->cccd, "-");
		printf("%3s Nhap lai CCCD gom 12 so: ", "");
		ReadInput(L_CCCD, " %s", now->cccd);

		if (checkOUT(now->cccd)) return;
	}

	printf("\n%3s SDT: ", "");
	ReadInput(L_SDT, " %s", now->sdt);

	if (checkOUT(now->sdt)) return;

	while (!checkNumInfo(now->sdt, L_SDT - 1))
	{
		strcpy(now->sdt, "-");
		printf("%3s Nhap lai SDT (10 so): ", "");
		ReadInput(L_SDT, " %s", now->sdt);

		if (checkOUT(now->sdt)) return;
	}

	int DUPLICATE_CHECK = -1;
	for (int i = 0; i < DEM_NV; i++)
		if ((stricmp ((LIST_NV + i)->ten, now->ten) == 0) &&
			(stricmp ((LIST_NV + i)->gt, now->gt) == 0) &&
			(stricmp ((LIST_NV + i)->dob, now->dob) == 0) &&
			(stricmp ((LIST_NV + i)->cccd, now->cccd) == 0) &&
			(stricmp ((LIST_NV + i)->sdt, now->sdt) == 0))
		{
			DUPLICATE_CHECK = 1;
			printf("\n%3s%s [!] %sNhan vien da ton tai. Tiep tuc them?", "", AC_YELLOW, AC_NORMAL);
			if (Confirmed())
			{
				printf("\n%3s%s [i] %sThem nhan vien thanh cong.\n", "", AC_GREEN, AC_NORMAL);
				getch();
			}
			else DEM_NV--;
			break;
		}

	if (DUPLICATE_CHECK == -1) printf("\n%3s%s [i] %sThem nhan vien thanh cong.\n", "", AC_GREEN, AC_NORMAL);
	getch();

	add_1_LIST_NV(); // Thêm 1 ô nhớ cho NV tiếp theo
	return;
}

void xoasuaNV()
{
	if (DEM_NV <= 0)
	{
		printf("\n%3s Khong co nhan vien nao de xoa.\n", "");
		return;
	}
	int vt = -1;

	printf("\n");
	printReturn();
	printf("\n%3s Nhap vi tri nhan vien: ", "");
	ReadInput(0, " %d", &vt);

	while (vt < 0 || vt > DEM_NV)
	{
		printf("\n%3s%s [!] %sKhong ton tai vi tri. Nhap lai: ", "", AC_YELLOW, AC_NORMAL);
		ReadInput(0, " %d", &vt);
	}
	if (vt == 0) return;

	cls();
	printOneNVOnly(vt-1);

	int option = -1;
	printf("\n%3s 1. Xoa nhan vien", "");
	printf("\n%3s 2. Sua thong tin nhan vien", "");
	printf("\n%3s 0. Quay lai", "");
	printf("\n\n%3s Nhan so de chon chuc nang: ", "");
	ReadInput(0, " %d", &option);

	while (option < 0 || option > 2)
	{
		printf("\n%3s%s [!] %sKhong ton tai chuc nang. Nhap lai: ", "", AC_YELLOW, AC_NORMAL);
		ReadInput(0, " %d", &option);
	}
	if (option == 0) return;

	switch(option)
	{
		case 1: xoaNV(vt); break;

		case 2: cls(); suaNV(vt); break;
	}
	return;
}

void xoaNV(int vt)
{
	NV * now = LIST_NV + vt - 1;

	printf("\n%3s Xoa nhan vien?", "");
	if (Confirmed())
	{
		strcpy(now->cccd, "-1");
		printf("\n%3s%s [i] %sXoa nhan vien thanh cong.", "", AC_GREEN, AC_NORMAL);
		getch();
	}

	return;
}

void xoatheoten()
{
	char f_ten[L_TENNV] = "\0";

	printf("\n%3s XOA NHAN VIEN THEO TEN\n", "");
	printf("%3s ----------------------\n", "");
	printReturn();

	printf("\n%3s Nhap ten nhan vien can xoa: ", "");
	ReadInput(L_TENNV, " %[^\n]", f_ten);

	while (f_ten[0] == '\0')
	{
		printf("\n%3s Nhap lai thong tin: ", "");
		ReadInput(L_TENNV, " %[^\n]", f_ten);
	}

	if (checkOUT(f_ten)) return;

	int count = 0;

	for (int i = 0; i < DEM_NV; i++)
		if (stricmp (((LIST_NV + i)->ten), f_ten) == 0)
		{
			count++;
			NV * now = LIST_NV + i;
			if (count == 1)
			{
				printf("\n%3s ----------------------------\n", "");
				titleprintNV();
			}
			printOneNVLine(count, now);
			strcpy(now->cccd, "-1");
		}

	printf("\n%3s ----------------------------\n", "");
	if (count == 0) printf("\n%3s Khong co nhan vien ten %s", "", f_ten);
		else printf("\n%3s Da xoa %d nhan vien", "", count);

	getch();
	return;
}

void suaNV(int vt)
{
	int option = -1;
	printOneNVOnly(vt-1);

	printf("\n%3s 1. Ten", "");
	printf("\n%3s 2. Gioi tinh", "");
	printf("\n%3s 3. Ngay sinh", "");
	printf("\n%3s 4. CCCD", "");
	printf("\n%3s 5. SDT", "");
	printf("\n%3s 0. Quay lai", "");
	printf("\n\n%3s Lua chon thong tin can sua: ", "");
	ReadInput(0, " %d", &option);

	while (option < 0 || option > 5)
	{
		printf("\n%3s%s [!] %sKhong ton tai lua chon. Nhap lai: ", "", AC_YELLOW, AC_NORMAL);
		ReadInput(0, " %d", &option);
	}
	if (option == 0) return;

	NV * now = LIST_NV + vt - 1;

	char input[L_INPUT] = "-";
	char temp[L_TEMP];

	printf("\n%3s -----------------\n", "");
	printReturn();
	if (option != 1) printf("\n%3s Nhan Enter de xoa thong tin cu.\n", "");
	
	printf("\n%3s Nhap thong tin sua lai: ", "");
	ReadInput(L_INPUT, " %[^\n]", input);

	if (checkOUT(input)) return;

	switch(option)
	{
		case 1: 
			while (input[0] == '-')
			{
				printf("%3s Nhap lai ten: ", "");
				ReadInput(L_INPUT, " %[^\n]", input);

				if (checkOUT(input)) return;
			}
			strcpy(temp, now->ten);
			strcpy(now->ten, input);
			break;

		case 2:
			while (!checkGT(input))
			{
				printf("%3s Nhap lai gioi tinh: ", "");
				ReadInput(L_INPUT, " %[^\n]", input);

				if (checkOUT(input)) return;
			}
			strcpy(temp, now->gt);
			strcpy(now->gt, input);
			break;
			
		case 3:
			strcpy(temp, now->dob);
			strcpy(now->dob, input);
			break;

		case 4:
			while (!checkNumInfo(input, L_CCCD - 1))
			{
				strcpy(input, "-");
				printf("%3s Nhap lai so CCCD: ", "");
				ReadInput(L_INPUT, " %[^\n]", input);

				if (checkOUT(input)) return;
			}
			strcpy(temp, now->cccd);
			strcpy(now->cccd, input);
			break;

		case 5:
			while (!checkNumInfo(input, L_SDT - 1))
			{
				strcpy(input, "-");
				printf("%3s Nhap lai SDT: ", "");
				ReadInput(L_INPUT, " %[^\n]", input);

				if (checkOUT(input)) return;
			}
			strcpy(temp, now->sdt);
			strcpy(now->sdt, input);
			break;
	};

	cls();
	printOneNVOnly(vt - 1);

	printf("\n%3s Luu thong tin?", "");
	if (Confirmed())
	{
		printf("\n%3s%s [i] %sSua thong tin thanh cong.", "", AC_GREEN, AC_NORMAL);
		getch();
		return;
	}
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

void timNV()
{
	if (DEM_NV <= 0)
	{
		printf("\n%3s Khong co nhan vien nao de tim kiem.\n", "");
		return;
	}

	int option = -1;
	printf("\n%3s TIM NHAN VIEN THEO THONG TIN\n", "");
	printf("%3s ---------------------------\n", "");

	printf("\n%3s 1. Theo ten", "");
	printf("\n%3s 2. Theo gioi tinh", "");
	printf("\n%3s 3. Theo CCCD", "");
	printf("\n%3s 4. Theo SDT", "");
	printf("\n%3s 0. Quay lai", "");
	printf("\n\n%3s Nhan so de chon chuc nang: ", "");
	ReadInput(0, " %d", &option);

	while (option < 0 || option > 4)
	{
		printf("\n%3s%s [!] %sKhong ton tai chuc nang. Nhap lai: ", "", AC_YELLOW, AC_NORMAL);
		ReadInput(0, " %d", &option);
	}
	if (option == 0) return;
	
	cls();
	switch(option)
	{
		case 1: timNVtheoten(); break;

		case 2: timNVtheoGT(); break;

		case 3: timNVtheoCCCD(); break;

		case 4: timNVtheoSDT(); break;
	}
	return;
}

void findNoticeNV(int count)
{
	if (count == 0) printf("\n%3s Khong tim thay nhan vien.", "");
	else printf("\n%3s Tim thay %d nhan vien.", "", count);

	return;
}

void timNVtheoten()
{
	char f_ten[L_TEMP] = "\0";

	printf("\n%3s TIM NHAN VIEN THEO TEN\n", "");
	printf("%3s ----------------------\n", "");

	printReturn();
	printf("\n%3s Nhap ten nhan vien: ", "");
	ReadInput(L_TEMP, " %[^\n]", f_ten);

	while (f_ten[0] == '\0')
	{
		printf("\n%3s Nhap lai thong tin: ", "");
		ReadInput(L_TEMP, " %[^\n]", f_ten);
	}

	if (checkOUT(f_ten)) return;

	int count = 0;
	for (int i = 0; i < DEM_NV; i++)
		if (stricmp ((LIST_NV + i)->ten, f_ten) == 0)
		{
			count++;
			if (count == 1) 
			{
				printf("\n%3s ----------------------\n", "");
				titleprintNV();
			}
			printOneNVLine(count, LIST_NV + i);
		}

	printf("\n%3s ----------------------\n", "");
	findNoticeNV(count);

	getch();

	return;
}

int timNVtheoGT_Choice(char * choice)
{
	int count = 0;
	for (int i = 0; i < DEM_NV; i++)
	{
		if (stricmp ((LIST_NV + i)->gt, choice) == 0)
		{
			count++;
			if (count == 1) 
			{
				printf("\n%3s ----------------------------\n", "");
				titleprintNV();
			}
			printOneNVLine(count, LIST_NV + i);
		}
	}
	return count;
}

void timNVtheoGT()
{
	char f_GT[L_GT];
	int option = -1;

	printf("\n%3s TIM NHAN VIEN THEO GIOI TINH\n", "");
	printf("%3s ----------------------------\n", "");

	printf("\n%3s 1. Nam", "");
	printf("\n%3s 2. Nu", "");
	printf("\n%3s 3. Nhan vien chua nhap gioi tinh", "");
	printf("\n%3s 0. Quay lai", "");
	printf("\n\n%3s Nhan so de chon chuc nang: ", "");
	ReadInput(0, " %d", &option);

	while (option < 0 || option > 3)
	{
		printf("\n%3s%s [!] %sKhong ton tai chuc nang. Nhap lai: ", "", AC_YELLOW, AC_NORMAL);
		ReadInput(0, " %d", &option);
	}
	if (option == 0) return;

	int count = 0;
	switch(option)
	{
		case 1: count = timNVtheoGT_Choice("Nam"); break;

		case 2: count = timNVtheoGT_Choice("Nu"); break;
				
		case 3: count = timNVtheoGT_Choice("-"); break;
	}

	printf("\n%3s ----------------------------\n", "");
	findNoticeNV(count);

	getch();

	return;
}

int timNVtheoCCCD_Choice(char * choice)
{
	int count = 0;
	for (int i = 0; i < DEM_NV; i++)
	{
		if (stricmp ((LIST_NV + i)->cccd, choice) == 0)
		{
			count++;
			if (count == 1) 
			{
				printf("\n%3s ----------------------------\n", "");
				titleprintNV();
			}
			printOneNVLine(count, LIST_NV + i);
		}
	}
	return count;
}

void timNVtheoCCCD()
{
	char f_cccd[L_TEMP] = "\0";

	printf("\n%3s TIM NHAN VIEN THEO CCCD\n", "");
	printf("%3s -----------------------\n", "");
	printReturn();

	printf("\n%3s Nhap so CCCD hoac nhap 1 de tim nhan vien chua nhap thong tin: ", "");
	ReadInput(L_TEMP, " %s", f_cccd);

	while (f_cccd[0] == '\0')
	{
		printf("\n%3s Nhap lai thong tin: ", "");
		ReadInput(L_TEMP, " %s", f_cccd);
	}

	if (checkOUT(f_cccd)) return;

	int option;
	if (stricmp(f_cccd, "1") == 0) option = 1; else option = 2;
	int count = 0;

	switch(option)
	{
		case 1: count = timNVtheoCCCD_Choice("-"); break;

		case 2: count = timNVtheoCCCD_Choice(f_cccd); break;
	}

	printf("\n%3s -----------------------\n", "");
	findNoticeNV(count);

	getch();

	return;
}

int timNVtheoSDT_Choice(char * choice)
{
	int count = 0;
	for (int i = 0; i < DEM_NV; i++)
	{
		if (stricmp ((LIST_NV + i)->sdt, choice) == 0)
		{
			count++;
			if (count == 1) 
			{
				printf("\n%3s ----------------------------\n", "");
				titleprintNV();
			}
			printOneNVLine(count, LIST_NV + i);
		}
	}
	return count;
}

void timNVtheoSDT()
{
	char f_sdt[L_TEMP] = "\0";

	printf("\n%3s TIM NHAN VIEN THEO SDT\n", "");
	printf("%3s ----------------------\n", "");
	printReturn();

	printf("\n%3s Nhap SDT hoac nhap 1 de tim nhan vien chua nhap thong tin: ", "");
	ReadInput(L_TEMP, " %s", f_sdt);

	while (f_sdt[0] == '\0')
	{
		printf("\n%3s Nhap lai thong tin: ", "");
		ReadInput(L_TEMP, " %s", f_sdt);
	}

	if (checkOUT(f_sdt)) return;

	int option;
	if (stricmp(f_sdt, "1") == 0) option = 1; else option = 2;
	int count = 0;

	switch(option)
	{
		case 1: count = timNVtheoSDT_Choice("-"); break;

		case 2: count = timNVtheoSDT_Choice(f_sdt); break;
	}

	printf("\n%3s ----------------------\n", "");
	findNoticeNV(count);
	
	getch();

	return;
}

void menuNV()
{
	char fileNV[] = "nhanvien.bin";
	int option;
	do
	{
		cls();
		docFileNV(fileNV); // Đọc hết trước khi chọn chức năng
		option = -1;

		xemNV();
		printf("\n%3s 1. Them nhan vien", "");
		printf("\n%3s 2. Xoa/sua nhan vien", "");
		printf("\n%3s 3. Tim kiem nhan vien", "");
		printf("\n%3s 4. Xoa theo ten", "");
		printf("\n%3s 0. Quay lai", "");
		printf("\n\n%3s Nhan so de chon chuc nang: ", "");
		ReadInput(0, " %d", &option);

		while (option < 0 || option > 4)
		{
			printf("\n%3s%s [!] %sKhong ton tai chuc nang. Nhap lai: ", "", AC_YELLOW, AC_NORMAL);
			ReadInput(0, " %d", &option);
		}
		if (option == 0) break;

		cls();
		switch(option)
		{
			case 1: themNV(); break;

			case 2: xemNV(); xoasuaNV(); break;

			case 3: timNV(); break;

			case 4: xoatheoten(); break;

		}
		luuFileNV(fileNV); // Lưu lại file và đóng sau mỗi lần thực hiện xong chức năng

	} while (option != 0);

	return;
}

/* QUẢN LÝ SẢN PHẨM */

struct sp
{
	char ten[L_TENSP];
	int gia;
};
typedef struct sp SP;

SP * LIST_SP;
int DEM_SP;	// Chỉ dùng ở trong docFileSP và themSP

void init_1_SP(SP * now) // Khởi tạo thông tin mặc định
{
	now->ten[0] = '\0';	// Necessary
	now->gia = -1;
}

void addSizeLIST_SP(int n)  // Thêm n ô nhớ vào mảng SP
{
	LIST_SP = (SP *) realloc (LIST_SP, sizeof(SP) * (DEM_SP + 1 + n));
	return;
}

void create_LIST_SP() // Khởi tạo mảng SP gồm 1 ô nhớ đầu tiên
{ 
	addSizeLIST_SP(0);
	init_1_SP(LIST_SP);
	DEM_SP = 0;
	return;
}

void add_1_LIST_SP() // Thêm 1 ô nhớ vào mảng SP
{
	addSizeLIST_SP(1);
	init_1_SP(LIST_SP + DEM_SP + 1);
	DEM_SP++;
	return;
}

void docFileSP(char fileSP[])
{
	FILE *f;

	if ((f = fopen(fileSP, "rb")) == NULL)
	{
		f = fopen(fileSP, "wb");
		printf("\n%3s%3s [!] %sFile san pham bi loi/ khong ton tai. He thong tao file moi.\n", "", AC_RED, AC_NORMAL);
	}

	create_LIST_SP();
	while (fread(LIST_SP + DEM_SP, sizeof(SP), 1, f) == 1) add_1_LIST_SP();

	fclose(f);
	return;
}

void titleprintSP()
{
	printf("\n%3s STT %s | Ten SP %24s | Gia \n", "", "", "");
	printf("%3s ____________________________________________________\n\n", "");
	return;
}

void printOneSPLine(int num, SP * chosen) // In thông tin theo bảng
{
	printf("%3s %-3d ", "", num);
	printf(" | %-31s ", chosen->ten);
	printCostVND(7, chosen->gia);
	printf("\n");
	return;
}

void printOneSPOnly(int vt) // In thông tin theo dòng
{
	SP * now = LIST_SP + vt;
	printf("\n%3s THONG TIN SAN PHAM\n", "");
	printf("%3s ------------------\n\n", "");
	printf("%3s Ten: %s\n", "", now->ten);
	//printf("%3s Gia: %d.000", "", now->gia);
	printf("%3s Gia: ", "");
	printCostVND(0, now->gia);

	printf("\n\n%3s -------------------------\n", "");
}

void xemSP() // Chỉ dùng sau khi đọc từ fileSP xong
{		
	printf("\n%20s DANH SACH SAN PHAM\n", "");
	printf("%20s ------------------\n", "");

	if (DEM_SP <= 0)
	{
		printf("\n%3s Khong co san pham nao.\n\n", "");
		printf("%3s -------------------------\n", "");
		return;
	}

	titleprintSP();
	for (int i = 0; i < DEM_SP; i++)
		printOneSPLine(i+1, LIST_SP + i);

	printf("\n%3s -------------------------\n", "");
	return;
}

void luuFileSP(char fileSP[])
{
	FILE *f = fopen(fileSP, "wb");

	for (int i = 0; i < DEM_SP; i++)
		if ((LIST_SP + i)->gia != -1)
			fwrite(LIST_SP + i, sizeof(SP), 1, f);

	fclose(f);
	return;
}

void themSP()
{
	xemSP();

	SP * now = LIST_SP + DEM_SP;

	printf("\n"); printReturn();
	printf("\n%3s Nhan Enter de bo qua thong tin.\n", "");
	printf("\n%3s THEM THONG TIN SAN PHAM\n", "");

	printf("\n%3s Ten: ", "");
	ReadInput(L_TENSP, " %[^\n]", now->ten);

	while (now->ten[0] == '\0')
	{
		printf("%3s Nhap lai ten: ", "");
		ReadInput(L_TENSP, " %[^\n]", now->ten);
	}

	if (checkOUT(now->ten)) return;

	for (int i = 0; i < DEM_SP; i++)
	{
		if (stricmp((LIST_SP + i)->ten, now->ten) == 0)
		{
			printf("\n%3s San pham da ton tai. Tiep tuc them?", "");
			if (!Confirmed())
				return;	// Don't enter price (stays default at -1 and get deleted)
		}
	}

	printf("\n%3s Gia (don vi: .000d): ", "");
	ReadInput(0, " %d", &now->gia);

	while (now->gia < 0)
	{
		printf("%3s Nhap lai gia (>=0): ", "");
		ReadInput(0, " %d", &now->gia);
	}

	add_1_LIST_SP(); // Thêm slot cho SP tiếp theo 

	printf("\n%3s%s [i] %sThem san pham thanh cong. ", "", AC_GREEN, AC_NORMAL);
	getch();
	return;
}

void xoasuaSP()
{
	if (DEM_SP <= 0)
	{
		printf("\n%3s Khong co san pham nao de xoa.\n", "");
		return;
	}
	int vt = -1;

	printf("\n");
	printReturn();
	printf("\n%3s Nhap vi tri san pham: ", "");
	ReadInput(0, " %d", &vt);

	while (vt < 0 || vt > DEM_SP)
	{
		printf("\n%3s%s [!] %sKhong ton tai vi tri. Nhap lai: ", "", AC_YELLOW, AC_NORMAL);
		ReadInput(0, " %d", &vt);
	}
	if (vt == 0) return;

	cls();
	printOneSPOnly(vt - 1);

	int option;
	printf("\n%3s 1. Xoa san pham", "");
	printf("\n%3s 2. Sua thong tin san pham", "");
	printf("\n%3s 0. Quay lai", "");
	printf("\n\n%3s Chon chuc nang: ", "");
	ReadInput(0, " %d", &option);

	while (option < 0 || option > 2)
	{
		printf("\n%3s%s [!] %sKhong ton tai chuc nang. Nhap lai: ", "", AC_YELLOW, AC_NORMAL);
		ReadInput(0, " %d", &option);
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
	printf("\n%3s Xoa san pham?", "");
	if (Confirmed()) 
	{
		(LIST_SP + vt - 1)->gia = -1;
		printf("\n%3s%s [i] %sXoa san pham thanh cong.", "", AC_GREEN, AC_NORMAL);
		getch();
	}

	return;
}

void suaSP(int vt)
{
	int option = -1;
	printf("\n%3s 1. Ten", "");
	printf("\n%3s 2. Gia", "");
	printf("\n%3s 0. Quay lai", "");
	printf("\n\n%3s Lua chon thong tin can sua: ", "");
	ReadInput(0, " %d", &option);

	while (option < 0 || option > 2)
	{
		printf("\n%3s%s [!] %sKhong ton tai lua chon. Nhap lai: ", "", AC_YELLOW, AC_NORMAL);
		ReadInput(0, " %d", &option);
	}
	if (option == 0) return;

	SP * now = LIST_SP + vt - 1;

	char input[L_INPUT] = "-";
	char temp[L_TEMP];
	int input_gia = -1, temp_gia;

	printf("\n%3s -----------------\n", "");

	switch(option)
	{
		case 1:
			printReturn();

			printf("\n%3s Ten: ", "");
			ReadInput(L_INPUT, " %[^\n]", input);
			if (checkOUT(input)) return;

			while (input[0] == '-')
			{
				printf("%3s Nhap lai ten: ", "");
				ReadInput(L_INPUT, " %[^\n]", input);

				if (checkOUT(input)) return;
			}

			strcpy(temp, now->ten);
			strcpy(now->ten, input);
			break;

		case 2:
			printf("\n%3s Gia (don vi: .000d): ", "");
			ReadInput(0, " %d", &input_gia);

			while (input_gia < 0)
			{
				printf("\n%3s Nhap lai gia (>=0): ", "");
				ReadInput(0, " %d", &input_gia);
			}

			temp_gia = now->gia;
			now->gia = input_gia;
			break;
	};

	cls();
	printOneSPOnly(vt - 1);

	printf("\n%3s Luu thong tin?", "");
	if (Confirmed())
	{
		printf("\n%3s%s [i] %sSua thong tin thanh cong.", "", AC_GREEN, AC_NORMAL);
		getch();
		return;
	}
	else
		switch(option)
		{
			case 1: strcpy(now->ten, temp); break;

			case 2: now->gia = temp_gia; break;
		};

	return;
}

int sosanhSP(const void * SP1, const void * SP2) // Hàm trả về KQ SS trên SP dùng trên qsort
{
	int name_cmp = strcmp(((SP *)SP1)->ten, ((SP *)SP2)->ten);

	if (name_cmp == 0)
	{
		int price_cmp = ((SP *)SP1)->gia - ((SP *)SP2)->gia;
		return price_cmp;
	}
	else return name_cmp;

	/*
	int cmp = strcmp(((SP *)sp1)->ten, ((SP *)sp2)->ten);

	if (cmp == 0) return strcmp(((SP *)sp1)->ho, ((SP *)sp2)->ho);
	else return cmp;
	*/
}

void sapxepSP()
{
	qsort(LIST_SP, DEM_SP, sizeof(SP), sosanhSP); // Không dùng bubble sort, thay vào đó dùng qsort
	return;
}

void timSP()
{
	if (DEM_SP <= 0)
	{
		printf("\n%3s Khong co san pham nao de tim kiem.\n", "");
		return;
	}

	int option = -1;
	printf("\n%3s TIM SAN PHAM THEO THONG TIN\n", "");
	printf("%3s --------------------------\n", "");

	printf("\n%3s 1. Theo ten", "");
	printf("\n%3s 2. Tren muc gia", "");
	printf("\n%3s 3. Duoi muc gia", "");
	printf("\n%3s 0. Quay lai", "");
	printf("\n\n%3s Nhan so de chon chuc nang: ", "");
	ReadInput(0, " %d", &option);

	while (option < 0 || option > 3)
	{
		printf("\n%3s%s [!] %sKhong ton tai chuc nang. Nhap lai: ", "", AC_YELLOW, AC_NORMAL);
		ReadInput(0, " %d", &option);
	}
	if (option == 0) return;
	
	cls();
	switch(option)
	{
		case 1: timSPtheoten(); break;

		case 2: timSPtrengia(); break;

		case 3: timSPduoigia(); break;

	}
	return;
}

void findNoticeSP(int count)
{
	if (count == 0) printf("\n%3s Khong tim thay san pham.", "");
	else printf("\n%3s Tim thay %d san pham.", "", count);

	return;
}

void timSPtheoten()
{
	char f_ten[L_TEMP] = "\0";

	printf("\n%3s TIM SAN PHAM THEO TEN\n", "");
	printf("%3s ---------------------\n", "");
	printReturn();

	printf("\n%3s Nhap ten san pham: ", "");
	ReadInput(L_TEMP, " %[^\n]", f_ten);

	while (f_ten[0] == '\0')
	{
		printf("\n%3s Nhap lai thong tin: ", "");
		ReadInput(L_TEMP, " %[^\n]", f_ten);
	}

	if (checkOUT(f_ten)) return;

	int count = 0;
	for (int i = 0; i < DEM_SP; i++)
		if (stricmp ((LIST_SP + i)->ten, f_ten) == 0)
		{
			count++;
			if (count == 1) 
			{
				printf("\n%3s ---------------------\n", "");
				titleprintSP();
			}
			printOneSPLine(count, LIST_SP + i);
		}

	printf("\n%3s ---------------------\n", "");
	findNoticeSP(count);

	getch();

	return;
}

void timSPtrengia()
{
	int f_gia = -1;

	printf("\n%3s TIM SAN PHAM TREN MUC GIA\n", "");
	printf("%3s -------------------------\n", "");

	printReturn();
	printf("\n%3s Tim san pham co muc gia > (.000d): ", "");
	ReadInput(0, " %d", &f_gia);

	while (f_gia < 0)
	{
		printf("%3s Nhap lai gia (>=0): ", "");
		ReadInput(0, " %d", &f_gia);
	}

	int count = 0;
	for (int i = 0; i < DEM_SP; i++)
		if ((LIST_SP + i)->gia > f_gia)
		{
			count++;
			if (count == 1) 
			{
				printf("\n%3s -------------------------\n", "");
				titleprintSP();
			}
			printOneSPLine(count, LIST_SP + i);
		} 

	printf("\n%3s -------------------------\n", "");
	findNoticeSP(count);

	getch();

	return;
}

void timSPduoigia()
{
	int f_gia = -1;

	printf("\n%3s TIM SAN PHAM DUOI MUC GIA\n", "");
	printf("%3s -------------------------\n", "");

	printReturn();
	printf("\n%3s Tim san pham co muc gia < (.000d): ", "");
	ReadInput(0, " %d", &f_gia);

	while (f_gia < 0)
	{
		printf("%3s Nhap lai gia (>=0): ", "");
		ReadInput(0, " %d", &f_gia);
	}

	int count = 0;
	for (int i = 0; i < DEM_SP; i++)
		if ((LIST_SP + i)->gia < f_gia)
		{
			count++;
			if (count == 1) 
			{
				printf("\n%3s -------------------------\n", "");
				titleprintSP();
			}
			printOneSPLine(count, LIST_SP + i);
		} 

	printf("\n%3s -------------------------\n", "");
	findNoticeSP(count);

	getch();

	return;
}

void menuSP()
{
	char fileSP[] = "sanpham.bin";
	int option;
	do
	{
		cls();
		docFileSP(fileSP); // Đọc hết trước khi chọn chức năng
		option = -1;

		xemSP();
		printf("\n%3s 1. Them san pham", "");
		printf("\n%3s 2. Xoa/sua san pham", "");
		printf("\n%3s 3. Tim kiem san pham", "");
		printf("\n%3s 0. Quay lai", "");
		printf("\n\n%3s Nhan so de chon chuc nang: ", "");
		ReadInput(0, " %d", &option);

		while (option < 0 || option > 3)
		{
			printf("\n%3s%s [!] %sKhong ton tai chuc nang. Nhap lai: ", "", AC_YELLOW, AC_NORMAL);
			ReadInput(0, " %d", &option);
		}
		if (option == 0) break;

		cls();
		switch(option)
		{
			case 1: themSP(); sapxepSP(); break; // Sau khi thêm sẽ sắp xếp luôn theo alphabet

			case 2: xemSP(); xoasuaSP(); break;

			case 3: timSP(); break;
		}
		luuFileSP(fileSP);	// Lưu lại file và đóng sau mỗi lần thực hiện xong chức năng

	} while (option != 0);

	return;
}

/* TẠO ĐƠN HÀNG */

struct item
{
	SP sanpham;
	int sl, sugar, ice;

	struct item * next;
};
typedef struct item ITEM;

#define L_TIME 25

struct hd
{
	ITEM * head;
	ITEM * last;
	int TOTAL_COST;
	int TOTAL_PAID;
	int COUNT_NODE;

	char time_str[L_TIME]; // "2003-10-01 12:34:56"
};
typedef struct hd HD;

HD NEW_HD;

void resetHD()
{
	NEW_HD.head = NULL;
	NEW_HD.last = NULL;
	NEW_HD.COUNT_NODE = 0;
	NEW_HD.TOTAL_COST = 0;
	NEW_HD.TOTAL_PAID = -1;

	return;
}

/* Chức năng cơ bản của DSLK */

ITEM * createNode(ITEM * current) // Tạo node
{
	ITEM * newItem = (ITEM *) malloc (sizeof * newItem);
	newItem->next = NULL;

	if (current != NULL)
		current->next = newItem;

	newItem->sl = 0;
	newItem->sugar = 0;
	newItem->ice = 0;

	return newItem;
}

void addItem() // Thêm node vào cuối
{ 
	NEW_HD.last = createNode(NEW_HD.last);

	if (NEW_HD.head == NULL) // Khi danh sách chưa được khởi tạo
		NEW_HD.head = NEW_HD.last;

	return;
}

void removeItem(int pos) // Xoá node
{
	int count = 1;
	ITEM * now = NEW_HD.head;
	ITEM * prev;

	// Xoá item vị trí đầu tiên
	if (pos == 1)
	{
		NEW_HD.head = (NEW_HD.head)->next;
		free(now);
	}

	// nếu không phải vị trí đầu
	else {
		while (now->next != NULL)
		{
			prev = now;
			now = now->next;
			count++;

			if (count == pos)
			{
				if (now == NEW_HD.last) NEW_HD.last = prev;
				prev->next = now->next;
				free(now);
				break;
			}
		}
	}
	return;
}

/* Thêm / xoá item */

void themItem()
{
	addItem(); // Tạo & thêm node vào cuối linked list
	ITEM * now = NEW_HD.last;

	int vt = -1;
	xemSP();
	printf("\n%3s Chon item: ", "");
	ReadInput(0, " %d", &vt);

	while (vt < 0 || vt > DEM_SP)
	{
		printf("\n%3s%s [!] %sKhong ton tai lua chon. Nhap lai: ", "", AC_YELLOW, AC_NORMAL);
		ReadInput(0, " %d", &vt);
	}

	now->sanpham = *(LIST_SP + vt - 1);

	printf("\n%3s So luong: ", "");
	ReadInput(0, " %d", &now->sl);

	while (now->sl <= 0)
	{
		printf("%3s Nhap lai so luong (> 0): ", "");
		ReadInput(0, " %d", &now->sl);
	}

	printf("\n%3s Luong duong: ", "");
	ReadInput(0, " %d", &now->sugar);

	while (now->sugar < 0)
	{
		printf("%3s Nhap lai luong duong (>= 0): ", "");
		ReadInput(0, " %d", &now->sugar);
	}

	printf("\n%3s Luong da: ", "");
	ReadInput(0, " %d", &now->ice);

	(NEW_HD.COUNT_NODE)++;
	return;
}

void xoaItem()
{
	if (NEW_HD.head == NULL) return;

	int pos = -1;
	printf("\n%3s -------------------------\n", "");
	printReturn();
	printf("\n%3s Xoa item o vi tri: ", "");
	ReadInput(0, " %d", &pos);

	while (pos > NEW_HD.COUNT_NODE || pos < 0)
	{
		printf("\n%3s%s [!] %sKhong ton tai vi tri. Nhap lai: ", "", AC_YELLOW, AC_NORMAL);
		ReadInput(0, " %d", &pos);
	}
	if (pos == 0) return;

	removeItem(pos); // Xoá node
	(NEW_HD.COUNT_NODE)--;
 
	if (NEW_HD.COUNT_NODE == 0) // Nếu đã xoá hết item trong đơn hàng
	{
		NEW_HD.head = NULL;
		NEW_HD.last = NULL;
	}

	return;
}

int billPaid() // Kiểm tra đã chọn thanh toán hay chưa
{
	if (NEW_HD.TOTAL_PAID > -1) return 1;
	else return 0;
}

void printThousand(int num) // In tiền theo hàng nghìn
{
	if (num < 1000)
	{
		printf("%d", num);
		return;
	}

	printThousand(num / 1000);
	printf(".%03d", num % 1000);
}

void printCostVND(int space, int num) // In giá
{
	char str[25]; // Giới hạn long long int là 1.8x10^19
	int negativecheck = num < 0;
	num = abs(num);

	sprintf(str, "%d", num); // Chuyển số thành string

	if (space > 0)
	{
		int numlen = strlen(str);
		space = space - numlen - (numlen - 1)/3 - negativecheck;
		// Minus the length of number & the comma ,
		for (int i = 0; i < space; i++) printf(" ");
	}

	if (negativecheck) printf("-");

	printThousand(num);
	printf(",000d");
}

void inHD()
{
	ITEM * now = NEW_HD.head;
	int count = 0;
	int TotalItemPrice = 0;
	int TongTT = 0;

	printf("\n");
	while (now != NULL)
	{
		count++;
		now = now->next;
	}

	if (count == 0)
	{
		printf("%3s San sang tao don hang moi.\n", "");
		printf("%3s --------------------------\n", "");
	}
	else
	{
		count = 0; now = NEW_HD.head;
		printf("\n%3s STT %5s Ten item %24s SL %5s Thanh tien \n", "", "", "", "");
		printf("%3s ________________________________________________________________\n\n", "");
		while (now != NULL)
		{
			count++;
	
			TotalItemPrice = now->sanpham.gia * now->sl;
			TongTT += TotalItemPrice;

			printf("%3s %d. %7s", "", count, "");
			printf("%-34s", now->sanpham.ten);
			printf("%-4d", now->sl);
			printCostVND(10, TotalItemPrice);
			printf(" | Duong: %-10d", now->sugar);
			printf(" | Da:    %-5d\n", now->ice);

			now = now->next;
		}
		NEW_HD.TOTAL_COST = TongTT;

		printf("\n%13s ------------------------------ Tong = ", "");
		printCostVND(10, TongTT); printf("\n");

		if (billPaid())
		{
			printf("%40sKhach tra = ", "");
			printCostVND(10, NEW_HD.TOTAL_PAID); printf("\n");

			printf("%40sTien thua = ", "");
			printCostVND(10, NEW_HD.TOTAL_PAID - TongTT); printf("\n");
		}
	}

	return;
}

void inputThanhToan()
{
	int inputPaid = -1;
	printf("\n%3s Khach tra (.000d): ", "");
	ReadInput(0, " %d", &inputPaid);

	while (inputPaid < NEW_HD.TOTAL_COST)
	{
		printf("\n%3s Nhap lai so tien khach tra: ", "");
		ReadInput(0, " %d", &inputPaid);
	}

	NEW_HD.TOTAL_PAID = inputPaid;

	return;
}

void inHDdaTT(); // Ở đây chỉ dùng để thông báo đã in bill

void menuDH()
{
	int option;
	docFileSP("sanpham.bin"); // Đọc hết sản phẩm trước khi chọn chức năng
	resetHD();
	do
	{
		cls();
		inHD();
		printf("\n%3s 1. Them item", "");
		if (NEW_HD.COUNT_NODE != 0)
		{
			printf("\n%3s 2. Xoa item", "");
			printf("\n%3s 3. Thanh toan", "");
		}
		printf("\n%3s 0. Quay lai", "");
		printf("\n\n%3s Nhan so de chon chuc nang: ", "");
		ReadInput(0, " %d", &option);

		while (option < 0 || option > 3)
		{
			printf("\n%3s%s [!] %sKhong ton tai chuc nang. Nhap lai: ", "", AC_YELLOW, AC_NORMAL);
			ReadInput(0, " %d", &option);
		}
		if (option == 0) break;

		switch(option)
		{
			case 1: cls(); themItem(); break;

			case 2: xoaItem(); break;

			case 3: inputThanhToan(); cls(); inHD(); inHDdaTT(); option = 0; break;

			case 0: break;
		}

	} while (option != 0);

	return;
}

/* QUẢN LÝ HOÁ ĐƠN */

HD * LIST_HD; // Để đọc hoá đơn theo tháng
int DEM_HD = 0;
int REVENUE_HD = 0;

void docHDHienTai(FILE * f)
{
	fread(&NEW_HD, sizeof(HD), 1, f);
	ITEM * now = NULL;
	NEW_HD.head = NULL;
	NEW_HD.last = NULL;

	for (int i = 0; i < NEW_HD.COUNT_NODE; i++)
	{
		addItem(); // Auto next
		now = NEW_HD.last;
		fread(now, sizeof(ITEM), 1, f);
	}
}

void docFileHD(char fileHDinfo[], char fileHDdata[])
{
	FILE * f1;
	FILE * f2;

	if ((f1 = fopen(fileHDinfo, "rb")) == NULL)
	{
		f1 = fopen(fileHDinfo, "wb");
		printf("\n%3s%3s [!] %sFile info %s bi loi/ khong ton tai. He thong tao file moi.\n", "", AC_RED, AC_NORMAL, fileHDinfo);
		return;
	}

	if ((f2 = fopen(fileHDdata, "rb")) == NULL)
	{
		f2 = fopen(fileHDdata, "wb");
		printf("\n%3s%3s [!] %sFile data %s bi loi/ khong ton tai. He thong tao file moi.\n", "", AC_RED, AC_NORMAL, fileHDdata);
		return;
	}

	docAllHD(f1, f2);

	fclose(f1);
	fclose(f2);
	return;
}

void docAllHD(FILE * fileinfo, FILE * filedata)
{
	fread(&DEM_HD, sizeof(int), 1, fileinfo);
	fread(&REVENUE_HD, sizeof(int), 1, fileinfo);

	LIST_HD = (HD *) realloc (LIST_HD, sizeof(HD) * (DEM_HD + 1)); // Allocate 1 more than needed

	for (int i = 0; i < DEM_HD; i++)
	{
		docHDHienTai(filedata); // Đọc từng hoá đơn một
		LIST_HD[i] = NEW_HD; // Sau khi đọc xong
	}

	return;
}

void luuHDHienTai(FILE * f)
{
	fwrite(&NEW_HD, sizeof(HD), 1, f);
	ITEM * now = NEW_HD.head;

	for (int i = 0; i < NEW_HD.COUNT_NODE; i++)
	{
		fwrite(now, sizeof(ITEM), 1, f);
		now = now->next;
	}

	return;
}

void luuThemFileHD(char fileHDinfo[], char fileHDdata[])
{
	FILE * f1;
	FILE * f2 = fopen(fileHDdata, "ab");

	if ((f1 = fopen(fileHDinfo, "rb+")) == NULL)
	{
		f1 = fopen(fileHDinfo, "wb+");
		// printf("\n%3s%3s [!] %sFile info bi loi/ khong ton tai. He thong tao file moi.\n", "", AC_RED, AC_NORMAL);
	}

	luuThem1HD(f1, f2);

	fclose(f1);
	fclose(f2);
	return;
}

void luuThem1HD(FILE * fileinfo, FILE * filedata)
{
	int COUNT_HDNUM = 0;
	int COUNT_DT = 0;

	if (fread(&COUNT_HDNUM, sizeof(int), 1, fileinfo) == 0)
		printf("\n%3s%3s [!] %sBo dem so hoa don bi loi. \n%7s Neu day khong phai hoa don dau tien trong thang, vui long bao quan ly.\n", "", AC_RED, AC_NORMAL, "");

	if (fread(&COUNT_DT, sizeof(int), 1, fileinfo) == 0)
		printf("\n%3s%3s [!] %sBo dem doanh thu bi loi. \n%7s Neu day khong phai hoa don dau tien trong thang, vui long bao quan ly.\n", "", AC_RED, AC_NORMAL, "");

	rewind(fileinfo);

	COUNT_HDNUM++;
	COUNT_DT += NEW_HD.TOTAL_COST;

	fwrite(&COUNT_HDNUM, sizeof(int), 1, fileinfo);
	fwrite(&COUNT_DT, sizeof(int), 1, fileinfo);

	luuHDHienTai(filedata);

	return;
}

void getCurrentMonthYear(int * p_month, int * p_year) // Lấy thời gian hiện tại
{
	time_t t = time(NULL);
	struct tm * current_time = localtime(&t);

	(*p_month) = current_time->tm_mon + 1;
	(*p_year) = current_time->tm_year + 1900;
	return; 
}

void getTenDanhSachHD(char * fileHDinfo, char * fileHDdata, int month, int year)
{
	char filename[15];

	sprintf(filename, "HD_%d_%d.bin", month, year);
	strcpy(fileHDdata, filename);

	sprintf(filename, "info_%d_%d.bin", month, year);
	strcpy(fileHDinfo, filename);

	return;
}

void getTenDanhSachHDThang(char * fileHDinfo, char * fileHDdata)
{
	int month, year;
	getCurrentMonthYear(&month, &year);
	getTenDanhSachHD(fileHDinfo, fileHDdata, month, year);
	return;
}

void saveTimeHD(HD * hoadon)
{
	time_t t = time(NULL);
	struct tm * current_time = localtime(&t);
	strftime(hoadon->time_str, L_TIME, "%d-%m-%Y %H:%M:%S", current_time);

	return;
}

void inHDdaTT()
{
	saveTimeHD(&NEW_HD);

	char fileHDinfo[20];
	char fileHDdata[20];

	getTenDanhSachHDThang(fileHDinfo, fileHDdata);
	luuThemFileHD(fileHDinfo, fileHDdata);

	printf("\n%3s%s [i] %sDa xuat hoa don.", "", AC_GREEN, AC_NORMAL);
	getch();
	return;
}

int inputYear(int year)
{
	printf("\n%3s Nam: ", "");
	ReadInput(0, " %d", &year);

	while (year < 1900) // Bộ đếm bắt đầu từ năm 1900, tương đương số 0
	{
		printf("Nhap lai nam: ");
		ReadInput(0, " %d", &year);
	}

	return year;
}

int inputMonth(int month)
{
	printf("\n%3s Thang: ", "");
	ReadInput(0, " %d", &month);

	while (month < 0 || month > 12)
	{
		printf("%3s Nhap lai thang: ", "");
		ReadInput(0, " %d", &month);
	}

	return month;
}

void QLdocHD()
{
	char fileHDinfo[20];
	char fileHDdata[20];

	printf("\n%3s XEM HOA DON\n", "");
	printf("%3s -----------\n", "");

	int year = inputYear(year);
	int month = inputMonth(month);

	getTenDanhSachHD(fileHDinfo, fileHDdata, month, year);
	docFileHD(fileHDinfo, fileHDdata);

	printf("\n%3s ----------------------------------------\n", "");

	for (int i = 0; i < DEM_HD; i++)
	{
		NEW_HD = LIST_HD[i];
		if (NEW_HD.COUNT_NODE != 0)
		{
			printf("\n%3s Hoa don #%d: %s", "", i+1, NEW_HD.time_str);
			inHD(); printf("\n");
		}
	}

	printf("\n%3s Tong so hoa don = %d", "", DEM_HD);
	printf("\n%3s Tong doanh thu = ", ""); printCostVND(0, REVENUE_HD);

	getch();

	return;
}

/* TÍNH DOANH SỐ */

void tinhDS()
{
	char fileHDinfo[20];
	char fileHDdata[20];

	printf("\n%3s TINH DOANH SO THANG\n", "");
	printf("%3s -------------------\n", "");

	int year = inputYear(year);
	int month = inputMonth(month);

	getTenDanhSachHD(fileHDinfo, fileHDdata, month, year);
	docFileHD(fileHDinfo, fileHDdata);

	int tienDien, tienNuoc, tienNL, tienPS;

	printf("\n%3s --------------------\n", "");
	printReturn();
	printf("%3s Don vi nhap: (.000d)\n", "");

	printf("\n%3s Nhap tien dien: ", "");
	ReadInput(0, " %d", &tienDien);

	if (tienDien == 0) return;

	printf("\n%3s Nhap tien nuoc: ", "");
	ReadInput(0, " %d", &tienNuoc);

	if (tienNuoc == 0) return;

	printf("\n%3s Nhap tien nguyen lieu: ", "");
	ReadInput(0, " %d", &tienNL);

	if (tienNL == 0) return;

	printf("\n%3s Nhap chi phi phat sinh: ", "");
	ReadInput(0, " %d", &tienPS);

	if (tienPS == 0) return;

	int temp = 0 - tienDien - tienNuoc - tienNL - tienPS;

	printf("\n%3s --------------------\n", "");
	printf("\n%3s Tong chi phi\t= ", ""); printCostVND(10, temp);
	printf("\n%3s Tong doanh thu\t= ", ""); printCostVND(10, REVENUE_HD);
	temp += REVENUE_HD;
	printf("\n%3s Doanh so thang\t= ", ""); printCostVND(10, temp);

	getch();

	return;
}

/* QUẢN LÝ MẬT KHẨU */

#define L_USER 10
#define L_PASS 30

char filePS[] = "password.bin";
char ADMIN_NAME[] = "admin"; 	char ADMIN_PASS[L_PASS] = "123456";
char STAFF_NAME[] = "user";	    char STAFF_PASS[L_PASS] = "000000";

char HASH_P[L_PASS]; // Lưu mật khẩu mã hoá

void unhashpass(char * hashedstr, char * normalstr)
{
	int nlen = strlen(normalstr);
	for (int i = 0; i < nlen; i++)
		normalstr[i] = 255 - hashedstr[i];
	
	return;
}

void hashpass(char * hashedstr, char * normalstr) // Simple password hash
{
	int nlen = strlen(normalstr);
	for (int i = 0; i < nlen; i++)
		hashedstr[i] = 255 - normalstr[i];
	
	return;
}

void luuFilePass()
{
	FILE * f = fopen(filePS, "wb");

	hashpass(HASH_P, ADMIN_PASS); fwrite(HASH_P, L_PASS, 1, f);
	hashpass(HASH_P, STAFF_PASS); fwrite(HASH_P, L_PASS, 1, f);

	fclose(f);
	return;
}

void docFilePass()
{
	FILE * f;
	if ((f = fopen(filePS, "rb")) == NULL)
	{
		printf("\n%3s%3s [!] %sFile mat khau bi loi / khong ton tai. Mat khau mac dinh duoc dat.\n", "", AC_RED, AC_NORMAL);
		luuFilePass(filePS);

		return;
	}

	fread(HASH_P, L_PASS, 1, f); unhashpass(HASH_P, ADMIN_PASS);
	fread(HASH_P, L_PASS, 1, f); unhashpass(HASH_P, STAFF_PASS);

	fclose(f);
	return;
}

void inputMatKhau(char ten[], char * passptr)
{
	char NEW_PASS[L_PASS];
	char CHECK_PASS[L_PASS];	

	if (stricmp(ten, "admin") == 0)
	{
		printf("\n%3s DOI MAT KHAU TAI KHOAN QUAN LY\n", "");
		printf("%3s ------------------------------\n", "");
	}
	else
	{
		printf("\n%3s DOI MAT KHAU TAI KHOAN NHAN VIEN\n", "");
		printf("%3s --------------------------------\n", "");
	}
	printReturn();

	while (1)
	{
		printf("\n%3s Nhap mat khau %s moi: ", "", ten);
		ReadInput(L_PASS, " %s", NEW_PASS);

		if (checkOUT(NEW_PASS)) return;

		printf("%3s Nhap lai mat khau: ", "");
		ReadInput(L_PASS, " %s", CHECK_PASS);
		
		if (strcmp(NEW_PASS, CHECK_PASS) == 0) break;
		else
			printf("\n%3s Mat khau khong khop. Nhap lai.\n", "");
	}

	strcpy(passptr, CHECK_PASS);
	luuFilePass();
	printf("\n%3s%s [i] %sDoi mat khau thanh cong.", "", AC_GREEN, AC_NORMAL);

	getch();
	return;
}

void doiMatKhau()
{
	cls();

	printf("\n%3s DOI MAT KHAU\n", "");
	printf("%3s ------------\n", "");

	int option = -1;
	printf("\n%3s 1. Quan li (admin)", "");
	printf("\n%3s 2. Nhan vien (user)", "");
	printf("\n%3s 0. Quay lai\n", "");

	printf("\n%3s Tai khoan? ", "");
	ReadInput(0, " %d", &option);

	while (option < 0 || option > 2)
	{
		printf("\n%3s%s [!] %sKhong ton tai lua chon. Nhap lai: ", "", AC_YELLOW, AC_NORMAL);
		ReadInput(0, " %d", &option);
	}
	if (option == 0) return;
	
	cls();
	switch(option)
	{
		case 1: inputMatKhau("admin", ADMIN_PASS); break;

		case 2: inputMatKhau("user", STAFF_PASS); break;
	}

	return;
}

/* MENU LỚN */

void BigMenuQL()
{
	int option;

	do {
		cls();
		option = -1;

		printf("\n%3s TAI KHOAN QUAN LY\n", "");
		printf("%3s -----------------\n\n", "");

		printf("%3s 1. Quan ly nhan vien\n", "");
		printf("%3s 2. Quan ly san pham\n", "");
		printf("%3s 3. Tinh doanh so\n", "");
		printf("%3s 4. Xem hoa don\n", "");
		printf("%3s 5. Doi mat khau\n", "");
		printf("%3s 0. Thoat\n", "");
		printf("\n%3s Nhan so de chon chuc nang: ", "");
		ReadInput(0, " %d", &option);

		while (option < 0 || option > 5)
		{
			printf("\n%3s%s [!] %sKhong ton tai chuc nang. Nhap lai: ", "", AC_YELLOW, AC_NORMAL);
			ReadInput(0, " %d", &option);
		}

		switch(option)
		{
			case 1: cls(); menuNV(); break;

			case 2: cls(); menuSP(); break;
			
			case 3: cls(); tinhDS(); break;

			case 4: cls(); QLdocHD(); break;

			case 5: cls(); doiMatKhau(); break;

			case 0: 
				printf("\n%3s Thoat tai khoan? ", "");
				if (Confirmed())
				{
					cls(); printf("\n%3s%s [i] %sDang xuat thanh cong.\n\n", "", AC_GREEN, AC_NORMAL); return;
				}
				option = -1;
				break;
		}

	} while (option != 0);
}
	
void BigMenuNV()
{	
	char fileSP[] = "sanpham.bin";
	int option;

	do {
		cls();
		option = -1;

		docFileSP(fileSP); // Đọc trước khi chọn chức năng

		printf("\n%3s TAI KHOAN NHAN VIEN\n", "");
		printf("%3s -------------------\n\n", "");

		printf("%3s 1. Tao don hang moi\n", "");
		printf("%3s 0. Thoat & luu tat ca don hang\n", "");
		printf("\n%3s Nhan so de chon chuc nang: ", "");
		ReadInput(0, " %d", &option);

		while (option < 0 || option > 1)
		{
			printf("\n%3s%s [i] %sKhong ton tai chuc nang. Nhap lai: ", "", AC_YELLOW, AC_NORMAL);
			ReadInput(0, " %d", &option);
		}

		switch(option)
		{
			case 1: cls(); menuDH(); break;
			
			case 0: 
				printf("\n%3s Thoat tai khoan? ", "");
				if (Confirmed())
				{
					cls(); printf("\n%3s%s [i] %sDang xuat thanh cong.\n\n", "", AC_GREEN, AC_NORMAL); return;
				}
				option = -1;
				break;
		}

	} while (option != 0);
}

/* ĐĂNG NHẬP */

int LoginStatus(char user[], char pass[])
{
	if ((strcmp(user, ADMIN_NAME) == 0) && (strcmp(pass, ADMIN_PASS) ==0 )) return 1;
	else if ((strcmp(user, STAFF_NAME) == 0) && (strcmp(pass, STAFF_PASS) == 0)) return 2;
	else return 0;
}

int exitProgram = 0;

void Login()
{
	char user[L_USER], pass[L_PASS];
	docFilePass(filePS);
	do
	{
		printf("\n%3s DANG NHAP HE THONG\n", "");
		printf("%3s ------------------\n", "");
		printf("%3s Nhan 0 de thoat.\n\n", "");

		printf("%3s Ten dang nhap: ", "");
		ReadInput(L_USER, " %s", user);

		if (strcmp(user, "0") == 0)
		{
			printf("\n%3s Thoat chuong trinh?", "");
			if (Confirmed())
			{
				exitProgram = 1;
				return;
			}
			else
			{
				strcpy(pass, "");
				continue;
			}
		}

		printf("%3s Mat khau: ", "");
		ReadInput(L_PASS, " %s", pass);
		
		if (LoginStatus(user, pass) == 1) BigMenuQL();
		else if (LoginStatus(user, pass) == 2) BigMenuNV();
		else
		{
			printf("\n%3s%s [!] %sThong tin khong dung. Moi nhap lai.", "", AC_YELLOW, AC_NORMAL);
			getch();
			cls();
		}

	} while ((LoginStatus(user, pass) == 0));
}

int main()
{
	cls();
	system("title PHAN MEM QUAN LY QUAN CAFE");
	inputptr = stdin;
	outputptr = stdout;
	
	while (!exitProgram) Login();
	return 0;
}