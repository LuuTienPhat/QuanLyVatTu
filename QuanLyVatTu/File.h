#pragma once
#include <fstream>
#include "Product.h"
#include "Employee.h"
#include <iomanip>
using namespace std;


//=================== GHI FILE NHAN VIEN ===================
void writeEmployeeFile(EmployeeList& employeeList) {
	fstream fileEmployeeOut;
	fileEmployeeOut.open("Employee3.txt", ios_base::out);
	fstream fileInvoiceOut;
	fileInvoiceOut.open("Invoice3.txt", ios_base::out);
	fstream fileInvoiceDetailOut;
	fileInvoiceDetailOut.open("InvoiceDetail3.txt", ios_base::out);

	int fileInvoicePointer = 0;
	int fileInvoiceDetailPointer = 0;

	if (fileEmployeeOut.fail()) return;
	for (int i = 0; i < employeeList.number; i++) 
	{
		Employee employee = *employeeList.employee[i];

		fileEmployeeOut << employee.employeeId << "|";
		fileEmployeeOut << employee.lastname << "|";
		fileEmployeeOut << employee.firstname << "|";
		fileEmployeeOut << employee.gender << "|";

		int numberOfInvoice = countInvoice(employee.invoiceList);
		fileEmployeeOut << numberOfInvoice << "|";

		//=================== GHI FILE HOA DON ===================
		for (NodeInvoice* p = employee.invoiceList; p != NULL; p = p->pNext) 
		{
			fileInvoiceOut << employee.employeeId << "|";
			fileInvoiceOut << p->invoice.invoiceNumber << "|";
			fileInvoiceOut << p->invoice.date.day << "|";
			fileInvoiceOut << p->invoice.date.month << "|";
			fileInvoiceOut << p->invoice.date.year << "|";
			fileInvoiceOut << p->invoice.type << "|";
			fileInvoiceOut << p->invoice.invoiceDetailList.number << "|";
			fileInvoiceOut << endl;

			//=================== GHI FILE CHI TIET HOA DON ===================
			InvoiceDetailList invoiceDetailList = p->invoice.invoiceDetailList;
			for (int i = 0; i < invoiceDetailList.number; i++) 
			{
				fileInvoiceDetailOut << p->invoice.invoiceNumber << "|";
				fileInvoiceDetailOut << invoiceDetailList.invoiceDetail[i].productId << "|";
				fileInvoiceDetailOut << invoiceDetailList.invoiceDetail[i].quantity << "|";

				fileInvoiceDetailOut << fixed << setprecision(2);
				fileInvoiceDetailOut << invoiceDetailList.invoiceDetail[i].price << "|";
				fileInvoiceDetailOut << invoiceDetailList.invoiceDetail[i].VAT << "|";

				fileInvoiceDetailOut << endl;
			}
		}

		if (i == employeeList.number - 1) break;
		fileEmployeeOut << endl;
	}

	fileEmployeeOut.close();
	fileInvoiceOut.close();
	fileInvoiceDetailOut.close();
}

//=================== GHI FILE NHAN VIEN KHONG GHI CAC FILE TRONG NO ===================
void writeOnlyEmployeeFile(EmployeeList& employeeList) {
	fstream fileEmployeeOut;
	fileEmployeeOut.open("Employee3.txt", ios_base::out);

	if (fileEmployeeOut.fail()) return;
	for (int i = 0; i < employeeList.number; i++) {
		Employee employee = *employeeList.employee[i];

		fileEmployeeOut << employee.employeeId << "|";
		fileEmployeeOut << employee.lastname << "|";
		fileEmployeeOut << employee.firstname << "|";
		fileEmployeeOut << employee.gender << "|";

		int numberOfInvoice = countInvoice(employee.invoiceList);
		fileEmployeeOut << numberOfInvoice << "|";

		if (i == employeeList.number - 1) break;
		fileEmployeeOut << endl;
	}
	fileEmployeeOut.close();
}


//=================== DOC FILE CHI TIET HOA DON ===================
void readInvoiceDetailFile(InvoiceDetailList &invoiceDetailList, ifstream& fileInvoiceDetailIn, int numberOfInvoiceDetail) {

	int count = 0;
	if (numberOfInvoiceDetail == count) return;
	while (fileInvoiceDetailIn.eof() != true)
	{
		string invoiceId;
		InvoiceDetail invoiceDetail;
		char c;

		getline(fileInvoiceDetailIn, invoiceId, '|');

		getline(fileInvoiceDetailIn, invoiceDetail.productId, '|');
		//getline(fileInvoiceDetailIn, invoiceDetail.productName, '|');
		fileInvoiceDetailIn >> invoiceDetail.quantity; fileInvoiceDetailIn >> c;
		fileInvoiceDetailIn >> invoiceDetail.price; fileInvoiceDetailIn >> c;
		fileInvoiceDetailIn >> invoiceDetail.VAT; fileInvoiceDetailIn >> c;

		insertInvoiceDetail(invoiceDetailList, invoiceDetail);
		fileInvoiceDetailIn.ignore();

		count++;
		if (count == numberOfInvoiceDetail) break;
	}
}

