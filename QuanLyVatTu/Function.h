#pragma once
#include "Struct.h"
#include "Product.h"
#include "Employee.h"
#include "mylib.h"
#include "Date.h"
#include "File.h"
#include <conio.h>
#include <iostream>
#include "Invoice.h"
#include <sstream>
#include <thread>
#include <iomanip> 

using namespace std;

void employeeTable(EmployeeList& employeeList, IndexList& sortedEmployeeList, bool isSearch);
void menu(boolean isInit);
void productTable(ProductList& productList, NodeIndexList& sortedProductList, bool isSearched);
int invoiceTable(EmployeeList& employeeList, int employeeIndex, ProductList& productList, Invoice& invoice);
void invoiceDetailListTable(EmployeeList& employeeList, int employeeIndex, ProductList& productList, NodeIndexList& sortedProductList, Invoice& invoice, bool isSearch);
void tableFooter(int x, int y, int* width, int column, int backgroundColor, int textColor, string text);
void tableHeader(int x, int y, int* width, int column, int backgroundColor, int textColor, string* text);


//---------- BIEN CHUOI THUONG THANH CHUOI IN KHI NHAP ----------
string toUpperCaseWhileTyping() {
	string string = "";
	char character;
	character = _getch();

	int x = whereX();
	int y = whereY();
	while (character != 13) {
		if (character == 8 || character == 46)
		{
			if (string.empty()) {
				continue;
			}

			string.pop_back();
			gotoXY(x + string.length(), y);
			cout << char(32);

			gotoXY(x + string.length(), y);
			character = _getch();
		}
		else {
			string.push_back(char(toupper(character)));
			cout << char(toupper(character));
			character = _getch();
		}
	}
	return string;
}

string trim(string s) {
	if (s.empty()) return s;
	//xu ly khoang trang dau
	while (s[0] == ' ')
		s.erase(s.begin() + 0);

	//xu ly khoang trang cuoi
	while (s[s.length() - 1] == ' ')
		s.erase(s.length() - 1);

	return s;
}

int stringToInt(string s) {
	stringstream geek(s);
	int i = 0;
	geek >> i;
	return i;
}

string intToString(int n) {
	stringstream str;
	str << n;
	return str.str();
}

float stringToFloat(string s) {
	stringstream geek(s);
	float i = 0;
	geek >> i;
	return i;
}

string floatToString(float f, int pre) {
	stringstream floatString;
	floatString << fixed << setprecision(pre);
	floatString << f;
	return floatString.str();
}

string generateSpace(int length) {
	string s;
	while (s.length() < length - 1) {
		s += " ";
	}
	return s;
}

void upperCaseWhileTyping(int x, int y, string& text, char& key) {
	ShowCur(1);
	setTextColor(COLOR_LIGHT_YELLOW);
	setBackgroundColor(COLOR_BLACK);

	if (!text.empty()) {
		gotoXY(x, y);
		cout << text;
	}
	else {
		gotoXY(x, y);
	}
	while (true) { // Note: chua xu li duoc truong hop nhan nhieu backspace lien tiep
		if (key == -32 || key == ESC || key == F4) {
			return;
		}
		else if (key == BACKSPACE)
		{
			if (text.empty()) {
				key = _getch();
			}
			else {
				text.pop_back();
				gotoXY(x + text.length(), y);
				cout << char(32);
				gotoXY(x + text.length(), y);
			}
		}
		else if (key >= 1 && key <= 255 && isprint(key) != 0) {
			text.push_back(char(toupper(key)));
			cout << char(toupper(key));
		}
		key = _getch();

	}
}

void upperCaseWhileTypingEnter(int x, int y, string& text, char& key) {
	ShowCur(1);
	setTextColor(COLOR_LIGHT_YELLOW);
	setBackgroundColor(COLOR_BLACK);

	if (!text.empty()) {
		gotoXY(x, y);
		cout << text;
	}
	else {
		gotoXY(x, y);
	}
	while (true) { // Note: chua xu li duoc truong hop nhan nhieu backspace lien tiep
		if (key == ENTER || key == ESC) {
			return;
		}
		else if (key == UP || key == DOWN || key == LEFT || key == RIGHT) {}
		else if (key == BACKSPACE)
		{
			if (text.empty()) {
				key = _getch();
			}
			else {
				text.pop_back();
				gotoXY(x + text.length(), y);
				cout << char(32);
				gotoXY(x + text.length(), y);
			}
		}
		else if (key >= 1 && key <= 255 && isprint(key) != 0) {
			text.push_back(char(toupper(key)));
			cout << char(toupper(key));
		}
		key = _getch();

	}
}

string floatToCurrency(double money) {
	string currency = to_string(money);
	int decimal = currency.find('.');
	if (decimal == std::string::npos) {
		decimal = currency.length();
	}

	if (decimal > 3)
	{
		for (int x = decimal - 3; x > 0; x -= 3)
			currency.insert(x, ",");
	}

	int i = currency.find('.');
	return currency.substr(0, i);
}

string doubleToCurrency(double money) {
	string currency = to_string(money);
	int decimal = currency.find('.');
	if (decimal == std::string::npos) {
		decimal = currency.length();
	}

	if (decimal > 3)
	{
		for (int x = decimal - 3; x > 0; x -= 3)
			currency.insert(x, ",");
	}

	int i = currency.find('.');
	return currency.substr(0, i);
}

string ChuSo[10]{ " khong", " mot", " hai", " ba"," bon", " nam", " sau", " bay", " tam", " chin" };
string Tien[6]{ "", " nghin", " trieu", " ty", " nghin ty", " trieu ty" };

string DocSo3ChuSo(int baso)
{
	int tram, chuc, donvi;
	string KetQua = "";
	tram = (int)(baso / 100);
	chuc = (int)((baso % 100) / 10);
	donvi = baso % 10;
	if ((tram == 0) && (chuc == 0) && (donvi == 0)) return "";
	if (tram != 0)
	{
		KetQua += ChuSo[tram] + " tram";
		if ((chuc == 0) && (donvi != 0)) KetQua += " linh";
	}
	if ((chuc != 0) && (chuc != 1))
	{
		KetQua += ChuSo[chuc] + " muoi";
		if ((chuc == 0) && (donvi != 0)) KetQua = KetQua + " linh";
	}
	if (chuc == 1) KetQua += " muoi";
	switch (donvi)
	{
	case 1:
	{
		if ((chuc != 0) && (chuc != 1))
		{
			KetQua += " mot";
		}
		else
		{
			KetQua += ChuSo[donvi];
		}
		break;
	}
	case 5:
	{
		if (chuc == 0)
		{
			KetQua += ChuSo[donvi];
		}
		else
		{
			KetQua += " lam";
		}
		break;
	}
	default:
	{
		if (donvi != 0)
		{
			KetQua += ChuSo[donvi];
		}
		break;
	}
	}
	return KetQua;
}

string DocTienBangChu(long SoTien, string strTail)
{
	int lan, i;
	long so;
	string KetQua = "", tmp = "";
	int* ViTri = new int[6];
	if (SoTien < 0) return "So am";
	if (SoTien == 0) return "Khong " + strTail;
	if (SoTien > 0)
	{
		so = SoTien;
	}
	else
	{
		so = -SoTien;
	}

	if (SoTien > 8999999999999999)
	{
		SoTien = 0;
		return "";
	}
	ViTri[5] = (int)(so / 1000000000000000);
	so = so - ViTri[5] * 1000000000000000;
	ViTri[4] = (int)(so / 1000000000000);
	so = so - ViTri[4] * +1000000000000;
	ViTri[3] = (int)(so / 1000000000);
	so = so - ViTri[3] * 1000000000;
	ViTri[2] = (int)(so / 1000000);
	ViTri[1] = (int)((so % 1000000) / 1000);
	ViTri[0] = (int)(so % 1000);
	if (ViTri[5] > 0)
	{
		lan = 5;
	}
	else if (ViTri[4] > 0)
	{
		lan = 4;
	}
	else if (ViTri[3] > 0)
	{
		lan = 3;
	}
	else if (ViTri[2] > 0)
	{
		lan = 2;
	}
	else if (ViTri[1] > 0)
	{
		lan = 1;
	}
	else
	{
		lan = 0;
	}
	for (i = lan; i >= 0; i--)
	{
		tmp = DocSo3ChuSo(ViTri[i]);
		KetQua += tmp;
		if (ViTri[i] != 0) KetQua += Tien[i];
		//if ((i > 0) && (!tmp.empty())) KetQua += ",";
	}
	//if (KetQua.substr(KetQua.length() - 1, 1) == ",") KetQua = KetQua.substr(0, KetQua.length() - 1);
	KetQua = trim(KetQua) + " " + strTail;
	return KetQua.substr(0, 1) + KetQua.substr(1);
}

//==================== VE HOP ====================
void box(int x, int y, int width, int height, int backgroundColor, int textColor, string text, int textAlignment) {
	setTextColor(backgroundColor);
	for (int j = y; j <= y + height - 1; j++) {
		for (int i = x; i <= x + width - 1; i++) {
			gotoXY(i, j);
			cout << char(219);
		}
	}

	setBackgroundColor(backgroundColor);
	setTextColor(textColor);

	if (textAlignment == TEXT_LEFT) {
		gotoXY(x, y + height / 2);
		cout << text;
	}

	else if (textAlignment == TEXT_CENTER) {
		gotoXY(x + getCenterX(width, text.length()), y + height / 2);
		cout << text;
	}

	else {
		gotoXY(x + width - text.length() - 1, y + height / 2);
		cout << text;
	}


}

void n_box(int x, int y, int width, int height, int backgroundColor, int textColor, string* text, int number) {
	for (int i = 0; i < number; i++) {
		box(x, y + (i * 4), width, height, backgroundColor, textColor, text[i], TEXT_CENTER);
	}
}

void box2(int x, int y, int width, int height, int backgroundColor, int textColor, string text) {
	setTextColor(backgroundColor);
	for (int ix = x; ix < x + width; ix++) {
		gotoXY(ix, y);
		cout << char(196);
		gotoXY(ix, y + height);
		cout << char(196);
	}

	for (int iy = y; iy < y + height; iy++) {
		gotoXY(x, iy);
		cout << char(179);
		gotoXY(x + width, iy);
		cout << char(179);
	}

	gotoXY(x, y); cout << char(218);
	gotoXY(x + width, y); cout << char(191);
	gotoXY(x, y + height); cout << char(192);
	gotoXY(x + width, y + height); cout << char(217);

	/*setTextColor(textColor);
	gotoXY(x + getCenterX(width, text.length()), y + height / 2);
	setBackgroundColor(backgroundColor);
	cout << text;*/
}

void box3(int x, int y, int width, int height, int backgroundColor, int textColor, string text) {
	setTextColor(backgroundColor);
	/*if (height <= 1 || width <= 1) return;*/

	for (int iy = y; iy <= y + height; iy++) {
		gotoXY(x, iy);
		cout << char(179);
		gotoXY(x + width, iy);
		cout << char(179);
	}

	setTextColor(textColor);
	gotoXY(x + 1, y + 1);
	cout << text;
}

int warningPopUp(string message) {
	ShowCur(0);
	int height = 10;
	int width = 50; //50
	int x = getCenterX(WIDTH_MAIN_FRAME, width);
	int y = getCenterY(HEIGHT_MAIN_FRAME, height);
	int xInput = x + 9;
	int yInput = y + 6;
	int boxWidth = 12;
	int boxHeight = 3;
	int boxDistance = 10;

	//ve bang pop up
	box(x, y, width, height, COLOR_WHITE, COLOR_BLACK, "", TEXT_CENTER);
	box(x, y, width, 1, COLOR_RED, COLOR_BRIGHT_WHITE, "THONG BAO", TEXT_CENTER);
	box(x, y + 3, width, 1, COLOR_WHITE, COLOR_BLACK, message, TEXT_CENTER);

	const int number = 2;
	string data[number] = { "CO" , "KHONG" };
	box(xInput, yInput, boxWidth, boxHeight, COLOR_RED, COLOR_BRIGHT_WHITE, data[0], TEXT_CENTER);
	box(xInput + boxDistance * 2, yInput, boxWidth, boxHeight, COLOR_RED, COLOR_BRIGHT_WHITE, data[1], TEXT_CENTER);

	int xPointer = xInput;
	int yPointer = yInput;
	int xPointerOld = xPointer;
	int yPointerOld = yPointer;
	int backgroundColorChoose = 7;
	int i = 0;
	int iOld = i;
	bool isClicked = true;


	while (true)
	{
		if (isClicked)
		{
			box(xPointerOld, yPointerOld, boxWidth, boxHeight, COLOR_RED, COLOR_BRIGHT_WHITE, data[iOld], TEXT_CENTER);
			box(xPointer, yPointer, boxWidth, boxHeight, COLOR_LIGHT_YELLOW, COLOR_BLACK, data[i], TEXT_CENTER);
			xPointerOld = xPointer;
			iOld = i;
			isClicked = false;
		}

		char key = _getch();
		switch (key)
		{
		case -32:
			isClicked = true;
			key = _getch();
			if (key == LEFT && i != 0)
			{
				xPointer -= boxDistance * 2;
				if (i > 0) i--;
			}
			else if (key == RIGHT && i < (number - 1))
			{
				xPointer += boxDistance * 2;
				if (i < (number + 1)) i++;
			}
			key = char();
			break;

		case ESC:
			return NO;
			break;

		case ENTER:
		{
			if (i == 0) return YES;
			if (i == 1) return NO;
			break;
		}
		default:
			break;
		}
	}
}

int notificationPopUp(string message) {
	ShowCur(0);
	int height = 10;
	int width = 50; //50
	int x = getCenterX(WIDTH_MAIN_FRAME, width);
	int y = getCenterY(HEIGHT_MAIN_FRAME, height);
	int xInput = x + 19;
	int yInput = y + 6;
	int boxWidth = 12;
	int boxHeight = 3;
	int boxDistance = 10;

	//ve bang pop up
	box(x, y, width, height, COLOR_WHITE, COLOR_BLACK, "", TEXT_CENTER);
	box(x, y, width, 1, COLOR_RED, COLOR_BRIGHT_WHITE, "THONG BAO", TEXT_CENTER);
	box(x, y + 3, width, 1, COLOR_WHITE, COLOR_BLACK, message, TEXT_CENTER);

	const int number = 1;
	string data[number] = { "OK" };
	box(xInput, yInput, boxWidth, boxHeight, COLOR_RED, COLOR_BRIGHT_WHITE, data[0], TEXT_CENTER);

	int xPointer = xInput;
	int yPointer = yInput;
	int xPointerOld = xPointer;
	int yPointerOld = yPointer;
	int backgroundColorChoose = 7;
	int i = 0;
	int iOld = i;
	bool isClicked = true;


	while (true)
	{
		if (isClicked)
		{
			//box(xPointerOld, yPointerOld, boxWidth, boxHeight, COLOR_RED, COLOR_BRIGHT_WHITE, data[iOld]);
			box(xPointer, yPointer, boxWidth, boxHeight, COLOR_LIGHT_YELLOW, COLOR_BLACK, data[i], TEXT_CENTER);
			//xPointerOld = xPointer;
			//iOld = i;
			isClicked = false;
		}

		char key = _getch();
		switch (key)
		{
		case -32:
			break;

		case ESC:
			return YES;
			break;

		case ENTER:
			return YES;
			break;

		default:
			break;
		}
	}
}

void titleBox(int y, int height, string text) {
	int x = getCenterX(WIDTH_MAIN_FRAME, text.length() + 4);
	int width = text.length() + 4;
	box(x, y, width, height, COLOR_LIGHT_YELLOW, COLOR_BLACK, text, TEXT_CENTER);
}

int hotKeyBox(int x, int y, string hotkey, string text) {
	gotoXY(x, y);
	setBackgroundColor(COLOR_RED);
	setTextColor(COLOR_LIGHT_YELLOW);
	cout << " " + hotkey + " ";
	gotoXY(x + hotkey.length() + 2 + 1, y);
	setBackgroundColor(COLOR_BLACK);
	setTextColor(COLOR_LIGHT_YELLOW);
	cout << text;

	return text.length() + 2 + 1 + hotkey.length();
}

void box4(int x, int y, int width, int height, int backgroundColor, int textColor, string text) {
	setTextColor(backgroundColor);
	if (height <= 1 || width <= 1) return;
	for (int ix = x; ix <= x + width; ix++) {
		gotoXY(ix, y);
		cout << char(196);
		gotoXY(ix, y + height);
		cout << char(196);
	}

	gotoXY(x, y);
	cout << char(193);
	gotoXY(x + width, y);
	cout << char(193);
	gotoXY(x, y + height);
	cout << char(196);
	gotoXY(x + width, y + height);
	cout << char(196);

}

void box5(int x, int y, int width, int height, int backgroundColor, int textColor, string text) {
	setTextColor(backgroundColor);
	if (height <= 1 || width <= 1) return;
	//VE CANH TREN DUOI CUA HINH HOP
	for (int ix = x; ix <= x + width; ix++) {
		gotoXY(ix, y);
		cout << char(196);
		gotoXY(ix, y + height);
		cout << char(196);
	}

	//VE 2 CANH BEN CUA HINH HOP
	for (int iy = y; iy <= y + height; iy++) {
		gotoXY(x, iy);
		cout << char(179);
		gotoXY(x + width, iy);
		cout << char(179);
	}
	gotoXY(x, y);
	cout << char(194);
	gotoXY(x + width, y);
	cout << char(194);
	gotoXY(x, y + height);
	cout << char(197);
	gotoXY(x + width, y + height);
	cout << char(197);

	setTextColor(textColor);
	gotoXY(x + 1, y + 1);

	int centerX = getCenterX(width, text.length());
	cout << generateSpace(centerX) << text;

}

void tableFooter(int x, int y, int* width, int column, int backgroundColor, int textColor, string text) {
	int height = 2;
	int ix = x;

	for (int i = 0; i <= column; i++) {
		if (i == column) {
			gotoXY(x, y);
			cout << char(195);
			gotoXY(x, y + 1);
			cout << char(179);
			gotoXY(x, y + 2);
			cout << char(192);

			gotoXY(ix, y);
			cout << char(180);
			gotoXY(ix, y + 1);
			cout << char(179);
			gotoXY(ix, y + 2);
			cout << char(217);
		}
		else {
			box4(ix, y, width[i], height, backgroundColor, textColor, "");
			ix += width[i];
		}

	}
}

