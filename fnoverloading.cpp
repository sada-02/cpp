#include "bits/stdc++.h"
using namespace std;

/*
Function type signature : used for function differentiation includes function name , num parameters , types of 
parameters and function level qualifiers.

Name Mangling : At compile type function names are altered to account number of parameters , type of parameters so
as to provide unique names.

Overload Resolution : Process of matching the most suitable overloaded function.

Default arguments : provided in function parameters in its definition, caller can either provide a new value or use
the default one. Useful when we want to add new parameter in the function -> we don't have fix all the function 
calling as they would be using the default value of the parameter. These are not the part of function signature.
*/

// 1
typedef int Height; // typedef
using Age = int; // type aliasing
void print(int x)
{
    cout<<x<<endl;
}
// void print(Height x)  // does not work (redefinition)
// {
//     cout<<x<<endl;
// }
// void print(Age x)  // does not work (redefinition)
// {
//     cout<<x<<endl;
// }
// void print(const int x)  // does not work (redefinition)
// {
//     cout<<x<<endl;
// }

// 5
/*
In case we do not want some overloading to work then in that case we can use "delete" keyword -> these functions are
still considered while matching the functions
*/
// void print(char x) = delete;
// void print(bool x) = delete;

// for deleting all the functions other than the one defined here
template <typename T>
void print(T x) = delete ;

// positioning does not affect
void print(double x) {
    cout<<"double "<<x<<endl;
}

/*
Functions can be differentiated on the basis of :
- num parameters 
- type parameters (excludes typedef and const)

remember it does not work for return types.
*/

// 2
int add(int x, int y) // integer version
{
    cout<<"Same : int + int"<<endl;
    return x + y;
}

int add(int x, int y, int z) // on basis of num parameters
{
    cout<<"Same : int + int + int"<<endl;
    return x + y + z;
}

double add(double x, double y) // on basis of type
{
    cout<<"Same : double + double"<<endl;
    return x + y;
}

double add(int x , double y) // mixing types
{   
    cout<<"Mixed : int + double"<<endl;
    return double(x) + y;
}

// 3
// // does not work for different return types
// int random() 
// {
//     return 9;
// }
// double random()
// {
//     return 9.1;
// }

/*
Matching of a function :
- Can be directly matching 
- Can be made to match after applying type conversions

Compiler applies a set of rules to match a function :
Three outcomes :
- No match is found , proceeds to next step 
- Single matching function is found -> best match so no subsequent steps are followed
- Multiple matches -> ambiguous match compile error

If it reaches end of steps and no function is found -> no matching overloaded function is found

Trivial Conversions are set of specific rules that compiler applies for finding a match :
- lvalue to rvalue
- qualification conversion (non const to const)
- non reference to refrence
Matches made by using these are exact matches.

If no match is found then we apply numeric promotions (narrow to wider data types)
If still no match then we apply numeric conversion (int to double)
If still not found then compiler applies any user defined conversion (yeh nhi ata)

Ambiguous match : When more than one function matches in single step -> compiler shows error
*/

// 4
// void foo(int x) {
//     cout<<"int "<<x<<endl;
// }    

// these are same for compiler
void foo(const int x) {
    cout<<"const int "<<x<<endl;
}  

void foo(const double& x) {
    cout<<"const double reference "<<x<<endl;
}  

/*
In the below example if I use int or double both of them can be numerically converted into unsigned int or float 
hence ambiguous error. 

To prevent this either define the function to support the data type or typecast the passed value before passing into
function.
*/

// void foo(unsigned int x) {
//     cout<<"unsigned int "<<x<<endl;
// }

// void foo(float x) {
//     cout<<"float "<<x<<endl;
// }

// void foo(string s) {  // char cannot be promoted to string
//     cout<<"string "<<s<<endl;
// }

// user defined conversion via classes
// after user defined conversion compiler may apply numeric conversions and numeric promotions to match it further
class X {
    public :
    operator char() {
        return 'b';
    }
};

/*
In case where multiple parameters have been passed compiler applies these operation one by one on each parameter and 
the best match is choosen among all the possibilities
*/  
void print(char a , int b) {
    cout<<"char int"<<endl;
}
void print(char a , float b) {
    cout<<"char int"<<endl;
}
void print(double a , long long b) {
    cout<<"char int"<<endl;
}

// 6
// initialisation by using y (2) or y {2} won't work here
void defaulting(int x , int y = 2) {
    cout<<"x : "<<x<<endl;
    cout<<"y : "<<y<<endl;
}

// parameters are provided from left to right
void defaulting2(string s = "header" , int x = 3) {
    cout<<"string : "<<s<<" int "<<x<<endl;
}
/* 
It is necessary to set deafault paramter to rightmost end while the leftmost ones are the ones that the user 
would be likely to change.
If a parameter is given a default argument, all subsequent parameters (to the right) must also be given default
arguments.
Default parameters can not be redeclared and must be declared before use the following two definitions won't work
So best practice is to declare them in forward declaration only (not in function definition)
*/

/*
void print(int x, int y=4); // forward declaration

void print(int x, int y=4) // compile error: redefinition of default argument
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}

void print(int x, int y); // forward declaration, no default argument

int main()
{
    print(3); // compile error: default argument for y hasn't been defined yet

    return 0;
}

void print(int x, int y=4)
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}
*/

// void defaulting(double x = 9 , double y) { // this won't work
//     cout<<"doubles "<<x<<" "<<y<<endl;
// }

void boo(int x) {
    cout<<"boo int"<<endl;
}
void boo(int x , int y = 3) {
    cout<<"boo int int"<<endl;
}
void boo(int x , double y = 8.2) {
    cout<<"boo int double"<<endl;
}

int main()
{
    // print(3); // 1

    // 2
    // cout<<add(1,1)<<endl;
    // cout<<add(1,1,1)<<endl;
    // cout<<add(1.2,2.1)<<endl;
    // cout<<add(3,8.3)<<endl;

    // int v = random(); // 3

    // 4
    // X x;
    // foo(x); // converted into int as defined by the user
    // foo('a'); // promoted to int
    // foo(true); // promoted to int
    // foo(4.5f); // promoted to double
    // foo(3);
    // foo(double(4.5));
    // foo(9.3);
    // foo(5L); // this results in ambiguous match due to simultaneous conversion between int and double of long
    // print('a' , 'b'); // Will print char int because of highest priority matching

    // 5
    // print('a'); // function is forbidden (not forgotten)
    // print(true);
    // print(8.43); // if functions would have been forgotten then this would have not given ambiguous error

    // 6
    // defaulting(3);
    // defaulting(4, 5);

    // defaulting2();
    // defaulting2(2); // this won't work
    // defaulting2("footer");
    // defaulting2(,2); // such a syntax does not work
    // defaulting2("footer" , 2);
    // defaulting(9.3 , 9.2);
    // boo(8) // this will throw error of ambiguity
    
    return 0;
}