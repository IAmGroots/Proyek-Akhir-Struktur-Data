#include <iostream>
using namespace std;

struct tiket {
	int jumlah, harga;
	string nama, kode, jadwal;
};

struct Node {
	tiket tkt;
	Node *next, *cur, *sebelum, *hapus;
};

Node *next, *cur, *sebelum, *hapus;

int lenght(Node *head) {
  int banyak = 0;
  while (head != NULL) {
    banyak++;
    head = head->next;
  }
  return banyak;
}

void menuUser() {
    cout << "Pemesanan Tiket Pesawat Travel Fly To The Moon" << endl;
    cout << "1. Pesan Tiket" << endl;
    cout << "2. Batalkan Tiket" << endl;
    cout << "3. Lihat Jadwal" << endl;
    cout << "0. Exit" << endl;
}

void menuAdmin() {
    cout << "Pemesanan Tiket Pesawat Travel Fly To The Moon" << endl;
    cout << "1. Tambah Jadwal" << endl;
    cout << "2. Melihat data user" << endl;
    cout << "3. Melihat Pesanan" << endl;
    cout << "0. Exit" << endl;
}

int main() {
    string username, password, pilih, lagi;
    login:
        cout << "Login" << endl;
        cout << "Username : "; getline(cin, username);
        cout << "Password : "; getline(cin, password);
    if (username == "admin" and password == "admin") {
        while(pilih != "0") {
            menuAdmin();
            cout << "Masukkan Pilihan : "; cin >> pilih;
            if (pilih == "1") {
                system("cls");
                cout << "Tambah Jadwal" << endl;
            } else if (pilih == "2") {
                system("cls");
                cout << "Melihat data user" << endl;
            } else if (pilih == "3") {
                system("cls");
                cout << "Melihat pesanan" << endl;
            } else if (pilih == "0") {
                system("cls");
                cout << "Anda Telah Logout\nTerimakasih Telah Menggunakan Program Kami!" << endl;
            } else {
                cout << "Pilihan Tidak Ada!" << endl;
            }
        }
        

    } else if (username == "user" and password == "user") {
        while(pilih != "0") {
            menuUser();
            cout << "Masukkan Pilihan : "; cin >> pilih;
            if (pilih == "1") {
                system("cls");
                cout << "Pesan Tiket" << endl;
            } else if (pilih == "2") {
                system("cls");
                cout << "Batalkan Tiket" << endl;
            } else if (pilih == "3") {
                system("cls");
                cout << "Lihat Jadwal" << endl;
            } else if (pilih == "0") {
                system("cls");
                cout << "Anda Telah Logout\nTerimakasih Telah Menggunakan Program Kami!" << endl;
            } else {
                cout << "Pilihan Tidak Ada!" << endl;
            }
        }
    } else {
        cout << "Password atau Username anda salah!" << endl;
        ulang:
            cout << "Ingin Login lagi? (y/n) "; cin >> lagi;
        if (lagi == "y") {
            goto login;
        } else if (lagi == "n") {
            cout << "Terimakasih Telah Menggunakan Program Kami!" << endl;
        } else {
            cout << "Masukkan y/n" << endl;
            goto ulang;
        }
    }
}