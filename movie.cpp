#include "movie.h"
#include "util.h"
#include <sstream>
#include <iomanip>
using namespace std;

Movie::Movie(const string& name, double price, int qty, const string& genre, const string& rating)
    : Product("movie", name, price, qty), genre_(genre), rating_(rating) {}

set<string> Movie::keywords() const {
    set<string> keys = parseStringToWords(name_);
    set<string> genreKeys = parseStringToWords(genre_);
    keys = setUnion(keys, genreKeys);
    return keys;
}

string Movie::displayString() const {
    stringstream ss;
    ss << name_ << "\nGenre: " << genre_ << " Rating: " << rating_ << "\n"
       << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Movie::dump(ostream& os) const {
    os << "movie\n" << name_ << "\n" << price_ << "\n" << qty_
       << "\n" << genre_ << "\n" << rating_ << endl;
}