void tableHeader(int x, int y, int* width, int column, int backgroundColor, int textColor, string* text) {
	int height = 2;
	int ix = x;
	for (int i = 0; i <= column; i++) {
		if (i == column) {
			setTextColor(backgroundColor);
			gotoXY(x, y);
			cout << char(218);
			gotoXY(x, y + 1);
			cout << char(179);
			gotoXY(x, y + 2);
			cout << char(195);

			setTextColor(backgroundColor);
			gotoXY(ix, y);
			cout << char(191);
			gotoXY(ix, y + 1);
			cout << char(179);
			gotoXY(ix, y + 2);
			cout << char(180);
		}
		else {
			box5(ix, y, width[i], height, backgroundColor, COLOR_LIGHT_YELLOW, text[i]);
			ix += width[i];
		}
	}
}

void coutBox(int x, int y, int width, int align, string text) {
	gotoXY(x, y);
	cout << fixed << setprecision(2);
	if (align == TEXT_RIGHT) {
		int num = width - 2;
		cout << std::right << setw(num);
		cout << text;
	}
	else {
		cout << " " << text;
	}

}

void showEmployeeMakeInvoice(EmployeeList& employeeList, int employeeIndex, Invoice& invoice) {
	setTextColor(COLOR_BRIGHT_WHITE);
	gotoXY(1, 0);
	cout << "MA NHAN VIEN: " << employeeList.employee[employeeIndex]->employeeId;
	gotoXY(1, 1);
	cout << "TEN NHAN VIEN: " << employeeList.employee[employeeIndex]->lastname + " " + employeeList.employee[employeeIndex]->firstname;
	gotoXY(1, 2);
	cout << "SO HOA DON: " << invoice.invoiceNumber;
	gotoXY(1, 3);
	cout << "NGAY LAP: " << dateToString(invoice.date);
	gotoXY(1, 4);
	cout << "LOAI HOA DON: " << (invoice.type == 'X' ? "XUAT" : "NHAP");
}



//=================== THEM VAT TU ===================
int addProductPopUp(ProductList& productList, NodeIndexList& sortedProductList) {
	ShowCur(1);
	int height = HEIGHT_POP_UP;// 61;
	int width = WIDTH_POP_UP; //20;
	int x = getCenterX(WIDTH_MAIN_FRAME, width);
	int y = getCenterY(HEIGHT_MAIN_FRAME, height);
	int backgroundColor = BACKGROUND_COLOR_POP_UP;
	int xInput = x + 18;
	int widthInput = 40;

	//ve bang pop up
	box(x, y, width, height, COLOR_WHITE, COLOR_BLACK, "", TEXT_CENTER);
	box(x, y, width, 1, COLOR_RED, COLOR_BRIGHT_WHITE, "THEM VAT TU", TEXT_CENTER);
	box(x, y + height, width, 1, COLOR_RED, COLOR_BRIGHT_WHITE, " ESC : QUAY LAI", TEXT_LEFT);

	string productId = generateProductId(productList);
	string productName;
	string unit;
	string quantity;

	const int number = 4;
	string title[number] = { "MA VAT TU", "TEN VAT TU", "DON VI TINH", "SO LUONG" };
	for (int i = 0; i <= number; i++) {
		if (i == 4) {
			box(xInput, y + 2 * (i + 1), 10, 3, COLOR_RED, COLOR_BRIGHT_WHITE, "OK", TEXT_CENTER);
		}
		else {
			gotoXY(x + 2, y + 2 * (i + 1));
			setBackgroundColor(COLOR_WHITE);
			setTextColor(COLOR_BLACK);
			cout << title[i];
			box(xInput, y + 2 * (i + 1), widthInput, 1, COLOR_BLACK, COLOR_LIGHT_YELLOW, "", TEXT_CENTER);
		}
	}

	int xPointer = xInput;
	int yPointer = y + 2;
	int xPointerOld = xPointer;
	int yPointerOld = yPointer;
	int backgroundColorChoose = 7;
	int i = 0;
	bool isClicked = true;
	char c = char();

	while (true)
	{
		if (isClicked)
		{
			ShowCur(1);
			if (i == 4) {
				ShowCur(0);
				box(xPointer, y + 2 * 5, 10, 3, COLOR_LIGHT_YELLOW, COLOR_BLACK, "OK", TEXT_CENTER);
			};
			if (i == 0) upperCaseWhileTyping(xPointer, yPointer, productId, c);
			isClicked = false;
		}

		if (i == 4) c = _getch();
		switch (c)
		{
		case -32: //DIEU HUONG LEN/XUONG
		{
			isClicked = true;
			c = _getch();
			if (c == UP && yPointer != y + 2)
			{
				yPointer -= 2;
				if (i == 4) box(xPointer, y + 2 * 5, 10, 3, COLOR_RED, COLOR_BRIGHT_WHITE, "OK", TEXT_CENTER);
				if (i > 0) i--;
			}
			else if (c == DOWN && yPointer != y + 2 * 5)
			{
				yPointer += 2;
				if (i < 5) i++;
			}
			c = char();
			break;
		}

		case ESC: //QUAY LAI BANG VAT TU
		{
			setBackgroundColor(COLOR_BLACK);
			return NO;
			break;
		}

		case ENTER: //NHAN OK DE THEM VAT TU VAO CAY VAT TU
		{
			if (i == 4) {
				box(xPointer, y + height - 6, widthInput, 5, COLOR_RED, COLOR_LIGHT_YELLOW, "", TEXT_LEFT);

				//KIEM TRA CAC DU LIEU NHAP VAO
				string e1 = checkProductId(productList, trim(productId));
				string e2 = checkProductName(trim(productName));
				string e3 = checkUnit(trim(unit));
				string e4 = checkQuantity(trim(quantity));

				int iy = y + height - 6;
				setTextColor(COLOR_BRIGHT_WHITE);
				if (!e1.empty()) { gotoXY(xPointer + 1, iy); cout << e1; iy += 1; }
				if (!e2.empty()) { gotoXY(xPointer + 1, iy); cout << e2; iy += 1; }
				if (!e3.empty()) { gotoXY(xPointer + 1, iy); cout << e3; iy += 1; }
				if (!e4.empty()) { gotoXY(xPointer + 1, iy); cout << e4; iy += 1; }
				if (e1.empty() && e2.empty() && e3.empty() && e4.empty()) {

					//THEM VAO CAY VAT TU
					Product product;
					newProduct(product, trim(productId), trim(productName), trim(unit), stoi(quantity));
					insertProduct(productList, product);

					//THEM VAO DANH SACH VAT TU SAP XEP
					NodeProduct* p = searchProduct(productList, productId);
					insertSortedProductList(sortedProductList, p);

					//GHI FILE
					writeProductFile(productList);
					return YES;
				}
			}
			else {
				continue;
			}
			break;
		}

		default:
		{
			if (i == 0) upperCaseWhileTyping(xPointer, yPointer, productId, c);
			else if (i == 1) upperCaseWhileTyping(xPointer, yPointer, productName, c);
			else if (i == 2) upperCaseWhileTyping(xPointer, yPointer, unit, c);
			else if (i == 3) upperCaseWhileTyping(xPointer, yPointer, quantity, c);
			break;
		}
		}
	}
}

//=================== SUA VAT TU ===================
int editProductPopUp(ProductList& productList, Product& product, NodeIndexList& sortedProductList) {
	ShowCur(1);
	int height = HEIGHT_POP_UP;
	int width = WIDTH_POP_UP;
	int x = getCenterX(WIDTH_MAIN_FRAME, width);
	int y = getCenterY(HEIGHT_MAIN_FRAME, height);
	int xInput = x + 18;
	int yInput = y + 2;
	int widthInputBox = 40;

	string oldProductId = product.productId;
	string productId = product.productId;
	string productName = product.productName;
	string unit = product.unit;

	const int number = 3;
	string title[number] = { "MA VAT TU", "TEN VAT TU", "DON VI TINH" };
	string data[number] = { oldProductId, productName, unit };

	box(x, y, width, height, COLOR_WHITE, COLOR_BLACK, "", TEXT_CENTER);
	box(x, y, width, 1, COLOR_RED, COLOR_BRIGHT_WHITE, "SUA VAT TU", TEXT_CENTER);
	box(x, y + height, width, 1, COLOR_RED, COLOR_BRIGHT_WHITE, " ESC : QUAY LAI", TEXT_LEFT);

	for (int i = 0; i <= number; i++) {
		if (i == number) {
			box(xInput, y + 2 * (i + 1), 10, 3, COLOR_RED, COLOR_BRIGHT_WHITE, "OK", TEXT_CENTER);
		}
		else
		{
			gotoXY(x + 2, y + 2 * (i + 1));
			setBackgroundColor(COLOR_WHITE);
			setTextColor(COLOR_BLACK);
			cout << title[i];

			if (i == 0 && product.isUsed) {
				box(xInput, y + 2 * (i + 1), widthInputBox, 1, COLOR_RED, COLOR_LIGHT_YELLOW, data[i], TEXT_LEFT);
			}
			else {
				box(xInput, y + 2 * (i + 1), widthInputBox, 1, COLOR_BLACK, COLOR_LIGHT_YELLOW, data[i], TEXT_LEFT);
			}
		}
	}

	int xPointer = xInput;
	int i = product.isUsed ? 1 : 0;
	int yPointer = y + 2 + (i * 2);
	int xPointerOld = xPointer;
	int yPointerOld = yPointer;
	int backgroundColorChoose = 7;
	bool isClicked = true;
	char key = char();

	while (true)
	{
		if (isClicked)
		{
			ShowCur(1);
			if (i == number) {
				ShowCur(0);
				box(xPointer, y + 2 * (number + 1), 10, 3, COLOR_LIGHT_YELLOW, COLOR_BLACK, "OK", TEXT_CENTER);
			};
			isClicked = false;
		}
		if (i == number) key = _getch();
		switch (key)
		{
		case -32: //DIEU HUONG LEN XUONG
		{
			isClicked = true;
			key = _getch();
			//LEN
			if (key == UP && yPointer != y + 2)
			{
				if (i == number) box(xPointer, y + 2 * (number + 1), 10, 3, COLOR_RED, COLOR_BRIGHT_WHITE, "OK", TEXT_CENTER);

				if (product.isUsed && i == 1) {}
				else if (i > 0) {
					yPointer -= 2;
					i--;
				}
			}

			//XUONG
			else if (key == DOWN && yPointer != y + 2 * (number + 1))
			{
				yPointer += 2;
				if (i < number) i++;
			}

			key = char();
			break;
		}

		case ENTER: //NHAN ENTER (QUAN TRONG)
		{
			if (i == number) {
				box(xInput, y + height - 6, widthInputBox, 5, COLOR_RED, COLOR_LIGHT_YELLOW, "", TEXT_CENTER);

				string e1;
				if (productId != oldProductId) {
					e1 = checkProductId(productList, trim(productId));
				}
				string e2 = checkProductName(trim(productName));
				string e3 = checkUnit(trim(unit));

				int iy = y + height - 6;
				setTextColor(COLOR_BRIGHT_WHITE);
				if (!e1.empty()) { gotoXY(xPointer + 1, iy); cout << e1; iy += 1; }
				if (!e2.empty()) { gotoXY(xPointer + 1, iy); cout << e2; iy += 1; }
				if (!e3.empty()) { gotoXY(xPointer + 1, iy); cout << e3; iy += 1; }
				if (e1.empty() && e2.empty() && e3.empty())
				{
					//VAT TU DA CO MAT TRONG DANH SACH HOA DON
					if (productId == oldProductId) {
						product.productName = trim(productName);
						product.unit = trim(unit);
						sortProductListByName(sortedProductList);
					}
					else { //KHI VAT TU CHUA DUOC THEM VAO HOA DON
						Product product;
						newProduct(product, trim(productId), trim(productName), trim(unit), product.quantity);

						//XOA VAT TU KHOI DANH SACH DA SAP XEP
						deleteFromSortedProductList(sortedProductList, trim(productName));

						//XOA VAT TU KHOI CAY VAT TU
						deleteProduct(productList, oldProductId);

						//THEM VAT TU MOI TAO VAO CAY
						insertProduct(productList, product);

						//THEM VAT TU MOI TAO VAO DANH SACH SAP XEP
						NodeProduct* p = searchProduct(productList, trim(productId));
						insertSortedProductList(sortedProductList, p);
					}
					writeProductFile(productList);
					return YES;
				}
			}
			else continue;
			break;
		}

		case ESC: //NHAN ESC
		{
			setBackgroundColor(COLOR_BLACK);
			return NO;
			break;
		}

		default: //NHAP VAO CAC FIELD
		{
			if (i == 0) upperCaseWhileTyping(xPointer, yPointer, productId, key);
			else if (i == 1) upperCaseWhileTyping(xPointer, yPointer, productName, key);
			else if (i == 2) upperCaseWhileTyping(xPointer, yPointer, unit, key);
			break;
		}
		}
	}
}

//=================== BANG VAT TU ===================
void productTable(ProductList& productList, NodeIndexList& sortedProductList, bool isSearch) {
	ShowCur(0);
	titleBox(1, 3, "QUAN LY VAT TU");

	int width = 20;
	int height = 2;
	int x = getCenterX(WIDTH_MAIN_FRAME, width * 7);
	int y = getCenterY(HEIGHT_MAIN_FRAME, height * 13);
	int backgroundColor = COLOR_BRIGHT_WHITE;
	int textColor = COLOR_RED;

	setBackgroundColor(0);
	setTextColor(COLOR_WHITE);

	int currentIndex = 0;
	int row = 12;
	const int column = 5;
	string title[column] = { "STT", "MA VAT TU", "TEN VAT TU", "DON VI TINH", "SO LUONG" };
	int cellWidth[column] = { 20, 30, 40, 30, 20 };

	int iy = y + 2;
	for (int k = currentIndex; k < row; k++) {
		int ix = x;
		for (int j = 0; j < column; j++) {
			box3(ix, iy, cellWidth[j], height, backgroundColor, textColor, "");
			ix += cellWidth[j];
		}
		iy = iy + 2;
	}

	tableHeader(x, y, cellWidth, column, backgroundColor, textColor, title);
	tableFooter(x, iy + 1, cellWidth, column, backgroundColor, textColor, "");
	int keyBoxWidth = hotKeyBox(x + 1, iy + 2, "ESC", "QUAY LAI"); keyBoxWidth += 5;
	keyBoxWidth += hotKeyBox(x + keyBoxWidth, iy + 2, "INSERT", "THEM"); keyBoxWidth += 5;
	keyBoxWidth += hotKeyBox(x + keyBoxWidth, iy + 2, "ENTER", "HIEU CHINH"); keyBoxWidth += 5;
	keyBoxWidth += hotKeyBox(x + keyBoxWidth, iy + 2, "DELETE", "XOA"); keyBoxWidth += 5;
	keyBoxWidth += hotKeyBox(x + keyBoxWidth, iy + 2, "CTRL + F", "TIM KIEM"); keyBoxWidth += 5;

	int xPage = x + 120 + 1;
	int yPage = iy + 2;
	int xPointer = x + 1;
	int yPointer = y + 3;
	int xPointerOld = xPointer;
	int yPointerOld = yPointer;
	int i = 0;
	int iOld = i;
	bool isUpDown = true;
	bool isLeftRight = true;
	bool isFromUp = false;
	bool isInit = false;

	while (true) {
		if (isInit) {
			setTextColor(COLOR_BRIGHT_WHITE);
			setBackgroundColor(COLOR_BLACK);
			int iy = y + 3;
			for (int k = 0; k < row; k++) {
				int ix = xPointer;
				for (int j = 0; j < column; j++) {
					gotoXY(ix, iy);
					cout << generateSpace(cellWidth[j]);
					ix += cellWidth[j];
				}
				iy = iy + 2;
			}
			isInit = false;
		}

		if (!isSortedProductListEmpty(sortedProductList)) {
			if (isLeftRight) {
				setTextColor(COLOR_BRIGHT_WHITE);
				setBackgroundColor(COLOR_BLACK);
				int ix;
				iy = y + 3;
				for (int k = currentIndex; k < row + currentIndex; k++) {
					if (k >= sortedProductList.number) break;
					else {
						ix = xPointer;
						Product product = sortedProductList.nodes[k].nodeProduct->product;

						coutBox(ix, iy, cellWidth[0], TEXT_RIGHT, to_string(k + 1));
						ix += cellWidth[0];

						coutBox(ix, iy, cellWidth[1], TEXT_LEFT, product.productId);
						ix += cellWidth[1];

						coutBox(ix, iy, cellWidth[2], TEXT_LEFT, product.productName);
						ix += cellWidth[2];

						coutBox(ix, iy, cellWidth[3], TEXT_LEFT, product.unit);
						ix += cellWidth[3];

						coutBox(ix, iy, cellWidth[4], TEXT_RIGHT, to_string(product.quantity));
						ix += cellWidth[4];
					}
					iy = iy + 2;
				}

				setTextColor(COLOR_LIGHT_YELLOW);
				gotoXY(xPage, yPage);
				cout << generateSpace(10);
				gotoXY(xPage, yPage);
				cout << "TRANG " << currentIndex / row + 1 << "/" << (sortedProductList.number - 1) / row + 1;

				i = 0;
				iOld = i;
				yPointer = y + 3;
				yPointerOld = yPointer;
				if (isFromUp) {
					yPointer = y + 3 + 2 * (row - 1);
					yPointerOld = yPointer;
					i = row - 1;
					iOld = i;
					isFromUp = false;
				}
				isLeftRight = false;
			}

			if (isUpDown) {
				gotoXY(xPointerOld + cellWidth[0] + 1, yPointerOld);
				setBackgroundColor(COLOR_BLACK);
				setTextColor(COLOR_BRIGHT_WHITE);
				cout << sortedProductList.nodes[iOld + currentIndex].nodeProduct->product.productId;

				gotoXY(xPointer + cellWidth[0] + 1, yPointer);
				setBackgroundColor(COLOR_RED);
				setTextColor(COLOR_LIGHT_YELLOW);
				cout << sortedProductList.nodes[i + currentIndex].nodeProduct->product.productId;

				xPointerOld = xPointer;
				yPointerOld = yPointer;

				isUpDown = false;
			}
		}

		char key = _getch();
		switch (key)
		{
		case -32: // PHIM DIEU HUONG, PHIM DELETE, PHIM INSERT
		{
			key = _getch();
			if (key == LEFT && currentIndex != 0) {
				currentIndex -= row;
				isLeftRight = true;
				isUpDown = true;
				isInit = true;
			}
			else if (key == RIGHT && (currentIndex + row) < sortedProductList.number) {
				currentIndex += row;
				isLeftRight = true;
				isUpDown = true;
				isInit = true;
			}
			else if (key == UP)
			{
				if (i == 0 && currentIndex != 0) {
					isLeftRight = true;
					isInit = true;
					isFromUp = true;
					currentIndex -= row;

				}
				else if (i > 0)
				{
					yPointer -= 2;
					iOld = i;
					i--;
				}
				isUpDown = true;
			}
			else if (key == DOWN && (i + currentIndex) < sortedProductList.number - 1)
			{
				if (i == row - 1) {
					isLeftRight = true;
					currentIndex += row;
					isInit = true;
				}
				else if (i < row)
				{
					yPointer += 2;
					iOld = i;
					i++;
				}
				isUpDown = true;
			}

			//XOA VAT TU TRONG DANH SACH VAT TU
			else if (key == DELETE_KEY && !isSortedProductListEmpty(sortedProductList))
			{
				NodeProduct* p = sortedProductList.nodes[i + currentIndex].nodeProduct;

				string message = "BAN MUON XOA VAT TU NAY?";
				int isAccepted = warningPopUp(message);

				if (isAccepted == YES) { //CHO PHEP XOA

					//NEU VAT TU DA XUAT HIEN TRONG DANH SACH HOA DON HOAC CO SO LUONG TON > 0
					if ((p->product.isUsed) || (p->product.quantity > 0)) {
						string message = "KHONG THE XOA VAT TU NAY.";
						int k = notificationPopUp(message);
						if (k == 0) {} //NHAN OK
					}
					else { //TRUONG HOP CON LAI THI XOA DUOC VAT TU
						deleteProduct(productList, p->product.productId);

						delete[] sortedProductList.nodes;
						productListToProductIndexList(productList, sortedProductList);
						sortProductListByName(sortedProductList);

						writeProductFile(productList);
					}

					clearConsole();
					productTable(productList, sortedProductList, false);
				}
				else {
					clearConsole();
					productTable(productList, sortedProductList, isSearch);
				}
			}

			//THEM VAT TU DANH SACH VAT VAT TU
			else if (key == INSERT_KEY) {

				//Khi danh sach vat tu theo ten day 
				// ==> tien hanh cap phat lai
				if (sortedProductList.init == sortedProductList.number)
				{
					delete[] sortedProductList.nodes;
					productListToProductIndexList(productList, sortedProductList);
					sortProductListByName(sortedProductList);
				}

				int k = addProductPopUp(productList, sortedProductList);
				if (k == YES) {  //DA CHINH SUA VAT TU
					clearConsole();
					productTable(productList, sortedProductList, false);
				}
				else {
					clearConsole();
					productTable(productList, sortedProductList, isSearch);
				}
			}
			break;
		}

		case ENTER: //HIEU CHINH VAT TU TRONG DANH SACH VAT TU
		{
			if (!isSortedProductListEmpty(sortedProductList))
			{
				NodeProduct* p = sortedProductList.nodes[i + currentIndex].nodeProduct;

				int k = editProductPopUp(productList, p->product, sortedProductList);

				if (k == NO) { //NEU AN ESC
					clearConsole();
					productTable(productList, sortedProductList, isSearch);
				}
				else {
					clearConsole();
					productTable(productList, sortedProductList, false);
				}
			}
			break;
		}

		case CTRL_F: //TIM KIEM TRONG DANH SACH VAT TU
		{
			setTextColor(COLOR_BRIGHT_WHITE);
			setBackgroundColor(COLOR_BLACK);
			string text = "NHAP TEN VAT TU: ";
			gotoXY(x + 1, 5);
			cout << text << generateSpace(30);

			string productName = "";
			gotoXY(x + text.length() + 1, 5);
			char c = char();
			upperCaseWhileTypingEnter(x + text.length() + 1, 5, productName, c);

			if (c == ENTER) //NHAN ENTER DE TIM KIEM
			{
				delete[] sortedProductList.nodes;
				sortedProductList.number = 0;
				searchProductListByName(productList, sortedProductList, trim(productName));

				ShowCur(0);
				isInit = true;
				isLeftRight = true;
				isUpDown = true;
				isSearch = true;

			}
			else if (c == ESC) {
				ShowCur(0);
				setBackgroundColor(COLOR_BLACK);
				gotoXY(x + 1, 5);
				cout << generateSpace(50);
			}

			break;
		}

		case ESC: //QUAY LAI
		{
			if (isSearch) {
				setBackgroundColor(COLOR_BLACK);
				gotoXY(x + 1, 5);
				cout << generateSpace(50);

				delete[] sortedProductList.nodes;
				sortedProductList.number = 0;
				sortedProductList.init = 0;
				productListToProductIndexList(productList, sortedProductList);
				sortProductListByName(sortedProductList);

				ShowCur(0);
				isInit = true;
				isLeftRight = true;
				isUpDown = true;
				isSearch = false;
			}
			else {
				delete[] sortedProductList.nodes;
				sortedProductList.number = 0;
				sortedProductList.init = 0;
				clearConsole();
				menu(false);
			}
			break;
		}

		default:
			break;
		}

	}
}



