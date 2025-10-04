#include "mydatastore.h"
#include <iostream>
#include <set>
#include <string>

using namespace std;

MyDataStore::MyDataStore() { }

MyDataStore::~MyDataStore() {
    for(Product* p : products_) {
        delete p;
    }
    for(auto& pair : users_) {
        delete pair.second;
    }
}

void MyDataStore::addProduct(Product* p) {
    if(p) products_.push_back(p);
}

void MyDataStore::addUser(User* u) {
    if(u) users_[u->getName()] = u;
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
    set<Product*> results;
    bool first = true;
    for(string term : terms) {
        set<Product*> temp;
        for(Product* p : products_) {
            set<string> keys = p->keywords();
            if(keys.find(convToLower(term)) != keys.end()) {
                temp.insert(p);
            }
        }
        if(first) {
            results = temp;
            first = false;
        } else {
            if(type == 0) {
                results = setIntersection(results, temp);
            } else {
                results = setUnion(results, temp);
            }
        }
    }
    return vector<Product*>(results.begin(), results.end());
}

void MyDataStore::dump(ostream& ofile) {
    ofile << "<products>" << endl;
    for(Product* p : products_) {
        p->dump(ofile);
    }
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    for(auto& pair : users_) {
        pair.second->dump(ofile);
    }
    ofile << "</users>" << endl;
}

void MyDataStore::addToCart(const string& username, Product* p) {
    if(users_.find(username) == users_.end()) {
        cout << "Invalid request" << endl;
        return;
    }
    carts_[username].push_back(p);
}

void MyDataStore::viewCart(const string& username) {
    if(users_.find(username) == users_.end()) {
        cout << "Invalid username" << endl;
        return;
    }
    int i = 1;
    for(Product* p : carts_[username]) {
        cout << "Item " << i << endl;
        cout << p->displayString() << endl;
        cout << endl;
        i++;
    }
}

void MyDataStore::buyCart(const string& username) {
    if(users_.find(username) == users_.end()) {
        cout << "Invalid username" << endl;
        return;
    }
    User* u = users_[username];
    vector<Product*>& cart = carts_[username];
    vector<Product*> remaining;

    for(Product* p : cart) {
        if(p->getQty() > 0 && u->getBalance() >= p->getPrice()) {
            p->subtractQty(1);
            u->deductAmount(p->getPrice());
        } else {
            remaining.push_back(p);
        }
    }
    cart = remaining;
}
