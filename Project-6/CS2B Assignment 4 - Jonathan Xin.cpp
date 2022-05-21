//-----------------------------------------------------------------------------
//  Date: 03-16-2021
//  Program purpose: This program simulates an account manager of messages.	
//  Disclaimer: If this program is working it's written by the author below.
//              If it is not I don't know who wrote it.
//  Revision history:
//  Date             Programmer            Change ID     Description
//  03/16/21         Jonathan Xin          1000          Initial implementation
//-----------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <iomanip>
#include <map>
#include <vector>
#include <exception>

using namespace std;

class AccountNotFoundException : public exception
{
private:
	string* error_message;
public:
	AccountNotFoundException(string non_exist_number);
	~AccountNotFoundException();
	virtual const char* what() const noexcept;
};

class Media
{
private:
	double size;
public:
	static const double DEFAULT_SIZE;
	static const double DEFAULT_CHARGE_PER_MB;
	static const double DEFAULT_MINI_CHARGE;
	static const double SIZE_THRESHOLD;
public:
	Media();
	Media(double size);
	~Media();

	void set_size(double size);
	double get_size() const;
	double GetCharge();
};

template <class T>
class Message
{
private:
	string to;
	T m_data;
public:
	static const string DEFAULT_PHONE_NUMBER;

	Message();
	Message(string to, T m_data);
	~Message();

	T get_data() const;
	string get_to() const;
	void set_data(T m_data);
	void set_to(string to);
};

class SmartCarrier
{
private:
	string carrier_name;
	bool init;
	map<string, vector<Message<Media>*>> account_list;
public:
	static const string DEFAULT_CARRIER_NAME;
	static const bool DEFAULT_INIT;
public:
	SmartCarrier();
	SmartCarrier(string carrier_name, bool init);
	~SmartCarrier();

	void Init();
	void StartService();
private:
	void Menu() const;
	int GetChoice() const;
	void ListAccounts() const;
	void InsertMessage();
	void PurgeLargeMessages();
	void DisconnectAccount();
	void Quit() const;
};

const double Media::DEFAULT_SIZE = 0.0;
const double Media::DEFAULT_CHARGE_PER_MB = 0.05;
const double Media::DEFAULT_MINI_CHARGE = 1.00;
const double Media::SIZE_THRESHOLD = 100.00;
template <class T>
const string Message<T>::DEFAULT_PHONE_NUMBER = "000-000-0000";
const string SmartCarrier::DEFAULT_CARRIER_NAME = "XYZ Wireless";
const bool SmartCarrier::DEFAULT_INIT = false;

int main()
{
	SmartCarrier* JX_Carrier = new SmartCarrier("JX WIRELESS", false);
	JX_Carrier->Init();
	JX_Carrier->StartService();
	delete JX_Carrier;
}

AccountNotFoundException::AccountNotFoundException(string non_exist_number)
{
	error_message = new string("Account " + non_exist_number + " does not exist!");
}

AccountNotFoundException::~AccountNotFoundException() { delete error_message; }

const char* AccountNotFoundException::what() const noexcept
{
	return error_message->c_str();
}


Media::Media(): size(Media::DEFAULT_SIZE) {}
Media::Media(double size): size(size) {}
Media::~Media() {}
void Media::set_size(double size) { this->size = size; }
double Media::get_size() const { return size; }
double Media::GetCharge()
{
	double charge = size * Media::DEFAULT_CHARGE_PER_MB;
	if (charge > Media::DEFAULT_MINI_CHARGE)
		return charge;
	else
		return Media::DEFAULT_MINI_CHARGE;
}


template <class T>
Message<T>::Message(): to(Message<T>::DEFAULT_PHONE_NUMBER) {}
template <class T>
Message<T>::Message(string to, T m_data): to(to), m_data(m_data) {}
template <class T>
Message<T>::~Message() {}
template <class T>
T Message<T>::get_data() const { return m_data; }
template <class T>
string Message<T>::get_to() const { return to; }
template <class T>
void Message<T>::set_data(T m_data) { this->m_data = m_data; }
template <class T>
void Message<T>::set_to(string to) { this->to = to; }


