	#pragma once
#include<iostream>
#include "myLib.h"
#include "VatTu.h"
#include<string>
#include <time.h>
using namespace std;
/// Chi Tiet Hoa Don
struct CT_HoaDon
{
	string MaVT;
	int SoLuong;
	int DonGia;
	int VAT;
};
struct Node
{
	CT_HoaDon info;
	struct Node* pNext;
};
typedef struct Node* PTR;

/// danh sách Hóa Đơn
struct Date
{
	int ngay;
	int thang;
	int nam;
};
struct HoaDon
{
	string SoHoaDOn;
	Date ngayLap;
	string Loai;
	PTR list_CT_HoaDon;
	int nList;
};
struct NodeHD
{
	HoaDon info;
	struct NodeHD* pNext;
};
typedef struct NodeHD* PTRHD;

struct NhanVien
{
	string MaNV;
	string Ho;
	string Ten;
	string Phai;
	PTRHD list_HoaDon;
	int nList = 0;
};

struct DS_NhanVien
{
	NhanVien* DS[MAXNV];
	int nNV;
};
// khởi tạo danh sách 
void Init(PTR& l)
{
	l = NULL;
}
PTR GetNode(CT_HoaDon info)
{
	PTR p = new Node;
	if (p == NULL)
	{
		cout << "khong du bo nho de cap phat ";
		return NULL;
	}
	p->info = info;
	p->pNext = NULL;
	return p;
}
// thêm 1 node vào danh sách
void Add(PTR& l, PTR  p)
{
	if (l == NULL)
	{
		l = p;
	}
	else
	{
		for (PTR q = l; q != NULL; q = q->pNext)
		{
			if (q->pNext == NULL)
			{
				q->pNext = p;
				break;
			}
		}
	}
}
bool nhapCT_HoaDon(Tree& t, PTR l, CT_HoaDon& ct, string tinhTrang)
{
	
	
	int checkMa = 0;
	int checkMa1 = 0;
	gotoxy(7, 20);
	cout << "Them Chi Tiet Hoa Don";

	gotoxy(2, 25);
	cout << "Ma Vat Tu:    ";
	gotoxy(2, 27);
	cout << "So Luong:   ";
	gotoxy(2, 29);
	cout << "Don Gia:  ";
	gotoxy(2, 31);
	cout << "%VAT: ";

	ct.MaVT = "";

	NODEVT* p = new NODEVT;
	
	do {

		int lengh = ct.MaVT.length();
		gotoxy(25 + lengh, 25);
		ct.MaVT = nganDauCachMASo(ct.MaVT);
		if (ct.MaVT == "")
		{
			return false;
		}
		p = Search(t, ct.MaVT);
		if (p == NULL)
		{
			XoaThongBao();
			InThongBao("Ma Vat Tu Khong Ton Tai Trong Kho");
			checkMa = 0;
		}
		else
		{
			for (PTR q = l; q != NULL; q = q->pNext)
			{
				if (q->info.MaVT == ct.MaVT)
				{
					XoaThongBao();
					InThongBao("Ma Vat Tu Da Ton Tai Trong Hoa Don");
					checkMa1 = 1;
					break;
				}
			}
			if (checkMa1 == 0)
			{
				checkMa = 1;
			}
			
		}

	} while (checkMa == 0);

	

	int length1 = 0;
	int checkSLT = 0;
	ct.SoLuong = 0;
	do {

		
		if (ct.SoLuong > 0)
		{
			length1 = lenghSo(ct.SoLuong);
		}
		else
		{
			int length1 = 0;
		}
		gotoxy(25 + length1, 27);
		ct.SoLuong = chiDuocNhapSo(ct.SoLuong, 10);
		
		if (tinhTrang == "X")
		{
			if (p->Data.SoLuongTon < ct.SoLuong)
			{
				
				
				
				InThongBao("So Luong Ton Kho Cua Vat Tu Khong Du De Xuat.So Luong Ton Kho Con: " + std::to_string(p->Data.SoLuongTon));
				checkSLT = 0;
			}
			else
			{
				checkSLT = 1;
			}
			
		}
		else
		{
			checkSLT = 1;
		}
		

	} while (checkSLT == 0);


	gotoxy(25, 29);
	ct.DonGia = chiDuocNhapSo(0, 20);
	gotoxy(25, 31);
	ct.VAT = chiDuocNhapSo(0, 10);

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
					if (tinhTrang == "N")
					{
						p->Data.SoLuongTon += ct.SoLuong;
					}
					else
					{
						p->Data.SoLuongTon -= ct.SoLuong;
					}
					return true;
				}

			}


		}

	}
		
	
}
void ThemCT_HoaDon(Tree& DSVT, PTR& l, string tinhTrang)
{
	XoaKhuVucHienThi();
	XoaThongBao();
	CT_HoaDon hd;
	Yescursortype();
	if (nhapCT_HoaDon(DSVT, l, hd, tinhTrang ) == true)
	{
		Add(l, GetNode(hd));
		InThongBao("Them Thanh Cong");

	}
	
	XoaKhuVucHienThi();
}
bool SuaCT_HoaDon(Tree &t, PTR& l, CT_HoaDon& ct, string tinhTrang)
{
	int checkMa = 0;
	int length = 0;
	gotoxy(7, 20);
	cout << "Sua Vat Tu";

	gotoxy(2, 25);
	cout << "Ma Vat Tu:    ";
	gotoxy(2, 27);
	cout << "So Luong:   ";
	gotoxy(2, 29);
	cout << "Don Gia:  ";
	gotoxy(2, 31);
	cout << "%VAT: ";

	gotoxy(25, 25);
	cout << ct.MaVT;
	gotoxy(25, 27);
	cout << ct.SoLuong;
	gotoxy(25, 29);
	cout << ct.DonGia;
	gotoxy(25, 31);
	cout << ct.VAT;

	int sl = ct.SoLuong, dongia = ct.DonGia, vat = ct.VAT;
	NODEVT* p = new NODEVT;
	p = Search(t, ct.MaVT);
	int checkSLT = 0;
	do {


		if (ct.SoLuong > 0)
		{
			length = lenghSo(sl);
		}
		else
		{
			 length = 0;
		}
		gotoxy(25 + length, 27);
		sl = chiDuocNhapSo(sl, 10);

		if (tinhTrang == "X")
		{
			if (p->Data.SoLuongTon + ct.SoLuong < sl)
			{
				InThongBao("So Luong Ton Kho Cua Vat Tu Khong Du De Xuat. So Luong Ton Kho Con: " + std::to_string(p->Data.SoLuongTon));
				checkSLT = 0;
			}
			else
			{
				checkSLT = 1;
			}
		}
		else
		{
			checkSLT = 1;
		}


	} while (checkSLT == 0);

	length = lenghSo(dongia);
	gotoxy(25 + length, 29);
	dongia = chiDuocNhapSo(dongia, 10);

	length = lenghSo(vat);
	gotoxy(25 + length, 31);
	vat = chiDuocNhapSo(vat, 10);

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
					if (tinhTrang == "N")
					{
						p->Data.SoLuongTon += (sl - ct.SoLuong);
						
					}
					else
					{
						p->Data.SoLuongTon -= (sl - ct.SoLuong);
					}
					ct.SoLuong = sl;
					ct.DonGia = dongia;
					ct.VAT = vat;
					
					return true;
				}

			}


		}

	}

}
void SuaDanhSachCT_HoaDon(Tree& t, PTR& l, string tinhTrang)
{
	XoaKhuVucHienThi();
	XoaThongBao();
	Yescursortype();
	gotoxy(7, 20);
	cout << "Sua Chi Tiet Hoa Don";

	gotoxy(2, 25);
	cout << "Ma Vat Tu Can Sua:    ";
	gotoxy(25, 25);
	string MaCTSua = nganDauCachMASo("");
	PTR p = new Node;
	bool checkTimKiem = false;
	for (p = l; p != NULL; p = p->pNext)
	{
		if (p->info.MaVT == MaCTSua)
		{
			checkTimKiem = true;
			break;
		}
	}

	if (checkTimKiem == false)
	{
		InThongBao("Khong Tim Thay CT Hoa Don");
		return;
	}
	
	XoaKhuVucHienThi();


	if (SuaCT_HoaDon(t,l, p->info,tinhTrang) == true)
	{
		InThongBao("Sua Thanh Cong");
	}
	XoaKhuVucHienThi();
	Nocursortype();
}
void xuatCT_HoaDon(CT_HoaDon ct, int stt)
{
	gotoxy(15, 21 + stt * 2);
	cout << ct.MaVT;
	gotoxy(35, 21 + stt * 2);
	cout << ct.SoLuong;
	gotoxy(65, 21 + stt * 2);
	cout << ct.DonGia;
	gotoxy(90, 21 + stt * 2);
	cout << ct.VAT<<"%";

}
void xuatDanhSachCT_HoaDon(PTR& l)
{
	Nocursortype();

	textcolor(7);

	gotoxy(15, 19);
	cout << "Ma Vat Tu";

	gotoxy(35, 19);
	cout << "So Luong";

	gotoxy(65, 19);
	cout << "Don Gia";


	gotoxy(90, 19);
	cout << "%VAT";

	
	int k = 0;
	for (PTR p = l; p != NULL; p = p->pNext)
	{
		xuatCT_HoaDon(p->info, k++);
	}
}
void xoaCT_HoaDon(Tree& t, PTR& l, string tinhTrang)
{
	

	Yescursortype();
	XoaKhuVucHienThi();
	XoaThongBao();
	gotoxy(7, 20);
	cout << "Xoa CT Hoa Don";

	gotoxy(2, 25);
	cout << "Ma Vat Tu Can Xoa:    ";
	gotoxy(25, 25);
	string MaCTXoa = nganDauCachMASo("");


	NODEVT* q = new NODEVT;
	q = Search(t, MaCTXoa);
	if (q == NULL)
	{
		InThongBao("Khong Co Hoa Don Chua Vat Tu Co MS: " + MaCTXoa + ".");
		XoaKhuVucHienThi();
		return;
	}
	for (PTR p = l; p != NULL; p = p->pNext)
	{

		if (MaCTXoa ==  l->info.MaVT)
		{
			InThongBao("Ban co chac chan xoa CT_Hoa Don Chua vat tu co MS: " + MaCTXoa + " khong ? (Y/N)");
			
			while (!_kbhit())
			{
				int key = _getch();
				if (key == 89 || key == 121)
				{
					PTR k = l;
					l = k->pNext;
					if (tinhTrang == "N")
					{
						q->Data.SoLuongTon -= p->info.SoLuong;

					}
					else
					{
						q->Data.SoLuongTon += p->info.SoLuong;
					}
					delete k;
					
					

					XoaThongBao();
					InThongBao("Xoa Thanh Cong");
					XoaKhuVucHienThi();
					Nocursortype();
					return;
				}
				else if (key == 78 || key == 110) // N || n
				{
					XoaThongBao();
					InThongBao("Ban Da Khong Xoa");
					XoaKhuVucHienThi();
					Nocursortype();
					return;
				}
			}
		}
		else if (p->pNext != NULL)
		{
			if (MaCTXoa == p->pNext->info.MaVT)
			{
				InThongBao("Ban co chac chan xoa T_Hoa Don Chua vat tu co MS: " + MaCTXoa + " khong ? (Y/N)");
				while (!_kbhit())
				{
					int key = _getch();
					if (key == 89 || key == 121)
					{
						PTR k = p->pNext;
						p->pNext = k->pNext;
						if (tinhTrang == "N")
						{
							q->Data.SoLuongTon -= p->info.SoLuong;

						}
						else
						{
							q->Data.SoLuongTon += p->info.SoLuong;
						}
						delete k;



						XoaThongBao();
						InThongBao("Xoa Thanh Cong");
						XoaKhuVucHienThi();
						Nocursortype();
						return;
					}
					else if (key == 78 || key == 110) // N || n
					{
						XoaThongBao();
						InThongBao("Ban Da Khong Xoa");
						XoaKhuVucHienThi();
						Nocursortype();
						return;
					}
				}
			}
		}
	}
	InThongBao("Khong Co Hoa Don Chua Vat Tu Co MS: " + MaCTXoa + ".");
	
	XoaKhuVucHienThi();
	Nocursortype();
			
	
}





