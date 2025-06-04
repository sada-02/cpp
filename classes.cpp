#include <bits/stdc++.h>
using namespace std;

/*
An object is piece of memory that can be used to store data.
An object with name is called variable
properties are represented as objects while behaviour is represented by functions
Class invariant is a condition that must be true throughout the lifetime of an object in order for the object to
remain in a valid state

Compiler goes from top to bottom 
So function needs to be first declared before using them
But in structs such an order does not matter but the use of variables might affect
what it does is just convert them into forward declarations and then at the end there is list of complete definitions

If the struct do not have any data then instead of creating objects it is good practice to use namespace to directly 
access the functions

In classes we have by default private declarations

Getter (accessors) -> return value of private members
setter (mutators) -> that set value of private members (mutators are broad term meaning it can modify the object)

member function have same rule for returning by reference as non member functions , returning value should not get 
destroyed after the function ends
third case is returning the data member -> if by value it can be expensive
it is safe to return these by refernce

constructors generally perform two functions:
They typically perform initialization of any member variables (via a member initialization list)
They may perform other setup functions (via statements in the body of the constructor). This might include things 
such as error checking the initialization values, opening a file or database, etc…

constructors are only for non aggregate type data

Constructors have same name as the class and no return type and are usually public
it do the implicit conversions

const effect of an object comes only after object is created not while it is under construction

*/

class Date{
    public :
    int year;
    int month;
    int day;

    void printDate() {
        cout<<year<<"/"<<month<<"/"<<day<<endl;
    }

    void printDateconst() const {
        // incrementDay(); // error can not call non const function from here
        // printDate();
        cout<<year<<"/"<<month<<"/"<<day<<endl;
    }

    void incrementDay() {
        day++;
    }
};

class FuncOrder{
    public :
    int x() {
        return y();
    }

    int y() {
        return 5;
    }
};

class Employee{
    // these are by default private
    string name;
    int age;
    int id;
    double salary;

    public :
    void SetInfo(const string& name , const int& age ,const int& id ,const double& salary) {
        this->name = name;
        this->age = age;
        this->id = id;
        this->salary = salary;
    }

    void addSalary(Employee& temp) {
        cout<<salary+temp.salary<<endl;
    }
};

// this throws error because of order of declaration
// int xx() {
//     return yy();
// }

// int yy() {
//     return 5;
// }

void printDate(const Date& d) {
    cout<<d.day<<"/"<<d.month<<"/"<<d.year<<endl;
}

namespace NoData {
    void printNoData() {
        cout<<"Nothing here to see"<<endl;
    }
};

class Data {
    private :
    int m_day {23};
    int m_month {3};
    int m_year {2023};

    public :
    const int& getYear() const {
        return m_year;
    }
    void setYear(int val) {
        m_year = val;
    }
    const int& getMonth() const {
        return m_month;
    }
    void setMonth(int val) {
        m_month = val;
    }
    const int& getDay() const {
        return m_day;
    }
    void setDay(int val) {
        m_day = val;
    }

    int& func() {
        return m_year;
    }
};

Data gettingData(const int& val) {
    Data temp;
    temp.setYear(val);
    return temp; // return of rvalue
}

class publicMemInit{
    public :
    int val;
    double vval;
};

class privateMemInit{
    private :
    int m_val;
    double m_vval;
};

class pubprvMemInit{
    public :
    int val;
    int vval;

    private :
    int m_val;
    double m_vval;
};

/*
Compiler looks for a matching constructor if not found then compile error
*/

int main() {
    Date x {2007 , 8 , 14};
    printDate(x);

    x.printDate(); // x is implicit object and it is passed implicitly to the printDate member function

    FuncOrder X;
    cout<<X.x()<<endl;

    // cout<<xx()<<endl;
    
    NoData::printNoData();

    const Date constx {2004 , 4 , 3} ;
    // constx.month++; // error
    // constx.incrementDay(); // error can not modify value directly or in directly
    // constx.printDate(); // error even though no change in data member here but still we are calling a non const 
    // function from a const variable
    // so to deal with this we need const member function -> will not modify the object or call any non const fn
    // this must be at both declaration and at definition time

    constx.printDateconst();

    // Employee emp {"Hello" , 42 , 34 , 34431.41}; // error as private data members

    Employee emp1 {} , emp2 {};
    emp1.SetInfo("Hello" , 42 , 34 , 34431.41);
    emp2.SetInfo("Hello Moto" , 24 , 43 , 341.41);

    emp1.addSalary(emp2);
    // remember private is per class based not per object based
    // emp1 member function is able to access emp2 private values

    Data p {};
    cout<<p.getYear()<<endl;
    p.setYear(2025);
    cout<<p.getYear()<<endl;

    cout<<gettingData(3021).getYear()<<endl; // works fine returns rvalue as after the getYear the full expression 
    // ends and rvalue object and its members are destroyed 

    // const int& ref = gettingData(3302).getYear() ; // now this is left dangling
    // cout<<ref<<endl;

    int val = gettingData(3021).getYear(); // now safe as it is copy
    cout<<val<<endl;

    // important do not return non const references to private members
    int& vv = p.func();
    vv = 9 ;
    cout<<p.getYear()<<endl;
    // what is the point of access control then

    // int& pp = p.getDay(); // cannot bind non const reference to const member function

    publicMemInit wiilwork {1 , 1.1}; // aggregate init works here
    // privateMemInit wiilnotwork {1 , 1.1}; // aggregate init does not work here error
    // pubprvMemInit notwork {21 , 3.2};

    return 0;
}