#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include "utils.h"
#include "rekening.h"
#include "kartu.h"
using namespace std;

class Person {
protected:
    string nama, id, telp;

public:

    Person(const string& n, const string& i, const string& t)
        : nama(n), id(i), telp(t) {}

 
    virtual ~Person() {}

   
    virtual void tampilInfo() const = 0;
    virtual string getPeran() const = 0;

   
    bool operator==(const Person& o) const { return id == o.id; }
    friend ostream& operator<<(ostream& os, const Person& p) {
        os << BOLD << p.nama << RESET << " (" << p.id << ")";
        return os;
    }

    string getNama() const { return nama; }
    string getId() const   { return id; }
};


class Nasabah : public Person {
    Rekening* rekening;
    KartuATM* kartu;

public:

    Nasabah(const string& n, const string& nim, const string& t,
            Rekening* rek, KartuATM* atm)
        : Person(n, nim, t), rekening(rek), kartu(atm) {}


    ~Nasabah() {
        delete rekening;
        delete kartu;
    }

  
    void tampilInfo() const override {
        garis();
        cout << CYAN << "  Nama     : " << RESET << BOLD << nama << RESET << "\n";
        cout << CYAN << "  NIM      : " << RESET << id << "\n";
        cout << CYAN << "  Telepon  : " << RESET << telp << "\n";
        cout << CYAN << "  Rekening : " << RESET << rekening->getNoRek() << "\n";
        cout << CYAN << "  Tipe     : " << RESET << rekening->getTipe() << "\n";
        cout << CYAN << "  Saldo    : " << RESET << GREEN << BOLD
             << rupiah(rekening->getSaldo()) << RESET << "\n";
    }

    string getPeran() const override { return "NASABAH"; }


    Rekening* getRekening() const { return rekening; }
    KartuATM* getKartu() const   { return kartu; }
    string    getNoRek() const   { return rekening->getNoRek(); }
};


class Admin : public Person {
    string password, level;

public:

    Admin(const string& n, const string& kode,
          const string& pwd, const string& lvl)
        : Person(n, kode, "-"), password(pwd), level(lvl) {}

  
    bool login(const string& pwd) const { return pwd == password; }


    void tampilInfo() const override {
        cout << CYAN << "  Nama  : " << RESET << BOLD << nama << RESET << "\n";
        cout << CYAN << "  Kode  : " << RESET << id << "\n";
        cout << CYAN << "  Level : " << RESET << YELLOW << level << RESET << "\n";
    }

    string getPeran() const override { return "ADMIN"; }
};

#endif 
