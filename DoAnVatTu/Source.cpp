#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include "myLib.h"
#include "VatTu.h"
#include "NhanVien.h"
#include "LietKe.h"
#include "ThongKe.h"
#include "File.h"
#include "Top10VatTu.h"
using namespace std;


bool kiemTraXoaVatTu(DS_NhanVien& DSNV,string &Ma)
{
	XoaKhuVucHienThi();
	Yescursortype();
	XoaThongBao();
	gotoxy(7, 20);
	cout << "Xoa Vat Tu";

	gotoxy(2, 25);
	cout << "Ma Vat Tu Can Xoa:    ";
	gotoxy(25, 25);
	string MaVTXoa = nganDauCachMASo("");
	Nocursortype();
	for (int i = 0;i< DSNV.nNV;i++)
	{
		for (PTRHD p = DSNV.DS[i]->list_HoaDon; p != NULL; p = p->pNext)
		{

			for (PTR q = p->info.list_CT_HoaDon; q != NULL; q = q->pNext)
			{
				if (q->info.MaVT == MaVTXoa)
				{
					InThongBao("Vat Tu Nay Da Co Trong Hoa Don. Khong The Xoa");
					return false;
				}
			}

		}
	}
	Ma = MaVTXoa;
	return true;
}
bool kiemTraSuaVatTu(DS_NhanVien& DSNV, string& Ma)
{
	XoaKhuVucHienThi();
	Yescursortype();
	XoaThongBao();
	gotoxy(7, 20);
	cout << "Sua Vat Tu";

	gotoxy(2, 25);
	cout << "Ma Vat Tu Can Sua:    ";
	gotoxy(25, 25);
	string MaVTSua = nganDauCachMASo("");

	Nocursortype();
	for (int i = 0;i < DSNV.nNV;i++)
	{
		for (PTRHD p = DSNV.DS[i]->list_HoaDon; p != NULL; p = p->pNext)
		{

			for (PTR q = p->info.list_CT_HoaDon; q != NULL; q = q->pNext)
			{
				if (q->info.MaVT == MaVTSua)
				{
					InThongBao("Vat Tu Nay Da Co Trong Hoa Don. Khong The Sua");
					return false;
				}
			}

		}
	}
	Ma = MaVTSua;
	return true;
}
void MenuPhu(int vitri, Tree& t, PTRHD& listHD, PTR& l, DS_NhanVien& DSNV,string tinhtrang = NULL)
{

	int vitri2 = 0;
	string MaNV;
	bool checkNV = false;
	string arrTuKhoa2[5][4] = { { "Nhap Vat Tu","Cap Nhap Vat Tu","Xoa Vat Tu","Xem Danh Sach Vat Tu" },
								{ "Nhap Nhan Vien","Cap Nhap Nhan Vien","Xoa Nhan Vien","Xem Danh Sach Nhan Vien" },
								{ "Nhap Hoa Don","Xem Danh Sach Hoa Don","","" },
								{ "Nhap Chi Tiet Hoa Don","Cap Nhap Chi Tiet Hoa Don","Xoa CT Hoa Don","Xem Danh Sach Chi Tiet Hoa Don" },
								{ "Nhap Chi Tiet Hoa Don","Xem Danh Sach Chi Tiet Hoa Don","","" }
	};
	
	gotoxy(45, 17);
	cout << arrTuKhoa2[vitri][vitri2];

	gotoxy(52, 5);
	cout << "                                     ";
	gotoxy(52, 5);
	cout << arrTuKhoa2[vitri][1];


	if (vitri == 4)
	{
		textcolor(setMauBoChon);
		for (int i = 2; i < 4;i++)
		{
			gotoxy(52, 3 + i * 2);
			cout << "                                     ";
		}
	}

	string MaVTXoa, MaVTSua;
	textcolor(setMauChon);
	gotoxy(52, 3 + vitri2 * 2);
	cout << arrTuKhoa2[vitri][vitri2];
	int key;


	while (true)
	{

		while (!_kbhit())
		{
			key = _getch();
			if (key == 224)
			{
				key = _getch();
				if (key == 80 && vitri2 < 3)
				{
					if (vitri == 2 && vitri2 > 0)
					{
						continue;
					}
					if (vitri == 4 && vitri2 > 0)
					{
						continue;
					}
					textcolor(setMauBoChon);
					gotoxy(52, 3 + vitri2 * 2);
					cout << arrTuKhoa2[vitri][vitri2];

					gotoxy(45, 17);
					cout << "                                 ";

					vitri2++;
					gotoxy(45, 17);
					cout << arrTuKhoa2[vitri][vitri2];
					textcolor(setMauChon);
					gotoxy(52, 3 + vitri2 * 2);
					cout << arrTuKhoa2[vitri][vitri2];


				}
				else if (key == 72 && vitri2 > 0)
				{
					textcolor(setMauBoChon);
					gotoxy(52, 3 + vitri2 * 2);
					cout << arrTuKhoa2[vitri][vitri2];
					gotoxy(45, 17);
					cout << "                                 ";
					vitri2--;
					gotoxy(45, 17);
					cout << arrTuKhoa2[vitri][vitri2];
					textcolor(setMauChon);
					gotoxy(52, 3 + vitri2 * 2);
					cout << arrTuKhoa2[vitri][vitri2];



				}
				else if (key == 75)
				{
					textcolor(setMauBoChon);
					gotoxy(45, 17);
					cout << "                                 ";
					gotoxy(40, 17);
					cout << "     ";
					gotoxy(52, 3 + vitri2 * 2);
					cout << arrTuKhoa2[vitri][vitri2];
					XoaKhuVucHienThi();
					return;
				}
			}
			else if (key == 13)
			{
				textcolor(setMauBoChon);
				switch (vitri)
				{
				case 0:
					switch (vitri2)
					{
					case 0:
						ThemDanhSachVatTu(t);
						break;
					case 1:
						if (kiemTraSuaVatTu(DSNV, MaVTSua) == true)
						{
							SuaDanhSachVatTu(t,MaVTSua);
						}
						break;
					case 2:
						
							if (kiemTraXoaVatTu(DSNV, MaVTXoa) == true)
							{
								xoaVatTu(t, MaVTXoa);
							}

						
						break;
					case 3:
						xuatDanhSachVatTu(t);
						break;
					}

					break;
				case 1:
					switch (vitri2)
					{
					case 0:
						ThemDanhSachNhanVien(DSNV);
						break;
					case 1:
						SuaDanhSachNhanVien(DSNV);
						break;
					case 2:
						xoaNhanVien(DSNV);
						break;
					case 3:
						xuatDanhSacNhanVien(DSNV);
						break;
					}
					break;
				case 2:

							switch (vitri2)
							{
							case 0:
								ThemHoaDon(DSNV,listHD);
								break;
							case 1:
								xuatDanhSachHoaDon(listHD);
								break;
							}
				
					break;
				case 3:
					switch (vitri2)
					{
					case 0:
						ThemCT_HoaDon(t, l, tinhtrang);
						break;
					case 1:
						SuaDanhSachCT_HoaDon(t, l, tinhtrang);
						break;
					case 2:
						xoaCT_HoaDon(t, l, tinhtrang);
						break;
					case 3:
						xuatDanhSachCT_HoaDon(l);
						break;
					}
					break;
				case 4:
					switch (vitri2)
					{
					case 0:
						ThemCT_HoaDon(t, l, tinhtrang);
						break;
					case 1:
						xuatDanhSachCT_HoaDon(l);
						break;
					}
					break;
				}

			}
		}
	}

}
void QuanLy()
{
	Tree t;
	Init(t);
	PTR l;
	Init(l);
	PTRHD listHD;
	InitHD(listHD);

	DS_NhanVien DSNV;
	DSNV.nNV = 0;

	OpenFile(t);
	readBinary(DSNV);
	GiaoDienMenu();
	string arrTuKhoa[] = { "Danh Sach Vat Tu","Danh Sach Nhan Vien","Danh Sach Hoa Don","Danh Sach Chi Tiet Hoa Don","Thong Ke Cac Hoa Don","In 10 Vat Tu Co Doanh Thu Cao Nhat","Thong Ke Doanh Thu 1 Nam" };
	
	GiaoDienMenuChon(arrTuKhoa);
	int vitri = 0, key , vitri2=0;
	

	gotoxy(2, 17);
	cout << arrTuKhoa[vitri];
	textcolor(setMauChon);
	gotoxy(2, 3 + vitri * 2);
	cout << arrTuKhoa[vitri];

	GiaoDienMenuChonHai(vitri);
	while (true)
	{

		while (!_kbhit())
		{
			
			key = _getch();
			if (key == 224)
			{
				key = _getch();
				if (key == 80 && vitri < 6)
				{
					XoaThongBao();
					XoaKhuVucHienThi();
					textcolor(setMauBoChon);
					gotoxy(2, 3 + vitri * 2);
					cout << arrTuKhoa[vitri];
					XoaGiaoDienMenuChonHai();

					gotoxy(2, 17);
					cout << "                                   ";

					vitri++;
					textcolor(setMauChon);
					gotoxy(2, 3 + vitri * 2);
					cout << arrTuKhoa[vitri];
					GiaoDienMenuChonHai(vitri);

					textcolor(setMauBoChon);
					gotoxy(2, 17);
					cout << arrTuKhoa[vitri];
				}
				else if (key == 72 && vitri > 0)
				{
				
					XoaThongBao();
					XoaKhuVucHienThi();
					textcolor(setMauBoChon);
					gotoxy(2, 3 + vitri * 2);
					cout << arrTuKhoa[vitri];
					XoaGiaoDienMenuChonHai();

					gotoxy(2, 17);
					cout << "                                   ";

					vitri--;
					textcolor(setMauChon);
					gotoxy(2, 3 + vitri * 2);
					cout << arrTuKhoa[vitri];
					GiaoDienMenuChonHai(vitri);

					textcolor(setMauBoChon);
					gotoxy(2, 17);
					cout << arrTuKhoa[vitri];
				}
				else if (key == 77)
				{
					gotoxy(40, 17);
					cout << " >>> ";
					
					if (vitri == 2)
					{
						Yescursortype();
						gotoxy(2, 25);
						cout << "Ma Nhan Vien Can Xem Hoa Don: ";
						gotoxy(35, 25);
						string MaNV = nganDauCachMASo("");
						Nocursortype();
						bool checkNV = false;
						for (int i = 0; i < DSNV.nNV;i++)
						{
							if (DSNV.DS[i]->MaNV == MaNV)
							{
								checkNV = true;		
								listHD = DSNV.DS[i]->list_HoaDon;
								XoaThongBao();
								XoaKhuVucHienThi();
								MenuPhu(vitri, t, listHD, l, DSNV,"");

								DSNV.DS[i]->list_HoaDon = listHD;
								int dem = 0;
								for (PTRHD p = listHD;p != NULL;p = p->pNext)
								{
									dem++;
								}
								DSNV.DS[i]->nList = dem;
								break;
							}
						}
						
						if (checkNV == false)
						{
							InThongBao("Khong Tim Thay Nhan Vien Co Ma: " + MaNV);
							break;
						}
						break;
						
					}
					else if (vitri == 3)
					{
						Yescursortype();
						gotoxy(2, 25);
						cout << "Ma Hoa Don Can Xem CT_Hoa Don: ";
						gotoxy(35, 25);
						string MaHD = nganDauCachMASo("");
						Nocursortype();
						bool check = false;
						for (int i = 0; i < DSNV.nNV;i++)
						{								
							for (PTRHD p = DSNV.DS[i]->list_HoaDon; p != NULL; p = p->pNext)
							{
								if (p->info.SoHoaDOn == MaHD)
								{
									check = true;
									l = p->info.list_CT_HoaDon;
									XoaThongBao();
									XoaKhuVucHienThi();
									if (l != NULL)
									{
										MenuPhu(4, t, listHD, l, DSNV, p->info.Loai);
									}
									else
									{
										MenuPhu(vitri, t, listHD, l, DSNV, p->info.Loai);
									}
									

									p->info.list_CT_HoaDon = l;
									int dem = 0;
									for (PTR q = l;q != NULL;q = q->pNext)
									{
										dem++;
									}
									p->info.nList = dem;
									break;
								}
							}
						}
						if (check == false)
						{
							InThongBao("Khong Tim Thay Hoa Don Co Ma: " + MaHD);
							break;
						}
						break;
					}
					if (vitri == 4)
					{
						XoaThongBao();
						XoaKhuVucHienThi();
						LietKe(DSNV);
						break;
					}
					if (vitri == 6)
					{
						XoaThongBao();
						XoaKhuVucHienThi();
						ThongKeNam(DSNV);
						break;
					}
					if (vitri == 5)
					{
						XoaThongBao();
						XoaKhuVucHienThi();
						Top10(DSNV,t);
						break;
					}					
					else
					{
						XoaThongBao();
						XoaKhuVucHienThi();						
						MenuPhu(vitri, t, listHD, l, DSNV,"");
						break;
					}
					
					
				}
			}
			else if (key == 0)
			{
				key = _getch();
			}
			
			else if (key == 27)
			{
				SaveFile(t);
				writeBinary(DSNV);
				clrscr();
				return;
			}

		}

	}
}
int main()
{
	setFullScreen();
	Nocursortype();
	QuanLy();
	
	_getch();
	return 0;
}
#endif