void InitHD(PTRHD& l)
{
	l = NULL;
}
PTRHD GetNode(HoaDon info)
{
	PTRHD p = new NodeHD;
	if (p == NULL)
	{
		cout << "khong du bo nho de cap phat ";
		return NULL;
	}
	p->info = info;
	p->pNext = NULL;
	return p;
}
void Add(PTRHD& l, PTRHD  p)
{
	if (l == NULL)
	{
		l = p;
	}
	else
	{
		for (PTRHD q = l; q != NULL; q = q->pNext)
		{
			if (q->pNext == NULL)
			{
				q->pNext = p;
				break;
			}
		}
	}
}
void Time(int& ngay, int& thang, int& nam)
{
	time_t baygio = time(0);

	tm* ltm = localtime(&baygio);
	int a = ltm->tm_mon;
	nam = 1900 + ltm->tm_year;
	thang = 1 + a;
	ngay = ltm->tm_mday;
}
bool SearchHD(DS_NhanVien ds,PTRHD l, string x)
{
	for (int i = 0; i < ds.nNV;i++)
	{
		
		for (PTRHD p = ds.DS[i]->list_HoaDon; p != NULL;p = p->pNext)
		{
			if (p->info.SoHoaDOn == x)
			{
				return true;
			}
		}
	}
	
	return false;
}

