#pragma once

#include "regexpr.h"
#include <iostream>
#include <string>

class Contact {
private:
    std::string NODATA = "NODATA";
    RegExpr *r = new RegExpr;

    std::string name;
    std::string fName;
    std::string numer;

    bool normalizeNumer(std::string &str);

public:

    Contact();

    void CreateContact(std::string &numer, std::string &name, std::string &fname);

    void CreateContact();

    void setName(std::string &val);

    void setFName(std::string &val);

    void setNumer(std::string &val);

    std::string getNumer();

    std::string getName();

    std::string getFName();
};