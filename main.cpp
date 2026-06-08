#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <ctime>
#include <limits>

using namespace std;

enum class JenisTransaksi { SETOR, TARIK, TRANSFER };

template<typename T>
void showData(T data)
{
    cout << data << endl;
}


struct Transaksi
{
    string jenis;
    double jumlah;
};


class Person
{
protected:
    string nama;
    string nim;

public:

    Person(string nama, string nim)
    {
        this->nama = nama;
        this->nim   = nim;
    }

    virtual void displayInfo() = 0;

    virtual ~Person()
    {
        cout << "\nDestructor Person\n";
    }
};


class Customer : public Person
{
public:

    Customer(string nama, string nim)
        : Person(nama, nim) {}

    void displayInfo() override
    {
        cout << "  Nama  : " << nama << endl;
        cout << "  NIM   : " << nim  << endl;
    }

    string getNama() { return nama; }
    string getNIM()  { return nim;  }

    ~Customer()
    {
        cout << "\nCustomer keluar.\n";
    }
};


class Account
{
protected:
    double saldo;

public:

    Account(double saldoAwal = 0)
    {
        saldo = saldoAwal;
    }

    virtual void deposit(double jumlah)
    {
        saldo += jumlah;
    }

    virtual void deposit(double jumlah, double bonus)
    {
        saldo += jumlah + bonus;
    }

    virtual void withdraw(double jumlah)
    {
        if(jumlah <= saldo)
        {
            saldo -= jumlah;
        }
        else
        {
            cout << "  [!] Saldo tidak cukup!\n";
        }
    }

    double operator +(double jumlah)
    {
        return saldo + jumlah;
    }

    virtual void displayInfo()
    {
        cout << "  Saldo : Rp "
             << fixed << setprecision(0)
             << saldo << endl;
    }

    double getSaldo() { return saldo; }

    virtual ~Account()
    {
        cout << "\nAccount ditutup.\n";
    }
};


class SavingsAccount : public Account
{
public:

    SavingsAccount(double saldo)
        : Account(saldo) {}

    void displayInfo() override
    {
        cout << "\n  ===== TABUNGAN REGULER =====\n";
        cout << "  Saldo : Rp "
             << fixed << setprecision(0)
             << saldo << "\n";
    }
};


class PremiumAccount : public Account
{
public:

    PremiumAccount(double saldo)
        : Account(saldo) {}

    void displayInfo() override
    {
        cout << "\n  ===== TABUNGAN PREMIUM =====\n";
        cout << "  Saldo   : Rp "
             << fixed << setprecision(0)
             << saldo << "\n";
        cout << "  Benefit : Cashback 5%\n";
    }
};


class FileManager
{
public:

    static bool saveCustomer(Customer *cust, Account *acc)
    {
        ofstream file("laporanAcc.txt");

        if(!file.is_open())
            return false;

        file << "Nama          : " << cust->getNama() << endl;
        file << "NIM           : " << cust->getNIM()  << endl;
        file << "Saldo terakhir: Rp "
             << fixed << setprecision(0)
             << acc->getSaldo() << endl;

        file.close();
        return true;
    }

    static bool saveTransaction(
        double setor,
        double tarik,
        const vector<Transaksi>& riwayat)
    {
        ofstream file("laporanTeller.txt");

        if(!file.is_open())
            return false;

        file << "Penyetoran : Rp "
             << fixed << setprecision(0)
             << setor << endl;

        file << "Penarikan  : Rp "
             << fixed << setprecision(0)
             << tarik << endl;

        file << "\n--- Riwayat Transaksi ---\n";
        for(const auto& t : riwayat)
        {
            file << t.jenis << " Rp "
                 << fixed << setprecision(0)
                 << t.jumlah << endl;
        }

        file.close();
        return true;
    }
};


class Bank
{
private:

    Customer* customer;
    Account*  account;

    double totalSetor = 0;
    double totalTarik = 0;

    vector<Transaksi> riwayat;


    bool cekAktif()
    {
        if(account == nullptr || customer == nullptr)
        {
            cout << "\n  [ERROR] Silakan input data user terlebih dahulu!\n";
            return false;
        }
        return true;
    }

public:

    Bank()
    {
        customer = nullptr;
        account  = nullptr;
    }

    void inputUser()
    {
        if(customer) { delete customer; customer = nullptr; }
        if(account)  { delete account;  account  = nullptr; }
        riwayat.clear();
        totalSetor = 0;
        totalTarik = 0;

        string nama, nim;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\n  Nama : ";
        getline(cin, nama);

        cout << "  NIM  : ";
        getline(cin, nim);

        customer = new Customer(nama, nim);

        int pilihan;

        cout << "\n  Jenis Rekening\n";
        cout << "  1. Reguler\n";
        cout << "  2. Premium\n";

        do
        {
            cout << "  Pilih (1/2) : ";
            cin >> pilihan;

            if(pilihan != 1 && pilihan != 2)
                cout << "  [!] Pilihan tidak valid. Masukkan 1 atau 2.\n";

        } while(pilihan != 1 && pilihan != 2);

        if(pilihan == 1)
            account = new SavingsAccount(0);
        else
            account = new PremiumAccount(0);

        cout << "\n  [OK] Akun berhasil dibuat!\n";
    }

    void cekSaldo()
    {
        if(!cekAktif()) return;
        account->displayInfo();
    }

