#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct Mahasiswa {
    char nama[50];
    char nim[15];
    char jurusan[50];
    int tahunMasuk;
    float ipk;
};

void opsilain() {
    cout << "========================================  " << endl;
    cout << "  Pilihan tidak Valid, silakan coba lagi  " << endl;
    cout << "========================================  " << endl;
}
void berhenti() {
    char pilihan;
    cout << "Apakah Anda Ingin Kembali ke Menu Awal? (y/n): ";
    cin >> pilihan;
    if (pilihan == 'y' || pilihan == 'Y'){
        system("cls");
    } else if (pilihan == 'n' || pilihan == 'N') {
        cout << "Program selesai.\n";
        exit(0);
    } else {
        opsilain();
        berhenti();
    }
}

void tampilanmenu(int &pilihan) {
    cout << "\n================= Menu =================\n";
    cout << "| 1. Tambah Mahasiswa                  |" << endl;
    cout << "| 2. Tampilkan Mahasiswa               |"<< endl;
    cout << "| 3. Cari Mahasiswa Berdasarkan NIM    |"<< endl;
    cout << "| 4. Cari Mahasiswa Berdasarkan Jurusan|" << endl;
    cout << "| 5. Perbarui IPK Mahasiswa            |"<< endl;
    cout << "| 6. Hapus Mahasiswa                   |"<< endl;
    cout << "| 7. Keluar                            |"<< endl;
    cout << "========================================" << endl;
    cout << "Pilih Menu[1-7]: ";
    cin >> pilihan;
    cin.ignore(); 
}


void tambahMahasiswa() {
    FILE *file = fopen("MahasiswaData.dat", "ab"); 
    if (!file) {
        cout << "Gagal membuka file!\n";
        return;
    }

    int jumlah;
    cout << "Berapa mahasiswa yang ingin ditambahkan? ";
    cin >> jumlah;
    cin.ignore(); // Membersihkan buffer

    for (int i = 0; i < jumlah; i++) {
        Mahasiswa mhs;

        cout << "\nMahasiswa ke-" << (i + 1) << ":\n";
        cout << "Masukkan Nama       : ";
        cin.getline(mhs.nama, 50);
        cout << "Masukkan NIM        : ";
        cin.getline(mhs.nim, 15);
        cout << "Masukkan Jurusan    : ";
        cin.getline(mhs.jurusan, 50);
        cout << "Masukkan Tahun Masuk: ";
        cin >> mhs.tahunMasuk;
        cin.ignore(); 

        mhs.ipk = 0.0; // IPK awal selalu 0.0 (tidak bisa diinput langsung)

        fwrite(&mhs, sizeof(Mahasiswa), 1, file); // Simpan data ke file

        cout << "Mahasiswa berhasil ditambahkan dengan IPK awal 0.0!\n";
    }
    fclose(file);
}



void tampilkanMahasiswa() {
    FILE *file = fopen("MahasiswaData.dat", "rb"); 
    if (!file) {
        cout << "\nTidak ada data mahasiswa.\n";
        return;
    }

    Mahasiswa mhs;
    bool adaData = false;

    cout << "\n========================================  " << endl;
    cout << "           Daftar Mahasiswa               " << endl;
    cout << "========================================  " << endl << endl;
    while (fread(&mhs, sizeof(Mahasiswa), 1, file)) { 
        adaData = true;
        cout << "NIM        : " << mhs.nim << "\n";
        cout << "Nama       : " << mhs.nama << "\n";
        cout << "Jurusan    : " << mhs.jurusan << "\n";
        cout << "Tahun Masuk: " << mhs.tahunMasuk << "\n";
        cout << "IPK        : " << mhs.ipk << "\n";
        cout << "----------------------------------------  " << endl;
    }
    fclose(file);

    if (!adaData) {
        cout << "---Tidak ada mahasiswa yang terdaftar---\n\n";
    }
}


