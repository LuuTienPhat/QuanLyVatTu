#pragma once
#include <iostream>
#include <string>
using namespace std;

#define WIDTH_MAIN_FRAME 160
#define HEIGHT_MAIN_FRAME 40

//=================== POP UP ===================
#define WIDTH_POP_UP 61;
#define HEIGHT_POP_UP 20;
#define BACKGROUND_COLOR_POP_UP 7;

#define COLOR_BLACK 0
#define COLOR_DEFAULT 51
#define COLOR_BACKGROUND_DEFAULT 51
#define COLOR_RED 4
#define COLOR_LIGHT_RED 12
#define COLOR_GREEN_LIGHT 2
#define COLOR_YELLOW 6
#define COLOR_LIGHT_YELLOW 14
#define COLOR_WHITE 7
#define COLOR_BRIGHT_WHITE 15

#define TEXT_LEFT -1
#define TEXT_CENTER 0
#define TEXT_RIGHT 1


#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define BACKSPACE 8
#define ESC 27
#define TAB 9
#define ENTER 13
#define F1 59
#define F2 60
#define F3 61
#define F4 62
#define DELETE_KEY 83
#define INSERT_KEY 82
#define YES 1
#define NO -1
#define CTRL_F 6

const int MAX_EMPLOYEE = 500;
const int MAX_INVOICE_DETAIL = 20;

//========== NGAY/THANG/NAM ==========
struct Date {
	int day; //ngay
	int month; //thang
	int year; //nam
};


//========== DANH SACH VAT TU ==========
struct Product {
	string productId; // 10 ki tu
	string productName; // ten vat tu
	string unit; // don vi tinh
	int quantity = 0; // so luong ton

	bool isUsed = false; //kiem tra vat tu co trong hoa don nao chua
};

struct NodeProduct {
	Product product;

	//pointer
	NodeProduct* pLeft;
	NodeProduct* pRight;
};

typedef struct NodeProduct* ProductList;

//========== CHI TIET HOA DON ==========
struct InvoiceDetail { //Danh sach tuyen tinh
	string productId; // 10 ki tu

	int quantity = 0; // so luong
	float price = 0; // gia
	float VAT = 0;
};

struct InvoiceDetailList {
	int number = 0;
	InvoiceDetail invoiceDetail[MAX_INVOICE_DETAIL];
};


//========== DANH SACH HOA DON ==========
struct Invoice {
	string invoiceNumber; //20 ki tu
	Date date;
	char type; // X: xuat, N: nhap

	InvoiceDetailList invoiceDetailList; //ds chi tiet hoa don
};

struct NodeInvoice {
	Invoice invoice;
	NodeInvoice* pNext;
};

typedef struct NodeInvoice* InvoiceList;

//========== DANH SACH NHAN VIEN ==========
struct Employee {
	string employeeId; //ma nhan vien
	string firstname; //ten
	string lastname; //ho va ten lot
	string gender; //gioi tinh

	//con tro den ds hoa don
	InvoiceList invoiceList;
};

struct EmployeeList { //Mang con tro
	int number = 0;
	Employee* employee[MAX_EMPLOYEE];
};

//==================== SAP XEP DANH SACH NHAN VIEN THEO TEN ====================
struct Index {
	int index; //vi tri cua nhan vien trong danh sach nhan vien
	string firstname; //ten
	string lastname; //ho
	
};

struct IndexList { //DANH SACH TUYEN TINH CAP PHAT DONG
	int number = 0;
	Index* nodes;
};


//==================== SAP XEP DANH SACH VAT TU THEO TEN ====================
struct NodeIndex { 
	NodeProduct* nodeProduct;
};

struct NodeIndexList { //DANH SACH TUYEN TINH CAP PHAT DONG
	int number = 0;
	int init = 0;
	NodeIndex* nodes;
};

//==================== THONG KE DANH SACH HOA DON ====================
const int  MAX_STAT_LIST = 1000;

struct Stat { 
	NodeInvoice* nodeInvoice; //giu dia chi cua node hoa don
	int index = 0; //vi tri cua nhan vien trong danh sach nhan vien
	double money = 0; //gia tri cua hoa don do
};

struct StatList {
	int number = 0;
	Stat* nodes[MAX_STAT_LIST];
};


//==================== THONG KE TOP DOANH THU ====================
struct Sales {
	NodeProduct* nodeProduct; //node vat tu
	double money = 0; //doanh thu vat tu do
};

struct SalesList { //DANH SACH CAP PHAT DONG
	int number = 0; 
	Sales* nodes;
};