SmartCarrier::SmartCarrier(): carrier_name(SmartCarrier::DEFAULT_CARRIER_NAME), init(SmartCarrier::DEFAULT_INIT) {}
SmartCarrier::SmartCarrier(string carrier_name, bool init) : carrier_name(carrier_name), init(init) {}
SmartCarrier::~SmartCarrier()
{
	map<string, vector<Message<Media>*>>::iterator account_iter;
	vector<Message<Media>*>::iterator message_iter;
	for (account_iter = account_list.begin(); account_iter != account_list.end(); ++account_iter)
	{
		for (message_iter = account_iter->second.begin(); message_iter != account_iter->second.end(); ++message_iter)
		{
			delete (*message_iter);
		}
		account_iter->second.clear();
	}	
	account_list.clear();
}

void SmartCarrier::Init()
{
	account_list["669-444-4444"];
	account_list["831-777-7777"].push_back(new Message <Media>("408-222-2222", Media(120.0)));
	account_list["408-555-5555"].push_back(new Message <Media>("408-555-8888", Media(875.35)));
	account_list["408-555-5555"].push_back(new Message <Media>("415-678-9011", Media(23.08)));
	account_list["408-555-5555"].push_back(new Message <Media>("669-000-1234", Media(57.59)));
	account_list["208-222-2222"].push_back(new Message <Media>("415-678-1111", Media(53.08)));
	account_list["208-222-2222"].push_back(new Message <Media>("408-666-8888", Media(75.35)));
	account_list["408-111-1111"].push_back(new Message <Media>("669-111-1234", Media(7.59)));
	account_list["408-111-1111"].push_back(new Message <Media>("669-222-1234", Media(357.59)));
	account_list["408-111-1111"].push_back(new Message <Media>("669-333-1234", Media(5.59)));
	account_list["708-111-1111"].push_back(new Message <Media>("669-444-1234", Media(45.45)));
	account_list["708-111-1111"].push_back(new Message <Media>("669-555-1234", Media(57.97)));
	account_list["708-111-1111"].push_back(new Message <Media>("669-666-1234", Media(115.59)));	
	account_list["108-111-1111"].push_back(new Message <Media>("669-777-1234", Media(145.45)));
	account_list["108-111-1111"].push_back(new Message <Media>("669-888-1234", Media(17.97)));
	account_list["108-111-1111"].push_back(new Message <Media>("669-999-1234", Media(215.59)));
	account_list["108-111-1111"].push_back(new Message <Media>("669-000-1234", Media(10.59)));
	account_list["108-111-1111"].push_back(new Message <Media>("569-999-1234", Media(143.59)));
	account_list["608-111-1111"].push_back(new Message <Media>("511-999-1234", Media(212.59)));
	account_list["608-111-1111"].push_back(new Message <Media>("522-999-1234", Media(111.59)));
	account_list["308-111-1111"].push_back(new Message <Media>("333-999-1234", Media(99.59)));
	account_list["308-111-1111"].push_back(new Message <Media>("333-999-1234", Media(173.59)));
	account_list["208-111-1111"].push_back(new Message <Media>("222-999-1234", Media(30.59)));
	account_list["208-111-1111"].push_back(new Message <Media>("222-999-1234", Media(40.59)));

	/*account_list["508-111-1111"].push_back(new Message <Media>("222-999-1234", Media(130.59)));
	account_list["508-111-1111"].push_back(new Message <Media>("222-999-1234", Media(140.59)));
	account_list["508-111-1111"].push_back(new Message <Media>("222-999-1234", Media(230.59)));
	account_list["508-111-1111"].push_back(new Message <Media>("222-999-1234", Media(240.59)));*/

	init = true;
}

void SmartCarrier::StartService()
{
	if (init)
	{
		int user_input = 0;
		do {
			try {
				Menu();
				user_input = GetChoice();
		
				switch (user_input) {
				case 1:
					ListAccounts();
					break;
				case 2:
					InsertMessage();
					break;
				case 3:
					PurgeLargeMessages();
					break;
				case 4:
					DisconnectAccount();
					break;
				}
			}

			catch (AccountNotFoundException & e) {
				cout << e.what() << endl;
			}

			catch (...) {
				cout << "Some error has occured." << endl;
			}

		} while (user_input != 5);

		Quit();
	}
}

