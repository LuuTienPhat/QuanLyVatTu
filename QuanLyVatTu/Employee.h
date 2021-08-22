#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include "mylib.h"
#include <cctype>
#include <cstdlib>
#include <ctime>
#include "Struct.h"
#include "Invoice.h"
using namespace std;


//==================== THEM/SUA/XOA NHAN VIEN ====================

//KHOI TAO DANH SACH NHAN VIEN
void initEmployeeList(EmployeeList& employeeList) {
	employeeList.number = 0;
}

//KIEM TRA DANH SACH NHAN VIEN DAY
bool isEmployeeListFull(EmployeeList& employeeList) {
	return employeeList.number == MAX_EMPLOYEE ? true : false;
}

//KIEM TRA DANH SACH NHAN VIEN RONG
bool isEmployeeListEmpty(EmployeeList& employeeList) {
	return employeeList.number == 0 ? true : false;
}

//KHOI TAO NHAN VIEN MOI
void newEmployee(Employee& employee, string emloyeeId, string firstname, string lastname, string gender) {
	employee.employeeId = emloyeeId;
	employee.firstname = firstname;
	employee.lastname = lastname;
	employee.gender = gender;
	employee.invoiceList = initInvoiceList();
}

//TIM KIEM NHAN VIEN
int searchEmployee(EmployeeList& employeeList, string employeeId) {
	for (int i = 0; i < employeeList.number; i++) {
		if (employeeList.employee[i]->employeeId.compare(employeeId) == 0) return i;
	}
	return -1;
}

//THEM NHAN VIEN
void insertEmployeeListOrder(EmployeeList& employeeList, Employee& employee) {
	int i, j;
	//TIM KIEM VI TRI SE THEM VAO
	for (i = 0; i < employeeList.number && employeeList.employee[i]->employeeId.compare(employee.employeeId) < 0; i++);
	
	//TINH TIEN TU VI TRI THU I DO
	for (j = employeeList.number - 1; j >= i; j--) {
		employeeList.employee[j + 1] = employeeList.employee[j];
	}

	//TAO NHAN VIEN MOI VA THEM VAO VI TRI DO
	employeeList.employee[i] = new Employee;
	*employeeList.employee[i] = employee;
	employeeList.number++;
}

//XOA NHAN VIEN
void deleteEmployee(EmployeeList& employeeList, string employeeId) {
	int i = searchEmployee(employeeList, employeeId);
	delete employeeList.employee[i];
	for (int k = i; k < employeeList.number - 1; k++) {
		employeeList.employee[k] = employeeList.employee[k + 1];
	}
	employeeList.number--;
}

// KIEM TRA NHAN VIEN CO DANH SACH HOA DON HAY CHUA
bool isEmployeeHasInvoiceList(Employee& employee) {
	return !isInvoiceListEmpty(employee.invoiceList);
}

//SAP XEP DANH SACH NHAN VIEN THEO MA NHAN VIEN
void sortEmployeeListByEmployeeId(EmployeeList& employeeList) {
	int i, j;
	bool flag;
	for (i = 0; i < employeeList.number - 1; i++) {
		flag = false;
		for (j = 0; j < employeeList.number - i - 1; j++) {
			if (employeeList.employee[j]->employeeId.compare(employeeList.employee[j + 1]->employeeId) > 0) {
				swap(employeeList.employee[j], employeeList.employee[j + 1]);
				flag = true;
			}
		}
		if (!flag) break;
	}
}

//==================== KIEM TRA DU LIEU NHAP VAO ====================

//TAO MA NHAN VIEN
string generateEmployeeId(EmployeeList& employeeList) {
	string employeeId = "NVxxx";
	do
	{
		srand(time(NULL));
		for (int i = 2; i < employeeId.length(); i++) {
			employeeId[i] = rand() % (57 - 48 + 1) + 48;
		}
	} while (searchEmployee(employeeList, employeeId) != -1);

	return employeeId;
}

//KIEM TRA MA NHAN VIEN
string checkEmployeeId(EmployeeList& employeeList, string employeeId) {
	if (employeeId.empty()) return "MA NHAN VIEN khong duoc de trong";
	if (employeeId.length() > 5) return "MA NHAN VIEN khong duoc qua 5 ki tu ";

	int s = searchEmployee(employeeList, employeeId);
	if (s != -1) return "MA NHAN VIEN da ton tai";
	else return "";
}

//KIEM TRA MANV KHONG TON TAI
string checkNotEmployeeId(EmployeeList& employeeList, string employeeId) {
	if (employeeId.empty()) return "MANV khong duoc de trong";
	int s = searchEmployee(employeeList, employeeId);
	if (s != -1) return "";
	else return "MANV khong ton tai";
}

