#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
using namespace std;

void getch(){
	cout<<"* Press Enter *"<<flush;
	getchar();
	getchar();
}

void clrscr() {
	for (int i = 0; i < 80; ++i)
		cout << "\n";
	cout << endl;
}

class shop {
	int identifier;
	float price[100];
	int stock[100], i, di, ordr[100], ono, grosel;
	class date {
		int dat, year, month, mon;
	public:
		date() {
			dat = year = month = mon = 0;
		}
		void getdate() {
			cout << "Enter Date Month Year ";
			cin >> dat >> month >> year;
		}
		void showdate() {

			cout << dat << "/" << month << "/" << year;
		}

	} MFG[100], EXP[100];
	char name[100][100];
public:
	class cost {
	public:
		char add[100][100];
		char cname[100][100];
		char cpro[100][100];
		int chow[100], cstat[100];
		float cprice[100];
	} c1;
	void ShowDet() {
		int car;
		do {
			cout << "Enter Order Number ";
			cin >> car;
			if (car >= ono)
				cout << "Order Number Does Not Exists ";
		} while (car >= ono);
		cout << "Name Of Customer " << c1.cname[car];
		cout << endl;
		cout << "Name Of Product Bought " << c1.cpro[car];
		cout << endl;
		cout << "Address Of Customer " << c1.add[car];
		cout << endl;
		cout << "Number Of Products Brought " << c1.chow[car];
		cout << endl;
		cout << "Amount To Be Paid " << c1.cprice[car];
		cout << endl;
	}
	shop() {
		for (int s = 0; s < 100; s++)
			c1.cstat[s] = 0;
		identifier = i = di = ono = grosel = 0;
		memset(price, 0, sizeof(price));
		memset(stock, 0, sizeof(stock));
		memset(ordr, 0, sizeof(ordr));
	}
	void startl()					 //Ctor
	{
		char ch;
		ifstream fin("ShopMan"), fin1("ShopMan1"), fin2("Shopman2"), filin(
				"Shopman3");
		fin >> i >> di >> ono >> grosel;
		if (i > 100 || i < 0) {
			i = 0;
			grosel = 0;
			ono = 0;
		}
		for (int faltu = 0; faltu < i; faltu++) {
			fin1.get(ch);
			fin1.get(name[faltu], 100);
			fin1 >> price[faltu] >> stock[faltu] >> ordr[faltu];
			if (i > 100 || i < 0)
				ordr[faltu] = 0;
			filin.read((char *) &MFG[faltu], sizeof(MFG[faltu]));
			filin.read((char *) &EXP[faltu], sizeof(EXP[faltu]));
		}
		for (int faltu = 0; faltu < ono; faltu++) {
			fin2.get(c1.cname[faltu], 100);
			fin2.get(ch);
			fin2.get(c1.cpro[faltu], 100);
			fin2.get(ch);
			fin2.get(c1.add[faltu], 100);
			fin2 >> c1.chow[faltu] >> c1.cstat[faltu] >> c1.cprice[faltu];
		}
		fin.close();
	}
	void endp() {
		ofstream fout("ShopMan"), fout1("ShopMan1"), fout2("ShopMan2"), filin(
				"Shopman3");
		fout << i << endl << di << endl << ono << endl << grosel;
		for (int faltu = 0; faltu < i; faltu++) {
			fout1 << endl << name[faltu];
			fout1 << endl << price[faltu] << endl << stock[faltu] << endl
					<< ordr[faltu];
			filin.write((char *) &MFG[faltu], sizeof(MFG[faltu]));
			filin.write((char *) &EXP[faltu], sizeof(EXP[faltu]));
		}

		for (int faltu = 0; faltu < ono; faltu++) {
			fout2 << c1.cname[faltu] << endl << c1.cpro[faltu] << endl
					<< c1.add[faltu] << endl << c1.chow[faltu] << endl
					<< c1.cstat[faltu] << endl << c1.cprice[faltu];
		}
		cout
				<< "=======================================================================";
		cout << "\n\n\n\t\t\tThank You\n\n\n";
		cout
				<< "=======================================================================";
		fout.close();
	}
	void cartman() {
		int m, ch;
		if (i == 0) {
			cout << "Nothing To Manage ";
			getch();
			return;
		}
		cout << "\n1.Shipping Completed\n2.Cancel Order";
		cin >> ch;
		do {
			cout << "Enter Order Number ";
			cin >> m;
			if (m >= ono)
				cout << "Invalid Product Code ";
		} while (m >= ono);
		if (ch == 1)
			c1.cstat[m] = 1;
		if (ch == 2)
			c1.cstat[m] = 2;
	}

