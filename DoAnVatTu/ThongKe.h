#pragma once
#include<iostream>
#include "myLib.h"
#include "NhanVien.h"

using namespace std;
struct ThongKeTheoNam
{
	int thang;
	double doanhThu;
};
struct DS_ThongKe
{
	ThongKeTheoNam tk[12];

};
//int SoSanhNgayThongke(Date a, Date b)
//{
//	if (a.nam > b.nam)
//	{
//		return 1;
//	}
//	else if (a.nam < b.nam)
//	{
//		return -1;
//	}
//	else
//	{
//		if (a.thang > b.thang)
//		{
//			return 1;
//		}
//		else if (a.thang < b.thang)
//		{
//			return -1;
//		}
//		else
//		{
//			if (a.ngay > b.ngay)
//			{
//				return 1;
//			}
//			else if (a.ngay < b.ngay)
//			{
//				return -1;
//			}
//			else
//				return 0;
//		}
//	}
//}

void Xuat(ThongKeTheoNam tk, int stt)
{
	gotoxy(15, 22 + stt );
	cout << tk.thang;
	gotoxy(35, 22 + stt );
	cout << tk.doanhThu;
	

}
void DuyetCay(DS_NhanVien& DSNV, int nam, DS_ThongKe& ds_tk)
{
	
	for(int i = 0; i < DSNV.nNV;i++ )
	{
		
		for (PTRHD p = DSNV.DS[i]->list_HoaDon; p != NULL; p = p->pNext)
		{
			if (p->info.ngayLap.nam == nam && p->info.Loai == "X")
			{
				int trigia = 0, kq = 0;
				
				for (PTR q = p->info.list_CT_HoaDon; q != NULL; q = q->pNext)
				{
					kq = q->info.SoLuong * q->info.DonGia;
					trigia += kq + (q->info.VAT * kq) / 100;
				}
				ds_tk.tk[p->info.ngayLap.thang - 1].doanhThu += trigia;
			}
		}
		
	}
}
void khoiTao(DS_ThongKe& ds_tk)
{
	for (int i = 0; i < 12; i++)
	{
		ds_tk.tk[i].thang = i + 1;
		ds_tk.tk[i].doanhThu = 0;
	}
}
void ThongKeNam(DS_NhanVien& DSNV)
{
	DS_ThongKe ds_tk;
	khoiTao(ds_tk);
	

	gotoxy(30, 19);
	cout << "Bang Thong Ke Doanh Thu Nam: ";	
	Yescursortype();
	gotoxy(80, 19);
	int nam = chiDuocNhapSo(0, 4);
	Nocursortype();
	
	gotoxy(15, 21);
	cout << "Thang";

	gotoxy(35, 21);
	cout << "Doanh Thu";

	DuyetCay(DSNV, nam, ds_tk);
	for (int i = 0; i < 12; i++)
	{
		Xuat(ds_tk.tk[i], i);
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