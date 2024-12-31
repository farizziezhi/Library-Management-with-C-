#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Membuat struct buku yang berisikan id, judul, penulis dan kategori buku
struct buku{
    string id, judul_buku, penulis, kategori;
};

vector<buku> perpus(100); // array vector yang menyimpan id, judul, penulis dan kategori buku

int indeks_buku = 0; // menyimpan jumlah buku yang ada

void tambah_buku(){ // prosedur untuk menambahkan buku
    cout << endl;
    ulangi:
    cout << "Masukkan ID Buku: "; cin >> perpus[indeks_buku].id;
    string cek_idBuku = perpus[indeks_buku].id;

    // cek apakah buku dengan id tersebut sudah ada atau belum, jika sudah ada maka minta untuk masukkan kembali
    for(int i = 0; i < indeks_buku; i++){
        if(cek_idBuku == perpus[i].id){
            cout << "Buku dengan ID tersebut sudah ada, Mohon Masukkan ID yang lain!" << endl;
            goto ulangi; // Kembali ke awal (label ulangi), untuk memasukkan ID buku yang lain
        }
    }

    // Meminta pengguna untuk memasukkan informasi buku
    cout << "Masukkan Judul Buku: "; cin.ignore(); getline(cin, perpus[indeks_buku].judul_buku);
    cout << "Masukkan Penulis: "; getline(cin, perpus[indeks_buku].penulis);
    cout << "Masukkan Kategori: "; getline(cin, perpus[indeks_buku].kategori);

    cout << endl << "Buku Berhasil Ditambahkan!" << endl << endl;

    indeks_buku++; // jumlah buku bertambah
}

void cari_buku(){ // prosedur untuk mencari buku berdasarkan id atau judul buku
    // cek apakah buku masih kosong atau tidak
    if(indeks_buku == 0){
        cout << endl << "Daftar Buku Masih Kosong" << endl;
        return; // kembali ke menu utama karena isi daftar buku masih kosong
    }
    
    string id_cari;

    cout << endl << "Silakan masukkan ID / Judul buku yang ingin anda cari: "; cin >> id_cari;
    bool buku_ada = false; // Menyimpan informasi apakah buku sudah ada atau belum

    // mencari buku berdasarkan id / judul
    for(int i = 0; i < indeks_buku; i++){
        if(id_cari == perpus[i].id || id_cari == perpus[i].judul_buku){
            cout << endl << "Buku Ditemukan!" << endl;
            buku_ada = true; // Buku sudah ada

            // Menampilkan informasi buku
            cout << "ID Buku: " << perpus[i].id << endl;
            cout << "Judul Buku: " << perpus[i].judul_buku << endl;
            cout << "Penulis: " << perpus[i].penulis << endl;
            cout << "Kategori: " << perpus[i].kategori << endl << endl;
        }
    }

    // Jika id atau judul buku tidak ditemukan dalam daftar
    if(!buku_ada) cout << "Buku Anda Tidak Ditemukan" << endl << endl;
}

void tampilkan_buku(){ // prosedur untuk menampilkan buku berdasarkan abjad judul buku yang terurut dari a - z
    // cek apakah buku masih kosong atau tidak
    if(indeks_buku == 0){
        cout << endl << "Daftar Buku Masih Kosong" << endl;
        return; // kembali ke menu utama karena isi daftar buku masih kosong
    }

    // Mengurutkan buku berdasarkan abjad judul
    sort(perpus.begin(), perpus.begin() + indeks_buku, [](const buku &a, const buku &b) {
        return a.judul_buku < b.judul_buku;
    });
    
    cout << endl << "Daftar Buku: " << endl;

    // mencetak semua buku yang ada, yang sudah diurutkan berdasarkan judul buku
    for(int i = 0; i < indeks_buku; i++){
        cout << i+1 << ". [" << perpus[i].id << "] " << perpus[i].judul_buku << " - " <<
            perpus[i].penulis << " (Kategori: " << perpus[i].kategori << ")" << endl;
    }

    cout << endl;
}

