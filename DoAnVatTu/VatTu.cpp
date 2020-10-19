#pragma once
#include<iostream>
#include "myLib.h"
#include<string>
using namespace std;
struct VatTu
{
	string MaVT;
	string TenVT;
	string DVT;
	float SoLuongTon;
};
struct DS_VatTu
{
	VatTu* vt[100];
	int nVt = 0;
};
VatTu* nhapVatTu()
{
	VatTu* vt = new VatTu;
	string MaVT, TenVT, DVT;
	float SoLuongTon = 0;

	gotoxy(xMapThem + 21, 2 * 0 + 1 + yMapThem);
	MaVT = chinhapchuvaso("");

	gotoxy(xMapThem + 21, 2 * 1 + 1 + yMapThem);
	TenVT = boDauCachThua("");
	gotoxy(xMapThem + 21, 2 * 2 + 1 + yMapThem);
	DVT = boDauCachThua("");
	gotoxy(xMapThem + 21, 2 * 3 + 1 + yMapThem);
	std::string::size_type sz;
	SoLuongTon = std::stof(nhapSoThuc(""), &sz);

	vt->MaVT = MaVT;
	vt->TenVT = TenVT;
	vt->DVT = DVT;
	vt->SoLuongTon = SoLuongTon;
	return vt;


}
void doiChoVatTu(VatTu& a, VatTu& b)
{
	VatTu temp = a;
	a = b;
	b = temp;

}
void sortTheoTen(DS_VatTu& DSVT)
{
	string temp, temp1;
	for (int i = 0; i < DSVT.nVt - 1; i++)
	{
		for (int j = i + 1; j < DSVT.nVt; j++)
		{
			temp = DSVT.vt[i]->TenVT;
			temp1 = DSVT.vt[j]->TenVT;


			if (temp > temp1)
			{
				doiChoVatTu(*DSVT.vt[i], *DSVT.vt[j]);

			}


		}
	}
}
void ThemDanhSachVatTu(DS_VatTu& DSVT, string* arrTuKhoaVatTu)
{
	Yescursortype();
	giaoDienThem(arrTuKhoaVatTu);
	VatTu* vt = nhapVatTu();//them dia chi bat dau mang vat tu vua nhap vao con tro vt
	for (int i = 0; i < DSVT.nVt;i++)
	{
		// kiem tra xem ma vat tu co ton tai khong neu ton tai thi thong bao va roi vong for
		if (DSVT.vt[i]->MaVT == vt->MaVT)
		{
			gotoxy(xMapThem, yMapThem + 15);
			cout << "MS: " << vt->MaVT << " Da Ton tai";
			_getch();
			return;
		}
	}
	DSVT.vt[DSVT.nVt++] = vt;
	sortTheoTen(DSVT);
}
void xuatVatTu(VatTu vt, int stt)
{
	gotoxy(arrGiaoDien[0] + 1, 3 + yMap + stt * 2);
	cout << vt.MaVT;
	gotoxy(arrGiaoDien[1] + 1, 3 + yMap + stt * 2);
	cout << vt.TenVT;
	gotoxy(arrGiaoDien[2] + 1, 3 + yMap + stt * 2);
	cout << vt.DVT;
	gotoxy(arrGiaoDien[3] + 1, 3 + yMap + stt * 2);
	cout << vt.SoLuongTon;
}
void xoaVatTu(DS_VatTu& DSVT, string* arrTuKhoaVatTu)
{
	giaoDienXoa(arrTuKhoaVatTu, "Xoa Vat Tu");
	gotoxy(xMapThem + 21, yMapThem + 1);
	Yescursortype();
	string MaVTXoa = chinhapchuvaso("");

	for (int j = 0; j < DSVT.nVt; j++)
	{
		if (MaVTXoa == DSVT.vt[j]->MaVT)
		{
			gotoxy(xMapThem, yMapThem + 5);
			cout << "Ban co chac chan xoa vat tu co MS: " << MaVTXoa << " khong ? (Y/N)";

			while (!_kbhit())// doi  bat phim
			{
				int key = _getch();
				if (key == 81 || key == 121)//Y/y
				{
					for (int k = j; k < DSVT.nVt - 1; k++)
					{


						DSVT.vt[k]->MaVT = DSVT.vt[k + 1]->MaVT;
						DSVT.vt[k]->TenVT = DSVT.vt[k + 1]->TenVT;
						DSVT.vt[k]->DVT = DSVT.vt[k + 1]->DVT;
						DSVT.vt[k]->SoLuongTon = DSVT.vt[k + 1]->SoLuongTon;
					}
					DSVT.nVt--;
					return;
				}
				else if (key == 78 || key == 110) // N || n
				{
					return;
				}

			}
		}
	}
	gotoxy(xMapThem, yMapThem + 5);
	cout << "Trong Kho Khong Co Vat Tu Co MS: " << MaVTXoa << ".";
	gotoxy(xMapThem, yMapThem + 6);
	cout << "Ban Co Muon Tiep Tuc khong ? (Y/N)";

	while (!_kbhit())
	{
		int key = _getch();
		if (key == 81 || key == 121)// Y || y
		{
			gotoxy(xMapThem, yMapThem + 5);
			cout << "                                         ";
			gotoxy(xMapThem, yMapThem + 6);
			cout << "                                  ";
			gotoxy(xMapThem + 21, yMapThem + 1);
			cout << "                      ";
			xoaVatTu(DSVT, arrTuKhoaVatTu);
			return;
		}
		else if (key == 78 || key == 110) // N || n
		{
			return;
		}
	}
}
void SuaVatTu(DS_VatTu& DSVT, string* arrTuKhoaVatTu)
{
	string Ho = "", Ten = "";
	int MaNV = 0, Phai = 0;
	giaoDienXoa(arrTuKhoaVatTu, "Sua Thong Tin Mon Hoc");
	gotoxy(xMapThem + 21, yMapThem + 1);
	Yescursortype();
	int check = 0;
	string MaSua = chinhapchuvaso("");
	Nocursortype();
	for (int i = 0;i < DSVT.nVt;i++)
	{
		if (DSVT.vt[i]->MaVT == MaSua)
		{
			gotoxy(xMapThem, yMapThem + 5);
			cout << "Ban co chac chan sua Vat Tu co MS: " << MaSua << " khong ? (Y/N)";

			while (!_kbhit())
			{
				int key = _getch();
				if (key == 81 || key == 121)
				{
					gotoxy(xMapThem, yMapThem + 5);
					cout << "                                                            ";

					giaoDienThem(arrTuKhoaVatTu);

					string  TenVT, DVT;
					float SoLuongTon = 0;


					Yescursortype();
					gotoxy(xMapThem + 21, 2 * 1 + 1 + yMapThem);
					TenVT = boDauCachThua("");
					gotoxy(xMapThem + 21, 2 * 2 + 1 + yMapThem);
					DVT = boDauCachThua("");
					gotoxy(xMapThem + 21, 2 * 3 + 1 + yMapThem);
					std::string::size_type sz;
					SoLuongTon = std::stof(nhapSoThuc(""), &sz);


					DSVT.vt[i]->TenVT = TenVT;
					DSVT.vt[i]->SoLuongTon = SoLuongTon;
					DSVT.vt[i]->DVT = DVT;
					Nocursortype();
					return;
				}
				else if (key == 78 || key == 110) // N || n
				{
					return;
				}
			}
		}
	}
	gotoxy(xMapThem, yMapThem + 5);
	cout << "MS: " << MaSua << " Khong Ton tai";
	_getch();
	return;
}
void xuatDanhSachVatTu(DS_VatTu& DSVT, string* arrTuKhoaVatTu, string nameGiaoDien, int viTri = 0)
{
	Nocursortype();


	clrscr();// xoa mang hinh

	textcolor(7);
	giaoDien(arrTuKhoaVatTu, nameGiaoDien, 4);
	int k = 0;
	for (int i = 0; i < DSVT.nVt; i++)
	{
		xuatVatTu(*DSVT.vt[i], k++);
	}
}
void CreateVatTu(DS_VatTu& DSVT)
{

	string nameVatTu = "DANH SACH VAT TU";
	string arrTuKhoaVatTu[5] = { "Ma Vat Tu" ,"Ten Vat Tu","Don Vi Tinh" ,"So Luong Ton Kho" };

	giaoDien(arrTuKhoaVatTu, nameVatTu, 4);

	int i = 0, viTri = 0;
	if (DSVT.nVt != 0)
		xuatDanhSachVatTu(DSVT, arrTuKhoaVatTu, nameVatTu);
	int key;
	while (true)
	{
		while (!_kbhit())
		{
			key = _getch();
			if (key == 0)
			{
				key = _getch();
				if (key == 60)
				{
					ThemDanhSachVatTu(DSVT, arrTuKhoaVatTu);
					break;
				}
				else if (key == 61)
				{
					xoaVatTu(DSVT, arrTuKhoaVatTu);

					break;
				}
				else if (key == 62)
				{

					SuaVatTu(DSVT, arrTuKhoaVatTu);

					break;
				}
			}
			else if (key == 224)
			{
				key = _getch();
			}
			else if (key == 27) // esc
			{
				clrscr();
				return;
			}
		}


		clrscr();
		xuatDanhSachVatTu(DSVT, arrTuKhoaVatTu, nameVatTu);

	}
}
