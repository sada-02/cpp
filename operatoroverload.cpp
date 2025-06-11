#include <bits/stdc++.h>
using namespace std;

/*
Function overloading to overload operators

Resolving operators
- If all operands are fundamental data types -> we call built in function else throw error
- If any one is program defined type -> resolution overload algorithm

only some operators cannot be overloaded :
conditional (?:) , sizeof , scope (::) , member select (.) , pointer member select (-> (.*))

- Only existing operators can be overloaded nothing new can be found
- at least one of the operand should be program (user as can work on strings but not prefered) defined (can not work on
fundamental types)
- Cannot change number of operands a operator can support
- default precedence and associativity is maintained

operators that do not modify their operands should return by value
operands that modify leftmost operand should return by reference

(int , class) and (class , int) are different functions

operands like = , [] , () (function call) , member select (->) can not be overloaded using friend function they must
overloaded using member function only
while << and >> can be overloaded using friend only as for member we need class but they ostream and istream objects
which are defined in the standard library only
also only (<class> , int) can be overloaded as in (int , <class>) leftmost isn't a class

operator!= can be implemented as !(operator==)
operator> can be implemented as operator< with the order of the parameters flipped
operator>= can be implemented as !(operator<)
operator<= can be implemented as !(operator>)

Overloaded typecasts must be non-static members, and should be const so they can be used with const objects.
Overloaded typecasts do not have explicit parameters, as there is no way to pass explicit arguments to them. They do 
still have a hidden *this parameter, pointing to the implicit object (which is the object to be converted).
Overloaded typecast do not declare a return type. The name of the conversion (e.g. int) is used as the return type, 
as it is the only return type allowed. This prevents redundancy in the declaration.
*/

int gcd(int& a , int& b) {
    if(a < b) {
        int t = b ;
        b = a;
        a = b;
    }

    while(b) {
        a = a%b;
        int t = b ;
        b = a;
        a = b;
    }

    return a;
}

// operator overloading using friend function
class fraction {
    private :
    int m_numerator {0};
    int m_denominator {1};
    int m_val {-1};
    int m_arr[10] {};
    int m_arrD[10][10] {};

    public :
    fraction() = default ;

    fraction(int num , int den) : m_numerator {num} , m_denominator {den} {
        cout<<"Constructor was called"<<endl;
    }
    fraction(int num , int den , int val) : m_numerator {num} , m_denominator {den} , m_val {val} {
        cout<<"Constructor was called"<<endl;
    }

    ~fraction() {
        cout<<"Destructor was called"<<endl;
    }

    void printFraction() {
        cout<<m_numerator<<"/"<<m_denominator<<endl;
    }

    // overlaoding function as member function uses this parameter for the left operand while other parameter are 
    // passed normally

    friend int gcd(int& a, int& b);

    friend fraction operator+(const fraction& op1 , const fraction& op2) {
        fraction temp;
        temp.m_numerator = op1.m_numerator*op2.m_denominator + op2.m_numerator*op1.m_denominator;
        temp.m_denominator = op1.m_denominator*op2.m_denominator;
        return temp;
    }
    friend fraction operator-(const fraction& op1 , const fraction& op2) {
        fraction temp;
        temp.m_numerator = op1.m_numerator*op2.m_denominator - op2.m_numerator*op1.m_denominator;
        temp.m_denominator = op1.m_denominator*op2.m_denominator;
        return temp;
    }
    friend fraction operator*(const fraction& op1 , const fraction& op2) {
        fraction temp;
        temp.m_numerator = op1.m_numerator*op2.m_numerator;
        temp.m_denominator = op1.m_denominator*op2.m_denominator;
        return temp;
    }

    friend fraction operator+(const fraction& op1 , int op2) {
        fraction temp;
        temp.m_numerator = op1.m_numerator + op2*op1.m_denominator;
        temp.m_denominator = op1.m_denominator;
        return temp;
    }
    friend fraction operator-(const fraction& op1 , int op2) {
        fraction temp;
        temp.m_numerator = op1.m_numerator - op2*op1.m_denominator;
        temp.m_denominator = op1.m_denominator;
        return temp;
    }
    friend fraction operator*(const fraction& op1 , int op2) {
        fraction temp;
        temp.m_numerator = op1.m_numerator*op2;
        temp.m_denominator = op1.m_denominator;
        return temp;
    }