//=================== THEM NHAN VIEN ===================
int addEmployeePopUp(EmployeeList& employeeList) {
	ShowCur(1);
	int height = HEIGHT_POP_UP;
	int width = WIDTH_POP_UP;
	int x = getCenterX(WIDTH_MAIN_FRAME, width);
	int y = getCenterY(HEIGHT_MAIN_FRAME, height);
	int xInput = x + 18;
	int widthInput = 40;

	string employeeId = generateEmployeeId(employeeList);
	string lastname;
	string firstname;
	string gender;

	//ve bang pop up
	box(x, y, width, height, COLOR_WHITE, COLOR_BLACK, "", TEXT_CENTER);
	box(x, y, width, 1, COLOR_RED, COLOR_BRIGHT_WHITE, "THEM NHAN VIEN", TEXT_CENTER);
	box(x, y + height, width, 1, COLOR_RED, COLOR_BRIGHT_WHITE, "", TEXT_CENTER);
	gotoXY(x + 1, y + height);
	cout << "ESC : QUAY LAI";

	const int number = 4;
	string title[number] = { "MA NHAN VIEN", "HO", "TEN", "PHAI" };
	for (int i = 0; i <= number; i++) {
		if (i == number) {
			box(xInput, y + 2 * (i + 1), 10, 3, COLOR_RED, COLOR_WHITE, "OK", TEXT_CENTER);
		}
		else {
			gotoXY(x + 2, y + 2 * (i + 1));
			setBackgroundColor(COLOR_WHITE);
			setTextColor(COLOR_BLACK);
			cout << title[i];
			box(xInput, y + 2 * (i + 1), widthInput, 1, COLOR_BLACK, COLOR_LIGHT_YELLOW, "", TEXT_CENTER);
		}
	}

	int xPointer = xInput;
	int yPointer = y + 2;
	int xPointerOld = xPointer;
	int yPointerOld = yPointer;
	int backgroundColorChoose = 7;
	int i = 0;
	bool isClicked = true;
	char key = char();

	while (true)
	{
		if (isClicked)
		{
			ShowCur(1);
			if (i == number) {
				ShowCur(0);
				box(xPointer, y + 2 * 5, 10, 3, COLOR_LIGHT_YELLOW, COLOR_BLACK, "OK", TEXT_CENTER);
			};
			if (i == 0) upperCaseWhileTyping(xPointer, yPointer, employeeId, key);
			isClicked = false;
		}
		if (i == 4) key = _getch();
		switch (key)
		{
		case -32: //DIEU HUONG LEN/XUONG
		{
			isClicked = true;
			key = _getch();
			if (key == UP && yPointer != y + 2)
			{
				yPointer -= 2;
				if (i == number) box(xPointer, y + 2 * 5, 10, 3, COLOR_RED, COLOR_WHITE, "OK", TEXT_CENTER);
				if (i > 0) i--;
			}
			else if (key == DOWN && yPointer != y + 2 * (number + 1))
			{
				yPointer += 2;
				if (i < (number + 1)) i++;
			}
			key = char();
			break;
		}


		case ENTER: //NHAN OK DE THEM NHAN VIEN VAO DANH SACH NHAN VIEN
		{
			if (i == 4) {
				box(xPointer, y + height - 6, widthInput, 5, COLOR_RED, COLOR_LIGHT_YELLOW, "", TEXT_CENTER);

				//KIEM TRA THONG TIN NHAP VAO
				string e1 = checkEmployeeId(employeeList, trim(employeeId));
				string e2 = checkLastName(trim(lastname));
				string e3 = checkFirstname(trim(firstname));
				string e4 = checkGender(trim(gender));

				int iy = y + height - 6;
				setTextColor(COLOR_BRIGHT_WHITE);
				if (!e1.empty()) { gotoXY(xPointer + 1, iy); cout << e1; iy += 1; }
				if (!e2.empty()) { gotoXY(xPointer + 1, iy); cout << e2; iy += 1; }
				if (!e3.empty()) { gotoXY(xPointer + 1, iy); cout << e3; iy += 1; }
				if (!e4.empty()) { gotoXY(xPointer + 1, iy); cout << e4; iy += 1; }
				if (e1.empty() && e2.empty() && e3.empty() && e4.empty()) {

					//THEM NHAN VIEN MOI VAO DANH SACH NHAN VIEN
					Employee employee;
					newEmployee(employee, trim(employeeId), trim(firstname), trim(lastname), trim(gender));
					insertEmployeeListOrder(employeeList, employee);

					//GHI LAI FILE
					writeEmployeeFile(employeeList);
					return YES;
				}
			}
			else {
				continue;
			}
			break;
		}

		case ESC: //THOAT POP UP
		{
			setBackgroundColor(COLOR_BLACK);
			return NO;
			break;
		}

		default: //NHAP CAC FIELD TRONG POP UP
		{
			if (i == 0) upperCaseWhileTyping(xPointer, yPointer, employeeId, key);
			else if (i == 1) upperCaseWhileTyping(xPointer, yPointer, lastname, key);
			else if (i == 2) upperCaseWhileTyping(xPointer, yPointer, firstname, key);
			else if (i == 3) upperCaseWhileTyping(xPointer, yPointer, gender, key);
			break;
		}
		}
	}
}

//=================== SUA NHAN VIEN =================== 
// MAU DE LAM POP UP
int editEmployeePopUp(EmployeeList& employeeList, int employeeIndex, IndexList& sortedEmployeeList) {
	ShowCur(1);
	int height = HEIGHT_POP_UP;
	int width = WIDTH_POP_UP;
	int x = getCenterX(WIDTH_MAIN_FRAME, width);
	int y = getCenterY(HEIGHT_MAIN_FRAME, height);
	int xInput = x + 18;
	int widthInput = 40;
	const int number = 4;

	string oldEmployeeId = employeeList.employee[employeeIndex]->employeeId;
	string employeeId = employeeList.employee[employeeIndex]->employeeId;
	string lastname = employeeList.employee[employeeIndex]->lastname;
	string firstname = employeeList.employee[employeeIndex]->firstname;
	string gender = employeeList.employee[employeeIndex]->gender;

	string title[number] = { "MANV", "HO", "TEN", "PHAI" };
	string data[number] = { oldEmployeeId, lastname, firstname, gender };

	//ve bang pop up
	box(x, y, width, height, COLOR_WHITE, COLOR_BLACK, "", TEXT_CENTER);
	box(x, y, width, 1, COLOR_RED, COLOR_BRIGHT_WHITE, "SUA NHAN VIEN", TEXT_CENTER);
	box(x, y + height, width, 1, COLOR_RED, COLOR_BRIGHT_WHITE, " ESC : QUAY LAI", TEXT_LEFT);

	for (int i = 0; i <= number; i++) {
		if (i == number) {
			box(xInput, y + 2 * (i + 1), 10, 3, COLOR_RED, COLOR_BRIGHT_WHITE, "OK", TEXT_CENTER);
		}
		else {
			gotoXY(x + 2, y + 2 * (i + 1));
			setBackgroundColor(COLOR_WHITE);
			setTextColor(COLOR_BLACK);
			cout << title[i];

			box(xInput, y + 2 * (i + 1), widthInput, 1, COLOR_BLACK, COLOR_LIGHT_YELLOW, data[i], TEXT_LEFT);
		}
	}

	int xPointer = xInput;
	int yPointer = y + 2;
	int xPointerOld = xPointer;
	int yPointerOld = yPointer;
	int backgroundColorChoose = 7;
	int i = 0;
	bool isClicked = true;
	char c = char();

	while (true)
	{
		if (isClicked)
		{
			ShowCur(1);
			if (i == number) {
				ShowCur(0);
				box(xPointer, y + 2 * (number + 1), 10, 3, COLOR_LIGHT_YELLOW, COLOR_BLACK, "OK", TEXT_CENTER);
			};
			if (i == 0) upperCaseWhileTyping(xPointer, yPointer, employeeId, c);
			isClicked = false;
		}
		if (i == number) c = _getch();

		switch (c)
		{
		case -32:
			isClicked = true;
			c = _getch();
			if (c == UP && yPointer != y + 2)
			{
				yPointer -= 2;
				if (i == number) box(xPointer, y + 2 * (number + 1), 10, 3, COLOR_RED, COLOR_BRIGHT_WHITE, "OK", TEXT_CENTER);
				if (i > 0) i--;
			}
			else if (c == DOWN && yPointer != y + 2 * (number + 1))
			{
				yPointer += 2;
				if (i < 5) i++;
			}
			c = char();
			break;

		case ESC:
		{
			setBackgroundColor(COLOR_BLACK);
			return NO;
			break;
		}

		case ENTER:
		{
			if (i == number) {
				box(xPointer, y + height - 6, widthInput, 5, COLOR_RED, COLOR_LIGHT_YELLOW, "", TEXT_CENTER);

				string e1;
				if (employeeId != oldEmployeeId) {
					e1 = checkEmployeeId(employeeList, trim(employeeId));
				}
				string e2 = checkLastName(trim(lastname));
				string e3 = checkFirstname(trim(firstname));
				string e4 = checkGender(trim(gender));

				int iy = y + height - 6;
				setTextColor(COLOR_BRIGHT_WHITE);
				if (!e1.empty()) { gotoXY(xPointer + 1, iy); cout << e1; iy += 1; }
				if (!e2.empty()) { gotoXY(xPointer + 1, iy); cout << e2; iy += 1; }
				if (!e3.empty()) { gotoXY(xPointer + 1, iy); cout << e3; iy += 1; }
				if (!e4.empty()) { gotoXY(xPointer + 1, iy); cout << e4; iy += 1; }
				if (e1.empty() && e2.empty() && e3.empty() && e4.empty()) {
					if (employeeId == oldEmployeeId) { //KHONG THAY DOI MA NHAN VIEN
						employeeList.employee[employeeIndex]->firstname = trim(firstname);
						employeeList.employee[employeeIndex]->lastname = trim(lastname);
						employeeList.employee[employeeIndex]->gender = trim(gender);

						for (int l = 0; l < sortedEmployeeList.number; l++) {
							if (sortedEmployeeList.nodes[l].index == employeeIndex) {
								sortedEmployeeList.nodes[l].firstname = trim(firstname);
								sortedEmployeeList.nodes[l].lastname = trim(lastname);
								break;
							}
						}
						sortEmployeeListByName(sortedEmployeeList);
					}
					else { //THAY DOI MA NHAN VIEN
						employeeList.employee[employeeIndex]->employeeId = trim(employeeId);
						employeeList.employee[employeeIndex]->firstname = trim(firstname);
						employeeList.employee[employeeIndex]->lastname = trim(lastname);
						employeeList.employee[employeeIndex]->gender = trim(gender);

						sortEmployeeListByEmployeeId(employeeList);

						delete[] sortedEmployeeList.nodes;
						employeeListToEmployeeIndexList(employeeList, sortedEmployeeList);
						sortEmployeeListByName(sortedEmployeeList);
					}

					writeEmployeeFile(employeeList);
					return YES;
				}
			}
			break;
		}

		default:
		{
			if (i == 0) upperCaseWhileTyping(xPointer, yPointer, employeeId, c);
			else if (i == 1) upperCaseWhileTyping(xPointer, yPointer, lastname, c);
			else if (i == 2) upperCaseWhileTyping(xPointer, yPointer, firstname, c);
			else if (i == 3) upperCaseWhileTyping(xPointer, yPointer, gender, c);
			break;
		}
		}
	}
}

