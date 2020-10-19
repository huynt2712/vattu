#pragma once
#include "VatTu.h"
#include<fstream>
#include "NhanVien.h"
struct VatTuGF
{
	char MaVT[50];
	char TenVT[50];
	char DVT[50];
	int SoLuongTon;
};
struct NhanVienGF
{
	char MaNV[50];
	char Ho[50];
	char Ten[50];
	char Phai[3];
	PTRHD list_HoaDon;
	int nList;

	
};
struct HoaDonGF
{
	char SoHoaDOn[50];
	Date ngayLap;
	char Loai[50];
	PTR list_CT_HoaDon;
	int nList;

};
struct CT_HoaDonGF
{
	char MaVT[50];
	int SoLuong;
	int DonGia;
	int VAT;

};
void DuyetCay(Tree& t, FILE*& f)
{
	if (t != NULL)
	{

		VatTuGF vtGF;


		vtGF.SoLuongTon = t->Data.SoLuongTon;
		
		strcpy(vtGF.MaVT, t->Data.MaVT.c_str());
		strcpy(vtGF.TenVT, t->Data.TenVT.c_str());
		strcpy(vtGF.DVT, t->Data.DVT.c_str());

		fwrite(&vtGF, sizeof(VatTuGF), 1, f);


		
		DuyetCay(t->pLeft, f);
		DuyetCay(t->pRight, f);
	}
}

void SaveFile(Tree& t) {
	FILE* f;
	if ((f = fopen("DanhSachVatTu.txt", "wb")) == NULL)
	{

	}
	DuyetCay(t, f);
	fclose(f);


}

void OpenFile(Tree& t) {
	FILE* f;
	if ((f = fopen("DanhSachVatTu.txt", "rb")) == NULL)
	{

	}

	VatTuGF vtGF;
	while (fread(&vtGF, sizeof(VatTuGF), 1, f) != 0)
	{
		 VatTu vt;
		vt.MaVT = vtGF.MaVT;
		vt.TenVT = vtGF.TenVT;
		vt.DVT = vtGF.DVT;
		vt.SoLuongTon = vtGF.SoLuongTon;
	

		InSert(t, vt);
	}
	fclose(f);


}


// xuất file nhị phân
void writeBinary(DS_NhanVien& DSNV)
{
	ofstream file("DanhSachNhanVien.txt", ios::out | ios::binary);
	for (int i = 0; i < DSNV.nNV; i++)
	{
		NhanVienGF nvGF;
		strcpy(nvGF.MaNV, DSNV.DS[i]->MaNV.c_str());
		strcpy(nvGF.Ho, DSNV.DS[i]->Ho.c_str());
		strcpy(nvGF.Ten, DSNV.DS[i]->Ten.c_str());
		strcpy(nvGF.Phai, DSNV.DS[i]->Phai.c_str());
		nvGF.list_HoaDon = DSNV.DS[i]->list_HoaDon;
		nvGF.nList = DSNV.DS[i]->nList;
		file.write(reinterpret_cast<char*>(&nvGF), sizeof(NhanVienGF));
		for (PTRHD p = DSNV.DS[i]->list_HoaDon; p != NULL; p = p->pNext)
		{
			HoaDonGF hdGF;
		
			strcpy(hdGF.SoHoaDOn, p->info.SoHoaDOn.c_str());
			hdGF.ngayLap = p->info.ngayLap;

			hdGF.nList = p->info.nList;
			strcpy(hdGF.Loai, p->info.Loai.c_str());
			file.write(reinterpret_cast<char*>(&hdGF), sizeof(HoaDonGF));
			
			for (PTR q = p->info.list_CT_HoaDon; q != NULL; q = q->pNext)			
			{
				CT_HoaDonGF CT_hdGF;
				
				strcpy(CT_hdGF.MaVT, q->info.MaVT.c_str());
				CT_hdGF.DonGia = q->info.DonGia;
				CT_hdGF.SoLuong = q->info.SoLuong;
				CT_hdGF.VAT = q->info.VAT;
			
				file.write(reinterpret_cast<char*>(&CT_hdGF), sizeof(CT_HoaDonGF));

			}
		}
	}
	file.close();
}
//đọc file nhị phân
void readBinary(DS_NhanVien& DSNV)
{
	ifstream file("DanhSachNhanVien.txt", ios::in | ios::binary);
	while (!file.eof())
	{
		NhanVienGF nvgf;
		NhanVien* nv = new NhanVien;
		file.read(reinterpret_cast<char*>(&nvgf), sizeof(NhanVienGF));

		nv->MaNV = nvgf.MaNV;
		nv->Ho = nvgf.Ho;
		nv->Ten = nvgf.Ten;
		nv->Phai = nvgf.Phai;


		
		nv->list_HoaDon = nvgf.list_HoaDon;
		nv->nList = nvgf.nList;
		InitHD(nv->list_HoaDon);
		for (int i = 0; i < nv->nList; i++)
		{
			HoaDon hd;
			HoaDonGF hdGF;
			file.read(reinterpret_cast<char*>(&hdGF), sizeof(HoaDonGF));			
			hd.SoHoaDOn = hdGF.SoHoaDOn;
			hd.ngayLap = hdGF.ngayLap;
			hd.Loai = hdGF.Loai;
			hd.nList = hdGF.nList;

			Init(hd.list_CT_HoaDon);
			for (int j = 0; j < hd.nList; j++)
			{

				CT_HoaDon CT_hd;


				CT_HoaDonGF CT_hdGF;
				
				file.read(reinterpret_cast<char*>(&CT_hdGF), sizeof(CT_HoaDonGF));
				CT_hd.MaVT = CT_hdGF.MaVT;
				CT_hd.DonGia = CT_hdGF.DonGia;
				CT_hd.SoLuong = CT_hdGF.SoLuong;			
				CT_hd.VAT = CT_hdGF.VAT;
				Add(hd.list_CT_HoaDon, GetNode(CT_hd));
			
			}
			Add(nv->list_HoaDon, GetNode(hd));
		}

		AddNhanVien(DSNV, nv);
		DSNV.nNV++;

	}
	DSNV.nNV--;
	file.close();
}
