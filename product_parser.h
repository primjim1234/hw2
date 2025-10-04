#ifndef PRODUCT_PARSER_H
#define PRODUCT_PARSER_H

#include <string>
#include <istream>
#include "product.h"

class ProductParser {
public:
    ProductParser();
    virtual ~ProductParser();

    Product* parse(std::string category,
                   std::istream& is,
                   bool& error,
                   std::string& errorMsg,
                   int& lineno);

    virtual std::string categoryID() = 0;

protected:
    virtual Product* parseSpecificProduct(std::string category,
                                          std::istream& is,
                                          bool& error,
                                          std::string& errorMsg,
                                          int& lineno) = 0;
    virtual Product* makeProduct() = 0;
    void parseCommonProduct(std::istream& is,
                            bool& error,
                            std::string& errorMsg,
                            int& lineno);

    std::string prodName_;
    double price_;
    int qty_;
};

class ProductBookParser : public ProductParser {
public:
    ProductBookParser() {}
    std::string categoryID();
protected:
    Product* parseSpecificProduct(std::string category,
                                  std::istream& is,
                                  bool& error,
                                  std::string& errorMsg,
                                  int& lineno);
    Product* makeProduct();
private:
    std::string isbn_;
    std::string author_;
};

class ProductClothingParser : public ProductParser {
public:
    ProductClothingParser() {}
    std::string categoryID();
protected:
    Product* parseSpecificProduct(std::string category,
                                  std::istream& is,
                                  bool& error,
                                  std::string& errorMsg,
                                  int& lineno);
    Product* makeProduct();
private:
    std::string size_;
    std::string brand_;
};

class ProductMovieParser : public ProductParser {
public:
    ProductMovieParser() {}
    std::string categoryID();
protected:
    Product* parseSpecificProduct(std::string category,
                                  std::istream& is,
                                  bool& error,
                                  std::string& errorMsg,
                                  int& lineno);
    Product* makeProduct();
private:
    std::string genre_;
    std::string rating_;
};

#endif