    void setor()
    {
        if(!cekAktif()) return;

        double jumlah;

        cout << "\n  Jumlah setor : Rp ";
        cin >> jumlah;

        if(jumlah <= 0)
        {
            cout << "  [!] Jumlah setor harus lebih dari 0!\n";
            return;
        }

        account->deposit(jumlah);
        totalSetor += jumlah;
        riwayat.push_back({"Setor", jumlah});

        cout << "  [OK] Berhasil setor Rp "
             << fixed << setprecision(0)
             << jumlah << "!\n";
    }

    void tarik()
    {
        if(!cekAktif()) return;

        double jumlah;

        cout << "\n  Jumlah tarik : Rp ";
        cin >> jumlah;

        if(jumlah <= 0)
        {
            cout << "  [!] Jumlah tarik harus lebih dari 0!\n";
            return;
        }

        if(jumlah > account->getSaldo())
        {
            cout << "  [!] Saldo tidak cukup!\n";
            return;
        }

        account->withdraw(jumlah);
        totalTarik += jumlah;
        riwayat.push_back({"Tarik", jumlah});

        cout << "  [OK] Berhasil tarik Rp "
             << fixed << setprecision(0)
             << jumlah << "!\n";
    }


    void transfer()
    {
        if(!cekAktif()) return;

        string noRek;
        double jumlah;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\n  No. Rekening Tujuan : ";
        getline(cin, noRek);

        if(noRek.empty())
        {
            cout << "  [!] Nomor rekening tidak boleh kosong!\n";
            return;
        }

        cout << "  Jumlah transfer    : Rp ";
        cin >> jumlah;

        if(jumlah <= 0)
        {
            cout << "  [!] Jumlah transfer harus lebih dari 0!\n";
            return;
        }

        if(jumlah > account->getSaldo())
        {
            cout << "  [!] Saldo tidak cukup!\n";
            return;
        }

        account->withdraw(jumlah);
        totalTarik += jumlah;
        riwayat.push_back({"Transfer ke " + noRek, jumlah});

        cout << "  [OK] Transfer Rp "
             << fixed << setprecision(0)
             << jumlah << " ke " << noRek << " berhasil!\n";
    }


    void riwayatTransaksi()
    {
        if(!cekAktif()) return;

        cout << "\n  ===== RIWAYAT TRANSAKSI =====\n";

        if(riwayat.empty())
        {
            cout << "  Belum ada transaksi.\n";
            return;
        }

        for(size_t i = 0; i < riwayat.size(); i++)
        {
            cout << "  " << (i + 1) << ". "
                 << riwayat[i].jenis << " : Rp "
                 << fixed << setprecision(0)
                 << riwayat[i].jumlah << "\n";
        }

        cout << "  -----------------------------\n";
        cout << "  Total Setor : Rp "
             << fixed << setprecision(0)
             << totalSetor << "\n";
        cout << "  Total Tarik : Rp "
             << fixed << setprecision(0)
             << totalTarik << "\n";
    }

    void cekData()
    {
        if(!cekAktif()) return;

        cout << "\n  ===== DATA NASABAH =====\n";
        customer->displayInfo();
        account->displayInfo();
    }

    void laporan()
    {
        if(!cekAktif()) return;

        bool ok1 = FileManager::saveCustomer(customer, account);
        bool ok2 = FileManager::saveTransaction(totalSetor, totalTarik, riwayat);

        if(!ok1 || !ok2)
        {
            cout << "\n  [!] Gagal menyimpan laporan. Periksa izin folder.\n";
            return;
        }

        cout << "\n  [OK] Laporan berhasil disimpan ke file!\n";
        cout << "       - laporanAcc.txt\n";
        cout << "       - laporanTeller.txt\n";
    }

    ~Bank()
    {
        delete customer;
        delete account;
    }
};


int main()
{
    Bank bank;
    int  pilih;

    do
    {
        cout << "\n";
        cout << "  +=====================================+\n";
        cout << "  |      BANK USU DIGITAL SYSTEM        |\n";
        cout << "  |      Sistem Perbankan Digital       |\n";
        cout << "  +=====================================+\n";
        cout << "  | 1. Input / Ganti Data Nasabah       |\n";
        cout << "  | 2. Cek Saldo                        |\n";
        cout << "  | 3. Setor Saldo                      |\n";
        cout << "  | 4. Tarik Saldo                      |\n";
        cout << "  | 5. Transfer                         |\n";
        cout << "  | 6. Riwayat Transaksi                |\n";
        cout << "  | 7. Laporan Keuangan (simpan file)   |\n";
        cout << "  | 8. Cek Data Nasabah                 |\n";
        cout << "  | 0. Keluar                           |\n";
        cout << "  +=====================================+\n";

        cout << "\n  Pilih menu : ";
        cin >> pilih;

        switch(pilih)
        {
        case 1:
            bank.inputUser();
            break;

        case 2:
            bank.cekSaldo();
            break;

        case 3:
            bank.setor();
            break;

        case 4:
            bank.tarik();
            break;

        case 5:
            bank.transfer();
            break;

        case 6:
            bank.riwayatTransaksi();
            break;

        case 7:
            bank.laporan();
            break;

        case 8:
            bank.cekData();
            break;

        case 0:
            cout << "\n  Terima kasih telah menggunakan Bank USU!\n\n";
            break;

        default:
            cout << "\n  [!] Menu tidak tersedia. Coba lagi.\n";
        }

    } while(pilih != 0);

    return 0;
}
