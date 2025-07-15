#include <bits/stdc++.h>
using namespace std;

/*
we can make a constructor protected to be able to use it in derieved classes only but not by public
The pointer or reference to the base class calls the base version of the function rather than the derived version. 
If only there was some way to make those base pointers call the derived version of a function instead of the base 
version

A virtual function is a special type of member function that, when called, resolves to the most-derived version of 
the function for the actual type of the object being referenced or pointed to.
A derived function is considered a match if it has the same signature (name, parameter types, and whether it is 
const) and return type as the base version of the function. Such functions are called overrides.

polymorphism refers to the ability of an entity to have multiple forms
Compile time -> resolved by compilers like overload resolution or template resolution
runtime -> resolved at runtime virtual function resolution

Note that if a function is marked as virtual, all matching overrides in derived classes are also implicitly 
considered virtual, even if they are not explicitly marked

the signature of the derived class function must exactly match the signature of the base class virtual function in 
order for the derived class function to be used
the return type of a virtual function and its override must match for it to compile

Never call virtual functions from constructors and destructors
As in case of constructor derieved class haven't yet been constructed an in destructors they have been deleted

overried specifiers implies virtual

there is one case in which return type can be different if return type of virtual function is to some class than 
override function can return a pointer to derieved class (called covariant return types)
*/

class Animal{
    protected :
    string m_name ;
    string m_voice ;

    public :
    Animal(const string& name = "unknown" , const string& voice = "????") : m_name {name} , m_voice {voice} {
        cout<<"Animal is Created"<<endl;
    }

    string getName() const {
        return m_name;
    }

    string getVoice() const {
        cout<<"In Animal"<<endl;
        return m_voice;
    }
};

class Cat : public Animal{
    public :
    Cat(const string& name) : Animal(name , "meow") {
        cout<<"Cat was created"<<endl;
    }

    string& getVoice() {
        cout<<"In Cat"<<endl;
        return m_voice;
    }
};


class Dog : public Animal{
    public :
    Dog(const string& name) : Animal(name , "bark") {
        cout<<"Dog was created"<<endl;
    }

    string& getVoice() {
        cout<<"In Dog"<<endl;
        return m_voice;
    }
};

void report(const Animal& rep) {
    cout<<rep.getName()<<" "<<rep.getVoice()<<endl;
}

class A{
public:
    virtual string getName() const { return "A"; }
};

class B: public A{
public:
    virtual string getName() const { return "B"; }
};

class C: public B{
public:
    virtual string getName() const { return "C"; }
};

class D: public C{
public:
    virtual string getName() const { return "D"; }
};

class AA {
    public :
    virtual string getname1(int v) {
        return "Lol in int AA";
    }
    virtual string getname2(double v) {
        return "Lol in double AA";
    }
    virtual string getname3(short v) const {
        return "Lol in short AA const";
    }
};
class BB : public AA {
    public :
    // these are not considered overrides as different signatures
    virtual string getname1(char v) {
        return "Lol in char BB";
    }
    virtual string getname2(double v) const {
        return "Lol in double BB const";
    }

    // for overriding this can also be used 
    string getname1(int a) override {
        return "Lol in int BB";
    }

    string getname3(short v) const override {
        return "Lol in short BB const";
    }
};

// final -> to unable someone to override a virtual function
class AF {
    public :
    virtual void getName() const {
        cout<<"In AF"<<endl;
    }

    virtual void getN(int val) {
        cout<<"Int in AF"<<endl;
    }
};

// if i make my class final i can not inherit it
class BF final : public AF{
    public :
    virtual void getName() const override final {
        cout<<"In BF"<<endl;
    }

    // void getN(short val) override { // this throws error
    //     cout<<"Short in BF"<<endl;
    // }
};
// class CF : public BF{ // this class cannot be inherited as it is considered final
//     public :
//     void getName() override{  // throws error as now we can't override it
//         cout<<"In CF"<<endl;
//     }
// };

// class DF : public BF {
//     public :
//     int no;
// };

// gendfad
class P {
    public :
    void printp() {
        cout<<"P ";
    }

    virtual void printvp() {
        cout<<"VP ";
    }
};

