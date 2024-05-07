#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

struct buku
{
    int ISBN;
    string judul;
    string penulis;
    int tahun_terbit;
    int jumlah_eksemplar;
};

void inputdata_baru(const string &file_buku)
{
    // membuat vektor untuk menyimpan data tanpa secara manual
    vector<buku> daftar_buku;
    // input data
    int stok_buku; // jumlah data
    cout << "Silahkan Masukkan jumlah buku!" << endl;
    cout << "Jumlah buku: ";
    cin >> stok_buku;
    cin.ignore();
    for (int i = 0; i < stok_buku; ++i)
    {
        // menyimpan di variabel temp
        buku temp;
        cout << "Masukkan data buku ke-" << i + 1 << ":" << endl;
        cout << "ISBN             : ";
        cin >> temp.ISBN;
        cin.ignore();
        cout << "Judul            : ";
        getline(cin, temp.judul);
        cout << "Penulis          : ";
        getline(cin, temp.penulis);
        cout << "Tahun Terbit     : ";
        cin >> temp.tahun_terbit;
        cout << "Jumlah Eksemplar : ";
        cin >> temp.jumlah_eksemplar;
        cout << endl;
        daftar_buku.push_back(temp);
    }

    ofstream file(file_buku, ios::app);
    if (file.is_open())
    {
        // const auto &b digunakan untuk mengakses vector daftar buku
        // contoh jika tanpa menggunakan const auto &b
        // for(size_t i = 1;i < daftar_buku.size();++i)
        // {
        //  buku &b = daftar[i];
        // }
        // size_t untuk menyimpan ukuran maksimum vector
        for (const auto &b : daftar_buku)
        {
            file << b.ISBN << "," << b.judul << ","
                 << b.penulis << "," << b.tahun_terbit << ","
                 << b.jumlah_eksemplar << "\n";
        }
        file.close();

        cout << "Data berhasil diinput ke " << file_buku << endl;
    }
    else
    {
        cout << "Gagal membuka " << file_buku << " untuk penulisan." << endl;
    }
}

void output_data(const string &file_buku)
{
    ifstream file(file_buku);
    if (file.is_open())
    {
        buku temp_b;
        int indeks = 1;
        cout << "Isi Database Buku:\n";
        // inisialisasi baris yang ada di file yang disimpan(database_buku.txt)
        string line;
        // membaca setiap baris yang ada di file. tugas akan berlanjut/atau berulang selama
        // masih ada yang tulisan pada baris file.
        while (getline(file, line))
        {
            stringstream ss(line);
            ss >> temp_b.ISBN;
            ss.ignore();
            getline(ss, temp_b.judul, ',');
            getline(ss, temp_b.penulis, ',');
            ss >> temp_b.tahun_terbit;
            ss.ignore();
            ss >> temp_b.jumlah_eksemplar;
            cout << "Buku ke-" << indeks << ":" << endl;
            cout << "ISBN             : " << temp_b.ISBN << endl;
            cout << "Judul            : " << temp_b.judul << endl;
            cout << "Penulis          : " << temp_b.penulis << endl;
            cout << "Tahun terbit     : " << temp_b.tahun_terbit << endl;
            cout << "Jumlah eksemplar : " << temp_b.jumlah_eksemplar << endl;
            cout << endl;
            indeks++;
        }
        file.close();
    }
    else
    {
        cout << "Gagal membuka "
             << file_buku
             << " untuk pembacaan." << endl;
    }
}
// hapus data
void hapus(const string &file_buku, const string &temp_buku)
{
    // membuat file temp_buku.txt
    ofstream file_temp(temp_buku);
    //
    ifstream file_sumber(file_buku);

    if (!file_temp.is_open() || !file_sumber.is_open())
    {
        cout << "Gagal membuka file." << endl;
        return;
    }

    cin.ignore();
    string judul;
    cout << "Masukkan judul atau ISBN buku yang ingin dihapus: ";
    getline(cin, judul);

    string line;
    bool buku_ditemukan = false;
    while (getline(file_sumber, line))
    {
        stringstream ss(line);
        buku temp;
        ss >> temp.ISBN;
        ss.ignore();
        getline(ss, temp.judul, ',');
        getline(ss, temp.penulis, ',');
        ss >> temp.tahun_terbit;
        ss.ignore();
        ss >> temp.jumlah_eksemplar;

        // ubah judul agar tidak terlalu sensitive
        string judul_lower = temp.judul;
        transform(judul_lower.begin(), judul_lower.end(), judul_lower.begin(), ::tolower);
        string judul_input_lower = judul;
        transform(judul_input_lower.begin(), judul_input_lower.end(), judul_input_lower.begin(), ::tolower);

        if (judul_input_lower == judul_lower || to_string(temp.ISBN) == judul)
        {
            cout << "Buku yang akan dihapus: " << endl;
            cout << "ISBN             : " << temp.ISBN << endl;
            cout << "Judul            : " << temp.judul << endl;
            cout << "Penulis          : " << temp.penulis << endl;
            cout << "Tahun terbit     : " << temp.tahun_terbit << endl;
            cout << "Jumlah eksemplar : " << temp.jumlah_eksemplar << endl;
            cout << endl;

            char konfirmasi;
            cout << "Apakah anda yakin ingin menghapus buku ini? (y/n): ";
            cin >> konfirmasi;

            if (konfirmasi == 'y' || konfirmasi == 'Y')
            {
                buku_ditemukan = true;
            }
        }
        else
        {
            file_temp << line << endl;
        }
    }

    file_temp.close();
    file_sumber.close();

    if (buku_ditemukan)
    {
        if (remove(file_buku.c_str()) != 0)
        {
            cout << "Gagal menghapus buku dari database." << endl;
            return;
        }

        if (rename(temp_buku.c_str(), file_buku.c_str()) != 0)
        {
            cout << "Gagal mengubah nama file sementara." << endl;
            return;
        }

        cout << "Buku berhasil dihapus dari database." << endl;
    }
    else
    {
        cout << "Buku dengan judul atau ISBN '" << judul << "' tidak ditemukan dalam database atau tidak dihapus." << endl;
    }
}

