#include "contact.h"

bool Contact::normalizeNumer(std::string &str) {
    std::string tmp;
    for (int i = 0; i < str.length(); i++) {
        if ((str[i] >= '0' && str[i] <= '9') ||
            str[i] == '+') {
            tmp += str[i];
        }
    }

    if (tmp.length() == 10 && r->match("[0-9]{10}", tmp)) {
        tmp = "+7" + tmp;
    } else if (tmp.length() == 11 && r->match("7[0-9]{10}", tmp)) {
        tmp = "+" + tmp;
    }

    if (tmp.length() == 12 && r->match("+7[0-9]{10}", tmp)) {
        str = tmp;
        return true;
    } else {
        return false;
    }
}

Contact::Contact() {
    numer = NODATA;
    setName(NODATA);
    setFName(NODATA);
}

void Contact::CreateContact(std::string &numer, std::string &name, std::string &fname) {
    setNumer(numer);
    setName(name);
    setFName(fname);
}

void Contact::CreateContact() {
    std::string tmp;

    std::cout << "Enter numer:" << std::endl;
    std::getline(std::cin, tmp);
    setNumer(tmp);

    std::cout << "Enter name:" << std::endl;
    std::getline(std::cin, tmp);
    setName(tmp);

    std::cout << "Enter surname:" << std::endl;
    std::getline(std::cin, tmp);
    setFName(tmp);

}


void Contact::setName(std::string &val) {
    if (val.length() == 0) {
        name = NODATA;
    } else {
        name = val;
    }
}

void Contact::setFName(std::string &val) {
    if (val.length() == 0) {
        fName = NODATA;
    } else {
        fName = val;
    }

}

void Contact::setNumer(std::string &val) {
    if (!normalizeNumer(val)) {
        std::cout << "Not a numer!" << std::endl;
        numer = NODATA;
        return;
    }

    numer = val;
}

std::string Contact::getNumer() {
    return numer;
}

std::string Contact::getName() {
    return name;
}

std::string Contact::getFName() {
    return fName;
}