#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include "mylib.h"
#include <cctype>
#include <cstdlib>
#include "Struct.h"
#include "Date.h"
using namespace std;

bool is_number(string s)
{
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == 32 && isalpha(s[i + 1])) {
			return false;
		}
		else if (isalpha(s[i])) {
			return false;
		}
	}
}

//==================== QUAN LY VAT TU ====================

//KHOI TAO DANH SACH VAT TU
void initProductList(ProductList& productList) {
	productList = NULL;
}

//KIEM TRA DANH SACH VAT TU CO RONG HAY KHONG
bool isProductListEmpty(ProductList& productList) {
	return productList == NULL ? true : false;
}

//TIM VAT TU TRONG DANH SACH VAT TU
NodeProduct* searchProduct(ProductList& root, string productId) {
	if (isProductListEmpty(root)) {
		return NULL;
	}

	NodeProduct* q = root;
	while (q != NULL && productId.compare(q->product.productId) != 0)
		if (productId.compare(q->product.productId) < 0)
			q = q->pLeft;
		else if (productId.compare(q->product.productId) > 0)
			q = q->pRight;
	return q;
}

//TAO NODE VAT TU RONG
NodeProduct* newNode() {
	NodeProduct* p = new NodeProduct;
	Product product;
	p->product = product;
	p->pLeft = NULL;
	p->pRight = NULL;

	return p;
}

//TAO VAT TU MOI
void newProduct(Product& product, string productId, string productName, string unit, int quantity) {
	product.productId = productId;
	product.productName = productName;
	product.unit = unit;
	product.quantity = quantity;
	product.isUsed = false;
}

//THEM VAT TU
void insertProduct(ProductList& root, Product& product) {
	if (root == NULL) {
		NodeProduct* p = new NodeProduct;
		p->product = product;
		p->pLeft = NULL;
		p->pRight = NULL;

		root = p;
	}
	else {
		if (product.productId.compare(root->product.productId) < 0) {
			insertProduct(root->pLeft, product);
		}
		else if (product.productId.compare(root->product.productId) > 0) {
			insertProduct(root->pRight, product);
		}
	}
}

//XOA VAT TU
void findNodeForDelete(ProductList& X, ProductList& Y) {
	if (Y->pLeft != NULL) {
		findNodeForDelete(X, Y->pLeft);
	}
	else {
		X->product = Y->product;
		X = Y;
		Y = Y->pRight;
	}
}

void deleteProduct(ProductList& root, string productId) {
	if (productId.compare(root->product.productId) < 0) {
		deleteProduct(root->pLeft, productId);
	}
	else if (productId.compare(root->product.productId) > 0) {
		deleteProduct(root->pRight, productId);
	}
	else { //da tim ra phan tu can xoa
		NodeProduct* X = root;
		if (X->pLeft == NULL)
		{
			root = root->pRight;
		}
		else if (X->pRight == NULL)
		{
			root = root->pLeft;
		}
		else //node can xoa la node co 2 con
		{
			/*NodeProduct* Y = root->pRight;*/
			findNodeForDelete(X, root->pRight);
		}
		delete X; //xoa node can xoa bang cach giai phong vung nho
	}


}

//DEM VAT TU
void countProductNLR(ProductList& root, int& count) {
	if (root != NULL) {
		count++;
		countProductNLR(root->pLeft, count);
		countProductNLR(root->pRight, count);
	}
}

int countProduct(ProductList& root) {
	int count = 0;
	countProductNLR(root, count);
	return count;
}



//=================== KIEM TRA DU LIEU NHAP VAO VAT TU ===================

//KIEM TRA MA VAT TU
string checkProductId(ProductList& productList, string productId) {
	if (productId.empty()) return "MA VAT TU khong duoc de trong";
	if (productId.length() > 10) return "MA VAT TU toi da 10 ki tu";

	NodeProduct* p = searchProduct(productList, productId);
	if (p != NULL)  return "MA VAT TU da ton tai";
	return "";
}

//TAO MA VAT TU
string generateProductId(ProductList& productList) {
	string productId = "VTxxxxxxxx";
	do
	{
		srand(time(NULL));
		for (int i = 2; i < productId.length(); i++) {
			productId[i] = rand() % (57 - 48 + 1) + 48;
		}
	} while (searchProduct(productList, productId) != NULL);

	return productId;
}