void SmartCarrier::Menu() const
{
	cout << "\n\t" + carrier_name + " ACCOUNT ADMIN\n" << endl;
	cout << "1. List all accounts and their messages' usages" << endl;
	cout << "2. Add a message to an account" << endl;
	cout << "3. Purge large messages from an account" << endl;
	cout << "4. Disconnect an account" << endl;
	cout << "5. Quit" << endl;
}

int SmartCarrier::GetChoice() const
{
	string input;
	cout << "Select an option (1-5): ";
	getline(cin, input);
	return stoi(input);
}

void SmartCarrier::ListAccounts() const
{
	map<string, vector<Message<Media>*>>::const_iterator account_iter;
	vector<Message<Media>*>::const_iterator message_iter;

	cout << "\nAccount\t\tTotal messages\t\tTotal message's sizes(MB)\t   Charge(dollar)" << endl;

	for (account_iter = account_list.begin(); account_iter != account_list.end(); ++account_iter)
	{
		double total_size = 0.0;
		double total_charge = 0.0;

		cout << "\n" + account_iter->first + "\t\t" << account_iter->second.size() << "\t\t\t";
		for (message_iter = account_iter->second.begin(); message_iter != account_iter->second.end(); ++message_iter)
		{
			total_size += (*message_iter)->get_data().get_size();
			total_charge += (*message_iter)->get_data().GetCharge();
		}
		cout << setprecision(2) << fixed << total_size << "\t\t\t\t" << total_charge << endl;
	}
}

void SmartCarrier::InsertMessage()
{
	string input;
	string phone_numer;
	double media_size;
	string number_to;

	cout << "Enter a phone number: ";
	getline(cin, phone_numer);

	map<string, vector<Message<Media>*>>::iterator account_iter;
	account_iter = account_list.find(phone_numer);
	if (account_iter != account_list.end())
	{
		cout << "Enter the media size: ";
		getline(cin, input);
		media_size = stod(input);
		cout << "Enter the phone number you are sending to: ";
		getline(cin, number_to);

		account_list[phone_numer].push_back(new Message <Media>(number_to, Media(media_size)));
	}
	else {
		throw AccountNotFoundException(phone_numer);
	}
}

void SmartCarrier::PurgeLargeMessages()
{
	string phone_numer;
	double purge_size = 0.0;

	cout << "Enter a phone number: ";
	getline(cin, phone_numer);

	map<string, vector<Message<Media>*>>::iterator account_iter;
	account_iter = account_list.find(phone_numer);

	if (account_iter != account_list.end())
	{
		vector<Message<Media>*>::iterator message_iter;
		for (message_iter = account_iter->second.begin(); message_iter != account_iter->second.end(); ++message_iter)
		{
			if ((*message_iter)->get_data().get_size() >= Media::SIZE_THRESHOLD)
			{				
				purge_size += (*message_iter)->get_data().get_size();
				delete (*message_iter);
				account_iter->second.erase(message_iter);

				if (account_iter->second.size() != 0)
					message_iter = account_iter->second.begin();
				else
					break;
			}
		}

		cout << purge_size << "MB of messages have been purged from the account." << endl;
	}
	else {
		throw AccountNotFoundException(phone_numer);
	}
}

void SmartCarrier::DisconnectAccount()
{
	string phone_numer;

	cout << "Enter a phone number: ";
	getline(cin, phone_numer);

	map<string, vector<Message<Media>*>>::iterator account_iter;
	account_iter = account_list.find(phone_numer);

	if (account_iter != account_list.end())
	{
		vector<Message<Media>*>::iterator message_iter;
		for (message_iter = account_iter->second.begin(); message_iter != account_iter->second.end(); ++message_iter)
		{
			delete (*message_iter);
		}
		account_iter->second.clear();
		account_list.erase(account_iter);
	}
	else {
		throw AccountNotFoundException(phone_numer); 
	}
}

void SmartCarrier::Quit() const { cout << "Thank you for using our service!" << endl; }