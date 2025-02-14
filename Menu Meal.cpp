#include <iostream>
#include <string>
using namespace std;

const int MAX_ITEMS = 3;

struct MenuItem {
    int id;
    string name;
    double price;
    bool isAvailable;
};

struct CartItem {
    int id;
    string name;
    double price;
};

struct Order {
    int orderID;
    double totalPrice;
    int itemCount;
    CartItem items[MAX_ITEMS];
};

MenuItem menu[MAX_ITEMS];
CartItem cart[MAX_ITEMS];
Order orderQueue[MAX_ITEMS];

int menuCount = 0, cartSize = 0, front = 0, rear = -1, nextOrderID = 1;
int top = -1;

void addItem() {
    int numItems;
    cout << "How many items do you want to enter? Maximum size is " << MAX_ITEMS << ": ";
    cin >> numItems;
    if (numItems <= 0 || numItems > MAX_ITEMS || menuCount + numItems > MAX_ITEMS) {
        cout << "Invalid number of items." << endl;
        return;
    }
    for (int i = 0; i < numItems; ++i) {
        cout << "Enter item ID, name, price, availability (1/0): ";
        cin >> menu[menuCount].id;
        cin.ignore();
        getline(cin, menu[menuCount].name);
        cin >> menu[menuCount].price >> menu[menuCount].isAvailable;
        menuCount++;
    }
}

void displayMenu() {
    for (int i = 0; i < menuCount; i++) {
        cout << "ID: " << menu[i].id << " Name: " << menu[i].name << " Price: Rs" << menu[i].price << " Available: " << (menu[i].isAvailable ? "Yes" : "No") << endl;
    }
}

void addToCart(string name) {
    if (top >= MAX_ITEMS - 1) { cout << "Cart is full."; return; }
    for (int i = 0; i < menuCount; i++) {
        if (menu[i].name == name && menu[i].isAvailable) {
            cart[++top] = menu[i];
            cout << name << " added to cart." << endl; return;
        }
    }
    cout << "Item not found or unavailable." << endl;
}

void removeFromCart() { if (top == -1) cout << "Cart is empty." << endl; else cout << cart[top--].name << " removed." << endl; }
void clearCart() { top = -1; cout << "Cart cleared." << endl; }

void displayCart() { if (top == -1) { cout << "Cart is empty."; return; } for (int i = top; i >= 0; i--) cout << cart[i].name << " Rs" << cart[i].price << endl; }

void enqueueOrder() {
    if (top == -1 || ((rear + 1) % MAX_ITEMS == front && rear != -1)) { cout << "Cart empty or order queue full."; return; }
    double total = 0; for (int i = 0; i <= top; i++) total += cart[i].price;
    rear = (rear + 1) % MAX_ITEMS;
    orderQueue[rear] = { nextOrderID++, total, top + 1 };
    for (int i = 0; i <= top; i++) orderQueue[rear].items[i] = cart[i];
    cout << "Order placed. Total: Rs" << total << endl;
    clearCart();
}

void dequeueOrder() {
    if (rear == -1) { cout << "No orders."; return; }
    Order o = orderQueue[front];
    front = (front == rear) ? (rear = -1, 0) : (front + 1) % MAX_ITEMS;
    cout << "Processing order ID: " << o.orderID << " Total: Rs" << o.totalPrice << endl;
}

void userInterface() {
    while (true) {
        int choice, id; double price; string name; bool avail;
        cout << "\n1.Add Menu 2.Display Menu 3.Add to Cart 4.Remove Cart 5.Display Cart 6.Clear Cart 7.Place Order 8.Process Orders 9.Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: addItem(); break;
            case 2: displayMenu(); break;
            case 3: cin.ignore(); getline(cin, name); addToCart(name); break;
            case 4: removeFromCart(); break;
            case 5: displayCart(); break;
            case 6: clearCart(); break;
            case 7: enqueueOrder(); break;
            case 8: dequeueOrder(); break;
            case 9: return;
            default: cout << "Invalid choice.";
        }
    }
}

int main() { userInterface(); return 0; }