//KIEM TRA TEN VAT TU
string checkProductName(string productName) {
	if (productName.empty()) return "TEN VAT TU khong duoc de trong";
	return "";
}

//KIEM TRA DON VI TINH
string checkUnit(string unit) {
	if (unit.empty()) return "DON VI khong duoc de trong";
	for (int i = 0; i < unit.length(); i++) {
		if (unit[i] == 32 && isalpha(unit[i + 1])) {
			return "DON VI chi duoc dien 1 tu";
		}
		else if (isdigit(unit[i])) {
			return "DON VI khong duoc chua ki tu so";
		}
	}
	return "";
}

//KIEM TRA SO LUONG TON
string checkQuantity(string quantity) {
	if (quantity.empty()) return "SO LUONG TON khong duoc de trong";
	if (!is_number(quantity)) return "SO LUONG TON phai la so";

	int q = stoi(quantity);
	if (q < 0) return "SO LUONG TON >= 0";

	return "";
}



//=================== DANH SACH SAP XEP HOA DON THEO TEN ===================

//KIEM TRA DANH SACH SAP XEP CO RONG KHONG
bool isSortedProductListEmpty(NodeIndexList& sortedProductList) {
	return sortedProductList.number == 0 ? true : false;
}

//SAP XEP DANH SACH VAT TU THEO TEN
void sortProductListByName(NodeIndexList& sortedProductList)
{
	int i, j;
	bool haveSwap = false;
	for (i = 0; i < sortedProductList.number - 1; i++) {
		haveSwap = false;
		for (j = 0; j < sortedProductList.number - i - 1; j++) {
			if (sortedProductList.nodes[j].nodeProduct->product.productName.compare(sortedProductList.nodes[j + 1].nodeProduct->product.productName) > 0) {
				swap(sortedProductList.nodes[j], sortedProductList.nodes[j + 1]);
				haveSwap = true;
			}
		}

		if (haveSwap == false) break;
	}
}

//TIM KIEM VAT TU THEO TEN
int searchSortedProductList(NodeIndexList& sortedProductList, string productName) {
	int i;
	for (i = 0; i < sortedProductList.number; i++) {
		if (productName.compare(sortedProductList.nodes[i].nodeProduct->product.productName) < 0) {
			return i;
		}
	}
	return -1;
}

//THEM VAO DANH SACH SAP XEP
void insertSortedProductList(NodeIndexList& sortedProductList, NodeProduct* nodeProduct) {
	int i;
	int j;
	for (i = 0; i < sortedProductList.number; i++) {
		if (nodeProduct->product.productName.compare(sortedProductList.nodes[i].nodeProduct->product.productName) < 0) {
			break;
		}
	}

	for (j = sortedProductList.number - 1; j >= i; j--) {
		sortedProductList.nodes[j + 1] = sortedProductList.nodes[j];
	}

	sortedProductList.nodes[i].nodeProduct = nodeProduct;
	sortedProductList.number++;
}

//XOA KHOI DANH SACH SAP XEP
void deleteFromSortedProductList(NodeIndexList& sortedProductList, string productName) {
	int i;
	int j;
	for (i = 0; i < sortedProductList.number; i++) {
		if (sortedProductList.nodes[i].nodeProduct->product.productName.compare(productName) == 0) {
			break;
		}
	}

	for (j = i; j < sortedProductList.number - 1; j++) {
		sortedProductList.nodes[j] = sortedProductList.nodes[j + 1];
	}
	sortedProductList.number--;
}

//CHUYEN CAY VAT TU THANH DANH SACH SAP XEP
void productListToProductIndexListLNR(ProductList& root, NodeIndexList& sortedProductList) {
	if (root != NULL) {
		productListToProductIndexListLNR(root->pLeft, sortedProductList);
		sortedProductList.nodes[sortedProductList.number].nodeProduct = root;
		sortedProductList.number++;
		productListToProductIndexListLNR(root->pRight, sortedProductList);
	}
}

void productListToProductIndexList(ProductList& root, NodeIndexList& sortedProductList) {

	int numberOfProduct = countProduct(root);
	sortedProductList.number = 0;
	sortedProductList.init = numberOfProduct + 10;
	sortedProductList.nodes = new NodeIndex[sortedProductList.init];

	productListToProductIndexListLNR(root, sortedProductList);
}

