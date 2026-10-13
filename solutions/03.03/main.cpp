// Problem 03.03:
/*
Implement a List class to represent a singly linked list. 
Implement a Node structure to represent the nodes of the singly linked list 
	as a private nested structure within the List class. 
Within the Node structure, implement an int field to store the value of the current list node 
	and a pointer of type Node* to store the address of the next list node. 
Within the List class, implement two private pointers of type Node* to store the addresses 
	of the first and last nodes of the list. 
Do not create a field for storing the current size of the list 
	or any user-defined constructors within the List class. 
Implement a public member function empty in the List class 
	to check for the presence of at least one node in the list. 
Implement a public member function show in the List class to print the values of all current list nodes 
	to the terminal using the standard std::print function. 
Implement public member functions push_front and push_back in the List class 
	to insert new nodes with user-defined values at the beginning and end of the list, respectively. 
Use the new operator for dynamic memory allocation. 
Implement public member functions pop_front and pop_back in the List class to remove nodes 
	from the beginning and end of the list, respectively. 
Use the delete operator to deallocate memory. 
Implement a public member function get in the List class to retrieve the value of the current middle node of the list. 
Use a single loop to traverse the list inside the get member function of the List class. 
Implement a user-defined destructor in the List class that correctly deallocates the memory 
	allocated during the creation of the list nodes. 
Perform unit and integration testing for all implemented member functions of the List class.
*/



#include <print>
#include <cassert>



class List;

void run_unit_tests();

void run_integration_tests();



int main() {
    run_unit_tests();
    run_integration_tests();
    return 0;
}



class List {
private:
    struct Node {
        int value;
        Node* next;
    };

    Node* head = nullptr;
    Node* tail = nullptr;

public:
    List() = default;

    ~List() {
        while (!empty()) {
            pop_front();
        }
    }

    bool empty() const {
        return head == nullptr;
    }

    void push_front(int val) {
        Node* newNode = new Node{val, head};
        head = newNode;
        if (tail == nullptr) {
            tail = newNode;
        }
    }

    void push_back(int val) {
        Node* newNode = new Node{val, nullptr};
        if (empty()) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void pop_front() {
        if (empty()) return;

        Node* temp = head;
        head = head->next;
        delete temp;

        if (head == nullptr) {
            tail = nullptr;
        }
    }

    void pop_back() {
        if (empty()) return;

        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }

        Node* current = head;
        while (current->next != tail) {
            current = current->next;
        }

        delete tail;
        tail = current;
        tail->next = nullptr;
    }

    // Tortoise and Hare algorithm
    int get() const {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }

        const Node* slow = head;
        const Node* fast = head;

        // when fast is at the end, slow will be at a half point
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            if (fast != nullptr) {
                slow = slow->next;
            }
        }
        return slow->value;
    }

    // print to terminal
    void show() const {
        Node* current = head;
        while (current != nullptr) {
            std::print("{} ", current->value);
            current = current->next;
        }
        std::print("\n");
    }
};



// tests

void run_unit_tests() {

    // unit test 1: empty()
    {
        List l;
        assert(l.empty() == true);
        l.push_back(10);
        assert(l.empty() == false);
    }

    // unit test 2: push_front(), push_back()
    {
        List l;
        l.push_front(1); // [1]
        l.push_back(2);  // [1, 2]
        l.push_front(0); // [0, 1, 2]
        
        assert(l.get() == 1);
    }

    // unit test 3: pop_front()
    {
        List l;
        l.push_back(1);
        l.push_back(2);
        l.pop_front();   // l = [2]
        assert(l.get() == 2);
        l.pop_front();
        assert(l.empty());
    }

    // unit test 4: pop_back()
    {
        List l;
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);
        l.pop_back();    // l = [1, 2]
        assert(l.get() == 1);
        l.pop_back();    // l = [1]
        assert(l.get() == 1);
    }

    // unit test 5: get()
    {
        List l1; l1.push_back(10);
        assert(l1.get() == 10); // l1 = [10]

        List l2; l2.push_back(10); l2.push_back(20);
        assert(l2.get() == 10); // l2 = [10, 20]

        List l3; l3.push_back(10); l3.push_back(20); l3.push_back(30);
        assert(l3.get() == 20); // l3 = [10, 20, 30]

        List l4; l4.push_back(10); l4.push_back(20); l4.push_back(30); l4.push_back(40);
        assert(l4.get() == 20); // l4 = [10, 20, 30, 40]
    }
}



void run_integration_tests() {

    std::println("Integration tests:");

    List l;
    
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    std::print("list.push_back().   Expected l = [1,2,3].   Got: ");
    l.show();

    l.push_front(0);
    std::print("list.push_front(0). Expected l = [0,1,2,3]. Got: ");
    l.show();

    std::print("list.get(). Expected 1. Got: {}\n", l.get());

    std::print("list.pop_front().   Expected l = [1,2,3].   Got: ");
    l.pop_front();
    l.show();

    std::print("list.pop_back().    Expected l = [1,2].     Got: ");
    l.pop_back();
    l.show();

    std::println("End integration tests.");
}
