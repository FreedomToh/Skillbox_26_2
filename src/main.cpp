/*
  Mobilephone simulator 
*/
#include <iostream>
#include <vector>
#include "exception"
#include "regexpr.h"

RegExpr *r = new RegExpr;
std::string NODATA = "NODATA";

class Contact {
private:
    std::string name;
    std::string fName;
    std::string numer;

    bool normalizeNumer(std::string &str) {
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

public:

    Contact() {
        numer = NODATA;
        setName(NODATA);
        setFName(NODATA);
    }

    void CreateContact(std::string &numer, std::string &name, std::string &fname) {
        setNumer(numer);
        setName(name);
        setFName(fname);
    }

    void CreateContact() {
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


    void setName(std::string &val) {
        if (val.length() == 0) {
            name = NODATA;
        } else {
            name = val;
        }
    }

    void setFName(std::string &val) {
        if (val.length() == 0) {
            fName = NODATA;
        } else {
            fName = val;
        }

    }

    void setNumer(std::string &val) {
        if (!normalizeNumer(val)) {
            std::cout << "Not a numer!" << std::endl;
            numer = NODATA;
            return;
        }

        numer = val;
    }

    std::string getNumer() {
        return numer;
    }

    std::string getName() {
        return name;
    }

    std::string getFName() {
        return fName;
    }
};

class Phone {
private:
    std::vector<Contact*> contacts;

    bool isNumer(std::string &str) {
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


public:

    void add(std::string &numer, std::string &name, std::string &fname) {
        Contact *c = new Contact;
        c->CreateContact(numer, name, fname);
        contacts.push_back(c);
    }

    void add() {
        Contact *c = new Contact;
        c->CreateContact();
        contacts.push_back(c);
    }

    void deinit() {
        //delete all contacts
        for (int i = 0; i < contacts.size(); i++) delete contacts[i];
    }

    bool findContact(Contact &c) {
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

    void call() {

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

    void showContacts() {
        for (int i = 0; i < contacts.size(); i++) {
            std::string numer = contacts[i]->getNumer();
            std::string name = contacts[i]->getName();
            std::string fname = contacts[i]->getFName();

            std::cout << name << " " << fname << ": " << numer << std::endl;
        }
    }

    void sendSms() {
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
};

int main() {
    Phone *phone = new Phone;

    while (true) {
        std::cout << "Enter command:" << std::endl;
        std::string command;
        std::getline(std::cin, command);

        if (command == "add") {
            /*
            std::string numer = "+79232938883";
            std::string name = "Andrey";
            std::string fname = "Ivanov";
            phone->add(numer, name, fname);

            numer = "9271891251";
            name = "Viktor";
            fname = "Novikov";
            phone->add(numer, name, fname);
             */

            phone->add();

        } else if (command == "call") {
            phone->call();

        } else if (command == "sms") {
            phone->sendSms();

        } else if (command == "contacts") {
            phone->showContacts();

        } else if (command == "exit") {
            phone->deinit();
            break;
        }

    }
    delete phone;
}