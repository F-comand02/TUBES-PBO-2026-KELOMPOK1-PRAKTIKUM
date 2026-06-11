#ifndef FILEMANAGER_H
#define FILEMANAGER_H


#include <fstream>
#include <string>
#include <stdexcept>
#include "utils.h"
using namespace std;

class FileManager {
public:
   
    void simpanLaporan(const string& isi) {
        ofstream f("laporan_bank.txt", ios::app);
        if (!f.is_open())
            throw runtime_error("Gagal membuka file laporan!");
        f << "\n" << string(50, '=') << "\n";
        f << "Tanggal: " << getTime() << "\n";
        f << string(50, '-') << "\n" << isi << "\n";
        f.close();
        cout << GREEN << "  Disimpan ke laporan_bank.txt\n" << RESET;
    }

 
    void simpanTransaksi(const string& data) {
        ofstream f("riwayat.txt", ios::app);
        if (f.is_open()) {
            f << data << "\n";
            f.close();
        }
    }
};

#endif 
