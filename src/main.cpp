/*
  Mobilephone simulator 
*/
#include <iostream>
#include <exception>
#include "contact.h"
#include "phone.h"


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