void quickSort(Mahasiswa arr[], int low, int high) {
    if (low < high) {
        int pivot = low;
        int i = low, j = high;
        Mahasiswa temp;
        while (i < j) {
            while (arr[i].nim[0] <= arr[pivot].nim[0] && i < high) i++;
            while (arr[j].nim[0] > arr[pivot].nim[0]) j--;
            if (i < j) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        temp = arr[pivot];
        arr[pivot] = arr[j];
        arr[j] = temp;
        quickSort(arr, low, j - 1);
        quickSort(arr, j + 1, high);
    }
}

int binarySearch(Mahasiswa arr[], int left, int right, const char nim[]) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = 0, i = 0;
        while (arr[mid].nim[i] != '\0' && nim[i] != '\0' && arr[mid].nim[i] == nim[i]) {
            i++;
        }
        cmp = arr[mid].nim[i] - nim[i];
        
        if (cmp == 0) return mid;
        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void cariMahasiswa() {
    FILE *file = fopen("MahasiswaData.dat", "rb"); 
    if (!file) {
        cout << "\nTidak ada data mahasiswa.\n";
        return;
    }

    char nimCari[15];
    cout << "\nMasukkan NIM yang dicari: ";
    cin>>nimCari;

    Mahasiswa mhs;
    bool ditemukan = false;

    while (fread(&mhs, sizeof(Mahasiswa), 1, file)) { 
        if (strcmp(mhs.nim, nimCari) == 0) { // Membandingkan NIM
            ditemukan = true;
            cout << "\n========================================  " << endl;
            cout << "       Pencarian Berdasarkan NIM          " << endl;
            cout << "========================================  " << endl;
            cout << "\n--------- Mahasiswa Ditemukan ---------\n";
            cout << "NIM        : " << mhs.nim << "\n";
            cout << "Nama       : " << mhs.nama << "\n";
            cout << "Jurusan    : " << mhs.jurusan << "\n";
            cout << "Tahun Masuk: " << mhs.tahunMasuk << "\n";
            cout << "IPK        : " << mhs.ipk << "\n";
            cout << "------------------------------\n";
            break; 
        }
    }

    fclose(file);

    if (!ditemukan) {
        cout << "Mahasiswa dengan NIM " << nimCari << " tidak ditemukan!\n";
    }
}


void cariMahasiswaJurusan() {
    FILE *file = fopen("MahasiswaData.dat", "rb"); 
    if (!file) {
        cout << "\nTidak ada data mahasiswa.\n";
        return;
    }

    char jurusanCari[50];
    cout << "\nMasukkan jurusan yang dicari: ";
    cin >> jurusanCari;

    Mahasiswa mhs;
    bool ditemukan = false;

    cout << "\n========================================  " << endl;
    cout << "      Pencarian Berdasarkan Jurusan       " << endl;
    cout << "========================================  " << endl << endl;
    cout << "\n----- Mahasiswa dengan Jurusan " << jurusanCari << " -----\n";
    while (fread(&mhs, sizeof(Mahasiswa), 1, file)) { 
        if (strcmp(mhs.jurusan, jurusanCari) == 0) { // Membandingkan jurusan
            ditemukan = true;
            cout << "NIM        : " << mhs.nim << "\n";
            cout << "Nama       : " << mhs.nama << "\n";
            cout << "Tahun Masuk: " << mhs.tahunMasuk << "\n";
            cout << "IPK        : " << mhs.ipk << "\n";
            cout << "--------------------------------------\n";
        }
    }

    fclose(file);

    if (!ditemukan) {
        cout << "Tidak ada mahasiswa dengan jurusan " << jurusanCari << "!\n";
    }
}


void perbaruiIPK() {
    FILE *file = fopen("MahasiswaData.dat", "rb"); 
    if (!file) {
        cout << "Tidak ada data mahasiswa.\n";
        return;
    }

    FILE *tempFile = fopen("TempData.dat", "wb"); // File sementara untuk update data
    if (!tempFile) {
        cout << "Gagal membuat file sementara!\n";
        fclose(file);
        return;
    }

    char nimCari[15];
    cout << "Masukkan NIM mahasiswa yang ingin diperbarui IPK-nya: ";
    cin >> nimCari;

    Mahasiswa mhs;
    bool ditemukan = false;

    while (fread(&mhs, sizeof(Mahasiswa), 1, file)) { 
        if (strcmp(mhs.nim, nimCari) == 0) { // Jika NIM cocok
            ditemukan = true;
            cout << "\n--------Mahasiswa ditemukan:--------\n";
            cout << "NIM        : " << mhs.nim << "\n";
            cout << "Nama       : " << mhs.nama << "\n";
            cout << "Jurusan    : " << mhs.jurusan << "\n";
            cout << "Tahun Masuk: " << mhs.tahunMasuk << "\n";
            cout << "IPK Saat Ini: " << mhs.ipk << "\n";

            float ipkBaru;
            do {
                cout << "Masukkan IPK baru (0.0 - 4.0): ";
                cin >> ipkBaru;
                if (ipkBaru < 0.0 || ipkBaru > 4.0) {
                    cout << "IPK tidak valid! Harus dalam rentang 0.0 - 4.0.\n";
                }
            } while (ipkBaru < 0.0 || ipkBaru > 4.0);

            mhs.ipk = ipkBaru; // Memperbarui IPK
            cout << "IPK mahasiswa dengan NIM " << mhs.nim << " berhasil diperbarui!\n";
        }

        fwrite(&mhs, sizeof(Mahasiswa), 1, tempFile); // Menulis data ke file sementara
    }

    fclose(file);
    fclose(tempFile);

    if (!ditemukan) {
        cout << "\n---------Mahasiswa tidak ditemukan!---------\n";
        remove("TempData.dat"); // Hapus file sementara jika tidak ada perubahan
    } else {
        remove("MahasiswaData.dat"); // Hapus file lama
        rename("TempData.dat", "MahasiswaData.dat"); // Ganti file sementara jadi file utama
    }
}

void hapusMahasiswa() {
    FILE *file = fopen("MahasiswaData.dat", "rb");
    if (!file) {
        cout << "Tidak ada data mahasiswa.\n";
        return;
    }
    
    FILE *tempFile = fopen("TempData.dat", "wb");
    if (!tempFile) {
        cout << "Gagal membuat file sementara!\n";
        fclose(file);
        return;
    }
    
    Mahasiswa mhs;
    char nimHapus[15];
    bool ditemukan = false;
    
    cout << "Masukkan NIM mahasiswa yang ingin dihapus: ";
    cin >> nimHapus;
    
    while (fread(&mhs, sizeof(Mahasiswa), 1, file)) {
        if (strcmp(mhs.nim, nimHapus) == 0) {
            ditemukan = true;
            cout << "Mahasiswa dengan NIM " << nimHapus << " telah dihapus.\n";
        } else {
            fwrite(&mhs, sizeof(Mahasiswa), 1, tempFile); // Simpan data yang tidak dihapus
        }
    }
    
    fclose(file);
    fclose(tempFile);
    
    if (ditemukan) {
        remove("MahasiswaData.dat"); // Hapus file lama
        rename("TempData.dat", "MahasiswaData.dat"); // Ganti file sementara jadi file utama
    } else {
        remove("TempData.dat"); // Hapus file sementara jika tidak ada perubahan
        cout << "\n---------Mahasiswa tidak ditemukan!---------\n";
    }
}



int main() {
    int pilihan;
    do {
        tampilanmenu(pilihan);
        switch (pilihan) {
            case 1: tambahMahasiswa(); break;
            case 2: tampilkanMahasiswa(); break;
            case 3: cariMahasiswa(); break;
            case 4: cariMahasiswaJurusan(); break;
            case 5: perbaruiIPK(); break;
            case 6: hapusMahasiswa(); break;
            case 7: 
                    cout << "Terima kasih telah menggunakan SmartCampus++! \n";
                    cout <<"Semoga sukses dalam studi Anda!\n";
                    break;
            default: 
                    opsilain();
                    berhenti();
        }
        berhenti();
    } while (pilihan != 7);
    return 0;
}