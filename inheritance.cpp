#include <bits/stdc++.h>
using namespace std;

/*
Under inheritance we are basically just extending the class in a seperate class
class being inherited from is called the parent class, base class, or superclass, and the class doing the inheriting 
is called the child class, derived class, or subclass.

the most-base class (at the top of the inheritance tree) is constructed. Then each child class is constructed in 
order, until the most-child class (at the bottom of the inheritance tree) is constructed last.

C++ prevents classes from initializing inherited member variables in the member initializer list of a constructor. 
Value of a member variable can only be set in a member initializer list of a constructor belonging to the same class 
as the variable.
why does it do this -> because of const and reference variables -> ensures that all variables are initialised once

Destructor is called in the reverse order as the constructors are beiing called

Private members can be accessed by friends and base members but not by derieved classes
Protected can be accessed by derieved classes

when resolving functions we first look at the overloaded versions of the function defined in the derrieved class 
and then move sequential to the base class following same procedures
this means we can change the behaviour of the functions

Mixin -> small functions that can be inherited to add functionalities
*/

class Person {
    public :
    string name {};
    int age {};

    // Person() = default;

    Person(string s = "", int v = 21) : name {s} , age {v} {
        cout<<"Person was Created"<<endl;
    }

    void infoPerson() {
        cout<<"Name : "<<name<<" Age : "<<age<<endl;
    }
};

// all the behaviours and properties of person are inherited by employee
class Employee : public Person {
    public :
    int salary {};
    int empID {};

    // Employee() = default;

    Employee(int wage = 0 , int id = 1000) : salary {wage} , empID {id} {
        cout<<"Employee was created"<<endl;
    }

    void infoEmp() {
        cout<<"Salary : "<<salary<<" empID : "<<empID<<endl;
    }
};

// inherites person also 
class CEO : public Employee {
    public :
    int stage {};

    CEO(int s , int salary , int id) : stage {s} , Employee(salary,id) {
        cout<<"CEO was created"<<endl;
    } 

    void infoCEO() {
        cout<<"Stage of being CEO : "<<stage<<endl;
    }
};

class A{
    private:
    int m_private {};
    public :
    int m_public {};
    protected :
    int m_protected {};

};

class B : public A {
    // public , protected remains same while private is inaccessible
    public :
    B() {
        m_public = 1;
        m_protected = 2;
        // m_private = 3; // inaccessible
    }
};

class C : protected A {
    // public and protected -> protected while private s inaccessible
    public :
    C() {
        m_public = 1;
        m_protected = 2;
        // m_private = 3; // inaccessible
    }
};

class D : private A {
    // public and protected -> private while private s inaccessible
    public :
    D() {
        m_public = 1;
        m_protected = 2;
        // m_private = 3; // inaccessible
    }
};

// remember base has no access to derieved functionalities

class foott{
    public :
    void print(int v) {
        cout<<"foo::print(int)"<<endl;
    }
    void print(double v) {
        cout<<"foo::print(double)"<<endl;
    }
};

class boott: public foott {
    public:
};


class footti{
    public :
    void print(int v) {
        cout<<"foo::print(int)"<<endl;
    }
    void print(double v) {
        cout<<"foo::print(double)"<<endl;
    }
};

class bootti: public footti {
    public:
    void print(double) {
        cout<<"boo::print(double)"<<endl;
    }
};

class foo{
    public :
    void print(int v) {
        cout<<"foo::print(int)"<<endl;
    }
    void print(double v) {
        cout<<"foo::print(double)"<<endl;
    }
};

class boo: public foo {
    public:
    void print(double v) {
        cout<<"boo::print(double)"<<endl;
        // adding existing functionalities to base function here 
        foo::print(v);

        // we do not use print() -> loops in recursion
    }
};

class fooq{
    public :
    void print(int v) {
        cout<<"foo::print(int)"<<endl;
    }
    void print(double v) {
        cout<<"foo::print(double)"<<endl;
    }
};

class booq: public fooq {
    public:
    void print(double v) {
        cout<<"boo::print(double)"<<endl;
    }
    // this allows to level the level of overloading among the functions
    using fooq::print;
};

// we can change the access level of the inherited members but not the ones that are private
// you can change access to private to hide the members but it would hide all overloads
// we can also use delete to remove specific overloads
class pvt{
    protected :
    int m_val {};
};

class pub : public pvt{
    public:
    using pvt::m_val;
};

class P{
    public :
    int m_p {};
};
class Q{
    public :
    int m_q {};
};
class R : public P , public Q{ // multiple inheritence
    public :
    int m_r {};
};

class AAA {
    public:
    void print() {
        cout<<"Hello AAA"<<endl;
    }
};
class BBB {
    public:
    void printbbb() {
        cout<<"Hello BBB"<<endl;
    }
};
class AA : public AAA {
    public:
    void printaa() {
        cout<<"Hello AA"<<endl;
    }
};
class BB : public BBB {
    public:
    void print() {
        cout<<"Hello BB"<<endl;
    }
};

class K : public AA , public BB {
    public :
    int m_val {};
};

// Diamond problem
class diamondhead{
    public:
    void print() {
        cout<<"Diamond"<<endl;
    }
};

class diamondleft : public diamondhead {
    public :
    int left {};
};
class diamondright : public diamondhead {
    public :
    int right {};
};
class diamond : public diamondleft , public diamondright {
    public :
    int diamund {};
};

int main() {
    Employee x(200,23);
    x.name = "Lol";

    CEO cx(5,3300,34);
    cout<<cx.salary<<endl;

    boott llll ;
    llll.print(8); // no matching function in boott so resolve to foott

    bootti lllll ;
    lllll.print(3); // best matching done in derivation order

    boo ll ;
    ll.print(4.3);

    booq lll ;
    lll.print(3);

    pub vvvvv;
    vvvvv.m_val = 9;

    K k ;
    // k.print(); // gives ambiguous match here order of inheritence is not being checked

    diamond d ;
    // d.print(); // diamond problem -> ambiguous match can be solved by scoping though
    d.diamondleft::print(); // works
    return 0;
}