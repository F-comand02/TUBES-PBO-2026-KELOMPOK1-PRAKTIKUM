#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdio>
#include <limits>

#ifdef _WIN32
    #include <windows.h>
    #include <io.h>
    #include <fcntl.h>
    #define SLEEP_MS(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

using namespace std;

enum class JenisTransaksi
{
    Setor,
    Tarik,
    TransferDebit,
    TopUp,
    BayarTagihan,
    Bunga
};

template<typename T>
void showData(T data)
{
    cout << data << endl;
}

string getTanggal()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);

    char buffer[20];

    snprintf(buffer, sizeof(buffer),
        "%02d/%02d/%04d",
        ltm->tm_mday,
        ltm->tm_mon + 1,
        ltm->tm_year + 1900
    );

    return buffer;
}

string jenisKeString(JenisTransaksi jenis)
{
    switch(jenis)
    {
        case JenisTransaksi::Setor:       return "Setor";
        case JenisTransaksi::Tarik:       return "Tarik";
        case JenisTransaksi::TransferDebit: return "Transfer";
        case JenisTransaksi::TopUp:       return "Top Up";
        case JenisTransaksi::BayarTagihan: return "Bayar Tagihan";
        case JenisTransaksi::Bunga:       return "Bunga";
        default:                          return "Unknown";
    }
}

struct Transaksi
{
    JenisTransaksi jenis;
    double jumlah;
    string keterangan;
    string tanggal;
};

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printTyping(const string& text, int delayMs = 40)
{
    for(char c : text)
    {
        cout << c << flush;
        SLEEP_MS(delayMs);
    }
}

void animasiMasukkanKartu()
{
    clearScreen();

    cout << "\n\n";
    cout << "  ╔══════════════════════════════════════════════╗\n";
    cout << "  ║                                              ║\n";
    cout << "  ║          BANK ONE HEARTH ONE MOTIF           ║\n";
    cout << "  ║                                              ║\n";
    cout << "  ╚══════════════════════════════════════════════╝\n";
    cout << "\n";

    SLEEP_MS(800);

    cout << "  ┌──────────────────────────────┐\n";
    cout << "  │   >>>  MASUKKAN KARTU ATM    │\n";
    cout << "  └──────────────────────────────┘\n\n";

    SLEEP_MS(600);

    string kartu = "  [===================";
    for(int i = 0; i <= 10; i++)
    {
      
        cout << "\r" << kartu.substr(0, kartu.size() - (10 - i)) + "]" << flush;
        SLEEP_MS(80);
    }
    cout << "\n";

    SLEEP_MS(400);
    printTyping("  Membaca kartu", 60);
    for(int i = 0; i < 3; i++)
    {
        SLEEP_MS(500);
        cout << "." << flush;
    }
    cout << "\n";

    SLEEP_MS(500);
    printTyping("  Kartu dikenali!", 40);
    cout << "\n";

    SLEEP_MS(400);

   
    cout << "\n  Memuat sistem  [";
    for(int i = 0; i < 20; i++)
    {
        SLEEP_MS(60);
        cout << "█" << flush;
    }
    cout << "] 100%\n";

    SLEEP_MS(500);

    clearScreen();


    cout << "\n\n";
    cout << "  ╔══════════════════════════════════════════════╗\n";
    cout << "  ║         SELAMAT DATANG DI                    ║\n";
    cout << "  ║         BANK ONE HEARTH ONE MOTIF            ║\n";
    cout << "  ║                                              ║\n";
    cout << "  ║         Silakan lengkapi data Anda.          ║\n";   
    cout << "  ║                                              ║\n";           
    cout << "  ╚══════════════════════════════════════════════╝\n\n";
}

// ─────────────────────────────────────────────

void tampilHeader()
{
    cout << "\n";
    cout << "=========================================================\n";
    cout << "                BANK ONE HEARTH ONE MOTIF                 \n";
    cout << "=========================================================\n";

    time_t now = time(0);
    cout << "Tanggal : " << ctime(&now);
    cout << "=========================================================\n";
}

class Person
{
protected:
    string nama;
    string nim;

public:
    Person(string nama, string nim)
    {
        this->nama = nama;
        this->nim = nim;
    }