//=================== BANG NHAN VIEN ===================
void employeeTable(EmployeeList& employeeList, IndexList& sortedEmployeeList, bool isSearch) {
	ShowCur(0);
	titleBox(1, 3, "QUAN LY NHAN VIEN");
	int width = 20;
	int height = 2;
	int x = getCenterX(WIDTH_MAIN_FRAME, width * 7);
	int y = getCenterY(HEIGHT_MAIN_FRAME, height * 13);
	int backgroundColor = COLOR_WHITE; // chinh mau vien table
	int textColor = COLOR_RED;
	setBackgroundColor(0);
	setTextColor(COLOR_WHITE);

	int currentIndex = 0;
	int row = 12;
	const int column = 5;
	string title[column] = { "STT", "MA NHAN VIEN", "HO", "TEN", "PHAI" };
	int cellWidth[column] = { 20, 30, 40, 30, 20 };

	int iy = y + 2;

	for (int k = currentIndex; k < row; k++) {
		int ix = x;
		for (int j = 0; j < column; j++) {
			box3(ix, iy, cellWidth[j], height, backgroundColor, textColor, "");
			ix += cellWidth[j];
		}
		iy = iy + 2;
	}
	tableHeader(x, y, cellWidth, column, backgroundColor, textColor, title);
	tableFooter(x, iy + 1, cellWidth, column, backgroundColor, textColor, "");


	int keyBoxWidth = hotKeyBox(x + 1, iy + 2, "ESC", "QUAY LAI"); keyBoxWidth += 5;
	keyBoxWidth += hotKeyBox(x + keyBoxWidth, iy + 2, "INSERT", "THEM"); keyBoxWidth += 5;
	keyBoxWidth += hotKeyBox(x + keyBoxWidth, iy + 2, "ENTER", "HIEU CHINH"); keyBoxWidth += 5;
	keyBoxWidth += hotKeyBox(x + keyBoxWidth, iy + 2, "DELETE", "XOA"); keyBoxWidth += 5;
	keyBoxWidth += hotKeyBox(x + keyBoxWidth, iy + 2, "CTRL + F", "TIM KIEM"); keyBoxWidth += 5;
	int xPage = x + 120 + 1;
	int yPage = iy + 2;

	int xPointer = x + 1;
	int yPointer = y + 3;
	int xPointerOld = xPointer;
	int yPointerOld = yPointer;
	int i = 0;
	int iOld = i;
	bool isUpDown = true;
	bool isLeftRight = true;
	bool isInit = false;
	bool isFromUp = false;

	while (true) {
		if (isInit) {
			setTextColor(COLOR_BRIGHT_WHITE);
			setBackgroundColor(COLOR_BLACK);
			int iy = y + 3;
			for (int k = 0; k < row; k++) {
				int ix = xPointer;
				for (int j = 0; j < column; j++) {
					gotoXY(ix, iy);
					cout << generateSpace(cellWidth[j]);
					ix += cellWidth[j];
				}
				iy = iy + 2;
			}
			isInit = false;
		}

		if (!isSortedEmployeeListEmpty(sortedEmployeeList)) {
			if (isLeftRight) {
				setTextColor(COLOR_BRIGHT_WHITE);
				setBackgroundColor(COLOR_BLACK);

				int ix;
				int index;
				iy = y + 3;
				for (int k = currentIndex; k < row + currentIndex; k++) {
					if (k >= sortedEmployeeList.number) break;
					else {
						index = sortedEmployeeList.nodes[k].index;
						ix = x + 1;

						coutBox(ix, iy, cellWidth[0], TEXT_RIGHT, to_string(k + 1));
						ix += cellWidth[0];

						coutBox(ix, iy, cellWidth[1], TEXT_LEFT, employeeList.employee[index]->employeeId);
						ix += cellWidth[1];

						coutBox(ix, iy, cellWidth[2], TEXT_LEFT, sortedEmployeeList.nodes[k].lastname);
						ix += cellWidth[2];

						coutBox(ix, iy, cellWidth[3], TEXT_LEFT, sortedEmployeeList.nodes[k].firstname);
						ix += cellWidth[3];

						coutBox(ix, iy, cellWidth[4], TEXT_LEFT, employeeList.employee[index]->gender);
						ix += cellWidth[4];
					}
					iy = iy + 2;
				}

				setTextColor(COLOR_LIGHT_YELLOW);
				gotoXY(xPage, yPage);
				cout << generateSpace(10);
				gotoXY(xPage, yPage);
				cout << "TRANG " << currentIndex / row + 1 << "/" << sortedEmployeeList.number / row + 1;

				i = 0;
				iOld = i;
				yPointer = y + 3;
				yPointerOld = yPointer;
				if (isFromUp) {
					yPointer = y + 3 + 2 * (row - 1);
					yPointerOld = yPointer;
					i = row - 1;
					iOld = i;
					isFromUp = false;
				}
				isLeftRight = false;
			}

			if (isUpDown) {
				gotoXY(xPointerOld + cellWidth[0] + 1, yPointerOld);
				setBackgroundColor(COLOR_BLACK);
				setTextColor(COLOR_BRIGHT_WHITE);
				int index = sortedEmployeeList.nodes[iOld + currentIndex].index;
				cout << employeeList.employee[index]->employeeId;

				gotoXY(xPointer + cellWidth[0] + 1, yPointer);
				setBackgroundColor(COLOR_RED);
				setTextColor(COLOR_LIGHT_YELLOW);
				index = sortedEmployeeList.nodes[i + currentIndex].index;
				cout << employeeList.employee[index]->employeeId;

				xPointerOld = xPointer;
				yPointerOld = yPointer;

				isUpDown = false;

			}
		}

		char key = _getch();
		switch (key)
		{
		case -32: //DIEU HUONG, THEM, SUA NHAN VIEN
		{
			key = _getch();
			if (key == LEFT && currentIndex != 0)
			{
				currentIndex -= row;
				isInit = true;
				isLeftRight = true;
				isUpDown = true;
			}
			else if (key == RIGHT && (currentIndex + row) < sortedEmployeeList.number) {
				currentIndex += row;
				isInit = true;
				isLeftRight = true;
				isUpDown = true;
			}
			else if (key == UP)
			{
				if (i == 0 && currentIndex != 0)
				{
					isLeftRight = true;
					isFromUp = true;
					isInit = true;
					currentIndex -= row;

				}
				else if (i > 0)
				{
					yPointer -= 2;
					iOld = i;
					i--;
				}
				isUpDown = true;
			}
			else if (key == DOWN && (i + currentIndex) < sortedEmployeeList.number - 1)
			{
				if (i == row - 1) {
					isInit = true;
					isLeftRight = true;
					currentIndex += row;
				}
				else if (i < row)
				{
					yPointer += 2;
					iOld = i;
					i++;
				}
				isUpDown = true;
			}

			//THEM NHAN VIEN
			else if (key == INSERT_KEY)
			{
				if (isEmployeeListFull(employeeList)) { //DANH SACH NHAN VIEN DA DAY
					string message = "DANH SACH NHAN VIEN DA DAY";
					int k = notificationPopUp(message);
					if (k == YES) {}
				}
				else { //DANH SACH NHAN VIEN CHUA DAY
					int k = addEmployeePopUp(employeeList);
					if (k == YES) {
						delete[] sortedEmployeeList.nodes;
						employeeListToEmployeeIndexList(employeeList, sortedEmployeeList);
						sortEmployeeListByName(sortedEmployeeList);

						clearConsole();
						employeeTable(employeeList, sortedEmployeeList, false);
					}
				}

				clearConsole();
				employeeTable(employeeList, sortedEmployeeList, isSearch);
			}

			//XOA NHAN VIEN
			else if (key == DELETE_KEY && !isSortedEmployeeListEmpty(sortedEmployeeList))
			{
				string message = "BAN MUON XOA NHAN VIEN NAY?";
				bool isAccepted = warningPopUp(message);
				int index = sortedEmployeeList.nodes[i + currentIndex].index;
				if (isAccepted)
				{
					if (isEmployeeHasInvoiceList(*employeeList.employee[index])) {
						string message = "NHAN VIEN NAY DA LAP HOA DON, KHONG XOA DUOC.";
						int t = notificationPopUp(message);
						if (t == YES) {};
					}
					else {
						deleteEmployee(employeeList, employeeList.employee[index]->employeeId);
						writeEmployeeFile(employeeList);

						delete[] sortedEmployeeList.nodes;
						employeeListToEmployeeIndexList(employeeList, sortedEmployeeList);
						sortEmployeeListByName(sortedEmployeeList);

						clearConsole();
						employeeTable(employeeList, sortedEmployeeList, false);
					}
				}
				writeEmployeeFile(employeeList);
				clearConsole();
				employeeTable(employeeList, sortedEmployeeList, isSearch);
			}

			break;
		}

		case ESC: //QUAY LAI
		{
			if (isSearch) {
				ShowCur(0);
				setBackgroundColor(COLOR_BLACK);
				gotoXY(x + 1, 5);
				cout << generateSpace(50);

				delete[] sortedEmployeeList.nodes;
				employeeListToEmployeeIndexList(employeeList, sortedEmployeeList);
				sortEmployeeListByName(sortedEmployeeList);

				ShowCur(0);
				isSearch = false;
				isInit = true;
				isLeftRight = true;
				isUpDown = true;
			}
			else {
				delete[] sortedEmployeeList.nodes;
				clearConsole();
				menu(false);
			}
			break;
		}

		case ENTER: // SUA NHAN VIEN TRONG DANH SACH NHAN VIEN
		{
			if (!isSortedEmployeeListEmpty(sortedEmployeeList))
			{
				int index = sortedEmployeeList.nodes[i + currentIndex].index;
				int k = editEmployeePopUp(employeeList, index, sortedEmployeeList);
				if (k == YES) { // DA HIEU CHINH NHAN VIEN
					clearConsole();
					employeeTable(employeeList, sortedEmployeeList, false);
				}
				else {//NHAN ESC
					clearConsole();
					employeeTable(employeeList, sortedEmployeeList, isSearch);
				}
			}
			break;
		}

		case CTRL_F: // TIM KIEM NHAN VIEN
		{
			setTextColor(COLOR_BRIGHT_WHITE);
			setBackgroundColor(COLOR_BLACK);
			string text = "NHAP TEN: ";
			gotoXY(x + 1, 5);
			cout << text << generateSpace(30);

			string name = "";
			gotoXY(x + text.length() + 1, 5);
			char c = char();
			upperCaseWhileTypingEnter(x + text.length() + 1, 5, name, c);

			if (c == ENTER) {
				delete[] sortedEmployeeList.nodes;
				searchEmployeeListByName(employeeList, sortedEmployeeList, trim(name));

				ShowCur(0);
				isInit = true;
				isLeftRight = true;
				isUpDown = true;
				isSearch = true;

			}
			else if (c == ESC) {
				ShowCur(0);
				setBackgroundColor(COLOR_BLACK);
				gotoXY(x + 1, 5);
				cout << generateSpace(50);
			}
			break;
		}

		default:
			break;
		}

	}

}



//=================== XUAT DANH SACH NHAN VIEN THEO TEN ===================
int employeeTableByName(EmployeeList& employeeList, IndexList& sortedEmployeeList, bool isSearch) {
	ShowCur(0);
	titleBox(1, 3, "CHON NHAN VIEN LAP HOA DON");
	int width = 20;
	int height = 2;
	int x = getCenterX(WIDTH_MAIN_FRAME, width * 6);
	int y = getCenterY(HEIGHT_MAIN_FRAME, height * 13);
	int backgroundColor = COLOR_WHITE; // chinh mau vien table
	int textColor = COLOR_RED;
	setBackgroundColor(0);
	setTextColor(COLOR_WHITE);

	int currentIndex = 0;
	int row = 12;
	const int column = 4;
	string title[column] = { "STT", "MA NHAN VIEN", "HO", "TEN" };
	int cellWidth[column] = { 20, 30, 40, 30 };

	int iy = y + 2;

	for (int k = currentIndex; k < row; k++) {
		int ix = x;
		for (int j = 0; j < column; j++) {
			box3(ix, iy, cellWidth[j], height, backgroundColor, textColor, "");
			ix += cellWidth[j];
		}
		iy = iy + 2;
	}
	tableHeader(x, y, cellWidth, column, backgroundColor, textColor, title);
	tableFooter(x, iy + 1, cellWidth, column, backgroundColor, textColor, "");


	int keyBoxWidth = hotKeyBox(x + 1, iy + 2, "ESC", "QUAY LAI"); keyBoxWidth += 5;
	keyBoxWidth += hotKeyBox(x + keyBoxWidth, iy + 2, "CTRL + F", "TIM KIEM"); keyBoxWidth += 5;
	int xPage = x + 105 + 1;
	int yPage = iy + 2;

	int xPointer = x + 1;
	int yPointer = y + 3;
	int xPointerOld = xPointer;
	int yPointerOld = yPointer;
	int i = 0;
	int iOld = i;
	bool isUpDown = true;
	bool isLeftRight = true;
	bool isInit = false;
	bool isFromUp = false;

	while (true) {
		if (isInit) {
			setTextColor(COLOR_BRIGHT_WHITE);
			setBackgroundColor(COLOR_BLACK);
			int iy = y + 3;
			for (int k = 0; k < row; k++) {
				int ix = xPointer;
				for (int j = 0; j < column; j++) {
					gotoXY(ix, iy);
					cout << generateSpace(cellWidth[j]);
					ix += cellWidth[j];
				}
				iy = iy + 2;
			}
			isInit = false;
		}

		if (!isSortedEmployeeListEmpty(sortedEmployeeList)) {
			if (isLeftRight) {
				setTextColor(COLOR_BRIGHT_WHITE);
				setBackgroundColor(COLOR_BLACK);

				int ix;
				int index;
				iy = y + 3;
				for (int k = currentIndex; k < row + currentIndex; k++) {
					if (k >= sortedEmployeeList.number) break;
					else {
						index = sortedEmployeeList.nodes[k].index;
						ix = x + 1;

						coutBox(ix, iy, cellWidth[0], TEXT_RIGHT, to_string(k + 1));
						ix += cellWidth[0];

						gotoXY(ix, iy); cout << employeeList.employee[index]->employeeId; ix += cellWidth[1];
						gotoXY(ix, iy); cout << sortedEmployeeList.nodes[k].lastname; ix += cellWidth[2];
						gotoXY(ix, iy); cout << sortedEmployeeList.nodes[k].firstname; ix += cellWidth[3];
					}
					iy = iy + 2;
				}

				setTextColor(COLOR_LIGHT_YELLOW);
				gotoXY(xPage, yPage);
				cout << generateSpace(10);
				gotoXY(xPage, yPage);
				cout << "TRANG " << currentIndex / row + 1 << "/" << sortedEmployeeList.number / row + 1;

				i = 0;
				iOld = i;
				yPointer = y + 3;
				yPointerOld = yPointer;
				if (isFromUp) {
					yPointer = y + 3 + 2 * (row - 1);
					yPointerOld = yPointer;
					i = row - 1;
					iOld = i;
					isFromUp = false;
				}
				isLeftRight = false;
			}

			if (isUpDown) {
				gotoXY(xPointerOld + cellWidth[0], yPointerOld);
				setBackgroundColor(COLOR_BLACK);
				setTextColor(COLOR_BRIGHT_WHITE);
				int index = sortedEmployeeList.nodes[iOld + currentIndex].index;
				cout << employeeList.employee[index]->employeeId;

				gotoXY(xPointer + cellWidth[0], yPointer);
				setBackgroundColor(COLOR_RED);
				setTextColor(COLOR_LIGHT_YELLOW);
				index = sortedEmployeeList.nodes[i + currentIndex].index;
				cout << employeeList.employee[index]->employeeId;

				xPointerOld = xPointer;
				yPointerOld = yPointer;

				isUpDown = false;

			}
		}

		char key = _getch();
		switch (key)
		{
		case -32: //DIEU HUONG
		{
			key = _getch();
			if (key == LEFT && currentIndex != 0)
			{
				currentIndex -= row;
				isInit = true;
				isLeftRight = true;
				isUpDown = true;
			}
			else if (key == RIGHT && (currentIndex + row) < sortedEmployeeList.number) {
				currentIndex += row;
				isInit = true;
				isLeftRight = true;
				isUpDown = true;
			}
			else if (key == UP)
			{
				if (i == 0 && currentIndex != 0)
				{
					isLeftRight = true;
					isFromUp = true;
					isInit = true;
					currentIndex -= row;

				}
				else if (i > 0)
				{
					yPointer -= 2;
					iOld = i;
					i--;
				}
				isUpDown = true;
			}
			else if (key == DOWN && (i + currentIndex) < sortedEmployeeList.number - 1)
			{
				if (i == row - 1) {
					isInit = true;
					isLeftRight = true;
					currentIndex += row;
				}
				else if (i < row)
				{
					yPointer += 2;
					iOld = i;
					i++;
				}
				isUpDown = true;
			}
			break;
		}
		case ESC: //QUAY LAI
		{
			if (isSearch) {
				ShowCur(0);
				setBackgroundColor(COLOR_BLACK);
				gotoXY(x + 1, 5);
				cout << generateSpace(50);

				delete[] sortedEmployeeList.nodes;
				employeeListToEmployeeIndexList(employeeList, sortedEmployeeList);
				sortEmployeeListByName(sortedEmployeeList);

				ShowCur(0);
				isSearch = false;
				isInit = true;
				isLeftRight = true;
				isUpDown = true;
			}
			else {
				delete[] sortedEmployeeList.nodes;
				return -1;
			}
			break;
		}

		case ENTER: {
			if (!isSortedEmployeeListEmpty(sortedEmployeeList)) {
				int index = sortedEmployeeList.nodes[i + currentIndex].index;
				delete[] sortedEmployeeList.nodes;
				return index;
			}
		}

		case CTRL_F: // TIM KIEM NHAN VIEN
		{
			setTextColor(COLOR_BRIGHT_WHITE);
			setBackgroundColor(COLOR_BLACK);
			string text = "NHAP TEN: ";
			gotoXY(x + 1, 5);
			cout << text << generateSpace(30);

			string name = "";
			gotoXY(x + text.length() + 1, 5);
			char c = char();
			upperCaseWhileTypingEnter(x + text.length() + 1, 5, name, c);

			if (c == ENTER) {
				delete[] sortedEmployeeList.nodes;
				searchEmployeeListByName(employeeList, sortedEmployeeList, name);

				ShowCur(0);
				isInit = true;
				isLeftRight = true;
				isUpDown = true;
				isSearch = true;

			}
			else if (c == ESC) {
				ShowCur(0);
				setBackgroundColor(COLOR_BLACK);
				gotoXY(x + 1, 5);
				cout << generateSpace(50);
			}
			break;
		}

		default:
			break;
		}

	}

}

