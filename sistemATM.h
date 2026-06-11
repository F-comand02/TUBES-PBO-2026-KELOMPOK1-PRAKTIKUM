#ifndef SISTEMATM_H
#define SISTEMATM_H


#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include "utils.h"
#include "exception.h"
#include "person.h"
#include "filemanager.h"
using namespace std;

class SistemATM {
    vector<Nasabah*> nasabahList;   
    vector<Admin*>   adminList;
    FileManager      fileMgr;
    Nasabah*         aktif;
    Admin*           adminAktif;
    int              noRekCounter;


    void header(const string& judul) {
        clearScreen();
        cout << BG_BLUE << BOLD << WHITE;
        cout << "\n+====================================================+\n";
        cout << "  | BANK ASLI GANTENG - " << left << setw(24) << judul << "|\n";
        cout << "  +====================================================+\n" << RESET;
        cout << CYAN << "  " << getTime() << "\n" << RESET;
    }

 
    double inputJumlah(const string& prompt) {
        double jml;
        cout << YELLOW << "  " << prompt << ": Rp " << RESET;
        cin >> jml;
        if (cin.fail() || jml <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw JumlahSalah();
        }
        return jml;
    }

    void daftarNasabah() {
        header("DAFTAR NASABAH BARU");
        garis();
        string nama, nim, telp, pin, tipe;

        cout << "\n" << YELLOW << "  Nama Lengkap      : " << RESET;
        cin.ignore(); getline(cin, nama);
        cout << YELLOW << "  NIM               : " << RESET; cin >> nim;
        cout << YELLOW << "  No. Telepon       : " << RESET; cin >> telp;
        cout << YELLOW << "  PIN ATM (6 digit) : " << RESET; cin >> pin;

        if (pin.size() != 6) { err("PIN harus 6 digit!"); enter(); return; }
        for (char c : pin)
            if (!isdigit(c)) { err("PIN hanya angka!"); enter(); return; }

        cout << "\n  Pilih jenis rekening:\n";
        cout << "  [1] Tabungan Biasa\n  [2] Rekening Premium\n";
        int pilih; cout << YELLOW << "  Pilihan: " << RESET; cin >> pilih;
        tipe = (pilih == 2) ? "PREMIUM" : "TABUNGAN";

       
        string noRek = "9900" + string(6 - to_string(++noRekCounter).size(), '0')
                       + to_string(noRekCounter);
        string noKartu = "4521" + string(12, '0');
        for (int i = 4; i < 16; i++)
            noKartu[i] = '0' + (noRekCounter * 7 + i) % 10;

       
        Rekening* rek;
        if (tipe == "PREMIUM") rek = new RekeningPremium(noRek, 0);
        else                   rek = new RekeningTabungan(noRek, 0);

        KartuATM* kartu = new KartuATM(noKartu, pin,
                                       tipe == "PREMIUM" ? "GOLD" : "SILVER");
        nasabahList.push_back(new Nasabah(nama, nim, telp, rek, kartu));

        cout << "\n"; ok("Pendaftaran berhasil!");
        cout << "  No. Rekening : " << BOLD << noRek << RESET << "\n";
        cout << "  Jenis        : " << tipe << "\n\n";
        cout << *kartu;   
        enter();
    }

  
    bool loginNasabah() {
        animasiKartu();
        header("LOGIN NASABAH");
        string noRek, pin;
        cout << "\n" << YELLOW << "  No. Rekening : " << RESET; cin >> noRek;
        cout << YELLOW << "  PIN          : " << RESET; cin >> pin;

        for (auto* n : nasabahList) {
            if (n->getNoRek() == noRek) {
                try {
                    if (n->getKartu()->cekPIN(pin)) {
                        aktif = n;
                        ok("Login berhasil! Selamat datang, " + n->getNama());
                        enter();
                        return true;
                    }
                } catch (exception& e) { err(e.what()); enter(); return false; }
                err("PIN salah!");
                enter();
                return false;
            }
        }
        err("Rekening tidak ditemukan!");
        enter();
        return false;
    }

   
    bool loginAdmin() {
        header("LOGIN ADMIN");
        string kode, pass;
        cout << "\n" << YELLOW << "  Kode Admin : " << RESET; cin >> kode;
        cout << YELLOW << "  Password   : " << RESET; cin >> pass;
        for (auto* a : adminList) {
            if (a->getId() == kode && a->login(pass)) {
                adminAktif = a;
                ok("Login admin berhasil!");
                enter();
                return true;
            }
        }
        err("Kode atau password salah!");
        enter();
        return false;
    }

  
    void cekSaldo() {
        header("CEK SALDO");
        Rekening* rek = aktif->getRekening();
        garis();
        cout << "\n  Nama     : " << BOLD << aktif->getNama() << RESET << "\n";
        cout << "  Rekening : " << rek->getNoRek() << "\n";
        cout << "  Tipe     : " << rek->getTipe() << "\n\n";
        cout << "  " << BG_GREEN << WHITE << BOLD
             << "  SALDO: " << rupiah(rek->getSaldo()) << "  " << RESET << "\n\n";
        cout << "  " << CYAN << rek->getInfo() << RESET << "\n";
        garis();
        enter();
    }