bool nhapHoaDon(DS_NhanVien ds,PTRHD& l,HoaDon &hd)
{
	int checkMa = 0;
	gotoxy(7, 20);
	cout << "Them Hoa Don";

	gotoxy(2, 25);
	cout << "So Hoa Don:    ";
	gotoxy(2, 27);
	cout << "Ngay Lap:   ";
	gotoxy(2, 29);
	cout << "Loai:  ";

	hd.SoHoaDOn = "";
	do {

		int lengh = hd.SoHoaDOn.length();
		gotoxy(25 + lengh, 25);
		hd.SoHoaDOn = nganDauCachMASo(hd.SoHoaDOn);
		if (SearchHD(ds,l, hd.SoHoaDOn)==true)
		{

			InThongBao("So Hoa Don Ton Tai");
			checkMa = 0;
		}
		else
		{
			checkMa = 1;
		}

	} while (checkMa == 0);


	XoaThongBao();


	string Loai;
	Date date;
	Time(date.ngay, date.thang, date.nam);
	gotoxy(25, 27);
	cout << date.ngay << " / " << date.thang << " / " << date.nam;
	hd.ngayLap = date;
	gotoxy(25, 29);
	hd.Loai = chiChoPhepNhap2Chu("");


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
					Init(hd.list_CT_HoaDon);
					return true;
				}

			}


		}

	}


}

