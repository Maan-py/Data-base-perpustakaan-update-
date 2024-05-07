#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
// file yang di include
#include "DBanggota.h"
#include "DBbuku.h"
using namespace std;
// daftar deklarasi porsedur
void clearScreen()
{
#ifdef _WIN32 // For windows
    system("cls");
#else
    system("clear"); // for linux
#endif
}
// prosedur dari anggota
void DBanggota();
// prosedur dari buku
void DBbuku();
void DBstatus();
// end
// struktur database
int main()
{
    int pilihan;
    cout << "Pilihan program: " << endl;
    cout << "1. Database Anggota\n"
         << "2. Database Buku\n"
         << "3. Database Status Buku\n";
    cout << "Pilih: ";
    cin >> pilihan;
    switch (pilihan)
    {
    case 1:
        // anggota
        DBanggota();
        break;
    case 2:
        // buku
        DBbuku();
        break;
    case 3:
        // status
        DBstatus();
        break;
    case 4:
        //
    default:
        break;
    }
    DBanggota();
    // database pusat yang untuk cek seluruh data

    // endl
}
// Database
enum status
{
    dipinjam,
    dikembalikan,
    terlambat
};
struct peminjaman
{
    string id_anggota;
    int ISBN;
    string buku_yang_dipinjam;
    string tanggal_peminjaman;
    string tanggal_jatuh_tempo;
    status status_peminjaman;
};
void inputS()
{
    vector<anggota> log_peminjaman;
    int jumlah_peminjaman;
    cout << "Silahkan masukkan jumlah data peminjaman!" << endl;
    cout << "Jumlah data: ";
    cin >> jumlah_peminjaman;
    cin.ignore();
}
void ouputS()
{
}
void HapusS()
{
}
void updateS()
{
}
void DBstatus()
{
    int pilih;
    cout << "Lakukan administrasi buku: " << endl;
    cout << "Menu pilihan: " << endl;
    cout << "1. Kelola data\n"
         << "2. Tampilkan data\n"
         << endl;
    cout << "Pilih: ";
    cin >> pilih;
    if (pilih == 1)
    {
        int pilih_menu;
        cout << "Apa yang ingin anda lakukan: \n"
             << "1. Buat peminjaman baru\n"
             << "2. Ubah status peminjaman\n"
             << "3. Hapus data peminjaman\n";
        cout << "Pilih: ";
        cin >> pilih_menu;
        switch (pilih_menu)
        {
        case 1:
            inputS();
            break;
        case 2:
            updateS();
            break;
        case 3:
            HapusS();
            break;
        }
    }
    if (pilih == 2)
    {
        ouputS();
    }
}
