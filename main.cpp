/*
  Bank Asli Ganteng | Kelompok 1 PBO

  Kelompok 1 Praktikum Pemrograman Berorientasi Objek:
  1. Farel Yamotaro Hia       (PM GANTENG) (251402069)
  2. Gabriel Saurman Parhusip (251402043)  (Si ganteng)
  3. Yabesh Day Siahaan       (251402004)  (Si tampan)
  4. Ray Nathan Geereno Saragih (251402046)(Si cakep)
  5. M Kevin Ramadhan         (251402013)  (Si cool)
  6. Jona Vebrian Gultom      (251402084)  (Si imut)

*/

#include "sistemATM.h"

int main() {
    enableAnsi();
    try {
        SistemATM atm;  
        atm.jalankan();
    } catch (exception& e) {
        cerr << RED << "Error fatal: " << e.what() << RESET << "\n";
        return 1;
    }
    return 0;   
}
