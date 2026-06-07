#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

template<typename T>
void showData(T data)
{
    cout << data << endl;
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
public:

    Customer(string nama, string nim)
        : Person(nama,nim)
    {

    }

    void displayInfo() override
    {
        cout << "Nama : " << nama << endl;
        cout << "NIM  : " << nim << endl;
    }

    string getNama()
    {
        return nama;
    }

    string getNIM()
    {
        return nim;
    }

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
            cout << "Saldo tidak cukup!\n";
        }
    }

    double operator +(double jumlah)
    {
        return saldo + jumlah;
    }

    virtual void displayInfo()
    {
        cout << "Saldo : Rp "
             << fixed << setprecision(0)
             << saldo << endl;
    }

    double getSaldo()
    {
        return saldo;
    }

    virtual ~Account()
    {
        cout << "\nAccount ditutup.\n";
    }
};

class SavingsAccount : public Account
{
public:

    SavingsAccount(double saldo)
        : Account(saldo)
    {

    }

    void displayInfo() override
    {
        cout << "\n===== TABUNGAN REGULER =====\n";
        cout << "Saldo : Rp " << saldo << endl;
    }
};

class PremiumAccount : public Account
{
public:

    PremiumAccount(double saldo)
        : Account(saldo)
    {

    }

    void displayInfo() override
    {
        cout << "\n===== TABUNGAN PREMIUM =====\n";
        cout << "Saldo : Rp " << saldo << endl;
        cout << "Benefit : Cashback 5%\n";
    }
};

class FileManager
{
public:

    static void saveCustomer(Customer *cust, Account *acc)
    {
        ofstream file("laporanAcc.txt");

        file << "Nama : "
             << cust->getNama()
             << endl;

        file << "NIM : "
             << cust->getNIM()
             << endl;

        file << "Saldo terakhir : Rp "
             << acc->getSaldo()
             << endl;

        file.close();
    }

    static void saveTransaction(
        double setor,
        double tarik)
    {
        ofstream file("laporanTeller.txt");

        file << "Penyetoran : Rp "
             << setor
             << endl;

        file << "Penarikan : Rp "
             << tarik
             << endl;

        file.close();
    }
};

class Bank
{
private:

    Customer* customer;
    Account* account;

    double totalSetor = 0;
    double totalTarik = 0;

public:

    Bank()
    {
        customer = nullptr;
        account = nullptr;
    }

    void inputUser()
    {
        string nama,nim;

        cout << "\nNama : ";
        cin.ignore();
        getline(cin,nama);

        cout << "NIM : ";
        getline(cin,nim);

        customer = new Customer(
            nama,
            nim
        );

        int pilihan;

        cout << "\nJenis Rekening\n";
        cout << "1. Reguler\n";
        cout << "2. Premium\n";
        cout << "Pilih : ";
        cin >> pilihan;

        if(pilihan == 1)
        {
            account = new SavingsAccount(0);
        }
        else
        {
            account = new PremiumAccount(0);
        }
    }

    void cekSaldo()
{
    if(account == nullptr)
    {
        cout << "\n[ERROR] Silakan input data user terlebih dahulu!\n";
        return;
    }

    account->displayInfo();
}

    void setor()
{
    if(account == nullptr)
    {
        cout << "\n[ERROR] Silakan input data user terlebih dahulu!\n";
        return;
    }

    double jumlah;

    cout << "Jumlah setor : ";
    cin >> jumlah;

    if(jumlah <= 0)
    {
        cout << "Jumlah setor harus lebih dari 0!\n";
        return;
    }

    account->deposit(jumlah);

    totalSetor += jumlah;

    cout << "Berhasil setor!\n";
}

    void tarik()
{
    if(account == nullptr)
    {
        cout << "\n[ERROR] Silakan input data user terlebih dahulu!\n";
        return;
    }

    double jumlah;

    cout << "Jumlah tarik : ";
    cin >> jumlah;

    if(jumlah <= 0)
    {
        cout << "Jumlah tarik harus lebih dari 0!\n";
        return;
    }

    account->withdraw(jumlah);

    totalTarik += jumlah;
}

    void cekData()
    {
        if(customer)
        {
            customer->displayInfo();
        }
    }

    void laporan()
    {
        FileManager::saveCustomer(
            customer,
            account
        );

        FileManager::saveTransaction(
            totalSetor,
            totalTarik
        );

        cout << "\nLaporan berhasil dibuat!\n";
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

    int pilih;

    do
    {
        cout << "\n";
        cout << "====================================\n";
        cout << "      BANK USU DIGITAL SYSTEM\n";
        cout << "====================================\n";

        cout << "1. Input Data User\n";
        cout << "2. Cek Saldo\n";
        cout << "3. Setor Saldo\n";
        cout << "4. Tarik Saldo\n";
        cout << "5. Laporan Keuangan\n";
        cout << "6. Cek Data User\n";
        cout << "0. Exit\n";

        cout << "\nPilih : ";
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
            bank.laporan();
            break;

        case 6:
            bank.cekData();
            break;

        case 0:
            cout << "\nTerima kasih.\n";
            break;

        default:
            cout << "\nMenu tidak tersedia.\n";
        }

    }while(pilih != 0);

    return 0;
}