//TIM VAT TU THEO TEN
void searchProductListByNameNLR(ProductList& root, NodeIndexList& sortedProductList, string productName) {
	if (root != NULL) {
		if (root->product.productName.find(productName) != string::npos) {
			sortedProductList.nodes[sortedProductList.number].nodeProduct = root;
			sortedProductList.number++;
		}
		searchProductListByNameNLR(root->pLeft, sortedProductList, productName);
		searchProductListByNameNLR(root->pRight, sortedProductList, productName);
	}

}

void searchProductListByName(ProductList& productList, NodeIndexList& sortedProductList, string productName) {
	int numberOfProduct = countProduct(productList);
	sortedProductList.number = 0;
	sortedProductList.nodes = new NodeIndex[numberOfProduct];

	searchProductListByNameNLR(productList, sortedProductList, productName);

	sortProductListByName(sortedProductList);
};



//==================== THONG KE TOP DOANH THU ====================

//TIM KIEM VAT TU TRONG DANH SACH SALES
int searchSalesList(SalesList& salesList, string productId) {
	for (int i = 0; i < salesList.number; i++) {
		if (salesList.nodes[i].nodeProduct->product.productId.compare(productId) == 0) {
			return i;
		}
	}
	return -1;
}

//THONG KE TOP DOANH THU
SalesList sortProductHasMostSales(ProductList& productList, EmployeeList& employeeList, Date& fromDate, Date& toDate) {
	//DEM SO LUONG VAT TU
	const int numberOfProduct = countProduct(productList);

	//KHOI TAO DANH SACH SALES
	SalesList salesList;
	salesList.nodes = new Sales[numberOfProduct];


	//DUYET DANH SACH NHAN VIEN
	for (int i = 0; i < employeeList.number; i++) {
		InvoiceList invoiceList = employeeList.employee[i]->invoiceList;

		//DUYET DANH SACH HOA DON CUA MOI NHAN VIEN
		NodeInvoice* p;
		for (p = invoiceList; p != NULL; p = p->pNext) {
			Date d = p->invoice.date;
			char type = p->invoice.type;

			//SO SANH NGAY LAP HOA DON CO NAM TRONG KHOANG KHONG
			if (isDateAfterOrSame(d, fromDate) && isDateBeforeOrSame(d, toDate) && type == 'X')
			{
				//DUYET DANH SACH CHI TIET HOA DON CUA TUNG HOA DON
				InvoiceDetailList invoiceDetailList = p->invoice.invoiceDetailList;
				for (int j = 0; j < invoiceDetailList.number; j++)
				{
					InvoiceDetail invoiceDetail = invoiceDetailList.invoiceDetail[j];

					//TINH SO TIEN CUA TUNG VAT TU
					double money = (double)invoiceDetail.quantity * invoiceDetail.price + (invoiceDetail.price * invoiceDetail.quantity * invoiceDetail.VAT / 100);

					//TIM VAT TU TRONG DANH SACH SALES
					int k = searchSalesList(salesList, invoiceDetail.productId);

					//NEU VAT TU DA CO TRONG DANH SACH SALES THI CAP NHAT LAI SO TIEN
					if (k != -1) {
						salesList.nodes[k].money += money;
					}
					else { //NEU VAT TU CHUA TON TAI TRONG DANH SACH SALES THI THEM MOI
						NodeProduct* np = searchProduct(productList, invoiceDetail.productId);
						salesList.nodes[salesList.number].nodeProduct = np;
						//salesList.nodes[salesList.number].productId = invoiceDetail.productId;
						salesList.nodes[salesList.number].money = money;
						salesList.number++;
					}
				}
			}
		}
		delete p;
	}

	//SAP XEP DANH SACH SALES THEO DOANH THU GIAM DAN
	bool haveSwap = true;
	for (int i = 0; i < salesList.number - 1; i++) {
		for (int j = 0; j < salesList.number - i - 1; j++) {
			if (salesList.nodes[j].money < salesList.nodes[j + 1].money) {
				swap(salesList.nodes[j], salesList.nodes[j + 1]);
				haveSwap = true;
			}
		}
		if (haveSwap == false) break;
	}

	//TRA VE DANH SACH SALES
	return salesList;
}