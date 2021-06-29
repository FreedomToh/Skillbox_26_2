#include "phone.h"


bool Phone::isNumer(std::string &str) {
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

void Phone::add(std::string &numer, std::string &name, std::string &fname) {
    Contact *c = new Contact;
    c->CreateContact(numer, name, fname);
    contacts.push_back(c);
}

void Phone::add() {
    Contact *c = new Contact;
    c->CreateContact();
    contacts.push_back(c);
}

void Phone::deinit() {
    //delete all contacts
    for (int i = 0; i < contacts.size(); i++) delete contacts[i];
}

bool Phone::findContact(Contact &c) {
    std::cout << "Enter name and surname or numer:" << std::endl;
    std::string request;
    std::getline(std::cin, request);

    for (int i = 0; i < contacts.size(); i++) {
        std::string numer = contacts[i]->getNumer();
        std::string name = contacts[i]->getName();
        std::string fname = contacts[i]->getFName();
        isNumer(request); // normalize

        if (request == numer) {
            c = *contacts[i];
            return true;
        }

        if (request.find(' ') < request.size()) {
            std::string first = request.substr(0, request.find(' '));
            std::string second = request.substr(request.find(' ') + 1, request.size() - request.find(' '));

            if ((name == first && fname == second) || (name == second && fname == first)) {
                c = *contacts[i];
                return true;
            }
        }

    }
    if (isNumer(request)) {
        c.setNumer(request);
        return true;
    }

    return false;
}

void Phone::call() {

    Contact c;
    if (!findContact(c)) {
        std::cout << "Fail" << std::endl;
        return;
    }

    if (c.getName() != NODATA || c.getFName() != NODATA) {
        std::cout << "Calling to " << c.getName() << " " << c.getFName() << std::endl;
    } else {
        std::cout << "Calling to " << c.getNumer() << std::endl;
    }

    std::cout << "CALL " << c.getNumer() << std::endl;
    // realization

}

void Phone::showContacts() {
    for (int i = 0; i < contacts.size(); i++) {
        std::string numer = contacts[i]->getNumer();
        std::string name = contacts[i]->getName();
        std::string fname = contacts[i]->getFName();

        std::cout << name << " " << fname << ": " << numer << std::endl;
    }
}

void Phone::sendSms() {
    Contact c;
    if (!findContact(c)) {
        std::cout << "Fail" << std::endl;
        return;
    }

    std::cout << "Enter message: " << std::endl;
    std::string mess;
    std::getline(std::cin, mess);

    if (c.getName() != NODATA || c.getFName() != NODATA) {
        std::cout << "Sending message to " << c.getName() << " " << c.getFName() << std::endl;
    } else {
        std::cout << "Sending message to " << c.getNumer() << std::endl;
    }

    std::cout << "Sending..." << std::endl;
    // realiztion
    std::cout << "Message has been send." << std::endl;
}

