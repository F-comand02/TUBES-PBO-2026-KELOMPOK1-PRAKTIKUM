#ifndef WADAH_H
#define WADAH_H


#include <vector>
using namespace std;

template<typename T>
class Wadah {
    vector<T> data;  
public:
    void tambah(const T& item)  { data.push_back(item); }
    T& ambil(int i)             { return data[i]; }
    int ukuran() const          { return (int)data.size(); }
    bool kosong() const         { return data.empty(); }
    vector<T>& semua()          { return data; }
};

#endif 