//=================== XUAT DANH SACH VAT TU THEO TEN ===================
void productTableByName(ProductList& root, NodeIndexList& nodeIndexList) {
	ShowCur(0);
	titleBox(1, 3, "DANH SACH VAT TU THEO TEN");
	int width = 20;
	int height = 2;
	int x = getCenterX(WIDTH_MAIN_FRAME, width * 6);
	int y = getCenterY(HEIGHT_MAIN_FRAME, height * 14);
	int backgroundColor = COLOR_BRIGHT_WHITE;
	int textColor = COLOR_RED;
	setBackgroundColor(0);
	setTextColor(COLOR_WHITE);

	int currentIndex = 0;
	int row = 12;
	const int column = 5;
	string title[column] = { "STT", "MA VAT TU", "TEN VAT TU", "DON VI TINH", "SO LUONG" };
	int cellWidth[column] = { 10, 30, 40, 20, 20 };

	int iy = y + 2;
	for (int k = currentIndex; k < row; k++) {
		int ix = x;
		for (int j = 0; j < column; j++) {
			box3(ix, iy, cellWidth[j], height, backgroundColor, textColor, "");
			ix += cellWidth[j];
		}
		iy = iy + 2;
	}
	tableHeader(x, y, cellWidth, column, backgroundColor, textColor, title);
	tableFooter(x, iy + 1, cellWidth, column, backgroundColor, textColor, "");
	int keyBoxWidth = hotKeyBox(x + 1, iy + 2, "ESC", "QUAY LAI"); keyBoxWidth += 5;
	keyBoxWidth += hotKeyBox(x + keyBoxWidth, iy + 2, "LEFT/RIGHT", "SANG TRANG"); keyBoxWidth += 5;

	bool isRightLeft = true;
	bool isInit = true;

	while (true) {
		if (isRightLeft) {
			if (!isInit) {
				int iy = y + 3;
				for (int k = currentIndex; k < row + currentIndex; k++) {
					int ix = x + 1;
					for (int j = 0; j < column; j++) {
						gotoXY(ix, iy);
						cout << generateSpace(cellWidth[j]);
						ix += cellWidth[j];
					}
					iy = iy + 2;
				}
			}

			int ix;
			int iy = y + 3;
			setTextColor(COLOR_BRIGHT_WHITE);
			for (int k = currentIndex; k < row + currentIndex; k++) {
				if (k >= nodeIndexList.number) {
					ix = x + 1;
					for (int j = 0; j < column; j++) {
						gotoXY(ix, iy);
						cout << "";
						ix += cellWidth[j];
					}
				}
				else {
					ix = x + 1;
					gotoXY(ix, iy); cout << intToString(k + 1); ix += cellWidth[0];
					gotoXY(ix, iy); cout << nodeIndexList.nodes[k].nodeProduct->product.productId; ix += cellWidth[1];
					gotoXY(ix, iy); cout << nodeIndexList.nodes[k].nodeProduct->product.productName; ix += cellWidth[2];
					gotoXY(ix, iy); cout << nodeIndexList.nodes[k].nodeProduct->product.unit; ix += cellWidth[3];
					gotoXY(ix, iy); cout << nodeIndexList.nodes[k].nodeProduct->product.quantity; ix += cellWidth[4];
				}
				iy = iy + 2;
			}

			isInit = false;
			isRightLeft = false;
		}

		char key = _getch();
		if (key == ESC)
		{
			clearConsole();
			menu(false);
		}
		else if (key == -32)
		{

			key = _getch();
			if (key == LEFT && currentIndex != 0)
			{
				currentIndex -= row;
				isRightLeft = true;
			}
			else if (key == RIGHT && (currentIndex + row) <= nodeIndexList.number)
			{
				currentIndex += row;
				isRightLeft = true;
			}
			if (key == UP || key == DOWN) {}
		}
	}
}



//=================== TAO HOA DON MOI ===================
void addInvoicePopUp(ProductList& productList, EmployeeList& employeeList, int employeeIndex) {
	InvoiceDetailList invoiceDetailList;
	ShowCur(1);
	int height = HEIGHT_POP_UP;
	int width = WIDTH_POP_UP;
	int x = getCenterX(WIDTH_MAIN_FRAME, width);
	int y = getCenterY(HEIGHT_MAIN_FRAME, height);
	int xInput = x + 18;
	int yInput = y + 2;
	int widthInput = 40;
	int backgroundColor = BACKGROUND_COLOR_POP_UP;

	string invoiceNumber = "";
	string employeeId = (employeeIndex == -1) ? "" : employeeList.employee[employeeIndex]->employeeId;
	string dateString = getDate();
	string type = "";

	//ve bang pop up
	box(x, y, width, height, backgroundColor, COLOR_BLACK, "", TEXT_CENTER);
	//ve ten bang
	box(x, y, width, 1, COLOR_RED, COLOR_BRIGHT_WHITE, "LAP HOA DON", TEXT_CENTER);
	box(x, y + height, width, 1, COLOR_RED, COLOR_BRIGHT_WHITE, "", TEXT_CENTER);
	gotoXY(x + 1, y + height);
	cout << "ESC : QUAY LAI";
	gotoXY(x + 20, y + height);
	cout << "F4: TRA CUU NHAN VIEN";

	const int number = 4;
	string title[number] = { "MA NHAN VIEN", "LOAI HOA DON", "NGAY THANG NAM", "SO HOA DON" };
	string data[number] = { employeeId, type, dateString, invoiceNumber };

	for (int i = 0; i <= number; i++) {
		if (i == number) {
			box(xInput, y + 2 * (i + 1), 10, 3, COLOR_RED, COLOR_BRIGHT_WHITE, "OK", TEXT_CENTER);
		}
		else {
			gotoXY(x + 2, y + 2 * (i + 1));
			setBackgroundColor(COLOR_WHITE);
			setTextColor(COLOR_BLACK);
			cout << title[i];
			box(xInput, y + 2 * (i + 1), widthInput, 1, COLOR_BLACK, COLOR_LIGHT_YELLOW, "", TEXT_CENTER);
			gotoXY(xInput, y + 2 * (i + 1));
			cout << data[i];
		}
	}

	int xPointer = xInput;
	int yPointer = yInput;
	int xPointerOld = xPointer;
	int yPointerOld = yPointer;
	int backgroundColorChoose = 7;
	int i = 0;
	bool isClicked = true;
	char c = char();

	while (true)
	{
		if (isClicked)
		{
			ShowCur(1);
			if (i == number) {
				ShowCur(0);
				box(xPointer, y + 2 * 5, 10, 3, COLOR_LIGHT_YELLOW, COLOR_BLACK, "OK", TEXT_CENTER);
			};
			isClicked = false;
		}
		if (i == 4) c = _getch();
		switch (c)
		{
		case -32:
		{
			isClicked = true;
			c = _getch();
			if (c == UP && yPointer != y + 2)
			{
				yPointer -= 2;
				if (i == number) box(xPointer, y + 2 * (number + 1), 10, 3, COLOR_RED, COLOR_WHITE, "OK", TEXT_CENTER);
				if (i > 0) i--;
			}
			else if (c == DOWN && yPointer != y + 2 * (number + 1))
			{
				yPointer += 2;
				if (i < number + 1) i++;
			}
			c = char();
			break;
		}

		case ESC:
		{
			setBackgroundColor(COLOR_BLACK);
			clearConsole();
			menu(false);
			break;
		}

		case F4:
		{
			IndexList sortedEmployeeList;
			employeeListToEmployeeIndexList(employeeList, sortedEmployeeList);
			sortEmployeeListByName(sortedEmployeeList);
			clearConsole();
			employeeIndex = employeeTableByName(employeeList, sortedEmployeeList, false);
			clearConsole();
			addInvoicePopUp(productList, employeeList, employeeIndex);
			break;
		}

		case ENTER:
		{
			if (i == number) {
				box(xPointer, y + height - 6, widthInput, 5, COLOR_RED, COLOR_LIGHT_YELLOW, "", TEXT_CENTER);

				int employeeIndex = -1;
				bool finishCheckInvoiceNumber = false;
				string e1;
				string e2;
				if (employeeId.empty()) e1 = "MA NHAN VIEN khong duoc de trong";
				if (invoiceNumber.empty()) e2 = "SO HOA DON khong duoc de trong";
				if (e1.empty() && e2.empty())
				{
					for (int i = 0; i < employeeList.number; i++) {
						if (employeeId.compare(employeeList.employee[i]->employeeId) == 0) {
							employeeIndex = i;
						}

						if (!finishCheckInvoiceNumber) {
							for (NodeInvoice* p = employeeList.employee[i]->invoiceList; p != NULL; p = p->pNext) {
								if (invoiceNumber.compare(p->invoice.invoiceNumber) == 0) {
									e2 = "SO HOA DON DA TON TAI";
									finishCheckInvoiceNumber = true;
									break;
								}
							}
						}
					}
					if (employeeIndex == -1) e1 = "MA NHAN VIEN khong ton tai";
				}

				string e3 = checkDate(trim(dateString));
				string e4 = checkType(trim(type));

				setTextColor(COLOR_BRIGHT_WHITE);
				int iy = y + height - 6;
				if (!e1.empty()) { gotoXY(xPointer + 1, iy); cout << e1; iy += 1; }
				if (!e2.empty()) { gotoXY(xPointer + 1, iy); cout << e2; iy += 1; }
				if (!e3.empty()) { gotoXY(xPointer + 1, iy); cout << e3; iy += 1; }
				if (!e4.empty()) { gotoXY(xPointer + 1, iy); cout << e4; iy += 1; }
				if (e1.empty() && e2.empty() && e3.empty() && e4.empty()) {
					Invoice invoice;

					Date date = stringToDate(trim(dateString));
					newInvoice(invoice, trim(invoiceNumber), date, trim(employeeId), type[0]);

					NodeIndexList sortedProductList;
					productListToProductIndexList(productList, sortedProductList);
					sortProductListByName(sortedProductList);

					clearConsole();
					invoiceDetailListTable(employeeList, employeeIndex, productList, sortedProductList, invoice, false);
				}
			}
			else {
				continue;
			}

			break;
		}

		default:
		{
			if (i == 0) upperCaseWhileTyping(xPointer, yPointer, employeeId, c);
			else if (i == 1) upperCaseWhileTyping(xPointer, yPointer, type, c);
			else if (i == 2) upperCaseWhileTyping(xPointer, yPointer, dateString, c);
			else if (i == 3) upperCaseWhileTyping(xPointer, yPointer, invoiceNumber, c);
			break;
		}
		}
	}
}

//=================== THEM / SUA VAT TU TRONG DANH SACH CHI TIET HOA DON ===================
int invoiceDetailListPopUp(Product& product, Invoice& invoice) {
	int height = 25;
	int width = WIDTH_POP_UP;
	int x = getCenterX(WIDTH_MAIN_FRAME, width);
	int y = getCenterY(HEIGHT_MAIN_FRAME, height);
	int xInput = x + 18;
	int yInput = y + 2;
	int widthInput = 40;
	int backgroundColor = BACKGROUND_COLOR_POP_UP;

	int index = searchInvoiceDetail(invoice.invoiceDetailList, product.productId);

	string productId = product.productId;
	string productName = product.productName;
	string quantity = to_string(product.quantity);
	string newQuantity = (index == -1) ? "" : to_string(invoice.invoiceDetailList.invoiceDetail[index].quantity);
	string price = (index == -1) ? "" : floatToString(invoice.invoiceDetailList.invoiceDetail[index].price, 0);
	string VAT = (index == -1) ? "" : floatToString(invoice.invoiceDetailList.invoiceDetail[index].VAT, 2);

	const int number = 6;
	string title1[number] = { "MA VAT TU", "TEN VAT TU", "SO LUONG TON", "SO LUONG XUAT", "DON GIA", "VAT (%)" };
	string title2[number] = { "MA VAT TU", "TEN VAT TU", "SO LUONG TON", "SO LUONG NHAP", "DON GIA", "VAT (%)" };

	string data[number] = { productId, productName, quantity, newQuantity, price, VAT };

	//ve bang pop up
	box(x, y, width, height, backgroundColor, COLOR_BLACK, "", TEXT_CENTER);
	//ve ten bang
	if (invoice.type == 'X') {
		box(x, y, width, 1, COLOR_RED, COLOR_BRIGHT_WHITE, "XUAT VAT TU", TEXT_CENTER);
	}
	else {
		box(x, y, width, 1, COLOR_RED, COLOR_BRIGHT_WHITE, "NHAP VAT TU", TEXT_CENTER);
	}
	box(x, y + height, width, 1, COLOR_RED, COLOR_BRIGHT_WHITE, "", TEXT_CENTER);
	gotoXY(x + 1, y + height);
	cout << "ESC : QUAY LAI";


	for (int i = 0; i <= number; i++) {
		if (i == number) {
			box(xInput, y + 2 * (i + 1), 10, 3, COLOR_RED, COLOR_BRIGHT_WHITE, "OK", TEXT_CENTER);
		}
		else {
			gotoXY(x + 2, y + 2 * (i + 1));
			setBackgroundColor(COLOR_WHITE);
			setTextColor(COLOR_BLACK);
			if (invoice.type == 'X') cout << title1[i];
			else cout << title2[i];

			if (i >= 0 && i <= 2) {
				box(xInput, y + 2 * (i + 1), widthInput, 1, COLOR_RED, COLOR_LIGHT_YELLOW, "", TEXT_CENTER);
			}
			else {
				box(xInput, y + 2 * (i + 1), widthInput, 1, COLOR_BLACK, COLOR_LIGHT_YELLOW, "", TEXT_CENTER);
			}
			gotoXY(xInput, y + 2 * (i + 1));
			cout << data[i];
		}
	}

	int xPointer = xInput;
	int yPointer = y + 2 * 4;
	int xPointerOld = xPointer;
	int yPointerOld = yPointer;
	int backgroundColorChoose = 7;
	int i = 3;
	bool isClicked = true;
	char c = char();

	while (true)
	{
		if (isClicked)
		{
			ShowCur(1);
			if (i == number) {
				ShowCur(0);
				box(xPointer, y + 2 * (number + 1), 10, 3, COLOR_LIGHT_YELLOW, COLOR_BLACK, "OK", TEXT_CENTER);
			};
			isClicked = false;
		}
		if (i == number) c = _getch();

		switch (c)
		{
		case -32:
			isClicked = true;
			c = _getch();
			if (c == UP && yPointer != y + 2 * 4)
			{
				yPointer -= 2;
				if (i == number) box(xPointer, y + 2 * (number + 1), 10, 3, COLOR_RED, COLOR_BRIGHT_WHITE, "OK", TEXT_CENTER);
				if (i > 3) i--;
			}
			else if (c == DOWN && yPointer != y + 2 * (number + 1))
			{
				yPointer += 2;
				if (i < number) i++;
			}
			c = char();
			break;

		case ESC: //THOAT KHOI POP UP
		{
			return NO;
			break;
		}

		case ENTER: //THEM VAT TU VAO DANH SACH CHI TIET HOA DON
			if (i == number) {
				box(xPointer, y + height - 6, widthInput, 5, COLOR_RED, COLOR_LIGHT_YELLOW, "", TEXT_CENTER);

				//KIEM TRA DU LIEU NHAP VAO
				string e1;
				if (invoice.type == 'X') {
					e1 = checkQuantityExport(quantity, trim(newQuantity));
				}
				else e1 = checkQuantity(trim(newQuantity));
				string e2 = checkPrice(trim(price));
				string e3 = checkVAT(trim(VAT));

				//XUAT CAC LOI DANG TON TAI
				int iy = y + height - 6;
				setTextColor(COLOR_BRIGHT_WHITE);
				if (!e1.empty()) { gotoXY(xPointer + 1, iy); cout << e1; iy += 1; }
				if (!e2.empty()) { gotoXY(xPointer + 1, iy); cout << e2; iy += 1; }
				if (!e3.empty()) { gotoXY(xPointer + 1, iy); cout << e3; iy += 1; }

				//NEU KHONG CO LOI NAO THI THEM VAO DANH SACH CHI TIET HOA DON
				if (e1.empty() && e2.empty() && e3.empty()) {
					int index = searchInvoiceDetail(invoice.invoiceDetailList, productId);
					if (index == -1) {
						InvoiceDetail invoiceDetail;
						newInvoiceDetail(invoiceDetail, productId, stoi(trim(newQuantity)), stof(trim(price)), stof(trim(VAT)));
						insertInvoiceDetail(invoice.invoiceDetailList, invoiceDetail);
					}
					else {
						invoice.invoiceDetailList.invoiceDetail[index].quantity = stoi(trim(newQuantity));
						invoice.invoiceDetailList.invoiceDetail[index].price = stof(trim(price));
						invoice.invoiceDetailList.invoiceDetail[index].VAT = stof(trim(VAT));
					}

					return 1;
				}
			}
			else {
				continue;
			}
			break;
		default:
		{
			if (i == 3) upperCaseWhileTyping(xPointer, yPointer, newQuantity, c);
			else if (i == 4) upperCaseWhileTyping(xPointer, yPointer, price, c);
			else if (i == 5) upperCaseWhileTyping(xPointer, yPointer, VAT, c);
			break;
		}
		}
	}
}