void hapus_buku(){ // prosedur untuk menghapus buku
    // cek apakah buku masih kosong atau tidak
    if(indeks_buku == 0){
        cout << endl << "Daftar Buku Masih Kosong" << endl;
        return; // kembali ke menu utama karena isi daftar buku masih kosong
    }
    
    string id_hapus;
    cout << endl << "Masukkan ID Buku yang Ingin Anda Hapus : "; cin >> id_hapus;

    // mencari buku yang memiliki id yang sama
    int simpan_indeks = -1;
    for(int i = 0; i < indeks_buku; i++){
        if(id_hapus == perpus[i].id){
            simpan_indeks = i;
            break;
        }
    }

    // cek apakah buku yang ingin dihapus ada dalam daftar, jika tidak ada maka kembali ke menu utama
    if(simpan_indeks == -1){
        cout << endl << "Buku dengan ID tersebut tidak Ditemukan!" << endl;
        return; // kembali ke menu utama
    }

    indeks_buku--; // jumlah buku berkurang

    // menghapus buku
    for(int i = simpan_indeks; i < indeks_buku; i++){
        perpus[i] = perpus[i+1]; // menggantikan buku yang dihapus dengan buku selanjutnya
                                 // tujuannya untuk menghapus buku yang ingin dihapus
    }

    cout << endl << "Buku Telah Berhasil di Hapus" << endl;
}

void jumlah_buku_kategori(){ // prosedur untuk menampilkan jumlah buku per kategori
    // cek apakah buku masih kosong atau tidak
    if(indeks_buku == 0){
        cout << endl << "Daftar Buku Masih Kosong" << endl;
        return; // kembali ke menu utama karena isi daftar buku masih kosong
    }

    int banyakBuku = indeks_buku;

    string cekKategori, kategoriTerakhir[100]; // Untuk menyimpan kategori yang sudah di cek
    int jumlahKategoriTerakhir = 0; // Untuk menghitung berapa banyak kategori yang ada

    cout << endl << "Jumlah Buku per Kategori: " << endl;
    for(int i = 0; i < banyakBuku; i++){
        cekKategori = perpus[i].kategori;

        // Cek kategori sudah diproses atau belum
        bool sudahProses = false;
        for(int j = 0; j < jumlahKategoriTerakhir; j++){
            if(kategoriTerakhir[j] == cekKategori){
                sudahProses = true; // kategori sudah diproses
                break;
            }
        }
        // Jika sudah maka lewati
        if(sudahProses) continue;

        // Hitung berapa banyak buku per kategori
        int jumlah_buku = 1; // Jumlah buku per kategori kita hitung dari buku yang sekarang
        for(int j = i + 1; j < banyakBuku; j++){
            if(cekKategori == perpus[j].kategori){
                jumlah_buku++; // Jika ada buku yang memiliki kategori sama
                               // maka jumlah buku kategori tersebut bertambah
            }
        }

        // cetak buku per kategori
        cout << jumlahKategoriTerakhir+1 << ". " << perpus[i].kategori << ": " << jumlah_buku << " Buku" << endl;
        
        // Masukkan kategori yang sudah dicek ke dalam array dan jumlah kategori bertambah
        kategoriTerakhir[jumlahKategoriTerakhir] = cekKategori;
        jumlahKategoriTerakhir++;
    }
}