// update data
void update(const string &file_buku)
{
    ifstream file(file_buku);
    if (!file.is_open())
    {
        cout << "Gagal membuka file" << file_buku << endl;
        return;
    }

    vector<buku> daftar_buku;
    buku temp_b;
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        ss >> temp_b.ISBN;
        ss.ignore();
        getline(ss, temp_b.judul, ',');
        getline(ss, temp_b.penulis, ',');
        ss >> temp_b.tahun_terbit;
        ss.ignore();
        ss >> temp_b.jumlah_eksemplar;
        daftar_buku.push_back(temp_b);
    }
    file.close();

    string input;

    cout << "Masukkan ISBN atau judul buku yang akan ingin diupdate!" << endl;
    cout << "Nama atau ISBN: ";
    getline(cin, input);
    bool buku_ditemukan = false;
    for (buku &b : daftar_buku)
    {
        if (to_string(b.ISBN) == input || b.judul == input)
        {
            cout << "Buku yang ditemukan." << endl;
            cout << "ISBN             : " << b.ISBN << endl;
            cout << "Judul            : " << b.judul << endl;
            cout << "Penulis          : " << b.penulis << endl;
            cout << "Tahun terbit     : " << b.tahun_terbit << endl;
            cout << "Jumlah eksemplar : " << b.jumlah_eksemplar << endl;
            // konfirmasi update
            char konfirmasi;

            cout << "Ingin melakukan update buku ini?(y/n): ";
            cin >> konfirmasi;
            cin.ignore();
            if (konfirmasi == 'y' || konfirmasi == 'Y')
            {
                // update data
                cout << "Masukkan data baru!" << endl;
                cout << "ISBN             : ";
                cin >> b.ISBN;
                cin.ignore();
                cout << "Judul            : ";
                getline(cin, b.judul);
                cout << "Penulis          : ";
                getline(cin, b.penulis);
                cout << "Tahun terbit     : ";
                cin >> b.tahun_terbit;
                cin.ignore();
                cout << "Jumlah eksemplar : ";
                cin >> b.jumlah_eksemplar;
                cout << "Data buku berhasil diupdate." << endl;
            }
            buku_ditemukan = true;
            break;
        }
    }
    if (!buku_ditemukan)
    {
        cout << "Buku tidak ditemukan." << endl;
    }

    // Menulis kembali data yang diupdate
    ofstream outfile(file_buku);
    if (outfile.is_open())
    {
        for (const auto &b : daftar_buku)
        {
            outfile << b.ISBN << "," << b.judul << ","
                    << b.penulis << "," << b.tahun_terbit << ","
                    << b.jumlah_eksemplar << "\n";
        }
        outfile.close();
    }
    else
    {
        cout << "Gagal membukan file untuk tulis ulang" << endl;
    }
}
void DBbuku()
{
    bool kembali = true;
    char kembali_menu;
    do
    {
        int pilih;
        cout << "MENU PILIHAN \n"
             << "1. Kelola Data \n"
             << "2. Tampilkan \n"
             << "Pilih: \n";
        cin >> pilih;
        if (pilih == 1)
        {
            int pilih_menu;
            cout << "Apa yang ingin anda lakukan: \n"
                 << "1. Buat\n"
                 << "2. Ubah data \n"
                 << "3. Hapus \n";
            cout << "Pilih: ";
            cin >> pilih_menu;
            // buat data baru
            if (pilih_menu == 1)
            {
                inputdata_baru("database_buku.txt");
            }
            // tambah data(update)
            if (pilih_menu == 2)
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                // ubah data
                update("database_buku.txt");
            }
            // hapus data
            if (pilih_menu == 3)
            {
                // Lakukan proses hapus disini
                hapus("database_buku.txt", "temp_buku.txt");
            }
        }

        if (pilih == 2)
        {

            // Tampilkan data dari file
            output_data("database_buku.txt");
        }

        cout << "Apakah Anda ingin kembali ke menu?" << endl;
        cout << "Pilih (y/n): ";
        cin >> kembali_menu;

        if (kembali_menu == 'n' || kembali_menu == 'N')
        {
            kembali = false;
        }

    } while (kembali);
}
