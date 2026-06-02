<div align="center">

# 🏦 BANK USU DIGITAL SYSTEM

### Tugas Besar Praktikum Pemrograman Berorientasi Objek 2026

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![OOP](https://img.shields.io/badge/Object-Oriented-green)
![USU](https://img.shields.io/badge/Universitas-Sumatera%20Utara-red)

</div>

Program Bank Sederhana berbasis **Object Oriented Programming (OOP)** yang dibuat untuk memenuhi tugas besar Praktikum Pemrograman Berorientasi Objek (PBO) Tahun 2026.

---

## 👨‍💻 Kelompok 1

| Nama | NIM |
|--------|--------|
| Farel Yamotaro Hia | 251402069 |
| Yabesh Day Siahaan | 251402004 |
| Jona V Gultom | 251402084 |
| Gabriel Parhusip | 251402043 |
| M Kevin Ramadhan | 251402013 |
| Ray Saragih | 251402046 |

---

## 📖 Deskripsi Program

BANK USU DIGITAL SYSTEM merupakan simulasi sistem perbankan sederhana yang memungkinkan pengguna untuk:

- Input data nasabah
- Melihat saldo rekening
- Melakukan penyetoran saldo
- Melakukan penarikan saldo
- Menampilkan data nasabah
- Membuat laporan keuangan
- Menyimpan data ke file

Program ini dikembangkan menggunakan konsep-konsep Object Oriented Programming (OOP) yang dipelajari selama perkuliahan.

---

## ✨ Fitur Program

### 👤 Manajemen Nasabah
- Input data nasabah
- Menampilkan data nasabah
- Nomor rekening otomatis

### 💰 Transaksi
- Setor saldo
- Tarik saldo
- Cek saldo

### 📊 Laporan
- Laporan data rekening
- Laporan transaksi
- Penyimpanan ke file TXT

### 🎨 Tampilan
- Menu interaktif
- Tampilan console berwarna
- Desain seperti sistem perbankan sederhana

---

## 🛠 Materi OOP yang Diimplementasikan

| Materi | Implementasi |
|----------|----------|
| Class & Object | Seluruh class program |
| Constructor | Constructor pada setiap class |
| Destructor | Destructor pada setiap class |
| Encapsulation | Penggunaan atribut private |
| Abstraction | Abstract class `Person` |
| Inheritance | `Customer` mewarisi `Person` |
| Method Overloading | Fungsi `deposit()` |
| Operator Overloading | Operator `+` pada Account |
| Overriding | `displayInfo()` |
| Polymorphism | Pointer class induk |
| Template | Fungsi template |
| Dynamic Memory Allocation | `new` dan `delete` |
| File Handling | Penyimpanan laporan ke file |

---

## 🏗 Struktur Class

```text
Person (Abstract Class)
│
└── Customer
     │
     └── Account
          ├── SavingsAccount
          └── PremiumAccount

FileManager
Bank
```

---

## 📂 Struktur File

```text
Project
│
├── main.cpp
├── laporanAcc.txt
├── laporanTeller.txt
├── history.txt
└── README.md
```

---

## 💻 Cara Menjalankan Program

### Compile

```bash
g++ main.cpp -o bank
```

### Run

```bash
./bank
```

atau pada Windows:

```bash
bank.exe
```

---

## 📸 Contoh Output

```text
====================================
      BANK USU DIGITAL SYSTEM
====================================

1. Input Data User
2. Cek Saldo
3. Setor Saldo
4. Tarik Saldo
5. Laporan Keuangan
6. Cek Data User
0. Exit

Pilih :
```

---

## 📄 Output Laporan

### laporanAcc.txt

```text
Nama : Timothy
NIM : 231402062
Saldo terakhir : Rp 20000
```

### laporanTeller.txt

```text
Penyetoran : Rp 120000
Penarikan : Rp 100000
```

---

## 🎯 Tujuan Project

Project ini dibuat untuk:

- Memahami konsep Object Oriented Programming
- Mengimplementasikan seluruh materi praktikum PBO
- Melatih penggunaan File Handling
- Mengembangkan program berbasis class secara terstruktur

---

## 📚 Teknologi

- C++
- OOP Programming
- File Handling
- Dynamic Memory Allocation

---

## © 2026

Praktikum Pemrograman Berorientasi Objek  
Universitas Sumatera Utara
