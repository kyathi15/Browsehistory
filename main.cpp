#include <iostream>
#include <string>
using namespace std;

class Customer {
public:
    string name;
    int priorityLevel;
    string priorityReason;
    Customer* next;

    Customer(string customerName, int priority, string reason = "")
        : name(customerName), priorityLevel(priority), priorityReason(reason), next(nullptr) {}

    void showDetails() const {
        cout << name;
        if (!priorityReason.empty()) {
            cout << " (Priority: " << priorityReason << ")";
        }
        cout << endl;
    }
};

class BankQueue {
private:
    Customer* front;

public:
    BankQueue() : front(nullptr) {}

    ~BankQueue() {
        while (front != nullptr) {
            dequeue();
        }
    }

    void enqueue(const string& name, int priorityLevel, const string& priorityReason = "") {
        Customer* newCustomer = new Customer(name, priorityLevel, priorityReason);
        Customer* current = front;
        Customer* previous = nullptr;

        while (current != nullptr && current->priorityLevel <= priorityLevel) {
            previous = current;
            current = current->next;
        }

        if (previous == nullptr) {
            newCustomer->next = front;
            front = newCustomer;
        } else {
            previous->next = newCustomer;
            newCustomer->next = current;
        }

        if (priorityLevel == 5) {
            cout << newCustomer->name << " has been added as a regular customer.\n";
        } else {
            cout << newCustomer->name << " has been added with priority " << newCustomer->priorityReason << ".\n";
        }
    }

    void dequeue() {
        if (front == nullptr) {
            cout << "No customers in the queue.\n";
            return;
        }

        Customer* customerToServe = front;
        front = front->next;
        cout << customerToServe->name << " is being served.\n";
        delete customerToServe;
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    void showQueueStatus() const {
        if (isEmpty()) {
            cout << "The queue is currently empty.\n";
            return;
        }

        cout << "\nCustomers in the queue:\n";
        Customer* current = front;
        while (current != nullptr) {
            current->showDetails();
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    BankQueue bankQueue;

    bankQueue.enqueue("Saritha", 5);
    bankQueue.enqueue("Bhatti Vikramarka", 2, "VIP");
    bankQueue.enqueue("Aadarsh", 5);
    bankQueue.enqueue("Ramulamma", 4, "Elderly");
    bankQueue.enqueue("Rambabu", 5);
    bankQueue.enqueue("Kavitha", 3, "Disabled");
    bankQueue.enqueue("Vaishnavi", 5);
    bankQueue.enqueue("Siri Chandana", 5);
    bankQueue.enqueue("Vikram Batra", 1, "Military");
    bankQueue.enqueue("Krishna", 5);
    bankQueue.enqueue("Jagadeeshwar", 4, "Elderly");
    bankQueue.enqueue("Mohan", 3, "Disabled");
    bankQueue.enqueue("Naveen", 5);
    bankQueue.enqueue("Sanjay", 5);
    bankQueue.enqueue("Santosh", 5);

    bankQueue.showQueueStatus();

    while (!bankQueue.isEmpty()) {
        bankQueue.dequeue();
    }

    return 0;
}