    void setorTunai() {
        header("SETOR TUNAI");
        try {
            double jml = inputJumlah("Jumlah Setor");
            aktif->getRekening()->setor(jml);
            fileMgr.simpanTransaksi(getTime() + " | " + aktif->getNoRek()
                                    + " | SETOR | " + rupiah(jml));
            cout << "\n"; ok("Setoran " + rupiah(jml) + " berhasil!");
            cout << "  Saldo baru: " << BG_GREEN << WHITE << BOLD << " "
                 << rupiah(aktif->getRekening()->getSaldo()) << " " << RESET << "\n";
        } catch (exception& e) { err(e.what()); }
        enter();
    }

    void tarikTunai() {
        header("TARIK TUNAI");
        try {
            vector<double> nominal = {100000, 200000, 500000, 1000000};
            cout << "\n  Pilih nominal:\n";
            for (int i = 0; i < (int)nominal.size(); i++)
                cout << "  [" << i+1 << "] " << rupiah(nominal[i]) << "\n";
            cout << "  [5] Jumlah lain\n\n";
            int pilih; cout << YELLOW << "  Pilihan: " << RESET; cin >> pilih;
            double jml;
            if (pilih >= 1 && pilih <= 4) jml = nominal[pilih - 1];
            else if (pilih == 5)           jml = inputJumlah("Jumlah Tarik");
            else throw runtime_error("Pilihan tidak valid!");
            aktif->getRekening()->tarik(jml);
            fileMgr.simpanTransaksi(getTime() + " | " + aktif->getNoRek()
                                    + " | TARIK | " + rupiah(jml));
            cout << "\n"; ok("Penarikan " + rupiah(jml) + " berhasil!");
            cout << "  Saldo baru: " << BG_GREEN << WHITE << BOLD << " "
                 << rupiah(aktif->getRekening()->getSaldo()) << " " << RESET << "\n";
        } catch (exception& e) { err(e.what()); }
        enter();
    }

    void transferDana() {
        header("TRANSFER");
        try {
            string tujuan;
            cout << "\n" << YELLOW << "  No. Rekening Tujuan: " << RESET; cin >> tujuan;
            Nasabah* penerima = nullptr;
            for (auto* n : nasabahList)
                if (n->getNoRek() == tujuan) { penerima = n; break; }
            if (!penerima) throw runtime_error("Rekening tujuan tidak ditemukan!");
            cout << "  Penerima: " << BOLD << penerima->getNama() << RESET << "\n\n";
            double jml = inputJumlah("Jumlah Transfer");
            cout << YELLOW << "\n  Konfirmasi? (y/n): " << RESET;
            char c; cin >> c;
            if (c != 'y' && c != 'Y') { cout << "  Dibatalkan.\n"; enter(); return; }
            aktif->getRekening()->transfer(jml, tujuan);
            penerima->getRekening()->tambahSaldo(jml);
            fileMgr.simpanTransaksi(getTime() + " | " + aktif->getNoRek()
                                    + " | TRANSFER | " + tujuan + " | " + rupiah(jml));
            cout << "\n"; ok("Transfer " + rupiah(jml) + " ke "
                             + penerima->getNama() + " berhasil!");
            cout << "  Saldo baru: " << BG_GREEN << WHITE << BOLD << " "
                 << rupiah(aktif->getRekening()->getSaldo()) << " " << RESET << "\n";
        } catch (exception& e) { err(e.what()); }
        enter();
    }