//=================== DOC FILE HOA DON ===================
void readInvoiceFile(Employee& employee, ifstream& fileInvoiceIn, ifstream& fileInvoiceDetailIn, int numberOfInvoice) {
	int count = 0;
	if (numberOfInvoice == count) return;
	while (fileInvoiceIn.eof() != true)
	{
		string numberOfInvoiceDetailString;
		string employeeId;
		Invoice invoice;
		Date date;
		char c;

		getline(fileInvoiceIn, employeeId, '|');
		
		getline(fileInvoiceIn, invoice.invoiceNumber, '|');
		fileInvoiceIn >> date.day; fileInvoiceIn >> c;
		fileInvoiceIn >> date.month; fileInvoiceIn >> c;
		fileInvoiceIn >> date.year; fileInvoiceIn >> c;
		invoice.date = date;
		fileInvoiceIn >> invoice.type;
		fileInvoiceIn >> c;
		initInvoiceDetailList(invoice.invoiceDetailList);

		getline(fileInvoiceIn, numberOfInvoiceDetailString, '|');
		int numberOfInvoiceDetail = stoi(numberOfInvoiceDetailString);
		readInvoiceDetailFile(invoice.invoiceDetailList, fileInvoiceDetailIn, numberOfInvoiceDetail);

		insertInvoice(employee.invoiceList, invoice);
		fileInvoiceIn.ignore();

		count++;
		if (count == numberOfInvoice) break;
	}
}

//=================== DOC FILE NHAN VIEN ===================
void readEmployeeFile(EmployeeList& employeelist) {
	ifstream fileIn;
	fileIn.open("Employee3.txt", ios_base::in);

	ifstream fileInvoiceIn;
	fileInvoiceIn.open("Invoice3.txt", ios_base::in);

	ifstream fileInvoiceDetailIn;
	fileInvoiceDetailIn.open("InvoiceDetail3.txt", ios_base::in);

	int fileInvoicePointer = 0;
	int fileInvoiceDetailPointer = 0;

	if (fileIn.fail()) return;
	if (fileIn.peek() == fstream::traits_type::eof()) {
		return;
	}
	while (fileIn.eof() != true)
	{
		string invoiceNumberString;
		Employee employee;

		getline(fileIn, employee.employeeId, '|');
		if (employee.employeeId.compare("") == 0) break;

		getline(fileIn, employee.lastname, '|');
		getline(fileIn, employee.firstname, '|');
		getline(fileIn, employee.gender, '|');
		employee.invoiceList = initInvoiceList();

		getline(fileIn, invoiceNumberString, '|');
		int invoiceNumber = stoi(invoiceNumberString);
		readInvoiceFile(employee, fileInvoiceIn, fileInvoiceDetailIn, invoiceNumber);

		insertEmployeeListOrder(employeelist, employee);
		fileIn.ignore();
	}
	fileIn.close();
	fileInvoiceIn.close();
	fileInvoiceDetailIn.close();
}


//=================== DOC FILE VAT TU ===================
void readProductFile(ProductList& productList)
{
	fstream FileIn;
	FileIn.open("Product2.txt", ios_base::in);
	if (FileIn.fail()) return;
	if (FileIn.peek() == fstream::traits_type::eof()) {
		return;
	}
	while (FileIn.eof() != true)
	{
		Product product;
		getline(FileIn, product.productId, '|');
		if (product.productId.compare("") == 0) break;

		getline(FileIn, product.productName, '|');
		getline(FileIn, product.unit, '|');

		string quantity = "";
		getline(FileIn, quantity, '|');
		product.quantity = stoi(quantity);

		string isUsed = "";
		getline(FileIn, isUsed, '|');
		if (isUsed.compare("0") == 0) product.isUsed = false;
		else product.isUsed = true;

		insertProduct(productList, product);

		FileIn.ignore();
	}
	FileIn.close();
}

//=================== GHI FILE VAT TU ===================
void writeProductFileNLR(ProductList& root, fstream& productFileOut) {
	if (root != NULL) {
		productFileOut << root->product.productId << "|";
		productFileOut << root->product.productName << "|";
		productFileOut << root->product.unit << "|";
		productFileOut << root->product.quantity << "|";
		productFileOut << root->product.isUsed << "|";
		productFileOut << endl;

		writeProductFileNLR(root->pLeft, productFileOut);
		writeProductFileNLR(root->pRight, productFileOut);
	}

}

void writeProductFile(ProductList& root) {
	fstream productFileOut;
	productFileOut.open("Product2.txt", ios_base::out);
	if (productFileOut.fail()) return;

	writeProductFileNLR(root, productFileOut);
	productFileOut.close();
}