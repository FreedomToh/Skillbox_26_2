#pragma once

#include <string>
#include <vector>
#include "regexpr.h"
#include "contact.h"


class Phone {

private:
    std::string NODATA = "NODATA";
    RegExpr *r = new RegExpr;

    std::vector<Contact*> contacts;

    bool isNumer(std::string &str);
public:

    void add(std::string &numer, std::string &name, std::string &fname);
    void add();
    void deinit();
    bool findContact(Contact &c);
    void call();
    void showContacts();
    void sendSms();
};