    void riwayatTransaksi() {
        header("RIWAYAT TRANSAKSI");
        auto& rwyt = aktif->getRekening()->getRiwayat();
        garis();
        if (rwyt.kosong()) { cout << "  Belum ada transaksi.\n"; enter(); return; }
        cout << "\n  " << CYAN << "Total transaksi: " << rwyt.ukuran()
             << "\n\n" << RESET;
        for (int i = 0; i < rwyt.ukuran(); i++)
            rwyt.ambil(i)->tampil();   
        garis();
        enter();
    }

    void gantiPIN() {
        header("GANTI PIN ATM");
        try {
            string lama, baru, konfirm;
            cout << "\n" << YELLOW << "  PIN Lama       : " << RESET; cin >> lama;
            cout << YELLOW << "  PIN Baru       : " << RESET; cin >> baru;
            cout << YELLOW << "  Konfirmasi PIN : " << RESET; cin >> konfirm;
            if (baru != konfirm) throw runtime_error("Konfirmasi PIN tidak cocok!");
            aktif->getKartu()->gantiPIN(lama, baru);
            cout << "\n"; ok("PIN berhasil diubah!");
        } catch (exception& e) { err(e.what()); }
        enter();
    }

    void simpanLaporan() {
        header("SIMPAN LAPORAN");
        try {
            ostringstream lap;
            lap << "Nasabah  : " << aktif->getNama() << "\n";
            lap << "Rekening : " << aktif->getNoRek() << "\n";
            lap << "Tipe     : " << aktif->getRekening()->getTipe() << "\n";
            lap << "Saldo    : " << rupiah(aktif->getRekening()->getSaldo()) << "\n\n";
            lap << "=== RIWAYAT TRANSAKSI ===\n";
            auto& rwyt = aktif->getRekening()->getRiwayat();
            for (int i = 0; i < rwyt.ukuran(); i++) {
                auto* t = rwyt.ambil(i);
                lap << t->getWaktu() << " | " << t->getJenis()
                    << " | " << rupiah(t->getJumlah()) << "\n";
            }
            fileMgr.simpanLaporan(lap.str());
            ok("Laporan berhasil disimpan!");
        } catch (exception& e) { err(e.what()); }
        enter();
    }


    void menuNasabah() {
        while (true) {
            clearScreen();
            cout << BG_BLUE << BOLD << WHITE;
            cout << "\n +====================================================+\n";
            cout << "  |        BANK ASLI GANTENG - NASABAH                |\n";
            cout << "  +===================================================+\n" << RESET;
            cout << "\n  " << CYAN << "Halo, " << BOLD << aktif->getNama() << RESET << "\n";
            cout << "  Saldo : " << GREEN << BOLD
                 << rupiah(aktif->getRekening()->getSaldo()) << RESET << "\n\n";
            garis();
            cout << "  [1] Cek Saldo           [2] Setor Tunai\n";
            cout << "  [3] Tarik Tunai         [4] Transfer\n";
            cout << "  [5] Riwayat Transaksi   [6] Ganti PIN\n";
            cout << "  [7] Data Saya           [8] Simpan Laporan\n";
            cout << "  " << RED << "[0] Logout\n" << RESET;
            garis();
            int pilih; cout << YELLOW << "\n  Pilihan: " << RESET; cin >> pilih;
            switch (pilih) {
                case 1: cekSaldo();          break;
                case 2: setorTunai();        break;
                case 3: tarikTunai();        break;
                case 4: transferDana();      break;
                case 5: riwayatTransaksi();  break;
                case 6: gantiPIN();          break;
                case 7:
                    header("DATA SAYA");
                    aktif->tampilInfo();
                    cout << "\n" << *aktif->getKartu();
                    enter();
                    break;
                case 8: simpanLaporan();     break;
                case 0:
                    cout << "\n  " << YELLOW << "Terima kasih, "
                         << aktif->getNama() << "!\n" << RESET;
                    aktif = nullptr;
                    return;
                default: err("Pilihan tidak valid!");
            }
        }
    }


