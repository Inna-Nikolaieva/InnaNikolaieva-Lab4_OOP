#include <iostream>
#include <string>

#define KST 30

using namespace std;

class Train_Ticket					//базовий клас
{
protected:
	string data;					//дані про пасажира
	int number;						//номер вагона
public:
	Train_Ticket() { data = ""; number = 0; }
	Train_Ticket(string str, int n) { data = str; number = n; }
	~Train_Ticket() {}
};

class Compartment_Ticket : public Train_Ticket
{
private:
	int place;						//місце у вагоні
	double price;					//вартість квитка
public:
	Compartment_Ticket() { place = price = 0; }
	Compartment_Ticket(int p, double c) { place = p; price = c; }
	~Compartment_Ticket(){}

	double get_price() { return price; }

	friend istream& operator>> (istream& in, Compartment_Ticket& ct);
	friend ostream& operator<< (ostream& out, const Compartment_Ticket& ct);

	int SetData(int p, double c)
	{
		if (p < 1 || p > 36)
		{
			cout << "Incorrectly entered data!!!" << endl;
			system("pause");
			return 0;
		}
		else
			place = p; price = c;
	}
	
	bool operator>(Compartment_Ticket& ct)
	{
		return this->price > ct.price;
	}
};

void Typeofplace(int p)
{
	if (p % 2 == 0)
		cout << "Top shelf.";
	else
		cout << "Bottom shelf.";
}

istream& operator>> (istream& in, Compartment_Ticket& ct)
{
	cout << endl << "Enter passenger data: ";
	in >> ct.data;
	cout << "Enter the train number: ";
	in >> ct.number;
	cout << "Enter a place: ";
	in >> ct.place;
	cout << "Enter the price: ";
	in >> ct.price;
	ct.SetData(ct.place, ct.price);
	return in;
}

ostream& operator<< (ostream& out, const Compartment_Ticket& ct)
{
	out << "Passenger data: " << ct.data << "        ";
	out << "Train number: " << ct.number << "        ";
	out << "Place: " << ct.place << "        ";
	Typeofplace(ct.place); out << "        ";
	out << "Price: " << ct.price;
	out << endl;
	return out;
}

void sort(Compartment_Ticket* ct, int k);
void print(Compartment_Ticket* ct, int k);
double total_cost(Compartment_Ticket* ct, int k);

int main(void)
{
	Compartment_Ticket ct[KST];
	int kst = 0;
	double sum = 0;

	cout << "Enter the number of tickets: ";
	cin >> kst;
	for (int i = 0; i < kst; i++)
		cin >> ct[i];
	cout << endl;
	sort(ct, kst);
	print(ct, kst);

	sum = total_cost(ct, kst);
	cout << endl << "Total cost: " << sum << endl;
	system("pause");
	return 0;
}

void sort(Compartment_Ticket* ct, int k)
{
	for (int i = 0; i < k; i++)
	{
		for (int j = i + 1; j < k; j++)
		{
			if (ct[i] > ct[j])
			{
				Compartment_Ticket tmp = ct[i];
				ct[i] = ct[j];
				ct[j] = tmp;
			}
		}
	}
}

void print(Compartment_Ticket* ct, int k)
{
	for (int i = 0; i < k; i++)
		cout << i + 1 << ". " << ct[i];
}

double total_cost(Compartment_Ticket* ct, int k)
{
	double sum = 0;
	for (int i = 0; i < k; i++)
		sum += ct[i].get_price();
	return sum;
}