void ThemHoaDon(DS_NhanVien ds,PTRHD& l)
{
	Yescursortype();
	
	XoaKhuVucHienThi();
	XoaThongBao();
	HoaDon hd;
	Yescursortype();
	if (nhapHoaDon(ds,l, hd) == true)
	{
		Add(l, GetNode(hd));
		InThongBao("Them Thanh Cong");

	}

	XoaKhuVucHienThi();

}
void xuatHoaDon(HoaDon hd, int stt)
{

	gotoxy(15, 21 + stt * 2);
	cout << hd.SoHoaDOn;
	gotoxy(35, 21 + stt * 2);
	cout << hd.ngayLap.ngay << " / " << hd.ngayLap.thang << " / " << hd.ngayLap.nam;
	gotoxy(65, 21 + stt * 2);
	if (hd.Loai== "N" )
		cout << "Nhap";
	else
	{
		cout << "Xuat";
	}


	
}
void xuatDanhSachHoaDon(PTRHD l)
{
	XoaKhuVucHienThi();
	Nocursortype();

	textcolor(7);

	gotoxy(15, 19);
	cout << "So Hoa Don";

	gotoxy(35, 19);
	cout << "Ngay Lap";

	gotoxy(65, 19);
	cout << "Loai";

	int k = 0;
	for (PTRHD p = l; p != NULL; p = p->pNext)
	{
		xuatHoaDon(p->info, k++);
	}
}