//KIEM TRA HO
string checkLastName(string lastname) {
	if (lastname.empty()) return "HO khong duoc de trong";
	for (int i = 0; i < lastname.length(); i++) {
		if (isdigit(lastname[i])) {
			return "HO khong duoc chua ki tu so";
		}
	}
	return "";
}

//KIEM TRA TEN
string checkFirstname(string firstname) {
	if (firstname.empty()) return "TEN khong duoc de trong";
	for (int i = 0; i < firstname.length(); i++) {
		if (firstname[i] == 32 && isalpha(firstname[i + 1])) {
			return "TEN chi duoc dien 1 tu";
		}
		else if (isdigit(firstname[i])) {
			return "TEN khong duoc chua ki tu so";
		}
	}
	return "";
}

//KIEM TRA GIOI TINH
string checkGender(string gender) {
	string male = "NAM";
	string female = "NU";

	if (gender.empty()) return "PHAI khong duoc de trong";
	if (gender.compare(male) != 0 && gender.compare(female) != 0) {
		return "PHAI chi la NAM hoac NU";
	}
	return "";
}


//==================== DANH SACH NHAN VIEN THEO TEN ====================

//KIEM TRA XEM DANH SACH NHAN VIEN THEO CO RONG KHONG
bool isSortedEmployeeListEmpty(IndexList& sortedEmployeeList) {
	return sortedEmployeeList.number == 0 ? true : false;
}

//SAP XEP NHAN VIEN THEO TEN
void sortEmployeeListByName(IndexList& sortedEmployeeList)
{
	int i, j;
	for (i = 0; i < sortedEmployeeList.number - 1; i++) {
		for (j = 0; j < sortedEmployeeList.number - i - 1; j++) {
			//OLD CODE
			/*if (sortedEmployeeList.nodes[j].firstname.compare(sortedEmployeeList.nodes[j + 1].firstname) > 0) {
				swap(sortedEmployeeList.nodes[j], sortedEmployeeList.nodes[j + 1]);
			}
			else if (sortedEmployeeList.nodes[j].firstname.compare(sortedEmployeeList.nodes[j + 1].firstname) == 0) {
				if (sortedEmployeeList.nodes[j].lastname.compare(sortedEmployeeList.nodes[j + 1].lastname) > 0) {
					swap(sortedEmployeeList.nodes[j], sortedEmployeeList.nodes[j + 1]);
				}
				else if (sortedEmployeeList.nodes[j].lastname.compare(sortedEmployeeList.nodes[j + 1].lastname) == 0) {
					if (sortedEmployeeList.nodes[j].index > (sortedEmployeeList.nodes[j + 1].index)) {
						swap(sortedEmployeeList.nodes[j], sortedEmployeeList.nodes[j + 1]);
					}
				}
			}*/

			//CODE THAY DOI THEO THAY GOP Y
			string employee1 = sortedEmployeeList.nodes[j].firstname + sortedEmployeeList.nodes[j].lastname + to_string(sortedEmployeeList.nodes[j].index);
			string employee2 = sortedEmployeeList.nodes[j + 1].firstname + sortedEmployeeList.nodes[j + 1].lastname + to_string(sortedEmployeeList.nodes[j + 1].index);

			if (employee1.compare(employee2) > 0) swap(sortedEmployeeList.nodes[j], sortedEmployeeList.nodes[j + 1]);
		}
	}
}

//CHUYEN TU DANH SACH NHAN VIEN SANG DANH SACH NHAN VIEN THEO TEN
void employeeListToEmployeeIndexList(EmployeeList& employeeList, IndexList& sortedEmployeeList)
{
	sortedEmployeeList.number = employeeList.number;
	sortedEmployeeList.nodes = new Index[employeeList.number];

	for (int i = 0; i < employeeList.number; i++) {
		sortedEmployeeList.nodes[i].index = i;
		sortedEmployeeList.nodes[i].firstname = employeeList.employee[i]->firstname;
		sortedEmployeeList.nodes[i].lastname = employeeList.employee[i]->lastname;
	}
}

//TIM KIEM DANH SACH NHAN VIEN THEO TEN
void searchEmployeeListByName(EmployeeList& employeeList, IndexList& sortedEmployeeList, string name) {
	sortedEmployeeList.number = 0;
	sortedEmployeeList.nodes = new Index[employeeList.number];
	
	for (int i = 0; i < employeeList.number; i++) {
		if (employeeList.employee[i]->firstname.find(name) != string::npos || employeeList.employee[i]->lastname.find(name) != string::npos) {
			sortedEmployeeList.nodes[sortedEmployeeList.number].index = i;
			sortedEmployeeList.nodes[sortedEmployeeList.number].firstname = employeeList.employee[i]->firstname;
			sortedEmployeeList.nodes[sortedEmployeeList.number].lastname = employeeList.employee[i]->lastname;
			sortedEmployeeList.number++;
		}
	}
	sortEmployeeListByName(sortedEmployeeList);
}