#include <iostream>
using namespace std;


struct IMS
{
	long prod_id;
	string prod_name;
	double prod_price;
	int prod_quantity;
	IMS *next;
};


IMS *CreateIMS(long id, string name, double price, int quantity) {
	IMS *newIMS = new IMS;
	newIMS->prod_id = id;
	newIMS->prod_name = name;
	newIMS->prod_price = price;
	newIMS->prod_quantity = quantity;
	newIMS->next = nullptr;
	return newIMS;
}


IMS *AddProd(IMS *Head) {
	long id;
	string name;
	double price;
	int quantity;


	cout << "Enter Product ID: ";
	cin >> id;
	cin.ignore();
	cout << "Enter Product Name: ";
	cout << "Enter Product Price: ";
	cin >> price;
	cout << "Enter Product Quantity: ";
	cin >> quantity;


	IMS *temp;
	if (Head == nullptr) {
		temp = CreateIMS(id, name, price, quantity);
		Head = temp;
		return Head;
	}
	temp = Head;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	temp->next = CreateIMS(id, name, price, quantity);
	return Head;
}


void Display(IMS *Head) {
	IMS *temp = Head;
	if (!temp) {
		cout << "Inventory is empty." << endl;
		return;
	}
	while (temp) {
		cout << temp->prod_id << " | " << temp->prod_name << " | $" << temp->prod_price << " | Quantity: " << temp->prod_quantity << endl;
		temp = temp->next;
	}
	cout << "END\n";
}


IMS *UpdateProd(IMS *Head, long id) {
	IMS *temp = Head;
	int c;
	int qu;
	double pr;
	bool found = false;


	while (temp) {
		if (temp->prod_id == id) {
			found = true;
			cout << "1. Update Price \n2. Update Quantity\nEnter choice: ";
			cin >> c;
			switch (c) {
			case 1:
				cout << "Enter the updated price: ";
				cin >> pr;
				temp->prod_price = pr;
				cout << "Price updated.\n";
				break;
			case 2:
				cout << "Enter the updated quantity: ";
				cin >> qu;
				temp->prod_quantity = qu;
				cout << "Quantity updated.\n";
				break;
			default:
				cout << "Invalid input.\n";
				break;
			}
			break;
		}
		temp = temp->next;
	}
	if (!found) {
		cout << "Product with the entered ID was not found.\n";
	}
	return Head;
}


IMS *DeleteProd(IMS *Head, long id) {
	if (!Head) {
		cout << "Inventory is Empty.\n";
		return Head;
	}
	if (Head->prod_id == id) {
		IMS *toDelete = Head;
		Head = Head->next;
		delete toDelete;
		cout << "Product deleted successfully.\n";
		return Head;
	}
	IMS *temp = Head;
	while (temp->next) {
		if (temp->next->prod_id == id) {
			IMS *toDelete = temp->next;
			temp->next = temp->next->next;
			delete toDelete;
			cout << "Product deleted successfully.\n";
			return Head;
		}
		temp = temp->next;
	}
	cout << "Product with the entered ID was not found.\n";
	return Head;
}


long TotalVal(IMS *Head) {
	long total = 0.0;


	IMS *temp = Head;
	while (temp) {
		total += (temp->prod_price * temp->prod_quantity);
		temp = temp->next;
	}
	cout << "Total valuation is: $" << total << endl;
	return total;
}


int main() {
	int choice;
	long id;
	IMS *Head = nullptr;


	while (true) {
		cout << "\nMenu:\n1. Add Product\n2. Display Products\n3. Update Product\n4. Delete Product\n5. Total Valuation\n6. Exit\nEnter choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			Head = AddProd(Head);
			break;


		case 2:
			Display(Head);
			break;


		case 3:
			cout << "Enter Product ID to update: ";
			cin >> id;
			Head = UpdateProd(Head, id);
			break;


		case 4:
			cout << "Enter Product ID to delete: ";
			cin >> id;
			Head = DeleteProd(Head, id);
			break;


		case 5:
			TotalVal(Head);
			break;


		case 6:
			cout << "Exiting......" << endl;
			return 0;


		default:
			cout << "Invalid input. Please try again.\n";
			break;
		}
	}
}