//=================== XEM LAI CHI TIET HOA DON ===================
int invoiceTable(EmployeeList& employeeList, int employeeIndex, ProductList& productList, Invoice& invoice) {
	ShowCur(0);
	showEmployeeMakeInvoice(employeeList, employeeIndex, invoice);

	if (invoice.type == 'X') titleBox(1, 3, "HOA DON XUAT");
	else titleBox(1, 3, "HOA DON NHAP");

	int width = 20;
	int height = 2;
	int x = getCenterX(WIDTH_MAIN_FRAME, width * 7);
	int y = getCenterY(HEIGHT_MAIN_FRAME, height * 14);
	int backgroundColor = COLOR_BRIGHT_WHITE;
	int textColor = COLOR_RED;
	setBackgroundColor(0);
	setTextColor(COLOR_WHITE);

	int currentIndex = 0;
	int row = 12;
	const int column = 7;
	string title1[column] = { "STT", "MA VAT TU", "TEN VAT TU", "DON GIA", "SO LUONG XUAT", "VAT (%)", "THANH TIEN" };
	string title2[column] = { "STT", "MA VAT TU", "TEN VAT TU", "DON GIA", "SO LUONG NHAP", "VAT (%)", "THANH TIEN" };

	int cellWidth[column] = { 10, 20, 30, 20, 20, 15, 25 };

	int iy = y + 2;

	for (int k = currentIndex; k < row; k++) {
		int ix = x;
		for (int j = 0; j < column; j++) {
			box3(ix, iy, cellWidth[j], height, backgroundColor, textColor, "");
			ix += cellWidth[j];
		}
		iy = iy + 2;
	}
	if (invoice.type == 'X') {
		tableHeader(x, y, cellWidth, column, backgroundColor, textColor, title1);
	}
	else tableHeader(x, y, cellWidth, column, backgroundColor, textColor, title2);

	tableFooter(x, iy + 1, cellWidth, column, backgroundColor, textColor, "");
	int keyBoxWidth = hotKeyBox(x + 1, iy + 2, "ESC", "QUAY LAI"); keyBoxWidth += 5;
	keyBoxWidth += hotKeyBox(x + keyBoxWidth, iy + 2, "ENTER", "HIEU CHINH"); keyBoxWidth += 5;
	keyBoxWidth += hotKeyBox(x + keyBoxWidth, iy + 2, "DELETE", "XOA"); keyBoxWidth += 5;
	keyBoxWidth += hotKeyBox(x + keyBoxWidth, iy + 2, "F2", "LAP HOA DON"); keyBoxWidth += 5;

	int xPointer = x + 1;
	int yPointer = y + 3;
	int xPointerOld = xPointer;
	int yPointerOld = yPointer;
	int i = 0;
	int iOld = i;
	bool isUpDown = true;
	bool isLeftRight = true;
	bool isFromUp = false;

	while (true) {
		if (!isInvoiceDetailListEmpty(invoice.invoiceDetailList)) {
			if (isLeftRight) {
				setTextColor(COLOR_BRIGHT_WHITE);
				setBackgroundColor(COLOR_BLACK);
				int iy = y + 3;
				for (int k = 0; k < row; k++) {
					int ix = xPointer;
					for (int j = 0; j < column; j++) {
						gotoXY(ix, iy);
						cout << generateSpace(cellWidth[j]);
						ix += cellWidth[j];
					}
					iy = iy + 2;
				}

				int ix;
				iy = y + 3;
				if (invoice.invoiceDetailList.number != 0) {
					float totalMoney = 0;

					for (int k = currentIndex; k < row + currentIndex; k++) {
						if (k >= invoice.invoiceDetailList.number) break;
						else {
							ix = xPointer;
							NodeProduct* p = searchProduct(productList, invoice.invoiceDetailList.invoiceDetail[k].productId);
							InvoiceDetail invoiceDetail = invoice.invoiceDetailList.invoiceDetail[k];

							coutBox(ix, iy, cellWidth[0], TEXT_RIGHT, to_string((k + 1)));
							ix += cellWidth[0];

							coutBox(ix, iy, cellWidth[1], TEXT_LEFT, invoiceDetail.productId);
							ix += cellWidth[1];

							coutBox(ix, iy, cellWidth[2], TEXT_LEFT, p->product.productName);
							ix += cellWidth[2];

							coutBox(ix, iy, cellWidth[3], TEXT_RIGHT, floatToCurrency(invoiceDetail.price));
							ix += cellWidth[3];

							coutBox(ix, iy, cellWidth[4], TEXT_RIGHT, to_string(invoiceDetail.quantity));
							ix += cellWidth[4];

							coutBox(ix, iy, cellWidth[5], TEXT_RIGHT, floatToString(invoiceDetail.VAT, 2));
							ix += cellWidth[5];

							float moneyOfProduct = invoiceDetail.quantity * invoiceDetail.price;
							float money = moneyOfProduct + (moneyOfProduct * (invoiceDetail.VAT / 100));
							coutBox(ix, iy, cellWidth[6], TEXT_RIGHT, floatToCurrency(money));
							ix += cellWidth[6];

							totalMoney += money;
						}
						iy = iy + 2;
					}

					gotoXY(x + 105, 34);
					setTextColor(COLOR_LIGHT_YELLOW);
					cout << "TONG CONG";

					gotoXY(x + 116, 34);
					setTextColor(COLOR_BRIGHT_WHITE);
					int num = cellWidth[6] - 2;
					cout << std::right << setw(num);
					cout << floatToCurrency(totalMoney);
				}


				i = 0;
				iOld = i;
				yPointer = y + 3;
				yPointerOld = yPointer;
				if (isFromUp) {
					yPointer = y + 3 + 2 * (row - 1);
					yPointerOld = yPointer;
					i = row - 1;
					iOld = i;
					isFromUp = false;
				}
				isLeftRight = false;
			}

			if (isUpDown) {
				gotoXY(xPointerOld + cellWidth[0] + 1, yPointerOld);
				setBackgroundColor(COLOR_BLACK);
				setTextColor(COLOR_BRIGHT_WHITE);
				cout << invoice.invoiceDetailList.invoiceDetail[iOld].productId;

				gotoXY(xPointer + cellWidth[0] + 1, yPointer);
				setBackgroundColor(COLOR_RED);
				setTextColor(COLOR_LIGHT_YELLOW);
				cout << invoice.invoiceDetailList.invoiceDetail[i + currentIndex].productId;

				xPointerOld = xPointer;
				yPointerOld = yPointer;

				isUpDown = false;
			}
		}

		char key = _getch();
		switch (key)
		{
		case -32:
		{
			key = _getch();
			if (key == LEFT && currentIndex != 0) {
				currentIndex -= row;
				isLeftRight = true;
				isUpDown = true;
			}
			else if (key == RIGHT && (currentIndex + row) <= invoice.invoiceDetailList.number - 1) {
				currentIndex += row;
				isLeftRight = true;
				isUpDown = true;
			}
			else if (key == UP)
			{
				if (i == 0 && currentIndex != 0) {
					isLeftRight = true;
					isFromUp = true;
					currentIndex -= row;

				}
				else if (i > 0)
				{
					yPointer -= 2;
					iOld = i;
					i--;
				}
				isUpDown = true;
			}
			else if (key == DOWN && (i + currentIndex) < invoice.invoiceDetailList.number - 1)
			{
				if (i == row - 1) {
					isLeftRight = true;
					currentIndex += row;
				}
				else if (i < row)
				{
					yPointer += 2;
					iOld = i;
					i++;
				}
				isUpDown = true;
			}

			// XOA VAT TU KHOI DANH SACH CHI TIET HOA DON
			else if (key == DELETE_KEY && !isInvoiceDetailListEmpty(invoice.invoiceDetailList))
			{
				string productId = invoice.invoiceDetailList.invoiceDetail[i + currentIndex].productId;

				string message = "XOA VAT TU KHOI DANH SACH CHI TIET HOA DON?";
				int isAccept = warningPopUp(message);
				if (isAccept == YES) { //CHO PHEP XOA
					deleteInvoiceDetail(invoice.invoiceDetailList, productId);
				}
				//KHONG CHO PHEP
				clearConsole();
				invoiceTable(employeeList, employeeIndex, productList, invoice);
			}
			break;
		}
		case ESC: //QUAY LAI TRANG THEM VAT TU VAO DANH SACH CHI TIET HOA DON
		{
			return NO;
			break;
		}

		case F2: //LAP HOA DON
		{
			//NEU DANH SACH CHI TIET HOA DON KHONG TRONG
			if (!isInvoiceDetailListEmpty(invoice.invoiceDetailList)) {
				//THEM HOA DON VAO DANH SACH HOA DON CUA NHAN VIEN
				insertInvoice(employeeList.employee[employeeIndex]->invoiceList, invoice);

				//DUYET DANH SACH CHI TIET HOA DON DE CAP NHAT SO LUONG VAT TU
				for (int i = 0; i < invoice.invoiceDetailList.number; i++) {
					NodeProduct* p = searchProduct(productList, invoice.invoiceDetailList.invoiceDetail[i].productId);

					//NEU HOA DON XUAT THI SE GIAM SO LUONG TON CUA VAT TU TRONG DANH SACH VAT TU
					if (invoice.type == 'X') {
						p->product.quantity -= invoice.invoiceDetailList.invoiceDetail[i].quantity;
						p->product.isUsed = true;
					}
					else { //NEU HOA DON NHAP THI SE TANG SO LUONG TON CUA VAT TU TRONG DANH SACH VAT TU
						p->product.quantity += invoice.invoiceDetailList.invoiceDetail[i].quantity;
						p->product.isUsed = true;
					}

				}
				//CAP NHAT FILE VAT TU
				writeProductFile(productList);

				//CAP NHAT FILE NHAN VIEN
				writeEmployeeFile(employeeList);

				//XOA MAN HINH TRO VE MENU
				string message = "LAP HOA DON THANH CONG";
				int k = notificationPopUp(message);
				if (k == YES) {
					clearConsole();
					menu(false);
				}
			}
			break;
		}

		case ENTER: //SUA VAT TU TRONG DANH SACH CHI TIET HOA DON
		{
			if (!isInvoiceDetailListEmpty(invoice.invoiceDetailList)) {
				NodeProduct* p = searchProduct(productList, invoice.invoiceDetailList.invoiceDetail[i + currentIndex].productId);
				int k = invoiceDetailListPopUp(p->product, invoice);
				if (k == YES || k == NO) {
					clearConsole();
					invoiceTable(employeeList, employeeIndex, productList, invoice);
				}
			}
			break;
		}

		default:
			break;
		}
	}

}

//=================== BANG CHON VAT TU DE THEM VAO DANH SACH CHI TIET HOA DON ===================
void invoiceDetailListTable(EmployeeList& employeeList, int employeeIndex, ProductList& productList, NodeIndexList& sortedProductList, Invoice& invoice, bool isSearch) {
	ShowCur(0);
	showEmployeeMakeInvoice(employeeList, employeeIndex, invoice);

	if (invoice.type == 'X') titleBox(1, 3, "CHON VAT TU DE XUAT");
	else titleBox(1, 3, "CHON VAT TU DE NHAP");

	int width = 20;
	int height = 2;
	int x = getCenterX(WIDTH_MAIN_FRAME, width * 7);
	int y = getCenterY(HEIGHT_MAIN_FRAME, height * 12);
	int backgroundColor = COLOR_BRIGHT_WHITE;
	int textColor = COLOR_RED;
	setBackgroundColor(COLOR_BLACK);

	int currentIndex = 0;
	int row = 12;
	const int column = 6;
	string title1[column] = { "MA VAT TU", "TEN VAT TU", "SO LUONG TON", "SO LUONG XUAT", "DON GIA (VND)", "VAT (%)" };;
	string title2[column] = { "MA VAT TU", "TEN VAT TU", "SO LUONG TON", "SO LUONG NHAP", "DON GIA (VND)", "VAT (%)" };

	int cellWidth[column] = { 20, 40, 20, 20, 25, 15 };

	int iy = y + 2;
	for (int k = currentIndex; k < row; k++) {
		int ix = x;
		for (int j = 0; j < column; j++) {
			box3(ix, iy, cellWidth[j], height, backgroundColor, textColor, "");
			ix += cellWidth[j];
		}
		iy = iy + 2;
	}
	if (invoice.type == 'X') {
		tableHeader(x, y, cellWidth, column, backgroundColor, textColor, title1);
	}
	else {
		tableHeader(x, y, cellWidth, column, backgroundColor, textColor, title2);
	}

	tableFooter(x, iy + 1, cellWidth, column, backgroundColor, textColor, "");
	int keyBoxWidth = hotKeyBox(x + 1, iy + 2, "ESC", "QUAY LAI"); keyBoxWidth += 5;
	keyBoxWidth += hotKeyBox(x + keyBoxWidth, iy + 2, "ENTER", "THEM / HIEU CHINH"); keyBoxWidth += 5;
	keyBoxWidth += hotKeyBox(x + keyBoxWidth, iy + 2, "DELETE", "XOA"); keyBoxWidth += 5;
	keyBoxWidth += hotKeyBox(x + keyBoxWidth, iy + 2, "CTRL + F", "TIM KIEM"); keyBoxWidth += 5;
	keyBoxWidth += hotKeyBox(x + keyBoxWidth, iy + 2, "F2", "TIEP TUC"); keyBoxWidth += 5;

	int xPointer = x + 1;
	int yPointer = y + 3;
	int xPointerOld = xPointer;
	int yPointerOld = yPointer;
	int xPage = x + 125;
	int yPage = iy + 2;
	int xSearchInput = x + 1;
	int ySearchInput = 7;
	int i = 0;
	int iOld = i;
	bool isUpDown = true;
	bool isLeftRight = true;
	bool isFromUp = false;
	bool isInit = false;

	while (true) {
		if (isInit) {
			setTextColor(COLOR_BRIGHT_WHITE);
			setBackgroundColor(COLOR_BLACK);
			int iy = y + 3;
			for (int k = 0; k < row; k++) {
				int ix = xPointer;
				for (int j = 0; j < column; j++) {
					gotoXY(ix, iy);
					cout << generateSpace(cellWidth[j]);
					ix += cellWidth[j];
				}
				iy = iy + 2;
			}
			isInit = false;
		}

		if (!isSortedProductListEmpty(sortedProductList)) {
			if (isLeftRight) {
				setTextColor(COLOR_BRIGHT_WHITE);
				int ix;
				iy = y + 3;
				for (int k = currentIndex; k < row + currentIndex; k++) {
					if (k >= sortedProductList.number) break;
					else {
						ix = xPointer;
						int index = searchInvoiceDetail(invoice.invoiceDetailList, sortedProductList.nodes[k].nodeProduct->product.productId);

						Product product = sortedProductList.nodes[k].nodeProduct->product;

						coutBox(ix, iy, cellWidth[0], TEXT_LEFT, product.productId);
						ix += cellWidth[0];

						coutBox(ix, iy, cellWidth[1], TEXT_LEFT, product.productName);
						ix += cellWidth[1];

						coutBox(ix, iy, cellWidth[2], TEXT_RIGHT, to_string(product.quantity));
						ix += cellWidth[2];

						if (index == -1) {
							gotoXY(ix, iy); cout << ""; ix += cellWidth[3];
							gotoXY(ix, iy); cout << ""; ix += cellWidth[4];
							gotoXY(ix, iy); cout << ""; ix += cellWidth[5];
						}
						else {
							InvoiceDetail invoiceDetail = invoice.invoiceDetailList.invoiceDetail[index];
							coutBox(ix, iy, cellWidth[3], TEXT_RIGHT, to_string(invoiceDetail.quantity));
							ix += cellWidth[3];

							coutBox(ix, iy, cellWidth[4], TEXT_RIGHT, floatToCurrency(invoiceDetail.price));
							ix += cellWidth[4];

							coutBox(ix, iy, cellWidth[5], TEXT_RIGHT, floatToString(invoiceDetail.VAT, 2));
							ix += cellWidth[5];
						}
					}
					iy = iy + 2;
				}

				setTextColor(COLOR_LIGHT_YELLOW);
				gotoXY(xPage, yPage);
				cout << generateSpace(10);
				gotoXY(xPage, yPage);
				cout << "TRANG " << currentIndex / row + 1 << "/" << (sortedProductList.number - 1) / row + 1;

				i = 0;
				iOld = i;
				yPointer = y + 3;
				yPointerOld = yPointer;
				if (isFromUp) {
					yPointer = y + 3 + 2 * (row - 1);
					yPointerOld = yPointer;
					i = row - 1;
					iOld = i;
					isFromUp = false;
				}
				isLeftRight = false;
			}

			if (isUpDown) {
				gotoXY(xPointerOld + 1, yPointerOld);
				setBackgroundColor(COLOR_BLACK);
				setTextColor(COLOR_BRIGHT_WHITE);
				cout << sortedProductList.nodes[iOld + currentIndex].nodeProduct->product.productId;

				gotoXY(xPointer + 1, yPointer);
				setBackgroundColor(COLOR_RED);
				setTextColor(COLOR_LIGHT_YELLOW);
				cout << sortedProductList.nodes[i + currentIndex].nodeProduct->product.productId;

				xPointerOld = xPointer;
				yPointerOld = yPointer;

				isUpDown = false;
			}
		}

		char key = _getch();
		switch (key)
		{
		case -32:
		{
			key = _getch();
			if (key == LEFT && currentIndex != 0) {
				currentIndex -= row;
				isInit = true;
				isLeftRight = true;
				isUpDown = true;
			}
			else if (key == RIGHT && (currentIndex + row) <= sortedProductList.number - 1) {
				currentIndex += row;
				isInit = true;
				isLeftRight = true;
				isUpDown = true;
			}
			else if (key == UP)
			{
				if (i == 0 && currentIndex != 0) {
					isInit = true;
					isLeftRight = true;
					isFromUp = true;
					currentIndex -= row;
				}
				else if (i > 0)
				{
					yPointer -= 2;
					iOld = i;
					i--;
				}
				isUpDown = true;
			}
			else if (key == DOWN && (i + currentIndex) < sortedProductList.number - 1)
			{
				if (i == row - 1) {
					isInit = true;
					isLeftRight = true;
					currentIndex += row;
				}
				else if (i < row)
				{
					yPointer += 2;
					iOld = i;
					i++;
				}
				isUpDown = true;
			}

			// XOA VAT TU KHOI DANH SACH CHI TIET HOA DON
			else if (key == DELETE_KEY) {
				string productId = sortedProductList.nodes[i + currentIndex].nodeProduct->product.productId;

				string message = "XOA VAT TU KHOI DANH SACH CHI TIET HOA DON?";
				int isAccept = warningPopUp(message);

				if (isAccept == YES) //DONG Y ==> XOA VAT TU
					deleteInvoiceDetail(invoice.invoiceDetailList, productId);

				clearConsole();
				invoiceDetailListTable(employeeList, employeeIndex, productList, sortedProductList, invoice, isSearch);
			}
			break;
		}
		case ESC: //QUAY LAI
		{
			if (isSearch) {
				setBackgroundColor(COLOR_BLACK);
				gotoXY(xSearchInput, ySearchInput);
				cout << generateSpace(50);

				delete[] sortedProductList.nodes;
				productListToProductIndexList(productList, sortedProductList);
				sortProductListByName(sortedProductList);

				ShowCur(0);
				isSearch = false;
				isInit = true;
				isLeftRight = true;
				isUpDown = true;
			}
			else {
				string message = "HUY HOA DON NAY?";
				int k = warningPopUp(message);
				if (k == YES) { //DONG Y
					delete[] sortedProductList.nodes;
					clearConsole();
					menu(false);
				}
				else {
					clearConsole();
					invoiceDetailListTable(employeeList, employeeIndex, productList, sortedProductList, invoice, isSearch);
				}
			}
			break;
		}

		case ENTER: //THEM VAT TU HOAC SUA VAT TU TRONG DANH SACH CHI TIET HOA DON
		{
			if (!isSortedProductListEmpty(sortedProductList))
			{
				Product product = sortedProductList.nodes[i + currentIndex].nodeProduct->product;

				//Neu danh sach chi tiet hoa don day va vat tu chua ton tai trong danh sach chi tiet hoa don
				if (isInvoiceDetailListFull(invoice.invoiceDetailList)
					&& searchInvoiceDetail(invoice.invoiceDetailList, product.productId) == -1)
				{
					string message = "DANH SACH CHI TIET HOA DON DA DAY";
					int k = notificationPopUp(message);
					if (k == YES) { //DONG Y
						clearConsole();
						invoiceDetailListTable(employeeList, employeeIndex, productList, sortedProductList, invoice, isSearch);
					}
				}
				else { //Neu danh sach vat tu chua day
					int k = invoiceDetailListPopUp(product, invoice);

					if (k == YES || k == NO) //Da them/sua vat tu
					{
						clearConsole();
						invoiceDetailListTable(employeeList, employeeIndex, productList, sortedProductList, invoice, isSearch);
					}
				}

			}
			break;
		}

		case CTRL_F: // TIM KIEM VAT TU TRONG DANH SACH VAT TU
		{
			setTextColor(COLOR_BRIGHT_WHITE);
			setBackgroundColor(COLOR_BLACK);
			string text = "NHAP TEN VAT TU: ";
			gotoXY(xSearchInput, ySearchInput);
			cout << text << generateSpace(30);

			string productName = "";
			char c = char();
			upperCaseWhileTypingEnter(xSearchInput + text.length() + 1, ySearchInput, productName, c);

			if (c == ENTER) {
				delete[] sortedProductList.nodes;
				searchProductListByName(productList, sortedProductList, productName);

				ShowCur(0);
				isSearch = true;
				isInit = true;
				isLeftRight = true;
				isUpDown = true;

			}
			else if (c == ESC) {
				setBackgroundColor(COLOR_BLACK);
				gotoXY(xSearchInput, ySearchInput);
				cout << generateSpace(50);
				ShowCur(0);
			}

			break;
		}

		case F2: //TIEP TUC
		{
			//KIEM TRA DANH SACH CHI TIET HOA DON RONG
			if (isInvoiceDetailListEmpty(invoice.invoiceDetailList)) {
				string message = "PHAI CO IT NHAT 1 VAT TU DUOC CHON";
				int k = notificationPopUp(message);
				if (k == YES) {
					clearConsole();
					invoiceDetailListTable(employeeList, employeeIndex, productList, sortedProductList, invoice, isSearch);
				}
			}

			//NEU DANH SACH KHONG RONG
			else {
				clearConsole();
				int k = invoiceTable(employeeList, employeeIndex, productList, invoice);
				if (k == NO) { //An ESC trong bang kiem tra danh sach chi tiet hoa don

					delete[] sortedProductList.nodes;
					productListToProductIndexList(productList, sortedProductList);
					sortProductListByName(sortedProductList);

					clearConsole();
					invoiceDetailListTable(employeeList, employeeIndex, productList, sortedProductList, invoice, false);
				}
			}
			break;
		}

		default:
			break;
		}
	}
}



