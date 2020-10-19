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
	int SoLuongTon;
};
struct NodeVT
{
	VatTu Data;
	struct NodeVT* pLeft;
	struct NodeVT* pRight;
};
typedef struct NodeVT NODEVT;
typedef NODEVT* Tree;


string arrVTtemp[MAX];
int nArrVTtemp = 0;

void Init(Tree& root)
{
	root = NULL;
}
bool Empty(Tree root)
{
	return (root == NULL ? true : false);
}

void InSert(Tree& t, VatTu info)
{
	if (t == NULL)
	{
		NODEVT* q = new NODEVT;
	
		q->Data = info;
		q->pLeft = q->pRight = NULL;
		t = q;
	}
	else
	{
		if (info.MaVT < t->Data.MaVT)
		{
			InSert(t->pLeft, info);
		}
		else if (info.MaVT > t->Data.MaVT)
		{
			InSert(t->pRight, info);
		}
	}
}
void TimPhanTuTheMang(Tree& t, Tree& p)
{
	if (t->pRight != NULL)
	{
		TimPhanTuTheMang(t->pRight, p);
	}
	else
	{
		p->Data = t->Data;
		p = t;
		t = t->pLeft;
	}
}
NodeVT* Search(Tree& t, string x)
{
	if (t == NULL)
		return NULL;
	if (x > t->Data.MaVT)
		return Search(t->pRight, x);
	else if (x < t->Data.MaVT)
		return Search(t->pLeft, x);
	else
		return t;

}
bool nhapVatTu(Tree t,VatTu& vt)
{
	int checkMa = 0;
	gotoxy(7, 20);
	cout << "Them Vat Tu";

	gotoxy(2, 25);
	cout << "Ma Vat Tu:    ";	
	gotoxy(2, 27);
	cout << "Ten Vat Tu:   ";
	gotoxy(2, 29);
	cout << "Don Vi Tinh:  ";
	gotoxy(2, 31);
	cout << "So Luong Ton: ";

	vt.MaVT = "";
	do {
	
		int lengh = vt.MaVT.length();
		gotoxy(25 +lengh, 25);
		vt.MaVT = nganDauCachMASo(vt.MaVT);
		if (Search(t, vt.MaVT) != NULL)
		{
			InThongBao("Ma Vat Tu Da Ton Tai");
			checkMa = 0;
		}
		else
		{
			XoaThongBao();
			checkMa = 1;
		}

	} while (checkMa == 0);
	
	gotoxy(25, 27);
	vt.TenVT = nganDauCachThua("", 50);
	gotoxy(25, 29);
	vt.DVT = nganDauCachThua("", 10);
	gotoxy(25, 31);
	vt.SoLuongTon = chiDuocNhapSo(0, 10);
	
	int key ,  vitri = 0;

	Nocursortype();
	gotoxy(30, 35);
	cout << "Thoat";
	textcolor(setMauChon);
	gotoxy(20, 35);
	cout << "Luu";
	while (true)
	{

		while (!_kbhit())
		{

			key = _getch();
			if (key == 224)
			{
				key = _getch();
				if (key == 77 && vitri < 2)
				{
					textcolor(setMauBoChon);
					
					gotoxy(20, 35);
					cout << "Luu";
					textcolor(setMauChon);
					gotoxy(30, 35);
					cout << "Thoat";
					vitri++;
				}
				else if (key == 75 && vitri > 0)
				{

					textcolor(setMauBoChon);
					gotoxy(30, 35);
					cout << "Thoat";
					
					textcolor(setMauChon);
					gotoxy(20, 35);
					cout << "Luu";
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
					return false;
				}
				else if (vitri == 0)
				{
					return true;
				}

			}
			

		}

	}
	
}
void ThemDanhSachVatTu(Tree& t)
{
	XoaKhuVucHienThi();
	XoaThongBao();
	VatTu vt;
	Yescursortype();
	if (nhapVatTu(t, vt) ==true)
	{
		InSert(t, vt);
		InThongBao("Them Thanh Cong");
	}
	XoaKhuVucHienThi();
	
}
void XoaNode(Tree& t, string x)
{
	// Trước tiên ta sẽ đi xóa các Node có 1 con và các Node lá
	if (t == NULL)
	{
		InThongBao("MS: " + x + " Khong Ton tai");		
		return;
	}
	if (x < t->Data.MaVT)
	{
		XoaNode(t->pLeft, x);
	}
	else if (x > t->Data.MaVT)
	{
		XoaNode(t->pRight, x);
	}
	else
	{		
		InThongBao("Ban co chac chan xoa vat tu co MS: " + t->Data.MaVT + " khong ? (Y/N)");	
		while (!_kbhit())
		{
			int key = _getch();
			if (key == 89 || key == 121)
			{
				NODEVT* p = t;
				/* ===== XÓA Node có 1 con và không có con ==== */
				if (p->pLeft == NULL)
				{
					t = p->pRight;	
				}
				else if (p->pRight == NULL)
				{
					t = p->pLeft;
				}
				/* ============================================ */
				/* Xóa Node có 2 con */
				else
				{
					TimPhanTuTheMang(t->pLeft, p);
				}
			
				XoaThongBao();
				InThongBao("Da Xoa Vat Tu Co MS:" + p->Data.MaVT);
				delete p;
				
				return;
			}
			else if (key == 78 || key == 110) // N || n
			{
				return;
			}
		}
	}
}
void xoaVatTu(Tree& t,string MaVTXoa)
{
	XoaNode(t, MaVTXoa);

	XoaKhuVucHienThi();
	Nocursortype();
}

