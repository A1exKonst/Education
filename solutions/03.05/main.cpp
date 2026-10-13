// Problem 03.05
/*
Implement a system for the separate overriding of multiply inherited virtual member functions 
	with identical signatures and different implementations. 
Implement the base classes Entity_v1 and Entity_v2. 
Implement virtual member functions named 'test' with identical signatures 
	and different implementations in the Entity_v1 and Entity_v2 classes. 
Implement a derived class Client, which inherits from the interfaces of the Entity_v1 and Entity_v2 classes. 
Note that separately overriding the inherited virtual member functions 
	named 'test' in the Client class is impossible due to their matching signatures. 
Implement derived classes Adapter_v1 and Adapter_v2 to act as intermediaries, 
	inheriting from the interfaces of the Entity_v1 and Entity_v2 classes respectively.
Implement a derived class Client, which inherits from the interfaces of the Adapter_v1 and Adapter_v2 classes. 
Implement virtual member functions test_v1 and test_v2 in the Adapter_v1 and Adapter_v2 classes respectively, 
	which are called from the overridden inherited virtual member functions named 'test' 
	and are separately overridden in the Client class.
*/



#include <print>



class Entity_v1;
class Entity_v2;
class Adapter_v1;
class Adapter_v2;
class Client;



class Entity_v1 {
public:
    virtual ~Entity_v1() = default;
    virtual void test() = 0;
};



class Entity_v2 {
public:
    virtual ~Entity_v2() = default;
    virtual void test() = 0;
};



class Adapter_v1 : public Entity_v1 {
public:
    virtual void test() override {
        test_v1();
    }
    
    virtual void test_v1() = 0; // new member function to override in Client.
};



class Adapter_v2 : public Entity_v2 {
public:
    virtual void test() override {
        test_v2();
    }
    
    virtual void test_v2() = 0; // new member function to override in Client.
};



class Client : public Adapter_v1, public Adapter_v2 {
public:
    // Раздельное переопределение для ветки Entity_v1
    void test_v1() override {
        std::print("call Client::test_v1() via virtual Entity_v1::test(). \n");
    }

    void test_v2() override {
        std::print("call Client::test_v2() via virtual Entity_v2::test(). \n");
    }
};



int main() {
    Client client;

    Entity_v1* entity1 = static_cast<Adapter_v1*>(&client); // static_cast ensures correct vtable choice
    entity1->test();

    Entity_v2* entity2 = static_cast<Adapter_v2*>(&client); // static_cast ensures correct vtable choice
    entity2->test();

    return 0;
}
