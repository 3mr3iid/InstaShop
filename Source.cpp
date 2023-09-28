#include<iostream>
#include<fstream>
using namespace std;
class Product
{
private:
	struct P {
		int Product_ID;
		string Product_Name;
		string Category;
		float Product_Price;
		int Product_Quantity;
	};
public:
	int Index;
	P p[100];
	Product()
	{
		for (int i = 0; i < 100; i++)
		{
			p[i].Product_ID = 0;
		}
		Index = Initialize();
	}
	string GetName(int ID)
	{
		return p[FindP(ID)].Product_Name;
	}
	~Product()
	{
		UpdateProducts();
	}
	bool AddProduct(int ID, string Name, string Cat, float Price, int Quantity)
	{
		if (FindP(ID) == -1)
		{
			p[Index].Product_ID = ID;
			p[Index].Product_Name = Name;
			p[Index].Category = Cat;
			p[Index].Product_Price = Price;
			p[Index].Product_Quantity = Quantity;
			Index++;
			return true;
		}
		cout << "ID already exists, choose another one!!" << endl;
		return false;
	}
	float GetPrice(int ID)
	{
		return p[FindP(ID)].Product_Price;
	}
	int GetQuantity(int ID)
	{
		return p[FindP(ID)].Product_Quantity;
	}
	void SetQuantity(int ID, int Quantity)
	{
		p[FindP(ID)].Product_Quantity = Quantity;
	}
	void SetPrice(int ID, float Price)
	{
		p[FindP(ID)].Product_Price = Price;
	}
	int FindP(int ID)
	{
		for (int j = 0; j < Index; j++)
		{
			if (ID == p[j].Product_ID)
			{
				return j;
			}
		}
		return -1;
	}
	void Swap(P& o, P& t)
	{
		P Temp = o;
		o = t;
		t = Temp;
	}
	void Sort()
	{
		for (int i = 0; i < Index; i++)
		{
			for (int j = 0; j < Index; j++)
			{
				if (p[i].Product_ID > p[j].Product_ID)
				{
					Swap(p[i], p[j]);
				}
			}
		}
	}
	void DeleteProduct(int ID)
	{
		if (FindP(ID) != -1)
		{
			p[FindP(ID)].Product_ID = 0;
			Sort();
			Index--;
		}
		else
		{
			cout << "Product does not exist in your database!!" << endl;
		}
	}
	void UpdateProducts()
	{
		ofstream myFile;
		myFile.open("Products.txt");
		for (int i = 0; i < Index; i++)
		{
			myFile << p[i].Product_ID << " " << p[i].Product_Name << " " << p[i].Category << " " << p[i].Product_Price << " " << p[i].Product_Quantity<<endl;
		}
	}
	int Initialize()
	{
		int ID1 = 0;
		int Index = 0;
		ifstream myFile;
		myFile.open("Products.txt");
		while (myFile >> ID1)
		{
			p[Index].Product_ID = ID1;
			myFile >> p[Index].Product_Name >> p[Index].Category >> p[Index].Product_Price >> p[Index].Product_Quantity;
			Index++;
		}
		myFile.close();
		return Index;
	}
	void DisplayProducts()
	{
		cout << "   ID   " << "\t" << "   Name   " << "\t" << "   Category   " << "\t" << "   Price   " << "\t" << "   Quantity" << endl;
		for (int i = 0; i < Index; i++)
		{
			cout << "   " << p[i].Product_ID << "   " << "\t\t" << "   " << p[i].Product_Name << "   " << "\t" << "   " << p[i].Category << "\t     " << p[i].Product_Price <<"\t\t" << "      " << p[i].Product_Quantity << endl;
		}
	}
};
class ShoppingCart
{
private:
	struct S
	{
		int Product_ID;
		string Name;
		int Quantity;
		float Price;
	};
	int IndexS;
	float Total;
	struct H {
		int Customer_ID;
		int Product_ID;
		string Product_Name;
		int Product_Quantity;
		float Product_Price;
		int Order_Number;
	};
	int IndexH;
	int Current_Order_Num;
public:
	S s[100];
	H h[100];
	void ResetTotal()
	{
		Total = 0.0;
	}
	int Calculate_Order_Num()
	{
		Current_Order_Num = 0;
		for (int i = 0; i < IndexH; i++)
		{
			if (h[i].Order_Number > Current_Order_Num)
			{
				Current_Order_Num = h[i].Order_Number;
			}
		}
		Current_Order_Num++;
		return Current_Order_Num;
	}
	int Calc(int OrderN)
	{
		int c = 0;
		for (int i = 0; i < IndexH; i++)
		{
			if (h[i].Order_Number == OrderN)
			{
				c++;
			}
		}
		return c;
	}
	void Re_order(int ID, int OrderN, Product& P)
	{
		int j = 0;
		bool Flag = false;
		if (HistoryExists(ID))
		{
			for (int i = 0; i < Calc(OrderN); i++)
			{
				while (true)
				{
					if (h[j].Order_Number == OrderN)
					{
						if (h[j].Customer_ID == ID)
						{
							AddItem(h[j].Product_ID, h[j].Product_Quantity, P);
							Flag = true;
							break;
						}
					}
					j++;
				}
			}
			if (Flag == false)
			{
				cout << "Order number was not found!!" << endl;
			}
		}
		else
		{
			cout << "You don't have any past orders!!" << endl;
		}
	}
	float CalculateTotal(Product& Pro)
	{
		ResetTotal();
		for (int i = 0; i < IndexS; i++)
		{
			Total += (s[i].Quantity * Pro.GetPrice(s[i].Product_ID));
		}
		return Total;
	}
	void Swap(S& o, S& t)
	{
		S Temp = o;
		o = t;
		t = Temp;
	}
	void Sort()
	{
		for (int i = 0; i < IndexS; i++)
		{
			for (int j = 0; j < IndexS; j++)
			{
				if (s[i].Quantity > s[j].Quantity)
				{
					Swap(s[i], s[j]);
				}
			}
		}
	}
	void ResetCart()
	{
		IndexS = 0;
		Total = 0.0;
		for (int i = 0; i < 10; i++)
		{
			s[i].Quantity = 0;
		}
	}
	ShoppingCart()
	{
		for (int i = 0; i < 100; i++)
		{
			h[i].Customer_ID = 0;
		}
		IndexS = 0;
		IndexH = 0;
		ResetCart();
		IndexH = InitializeHistory();
		Calculate_Order_Num();
	}
	~ShoppingCart()
	{
		ResetCart();
		UpdateHistory();
	}
	bool is_empty()
	{
		return(IndexS == 0);
	}
	void UpdateHistory()
	{
		ofstream myFile;
		myFile.open("History.txt");
		for (int i = 0; i < IndexH; i++)
		{
			myFile << h[i].Customer_ID << " " << h[i].Product_ID << " " << h[i].Product_Name << " " << h[i].Product_Quantity << " " << h[i].Product_Price << " " << h[i].Order_Number<<endl;
		}
	}
	int InitializeHistory()
	{
		int ID1;
		int IndexH = 0;
		ifstream myFile;
		myFile.open("History.txt");
		while (myFile >> ID1)
		{
			h[IndexH].Customer_ID = ID1;
			myFile >> h[IndexH].Product_ID >> h[IndexH].Product_Name >> h[IndexH].Product_Quantity >> h[IndexH].Product_Price >> h[IndexH].Order_Number;
			IndexH++;
		}
		myFile.close();
		return IndexH;
	}
	int Find(int id)
	{
		for (int i = 0; i < IndexS; i++)
		{
			if (id == s[i].Product_ID)
			{
				return i;
			}
		}
		return -1;
	}

