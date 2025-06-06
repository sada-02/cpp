#include "bits/stdc++.h"
using namespace std;

// static var created at start of program and destroyed at the end of the program
int getID() {
    static int l_id {0};
    return ++l_id;
}

struct normalval{
    int val {1} ;
};

// static variable are there even when there is no object declared as they are not bounded to an object
struct staticval {
    static int val;
};

// Static members are global variables that live inside the scope region of the class so this is how we access it 
// without using an object  
int staticval::val {1};

class Foo{
    private :
    // static int m_val {1}; // error invalid initialisation
    // static const int m_val {-1}; // this works
    static inline int m_val {-2}; // this works
    int m_lol;

    public :
    static int pubval;

    int getVal() {
        return m_val;
    }

    // static member function
    static int getpVal() {
        // remember you can't pass non static values also they have no this pointer
        return m_val;
    }

    static void updateVal() ;
};

int Foo::pubval {-20}; // this also works for initialisation
void Foo::updateVal() {
    m_val++;
}

// a friend class or function is given full access to private as well as protected members
class Calculator{
    private :
    int m_val{-1};
    int m_res{3};

    public :
    // one way of defining
    friend void printc(const Calculator& t) {
        cout<<"val : "<<t.m_val<<" res : "<<t.m_res<<endl;
    }

    // other way
    friend int addValRes(const Calculator& t);
};

int addValRes(const Calculator& t) {
    return t.m_res + t.m_val;
}

// a non member function can be friend to multiple classes
// prefer using a non friend fn instead of friend
class Humidity; // forward declaration of Humidity
class Temperature{
private:
    int m_temp { 0 };
public:
    explicit Temperature(int temp) : m_temp { temp } { }

    friend void printWeather(const Temperature& temperature, const Humidity& humidity); // forward declaration needed 
};

class Humidity{
private:
    int m_humidity { 0 };
public:
    explicit Humidity(int humidity) : m_humidity { humidity } {  }

    friend void printWeather(const Temperature& temperature, const Humidity& humidity);
};

void printWeather(const Temperature& temperature, const Humidity& humidity){
    cout << "The temperature is " << temperature.m_temp <<" and the humidity is " << humidity.m_humidity << endl;
}

// friend class that can access private and protected members of the other class
class Storage {
private:
    int m_nValue {};
    double m_dValue {};
public:
    Storage(int nValue, double dValue) : m_nValue { nValue }, m_dValue { dValue }{ 

       }

    // Make the Display class a friend of Storage acts as both forward declareation and friend declaration
    friend class Display;
};

class Display{
private:
    bool m_displayIntFirst {};

public:
    Display(bool displayIntFirst) : m_displayIntFirst { displayIntFirst } {

    }

    // Because Display is a friend of Storage, Display members can access the private members of Storage
    void displayStorage(const Storage& storage) {
        if (m_displayIntFirst) cout << storage.m_nValue << ' ' << storage.m_dValue <<endl;
        else cout << storage.m_dValue << ' ' << storage.m_nValue <<endl;
    }

    void setDisplayIntFirst(bool b) {
         m_displayIntFirst = b;
    }
};

// We can also make particular member functions as friends
/*
class Display; // forward declaration for class Display

class Storage
{
private:
	int m_nValue {};
	double m_dValue {};
public:
	Storage(int nValue, double dValue)
		: m_nValue { nValue }, m_dValue { dValue }
	{
	}

	// Make the Display::displayStorage member function a friend of the Storage class
	friend void Display::displayStorage(const Storage& storage); // error: Storage hasn't seen the 
    full definition of class Display
};

class Display
{
private:
	bool m_displayIntFirst {};

public:
	Display(bool displayIntFirst)
		: m_displayIntFirst { displayIntFirst }
	{
	}

	void displayStorage(const Storage& storage)
	{
		if (m_displayIntFirst)
			cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
		else // display double first
			cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
	}
};

int main()
{
    Storage storage { 5, 6.7 };
    Display display { false };
    display.displayStorage(storage);

    return 0;
}

This won't work as Storage needs to first see the full definition of Display class
*/

/*
class Storage; // forward declaration for class Storage

class Display
{
private:
	bool m_displayIntFirst {};

public:
	Display(bool displayIntFirst)
		: m_displayIntFirst { displayIntFirst }
	{
	}

	void displayStorage(const Storage& storage); // forward declaration for Storage needed for reference here
};

class Storage // full definition of Storage class
{
private:
	int m_nValue {};
	double m_dValue {};
public:
	Storage(int nValue, double dValue)
		: m_nValue { nValue }, m_dValue { dValue }
	{
	}

	// Make the Display::displayStorage member function a friend of the Storage class
	// Requires seeing the full definition of class Display (as displayStorage is a member)
	friend void Display::displayStorage(const Storage& storage);
};

// Now we can define Display::displayStorage
// Requires seeing the full definition of class Storage (as we access Storage members)
void Display::displayStorage(const Storage& storage)
{
	if (m_displayIntFirst) cout << storage.m_nValue << ' ' << storage.m_dValue <<endl;
	else cout << storage.m_dValue << ' ' << storage.m_nValue <<endl;
}

int main() {
    Storage storage { 5, 6.7 };
    Display display { false };
    display.displayStorage(storage);

    return 0;
}

this code will function properly
*/

// ref-qualifier that allows us to overload a member function based on whether it is being called on an lvalue or an
// rvalue implicit object
class Employee {
private:
	string m_name{};

public:
	Employee(string_view name): m_name { name } {}

	const string& getName() const &  { 
        cout<<"lvalue"<<endl;
        return m_name; 
    } //  & qualifier overloads function to match only lvalue implicit objects
	string getName() const && {
        cout<<"rvalue"<<endl;
        return m_name; 
        } // && qualifier overloads function to match only rvalue implicit objects
};
// non-ref-qualified overloads and ref-qualified overloads cannot coexist
// deleting the rvalue-qualified version prevents use of the function with rvalue implicit objects

// createEmployee() returns an Employee by value (which means the returned value is an rvalue)
Employee createEmployee(string_view name) {
	Employee e { name };
	return e;
}
int main() {
    cout<<getID()<<endl;
    cout<<getID()<<endl;
    cout<<getID()<<endl;

    // now no need to instantiate an object to access variable
    cout<<Foo::getpVal()<<endl;
    Foo::updateVal();
    cout<<Foo::getpVal()<<endl;

    normalval aaa {} , bbb {};
    aaa.val = 2;
    cout<<aaa.val<<" "<<bbb.val<<endl;

    // all the objects share the same static variable
    staticval saaa {} , sbbb {};
    saaa.val = 2;
    cout<<saaa.val<<" "<<sbbb.val<<endl;

    Foo x;
    cout<<x.getVal()<<endl;
    cout<<x.pubval<<endl;

    Calculator p{};
    printc(p);
    cout<<addValRes(p)<<endl;
    
    Humidity hum { 10 };
    Temperature temp { 12 };
    printWeather(temp, hum);

    Storage storage { 5, 6.7 };
    Display display { false };
    display.displayStorage(storage);
    // even though Display is friend of Storage it don't have access to this pointer of storage (as fn parameter)
    display.setDisplayIntFirst(true);
    display.displayStorage(storage);

    Employee joe { "Joe" };
	cout << joe.getName() << '\n'; // Joe is an lvalue, so this calls string& getName() & (returns a reference)
	cout << createEmployee("Frank").getName() << '\n'; // Frank is an rvalue, so this calls string getName() && 
    // (makes a copy)
    
    return 0;
}