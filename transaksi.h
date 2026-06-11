#ifndef TRANSAKSI_H
#define TRANSAKSI_H

#include <iostream>
#include <string>
#include "utils.h"
#include "wadah.h"
using namespace std;


class Transaksi {
protected:
    string id, waktu, keterangan;
    double jumlah;

public:
  
    Transaksi(const string& id_, double jml, const string& ket)
        : id(id_), jumlah(jml), keterangan(ket), waktu(getTime()) {}

   
    virtual ~Transaksi() {}

  
    virtual string getJenis() const = 0;

   
    virtual void tampil() const {
        cout << CYAN << "  [" << getJenis() << "] " << RESET
             << GREEN << rupiah(jumlah) << RESET
             << "  " << waktu << "\n"
             << "     " << keterangan << "\n\n";
    }

   
    bool operator>(const Transaksi& o) const  { return jumlah > o.jumlah; }
    bool operator==(const Transaksi& o) const { return id == o.id; }


    double getJumlah() const      { return jumlah; }
    string getWaktu() const       { return waktu; }
    string getKeterangan() const  { return keterangan; }
    string getId() const          { return id; }
};


class Setor : public Transaksi {
public:
    Setor(const string& id, double jml)
        : Transaksi(id, jml, "Setor Tunai") {}
    string getJenis() const override { return "SETOR"; }
};


class Tarik : public Transaksi {
public:
    Tarik(const string& id, double jml)
        : Transaksi(id, jml, "Tarik Tunai") {}
    string getJenis() const override { return "TARIK"; }
};


class Transfer : public Transaksi {
public:
    Transfer(const string& id, double jml, const string& tujuan)
        : Transaksi(id, jml, "Transfer ke " + tujuan) {}
    string getJenis() const override { return "TRANSFER"; }
};

#endif 
