#ifndef REKENING_H
#define REKENING_H

#include <string>
#include "utils.h"
#include "exception.h"
#include "transaksi.h"
#include "wadah.h"
using namespace std;


class Rekening {
protected:
    string noRek, tipe, tanggalBuka;
    double saldo;
    Wadah<Transaksi*> riwayat;
    int counter;

public:
  
    Rekening(const string& no, double sal, const string& tp)
        : noRek(no), saldo(sal), tipe(tp), tanggalBuka(getTime()), counter(0) {}

    
    virtual ~Rekening() {
        for (auto t : riwayat.semua()) delete t;
    }

    
    virtual double getBunga() const = 0;
    virtual string getInfo() const  = 0;


    void setor(double jml) {
        if (jml <= 0) throw JumlahSalah();
        saldo += jml;
        riwayat.tambah(new Setor("TXN" + to_string(++counter), jml));
    }
    void setor(double jml, const string&) { setor(jml); }

    void tarik(double jml) {
        if (jml <= 0) throw JumlahSalah();
        if (jml > saldo) throw SaldoKurang(saldo, jml);
        saldo -= jml;
        riwayat.tambah(new Tarik("TXN" + to_string(++counter), jml));
    }

    void transfer(double jml, const string& tujuan) {
        if (jml <= 0) throw JumlahSalah();
        if (jml > saldo) throw SaldoKurang(saldo, jml);
        saldo -= jml;
        riwayat.tambah(new Transfer("TXN" + to_string(++counter), jml, tujuan));
    }

   
    Rekening& operator+=(double n) { setor(n); return *this; }
    Rekening& operator-=(double n) { tarik(n); return *this; }
    bool operator==(const Rekening& o) const { return noRek == o.noRek; }

    void tambahSaldo(double n)           { saldo += n; }

   
    string getNoRek() const              { return noRek; }
    double getSaldo() const              { return saldo; }
    string getTipe() const               { return tipe; }
    Wadah<Transaksi*>& getRiwayat()      { return riwayat; }
};

class RekeningTabungan : public Rekening {
public:
    RekeningTabungan(const string& no, double sal)
        : Rekening(no, sal, "TABUNGAN") {}

    double getBunga() const override { return 0.035; }
    string getInfo() const override  { return "Tabungan Biasa | Bunga 3.5%/thn"; }
};

class RekeningPremium : public Rekening {
public:
    RekeningPremium(const string& no, double sal)
        : Rekening(no, sal, "PREMIUM") {}

    double getBunga() const override { return 0.055; }
    string getInfo() const override  { return "Premium | Bunga 5.5%/thn | Cashback 0.5%"; }
};

#endif 