    virtual void displayInfo() = 0;

    virtual ~Person()
    {
        cout << "\nDestructor Person\n";
    }
};

class Customer : public Person
{
private:
    string nomorRekening;

public:
    Customer(string nama, string nim)
        : Person(nama, nim)
    {
        nomorRekening = "USU" + nim;
    }

    void displayInfo() override
    {
        cout << "Nama            : " << nama << endl;
        cout << "NIM             : " << nim << endl;
        cout << "No Rekening     : " << nomorRekening << endl;
    }

    string getNama()      { return nama; }
    string getNIM()       { return nim; }
    string getNoRekening(){ return nomorRekening; }

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
    Account(double saldoAwal = 0) { saldo = saldoAwal; }

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
            saldo -= jumlah;
        else
            cout << "Saldo tidak cukup!\n";
    }

    double operator+(double jumlah) { return saldo + jumlah; }

    virtual void displayInfo()
    {
        cout << "Saldo : Rp "
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
    SavingsAccount(double saldo) : Account(saldo) {}

    void displayInfo() override
    {
        cout << "\n===== TABUNGAN REGULER =====\n";
        cout << "Saldo : Rp "
             << fixed << setprecision(0)
             << saldo << endl;
    }
};

class PremiumAccount : public Account
{
public:
    PremiumAccount(double saldo) : Account(saldo) {}

    void deposit(double jumlah) override
    {
        double cashback = jumlah * 0.05;
        saldo += jumlah + cashback;
        cout << "Cashback Premium : Rp " << cashback << endl;
    }

    void displayInfo() override
    {
        cout << "\n===== TABUNGAN PREMIUM =====\n";
        cout << "Saldo : Rp "
             << fixed << setprecision(0)
             << saldo << endl;
        cout << "Benefit : Cashback 5%\n";
    }
};

