// Problem 03.04.
/*
Implement an external testing system for the private member functions of a certain class. 
Implement the Entity class. 
Inside the Entity class, implement private member functions test_v1 and test_v2 that need to be tested. 
Keep in mind the first principle of SOLID — the Single Responsibility Principle. 
Implement Tester_v1 and Tester_v2 classes as friends of the Entity class 
	to represent the testers for the test_v1 and test_v2 member functions of the Entity class, respectively. 
This will provide direct access to the private section of the Entity class and avoid using its public interface. 
Use the Attorney-Client pattern to restrict the access of the Tester_v1 and Tester_v2 classes 
	to the private section of the Entity class.
*/



#include <iostream>
#include <string>
#include <print>



class Entity;
class Tester_v1;
class Tester_v2;
class Attorney_v1;
class Attorney_v2;



// Client in an Attorney-Client pattern:
class Entity {
private:
    bool data = true;

    // Testers have access through Attorneys:
    friend class Attorney_v1;
    friend class Attorney_v2;

    void test_v1() {
        std::print("call Entity::test_v1(). Data: {}\n", data);
    }

    void test_v2() {
        std::print("call Entity::test_v2(). Change data\n");
        data = !data;
    }
};



class Attorney_v1 {
private:
    friend class Tester_v1;

    static void call_test_v1(Entity& entity) {
        entity.test_v1(); // Tester_v1 has access only to Entity::test_v1().
    }
};



class Attorney_v2 {
private:
    friend class Tester_v2;

    static void call_test_v2(Entity& entity) {
        entity.test_v2(); // Tester_v2 has access only to Entity::test_v2().
    }
};



class Tester_v1 {
public:
    void run_test(Entity& entity) {
        Attorney_v1::call_test_v1(entity);
        
        // CE compile error:
        // Attorney_v2::call_test_v2(entity); 
    }
};



class Tester_v2 {
public:
    void run_test(Entity& entity) {
        Attorney_v2::call_test_v2(entity);

        // CE compile error:
        // Attorney_v1::call_test_v1(entity); 
    }
};



int main() {
    Entity entity;
    
    Tester_v1 t1;
    Tester_v2 t2;

    t1.run_test(entity); // check data
    t2.run_test(entity); // change data
    t1.run_test(entity); // check data

    return 0;
}
