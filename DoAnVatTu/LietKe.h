#pragma once
#include<iostream>
#include "myLib.h"
#include "NhanVien.h"


using namespace std;
struct LietKeHD
{
	string SoHD;
	Date ngayLap;
	string LoaiHD;
	string ten;
	int TriGia;
};
Date nhapNgayThang(int x, int y)
{
	Date date;
	gotoxy(x, y);
	date.ngay = chiDuocNhapSo(0, 2);
	gotoxy(x + 3, y);
	date.thang = chiDuocNhapSo(0, 2);
	gotoxy(x + 6, y);
	date.nam = chiDuocNhapSo(0, 4);
	return date;
}
int SoSanhNgayLietKe(Date a, Date b)
{
	if (a.nam > b.nam)
	{
		return 1;
	}
	else if (a.nam < b.nam)
	{
		return -1;
	}
	else
	{
		if (a.thang > b.thang)
		{
			return 1;
		}
		else if (a.thang < b.thang)
		{
			return -1;
		}
		else
		{
			if (a.ngay > b.ngay)
			{
				return 1;
			}
			else if (a.ngay < b.ngay)
			{
				return -1;
			}
			else
				return 0;
		}
	}
}
bool kiemTraNgay(Date date)
{
	int ngay = date.ngay, thang = date.thang, nam = date.nam;
	bool checkNam = false;
	int soNgayMax;
	if (nam % 4 == 0 && nam % 100 != 0 || nam % 400 == 0)
	{
		checkNam = true;
	}
	if (thang > 12)
	{
		return false;
	}
	else
	{
		switch (thang)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			soNgayMax = 31;
			break;
		case 2:
			if (checkNam)
			{
				soNgayMax = 29;
			}
			else
			{
				soNgayMax = 28;
			}
			break;
		default:
			soNgayMax = 30;
			break;
		}
	}
	if (ngay > soNgayMax)
	{
		return false;
	}
	return true;
}
void Xuat(LietKeHD lk, int stt)
{

	gotoxy(15, 22 + stt * 2);
	cout << lk.SoHD;
	gotoxy(35, 22 + stt * 2);
	cout << lk.ngayLap.ngay << " / " << lk.ngayLap.thang << " / " << lk.ngayLap.nam;
	gotoxy(65, 22 + stt * 2);
	if (lk.LoaiHD == "N")
	{
		cout << "Nhap";
	}
	else
	{
		cout << "Xuat";
	}
	gotoxy(80, 22 + stt * 2);
	cout << lk.ten;

	gotoxy(110, 22 + stt * 2);
	
	cout << lk.TriGia;

}
void LietKe(DS_NhanVien& DSNV)
{
	string arrTuKhoaCT_HoaDon[5] = { "So HD", "Ngay Lap", "Loai HD", "Tri Gia Hoa Don" };


	gotoxy(30, 19);
	cout<< "Bang Liet Ke Cac Hoa Don Trong Khoang Thoi Gian";
	gotoxy(30, 20);
	cout << "Tu Ngay:   /  /       Den Ngay:   /  /    ";

	gotoxy(15, 21);
	cout << "So HD";

	gotoxy(35, 21);
	cout << "Ngay Lap";

	gotoxy(65, 21);
	cout << "Loai HD";

	gotoxy(80, 21);
	cout << "Ho Ten NV Lap";

	gotoxy(110, 21);
	cout << "Tri Gia Hoa Don";
	
	Yescursortype();
	Date dateTu = nhapNgayThang(39, 20);
	Date dateDen = nhapNgayThang(62, 20);
	Nocursortype();
	//int MaNV;
	int k = 0;
	if (kiemTraNgay(dateTu) && kiemTraNgay(dateDen) && SoSanhNgayLietKe(dateDen, dateTu) == 1|| kiemTraNgay(dateTu) && kiemTraNgay(dateDen) && SoSanhNgayLietKe(dateDen, dateTu) == 0)
	{
		
		Nocursortype();
		for (int i = 0; i < DSNV.nNV;i++)
		{
				for (PTRHD p = DSNV.DS[i]->list_HoaDon; p != NULL; p = p->pNext)
				{
					if (SoSanhNgayLietKe(p->info.ngayLap, dateTu) == 1 && SoSanhNgayLietKe(p->info.ngayLap, dateDen) == -1 || SoSanhNgayLietKe(p->info.ngayLap, dateTu) == 0 && SoSanhNgayLietKe(p->info.ngayLap, dateDen) == 0)
					{
						LietKeHD lkhd;
						lkhd.SoHD = p->info.SoHoaDOn;
						lkhd.ngayLap = p->info.ngayLap;
						lkhd.LoaiHD = p->info.Loai;
						lkhd.ten = DSNV.DS[i]->Ho + " " + DSNV.DS[i]->Ten;
						int trigia = 0, kq = 0;
						for (PTR q = p->info.list_CT_HoaDon; q != NULL; q = q->pNext)						
						{
							kq = q->info.SoLuong * q->info.DonGia;
							trigia += kq + (q->info.VAT * kq) / 100;
						}
						lkhd.TriGia = trigia;
						Xuat(lkhd, k++);
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