//=================== IN HOA DON ===================
int showInvoice(ProductList& productList, Employee& employee, Invoice& invoice) {
	box2(2, 1, WIDTH_MAIN_FRAME - 5, HEIGHT_MAIN_FRAME - 3, COLOR_BRIGHT_WHITE, COLOR_BLACK, "");
	ShowCur(0);
	int width = 20;
	int height = 1;
	int x = getCenterX(WIDTH_MAIN_FRAME, width * 7);
	int y = getCenterY(HEIGHT_MAIN_FRAME, height * 16);
	int backgroundColor = COLOR_WHITE; // chinh mau vien table
	int textColor = COLOR_RED;
	setBackgroundColor(0);
	setTextColor(COLOR_BRIGHT_WHITE);

	int xText = 4;
	int xText2 = xText + 30;
	int yText = 2;
	int iyText = yText + 1;

	string text1 = "BANG TONG HOP DON HANG";
	gotoXY(getCenterX(WIDTH_MAIN_FRAME, text1.length()), iyText);
	cout << text1; iyText += 2;

	string title1[7] = { "Khach hang", "Dia chi", "Dien thoai" };


	gotoXY(x, iyText);
	cout << "Khach hang :";
	gotoXY(xText2, iyText);
	cout << "LUU TIEN PHAT";

	Date date = invoice.date;
	gotoXY(x + 70, iyText);
	cout << "Ngay " << date.day << " thang " << date.month << " nam " << date.year;

	iyText++;


	gotoXY(x, iyText);
	cout << "Dia chi :";
	gotoXY(xText2, iyText);
	cout << "Tan Binh";

	gotoXY(x + 70, iyText);
	cout << "Nguoi lap :";
	gotoXY(x + 70 + 20, iyText);
	cout << employee.lastname + " " + employee.firstname;

	iyText++;

	gotoXY(x, iyText);
	cout << "Dien thoai :";
	gotoXY(xText2, iyText);
	cout << "0796919429";

	gotoXY(x + 70, iyText);
	cout << "Loai hoa don :";
	gotoXY(x + 70 + 20, iyText);
	if (invoice.type == 'X') cout << "XUAT";
	else cout << "NHAP";

	iyText += 3;

	gotoXY(xText2 + 80, iyText);
	cout << "DON VI TINH: VND";

	iyText += 1;


	int currentIndex = 0;
	int row = invoice.invoiceDetailList.number;
	const int column = 8;
	string cellHeader1[column] = { "STT", "NOI DUNG", "DON GIA", "SO LUONG", "TRI GIA", "VAT (%)", "VAT (VND)", "THANH TIEN" };
	string cellHeader2[column] = { "STT", "NOI DUNG", "DON GIA", "SO LUONG", "TRI GIA", "VAT (%)", "VAT (VND)", "THANH TIEN" };

	int cellWidth[column] = { 5, 25, 20, 12, 20, 13, 20, 25 };

	int iy = iyText + 2;
	for (int k = currentIndex; k < row; k++) {
		int ix = x;
		for (int j = 0; j < column; j++) {
			box3(ix, iy, cellWidth[j], height, backgroundColor, textColor, "");
			ix += cellWidth[j];
		}
		iy = iy + 1;
	}
	if (invoice.type == 'X') tableHeader(x, iyText, cellWidth, column, backgroundColor, textColor, cellHeader1);
	else tableHeader(x, iyText, cellWidth, column, backgroundColor, textColor, cellHeader2);
	tableFooter(x, iy + 1, cellWidth, column, backgroundColor, textColor, "");


	int xPointer = x + 1;
	int yPointer = iyText + 3;
	int xPointerOld = xPointer;
	int yPointerOld = yPointer;
	int i = 0;
	int iOld = i;
	bool isInit = true;
	InvoiceDetailList invoiceDetailList = invoice.invoiceDetailList;

	while (true) {
		if (isInit) {
			setTextColor(COLOR_BRIGHT_WHITE);
			setBackgroundColor(COLOR_BLACK);

			int ix;
			iy = yPointer;
			float totalMoney = 0;
			for (int k = 0; k < row; k++) {
				if (k >= invoiceDetailList.number) break;
				else {
					InvoiceDetail invoiceDetail = invoiceDetailList.invoiceDetail[k];
					NodeProduct* p = searchProduct(productList, invoiceDetail.productId);

					ix = x + 1;

					coutBox(ix, iy, cellWidth[0], TEXT_RIGHT, to_string(k + 1));
					ix += cellWidth[0];

					coutBox(ix, iy, cellWidth[1], TEXT_LEFT, p->product.productName);
					ix += cellWidth[1];

					coutBox(ix, iy, cellWidth[2], TEXT_RIGHT, floatToCurrency(invoiceDetail.price));
					ix += cellWidth[2];

					coutBox(ix, iy, cellWidth[3], TEXT_RIGHT, to_string(invoiceDetail.quantity));
					ix += cellWidth[3];

					float moneyOfProduct = invoiceDetail.price * invoiceDetail.quantity;
					coutBox(ix, iy, cellWidth[4], TEXT_RIGHT, floatToCurrency(moneyOfProduct));
					ix += cellWidth[4];

					coutBox(ix, iy, cellWidth[5], TEXT_RIGHT, floatToString(invoiceDetail.VAT, 2));
					ix += cellWidth[5];

					float moneyWithVAT = moneyOfProduct * (invoiceDetail.VAT / 100);
					coutBox(ix, iy, cellWidth[6], TEXT_RIGHT, floatToCurrency(moneyWithVAT));
					ix += cellWidth[6];

					float money = moneyWithVAT + moneyOfProduct;
					coutBox(ix, iy, cellWidth[7], TEXT_RIGHT, floatToCurrency(money));
					ix += cellWidth[7];

					totalMoney += money;
				}
				iy = iy + 1;
			}

			gotoXY(x + 105, iy + 1);
			setTextColor(COLOR_LIGHT_YELLOW);
			cout << "TONG CONG";

			gotoXY(x + 116, iy + 1);
			setTextColor(COLOR_BRIGHT_WHITE);
			int num = cellWidth[7] - 2;
			cout << std::right << setw(num);
			cout << floatToCurrency(totalMoney);

			gotoXY(x, iy + 3);
			setTextColor(COLOR_LIGHT_YELLOW);
			cout << "Bang chu: " + DocTienBangChu(totalMoney, "dong");
		}


		char key = _getch();
		switch (key)
		{
		case ESC:
		{
			return 1;
			break;
		}
		default:
			break;
		}

	}
}

void invoicePopUp(ProductList& productList, EmployeeList& employeeList) {
	ShowCur(1);
	int height = HEIGHT_POP_UP;
	int width = WIDTH_POP_UP;
	int x = getCenterX(WIDTH_MAIN_FRAME, width);
	int y = getCenterY(HEIGHT_MAIN_FRAME, height);
	int xInput = x + 18;
	int widthInput = 40;

	/*string employeeId = "NV000";*/
	string invoiceNumber = "";

	const int number = 1;
	//string title[number] = { "MANV", "SO HOA DON" };
	string title[number] = { "SO HOA DON" };
	//ve bang pop up
	box(x, y, width, height, COLOR_WHITE, COLOR_BLACK, "", TEXT_CENTER);
	box(x, y, width, 1, COLOR_RED, COLOR_BRIGHT_WHITE, "IN HOA DON", TEXT_CENTER);
	box(x, y + height, width, 1, COLOR_RED, COLOR_BRIGHT_WHITE, "", TEXT_CENTER);
	gotoXY(x + 1, y + height);
	cout << "ESC : QUAY LAI";

	for (int i = 0; i <= number; i++) {
		if (i == number) {
			box(xInput, y + 2 * (i + 1), 10, 3, COLOR_RED, COLOR_BRIGHT_WHITE, "OK", TEXT_CENTER);
		}
		else {
			gotoXY(x + 2, y + 2 * (i + 1));
			setBackgroundColor(COLOR_WHITE);
			setTextColor(COLOR_BLACK);
			cout << title[i];
			box(xInput, y + 2 * (i + 1), widthInput, 1, COLOR_BLACK, COLOR_LIGHT_YELLOW, "", TEXT_CENTER);
		}
	}

	int xPointer = xInput;
	int yPointer = y + 2;
	int xPointerOld = xPointer;
	int yPointerOld = yPointer;
	int i = 0;
	bool isClicked = true;
	char c = char();

	while (true)
	{
		if (isClicked)
		{
			ShowCur(1);
			if (i == number) {
				ShowCur(0);
				box(xPointer, y + 2 * (number + 1), 10, 3, COLOR_LIGHT_YELLOW, COLOR_BLACK, "OK", TEXT_CENTER);
			};
			/*if (i == 0) upperCaseWhileTyping(xPointer, yPointer, employeeId, c);*/
			isClicked = false;
		}
		if (i == number) c = _getch();

		switch (c)
		{
		case -32:
		{
			isClicked = true;
			c = _getch();
			if (c == UP && yPointer != y + 2)
			{
				yPointer -= 2;
				if (i == number) box(xPointer, y + 2 * (number + 1), 10, 3, COLOR_RED, COLOR_BRIGHT_WHITE, "OK", TEXT_CENTER);
				if (i > 0) i--;
			}
			else if (c == DOWN && yPointer != y + 2 * (number + 1))
			{
				yPointer += 2;
				if (i < (number + 1)) i++;
			}
			c = char();
			break;
		}

		case ESC:
		{
			setBackgroundColor(COLOR_BLACK);
			clearConsole();
			menu(false);
			break;
		}

		case ENTER:
		{
			if (i == number) {
				box(xPointer, y + height - 6, widthInput, 5, COLOR_RED, COLOR_LIGHT_YELLOW, "", TEXT_CENTER);

				string e = "";
				string e1 = "";
				Employee employee;
				invoiceNumber = trim(invoiceNumber);

				int employeeIndex = 0;
				NodeInvoice* p = nullptr;
				for (employeeIndex = 0; employeeIndex < employeeList.number; employeeIndex++) {
					bool found = false;
					for (p = employeeList.employee[employeeIndex]->invoiceList; p != NULL; p = p->pNext) {
						if (invoiceNumber.compare(p->invoice.invoiceNumber) == 0) {
							found = true;
							break;
						}
					}
					if (found == true) break;
				}

				if (p == nullptr) e = "MA HOA DON khong ton tai";

				int iy = y + height - 6;
				setTextColor(COLOR_BRIGHT_WHITE);
				if (!e.empty()) { gotoXY(xPointer + 1, iy); cout << e; iy += 1; }

				if (e.empty()) {
					clearConsole();
					int k = showInvoice(productList, *employeeList.employee[employeeIndex], p->invoice);
					if (k >= 0) {
						clearConsole();
						invoicePopUp(productList, employeeList);
					}

					c = ESC; i--;
				}
			}
			else {
				continue;
			}

			break;
		}

		default:
		{
			//if (i == 0) upperCaseWhileTyping(xPointer, yPointer, employeeId, c);
			if (i == 0) upperCaseWhileTyping(xPointer, yPointer, invoiceNumber, c);
			break;
		}

		}
	}
}



//=================== THONG KE HOA DON TRONG KHOANG THOI GIAN ===================
int statisticialTable(StatList& statList, EmployeeList& employeeList, Date& fromDate, Date& toDate) {
	ShowCur(0);
	string text1 = "BANG LIET KE CAC HOA DON TRONG KHOANG THOI GIAN";
	string text2 = "TU NGAY: " + dateToString(fromDate) + "  DEN NGAY: " + dateToString(toDate);
	gotoXY(getCenterX(WIDTH_MAIN_FRAME, text1.length()), 2);
	cout << text1;
	gotoXY(getCenterX(WIDTH_MAIN_FRAME, text2.length()), 3);
	cout << text2;


	int width = 20;
	int height = 2;
	int x = getCenterX(WIDTH_MAIN_FRAME, width * 7);
	int y = getCenterY(HEIGHT_MAIN_FRAME, height * 14);
	int backgroundColor = COLOR_WHITE; // chinh mau vien table
	int textColor = COLOR_RED;
	setBackgroundColor(0);
	setTextColor(COLOR_WHITE);

	int currentIndex = 0;
	int row = 12;
	const int column = 5;
	string title[column] = { "SO HOA DON", "NGAY LAP", "LOAI HOA DON", "HO TEN NHAN VIEN LAP", "TRI GIA HOA DON" };
	int cellWidth[column] = { 25, 25, 20, 40, 30 };

	int iy = y + 2;

	for (int k = currentIndex; k < row; k++) {
		int ix = x;
		for (int j = 0; j < column; j++) {
			box3(ix, iy, cellWidth[j], height, backgroundColor, textColor, "");
			ix += cellWidth[j];
		}
		iy = iy + 2;
	}
	tableHeader(x, y, cellWidth, column, backgroundColor, textColor, title);
	tableFooter(x, iy + 1, cellWidth, column, backgroundColor, textColor, "");

	int keyBoxWidth = hotKeyBox(x + 1, iy + 2, "ESC", "QUAY LAI"); keyBoxWidth += 5;
	keyBoxWidth += hotKeyBox(x + keyBoxWidth, iy + 2, "LEFT/RIGHT", "SANG TRANG"); keyBoxWidth += 5;


	int xPointer = x + 1;
	int yPointer = y + 3;
	int xPointerOld = xPointer;
	int yPointerOld = yPointer;
	int i = 0;
	int iOld = i;
	bool isLeftRight = true;
	bool isFromUp = false;

	while (true) {
		if (isLeftRight) {
			setTextColor(COLOR_BRIGHT_WHITE);
			setBackgroundColor(COLOR_BLACK);
			int iy = y + 3;
			for (int k = 0; k < row; k++) {
				int ix = xPointer;
				for (int j = 0; j < column; j++) {
					gotoXY(ix, iy);
					cout << generateSpace(cellWidth[j]);
					ix += cellWidth[j];
				}
				iy = iy + 2;
			}

			if (statList.number != 0)
			{
				int ix;
				iy = y + 3;
				for (int k = currentIndex; k < row + currentIndex; k++) {
					if (k >= statList.number) break;
					else {
						ix = xPointer;
						Stat invoiceStatistics = *statList.nodes[k];

						int num = 0;
						gotoXY(ix, iy); cout << " " << invoiceStatistics.nodeInvoice->invoice.invoiceNumber; ix += cellWidth[0];

						gotoXY(ix, iy);
						num = cellWidth[1] - 2;
						cout << std::right << setw(num);
						cout << dateToString(invoiceStatistics.nodeInvoice->invoice.date); ix += cellWidth[1];

						gotoXY(ix, iy);
						cout << " " << (invoiceStatistics.nodeInvoice->invoice.type == 'X' ? "XUAT" : "NHAP");
						ix += cellWidth[2];

						gotoXY(ix, iy);
						cout << " " << employeeList.employee[invoiceStatistics.index]->lastname + " " + employeeList.employee[invoiceStatistics.index]->firstname; ix += cellWidth[3];

						gotoXY(ix, iy);
						num = cellWidth[4] - 2;
						cout << std::right << setw(num);
						cout << doubleToCurrency(invoiceStatistics.money); ix += cellWidth[4];
					}
					iy = iy + 2;
				}
			}

			i = 0;
			iOld = i;
			yPointer = y + 3;
			yPointerOld = yPointer;
			if (isFromUp) {
				yPointer = y + 3 + 2 * (row - 1);
				yPointerOld = yPointer;
				i = row - 1;
				iOld = i;
				isFromUp = false;
			}
			isLeftRight = false;
		}

		char key = _getch();
		switch (key)
		{
		case -32:
		{
			if (statList.number != 0)
			{
				key = _getch();
				if (key == LEFT && currentIndex != 0)
				{
					currentIndex -= row;
					isLeftRight = true;
				}
				else if (key == RIGHT && (currentIndex + row) <= statList.number - 1) {
					currentIndex += row;
					isLeftRight = true;
				}
				else if (key == UP) {}
				else if (key == DOWN) {}
			}
			break;
		}
		case ESC:
		{
			for (int i = 0; i < statList.number; i++)
			{
				delete statList.nodes[i];
			}
			statList.number = 0;
			return 1;
			break;
		}

		default:
			break;
		}
	}
}