	void noneed() {
	}
	void book() {
		int m, x;
		do {
			cin >> m;
			if (stock[m] == 0 || i == 0) {
				cout << "Sorry!! You Don't Have Any Thing To Sell ";
				return;
				getch();
			}
			if (m >= i)
				cout << "Invalid Product Code ";
		} while (m >= i);
		cout << "No Of Product To Buy ";
		do {
			cin >> x;
			if (x > stock[m])
				cout << "Stock Not Available ";
		} while (x > stock[m]);
		stock[m] = stock[m] - x;
		ordr[m] = 1;
		cout << "Enter Your Name ";
		cin >> c1.cname[ono];
		cout << "Enter Address "<<flush;
		gets(c1.add[ono]);
		gets(c1.add[ono]);
		strcpy(c1.cpro[ono], name[m]);
		c1.chow[ono] = x;
		c1.cprice[ono] = price[m] * x;
		grosel = grosel + c1.cprice[ono];
		ono++;
	}
	void Sr() {
		int gml;
		if (ono == 0)
			cout << "\nNothing Is In Cart ";
		for (i = 0; i < ono; i++)
			if (c1.cstat[i] == 0) {
				cout << c1.cname[i] << "'s Order Is Not Complete " << "\n";
				gml = 0;
			}
		if (gml != 0)
			cout << "\nAll The Orders Are Complete ";
	}
	void ac() {
		if (ono == 0)
			return;
		int command, crm;
		do {
			cout << "\nEnter Order Number ";
			cin >> command;
			cout << "\nEnter Discount Rupees ";
			cin >> crm;
			if (ono <= command || crm > c1.cprice[command])
				cout << "Order Number Or Discount Price May Be Wrong ";
		} while (ono <= command || crm > c1.cprice[command]);
		c1.cprice[command] = c1.cprice[command] - crm;
		grosel = grosel - crm;

	}
	void dgs() {
		grosel = 0;
	}
	void get() {
		cout << endl;
		cout << "Enter Name Of Product "<<flush;
		gets(name[i]);
		gets(name[i]);
		cout << endl;
		cout << "Enter Price Of " << name[i] << " ";
		cin >> price[i];
		cout << endl;
		cout << "Enter Manufacturing Details : ";
		MFG[i].getdate();
		cout << endl;
		cout << "Enter Expiring Details : ";
		EXP[i].getdate();
		cout << endl;
		cout << "Enter Stock Available ";
		cin >> stock[i];
		cout << endl;
	}
	void shows() {
		cout
				<< "\n=======================================================================";
		cout << "\nProduct Code\t| Product Name\t| Stock Available";
		cout
				<< "\n=======================================================================";
		if (i >= 1)
			for (int demo = 0; demo <= (i - 1); demo++)
				cout << endl << demo << "\t\t| " << name[demo] << "\t\t| "
						<< stock[demo];
		cout
				<< "\n=======================================================================";
	}
	void cart() {
		cout
				<< "\n=======================================================================";
		cout
				<< "\nProduct Code \t| Name \t| Product Name\t| Product Brought\t| Amount";
		cout
				<< "\n=======================================================================";
		if (ono >= 1)
			for (int demo = 0; demo <= (ono - 1); demo++) {
				cout << endl << demo << "\t\t|" << c1.cname[demo] << "\t| "
						<< c1.cpro[demo] << "\t\t| " << c1.chow[demo]
						<< "\t\t| " << c1.cprice[demo];
				if (c1.cstat[demo] == 0)
					cout << endl << "\t\t\tIn Progress";
				if (c1.cstat[demo] == 1)
					cout << endl << "\t\t\tProduct Delivered";
				if (c1.cstat[demo] == 2)
					cout << endl << "\t\t\tCancelled";
			}
		cout
				<< "\n=======================================================================";
	}
	void GS() {
		cout << grosel;
	}
	void show();
	void Buy();
	void Del() {
		i = 0;
		ono = 0;
	}
};
void shop::show() {
	do {
		cout << "\nEnter Product Code ";
		cin >> di;
		if (di >= i)
			cout << "This Product Code Is Not Available \n";
	} while (di >= i);
	cout << "Name Of Product ";
	cout << name[di];
	cout << endl;
	cout << "Price Of " << name[di] << " ";
	cout << price[di];
	cout << endl;
	cout << "Manufacturing Details : ";
	MFG[di].showdate();
	cout << endl;
	cout << "Expiring Details : ";
	EXP[di].showdate();
	cout << endl;
	cout << "Stock Available ";
	cout << stock[di];
	cout << endl;
}
void shop::Buy() {
	get();
	++i;
}