    friend fraction operator+(int op1 , const fraction& op2) {
        return op2 + op1;
    }
    friend fraction operator-(int op1 , const fraction& op2) {
        fraction temp;
        temp.m_numerator = op1*op2.m_denominator - op2.m_numerator;
        temp.m_denominator = op2.m_denominator;
        return temp;
    }
    friend fraction operator*(int op1 , const fraction& op2) {
        return op2 * op1;
    }

    int getNum() const {
        return m_numerator;
    }
    int getDen() const {
        return m_denominator;
    }

    friend ostream& operator<<(ostream& out ,const fraction& temp);
    friend istream& operator>>(istream& in , fraction& temp);

    // overloading unary operators + , - , ! typically done using member function only
    fraction operator+() const;
    fraction operator-() const;
    bool operator!() const;

    // overloading comparison operators
    friend bool operator==(const fraction& a , const fraction& b) ;
    friend bool operator!=(const fraction& a , const fraction& b) ;
    friend bool operator>(const fraction& a , const fraction& b) ;
    friend bool operator<(const fraction& a , const fraction& b) ;

    // overloading increment and decrement operators
    fraction& operator++(); // prefix
    fraction& operator--();
    fraction operator++(int); // postfix this is how compiler finds distinction
    fraction operator--(int);

    // overloading [] subscript operator
    // traditionally this is how we would have accessed element
    // void setArr(int ind , int val) {
    //     m_arr[ind] = val;
    // }
    // int getArr(int ind) {
    //     return m_arr[ind];
    // }

    // remember for assignment operator lefthand operator needs to be lvalue that is why we are returning by 
    // reference and must be overloaded as member function
    // prior to C++ 23 it is single parameter based hence can not be used to access two dim arrays
    int& operator[](int ind) {
        return m_arr[ind];
    }
    // parameter can be anything 
    // we can define both const and non const version simultaneously
    const int& operator[] (int ind) const {
        return m_arr[ind];
    }

    // overloading parenthesis operator also must be member function used to create functors
    void operator()() {
        for(int i=0 ;i<10 ;i++) {
            for(int j=0 ;j<10 ;j++) {
                m_arrD[i][j] = 0;
            }
        }
    }

    int& operator()(int row , int col) {
        return m_arrD[row][col];
    }

    const int& operator()(int row , int col) const {
        return m_arrD[row][col];
    }

    // overloading typecast 
    operator int() const {
        return m_val;
    }
    // other than fundamental data types there can be user defined datatypes here (like other classes)

    // explicit operator double() const {
    //     return double(m_val);
    // }

    // If a new object has to be created before the copying can occur, the copy constructor is used.
    // If a new object does not have to be created before the copying can occur, the assignment operator is used.
    // overloading assignment operator
    fraction(const fraction& copy) : m_numerator {copy.m_numerator} , m_denominator {copy.m_denominator} 
    , m_val {copy.m_val} {
        cout<<"Copy Constructor was called"<<endl;
    }

    fraction& operator= (const fraction& temp) {
        cout<<"Overloaded assignment was called"<<endl;
        this->m_numerator = temp.m_numerator;
        this->m_denominator = temp.m_denominator;
        this->m_val = temp.m_val;
        
        return *this;
    }

    // fraction(const fraction& copy) = delete; // disabling copy constructors
    // fraction& operator= (const fraction& copy) = delete; // disabling assignment operator

};

// cout is of type ostream overloading output operator
// return by value is disallowed here also provides chaining output commands
ostream& operator<<(ostream& out , const fraction& temp) {
    out<<temp.m_numerator<<"/"<<temp.m_denominator<<" val : "<<temp.m_val;
    return out;
}

// overloading input operator
istream& operator>>(istream& in , fraction& temp) {
    // in>>temp.m_numerator>>temp.m_denominator;
    // return in;

    int x {} , y {};
    in>>x>>y;

    temp = in ? fraction {x,y} : fraction {}; // now you are checking whether the input is correct or not
    return in;
}
// though we have overloaded input operator but it could happen that the extraction is interrupt which results in 
// partial assignments we can avoid this by making operation transactional -> which must either completely suceed or
// fails completely

