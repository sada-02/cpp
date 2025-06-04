#include <bits/stdc++.h>
using namespace std;

/*
Compound datatypes - defined interms of other data types ,eg functions
Expression : a combination of literals , variables , operators and function calls that can be executed to produce 
singular value
Type of an expression - equivalent to type of value, object or function that results from the evaluated expression
It must be determinable at compile time.
Value of a expression - Whether an expression resolves to a value, function or object of some kind.

Type must be determinable at compile time while value can be determined at compile or run time.
*/

/*
Lvalue (left or locator value)
Expression that evaluates to an identifiable object or function.

An entity with identity can be differentiated from other similar entities and can accessed via an identifier, 
reference or pointer that persist beyond their expression.

Lvalue 
modifiable or non modifiable (const)

Rvalue (right value)
Evaluates to a value . Includes literals , return values of functions and operators that return by value.
These aren't identifiable (they have to be used immediately) only exist within the scope of expression in which they
are used.

operators expect there operands to be rvalues
= requires that left side is modifiable lvalue

lvalues can be used anywhere where where rvalue is required due to conversion from lvalue to rvalue
*/

/*
Lvalue refrence
To read and write on the object being refered to.
scope is same as that of variables

Lifetimes can be diiferent
A reference can be destroyed before the object it is referencing.
The object being referenced can be destroyed before the reference. -> leads to dangling pointers

References are not objects, does not occupy storage just an other name for the object
Because of this you can not have reference to reference.
When a reference is a member of a class or used in certain closures the compiler may need something to store.

lvalue reference to const can bind to rvalues
*/

int getvalue() {
    return 5;
}

void printv(int n , int& ref) {
    cout<<"address n : "<<&n<<endl;
    cout<<"address ref : "<<&ref<<endl;
}

void prints(int& val) {
    cout<<"value : "<<val<<endl;
}

void printval(double val) {
    cout<<"value : "<<val<<endl;
}
void printref(const double& val) {
    cout<<"value : "<<val<<endl;
}

int main() {
    double a = 1.3;
    int x = 5 ; // x is lvalue while 5 is rvalue
    int y = x ; // x is mofifiable lvalue, x undergoes lvalue (ro produce its value) to rvalue conversion  
    // 5 = x; // error

    const int d = 10 ;
    const int e = d ; // d is non modifiable lvalue
    // d = e; // error

    int z = getvalue(); // getvalue() is rvalue
    int w = x + 1; // x+1 is rvalue
    // rvalues  as they produce temporary values that are not identifiable objects
    
    // int& reff; // throws error as needed to be initialised
    // ref is bound to x . x is called referent
    int& ref = x ;
    // cout<<x<<" "<<ref<<endl;
    // x = 6;
    // cout<<x<<" "<<ref<<endl;
    // ref = 7;
    // cout<<x<<" "<<ref<<endl;

    // non const lvalue reference can only be bound to modifiable lvalue
    // int& reff = d; // can't bind to non mofifiable lvalue as it may allow changes to the const d through reff
    // int& reff = 0; // can't bind to rvalue as we can't alter there constness property
    // double& dref = x; // no conversion are applied here
    // int& reff = a; // error

    // conversion are rvalue that is why compilation error
    // double&& dref = x; // no error here

    // int b = 3;
    // ref = b;
    // cout<<x<<" "<<ref<<" "<<b<<endl;
    // reference to x haven't by this only the value of b is taken to be assigned to x

    // ref dies before object
    // int v = 10;
    // if(true) {
    //     int& vref = v;
    //     cout<<vref<<endl;
    // }
    // cout<<vref<<endl; // error undefined

    // int& refff = ref ; // not a reference to ref but to x only
    // refff = 9 ;
    // cout<<x<<" "<<ref<<" "<<refff;
    
    // const int& cref = d;
    // cout<<cref<<" "<<d<<endl;
    // cref = 2; // error

    // we can refer non const var using const reference but we can not modify the variable using that reference
    // const int& ncref = x;
    // cout<<ncref<<" "<<x<<endl;
    // ncref = 9; // error

    // const int& rref = 10; // points to a temp var created for this and initialized by this value
    // cout<<rref<<endl;

    const char& diref = 65;
    cout<<diref<<endl;
    char c = 'a';
    const int& chref = c ;
    cout<<chref<<endl;
    // compiler will create a temporary object of the same type as the reference, initialize it using the value,
    // and then bind the reference to the temporary.
    // remember any changes made to this variable will not be reflected in the reference as it points to temp var
    // lifetime of the constant expression(temperory var) is increased to that of const reference 

    cout<<"address x : "<<&x<<endl;
    printv(x,x);

    prints(x);
    // prints(d); //error
    // prints(9); //error

    printval(5); // this creates copy
    printref('a'); // this will also create a copy since temporary variable would be needed for conversion

    

    return 0;
}