    void menuAdmin() {
        while (true) {
            clearScreen();
            cout << "\n  " << BOLD << YELLOW << "MENU ADMIN - "
                 << adminAktif->getNama() << RESET << "\n\n";
            garis();
            cout << "  [1] Lihat Semua Nasabah\n";
            cout << "  " << RED << "[0] Logout\n" << RESET;
            garis();
            int pilih; cout << YELLOW << "\n  Pilihan: " << RESET; cin >> pilih;
            if (pilih == 1) {
                header("DAFTAR SEMUA NASABAH");
                cout << "\n  Total Nasabah: " << BOLD << nasabahList.size()
                     << RESET << "\n\n";
                cout << "  " << BOLD << left
                     << setw(20) << "NAMA" << setw(14) << "REKENING"
                     << setw(10) << "TIPE" << "SALDO" << RESET << "\n";
                garis();
                double total = 0;
                for (auto* n : nasabahList) {
                    double sal = n->getRekening()->getSaldo();
                    total += sal;
                    cout << "  " << left << setw(20) << n->getNama()
                         << setw(14) << n->getNoRek()
                         << setw(10) << n->getRekening()->getTipe()
                         << GREEN << rupiah(sal) << RESET << "\n";
                }
                garis();
                cout << "  Total Dana Bank: " << BG_GREEN << WHITE << BOLD
                     << " " << rupiah(total) << " " << RESET << "\n\n";
                enter();
            } else if (pilih == 0) {
                adminAktif = nullptr; return;
            } else {
                err("Pilihan tidak valid!");
            }
        }
    }

   
    void initAdmin() {
        adminList.push_back(
            new Admin("Budi Santoso", "ADM001", "admin123", "SUPERVISOR"));
    }

public:
 
    SistemATM() : aktif(nullptr), adminAktif(nullptr), noRekCounter(0) {
        initAdmin();
    }

   
    ~SistemATM() {
        for (auto* n : nasabahList) delete n;
        for (auto* a : adminList)   delete a;
    }

 
    void jalankan() {
        while (true) {
            clearScreen();
            cout << BG_BLUE << BOLD << WHITE;
            cout << "\n+====================================================+\n";
            cout << "  |              BANK ASLI GANTENG                     |\n";
            cout << "  |       Solusi Perbankan Digital Terpercaya          |\n";
            cout << "  +====================================================+\n" << RESET;
            cout << "\n  " << CYAN << getTime() << "\n\n" << RESET;
            garis();
            cout << "  [1] Login Nasabah\n";
            cout << "  [2] Daftar Nasabah Baru\n";
            cout << "  [3] Login Admin\n";
            cout << "  " << RED << "[0] Keluar\n" << RESET;
            garis();
            cout << BOLD << "  Info Admin : Kode ADM001 | Pass admin123\n" << RESET;
            garis();
            int pilih; cout << YELLOW << "\n  Pilihan: " << RESET; cin >> pilih;

            if      (pilih == 1) { if (loginNasabah()) menuNasabah(); }
            else if (pilih == 2) daftarNasabah();
            else if (pilih == 3) { if (loginAdmin()) menuAdmin(); }
            else if (pilih == 0) {
                cout << "\n  " << CYAN << BOLD
                     << "Terima kasih telah menggunakan Bank Asli Ganteng!\n"
                     << RESET << "\n";
                break;
            } else {
                err("Pilihan tidak valid!");
            }
        }
    }
};

#endif 