// operator overload using normal function
fraction operator/(const fraction& op1 , const fraction& op2) {
    return fraction(op1.getNum()*op2.getDen() , op1.getDen()*op2.getNum());
}
// it is similar to friend function but the difference is at level of access and that the friend function can be 
// friend function declaration inside also serves as a prototype

fraction fraction::operator+() const {
    return fraction(m_numerator,m_denominator,-m_val);
}
fraction fraction::operator-() const {
    return fraction(-m_numerator,-m_denominator,m_val);
}
bool fraction::operator!() const {
    return (m_numerator == 0 && m_val == 0);
}

bool operator==(const fraction& a , const fraction& b) {
    int ta = gcd(a.m_numerator , b.m_denominator);
    int tb = gcd(b.m_numerator , b.m_denominator);

    if(a.m_numerator/ta == b.m_numerator/tb && a.m_denominator/ta == b.m_denominator/tb) return true;
    else return false;
}

bool operator!=(const fraction& a , const fraction& b) {
    int ta = gcd(a.m_numerator , b.m_denominator);
    int tb = gcd(b.m_numerator , b.m_denominator);

    if(a.m_numerator/ta == b.m_numerator/tb && a.m_denominator/ta == b.m_denominator/tb) return false;
    else return true;
}

bool operator>(const fraction& a , const fraction& b) {
    if(a.m_val > b.m_val) return true;
    else return false;
}
bool operator<(const fraction& a , const fraction& b) {
    if(a.m_val > b.m_val) return false;
    else return true;
}

fraction& fraction::operator++() {
    this->m_val++;
    return *this;
}
fraction& fraction::operator--() {
    this->m_val--;
    return *this;
}

fraction fraction::operator++(int) {
    fraction temp {*this};
    this->m_val++;
    return temp;
}
fraction fraction::operator--(int) {
    fraction temp {*this};
    this->m_val--;
    return temp;
}

int mul100(int v) {
    return 100*v;
}

double div2(double v) {
    return v/2;
}

int main() {
    int x {5} , y {4};
    cout<<x + y<<endl; // x + y -> operator+ (fn)

    double dx {9.1} , dy {8.3};
    cout<<dx + dy<<endl; // dx + dy -> operator+ (overload for double operands) 

    fraction a (1,2) , b (1,3);
    (a+b).printFraction();
    (a-b).printFraction();
    (a*b).printFraction();

    (a+x).printFraction();
    (a-x).printFraction();
    (a*x).printFraction();

    (x+a).printFraction();
    (x-a).printFraction();
    (x*a).printFraction();

    (y+a+x+b).printFraction(); // moves from left to right fashion like normal arithmetic rule

    (a/b).printFraction();
    cout<<a<<endl;
    // cin>>b;
    // cout<<b<<endl;

    cout<<+a<<endl;
    cout<<-a<<endl;
    cout<<!a<<endl;

    fraction p(1,2,3) , q(2,3,3) , r(2,4,5);
    cout<<(p != q)<<endl;
    cout<<(p == r)<<endl;
    cout<<(p != r)<<endl;
    cout<<(p == q)<<endl;
    cout<<(r > q)<<endl;
    cout<<(r < q)<<endl;

    cout<<++p<<endl;
    cout<<--p<<endl;
    cout<<p++<<endl;
    cout<<p--<<endl;

    a[1]= 90;
    cout<<a[1]<<endl;

    const fraction ca(1,2,3);
    // ca[1] = 12; // error
    cout<<ca[1]<<endl;

    fraction* ptr {&a};
    cout<<"lol "<<(*ptr)[1]<<endl; // correct way of accessing assumes we are accessing array of fractions

    a(1,5) = 19;
    cout<<a(1,5)<<endl;
    a();
    cout<<a(1,5)<<endl;

    cout<<mul100(a)<<endl;
    // cout<<div2(a)<<endl; // error it was firstly compiling if i haven't commented the int conversion

    fraction copya {a};
    b = a;

    // beware of self assignment a = a , it can be dangerous use self assignement guard
    // if(this == &temp) return *this;

    // if your class has const member it will be considered deleted so need to explicitly define it

    // default copy constructor and assignment uses shallow copy (copies of each member) works when no dynamic memory
    // pointers would point to same location because of which there can be a lot of problem
    // in shallow copy dynamic ones share same memory locations while static ones are copied
    // in a deep copy first a new memory location is allocated and then assignment is done on them
    


    return 0;
}