#pragma once
#include<iostream>
#include "myLib.h"
#include "NhanVien.h"


using namespace std;
struct Top
{
	string MaVT;	
	string TenVT;	
	int TriGia;
};
struct DS_Top
{
	Top tk[MAX];
	int nTop = 0;
};

void khoiTaoTop(Tree t,DS_Top &ds)
{
	if (t != NULL)
	{
		khoiTaoTop(t->pLeft,ds);
		ds.tk[ds.nTop].MaVT = t->Data.MaVT;
		ds.tk[ds.nTop].TenVT = t->Data.TenVT;
		ds.tk[ds.nTop++].TriGia = 0;
		khoiTaoTop(t->pRight,ds);
	}
}



void Xuat(Top ds, int stt)
{

	gotoxy(15, 22 + stt * 2);
	cout << stt;
	gotoxy(35, 22 + stt * 2);
	cout << ds.MaVT;
	gotoxy(65, 22 + stt * 2);
	
	cout << ds.TenVT;

	gotoxy(90, 22 + stt * 2);
	cout << ds.TriGia;

}
void sapXepTop10(DS_Top& dsTop)
{
	for (int i = 0; i < dsTop.nTop - 1; i++) {
		for (int j = i + 1; j < dsTop.nTop; j++) {

			if (dsTop.tk[i].TriGia < dsTop.tk[j].TriGia) {

				Top tg = dsTop.tk[i];
				dsTop.tk[i] = dsTop.tk[j];
				dsTop.tk[j] = tg;
			}
		}
	}
}
void Top10(DS_NhanVien& DSNV,Tree t)
{
	DS_Top ds;
	ds.nTop = 0;
	string arrTuKhoaCT_HoaDon[5] = { "So HD", "Ngay Lap", "Loai HD", "Tri Gia Hoa Don" };
	khoiTaoTop(t,ds);

	gotoxy(30, 19);
	cout << "10 Vat Tu Co Doanh Thu Cao Nhat Trong Khoang Thoi Gian";
	gotoxy(30, 20);
	cout << "Tu Ngay:   /  /       Den Ngay:   /  /    ";

	gotoxy(15, 21);
	cout << "STT";

	gotoxy(35, 21);
	cout << "Ma Vat Tu";

	gotoxy(65, 21);
	cout << "Ten Vat Tu";


	gotoxy(90, 21);
	cout << "Tri Gia Hoa Don";

	Yescursortype();
	Date dateTu = nhapNgayThang(39, 20);
	Date dateDen = nhapNgayThang(62, 20);
	Nocursortype();
	//int MaNV;
	int k = 0;
	if (kiemTraNgay(dateTu) && kiemTraNgay(dateDen) && SoSanhNgayLietKe(dateDen, dateTu) == 1 || kiemTraNgay(dateTu) && kiemTraNgay(dateDen) && SoSanhNgayLietKe(dateDen, dateTu) == 0)
	{

		Nocursortype();
		for (int i = 0; i < DSNV.nNV;i++)
		{
			for (PTRHD p = DSNV.DS[i]->list_HoaDon; p != NULL; p = p->pNext)
			{
				if (SoSanhNgayLietKe(p->info.ngayLap, dateTu) == 1 && SoSanhNgayLietKe(p->info.ngayLap, dateDen) == -1 && p->info.Loai=="X" || SoSanhNgayLietKe(p->info.ngayLap, dateTu) == 0 && SoSanhNgayLietKe(p->info.ngayLap, dateDen) == 0 && p->info.Loai == "X")
				{
					
					k = 1;
					for (PTR q = p->info.list_CT_HoaDon; q != NULL; q = q->pNext)
					{
						int trigia = 0, kq = 0;
						kq = q->info.SoLuong * q->info.DonGia;
						trigia += kq + (q->info.VAT * kq) / 100;
						for (int k = 0; k < ds.nTop;k++)
						{
							if (ds.tk[k].MaVT == q->info.MaVT)
							{
								ds.tk[k].TriGia += trigia;
							}
						}
					}
					
					
				}
			}
		}

	}
	else
	{
		InThongBao("Ngay Khong Ton tai.");
		return;
	}

	if (k == 0)
	{
		InThongBao("Khong Co Hoa Don Nao Trong Khoang Thoi Gian Nay.");
	}
	int key;
	sapXepTop10(ds);
	int n;
	if (ds.nTop < 10) 
	{
		n = ds.nTop;
	}
	else
	{
		n = 10;
	}
	for (int k = 0; k < n;k++)
	{
		Xuat(ds.tk[k], k+1);
	}
	while (true)
	{
		while (!_kbhit())
		{
			key = _getch();
			if (key == 0)
			{
				key = _getch();
			}
			else if (key == 224)
			{
				key = _getch();
			}
			else if (key == 27) // esc
			{
				XoaKhuVucHienThi();
				return;
			}
		}

	}

}