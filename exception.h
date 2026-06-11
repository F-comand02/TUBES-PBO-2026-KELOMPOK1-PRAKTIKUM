#ifndef EXCEPTION_H
#define EXCEPTION_H


#include <stdexcept>
#include "utils.h"
using namespace std;

class SaldoKurang : public exception {
    string msg;
public:
    SaldoKurang(double saldo, double butuh) {
        msg = "Saldo tidak cukup! Saldo: " + rupiah(saldo) + " | Butuh: " + rupiah(butuh);
    }
    const char* what() const noexcept override { return msg.c_str(); }
};


class JumlahSalah : public exception {
public:
    const char* what() const noexcept override {
        return "Jumlah harus lebih dari 0!";
    }
};

#endif
