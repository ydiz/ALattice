If a member function is not virtual but hides the function in base class. Then `base -> f()` will call the base class's member function 


```
class Base
{
public:
    int b;
    void Display()
    {
        cout<<"Base: Non-virtual display."<<endl;
    };
    virtual void vDisplay()
    {
        cout<<"Base: Virtual display."<<endl;
    };
};

class Derived : public Base
{
public:
    int d;
    void Display()
    {
        cout<<"Derived: Non-virtual display."<<endl;
    };
    virtual void vDisplay()
    {
        cout<<"Derived: Virtual display."<<endl;
    };
};
```

```
Base *b = &ba;
b->Display();  // Base: Non-virtual display.
b->vDisplay();  // Base: Virtual display.
b = &de;
b->Display();  // Base: Non-virtual display. !!!!! not virtual function
b->vDisplay(); // Derived: Virtual display.

```



--------------------

## zyd: "overload" and "hide"

overload a function: compiler knows there are multiple functions with the same name, and it will choose one.

hide a function: compiler only knows there is one function.

e.g. define function with different sets of arguments : overloading; virtual functions will be overloaded.

e.g. **functions don't overload across namescopes.** So for a non-virtual function, if you define it again(define a function with the same name) in the derived class, even with different arguments, the function in base class will be hidden.

```
class Base{
  void f(int);
};
class Derived : Base{
  void f(double);  //will hide the function in Base, instead of overriding.
};
Derived d;
d.f(1); //will call f(double) in Derived.
```

-----
## virtual function misc

1. Derived classes do not have to implement all virtual functions themselves. They only need to implement the pure ones.

2. Pointer to base class cannot access members exclusive to derived class.

```
class Base
{
    int base_int;
};
class Derived : public Base
{
    int derived_int;
};
Base* basepointer = new Derived();
basepointer-> derived_int; //error!!
```

Especially, **You cannot call a non-virtual member function of the derived class with base class pointer.**

**If two non-virtual functions with the same name are defined in derived and base class, the base class one will always be called.**

```
class Base
{
public:
    void f(int i) { cout << "Base" <<endl;};
};
class Derived : public Base
{
public:
    void f(int i) { cout << "Derived" <<endl;};
    void g(double i) { cout << "Derived" <<endl;}
};

Derived d;
Base* pb = &d;
pb->f(1);   // "Base"
d.f(1);     // "Derived"
pb->g(1);   // error! Base has no member g
```

---

## virtual and override identifier

By default, a function that overrides a virtual function itself becomes virtual. It is recommended not repeating `virtual`. If you want to be explicit, use `override`.

`override` comes last in the declaration in class. It is not a part of the type of function, so it cannot be repeated in an out-of-class definition.

```
class Base{
  virtual void f(int) const;
  virtual void g(int);
};
class Derived : Base{
  void f(int) const override;  // automatically virtual; add override to be explicit; override is after const
  void g(double) override;   // error; g() takes int; adding `override` can help you avoid mistakes like this!!!
                            // otherwise it will hide g(int) in base and introduce a new function.
};

void Derived::f(int i) const  //do not add override; not part of the type of the function
{}
```
