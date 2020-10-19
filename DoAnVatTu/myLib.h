#pragma once
#include<iostream>s
using namespace std;
#include <Windows.h>
#include<conio.h>
#include <string>

#define setMauChon  158
#define setMauBoChon  7
#define MAX 10000
#define MAXNV 500

// Hàm tô màu.
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

//ham dich chuyen con tro
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1, y - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
void Nocursortype()//an dau nhay
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void Yescursortype()//hien dau nhay
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
// Thiết lập chế độ hiển thị, có fullscreen hay không
BOOL NT_SetConsoleDisplayMode(HANDLE hOutputHandle, DWORD dwNewMode)
{
	typedef BOOL(WINAPI* SCDMProc_t) (HANDLE, DWORD, LPDWORD);
	SCDMProc_t SetConsoleDisplayMode;
	HMODULE hKernel32;
	BOOL bFreeLib = FALSE, ret;
	const char KERNEL32_NAME[] = "kernel32.dll";

	hKernel32 = GetModuleHandleA(KERNEL32_NAME);
	if (hKernel32 == NULL)
	{
		hKernel32 = LoadLibraryA(KERNEL32_NAME);
		if (hKernel32 == NULL)
			return FALSE;

		bFreeLib = true;
	}

	SetConsoleDisplayMode =
		(SCDMProc_t)GetProcAddress(hKernel32, "SetConsoleDisplayMode");
	if (SetConsoleDisplayMode == NULL)
	{
		SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
		ret = FALSE;
	}
	else
	{
		DWORD tmp;
		ret = SetConsoleDisplayMode(hOutputHandle, dwNewMode, &tmp);
	}

	if (bFreeLib)
		FreeLibrary(hKernel32);

	return ret;
}

// Đặt chế độ FullScreen
void setFullScreen()
{
	NT_SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), 1);

}
void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

int  lenghSo(int n)//độ dài của một số
{
	return (int)log10(n) + 1;
}


void GiaoDienMenu()
{
	gotoxy(25, 1);
	cout << "Quan Ly Vat Tu  ";

	gotoxy(2, 43);
	cout << "Thong Bao: ";
	gotoxy(2, 45);
	cout << "ESC: Thoat       Enter: Chon ";



	for (int i = 1; i < 150;i++)
	{
		gotoxy(i, 2);
		cout << char(196);
		gotoxy(i, 16);
		cout << char(196);
		gotoxy(i, 18);
		cout << char(196);
		gotoxy(i, 42);
		cout << char(196);
		gotoxy(i, 44);
		cout << char(196);
		gotoxy(i, 46);
		cout << char(196);
	}

	for (int i = 1; i < 14;i++)
	{
		gotoxy(50, i + 2);
		cout << char(179);
	}
	gotoxy(50, 2);
	cout << char(194);
	gotoxy(50, 16);
	cout << char(193);
}


void GiaoDienMenuChon(string* arrTuKhoa)
{
	for (int i = 0; i < 7;i++)
	{
		gotoxy(2, 3 + i * 2);
		cout << arrTuKhoa[i];
	}

}


void GiaoDienMenuChonHai(int viTri)
{
	if (viTri > 3)
	{
		return;
	}
	textcolor(setMauBoChon);
	string arrTuKhoa1[4][4] = { { "Nhap Vat Tu","Cap Nhap Vat Tu","Xoa Vat Tu","Xem Danh Sach Vat Tu" },
								{ "Nhap Nhan Vien","Cap Nhap Nhan Vien","Xoa Nhan Vien","Xem Danh Sach Nhan Vien" },
								{ "Nhap Hoa Don","Xem Danh Sach Hoa Don","","" }, 
								{ "Nhap Chi Tiet Hoa Don","Cap Nhap Chi Tiet Hoa Don","Xoa CT Hoa Don","Xem Danh Sach Chi Tiet Hoa Don" }
								 };

	for (int i = 0; i < 4;i++)
	{
		gotoxy(52, 3 + i * 2);
		cout << arrTuKhoa1[viTri][i];
	}
}

void XoaGiaoDienMenuChonHai()
{
	textcolor(setMauBoChon);	
	for (int i = 0; i < 4;i++)
	{
		gotoxy(52, 3 + i * 2);
		cout << "                                     ";
	}
}

void InThongBao(string thongBao)
{
	textcolor(setMauBoChon);
	gotoxy(17, 43);
	cout << thongBao;
}

void XoaThongBao()
{
	textcolor(setMauBoChon);
	gotoxy(17, 43);
	cout <<"                                                                                 ";
}
void XoaKhuVucHienThi()
{
	textcolor(setMauBoChon);
	for (int i = 19;i < 42;i++)
	{
		gotoxy(1, i);
		cout << "                                                                                                                                                          ";
	}
	
	
}