class FileManager
{
public:
    static bool saveCustomer(Customer* cust, Account* acc)
    {
        ofstream file("laporanAcc.txt");
        if(!file.is_open()) return false;

        file << "===== DATA NASABAH =====\n";
        file << "Nama          : " << cust->getNama() << endl;
        file << "NIM           : " << cust->getNIM() << endl;
        file << "No Rekening   : " << cust->getNoRekening() << endl;
        file << "Saldo Akhir   : Rp "
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
        if(!file.is_open()) return false;

        file << "===== LAPORAN TRANSAKSI =====\n\n";
        file << "Total Setor : Rp " << fixed << setprecision(0) << setor << endl;
        file << "Total Tarik : Rp " << fixed << setprecision(0) << tarik << endl;
        file << "\n===== RIWAYAT =====\n";

        for(const auto& t : riwayat)
        {
            file << t.tanggal
                 << " | " << jenisKeString(t.jenis)
                 << " | Rp " << fixed << setprecision(0) << t.jumlah;

            if(!t.keterangan.empty())
                file << " | " << t.keterangan;

            file << endl;
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
    string    pin;
    double    totalSetor;
    double    totalTarik;
    vector<Transaksi> riwayat;

    bool cekAktif()
    {
        if(customer == nullptr || account == nullptr)
        {
            cout << "\n[ERROR] Input data nasabah terlebih dahulu!\n";
            return false;
        }
        return true;
    }

    double inputNominal()
    {
        double jumlah;
        while(true)
        {
            cin >> jumlah;
            if(cin.fail() || jumlah <= 0)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Input tidak valid, ulangi : ";
            }
            else break;
        }
        return jumlah;
    }

public:
    Bank()
    {
        customer   = nullptr;
        account    = nullptr;
        totalSetor = 0;
        totalTarik = 0;
        pin        = "123456";
    }

    string levelNasabah()
    {
        if(!cekAktif()) return "-";
        double saldo = account->getSaldo();
        if(saldo >= 10000000) return "PLATINUM";
        if(saldo >= 5000000)  return "GOLD";
        if(saldo >= 1000000)  return "SILVER";
        return "REGULAR";
    }

    void inputUser()
    {
        if(customer) { delete customer; customer = nullptr; }
        if(account)  { delete account;  account  = nullptr; }

        totalSetor = 0;
        totalTarik = 0;
        riwayat.clear();

        string nama, nim;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << " ===== DATA DIRI =====\n";
        cout << " Nama : ";
        getline(cin, nama);

        cout << " NIM  : ";
        getline(cin, nim);

        customer = new Customer(nama, nim);

        int pilih;
        cout << "\nJenis Rekening\n";
        cout << "1. Reguler\n";
        cout << "2. Premium\n";

        do
        {
            cout << "Pilih : ";
            cin >> pilih;
        } while(pilih < 1 || pilih > 2);

        if(pilih == 1) account = new SavingsAccount(0);
        else           account = new PremiumAccount(0);

        cout << "\nAkun berhasil dibuat.\n";
    }

    void cekSaldo()
    {
        if(!cekAktif()) return;
        account->displayInfo();
    }

    void setor()
    {
        if(!cekAktif()) return;
        cout << "\nJumlah setor : Rp ";
        double jumlah = inputNominal();
        account->deposit(jumlah);
        totalSetor += jumlah;
        riwayat.push_back({ JenisTransaksi::Setor, jumlah, "", getTanggal() });
        cout << "Setor berhasil.\n";
    }

    void tarik()
    {
        if(!cekAktif()) return;
        cout << "\nJumlah tarik : Rp ";
        double jumlah = inputNominal();
        if(jumlah > account->getSaldo()) { cout << "Saldo tidak cukup.\n"; return; }
        account->withdraw(jumlah);
        totalTarik += jumlah;
        riwayat.push_back({ JenisTransaksi::Tarik, jumlah, "", getTanggal() });
        cout << "Penarikan berhasil.\n";
    }

    void transfer()
    {
        if(!cekAktif()) return;
        string tujuan;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nNo Rekening Tujuan : ";
        getline(cin, tujuan);
        cout << "Jumlah Transfer : Rp ";
        double jumlah = inputNominal();
        if(jumlah > account->getSaldo()) { cout << "Saldo tidak cukup.\n"; return; }
        account->withdraw(jumlah);
        totalTarik += jumlah;
        riwayat.push_back({ JenisTransaksi::TransferDebit, jumlah, "Transfer ke " + tujuan, getTanggal() });
        cout << "Transfer berhasil.\n";
    }

    void topUp()
    {
        if(!cekAktif()) return;
        string ewallet;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nNama E-Wallet : ";
        getline(cin, ewallet);
        cout << "Jumlah Top Up : Rp ";
        double jumlah = inputNominal();
        if(jumlah > account->getSaldo()) { cout << "Saldo tidak cukup.\n"; return; }
        account->withdraw(jumlah);
        totalTarik += jumlah;
        riwayat.push_back({ JenisTransaksi::TopUp, jumlah, ewallet, getTanggal() });
        cout << "Top Up berhasil.\n";
    }

    void bayarTagihan()
    {
        if(!cekAktif()) return;
        cout << "\n===== PILIH TAGIHAN =====\n";
        cout << "1. Listrik\n";
        cout << "2. Air\n";
        cout << "3. Internet\n";
        int pilih;
        cin >> pilih;
        string jenis;
        switch(pilih)
        {
            case 1: jenis = "Listrik";  break;
            case 2: jenis = "Air";      break;
            case 3: jenis = "Internet"; break;
            default: cout << "Pilihan salah.\n"; return;
        }
        cout << "Nominal Tagihan : Rp ";
        double jumlah = inputNominal();
        if(jumlah > account->getSaldo()) { cout << "Saldo tidak cukup.\n"; return; }
        account->withdraw(jumlah);
        totalTarik += jumlah;
        riwayat.push_back({ JenisTransaksi::BayarTagihan, jumlah, jenis, getTanggal() });
        cout << "Tagihan berhasil dibayar.\n";
    }

    void tambahBunga()
    {
        if(!cekAktif()) return;
        double bunga = account->getSaldo() * 0.02;
        account->deposit(bunga);
        riwayat.push_back({ JenisTransaksi::Bunga, bunga, "Bunga 2%", getTanggal() });
        cout << "Bunga masuk Rp " << fixed << setprecision(0) << bunga << endl;
    }

    void gantiPin()
    {
        string lama, baruPin;
        cout << "\nPIN lama : ";
        cin >> lama;
        if(lama != pin) { cout << "PIN salah.\n"; return; }
        cout << "PIN baru : ";
        cin >> baruPin;
        pin = baruPin;
        cout << "PIN berhasil diganti.\n";
    }

    void riwayatTransaksi()
    {
        if(!cekAktif()) return;
        cout << "\n=========== RIWAYAT TRANSAKSI ===========\n";
        if(riwayat.empty()) { cout << "Belum ada transaksi.\n"; return; }
        for(size_t i = 0; i < riwayat.size(); i++)
        {
            cout << "\n[" << i + 1 << "] " << riwayat[i].tanggal << endl;
            cout << "Jenis      : " << jenisKeString(riwayat[i].jenis) << endl;
            cout << "Jumlah     : Rp " << fixed << setprecision(0) << riwayat[i].jumlah << endl;
            if(!riwayat[i].keterangan.empty())
                cout << "Keterangan : " << riwayat[i].keterangan << endl;
            cout << "---------------------------------\n";
        }
        cout << "\nTotal Setor : Rp " << fixed << setprecision(0) << totalSetor << endl;
        cout << "Total Tarik : Rp " << fixed << setprecision(0) << totalTarik << endl;
    }

    void cekData()
    {
        if(!cekAktif()) return;
        cout << "\n=========== DATA NASABAH ===========\n";
        customer->displayInfo();
        cout << "Level Nasabah : " << levelNasabah() << endl;
        account->displayInfo();
    }

    void laporan()
    {
        if(!cekAktif()) return;
        bool ok1 = FileManager::saveCustomer(customer, account);
        bool ok2 = FileManager::saveTransaction(totalSetor, totalTarik, riwayat);
        if(ok1 && ok2)
        {
            cout << "\nLaporan berhasil disimpan.\n";
            cout << "1. laporanAcc.txt\n";
            cout << "2. laporanTeller.txt\n";
        }
        else cout << "\nGagal menyimpan laporan.\n";
    }

    ~Bank()
    {
        delete customer;
        delete account;
    }
};

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    Bank bank;