NhanVien* Search(DS_NhanVien DSNV, string x)
{
	for (int i = 0; i < DSNV.nNV;i++)
	{
		if (DSNV.DS[i]->MaNV == x)
		{
			return DSNV.DS[i];
		}
	}
	return NULL;
}
void AddNhanVien(DS_NhanVien& DSNV, NhanVien* nv)
{
	if (DSNV.nNV == 0)
	{
		DSNV.DS[0] = nv;
		return;
	}
	
	string temp = DSNV.DS[0]->Ten + DSNV.DS[0]->Ho;		
	string temp2 = nv->Ten + nv->Ho;
	string temp1;
	if (temp.compare(temp2) > 0)
	{
		for (int j = DSNV.nNV; j > 0;j--)
		{
			DSNV.DS[j] = DSNV.DS[j - 1];
		}
		DSNV.DS[0] = nv;
			return;
	}

	
	for (int i = 0; i < DSNV.nNV-1;i++)
	{
		 temp = DSNV.DS[i]->Ten + DSNV.DS[i]->Ho;
		  temp1 = DSNV.DS[i+1]->Ten + DSNV.DS[i+1]->Ho;
		 temp2 = nv->Ten + nv->Ho;
		if (temp.compare(temp2) < 0 && temp1.compare(temp2) > 0)
		{
			for (int j = DSNV.nNV; j > i + 1;j--)
			{
				DSNV.DS[j] = DSNV.DS[j - 1];
			}
			DSNV.DS[i + 1] = nv;
			return;
		}
	}
	DSNV.DS[DSNV.nNV] = nv;
}
bool nhapNhanVien(DS_NhanVien &DSNV)
{
	NhanVien* nv = new NhanVien;
	int checkMa = 0;
	gotoxy(7, 20);
	cout << "Them Nhan Vien";

	gotoxy(2, 25);
	cout << "Ma Nhan Vien:    ";
	gotoxy(2, 27);
	cout << "Ho:              ";
	gotoxy(2, 29);
	cout << "Ten:             ";
	gotoxy(2, 31);
	cout << "Phai:            ";

	nv->MaNV = "";
	do {

		int lengh = nv->MaNV.length();
		gotoxy(25 + lengh, 25);
		nv->MaNV = nganDauCachMASo(nv->MaNV);
		if (Search(DSNV, nv->MaNV) != NULL)
		{
			InThongBao("Ma Nhan Vien Da Ton Tai");
			checkMa = 0;
		}
		else
		{
			XoaThongBao();
			checkMa = 1;
		}

	} while (checkMa == 0);

	gotoxy(25, 27);
	nv->Ho = nganDauCachThua("", 50);
	gotoxy(25, 29);
	nv->Ten = nganDauCachThua("", 10);
	gotoxy(25, 31);
	nv->Phai = nhapNamOrNu();

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
					nv->list_HoaDon = NULL;

					AddNhanVien(DSNV, nv);
					DSNV.nNV++;
					
					return true;
				}

			}


		}

	}

}
void ThemDanhSachNhanVien(DS_NhanVien &DSNV)
{
	XoaThongBao();
	XoaKhuVucHienThi();
	Yescursortype();
	if (nhapNhanVien( DSNV) == true)
	{
		
		InThongBao("Them Thanh Cong");
	}
	XoaKhuVucHienThi();

}

