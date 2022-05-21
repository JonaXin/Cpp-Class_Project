//-----------------------------------------------------------------------------
//  Date: 02-21-2021
//  Program purpose: This program simulates an address book for a company to 
//                   store their employees'/contractors' contact information.
//  Disclaimer: If this program is working it's written by the author below.
//              If it is not I don't know who wrote it.
//  Revision history:
//  Date             Programmer            Change ID     Description
//  02/21/21         Jonathan Xin          1000          Initial implementation
//-----------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Name {

private:
    string first_name;
    string last_name;
public:
    static const string DEFAULT_FIRST_NAME;
    static const string DEFAULT_LAST_NAME;
public:
    Name();
    Name(string first_name, string last_name);
    ~Name();

    string get_first_name() const;
    string get_last_name() const;
    void set_first_name(string first_name);
    void set_last_name(string last_name);
    bool operator== (const Name& right) const;
};

class Contact
{
private:
    Contact* next;
protected:
    Name name;
    string business_phone;
    string email;
    int location;
public:
    static const string DEFAULT_BUSINESS_PHONE;
    static const string DEFAULT_EMAIL;
    static const int DEFAULT_LOCATION;
public:
    Contact();
    Contact(string first_name, string last_name, string business_phone, string email, int location);
    virtual ~Contact();

    Contact* get_next() const;
    Name get_name() const;
    string get_business_phone() const;
    string get_email() const;
    int get_location() const;
    void set_next(Contact* p_contact);
    void set_name(Name name);
    void set_business_phone(string business_phone);
    void set_email(string email);
    void set_location(int location);
    virtual void ShowContact() const = 0;
};

class EmployeeContact : public Contact
{
private:
    string title;
    string department;
public:
    static const string DEFAULT_TITLE;
    static const string DEFAULT_DEPARTMENT;

    EmployeeContact();
    EmployeeContact(string first_name, string last_name, string business_phone, string email,
        int location, string title, string department);
    virtual ~EmployeeContact();
    string get_title() const;
    string get_department() const;
    void set_title(string title);
    void set_department(string department);
    virtual void ShowContact() const;
};

class ContractorContact : public Contact
{
private:
    string company_from;
    int assignment_duration;
public:
    static const string DEFAULT_COMPANY_FROM;
    static const int DEFAULT_DURATION;

    ContractorContact();
    ContractorContact(string first_name, string last_name, string business_phone, string email,
        int location, int assignment_duration, string company_from);
    virtual ~ContractorContact();
    string get_company_from() const;
    int get_assignment_duration() const;
    void set_company_from(string company_from);
    void set_assignment_duration(int assignment_duration);
    virtual void ShowContact() const;
};

class ContactList
{
private:
    Contact* head;
public:
    ContactList();
    ~ContactList();
private:
    Contact* FindContact(const Name& name) const;
    void Insert(Contact* p_contact);
public:
    void Init();
    void ShowAllContacts() const;
    void SearchByName(const Name& name) const;
    void SearchByDepartment(string department) const;
};

class AddressBook
{
private:
    string company_name;
    ContactList contact_list;
public:
    static const string DEFAULT_COMPANY_NAME;

    AddressBook();
    AddressBook(string company_name);
    ~AddressBook();
    void Init();
    void Run() const;
private:
    void Menu() const;
    int GetUserOption() const;
    void ShowAllContacts() const;
    void SearchByName() const;
    void SearchByDepartment() const;
    void Quit() const;
    void ErrorMessage() const;
};


const string Name::DEFAULT_FIRST_NAME = "FirstName";
const string Name::DEFAULT_LAST_NAME = "LastName";
const string Contact::DEFAULT_BUSINESS_PHONE = "1-000-000-0000";
const string Contact::DEFAULT_EMAIL = "default@email.com";
const int Contact::DEFAULT_LOCATION = 10;
const string EmployeeContact::DEFAULT_TITLE = "Employee";
const string EmployeeContact::DEFAULT_DEPARTMENT = "Default Department";
const string ContractorContact::DEFAULT_COMPANY_FROM = "Default Company FROM";
const int ContractorContact::DEFAULT_DURATION = 0;
const string AddressBook::DEFAULT_COMPANY_NAME = "Default Company";


int main()
{
    AddressBook* TP_Communications = new AddressBook("TP Communications");
    TP_Communications->Init();
    TP_Communications->Run();
    delete TP_Communications;
}

Name::Name():first_name(Name::DEFAULT_FIRST_NAME), last_name(Name::DEFAULT_LAST_NAME) {}
Name::Name(string first_name, string last_name):first_name(first_name), last_name(last_name) {}
Name::~Name() {}
string Name::get_first_name() const { return first_name; }
string Name::get_last_name() const { return last_name; }
void Name::set_first_name(string first_name) { this->first_name = first_name; }
void Name::set_last_name(string last_name) { this->last_name = last_name; }
bool Name::operator== (const Name& right) const
{
    bool is_equal = true;

    if (this->first_name.size() != right.first_name.size() || this->last_name.size() != right.last_name.size())
        return false;

    for (int i = 0; i < this->first_name.size(); i++)
    {
        if (tolower(this->first_name[i]) != tolower(right.first_name[i]))
            is_equal = false;
    }

    for (int i = 0; i < this->last_name.size(); i++)
    {
        if (tolower(this->last_name[i]) != tolower(right.last_name[i]))
            is_equal = false;
    }

    return is_equal;
}