void statisticialPopUp(EmployeeList& employeeList) {
	ShowCur(1);
	int height = HEIGHT_POP_UP;
	int width = WIDTH_POP_UP;
	int x = getCenterX(WIDTH_MAIN_FRAME, width);
	int y = getCenterY(HEIGHT_MAIN_FRAME, height);
	int xInput = x + 22;
	int widthInput = 36;
	const int number = 2;

	/*string startDateString = "01/01/2000";
	string endDateString = "31/12/2000";*/

	string startDateString = "";
	string endDateString = "";

	string title[number] = { "NGAY BAT DAU", "NGAY KET THUC" };

	//ve bang pop up
	box(x, y, width, height, COLOR_WHITE, COLOR_BLACK, "", TEXT_CENTER);
	box(x, y, width, 1, COLOR_RED, COLOR_BRIGHT_WHITE, "THONG KE HOA DON", TEXT_CENTER);
	box(x, y + height, width, 1, COLOR_RED, COLOR_BRIGHT_WHITE, "", TEXT_CENTER);
	gotoXY(x + 1, y + height);
	cout << "ESC : QUAY LAI";

	for (int i = 0; i <= number; i++) {
		if (i == number) {
			box(xInput, y + 2 * (i + 1), 10, 3, COLOR_RED, COLOR_BRIGHT_WHITE, "OK", TEXT_CENTER);
		}
		else {
			gotoXY(x + 2, y + 2 * (i + 1));
			setBackgroundColor(COLOR_WHITE);
			setTextColor(COLOR_BLACK);
			cout << title[i];
			box(xInput, y + 2 * (i + 1), widthInput, 1, COLOR_BLACK, COLOR_LIGHT_YELLOW, "", TEXT_CENTER);
		}
	}

	int xPointer = xInput;
	int yPointer = y + 2;
	int xPointerOld = xPointer;
	int yPointerOld = yPointer;
	int backgroundColorChoose = 7;
	int i = 0;
	bool isClicked = true;
	char c = char();

	while (true)
	{
		if (isClicked)
		{
			ShowCur(1);
			if (i == number) {
				ShowCur(0);
				box(xPointer, y + 2 * (number + 1), 10, 3, COLOR_LIGHT_YELLOW, COLOR_BLACK, "OK", TEXT_CENTER);
			};
			if (i == 0) upperCaseWhileTyping(xPointer, yPointer, startDateString, c);
			isClicked = false;
		}

		if (i == number) c = _getch();

		switch (c)
		{
		case -32:
		{
			isClicked = true;
			c = _getch();
			if (c == UP && yPointer != y + 2)
			{
				yPointer -= 2;
				if (i == number) box(xPointer, y + 2 * (number + 1), 10, 3, COLOR_RED, COLOR_BRIGHT_WHITE, "OK", TEXT_CENTER);
				if (i > 0) i--;
			}
			else if (c == DOWN && yPointer != y + 2 * (number + 1))
			{
				yPointer += 2;
				if (i < 5) i++;
			}
			c = char();
			break;
		}

		case ESC:
		{
			setBackgroundColor(COLOR_BLACK);
			clearConsole();
			menu(false);
			break;
		}

		case ENTER:
		{
			if (i == number) {
				box(xPointer, y + height - 6, widthInput, 5, COLOR_RED, COLOR_LIGHT_YELLOW, "", TEXT_CENTER);

				string e1 = checkFromDate(startDateString);
				string e2 = checkToDate(endDateString);
				string e3 = "";
				if (e1.empty() && e2.empty()) {
					e3 = checkDateToDate(startDateString, endDateString);
				}

				int iy = y + height - 6;
				setTextColor(COLOR_BRIGHT_WHITE);
				if (!e1.empty()) { gotoXY(xPointer + 1, iy); cout << e1; iy += 1; }
				if (!e2.empty()) { gotoXY(xPointer + 1, iy); cout << e2; iy += 1; }
				if (!e3.empty()) { gotoXY(xPointer + 1, iy); cout << e3; iy += 1; }
				if (e1.empty() && e2.empty() && e3.empty()) {
					Date fromDate = stringToDate(startDateString);
					Date toDate = stringToDate(endDateString);

					//DANH SACH THONG KE HOA DON
					StatList statList;
					for (int i = 0; i < employeeList.number; i++) {

						//LAY DANH SACH HOA DON CUA TUNG NHAN VIEN
						InvoiceList list = employeeList.employee[i]->invoiceList;

						//DUYET DANH SACH HOA DON DO
						for (NodeInvoice* p = list; p != NULL; p = p->pNext) {
							Date d = p->invoice.date;

							//KIEM TRA NGAY LAP HOA DON CO NAM TRONG KHOANG KHONG
							if (isDateAfterOrSame(d, fromDate) && isDateBeforeOrSame(d, toDate))
							{
								statList.nodes[statList.number] = new Stat;
								statList.nodes[statList.number]->index = i;
								statList.nodes[statList.number]->nodeInvoice = p;

								double money = 0;
								InvoiceDetailList invoiceDetailList = p->invoice.invoiceDetailList;

								//DUYET DANH SACH CHI TIET HOA DON CUA HOA DON DO
								for (int j = 0; j < invoiceDetailList.number; j++)
								{
									InvoiceDetail invoiceDetail = invoiceDetailList.invoiceDetail[j];
									money += (double)invoiceDetail.quantity * invoiceDetail.price + (invoiceDetail.price * invoiceDetail.quantity * invoiceDetail.VAT / 100);
								}
								statList.nodes[statList.number]->money = money;
								statList.number++;
							}
						}
					}

					for (int i = 0; i < statList.number - 1; i++) {
						for (int j = 0; j < statList.number - i - 1; j++) {
							Date d1 = statList.nodes[j]->nodeInvoice->invoice.date;
							Date d2 = statList.nodes[j + 1]->nodeInvoice->invoice.date;

							if (isDateAfterOrSame(d1, d2)) {
								swap(statList.nodes[j], statList.nodes[j + 1]);
							}
						}
					}

					clearConsole();
					int k = statisticialTable(statList, employeeList, fromDate, toDate);
					if (k == 1) {
						clearConsole();
						statisticialPopUp(employeeList);
					}
					c = ESC; i--;
				}
			}
			else {
				continue;
			}
			break;
		}

		default:
		{
			if (i == 0) upperCaseWhileTyping(xPointer, yPointer, startDateString, c);
			else if (i == 1) upperCaseWhileTyping(xPointer, yPointer, endDateString, c);
			break;
		}

		}
	}
}



//=================== TOP 10 VAT TU CO DOANH THU CAO ===================
int salesTable(ProductList& productList, SalesList& salesList, Date& fromDate, Date& toDate) {
	ShowCur(0);
	string text1 = "BANG LIET KE 10 VAT TU CO DOANH THU CAO NHAT TRONG KHOANG THOI GIAN";
	string text2 = "TU NGAY: " + dateToString(fromDate) + "  DEN NGAY: " + dateToString(toDate);
	gotoXY(getCenterX(WIDTH_MAIN_FRAME, text1.length()), 2);
	cout << text1;
	gotoXY(getCenterX(WIDTH_MAIN_FRAME, text2.length()), 3);
	cout << text2;

	int width = 20;
	int height = 2;
	int x = getCenterX(WIDTH_MAIN_FRAME, width * 6);
	int y = getCenterY(HEIGHT_MAIN_FRAME, height * 14);
	int backgroundColor = COLOR_WHITE; // chinh mau vien table
	int textColor = COLOR_RED;
	setBackgroundColor(0);
	setTextColor(COLOR_WHITE);

	int row = 10;
	const int column = 4;
	string title[column] = { "HANG", "MA VAT TU", "TEN VAT TU", "DOANH THU" };
	int cellWidth[column] = { 10, 30, 40, 40 };

	int iy = y + 2;

	for (int k = 0; k < row; k++) {
		int ix = x;
		for (int j = 0; j < column; j++) {
			box3(ix, iy, cellWidth[j], height, backgroundColor, textColor, "");
			ix += cellWidth[j];
		}
		iy = iy + 2;
	}
	tableHeader(x, y, cellWidth, column, backgroundColor, textColor, title);
	tableFooter(x, iy + 1, cellWidth, column, backgroundColor, textColor, "");

	int keyBoxWidth = hotKeyBox(x + 1, iy + 2, "ESC", "QUAY LAI"); keyBoxWidth += 5;


	int xPointer = x + 1;
	int yPointer = y + 3;
	int xPointerOld = xPointer;
	int yPointerOld = yPointer;
	int i = 0;
	int iOld = i;
	bool isLeftRight = true;
	bool isFromUp = false;

	while (true) {
		if (isLeftRight) {
			setTextColor(COLOR_BRIGHT_WHITE);
			setBackgroundColor(COLOR_BLACK);
			int iy = y + 3;
			for (int k = 0; k < row; k++) {
				int ix = xPointer;
				for (int j = 0; j < column; j++) {
					gotoXY(ix, iy);
					cout << generateSpace(cellWidth[j]);
					ix += cellWidth[j];
				}
				iy = iy + 2;
			}

			if (salesList.number != 0)
			{
				int ix;
				iy = y + 3;
				for (int k = 0; k < row; k++) {
					if (k >= salesList.number) break;
					else {
						ix = xPointer;

						coutBox(ix, iy, cellWidth[0], TEXT_RIGHT, to_string(k + 1));
						ix += cellWidth[0];

						coutBox(ix, iy, cellWidth[1], TEXT_LEFT, salesList.nodes[k].nodeProduct->product.productId);
						ix += cellWidth[1];

						coutBox(ix, iy, cellWidth[2], TEXT_LEFT, salesList.nodes[k].nodeProduct->product.productName);
						ix += cellWidth[2];

						coutBox(ix, iy, cellWidth[3], TEXT_RIGHT, doubleToCurrency(salesList.nodes[k].money));
						ix += cellWidth[3];
					}
					iy = iy + 2;
				}
			}

			i = 0;
			iOld = i;
			yPointer = y + 3;
			yPointerOld = yPointer;
			if (isFromUp) {
				yPointer = y + 3 + 2 * (row - 1);
				yPointerOld = yPointer;
				i = row - 1;
				iOld = i;
				isFromUp = false;
			}
			isLeftRight = false;
		}

		char key = _getch();
		switch (key)
		{
		case -32:
		{
			if (key == LEFT) {}
			else if (key == RIGHT) {}
			else if (key == UP) {}
			else if (key == DOWN) {}
			break;
		}
		case ESC:
		{
			delete[] salesList.nodes;
			return 1;
			break;
		}
		default:
			break;
		}
	}
}

void salesPopUp(ProductList& productList, EmployeeList& employeeList) {
	ShowCur(1);
	int height = HEIGHT_POP_UP;
	int width = WIDTH_POP_UP;
	int x = getCenterX(WIDTH_MAIN_FRAME, width);
	int y = getCenterY(HEIGHT_MAIN_FRAME, height);
	int xInput = x + 22;
	int widthInput = 36;
	const int number = 2;

	/*string fromDateString = "01/01/2000";
	string toDateString = "31/12/2000";*/

	string fromDateString = "";
	string toDateString = "";
	string title[number] = { "NGAY BAT DAU", "NGAY KET THUC" };

	//ve bang pop up
	box(x, y, width, height, COLOR_WHITE, COLOR_BLACK, "", TEXT_CENTER);
	box(x, y, width, 1, COLOR_RED, COLOR_BRIGHT_WHITE, "TOP 10 VAT TU CO DOANH THU CAO NHAT", TEXT_CENTER);
	box(x, y + height, width, 1, COLOR_RED, COLOR_BRIGHT_WHITE, "", TEXT_CENTER);
	gotoXY(x + 1, y + height);
	cout << "ESC : MENU";

	for (int i = 0; i <= number; i++) {
		if (i == number) {
			box(xInput, y + 2 * (i + 1), 10, 3, COLOR_RED, COLOR_BRIGHT_WHITE, "OK", TEXT_CENTER);
		}
		else {
			gotoXY(x + 2, y + 2 * (i + 1));
			setBackgroundColor(COLOR_WHITE);
			setTextColor(COLOR_BLACK);
			cout << title[i];
			box(xInput, y + 2 * (i + 1), widthInput, 1, COLOR_BLACK, COLOR_LIGHT_YELLOW, "", TEXT_CENTER);
		}
	}

	int xPointer = xInput;
	int yPointer = y + 2;
	int xPointerOld = xPointer;
	int yPointerOld = yPointer;
	int backgroundColorChoose = 7;
	int i = 0;
	bool isClicked = true;
	char c = char();

	while (true)
	{
		if (isClicked)
		{
			ShowCur(1);
			if (i == number) {
				ShowCur(0);
				box(xPointer, y + 2 * (number + 1), 10, 3, COLOR_LIGHT_YELLOW, COLOR_BLACK, "OK", TEXT_CENTER);
			};
			if (i == 0) upperCaseWhileTyping(xPointer, yPointer, fromDateString, c);
			isClicked = false;
		}
		if (i == number) c = _getch();

		switch (c)
		{
		case -32:
			isClicked = true;
			c = _getch();
			if (c == UP && yPointer != y + 2)
			{
				yPointer -= 2;
				if (i == number) box(xPointer, y + 2 * (number + 1), 10, 3, COLOR_RED, COLOR_BRIGHT_WHITE, "OK", TEXT_CENTER);
				if (i > 0) i--;
			}
			else if (c == DOWN && yPointer != y + 2 * (number + 1))
			{
				yPointer += 2;
				if (i < 5) i++;
			}
			c = char();
			break;

		case ESC:
		{
			setBackgroundColor(COLOR_BLACK);
			clearConsole();
			menu(false);
			break;
		}

		case ENTER:
		{
			if (i == number) {
				box(xPointer, y + height - 6, widthInput, 5, COLOR_RED, COLOR_LIGHT_YELLOW, "", TEXT_CENTER);

				string e1 = checkFromDate(fromDateString);
				string e2 = checkToDate(toDateString);
				string e3 = "";
				if (e1.empty() && e2.empty()) {
					e3 = checkDateToDate(fromDateString, toDateString);
				}

				int iy = y + height - 6;
				setTextColor(COLOR_BRIGHT_WHITE);
				if (!e1.empty()) { gotoXY(xPointer + 1, iy); cout << e1; iy += 1; }
				if (!e2.empty()) { gotoXY(xPointer + 1, iy); cout << e2; iy += 1; }
				if (!e3.empty()) { gotoXY(xPointer + 1, iy); cout << e3; iy += 1; }
				if (e1.empty() && e2.empty() && e3.empty()) {
					Date fromDate = stringToDate(trim(fromDateString));
					Date toDate = stringToDate(trim(toDateString));

					SalesList salesList = sortProductHasMostSales(productList, employeeList, fromDate, toDate);
					clearConsole();
					int k = salesTable(productList, salesList, fromDate, toDate);
					if (k == 1) {
						clearConsole();
						salesPopUp(productList, employeeList);
					}
					//c = ESC; i--;
				}
			}
			else {
				continue;
			}
			break;
		}

		default:
		{
			if (i == 0) upperCaseWhileTyping(xPointer, yPointer, fromDateString, c);
			else if (i == 1) upperCaseWhileTyping(xPointer, yPointer, toDateString, c);
			break;
		}
		}
	}
}


EmployeeList employeeList;
ProductList productList;

void menu(boolean isInit) {
	ShowCur(0);
	int x = 2, y = 6, width = 40, height = 3;
	int textColor = 0;
	int backgroundColor = 14;
	int backgroundColorChoose = 15;

	if (isInit) {
		readEmployeeFile(employeeList);

		initProductList(productList);
		readProductFile(productList);
	}

	const int number = 7;
	string options[number] = {
		"1. QUAN LY VAT TU",
		"2. QUAN LY NHAN VIEN",
		"3. LAP HOA DON",
		"4. IN HOA DON",
		"5. THONG KE HOA DON",
		"6. IN VAT TU CO DOANH THU CAO NHAT",
		"7. THOAT CHUONG TRINH",
	};

	n_box(x, y, width, height, backgroundColor, textColor, options, number);

	int xPointer = x;
	int yPointer = y;
	int xPointerOld = xPointer;
	int yPointerOld = yPointer;
	int i = 0;
	int iOld = i;
	bool isClicked = true;
	bool flag = true;

	while (flag)
	{
		if (isClicked)
		{
			box(xPointerOld, yPointerOld, width, height, backgroundColor, textColor, options[iOld], TEXT_CENTER);
			box(xPointer, yPointer, width, height, backgroundColorChoose, textColor, options[i], TEXT_CENTER);
			xPointerOld = xPointer;
			yPointerOld = yPointer;
			isClicked = false;
		}

		char c = _getch();
		if (c == ENTER) {
			if (i == 0) { //QUAN LY VAT TU
				setBackgroundColor(COLOR_BLACK);

				NodeIndexList sortedProductList;
				productListToProductIndexList(productList, sortedProductList);
				sortProductListByName(sortedProductList);

				clearConsole();
				productTable(productList, sortedProductList, false);
			}
			else if (i == 1) { //QUAN LY NHAN VIEN
				setBackgroundColor(COLOR_BLACK);

				IndexList sortedEmployeeList;
				employeeListToEmployeeIndexList(employeeList, sortedEmployeeList);
				sortEmployeeListByName(sortedEmployeeList);

				clearConsole();
				employeeTable(employeeList, sortedEmployeeList, false);
			}

			else if (i == 2) { //TAO HOA DON MOI
				Invoice invoice;
				setBackgroundColor(COLOR_BLACK);
				clearConsole();
				InvoiceDetailList invoiceDetailList;
				addInvoicePopUp(productList, employeeList, -1);
			}

			else if (i == 3) { //IN HOA DON
				setBackgroundColor(COLOR_BLACK);
				clearConsole();
				invoicePopUp(productList, employeeList);
			}

			else if (i == 4) { //THONG KE HOA DON
				setBackgroundColor(COLOR_BLACK);
				clearConsole();
				statisticialPopUp(employeeList);
			}

			else if (i == 5) { //TOP DOANH THU
				setBackgroundColor(COLOR_BLACK);
				clearConsole();
				salesPopUp(productList, employeeList);
			}

			else if (i == 6) { //THOAT CHUONG TRINH
				clearConsole();
				setBackgroundColor(COLOR_BLACK);
				setTextColor(COLOR_BRIGHT_WHITE);
				for (int i = 0; i < employeeList.number; i++) {
					delete employeeList.employee[i];
				}
				exit(0);
			}
		}
		else if (c == -32)
		{
			c = _getch();
			if (c == UP && i != 0)
			{
				yPointer -= 4;
				if (i > 0)
				{
					iOld = i;
					i--;
				}
				isClicked = true;
			}
			else if (c == DOWN && i != (number - 1))
			{
				yPointer += 4;
				if (i < number)
				{
					iOld = i;
					i++;

				}
				isClicked = true;
			}
		}

	}
}
