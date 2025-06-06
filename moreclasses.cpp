#include "bits/stdc++.h"
// #include "date.h"
using namespace std;

/*
Holds the address of current implicit object

What we write vs what compiler makes it
simple.setID(2); -> Simple::setID(&simple, 2);
void setID(int id) { m_id = id; } -> static void setID(Simple* const this, int id) { this->m_id = id; }

static does not mean it is associated with object rather it a normal fn defined in scope region of class
this is a const pointer meaning it cannot point to any other object but its state can be modified
this is just fn parameter not a member 

Function chaning calling several member function on the same object in a single expression

For non-const member functions, this is a const pointer to non const value while for const member fns these are const 
pointer to const value 

Other than data members and member functions we have nested types

There can only be one destructor , they have no parameters and return value
remember static variable are defined at program startup and ends when program terminates

~<> () {} -> default destructor
exit() -> terminates program immediately , local variables are not destroyed and hence no destructors are called.
Any unhandled exception that leads to program termination without unwinding the stack can result to never calling 
the destructors 
*/

// class Foo;
// class Foo::inner1; // compile error can not be declared before outer class definition

class Foo{
    // nested typedefs and type aliases
    private:
    using TypeID = int;
    int m_val;
    int m_lol;
    int m_sum;
    TypeID m_id;

    public:
    using ExpilicitType = int;

    Foo() = default;
    Foo(int val , int lol , int sum);

    ~Foo() {
        cout<<"Destructor are called on id : "<<m_id<<endl;
    }

    void print() const ;

    int getVal() {
        return this->m_val;
    }
    int getSum() {
        return this->m_sum;
    }
    //same
    int getLol() {
        return m_lol; // this implicitly converts to this->m_lol
    }
    TypeID getID() {
        return this->m_id;
    }

    void setVal(int val) {
        this->m_val = val;
    }
    void setSum(int sum) {
        this->m_sum = sum;
    }
    // same
    void setLol(int lol) {
        m_lol = lol;
    }
    void setID(TypeID id) {
        m_id = id;
    }

    Foo& add(int sum) {
        m_sum+=sum;
        return *this;
    }
    Foo& sub(int sum) {
        m_sum-=sum;
        return *this;
    }
    Foo& mul(int sum) {
        m_sum*=sum;
        return *this;
    }

    void reset() { // this creates new object that is assigned to this implicit object with defaults
        *this = {};
    }

    class FooFoo{
        public :
        // nested class do not have access to the this pointer of the outer class but can access private members
        void print(const Foo& temp) {// since no direct access to this
            cout<<temp.m_val<<" "<<temp.m_lol<<" "<<temp.m_sum<<" "<<temp.m_id<<endl;
        }
    };

    // class can be forward declared and then later defined within the class or outside
    // but cannot be declared before definition of the outer class
    class inside1;
    class inside1 {};
    class inside2;
};

class inside2{};

Foo::Foo(int val , int lol , int sum) : m_val {val} , m_lol {lol} , m_sum {sum}{
    cout<<"Constructor is called"<<endl;
}
void Foo::print() const {
    cout<<"val : "<<m_val<<" lol : "<<m_lol<<" sum : "<<m_sum<<endl;
}

/*
Unqualified name of a class within scope of the class is called injected class name which serves as a shorthand for 
fully templated name
*/

template <typename T>
class Pair{
    private:
    T m_first;
    T m_second;

    public:
    T getFirst() {
        return m_first;
    }
    T getSecond() {
        return m_second;
    }
    void setFirst(T val) {
        m_first = val;
    }
    void setSecond(T val) {
        m_second = val;
    }

    Pair(const T& first ,const T& second);
    void print();

    // the template parameter declaration belonging to the class applies
    bool comp(const Pair& temp) {
        if(temp.m_first == m_first && temp.m_second == m_second) return true;
        else return false;
    }
};

// When we define a member function outside the class definition -> resupply a template parameter declaration
template<typename T>    
Pair<T>::Pair(const T& first , const T& second) : m_first {first} , m_second {second} {

}

// full templated name Pair<T> is used
template<typename T>
void Pair<T>::print() {
    cout<<"("<<m_first<<" , "<<m_second<<")"<<endl;
}

int main() {
    Foo x ;
    x.setVal(5);
    x.setLol(-1);
    cout<<x.getLol()<<endl;
    cout<<x.getVal()<<endl;

    x.setSum(0);
    x.add(20).sub(10).mul(3); // chaining
    cout<<x.getSum()<<endl; 
    x.reset();
    cout<<x.getSum()<<endl; 

    x.setID(34);
    cout<<x.getID()<<endl;

    Foo::ExpilicitType value {x.getID()}; // here how you can access the nested typedefs
    cout<<value<<endl;

    Foo y(1,2,3);
    y.print();
    y.setID(32);
    // need to compile both of them now ufff
    // Date d {12,7,2019};
    // d.printDate();

    Foo::FooFoo p {};
    p.print(y);

    if(true) {
        Foo lao {4,5,6};
        lao.setID(90);
    }

    Pair vp(12,43) , qp(12,43);
    vp.print();
    if(vp.comp(qp)) {
        cout<<"Pairs are same"<<endl;
    }
    else {
        cout<<"Pairs are not same"<<endl;
    }

    return 0;   
}