    animasiMasukkanKartu();
    bank.inputUser();

    int pilih;

    do
    {
        tampilHeader();

        cout << "\n";
        cout << "=============== PILIH MENU ===============\n";
        cout << "1. Cek Saldo\n";
        cout << "2. Setor Tunai\n";
        cout << "3. Tarik Tunai\n";
        cout << "4. Transfer\n";
        cout << "5. Riwayat Transaksi\n";
        cout << "6. Simpan Laporan\n";
        cout << "7. Cek Data Nasabah\n";
        cout << "8. Ganti PIN\n";
        cout << "9. Tambah Bunga 2%\n";
        cout << "10. Top Up E-Wallet\n";
        cout << "11. Bayar Tagihan\n";
        cout << "0. Keluar\n";
        cout << "===========================================\n";

        cout << "\nPilih Menu : ";
        cin >> pilih;

        switch(pilih)
        {
            case 1:  bank.cekSaldo();          break;
            case 2:  bank.setor();             break;
            case 3:  bank.tarik();             break;
            case 4:  bank.transfer();          break;
            case 5:  bank.riwayatTransaksi();  break;
            case 6:  bank.laporan();           break;
            case 7:  bank.cekData();           break;
            case 8:  bank.gantiPin();          break;
            case 9:  bank.tambahBunga();       break;
            case 10: bank.topUp();             break;
            case 11: bank.bayarTagihan();      break;
            case 0:
                cout << "\n=====================================\n";
                cout << "Terima kasih telah berkunjung\n";
                cout << "BANK ONE HEARTH ONE MOTIF\n";
                cout << "=====================================\n";
                break;
            default:
                cout << "\nMenu tidak tersedia.\n";
        }

        if(pilih != 0)
        {
            cout << "\nTekan ENTER untuk lanjut...";
            cin.ignore();
            cin.get();
        }

    } while(pilih != 0);

    return 0;
}