class Q : public P {
    public :
    void printp() {
        cout<<"Q ";
    }

    void printvp() override {
        cout<<"VQ ";
    }
};

class childP{
    private :
    P m_p {};

    public :
    virtual P& get() {
        return m_p;
    }
};

class childQ : public childP{
    private :
    Q m_q {};

    public :
    Q& get() override {
        return m_q;
    }
};

class Base {
    private :
    int m_v ;
    
    public :
    Base(int v = 5) : m_v {v} {
        cout<<"Constructor Base"<<endl;
    }

    virtual ~Base() {
        cout<<"Destructor Base"<<endl;
    }

    int getv() {
        return m_v;
    }
};

class Derieved : public Base {
    private :
    int m_l ;

    public :
    Derieved(int l) : m_l {l} {
        cout<<"Derieved Constructor"<<endl;
    }

    virtual ~Derieved() {
        cout<<"Derieved Destructor"<<endl;
    }

    int getl() {
        return m_l;
    }
};

class base{
    public :
    virtual void function1() = 0 ;
    virtual void function2() = 0 ;
};

void base::function1() {
    cout<<"base"<<endl;
}
void base::function2() {
    cout<<"base"<<endl;
}

class derive : public base{
    public :
    void function1() override {
        cout<<"Derive"<<endl;
    }

    void function2() override {
        base::function2();
    }
};

class Diamondhead{
    public :
    int val ;

    Diamondhead(int v) : val{v} {
        cout<<"head"<<endl;
    }
};
class Diamondleft : virtual public Diamondhead{
    public :
    Diamondleft() {
        cout<<"left"<<endl;
    }
};
class Diamondright : virtual public Diamondhead {
    public :
    Diamondright() {
        cout<<"right"<<endl;
    }
};

class Diamondcentre : virtual public Diamondhead {
    public :
    Diamondcentre() {
        cout<<"centre"<<endl;
    }

    void setval(int v) {
        val = v ;
    }
};

class Diamondchild : public Diamondleft , public Diamondright {
    public :
    Diamondchild(int v) : Diamondhead(v) {
        cout<<"child"<<endl;
    }
};

int main() {
    Cat x("shanny");
    Dog y("shane");

    Cat& refx {x};
    Cat* ptrx {&x};

    cout<<x.getVoice()<<endl;
    cout<<refx.getVoice()<<endl;
    cout<<ptrx->getVoice()<<endl;

    // a direct base pointer or reference
    Animal& refanim {x};
    Animal* ptranim {&x};
    // these can only see base members as derieved members are invisible to it

    cout<<refanim.getVoice()<<endl;
    cout<<ptranim->getVoice()<<endl;

    report(x);
    report(y);

    // virtual fns work only for references and pointers

    C c {};
    A& rBase{ c };
    cout << "rBase is a " << rBase.getName() << endl;
    // only function between A and C are considered and hence D is not called
    //  A::getName() is virtual, so the compiler will call the most-derived match between A and C. In this case, 
    // that is C::getName(). Note that it will not call D::getName(), because our original object was a C, not a D, 
    // so only functions between A and C are considered.

    // virtual function resolution only works when a virtual member function is called through a pointer or reference
    A a { c }; // copies the A portion of c into a (don't do this)
    cout << a.getName()<<endl;

    BB bb {};
    AA& aa {bb};
    cout<<aa.getname1(5)<<endl;
    cout<<aa.getname2(5.3)<<endl;   
    cout<<aa.getname3(5)<<endl;

    childP DD {};
    DD.get().printp();
    DD.get().printvp();
    cout<<endl;
    childQ CC {};
    CC.get().printp();
    CC.get().printvp();
    cout<<endl;
    childP& ref {CC};
    ref.get().printp();
    ref.get().printvp();
    cout<<endl;

    Base* refbase {new Derieved(10)} ;
    delete refbase;
    // cout<<lol.getl()<<endl;

    // base h ;
    derive h ;
    h.function1();
    h.function2();

    // if we haven't added virtual then two copies of head would have been formed 
    // virtual means that the same object would be shared among all (beware)
    Diamondchild lol(10) ;
    
    return 0;
}