void LNR(Tree& t)
{
	if (t != NULL)
	{
		LNR(t->pLeft);
		arrVTtemp[nArrVTtemp++] = t->Data.TenVT + "#" + t->Data.MaVT;
		LNR(t->pRight);
	}
}
void doiCho2Chuoi(string& a, string& b)
{
	string temp;
	temp = a;
	a = b;
	b = temp;

}
void sortTheoTen()
{
	string temp, temp1;
	for (int i = 0; i < nArrVTtemp - 1; i++)
	{
		for (int j = i + 1; j < nArrVTtemp; j++)
		{
			temp = arrVTtemp[i];
			temp1 = arrVTtemp[j];
			string a = strtok((char*)temp.c_str(), "#");
			string b = strtok((char*)temp1.c_str(), "#");
			if (a.compare(b) > 0)
			{
				doiCho2Chuoi(arrVTtemp[i], arrVTtemp[j]);

			}

		}
	}
}
void xuatVatTu(VatTu vt, int stt)
{
	gotoxy(15, 21+stt*2);
	cout << vt.MaVT;
	gotoxy(35, 21+ stt * 2);
	cout << vt.TenVT;
	gotoxy(65, 21 + stt * 2);
	cout << vt.DVT;
	gotoxy(90, 21 + stt * 2);
	cout << vt.SoLuongTon;

}
void xuatDanhSachVatTu(Tree t)
{
	XoaKhuVucHienThi();
	Nocursortype();

	textcolor(7);
	
	gotoxy(15, 19);
	cout << "Ma Vat Tu";
	
	gotoxy(35, 19);
	cout << "Ten Vat Tu";

	gotoxy(65, 19);
	cout << "Don Vi Tinh";


	gotoxy(90, 19);
	cout << "So Luong Ton";
	nArrVTtemp = 0;
	LNR(t);
	sortTheoTen();
	int k = 0;
	for (int i = 0; i < nArrVTtemp; i++)
	{
		NodeVT	* p = new NodeVT;
		string temp = arrVTtemp[i];
		string temp1 = strtok((char*)temp.c_str(), "#");
		string temp2 = strtok(NULL, "#");
		p = Search(t, temp2);
		xuatVatTu(p->Data, k++);
	}
}

bool SuaVatTu(Tree t, VatTu& vt)
{
	int checkMa = 0;
	int length = 0;
	gotoxy(7, 20);
	cout << "Sua Vat Tu";

	gotoxy(2, 25);
	cout << "Ma Vat Tu:    ";
	gotoxy(2, 27);
	cout << "Ten Vat Tu:   ";
	gotoxy(2, 29);
	cout << "Don Vi Tinh:  ";
	gotoxy(2, 31);
	cout << "So Luong Ton: ";

	gotoxy(25, 25);
	cout << vt.MaVT;
	gotoxy(25, 27);
	cout << vt.TenVT;
	gotoxy(25, 29);
	cout << vt.DVT;
	gotoxy(25, 31);
	cout << vt.SoLuongTon;

	string ten = vt.TenVT, dvt = vt.DVT;
	int sl = vt.SoLuongTon;
	length = vt.TenVT.length();
	gotoxy(25 + length, 27);
	ten = nganDauCachThua(ten, 50);
	length = vt.DVT.length();
	gotoxy(25 + length, 29);
	dvt = nganDauCachThua(dvt, 10);
	//length = lenghSo(vt.SoLuongTon);
	//gotoxy(25 + length, 31);
	//sl = chiDuocNhapSo(sl, 10);

	int key, vitri = 0;

	Nocursortype();
	gotoxy(30, 35);
	cout << "Thoat";
	textcolor(setMauChon);
	gotoxy(20, 35);
	cout << "Luu";
	while (true)
	{

		while (!_kbhit())
		{

			key = _getch();
			if (key == 224)
			{
				key = _getch();
				if (key == 77 && vitri < 2)
				{
					textcolor(setMauBoChon);

					gotoxy(20, 35);
					cout << "Luu";
					textcolor(setMauChon);
					gotoxy(30, 35);
					cout << "Thoat";
					vitri++;
				}
				else if (key == 75 && vitri > 0)
				{

					textcolor(setMauBoChon);
					gotoxy(30, 35);
					cout << "Thoat";

					textcolor(setMauChon);
					gotoxy(20, 35);
					cout << "Luu";
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
					return false;
				}
				else if (vitri == 0)
				{
					vt.TenVT = ten;
					vt.DVT = dvt;
					vt.SoLuongTon = sl;
					return true;
				}

			}


		}

	}

}
void SuaDanhSachVatTu(Tree& t,string MaVTSua)
{
	
	 NODEVT * p = Search(t, MaVTSua);
	if (p == NULL)
	{
		InThongBao("Ma Vat Tu Khong Ton Tai");	
		XoaKhuVucHienThi();
		Nocursortype();
		return;
	}
	XoaKhuVucHienThi();
	
	Yescursortype();
	if (SuaVatTu(t, p->Data) == true)
	{		
		InThongBao("Sua Thanh Cong");
	}
	XoaKhuVucHienThi();
	Nocursortype();
}

