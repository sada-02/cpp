#include <bits/stdc++.h>
using namespace std;

/*
Cannot define constructors in privvate section they are always public
members in member initalisation list are always initilised in the order they are defined inside the class to avoid 
unintended behaviour

If i have const members then initialisation list will be used if you use assignments it won't work

If no constructor present then compiler makes a implicit default constructor that is empty having no parameters ,
no member initialisation list and statements    

Initialisation of objects is completed once initialisation list gets finished.

copy constructor is a constructor that is used to initialize an object with an existing one
After copy constructor is runned , the object created is copy of the original object

A copy constructor should not do anything other than copy an object. This is because the compiler may optimize the
copy constructor out in certain cases. If you are relying on the copy constructor for some behavior other than just
copying, that behavior may or may not occur

Copy elision is a compiler optimization technique that allows the compiler to remove unnecessary copying of objects.
Compiler is free to rewrite the code to prevent executing copy constructor
that is why copy constructors should not have any side effects as they might not get executed 
*/

class Foo{
    private:
    int m_val;
    double m_d;

    public :
    // implicitly doing have a problem that it don't default initialize all the values
    // Foo() {
    // }

    // Foo() = default; // to forcefully generate implicit constructor
    // default values if all parameters have default values then it becomes default constructor
    Foo(int val, double d=3.4) : m_val {val} , m_d {d} { // member initialisation list m_val = val does not work
        cout<<"This is constructor"<<endl;
        cout<<"val : "<<m_val<<" d : "<<m_d<<endl;
        // m_val = val ; // this is assignment not working for const
        // m_d = d ; 
    }
    
    Foo() { 
        cout<<"This default constructor and is called at both value and default initialisation"<<endl;
    }

    void print() {
        cout<<"val : "<<m_val<<" d : "<<m_d<<endl;
    }
};

class Boo{
    int m_val {};
    int m_del {};

    public:
    Boo(int val) : m_val {val} {
        cout<<"Only val"<<endl;
    } 

    Boo(int val , int del) : m_del {del} {
        cout<<"Both val and del"<<endl;
        // Boo(val); // creates a temporary object that is deleted once it is finished also the val value is 
        // initialised in that temp obj and the main obj is never initialised with this
    }

    void printval() {
        cout<<"val : "<<m_val<<" del : "<<m_del<<endl;
    }
};

// delegates -> transfer responsibility for initialisation to another constructor (constructor chaining)
// at a time a constructor can either initialize values or delegate to other constructor bot not simultaneously
class Lol{
    private :
    int m_val;
    int m_temp;

    public :
    explicit Lol(int val) : Lol{val, -1} { // delegates 
        // first instructions in the called one is called after this caller is called
        cout<<"Single Valued Called"<<endl;
    }

    Lol(int val , int temp) : m_val {val} , m_temp {temp} { 
        // by doing this there is no way to refer to default initialisation value
        // generally fns with lesser parameters are delegated to larger ones
        cout<<"Double Valued Called"<<endl;
        cout<<"val : "<<m_val<<" temp : "<<m_temp<<endl;
    }

    // user defined explicit constructor , it must be const <>& type 
    Lol(const Lol& temp) : m_val {temp.m_val} , m_temp {temp.m_temp} {
        cout<<"Copy constructor is called"<<endl;
    }

    // Lol(const Lol& temp) = delete; // to prevent copy initialisation

    int getVal() {
        return m_val;
    }
    int getTemp() {
        return m_temp;
    }

};

void print(Lol temp) {
    cout<<temp.getVal()<<" "<<temp.getTemp()<<endl;
}

Lol createLOL() {
    Lol p {2,4};
    return p; // temp value
    // return Lol {2,4}
}

// Lol getLol() {
//     return 5 ;
// }

Lol getLoll() {
    return {5,5} ;
}

int main() {
    Foo x(5,9.4);
    // x.print();

    // these call same constructors it is always safe to use value initialisation always 
    Foo ywqdscndwav {};
    Foo zcdabvaibv;

    Boo t(10) ;
    t.printval();

    Lol y(5);
    print(Lol {5,6}); // temperory object when the function return temp object is destroyed
    
    char temp {'a'};

    cout<<static_cast<int>(temp)<<endl; // temp obj with direct initialisation
    // prefered when narrowing conversion

    cout<<int(temp)<<endl; // temp obj with C-style , dangerous to work with
    cout<<int{temp}<<endl; // temp obj with list initialisation

    Lol yo {y}; // this create implicit copy constructor if we haven't defined one
    cout<<yo.getVal()<<endl;

    print(yo); // here copy initialisation would be called when passed by value
    Lol val {createLOL()}; // here copy initialisation is not being called idk why in learncpp it has been called 
    // twice , once when p is returned and stored in temperory variable and then to init val with temp var
    // oh i know got it , these are being elided

    print({4,4}); // constructor act as implicit conversions and such are called converting constructors
    // first temp and then copy init these have been elided now 

    // remember only one user defined conversion can work at a time for example use string_view and string

    // making an constructor explicit unables them to make user defined conversions used only on declaration
    // print(8); // compile error now

    // Lol vaal {getLol()}; // compile error
    Lol vall (getLoll()); // workss as no problem of explicit
    return 0;  
}