int main() {
	getch();
	char end[30];
	ifstream dell("Main");
	if (!dell)
		return -1;
	dell.get(end, 30);
	shop s1;
	s1.startl();

	menu: clrscr();
	cout
			<< "=======================================================================";
	cout << "\n\n\n\t\t\tShop Management\n\n\n";
	cout
			<< "=======================================================================";
	int ch;
	cout << "\n1.Buy Product For Shop \n";
	cout << "2.Sell Product From Shop \n";
	cout
			<< "3.See Cart \n4.Manage Cart\n5.Add Coupon\n6.Gross Sell\n7.Delete\n8.Exit";
	cin >> ch;
	switch (ch) {
	case 1:
//		textcolor(53);
//		clrscr();
		clrscr();
		cout
				<< "=======================================================================";
		cout << "\n\n\n\t\t\tShop Management\n\n\n";
		cout
				<< "=======================================================================\n\n";
		s1.shows();
		do {
			cout << "\n1.Main Menu\n2.Add Product";
			cin >> ch;
			if (ch == 1)
				goto menu;
			if (ch == 2)
				s1.Buy();
			if (ch < 0 || ch > 3)
				cout << "\nSee The Instructions \n";
		} while (ch < 0 || ch > 3);
		getch();
		goto menu;
		break;
	case 2:
//		textcolor(52);
//		clrscr();
		clrscr();
		cout
				<< "=======================================================================";
		cout << "\n\n\n\t\t\tShop Management\n\n\n";
		cout
				<< "=======================================================================\n\n";
		s1.shows();
		do {
			cout << "\n1.Main Menu\n2.Detailed Info\n3.Sell Product";
			cin >> ch;
			if (ch == 1)
				goto menu;
			if (ch == 2)
				s1.show();
			if (ch == 3) {
				cout << "Enter Product Code";
				s1.book();
			}
			if (ch < 0 || ch > 3)
				cout << "\nSee The Instructions \n";
		} while (ch < 0 || ch > 3);
		getch();
		goto menu;
		break;
	case 3:
//		textcolor(637);
//		clrscr();
		clrscr();

		cout
				<< "=======================================================================";
		cout << "\n\n\n\t\t\tShop Management\n\n\n";
		cout
				<< "=======================================================================\n\n";

		s1.cart();
		cout << "\n\n1.Go to Main Menu\n2.Show Details";
		cin >> ch;
		if (ch == 1)
			goto menu;
		if (ch == 2)
			s1.ShowDet();
		getch();
		goto menu;
		break;
	case 4:
//		textcolor(46);
//		clrscr();
		clrscr();

		cout
				<< "=======================================================================";
		cout << "\n\n\n\t\t\tShop Management\n\n\n";
		cout
				<< "=======================================================================\n\n";

		s1.cart();
		cout << "\n1.Go To Main Menu \n2.Manage \n3.Show Incomplete Orders";
		cin >> ch;
		if (ch == 1)
			goto menu;
		if (ch == 2)
			s1.cartman();
		if (ch == 3)
			s1.Sr();
		getch();
		goto menu;
		break;
	case 6:
//		textcolor(27);
//		clrscr();
		clrscr();

		cout
				<< "=======================================================================";
		cout << "\n\n\n\t\t\tShop Management\n\n\n";
		cout
				<< "=======================================================================\n\n";

		cout << "Gross Sell Is ";
		s1.GS();
		getch();
		goto menu;
		break;
	case 5:
//		textcolor(19);
//		clrscr();
		clrscr();

		cout
				<< "=======================================================================";
		cout << "\n\n\n\t\t\tShop Management\n\n\n";
		cout
				<< "=======================================================================\n\n";

		s1.cart();
		s1.ac();
		getch();
		goto menu;
	case 7:
//		textcolor(10);
//		clrscr();
		clrscr();

		cout
				<< "=======================================================================";
		cout << "\n\n\n\t\t\tShop Management\n\n\n";
		cout
				<< "=======================================================================\n\n";

		cout << "\n\n1.Confirm\n2.Go Back To Main Menu";
		cin >> ch;
		if (ch == 1) {
			s1.Del();
			cout << "\n1.Delete Gross Sell \n2.Don't Delete Gross Sell";
			cin >> ch;
			if (ch == 1)
				s1.dgs();
			cout << "\nDeleted Successfully ";
			getch();
		}
		goto menu;
		break;
	default:
		break;
	}
//	textcolor(35);
//	clrscr();
	clrscr();

	cout << "\n\n\n\t\t\t" << endl;
	getch();
//	clrscr();
	clrscr();

	s1.endp();

}

