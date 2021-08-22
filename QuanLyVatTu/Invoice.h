#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include "Struct.h"
#include "Product.h"
#include "Employee.h"
using namespace std;


//==================== CHI TIET HOA DON ====================

//KHOI TAO DANH SACH CHI TIET HOA DON
void initInvoiceDetailList(InvoiceDetailList& invoiceDetailList) {
	invoiceDetailList.number = 0;
}

//KIEM TRA DANH SACH CHI TIET HOA DON DAY
bool isInvoiceDetailListFull(InvoiceDetailList& invoiceDetailList) {
	if (invoiceDetailList.number == MAX_INVOICE_DETAIL)
		return true;
	return false;
}

//KIEM TRA DANH SACH CHI TIET HOA DON RONG
bool isInvoiceDetailListEmpty(InvoiceDetailList& invoiceDetailList) {
	if (invoiceDetailList.number == 0)
		return true;
	return false;
}

void newInvoiceDetail(InvoiceDetail& invoiceDetail, string productId, int quantity, float price, float VAT) {
	invoiceDetail.price = price;
	invoiceDetail.productId = productId;
	invoiceDetail.quantity = quantity;
	invoiceDetail.VAT = VAT;
}

//TIM CHI TIET HOA DON
int searchInvoiceDetail(InvoiceDetailList& invoiceDetailList, string productId) {
	//TRA VE INDEX TRONG DANH SACH CHI TIET HOA DON
	for (int i = 0; i < invoiceDetailList.number; i++) {
		if (productId.compare(invoiceDetailList.invoiceDetail[i].productId) == 0)
			return i;
	}
	//KHONG TIM THAY TRA VE -1
	return -1;
}

//THEM CHI TIET HOA DON
void insertInvoiceDetail(InvoiceDetailList& invoiceDetailList, InvoiceDetail& invoiceDetail) {
	invoiceDetailList.invoiceDetail[invoiceDetailList.number] = invoiceDetail;
	invoiceDetailList.number++;
}

//XOA CHI TIET HOA DON
void deleteInvoiceDetail(InvoiceDetailList& invoiceDetailList, string productId) {
	int i = searchInvoiceDetail(invoiceDetailList, productId);
	if (i == -1) return;
	else {
		for (int j = i; j < invoiceDetailList.number; j++) {
			invoiceDetailList.invoiceDetail[j] = invoiceDetailList.invoiceDetail[j + 1];
		}
	}
	invoiceDetailList.number--;
}


//=================== KIEM TRA DU LIEU NHAP VAO CHI TIET HOA DON ===================

//KIEM TRA SO LUONG XUAT
string checkQuantityExport(string quantity, string newQuantity) {
	if (newQuantity.empty()) return "SO LUONG XUAT khong duoc de trong";

	if (!is_number(newQuantity)) return "SO LUONG XUAT phai la so";

	int q = stoi(quantity);
	int nq = stoi(newQuantity);
	if (nq <= 0) return "SO LUONG XUAT > 0";
	if (q < nq) return "SO LUONG XUAT <= SO LUONG TON";
	return "";
}

//KIEM TRA SO LUONG NHAP
string checkQuantityImport(string quantity) {
	if (quantity.empty()) return "SO LUONG NHAP khong duoc de trong";

	if (!is_number(quantity)) return "SO LUONG NHAP phai la so";

	int q = stoi(quantity);
	if (q <= 0) return "SO LUONG NHAP > 0";
	return "";
}

//KIEM TRA GIA
string checkPrice(string price) {
	if (price.empty()) return "DON GIA khong duoc de trong";

	if (!is_number(price)) return "DON GIA phai la so";

	int num = stoi(price);
	if (num <= 0) return "DON GIA > 0";
	return "";
}

//KIEM TRA VAT
string checkVAT(string VAT) {
	if (VAT.empty()) return "VAT khong duoc de trong";
	if (!is_number(VAT)) return "VAT phai la so";

	/*for (int i = 0; i < VAT.length(); i++) {
		if (VAT[i] == 32 && isalpha(VAT[i + 1])) {
			return "VAT phai la so";
		}
		else if (isalpha(VAT[i])) {
			return "VAT phai la so";
		}
	}*/
	float num = stof(VAT);
	if (num < 0) return "VAT >= 0";
	return "";
}


//==================== DANH SACH HOA DON ====================

//KHOI TAO DANH SACH HOA DON
InvoiceList initInvoiceList() {
	InvoiceList invoiceList = NULL;
	return invoiceList;
}

//KIEM TRA DANH SACH HOA DON RONG
bool isInvoiceListEmpty(InvoiceList& first) {
	if (first == NULL) return true;
	return false;
}

//TAO HOA DON MOI
void newInvoice(Invoice& invoice, string invoiceNumber, Date& date, string EmployeeId, char type) {
	invoice.invoiceNumber = invoiceNumber;
	invoice.date = date;
	invoice.type = type;
	initInvoiceDetailList(invoice.invoiceDetailList);
}

//TIM KIEM NODE HOA DON
NodeInvoice* searchInvoiceList(InvoiceList& first, string invoiceId) {
	if (isInvoiceListEmpty(first)) return NULL;

	for (NodeInvoice* p = first; p != NULL; p = p->pNext) {
		if (invoiceId.compare(p->invoice.invoiceNumber) == 0) {
			return p;
		}
	}
	return NULL;
}

