#include "clothing.h"
#include "util.h"
#include <sstream>
#include <iomanip>
using namespace std;

Clothing::Clothing(const string& name, double price, int qty, const string& size, const string& brand)
    : Product("clothing", name, price, qty), size_(size), brand_(brand) {}

set<string> Clothing::keywords() const {
    set<string> keys = parseStringToWords(name_);
    set<string> brandKeys = parseStringToWords(brand_);
    keys = setUnion(keys, brandKeys);
    return keys;
}

string Clothing::displayString() const {
    stringstream ss;
    ss << name_ << "\nSize: " << size_ << " Brand: " << brand_ << "\n"
       << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Clothing::dump(ostream& os) const {
    os << "clothing\n" << name_ << "\n" << price_ << "\n" << qty_
       << "\n" << size_ << "\n" << brand_ << endl;
}