// dùng để nhập tên(chữ)
string nganDauCachThua(string temp, int soKiTuToiDa = 20)
{
	int key;
	bool isSpaced = false;
	int count = temp.length();
	while (true)
	{
		while (!_kbhit())
		{
			key = _getch();
			if (key != 224 && key != 0)
			{
				if ((key >= 65 && key <= 90) || (key >= 97 && key <= 142) || key == 32)
				{

					if (!isSpaced && key == 32 && temp.length() > 0 && temp[count - 1] == ' ')
					{
						cout << (char)key;
						temp += (char)key;
						isSpaced = true;
						count++;
					}
					else if (key != 32 && count < soKiTuToiDa)
					{
							cout << char(toupper((char)key));
							temp += char(toupper((char)key));

						count++;
						isSpaced = false;
					}

				}
				else if (key == 13)
				{
					if (count > 0)
						return temp;

				}
				else if (key == 8 && count > 0)
				{
					cout << "\b" << " " << "\b";
					temp.erase(temp.length() - 1, 1);
					count--;

				}
			}
			else
			{
				key = _getch();
			}

		}
	}
	return temp;
}
// dùng để nhập MS(chữ và số)
string nganDauCachMASo(string temp, int countMax = 10)
{
	int key, count = temp.length();
	while (!_kbhit())
	{
		key = _getch();
		if (key != 224 && key != 0)
		{
			if ((key >= 65 && key <= 90) || (key >= 97 && key <= 142) || (key >= 48 && key <= 57))
			{

				if (key != 32 && count < countMax)
				{
					cout << char(toupper((char)key));
					temp += char(toupper((char)key));
					count++;
				}

			}
			else if (key == 13)
			{
				if (count > 0)
					return temp;

			}
			else if (key == 27)
			{
				if (count > 0)
					return "";

			}
			else if (key == 8 && count > 0)
			{
				cout << "\b" << " " << "\b";
				temp.erase(temp.length() - 1, 1);
				count--;

			}
		}
		else
		{
			key = _getch();
		}
	}
	return temp;
}
int chiDuocNhapSo(int temp, int countMax = 10)
{
	int kq = 0;
	int count = 0;
	if (temp > 0)
	{
		count = lenghSo(temp);
	}
	while (!_kbhit())
	{
		int key = _getch();
		if (key != 224 && key != 0)
		{
			if ((key >= 48 && key <= 57) && count < countMax)
			{
				kq = key - 48;
				cout << kq;
				temp = temp * 10 + kq;
				count++;
			}
			else if (key == 13)
			{
				if (count > 0)
					return temp;
			}
			else if (key == 8 && count > 0)
			{
				cout << "\b" << " " << "\b";
				temp /= 10;
				count--;
			}
		}
		else
		{
			key = _getch();
		}
	}
	return temp;
}

string chiChoPhepNhap2Chu(string temp )
{
	int key;
	int count = temp.length();
	while (true)
	{
		while (_kbhit())
		{
			key = _getch();

			if ((key == 78 || key == 110 || key == 88 || key == 120) && count < 1)
			{
				cout << char(toupper((char)key));
				temp += char(toupper((char)key));
				count++;


			}
			else if (key == 13)
			{
				if (count > 0)
					return temp;

			}
			else if (key == 8 && count > 0)
			{
				cout << "\b" << " " << "\b";
				temp.erase(temp.length() - 1, 1);
				count--;

			}
		}
	}
	return temp;
}

string nhapNamOrNu()
{
	int key, vitri = 0;

	Nocursortype();
	gotoxy(40, 31);
	cout << "Nu";

	textcolor(setMauChon);
	gotoxy(30, 31);
	cout << "Nam";
	while (true)
	{

		while (!_kbhit())
		{

			key = _getch();
			if (key == 224)
			{
				key = _getch();
				if (key == 77 && vitri < 1)
				{
					textcolor(setMauBoChon);

					gotoxy(30, 31);
					cout << "Nam";
					textcolor(setMauChon);
					gotoxy(40, 31);
					cout << "Nu";
					vitri++;
				}
				else if (key == 75 && vitri > 0)
				{

					textcolor(setMauBoChon);
					gotoxy(40, 31);
					cout << "Nu";

					textcolor(setMauChon);
					gotoxy(30, 31);
					cout << "Nam";
					vitri--;
				}

			}
			else if (key == 0)
			{
				key = _getch();
			}
			else if (key == 13)
			{
				if (vitri == 1)
				{
					textcolor(setMauBoChon);
					return "Nu";
				}
				else if (vitri == 0)
				{
					textcolor(setMauBoChon);
					return "Nam";
				}

			}


		}

	}
}