Contact::Contact() :next(nullptr), name(), business_phone(Contact::DEFAULT_BUSINESS_PHONE),
    email(Contact::DEFAULT_EMAIL), location(Contact::DEFAULT_LOCATION) {}

Contact::Contact(string first_name, string last_name, string business_phone, string email, int location):
    next(nullptr), name(first_name, last_name), business_phone(business_phone), email(email), location(location) {}

Contact::~Contact() { cout << name.get_first_name() + " " << name.get_last_name() << " has gone home ..." << endl; }

Contact* Contact::get_next() const { return next; }
Name Contact::get_name() const { return name; }
string Contact::get_business_phone() const { return business_phone; }
string Contact::get_email() const { return email; }
int Contact::get_location() const { return location; }
void Contact::set_next(Contact* p_contact) { this->next = p_contact; }
void Contact::set_name(Name name) { this->name = name; }
void Contact::set_business_phone(string business_phone) { this->business_phone = business_phone; }
void Contact::set_email(string email) { this->email = email; }
void Contact::set_location(int location) { this->location = location; }


EmployeeContact::EmployeeContact() : Contact(), title(EmployeeContact::DEFAULT_TITLE),
    department(EmployeeContact::DEFAULT_DEPARTMENT) {}

EmployeeContact::EmployeeContact(string first_name, string last_name, string business_phone, string email,
                                 int location, string title, string department) :
    Contact(first_name, last_name, business_phone, email, location), title(title), department(department) {}

EmployeeContact::~EmployeeContact() {}
string EmployeeContact::get_title() const { return title; }
string EmployeeContact::get_department() const { return department; }
void EmployeeContact::set_title(string title) { this->title = title; }
void EmployeeContact::set_department(string department) { this->department = department; }
void EmployeeContact::ShowContact() const
{
    string spaces = "    ";

    cout << "------------------------------------------------------------------------------------------------------" << endl;
    cout << name.get_first_name() + " " + name.get_last_name() + spaces + title + spaces + department
        + spaces + "Room " << location << spaces + business_phone + spaces + email << endl;
    cout << "------------------------------------------------------------------------------------------------------\n" << endl;
}


ContractorContact::ContractorContact() : Contact(), company_from(ContractorContact::DEFAULT_COMPANY_FROM),
    assignment_duration(ContractorContact::DEFAULT_DURATION) {}

ContractorContact::ContractorContact(string first_name, string last_name, string business_phone, string email,
                                     int location, int assignment_duration, string company_from) :
    Contact(first_name, last_name, business_phone, email, location),
    assignment_duration(assignment_duration), company_from(company_from) {}

ContractorContact::~ContractorContact() {}
string ContractorContact::get_company_from() const { return company_from; }
int ContractorContact::get_assignment_duration() const { return assignment_duration; }
void ContractorContact::set_company_from(string company_from) { this->company_from = company_from; }
void ContractorContact::set_assignment_duration(int assignment_duration) { this->assignment_duration = assignment_duration; }
void ContractorContact::ShowContact() const
{
    string spaces = "    ";

    cout << "------------------------------------------------------------------------------------------------------" << endl;
    cout << name.get_first_name() + " " + name.get_last_name() + spaces << assignment_duration << " months (contractor)" 
        + spaces + company_from + spaces + "Room " << location << spaces + business_phone + spaces + email << endl;
    cout << "------------------------------------------------------------------------------------------------------\n" << endl;
}


ContactList::ContactList() : head(nullptr) {}
ContactList::~ContactList()
{
    Contact* p_contact = head;// ->get_next();
    while (p_contact != nullptr)
    {
        Contact* next = p_contact->get_next();
        delete p_contact;
        //head = p_contact;
        p_contact = next;//head->get_next();
    }
    //delete head;
}

Contact* ContactList::FindContact(const Name& name) const
{
    Contact* p_contact = head;

    while (p_contact != nullptr) {
        if (p_contact->get_name() == name)
            return p_contact;
        p_contact = p_contact->get_next();
    }
    return nullptr;
}

void ContactList::Insert(Contact* p_contact)
{
    p_contact->set_next(head);
    head = p_contact;
}