//THEM HOA DON VAO DANH SACH HOA DON
void insertInvoice(InvoiceList& first, Invoice& invoice)
{
	NodeInvoice* p = new NodeInvoice;
	NodeInvoice* t = new NodeInvoice;
	NodeInvoice* s = new NodeInvoice;  // t la nut truoc, s la nut sau
	p->invoice = invoice;

	for (s = first; s != NULL && s->invoice.invoiceNumber.compare(invoice.invoiceNumber) < 0; t = s, s = s->pNext);
	if (s == first)  // them nut vao dau danh sach lien ket
	{
		p->pNext = first;
		first = p;
	}
	else // them nut p vao truoc nut s
	{
		p->pNext = s;
		t->pNext = p;
	}
}

//DEM SO LUONG HOA DON
int countInvoice(InvoiceList& first) {
	int count = 0;
	for (NodeInvoice* p = first; p != NULL; p = p->pNext) {
		count++;
	}
	return count;
}


//==================== KIEM TRA DU LIEU NHAP VAO ====================

//KIEM TRA SO HOA DON CO TRUNG KHONG
string checkInvoiceNumber(EmployeeList& emloyeeList, string& invoiceNumber, string& employeeId) {
	if (invoiceNumber.empty()) return "SO HOA DON khong duoc de trong";
	if (invoiceNumber.length() > 20) return "SO HOA DON toi da 20 ki tu";
	for (int i = 0; i < emloyeeList.number; i++) {
		for (NodeInvoice* p = emloyeeList.employee[i]->invoiceList; p != NULL; p = p->pNext) {
			if (p->invoice.invoiceNumber.compare(invoiceNumber) == 0) {
				return "SO HOA DON da ton tai";
			}
		}
	}
	return "";
}

//KIEM TRA LOAI HOA DON LA 'X' HAY 'N'
string checkType(string type) {
	string import1 = "N";
	string export1 = "X";
	if (type.empty()) return "LOAI HOA DON khong duoc de trong";
	if (type.compare(import1) != 0 && type.compare(export1) != 0)
		return "LOAI HOA DON la 'N' hoac 'X'";
	return "";
}



//==================== THONG KE HOA DON ====================

//SAP XEP DANH SACH THONG KE HOA DON THEO NGAY/THANG/NAM
void sortStatListByDate(StatList &statList) {
	
	for (int i = 0; i < statList.number - 1; i++) {
		for (int j = 0; j < statList.number - i - 1; j++) {
			Date d1 = statList.nodes[j].nodeInvoice->invoice.date;
			Date d2 = statList.nodes[j + 1].nodeInvoice->invoice.date;

			if (isDateAfter(d1, d2)) {
				swap(statList.nodes[j], statList.nodes[j + 1]);
			}
		}
	}
}

//TRA VE DANH SACH THONG KE HOA DON
StatList makeStatList(EmployeeList& employeeList, Date& fromDate, Date& toDate) {
	//DANH SACH THONG KE HOA DON
	StatList statList;
	statList.nodes = new Stat[statList.init];

	for (int i = 0; i < employeeList.number; i++) {

		//LAY DANH SACH HOA DON CUA TUNG NHAN VIEN
		InvoiceList list = employeeList.employee[i]->invoiceList;

		//DUYET DANH SACH HOA DON DO
		for (NodeInvoice* p = list; p != NULL; p = p->pNext) {
			Date d = p->invoice.date;

			//KIEM TRA NGAY LAP HOA DON CO NAM TRONG KHOANG KHONG
			if (isDateAfterOrSame(d, fromDate) && isDateBeforeOrSame(d, toDate))
			{
				//NEU DANH SACH THONG KE DAY
				if (statList.init == statList.number) {
					StatList statList2;
					statList2.init = statList.init;
					statList2.nodes = new Stat[statList.number];
					for (int m = 0; m < statList.number; m++) {
						statList2.nodes[m] = statList.nodes[m];
						statList2.number++;
					}
					delete[] statList.nodes;

					statList.number = 0;
					statList.init = statList2.init + 100;
					statList.nodes = new Stat[statList.init];
					for (int m = 0; m < statList2.number; m++) {
						statList.nodes[m] = statList2.nodes[m];
						statList.number++;
					}
					delete[] statList2.nodes;
				}

				statList.nodes[statList.number].index = i;
				statList.nodes[statList.number].nodeInvoice = p;

				double money = 0;
				InvoiceDetailList invoiceDetailList = p->invoice.invoiceDetailList;

				//DUYET DANH SACH CHI TIET HOA DON CUA HOA DON DO
				for (int j = 0; j < invoiceDetailList.number; j++)
				{
					InvoiceDetail invoiceDetail = invoiceDetailList.invoiceDetail[j];
					money += (double)invoiceDetail.quantity * invoiceDetail.price + (invoiceDetail.price * invoiceDetail.quantity * invoiceDetail.VAT / 100);
				}

				statList.nodes[statList.number].money = money;
				statList.number++;

			}
		}
	}

	sortStatListByDate(statList);
	return statList;
}