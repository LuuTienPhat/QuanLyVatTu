#pragma once
#include <iostream>
#include <string>
#include "Struct.h"
#include <cctype>
#include <ctime>
#include "Windows.h"
using namespace std;

//KIEM TRA NAM NHUAN
bool isLeap(int year)
{
	// Return true if year
	// is a multiple pf 4 and
	// not multiple of 100.
	// OR year is multiple of 400.
	return (((year % 4 == 0) &&
		(year % 100 != 0)) ||
		(year % 400 == 0));
}

//KIEM TRA NGAY THANG NAM CO HOP LE HAY KHONG
bool isValidDate(int day, int month, int year)
{
	const int MAX_VALID_YR = 9999;
	const int MIN_VALID_YR = 1800;
	// If year, month and day
	// are not in given range
	if (year > MAX_VALID_YR ||
		year < MIN_VALID_YR)
		return false;
	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > 31)
		return false;

	// Handle February month
	// with leap year
	if (month == 2)
	{
		if (isLeap(year))
			return (day <= 29);
		else
			return (day <= 28);
	}

	// Months of April, June,
	// Sept and Nov must have
	// number of days less than
	// or equal to 30.
	if (month == 4 || month == 6 ||
		month == 9 || month == 11)
		return (day <= 30);

	return true;
}

//TAO DATE MOI
void newDate(Date& date, int day, int month, int year) {
	/*if (!isValidDate(day, month, year)) {
		return -1;
	}*/
	/*else {*/
	date.day = day;
	date.month = month;
	date.year = year;
	//}
	/*return 1;*/
}

//LAY THONG TIN NGAY THANG NAM HIEN TAI CHUYEN SANG CHUOI
string getDate() {
	SYSTEMTIME time;
	GetLocalTime(&time);
	string day = to_string(time.wDay);
	day = day.length() == 1 ? "0" + day : day;

	string month = to_string(time.wMonth);
	month = month.length() == 1 ? "0" + month : month;

	string year = to_string(time.wYear);

	return day + "/" + month + "/" + year;
}

//CHUYEN NGAY SANG CHUOI
string dateToString(Date& date) {
	string day = to_string(date.day);
	day = day.length() == 1 ? "0" + day : day;

	string month = to_string(date.month);
	month = month.length() == 1 ? "0" + month : month;

	string year = to_string(date.year);

	return day + "/" + month + "/" + year;
}

//CHUYEN CHUOI SANG NGAY
Date stringToDate(string date) {
	Date d;

	string day = date.substr(0, 2);
	string month = date.substr(3, 5);
	string year = date.substr(6, 10);

	d.day = stoi(day);
	d.month = stoi(month);
	d.year = stoi(year);

	return d;
}


//==================== KIEM TRA DU LIEU NHAP VAO ====================

//Kiem tra dinh dang ngay
string checkDate(string date) {
	if (date.empty()) return "NGAY THANG NAM khong duoc de trong";
	if (date.length() != 10) return "NGAY THANG NAM phai la dd/mm/yyyy";
	for (int i = 0; i < date.length(); i++) {
		if (!isdigit(date[i]) && date[i] != '/') {
			return "NGAY THANG NAM phai la dd/mm/yyyy";
		}
	}
	Date d = stringToDate(date);
	if (isValidDate(d.day, d.month, d.year)) return "";
	return "NGAY THANG NAM khong hop le";
}

//Kiem tra ngay bat dau
string checkFromDate(string date) {
	if (date.empty()) return "NGAY BAT DAU khong duoc de trong";
	if (date.length() != 10) return "NGAY BAT DAU phai la dd/mm/yyyy";
	for (int i = 0; i < date.length(); i++) {
		if (!isdigit(date[i]) && date[i] != '/') {
			return "NGAY BAT DAU phai la dd/mm/yyyy";
		}
	}

	Date d = stringToDate(date);
	if (isValidDate(d.day, d.month, d.year)) return "";
	return "NGAY BAT DAU khong hop le";
}

//Kiem tra ngay ket thuc
string checkToDate(string date) {
	if (date.empty()) return "NGAY KET THUC khong duoc de trong";
	if (date.length() != 10) return "NGAY KET THUC phai la dd/mm/yyyy";
	for (int i = 0; i < date.length(); i++) {
		if (!isdigit(date[i]) && date[i] != '/') {
			return "NGAY KET THUC phai la dd/mm/yyyy";
		}
	}

	Date d = stringToDate(date);
	if (isValidDate(d.day, d.month, d.year)) return "";
	return "NGAY KET THUC khong hop le";
}

//kiem tra ngay bat dau va ket thuc co hop le khong
string checkDateToDate(string fromDateString, string toDateString) {
	Date fromDate = stringToDate(fromDateString);
	Date toDate = stringToDate(toDateString);
	if (fromDate.year < toDate.year) {

	}
	else if (fromDate.year == toDate.year) {
		if (fromDate.month < toDate.month) {

		}
		else if (fromDate.month == toDate.month) {
			if (fromDate.day < toDate.day) {

			}
			else if (fromDate.day == toDate.day) {
				
			}
			else {
				return "NGAY BAT DAU <= NGAY KET THUC";
			}
		}
		else {
			return "NGAY BAT DAU <= NGAY KET THUC";
		}
	}
	else {
		return "NGAY BAT DAU <= NGAY KET THUC";
	}
	return "";
}

//kiem tra date1 co sau date2 khong
bool isDateAfterOrSame(Date &date1, Date &date2) {
	if (date1.year < date2.year) {
	}
	else if (date1.year == date2.year) {
		if (date1.month < date2.month) {
		}
		else if (date1.month == date2.month) {
			if (date1.day < date2.day) {
			}
			else if (date1.day == date2.day) {
				return true;
			}
			else {
				return true;
			}
		}
		else {
			return true;
		}
	}
	else {
		return true;
	}
	return false;
}

//kiem tra date1 co truoc date2 khong?
bool isDateBeforeOrSame(Date &date1, Date &date2) {
	if (date1.year < date2.year) {
	}
	else if (date1.year == date2.year) {
		if (date1.month < date2.month) {
		}
		else if (date1.month == date2.month) {
			if (date1.day < date2.day) {
			}
			else if (date1.day == date2.day) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	return true;
}

bool isDateAfter(Date& date1, Date& date2) {
	if (date1.year < date2.year) {
	}
	else if (date1.year == date2.year) {
		if (date1.month < date2.month) {
		}
		else if (date1.month == date2.month) {
			if (date1.day < date2.day) {
			}
			else if (date1.day == date2.day) {
				return false;
			}
			else {
				return true;
			}
		}
		else {
			return true;
		}
	}
	else {
		return true;
	}
	return false;
}