	void AddToHistory(int ID, Product& Pro)
	{
		for (int i = 0; i < IndexS; i++)
		{
			h[IndexH].Customer_ID = ID;
			h[IndexH].Product_ID = s[i].Product_ID;
			h[IndexH].Product_Name = Pro.GetName(s[i].Product_ID);
			h[IndexH].Product_Quantity = s[i].Quantity;
			h[IndexH].Product_Price = Pro.GetPrice(s[i].Product_ID);
			h[IndexH].Order_Number = Current_Order_Num;
			IndexH++;
		}
	}
	bool HistoryExists(int ID)
	{
		for (int i = 0; i < IndexH; i++)
		{
			if (h[i].Customer_ID == ID)
			{
				return true;
			}
		}
		return false;
	}
	float CalculateAll(int ID)
	{
		float T = 0;
		for (int i = 0; i < IndexH; i++)
		{
			if (h[i].Customer_ID == ID)
			{
				T += (h[i].Product_Quantity * h[i].Product_Price);
			}
		}
		return T;
	}
	float CalcSkinCareP(Product& Pro)
	{
		float T = 0;
		for (int i = 0; i < IndexS; i++)
		{
			if (Pro.p[Pro.FindP(s[i].Product_ID)].Category == "SkinCare")
			{
				T += (s[i].Price * s[i].Quantity);
			}
		}
		float Deducted = T * 0.2;
		return Deducted;
	}
	bool SkinCareExists(Product &Pro)
	{
		bool Flag = false;
		for (int i = 0; i < IndexS; i++)
		{
			if (Pro.p[Pro.FindP(s[i].Product_ID)].Category == "SkinCare")
			{
				Flag = true;
				break;
			}
		}
		return Flag;
	}
	void DisplayHistory(int ID)
	{
		if (HistoryExists(ID))
		{
			cout << "CustomerID\tProductID\tProductName\tProoductQuantity\tProductPrice\tOrderNumber" << endl;
			for (int i = 0; i < IndexH; i++)
			{
				if (h[i].Customer_ID == ID)
				{
					cout <<"    " << h[i].Customer_ID << "\t\t   " << h[i].Product_ID << "\t\t  " << h[i].Product_Name << "\t      " << h[i].Product_Quantity << "\t\t     " << h[i].Product_Price << "\t\t     " << h[i].Order_Number << endl;
				}
			}
		}
		else
		{
			cout << "Your history is empty!!" << endl;
		}
	}
	void AddItem(int id, int Quantity, Product& Pro)
	{
		if (Pro.FindP(id) != -1)
		{
			if (Quantity <= Pro.GetQuantity(id))
			{
				Pro.SetQuantity(id, (Pro.GetQuantity(id) - Quantity));
				if (Find(id) != -1)
				{
					s[Find(id)].Quantity += Quantity;
				}
				else
				{
					s[IndexS].Product_ID = id;
					s[IndexS].Quantity = Quantity;
					s[IndexS].Price = Pro.GetPrice(id);
					s[IndexS].Name = Pro.GetName(id);
					IndexS++;
				}
			}
			else
			{
				cout << "Insufficient Quantity!!" << endl;
			}
		}
		else
		{
			cout << "Item does not exist!!" << endl;
		}
	}
	void DeleteItem(int id, int Quantity, Product& Pro)
	{
		if (Find(id) != -1)  
		{
			if (s[Find(id)].Quantity >= Quantity)
			{
				s[Find(id)].Quantity -= Quantity;
				if (s[Find(id)].Quantity == 0)
				{
					Sort();
					IndexS--;
				}
				Pro.SetQuantity(id, Pro.GetQuantity(id) + Quantity);
			}
			else
			{
				cout << "The quantity that you want to remove is greater than the quantity that you have in your shopping cart!!" << endl;
			}
		}
		else
		{
			cout << "Item not found in your shopping cart!!" << endl;
		}
	}
	void DisplayCart(Product& P)
	{
		if (IndexS != 0)
		{
			cout << "ID\t" << "Name\t" << "   Quantity\t" << "Price\t" << endl;
			for (int i = 0; i < IndexS; i++)
			{
				cout << s[i].Product_ID << "\t" << s[i].Name << "\t      " << s[i].Quantity << "\t\t  " << s[i].Price << endl;
			}
			cout << "========================================" << endl;
			cout << "The total price of your shopping cart is : " << CalculateTotal(P) << endl;
		}
		else
		{
			cout << "Your shopping cart is empty!!" << endl;
		}
	}
};
class Credit_Card {
private:
	struct Card {
		int Account_Number;
		string Pin;
		float Balance;
	};
	int Index;
public:
	Card v[100];
	void Update()
	{
		ofstream myFile;
		myFile.open("CreditCards.txt");
		for (int i = 0; i < Index; i++)
		{
			myFile << v[i].Account_Number << " " << v[i].Pin << " " << v[i].Balance<<endl;
		}
	}
	bool NewCreditCard(int Acc, string Pin1, float Money)
	{
		if (Find(Acc) == -1)
		{
			v[Index].Account_Number = Acc;
			v[Index].Pin = Pin1;
			v[Index].Balance = Money;
			Index++;
			return true;
		}
		cout << "Account number already exists, choose another one!!" << endl;
		return false;
	}
	int Initialize()
	{
		int Acc;
		int Index = 0;
		ifstream myFile;
		myFile.open("CreditCards.txt");
		while (myFile >> Acc)
		{
			v[Index].Account_Number = Acc;
			myFile >> v[Index].Pin >> v[Index].Balance;
			Index++;
		}
		myFile.close();
		return Index;
	}
	Credit_Card()
	{
		for (int i = 0; i < 10; i++)
		{
			v[i].Account_Number = 0;
		}
		Index = Initialize();
	}
	~Credit_Card()
	{
		Update();
	}
	int Find(int Acc)
	{
		int j = -1;
		for (int i = 0; i < Index; i++)
		{
			if (v[i].Account_Number == Acc)
			{
				j = i;
				break;
			}
		}
		return j;
	}
	bool Login(int Acc, string Pin)
	{
		if (Find(Acc) != -1)
		{
			if (Pin == v[Find(Acc)].Pin)
			{
				cout << "Access Granted!!" << endl;
				return true;
			}
			else
			{
				cout << "This pin does not match your account number!!" << endl;
				cout << "Access Denied!!" << endl;
				return false;
			}
		}
		else
		{
			cout << "ACCOUNT NOT FOUND!!" << endl;
			return false;
		}
	}
	void ChargeCreditCard(float Amount, int Acc)
	{
		v[Find(Acc)].Balance += Amount;
	}
};
class Customer
{
private:
	struct C {
		int Customer_ID;
		bool is_admin;
		string Customer_Password;
		string Customer_Name;
		float Customer_Balance;
		string Customer_Address;
	};
	int Index;
public:
	C c[100];
	Customer()
	{
		for (int i = 0; i < 100; i++)
		{
			c[i].Customer_ID = 0;
		}
		Index = Initialize();
	}
	~Customer()
	{
		UpdateCustomers();
	}
	bool is_special(int ID,ShoppingCart &S)
	{
		if (S.CalculateAll(ID) > 10000)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void ChangeName(string Name, int ID)
	{
		c[Find(ID)].Customer_Name = Name;
	}
	void DisplayDetails(int ID)
	{
		cout << "Your ID is : " << c[Find(ID)].Customer_ID << endl;
		cout << "Your Name is : " << c[Find(ID)].Customer_Name << endl;
		cout << "Your account balance is : " << c[Find(ID)].Customer_Balance << endl;
		cout << "Your Address is : " << c[Find(ID)].Customer_Address << endl;
	}
	void ChargeWallet(float Amount, int ID, int Acc, Credit_Card& V)
	{
		if (V.v[V.Find(Acc)].Balance >= Amount)
		{
			V.v[V.Find(Acc)].Balance -= Amount;
			c[Find(ID)].Customer_Balance += Amount;
		}
	}
	void MakeAdmin(int ID)
	{
		c[Find(ID)].is_admin = 1;
	}
	void DismissAdmin(int ID)
	{
		c[Find(ID)].is_admin = 0;
	}
	void ChangePassword(string New, string Old, int id)
	{
		if (Old == c[Find(id)].Customer_Password)
		{
			if (Old == New)
			{
				cout << "The new password cannot be the same as the old one!!" << endl;
			}
			else
			{
				c[Find(id)].Customer_Password = New;
				cout << "Password successfully changed" << endl;
			}
		}
		else
		{
			cout << "The old password is incorrect!!" << endl;
		}
	}
	void ChangeAddress(string Add, int ID)
	{
		c[Find(ID)].Customer_Address = Add;
	}
	int Find(int id)
	{
		for (int i = 0; i < Index; i++)
		{
			if (c[i].Customer_ID == id)
			{
				return i;
			}
		}
		return -1;
	}
	void UpdateCustomers()
	{
		ofstream myFile;
		myFile.open("Customers.txt");
		for (int i = 0; i < Index; i++)
		{
			myFile << c[i].Customer_ID << " " << c[i].is_admin << " " << c[i].Customer_Password << " " << c[i].Customer_Name << " " << c[i].Customer_Balance << " " << c[i].Customer_Address<<endl;
		}
	}
	bool NewCustomer(int id, string Password, string Name, string Address)
	{
		if (Find(id) == -1)
		{
			c[Index].Customer_ID = id;
			c[Index].is_admin = 0;
			c[Index].Customer_Password = Password;
			c[Index].Customer_Name = Name;
			c[Index].Customer_Balance = 0;
			c[Index].Customer_Address = Address;
			Index++;
			return true;
		}
		cout << "ID already exists, choose another one!!" << endl;
		return false;
	}
	int Initialize()
	{
		int ID1;
		int Index = 0;
		ifstream myFile;
		myFile.open("Customers.txt");
		while (myFile >> ID1)
		{
			c[Index].Customer_ID = ID1;
			myFile >> c[Index].is_admin >> c[Index].Customer_Password >> c[Index].Customer_Name >> c[Index].Customer_Balance >> c[Index].Customer_Address;
			Index++;
		}
		myFile.close();
		return Index;
	}
	bool Login(int id, string Password)
	{
		if (Find(id) != -1)
		{
			if (Password == c[Find(id)].Customer_Password)
			{
				cout << "Access granted!!" << endl;
				return true;
			}
			else
			{
				cout << "This password does not match your ID!!" << endl;
				cout << "Access denied!!" << endl;
				return false;
			}
		}
		else
		{
			cout << "ID NOT FOUND!!" << endl;
			return false;
		}
	}
	bool AdminLogin(int id, string Password)
	{
		if (Find(id) != -1)
		{
			if (c[Find(id)].is_admin == true)
			{
				if (Password == c[Find(id)].Customer_Password)
				{
					cout << "Access granted!!" << endl;
					return true;
				}
				else
				{
					cout << "This password does not match your ID!!" << endl;
					cout << "Access denied!!" << endl;
					return false;
				}
			}
			else
			{
				cout << "You are not an adminstrator!!" << endl;
				cout << "Access Denied!!" << endl;
				return false;
			}
		}
		else
		{
			cout << "ID NOT FOUND!!" << endl;
			return false;
		}
	}
	bool FinalCheckOut(Product& P, int ID, ShoppingCart& S, Customer& C, Credit_Card& V)
	{
		bool Flag = false;
		float FinalTotal = S.CalculateTotal(P);
		if (C.c[C.Find(ID)].Customer_Balance < 0)
		{
			float Fee = (C.c[C.Find(ID)].Customer_Balance) * -1;
			cout << "Please note that a fee of " << Fee << "$ will be added to the total price of this order!!" << endl;
			FinalTotal += ((C.c[C.Find(ID)].Customer_Balance) * -1);
			C.c[C.Find(ID)].Customer_Balance = 0;
		}
		if (C.is_special(ID, S) && S.SkinCareExists(P))
		{
			cout << "Please note that a discount of 20% will be applied on your skin care products since you are a special customer!!" << endl;
			FinalTotal -= S.CalcSkinCareP(P);
		}
		bool Flag1 = false;
		do
		{
			cout << "Choose a payment method:" << endl;
			cout << "1. Pay with cash." << endl;
			cout << "2. Pay with credit card." << endl;
			cout << "Enter your choice >> " << flush;
			int c;
			cin >> c;
			system("cls");
			if (c == 1)
			{
				cout << "These are the details of your order:" << endl;
				S.DisplayCart(P);
				cout << "Do you want to rush the order?? (Y/N) : " << flush;
				char z;
				cin >> z;
				if (z == 'y' || z == 'Y')
				{
					cout << "Order will arrive within 24 hours!!" << endl;
					cout << "please note that an extra rushing fee of 10$ will be be added to the total price of the order!!" << endl;
					FinalTotal += 10;
					Flag1 = true;
				}
				if (C.c[C.Find(ID)].Customer_Balance >= FinalTotal)
				{
					cout << FinalTotal << "$ were deducted from your account balance." << endl;
					cout << "The new total price of your order is : " << 0 << "$" << endl;
					C.c[C.Find(ID)].Customer_Balance -= FinalTotal;
				}
				else
				{
					cout << C.c[C.Find(ID)].Customer_Balance << "$ were deducted from your account balance." << endl;
					cout << "The new total price of your order is : " << FinalTotal - C.c[C.Find(ID)].Customer_Balance << "$" << endl;
					C.c[C.Find(ID)].Customer_Balance = 0;
				}
				if (Flag1 == false)
				{
					cout << "Order will be delivered to " << C.c[C.Find(ID)].Customer_Address << " within 3 days." << endl;
				}
				Flag = true;
				system("pause");
				system("cls");
			}
			else if (c == 2)
			{
				cout << "These are the details of your order:" << endl;
				S.DisplayCart(P);
				cout << "Do you want to rush the order?? (Y/N) : " << flush;
				char z;
				cin >> z;
				if (z == 'y' || z == 'Y')
				{
					cout << "Order will arrive within 24 hours!!" << endl;
					cout << "please note that an extra rushing fee of 10$ will be be added to the total price of the order!!" << endl;
					FinalTotal += 10;
					Flag1 = true;
				}
				cout << "Enter your account number >> " << flush;
				int Acc;
				cin >> Acc;
				cout << "Enter your PIN code >> " << flush;
				string Pin;
				cin >> Pin;
				if (V.Login(Acc, Pin))
				{
					if (C.c[C.Find(ID)].Customer_Balance >= FinalTotal)
					{
						cout << FinalTotal << "$ were deducted from your account balance." << endl;
						cout << "Nothing was deducted from your credit card balance." << endl; 
						cout << "The new total price of your order is : " << 0 << "$" << endl;
						C.c[C.Find(ID)].Customer_Balance -= FinalTotal;
					}
					else
					{
						cout << C.c[C.Find(ID)].Customer_Balance << "$ were deducted from your account balance." << endl;
						float New = FinalTotal - C.c[C.Find(ID)].Customer_Balance;
						cout << "The new total price of your order is : " << New << "$" << endl;
						C.c[C.Find(ID)].Customer_Balance = 0;
						if (V.v[V.Find(Acc)].Balance >= New)
						{
							V.v[V.Find(Acc)].Balance -= New;
							cout << New << "$ were deducted from your credit card balance." << endl;
						}
						else
						{
							New -= V.v[V.Find(Acc)].Balance;
							C.c[C.Find(ID)].Customer_Balance -= New;
							V.v[V.Find(Acc)].Balance = 0;
							cout << "Since your credit card balance was insufficient, we have added a fee of " << New << "$ to your next purchase." << endl;
						}
					}
					if (Flag1 == false)
					{
						cout << "Order will be delivered to " << C.c[C.Find(ID)].Customer_Address << " within 3 days." << endl;
					}
					Flag = true;
				}
				system("pause");
				system("cls");
			}
			system("cls");
		} while (Flag == false);
		return Flag;

	}
	void Process1(Product& P,Customer &C)
	{
		char x;
		do
		{
			cout << "Enter your ID >> " << flush;
			int ID;
			cin >> ID;
			cout << "Enter your password >> " << flush;
			string Pass;
			cin >> Pass;
			if (AdminLogin(ID, Pass))
			{
				system("cls");
				char y;
				do
				{
					cout << "Choose from the following menu:" << endl;
					cout << "1. Add new product." << endl;
					cout << "2. Remove an existing product." << endl;
					cout << "3. Change the quantity of a product." << endl;
					cout << "4. Change the price of a product." << endl;
					cout << "5. Display all products." << endl;
					cout << "6. Make new adminstrator." << endl;
					cout << "7. Dismiss a user as an adminstrator." << endl;
					cout << "Enter your choice >> " << flush;
					int c;
					cin >> c;
					system("cls");
					if (c == 1)
					{
						cout << "Enter the ID of the product >> " << flush;
						int ID;
						cin >> ID;
						cout << "Enter the Name of the product >> " << flush;
						string Name;
						cin >> Name;
						cout << "Enter the category of the product >> " << flush;
						string Cat;
						cin >> Cat;
						cout << "Enter the price of the product >> " << flush;
						float Price;
						cin >> Price;
						cout << "Enter the Quantity of the product >> " << flush;
						int Q;
						cin >> Q;
						P.AddProduct(ID, Name, Cat, Price, Q);
					}
					else if (c == 2)
					{
						P.DisplayProducts();
						cout << "Enter the ID of the product that you want to remove >> " << flush;
						int ID;
						cin >> ID;
						P.DeleteProduct(ID);
					}
					else if (c == 3)
					{
						P.DisplayProducts();
						cout << "Enter the ID of the product >> " << flush;
						int ID;
						cin >> ID;
						cout << "Enter the new quantity >> " << flush;
						int Q;
						cin >> Q;
						P.SetQuantity(ID, Q);
					}
					else if (c == 4)
					{
						P.DisplayProducts();
						cout << "Enter the ID of the product >> " << flush;
						int ID;
						cin >> ID;
						cout << "Enter the new price >> " << flush;
						float Price;
						cin >> Price;
						P.SetPrice(ID, Price);
					}
					else if (c == 5)
					{
						P.DisplayProducts();
					}
					else if (c == 6)
					{
						cout << "Enter the ID of the user that you want to make an admistrator >> " << flush;
						int ID;
						cin >> ID;
						C.MakeAdmin(ID);
					}
					else if (c == 7)
					{
						cout << "Enter the ID of the user that you want to dismiss as an admistrator >> " << flush;
						int ID;
						cin >> ID;
						C.DismissAdmin(ID);
					}
					else
					{
						cout << "Invalid choice, please choose an option from the menu!!" << endl;
					}
					cout << "Do you want to perform any other operations?? (Y/N) : " << flush;
					cin >> y;
					system("cls");
				} while (y == 'y' || y == 'Y');
			}
			cout << "Do you want to login again?? (Y/N) : " << flush;
			cin >> x;
			system("cls");
		} while (x == 'y' || x == 'Y');
	}
	void Process2(ShoppingCart& S, Product& P, Credit_Card& V, Customer& C)
	{
		char x;
		do
		{
			cout << "Enter your ID >> " << flush;
			int Login_ID;
			cin >> Login_ID;
			cout << "Enter your password >> " << flush;
			string Pass;
			cin >> Pass;
			if (Login(Login_ID, Pass))
			{
				system("cls");
				char y;
				do
				{
					cout << "Choose from the following menu:" << endl;
					cout << "1. Display products." << endl;
					cout << "2. Add an item to your shopping cart." << endl;
					cout << "3. Remove an item from your shopping cart." << endl;
					cout << "4. Display your shopping cart." << endl;
					cout << "5. Display your past orders." << endl;
					cout << "6. Re-order a past order." << endl;
					cout << "7. Perform actions on your account." << endl;
					cout << "Enter your choice >> " << flush;
					int c;
					cin >> c;
					system("cls");
					if (c == 1)
					{
						P.DisplayProducts();
					}
					else if (c == 2)
					{
						P.DisplayProducts();
						cout << "Enter the ID of the item that you want >> " << flush;
						int ID;
						cin >> ID;
						cout << "Enter the quantity that you want >> " << flush;
						int Q;
						cin >> Q;
						S.AddItem(ID, Q, P);
					}
					else if (c == 3)
					{
						S.DisplayCart(P);
						if (!S.is_empty())
						{
							cout << "Enter the ID of the item that you want to remove >> " << flush;
							int ID;
							cin >> ID;
							cout << "Enter the quantity that you want to remove >> " << flush;
							int Q;
							cin >> Q;
							S.DeleteItem(ID, Q, P);
						}
					}
					else if (c == 4)
					{
						S.DisplayCart(P);
					}
					else if (c == 5)
					{
						S.DisplayHistory(Login_ID);
					}
					else if (c == 6)
					{
						S.DisplayHistory(Login_ID);
						cout << "Enter the number of the order that you want to re-order >> " << flush;
						int Num;
						cin >> Num;
						S.Re_order(Login_ID, Num, P);
					}
					else if (c == 7)
					{
						char k;
						do
						{
							cout << "Choose from the following menu:" << endl;
							cout << "1. View your account details." << endl;
							cout << "2. Change your name." << endl;
							cout << "3. Change your password." << endl;
							cout << "4. Change your address." << endl;
							cout << "5. Charge your account balance." << endl;
							cout << "6. Charge your credit card balance." << endl;
							cout << "7. New credit card." << endl;
							cout << "Enter your choice >> " << flush;
							int o;
							cin >> o;
							system("cls");
							if (o == 1)
							{
								C.DisplayDetails(Login_ID);
							}
							else if (o == 2)
							{
								cout << "Enter a new name >> " << flush;
								string Name;
								cin >> Name;
								C.ChangeName(Name, Login_ID);
							}
							else if (o == 3)
							{
								cout << "Enter your old password >> " << flush;
								string OPass;
								cin >> OPass;
								cout << "Enter your new password >> " << flush;
								string NPass;
								cin >> NPass;
								C.ChangePassword(NPass, OPass, Login_ID);
							}
							else if (o == 4)
							{   
								cout << "Enter your new address >> " << flush;
								string Add;
								cin >> Add;
								C.ChangeAddress(Add, Login_ID);
							}
							else if (o == 5)
							{
								cout << "Enter your account number >> " << flush;
								int Acc;
								cin >> Acc;
								cout << "Enter your PIN code >> " << flush;
								string Pin;
								cin >> Pin;
								if (V.Login(Acc, Pin))
								{
									cout << "Enter the amount of money that you want to charge >> " << flush;
									float Amount;
									cin >> Amount;
									C.ChargeWallet(Amount, Login_ID, Acc, V);
								}
							}
							else if (o == 6)
							{
								cout << "Enter your account number >> " << flush;
								int Acc;
								cin >> Acc;
								cout << "Enter your PIN code >> " << flush;
								string Pin;
								cin >> Pin;
								if (V.Login(Acc, Pin))
								{
									cout << "Enter the amount of money that you want to charge >> " << flush;
									float Amount;
									cin >> Amount;
									V.ChargeCreditCard(Amount, Acc);
								}
							}
							else if (o == 7)
							{
								cout << "Enter your account number >> " << flush;
								int Acc;
								cin >> Acc;
								cout << "Enter your PIN code >> " << flush;
								string Pin;
								cin >> Pin;
								cout << "Enter the amount of money in your credit card >> " << flush;
								float Mon;
								cin >> Mon;
								V.NewCreditCard(Acc, Pin, Mon);
							}
							else
							{
								cout << "Invalid choice, please choose an option from the menu!!" << endl;
							}
							cout << "Do you want to perform any other actions on your account?? (Y/N) : " << flush;
							cin >> k;
							system("cls");
						} while (k == 'y' || k == 'Y');
					}
					else
					{
						cout << "Invalid choice, please choose an option from the menu!!" << endl;
					}
					cout << "Do you want to perform any other operations?? (Y/N) : " << flush;
					cin >> y;
					system("cls");
					if (y != 'y' && y != 'Y')
					{
						if (!S.is_empty())
						{
							C.FinalCheckOut(P, Login_ID, S, C, V);
						}
						S.AddToHistory(Login_ID, P);
						S.ResetCart();
					}
				} while (y == 'y' || y == 'Y');
			}
			cout << "Do you want to login again?? (Y/N) : " << flush;
			cin >> x;
			system("cls");
		} while (x == 'y' || x == 'Y');
	}
};
int main()
{
	Product P;
	Customer C;
	ShoppingCart S;
	Credit_Card V;
	char x;
	do
	{
		cout << "                                                  WELCOME TO INSTASHOP" << endl;
		cout << "Choose from the following menu:" << endl;
		cout << "1. Login as an adminstrator." << endl;
		cout << "2. Login as a customer." << endl;
		cout << "3. Create a new account." << endl;
		cout << "Enter your choice >> " << flush;
		int c;
		cin >> c;
		system("cls");
		if (c == 1)
		{
			C.Process1(P,C);
		}
		else if (c == 2)
		{
			C.Process2(S, P, V, C);
		}
		else if (c == 3)
		{
			cout << "Choose an ID >> " << flush;
			int ID;
			cin >> ID;
			cout << "Choose a Password >> " << flush;
			string Pass;
			cin >> Pass;
			cout << "Enter your name >> " << flush;
			string Name;
			cin >> Name;
			cout << "Enter your address >> " << flush;
			string Add;
			cin >> Add;
			if (C.NewCustomer(ID, Pass, Name, Add))
			{
				system("cls");
				cout << "**Please login with your new account**" << endl;
				C.Process2(S, P, V, C);
			}
		}
		cout << "Do you want to try again?? (Y/N) : " << flush;
		cin >> x;
		system("cls");
	} while (x == 'y' || x == 'Y');
}