void ContactList::Init()
{
    Insert(new EmployeeContact("David", "Summer", "1-408-790-1682", "davids@tpcommuniations", 23, "Software Engineer", "Engineering"));
    Insert(new EmployeeContact("Jennifer", "Hans", "1-408-790-2381", "jenniferh@tpcommuniations", 17, "HR Representative", "Human Resources"));
    Insert(new ContractorContact("Cindy", "Morgan", "1-408-790-3953", "cindym@tpcommuniations", 43, 12, "TK Consultings"));
    Insert(new EmployeeContact("Steven", "Murphy", "1-408-790-1234", "stevenm@tpcommuniations", 21, "Test Technician", "Engineering"));
    Insert(new EmployeeContact("Adam", "Smith", "1-408-790-4321", "adams@tpcommuniations", 10, "IT Technical Support", "IT"));
    Insert(new ContractorContact("Logan", "Sling", "1-408-790-5521", "logans@tpcommuniations", 26, 10, "Brothers Inc"));
    Insert(new ContractorContact("Smith", "Lora", "1-408-790-3111", "smithl@tpcommuniations", 28, 7, "Widdle Union"));
    Insert(new ContractorContact("Jackson", "Dinky", "1-408-790-3222", "cindym@tpcommuniations", 31, 6, "SSS"));
    Insert(new EmployeeContact("Calvin", "Clay", "1-408-790-1111", "calvinc@tpcommuniations", 13, "Hardware Engineer", "Engineering"));
    Insert(new EmployeeContact("Tim", "Antonie", "1-408-790-2222", "tima@tpcommuniations", 17, "Director", "Administration"));
    Insert(new ContractorContact("Zack", "Burg", "1-408-790-3333", "zackb@tpcommuniations", 19, 4, "In-Tech"));
    Insert(new ContractorContact("Cecilia", "Lyn", "1-408-790-4444", "cecilial@tpcommuniations", 7, 4, "Apple"));
    Insert(new ContractorContact("Mary", "Lu", "1-408-790-5555", "maryl@tpcommuniations", 5, 3, "Google"));
    Insert(new EmployeeContact("Lucy", "Seth", "1-408-790-6666", "lucys@tpcommuniations", 41, "Admin Assistant", "Administration"));
    Insert(new EmployeeContact("Becky", "Brook", "1-408-790-7777", "beckyb@tpcommuniations", 55, "Product Support Engineer", "Engineering"));
    Insert(new EmployeeContact("Joseph", "Long", "1-408-790-8888", "josephl@tpcommuniations", 22, "Business Analyst", "Marketing"));
}

void ContactList::ShowAllContacts() const
{
    Contact* p_contact = head;
    while (p_contact != nullptr)
    {
        p_contact->ShowContact();
        p_contact = p_contact->get_next();
    }
}

void ContactList::SearchByName(const Name &name) const
{
    Contact* p_contact = FindContact(name);
    if (p_contact != nullptr)
        p_contact->ShowContact();
    else {
        cout << "Sorry no match is found. \n" << endl;
    }
}

void ContactList::SearchByDepartment(string department) const
{
    int count = 0;
    Contact* p_contact = head;
    while (p_contact != nullptr)
    {
        EmployeeContact* p_employee = dynamic_cast<EmployeeContact*>(p_contact);
        if (p_employee != nullptr)
        {
            if (p_employee->get_department() == department)
            {
                p_employee->ShowContact();   
                count++;
            }
        }
        p_contact = p_contact->get_next();
    }

    if (count == 0)
        cout << "Sorry no match is found. \n" << endl;
}


AddressBook::AddressBook(): contact_list(), company_name(AddressBook::DEFAULT_COMPANY_NAME) {}
AddressBook::AddressBook(string company_name): contact_list(), company_name(company_name) {}
AddressBook::~AddressBook() {}

void AddressBook::Init()
{
    contact_list.Init();
}

void AddressBook::Run() const
{
    Menu();
    int option = GetUserOption();

    while (option != 4)
    {
        switch (option) {
        case 1:
            ShowAllContacts();
            break;
        case 2:
            SearchByName();
            break;
        case 3:
            SearchByDepartment();
            break;
        default:
            ErrorMessage();
        }

        Menu();
        option = GetUserOption();
    }

    Quit();
}

void AddressBook::Menu() const
{
    cout << "      " + company_name + " Address Book Menu\n" << endl;
    cout << "1. View all contacts " << endl << "2. Search by name" << endl
         << "3. Search by department " << endl << "4. Quit" << endl;
}

int AddressBook::GetUserOption() const
{
    string input;
    int option = -1;
    cout << "Select an option (1-4): ";
    getline(cin, input);
    if (isdigit(input[0]) && input.size() == 1)
        option = stoi(input);
    return option;
}

void AddressBook::ShowAllContacts() const { contact_list.ShowAllContacts(); }
void AddressBook::SearchByName() const
{
    string first_name;
    string last_name;

    cout << "Enter a contact first name: ";
    getline(cin, first_name);
    cout << "Enter a contact last name: ";
    getline(cin, last_name);

    Name name(first_name, last_name);
    contact_list.SearchByName(name);
}

void AddressBook::SearchByDepartment() const
{
    string department;

    cout << "Enter a department: ";
    getline(cin, department);

    contact_list.SearchByDepartment(department);
}

void AddressBook::Quit() const { cout << "Thanks for using our AddressBook. See you again!" << endl; }
void AddressBook::ErrorMessage() const { cout << "Invalid option.Please try again.\n" << endl; }