void xuatNhanVien(NhanVien nv, int stt)
{
	gotoxy(15, 21 + stt * 2);
	cout << nv.MaNV;
	gotoxy(35, 21 + stt * 2);
	cout <<nv.Ho;
	gotoxy(65, 21 + stt * 2);
	cout << nv.Ten;
	gotoxy(90, 21 + stt * 2);
	cout << nv.Phai;

}
void xuatDanhSacNhanVien(DS_NhanVien DSNV)
{
	Nocursortype();

	textcolor(7);

	gotoxy(15, 19);
	cout << "Ma Nhan Vien";

	gotoxy(35, 19);
	cout << "Ho";

	gotoxy(65, 19);
	cout << "Ten";


	gotoxy(90, 19);
	cout << "Phai";
		
	for (int i = 0; i < DSNV.nNV; i++)
	{
		
		xuatNhanVien(*DSNV.DS[i], i);
	}
}
void xoaNhanVien(DS_NhanVien& DSNV)
{
	XoaKhuVucHienThi();
	Yescursortype();
	XoaThongBao();
	gotoxy(7, 20);
	cout << "Xoa Nhan Vien";

	gotoxy(2, 25);
	cout << "Ma Nhan Vien Can Xoa:    ";
	gotoxy(25, 25);
	string MaNVXoa = nganDauCachMASo("");



	for (int i = 0; i < DSNV.nNV;i++)
	{

		if (MaNVXoa == DSNV.DS[i]->MaNV)
		{
			if (DSNV.DS[i]->list_HoaDon != NULL)
			{
				InThongBao("Nhan Vien Da Lap Hoa Don. Khong The Xoa");
				return;
			}

			InThongBao("Ban co chac chan xoa Nhan Vien co MS: " + MaNVXoa + " khong ? (Y/N)");

			while (!_kbhit())// doi  bat phim
			{
				int key = _getch();
				if (key == 89 || key == 121)//Y/y
				{
					delete DSNV.DS[i];
					for (int k = i+1; k < DSNV.nNV; k++)
					{
						DSNV.DS[k-1]=DSNV.DS[k];
					}
					DSNV.nNV--;
					XoaThongBao();
					InThongBao("Xoa Thanh Cong Nhan Vien Co MS: " + MaNVXoa + ".");
					XoaKhuVucHienThi();
					Nocursortype();
					return;
				}
				else if (key == 78 || key == 110) // N || n
				{
					XoaKhuVucHienThi();
					Nocursortype();
					return;
				}

			}
		}

		InThongBao("Khong Co Nhan Vien Co MS: " + MaNVXoa + ".");

		XoaKhuVucHienThi();
		Nocursortype();


	}
}
bool SuaNhanVien(NhanVien &nv)
{
	int checkMa = 0;
	int length = 0;
	int key, vitri = 0;
	gotoxy(7, 20);
	cout << "Sua Nhan Vien";

	gotoxy(2, 25);
	cout << "Ma Nhan Vien:    ";
	gotoxy(2, 27);
	cout << "Ho:   ";
	gotoxy(2, 29);
	cout << "Ten:  ";
	gotoxy(2, 31);
	cout << "Phai: ";

	gotoxy(25, 25);
	cout << nv.MaNV;
	gotoxy(25, 27);
	cout << nv.Ho;
	gotoxy(25, 29);
	cout << nv.Ten;
	gotoxy(25, 31);
	cout << nv.Phai;

	string MaNV = nv.MaNV, ho = nv.Ho, ten = nv.Ten, phai = nv.Phai;

	

	length = ho.length();
	gotoxy(25 + length, 27);
	ho = nganDauCachThua(ho, 10);

	length = ten.length();
	gotoxy(25 + length, 29);
	ten = nganDauCachThua(ten, 10);

	length = phai.length();
	gotoxy(25 + length, 31);	
	do
	{ 
		key = _getch();
			if (key == 13)
			{
				break;
			}
			else
			{
				gotoxy(25, 31);
				cout << "     ";
				gotoxy(25 + length, 31);
				phai = nhapNamOrNu();
				break;
			}
	} while (true);
	



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
					nv.Ho = ho;
					nv.Ten = ten;
					nv.Phai = phai;

					return true;
				}

			}


		}

	}
}
void SapXepNhanVien(DS_NhanVien& DSNV)
{
	string ten, ten1;
	NhanVien *tg;
	for (int i = 0; i < DSNV.nNV - 1; i++) {
		for (int j = i + 1; j < DSNV.nNV; j++) {
			 ten = DSNV.DS[i]->Ten + DSNV.DS[i]->Ho;
			 ten1 = DSNV.DS[j]->Ten + DSNV.DS[j]->Ho;
			if (ten   > ten1) {
				// Hoan vi 2 so a[i] va a[j]
				tg = DSNV.DS[i];
				DSNV.DS[i] = DSNV.DS[j];
				DSNV.DS[j] = tg;
			}
		}
	}
}
void SuaDanhSachNhanVien(DS_NhanVien& DSNV)
{
	XoaKhuVucHienThi();	
	XoaThongBao();
	Yescursortype();
	gotoxy(7, 20);
	cout << "Sua Nhan Vien";

	gotoxy(2, 25);
	cout << "Ma Nhan Vien Can Sua:    ";
	gotoxy(25, 25);
	string MaNVSua = nganDauCachMASo("");
	int i = 0;
	bool checkTimKiem = false;
	for ( i =0; i < DSNV.nNV;i++)
	{
		if (DSNV.DS[i]->MaNV == MaNVSua)
		{
			checkTimKiem = true;
			break;
		}
	}

	if (checkTimKiem == false)
	{
		InThongBao("Ma Nhan Vien Khong Ton Tai");
		XoaKhuVucHienThi();
		Nocursortype();
		return;
	}
	XoaKhuVucHienThi();


	if (SuaNhanVien(*DSNV.DS[i]) == true)
	{
		InThongBao("Sua Thanh Cong");
		SapXepNhanVien(DSNV);
	}
	XoaKhuVucHienThi();
	Nocursortype();
}