#include <iostream>

class Base
{
public:
    virtual std::string name() const = 0;
protected:
    Base() {}
    virtual ~Base() {}
};

template <typename T>
class Parent : public Base
{
public:
    std::string Name() const {return name_;}
protected:
    static T* instance_;
    explicit Parent(const std::string& name); 
private:
    std::string name_;
};

template <typename T> T* Parent<T>::instance_ = 0;
template <typename T> Parent<T>::Parent(const std::string& name) : Base(), name_(name) {}


class Child;
inline const Child& GET_INSTANCE();

class Child : public Parent<Child>
{
public:
    Child();
    int data = 5;
private:
    friend const Child& GET_INSTANCE();
};

/* inline */ const Child& GET_INSTANCE()
{
    return *Child::instance_;
}

Child::Child() : Parent<Child>("inputName") {}

int main()
{
    std::cout << "data = " << GET_INSTANCE().data << std::endl; // TODO: accessing any memebers through GET_INSTANCE causes a core dump... find out why
    return 0;
}
