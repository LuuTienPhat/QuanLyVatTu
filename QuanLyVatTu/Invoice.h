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
	int num = stof(VAT);
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

//Tim kiem node hoa don trong danh sach hoa don
NodeInvoice* searchInvoiceList(InvoiceList& first, string invoiceId) {
	if (isInvoiceListEmpty(first)) return NULL;

	for (NodeInvoice* p = first; p != NULL; p = p->pNext) {
		if (invoiceId.compare(p->invoice.invoiceNumber) == 0) {
			return p;
		}
	}
	return NULL;
}

//Them tat ca cac truong hop trong danh sach hoa don
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

//Xoa tat ca cac truong hop trong danh sach hoa don
void deleteInvoiceFromList(InvoiceList& first, string invoiceNumber) {
	if (isInvoiceListEmpty(first)) return;

	if (first->invoice.invoiceNumber.compare(invoiceNumber) == 0) {
		NodeInvoice* p = first;    // nut can xoa la nut dau
		first = p->pNext;
		delete p;
		return;
	}

	NodeInvoice* q = nullptr;
	NodeInvoice* p = nullptr; //node dung truoc node q;
	for (q = first; q != NULL; q = q->pNext) {
		if (q->invoice.invoiceNumber.compare(invoiceNumber) == 0) {
			break;
		}
		p = q;
	}

	if (q != nullptr) { 
		if (q->pNext != NULL) { //DELETE AFTER
			p->pNext = q->pNext;
		}
		else { //DELETE LAST
			p->pNext = NULL;
		}
		delete q;
	}
}

//==================== KIEM TRA DU LIEU NHAP VAO ====================

//Kiem tra so hoa don co trung khong
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

//Kiem tra loai hoa don la 'X' hay 'N'
string checkType(string type) {
	string import1 = "N";
	string export1 = "X";
	if (type.empty()) return "LOAI HOA DON khong duoc de trong";
	if (type.compare(import1) != 0 && type.compare(export1) != 0)
		return "LOAI HOA DON la 'N' hoac 'X'";
	return "";
}











//Them vao dau danh sach hoa don
void insertFirst(InvoiceList& first, Invoice& invoice) {
	NodeInvoice* p;
	p = new NodeInvoice;
	p->invoice = invoice;
	p->pNext = first;
	first = p;
}

//Them vao cuoi danh sach hoa don
void insertLast(InvoiceList& last, Invoice& invoice) {
	NodeInvoice* p;
	p = new NodeInvoice;
	p->invoice = invoice;
	last->pNext = p;
	last = p;
}

//Them co thu tu trong danh sach hoa don
void insertOrder(InvoiceList& first, Invoice& invoice) {
	if (first == NULL) {  // Insert First
		insertFirst(first, invoice);
		return;
	}

	NodeInvoice* k = new NodeInvoice;
	k = first;
	for (NodeInvoice* p = k; p != NULL; p = p->pNext) {
		if (invoice.invoiceNumber.compare(p->invoice.invoiceNumber) < 0) {
			break;
		}
	}

	if (k == first) {
		insertFirst(first, invoice);
		return;
	}

	NodeInvoice* q;
	q = new NodeInvoice;
	q->invoice = invoice;
	q->pNext = k->pNext;
	k->pNext = q;
}

//Xoa phan tu dau trong danh sach hoa don
void deleteFirst(InvoiceList& first) {
	if (isInvoiceListEmpty(first)) return;
	NodeInvoice* p = first;    // nut can xoa la nut dau
	first = p->pNext;
	delete p;
}