void update_buku(){ // prosedur untuk mengupdate isi informasi buku
    // cek apakah buku masih kosong atau tidak
    if(indeks_buku == 0){
        cout << endl << "Daftar Buku Masih Kosong" << endl;
        return; // kembali ke menu utama karena isi daftar buku masih kosong
    }

    string id, judul_baru, penulis_baru, kategori_baru;

    ulangi:
    cout << "Masukkan ID Buku Yang Ingin diganti: "; cin >> id;
    string cek_idBuku = id; 
    bool cek_buku = false;

    // cek apakah buku dengan id tersebut sudah ada atau belum, 
    // jika sudah ada maka minta pengguna untuk memasukkan judul, penulis dan kategori yang baru
    for(int i = 0; i < indeks_buku; i++){
        if(cek_idBuku == perpus[i].id){
            cek_buku = true;
            cout << "Buku ditemukan!" << endl;

            // Meminta pengguna untuk memasukkan informasi baru
            cout << "Masukkan Judul Buku Baru: "; cin.ignore(); getline(cin, judul_baru);
            cout << "Masukkan Penulis Baru: "; getline(cin, penulis_baru);
            cout << "Masukkan Kategori Baru: "; getline(cin, kategori_baru);

            // Menyimpan informasi buku yang baru dimasukkan pengguna
            perpus[i].judul_buku = judul_baru;
            perpus[i].penulis = penulis_baru;
            perpus[i].kategori = kategori_baru;

            cout << endl << "Buku Berhasil Diupdate!" << endl << endl;
            break;
        }
    }

    // jika buku belum ada maka minta pengguna untuk memasukkan ID Buku kembali
    if(!cek_buku){
        cout << "Buku dengan ID Anda tidak Ditemukan, silahkan masukkan ID yang Benar!" << endl;
        goto ulangi; // Kembali ke awal (label ulangi), untuk memasukkan ID buku yang benar
    }
}

void sistem_manajemen(){ // prosedur untuk menu awal sistem perpustakaan
    menu: // untuk mengulang program

    // Menampilkan tampilan menu program
    cout << endl << "Sistem Manajemen Perpustakaan" << endl;
    cout << "1. Tambah Buku Baru" << endl;
    cout << "2. Cari Buku" << endl;
    cout << "3. Tampilkan Semua Buku" << endl;
    cout << "4. Hapus Buku" << endl;
    cout << "5. Tampilkan Jumlah Buku per Kategori" << endl;
    cout << "6. Update Isi Buku" << endl;
    cout << "7. Keluar" << endl;

    int pilihan;

    // meminta pengguna untuk memasukkan pilihan
    // sesuai dengan pilihan yang tertera
    cout << "Masukkan Pilihan anda (1-7) : "; cin >> pilihan;

    // Mengecek kemudian menjalankan prosedur sesuai pilihan pengguna
    switch(pilihan){
        case 1 :
            tambah_buku(); // Masuk ke prosedur tambah buku
            goto menu; // Kembali ke awal (label menu), untuk memasukkan pilihan yang lain
            break;
        case 2 :
            cari_buku(); // Masuk ke prosedur cari buku
            goto menu; // Kembali ke awal (label menu), untuk memasukkan pilihan yang lain
            break;
        case 3 :
            tampilkan_buku(); // Masuk ke prosedur tampilkan buku
            goto menu; // Kembali ke awal (label menu), untuk memasukkan pilihan yang lain
            break;
        case 4 :
            hapus_buku(); // Masuk ke prosedur hapus buku
            goto menu; // Kembali ke awal (label menu), untuk memasukkan pilihan yang lain
            break;
        case 5 :
            jumlah_buku_kategori(); // Masuk ke prosedur jumlah buku per kategori
            goto menu; // Kembali ke awal (label menu), untuk memasukkan pilihan yang lain
            break;
        case 6 :
            update_buku(); // Masuk ke prosedur update isi buku
            goto menu; // Kembali ke awal (label menu), untuk memasukkan pilihan yang lain
            break;
        case 7 :
            cout << endl << "Apakah anda yakin ingin keluar? (y/n) : ";
            char yes_no;
            cin >> yes_no;
            
            // Cek pilihan pengguna apakah ingin keluar dari program atau tidak
            // Jika 'y' maka keluar, jika 'n' maka tidak
            switch (yes_no){
                case 'y' :
                    // Keluar dari program
                    cout << endl << "Keluar dari Sistem Manajemen Perpustakaan" << endl;
                    break;
                case 'n' :
                    goto menu; // Kembali ke awal (label menu), untuk memasukkan pilihan yang lain
                    break;
            }
            break;
        default :
            cout << endl << "Masukkan Pilihan yang Benar!" << endl;
            goto menu; // Kembali ke awal (label menu), untuk memasukkan pilihan yang lain
            break;
    }
}

int main(){ // fungsi utama
    sistem_manajemen(); // masuk ke prosedur sistem manajemen
                        // untuk menampilkan menu utama perpustakaan
}
