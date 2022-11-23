#include <iostream>
#include <string>
#include <iomanip>
#include <map>
#include <sstream>
#include <stdlib.h>
using namespace std;

struct user
{
	string nama_lengkap;
	string password;
	string email;
	string no_hp;
	string alamat;
};

struct jadwal
{
	string maskapai;
	string asal;
	string tujuan;
	string jadwal;
	int kapasitas;
};

struct pesanan
{
	string user;
	int jumlahTiket;
	string maskapai;
	string jadwalPenerbangan;
	string status;
};

struct NodeUser
{
	user data;
	NodeUser *prev = NULL;
	NodeUser *next = NULL;
};

struct NodeJadwal
{
	jadwal data;
	NodeJadwal *prev = NULL;
	NodeJadwal *next = NULL;
};

struct NodePesanan
{
	pesanan data;
	NodePesanan *prev = NULL;
	NodePesanan *next = NULL;
};

// Program dimulai dengan 1 data user
NodeUser user1;
NodeUser *HEAD_USER = &user1;
NodeUser *TAIL_USER = &user1;

// Program dimulai dengan 0 data pesanan / tidak ada pesanan
NodePesanan pesanan1;
NodePesanan *HEAD_PESANAN = &pesanan1;
NodePesanan *TAIL_PESANAN = &pesanan1;

// Program dimulai dengan 3 data jadwal
NodeJadwal jadwal1;
NodeJadwal jadwal2;
NodeJadwal jadwal3;
NodeJadwal jadwal4;
NodeJadwal *HEAD_JADWAL = &jadwal1;
NodeJadwal *TAIL_JADWAL = &jadwal4;


NodeUser *newUser();

void clearScreen();
void tabel(string jenis);
int panjangData(string jenis, string data);
int jumlahNode(string jenis);
bool isNumber(string data);

void registrasi(NodeUser **head, NodeUser **tail);
void login(NodeUser *head);

// Dapat diakses Admin dan User
void menuAwal();
void lihatJadwal();
// OTW
// void mencariJadwal();

// Hanya dapat diakses Admin
void menuAdmin();
void lihatUser();
void konfirmasi();
void hapusAwal(NodePesanan **head, NodePesanan **tail);
void tambahJadwal(NodeJadwal **head, NodeJadwal **tail);
void editJadwal(NodeJadwal **head, NodeJadwal **tail);
void hapusJadwal(NodeJadwal **head, NodeJadwal **tail);
// OTW
// void pesananSelesai();

// Hanya dapat diakses User
void menuUser();
void daftarPesananUser();
void pemesanan(NodePesanan **head, NodePesanan **tail);

// QuickSort Start
struct NodeJadwal *getTail(struct NodeJadwal *cur)
{
  while (cur != NULL && cur->next != NULL)
  {
    cur = cur->next;
  }
  return cur;
}

struct NodeJadwal *partition(struct NodeJadwal *head, struct NodeJadwal *tail, struct NodeJadwal **newHead, struct NodeJadwal **newEnd)
{
  struct NodeJadwal *prev = NULL, *cur = head, *pivot = tail;
  while (cur != pivot)
  {
    if (cur->data.jadwal < pivot->data.jadwal)
    {
      if ((*newHead) == NULL)
      {
        (*newHead) = cur;
      }
      prev = cur;
      cur = cur->next;
    }
    else
    {
      if (prev)
      {
        prev->next = cur->next;
      }
      struct NodeJadwal *tmp = cur->next;
      cur->next = NULL;
      tail->next = cur;
      tail = cur;
      cur = tmp;
    }
  }
  if ((*newHead) == NULL)
  {
    (*newHead) = pivot;
  }
  (*newEnd) = tail;
  return pivot;
}

struct NodeJadwal *quickSortRecur(struct NodeJadwal *head, struct NodeJadwal *tail)
{
  if (!head || head == tail)
  {
    return head;
  }
  NodeJadwal *newHead = NULL, *newEnd = NULL;
  struct NodeJadwal *pivot = partition(head, tail, &newHead, &newEnd);
  if (newHead != pivot)
  {
    struct NodeJadwal *tmp = newHead;
    while (tmp->next != pivot)
    {
      tmp = tmp->next;
      tmp->next = NULL;
      newHead = quickSortRecur(newHead, tmp);
      tmp = getTail(newHead);
      tmp->next = pivot;
    }
  }
  pivot->next = quickSortRecur(pivot->next, newEnd);

  return newHead;
}

void quickSort(struct NodeJadwal **headRef)
{
  (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
	TAIL_JADWAL = getTail(*headRef);
	cout<<TAIL_JADWAL->data.maskapai<<endl;
	cout<<""<<endl;
	cout<<getTail(*headRef)->data.maskapai<<endl;
	getchar();
}
// QuickSort End

map<string, string> userAktif;

// Untuk membersihkan layar
void clearScreen()
{
	system("cls");
}

// Cek angka valid atau bukan
bool isNumber(string data)
{
	for (int i = 0; i < data.length(); i++)
		if (isdigit(data[i]) == false)
			// Berarti bukan angka valid
			return false;
	// Berarti angka valid
	return true;
}

// Mendapatkan jumlah node/data didalam linked list
int jumlahNode(string jenis)
{
	int jumlah = 0;
	if (jenis == "user")
	{
		NodeUser *head = HEAD_USER;
		while (head != NULL)
		{
			jumlah++;
			head = head->next;
		}
	}
	if (jenis == "pesanan")
	{
		NodePesanan *head = HEAD_PESANAN;
		while (head != NULL)
		{
			jumlah++;
			head = head->next;
		}
	}
	if (jenis == "jadwal")
	{
		NodeJadwal *head = HEAD_JADWAL;
		while (head != NULL)
		{
			jumlah++;
			head = head->next;
		}
	}
	return jumlah;
}

// Untuk mendapatkan jumlah data didalam suatu atribut setiap struct
int panjangData(string jenis, string data){
	int panjang = 0;
	if (jenis == "user"){
		NodeUser *head = HEAD_USER;
		while (head != NULL)
		{	
			int nama_lengkap, password, email, no_hp, alamat;
			if (head->data.nama_lengkap.length() > panjang){
				nama_lengkap = head->data.nama_lengkap.length();
			}
			if (head->data.password.length() > panjang){
				password = head->data.password.length();
			}
			if (head->data.email.length() > panjang){
				email = head->data.email.length();
			}
			if (head->data.no_hp.length() > panjang){
				no_hp = head->data.no_hp.length();
			}
			if (head->data.alamat.length() > panjang){
				alamat = head->data.alamat.length();
			}
			if (data == "nama_lengkap"){
				panjang = nama_lengkap;
			}
			if (data == "password"){
				panjang = password;
			}
			if (data == "email"){
				panjang = email;
			}
			if (data == "no_hp"){
				panjang = no_hp;
			}
			if (data == "alamat"){
				panjang = alamat;
			}
			head = head->next;
		}
	}

	if (jenis == "pesanan"){
		NodePesanan *head = HEAD_PESANAN;
		while (head != NULL)
		{	
			int user, jumlahTiket, maskapai, jadwalPenerbangan, status;
			if (head->data.user.length() > panjang){
				user = head->data.user.length();
			}
			if (to_string(head->data.jumlahTiket).length() > panjang){
				jumlahTiket = to_string(head->data.jumlahTiket).length();
			}
			if (head->data.maskapai.length() > panjang){
				maskapai = head->data.maskapai.length();
			}
			if (head->data.jadwalPenerbangan.length() > panjang){
				jadwalPenerbangan = head->data.jadwalPenerbangan.length();
			}
			if (head->data.status.length() > panjang){
				status = head->data.status.length();
			}
			if (data == "user"){
				panjang = user;
			}
			if (data == "jumlahTiket"){
				panjang = jumlahTiket;
			}
			if (data == "maskapai"){
				panjang = maskapai;
			}
			if (data == "jadwalPenerbangan"){
				panjang = jadwalPenerbangan;
			}
			if (data == "status"){
				panjang = status;
			}
			head = head->next;
		}
	}

	if (jenis == "jadwal"){
		NodeJadwal *head = HEAD_JADWAL;
		while (head != NULL)
		{	
			int maskapai, asal, tujuan, jadwalPenerbangan, kapasitas;
			if (head->data.maskapai.length() > panjang){
				maskapai = head->data.maskapai.length();
			}
			if (head->data.asal.length() > panjang){
				asal = head->data.asal.length();
			}
			if (head->data.tujuan.length() > panjang){
				tujuan = head->data.tujuan.length();
			}
			if (head->data.jadwal.length() > panjang){
				jadwalPenerbangan = head->data.jadwal.length();
			}
			if (to_string(head->data.kapasitas).length() > panjang){
				kapasitas = to_string(head->data.kapasitas).length();
			}
			if (data == "maskapai"){
				panjang = maskapai;
			}
			if (data == "asal"){
				panjang = asal;
			}
			if (data == "tujuan"){
				panjang = tujuan;
			}
			if (data == "jadwalPenerbangan"){
				panjang = jadwalPenerbangan;
			}
			if (data == "kapasitas"){
				panjang = kapasitas;
			}
			head = head->next;
		}
	}
	// Untuk mengembalikan data terpanjang pada suatu atribut
	return panjang;
}

// Untuk membuat tabel setiap struct
void tabel(string jenis)
{
	if (jenis == "user"){
		NodeUser *head = HEAD_USER;
		if (head == NULL){
			cout<< "" << endl;
			cout<< "Data User Kosong" << endl;
			return;
		}
		NodeUser *sementara = head;
		int pjgId = 0;
		int pjgNama = panjangData("user", "nama_lengkap");
		int pjgPassword = panjangData("user", "password");
		int pjgEmail = panjangData("user", "email");
		int pjgNoHp = panjangData("user", "no_hp");
		int pjgAlamat = panjangData("user", "alamat");
		if (pjgId < 2){
			pjgId = 2;
		}
		if (pjgNama < 16){
			pjgNama = 16;
		}
		if (pjgPassword < 16){
			pjgPassword = 16;
		}
		if (pjgEmail < 16){
			pjgEmail = 16;
		}
		if (pjgNoHp < 16){
			pjgNoHp = 16;
		}
		if (pjgAlamat < 16){
			pjgAlamat = 16;
		}
		int pjgBaris = pjgId + pjgNama + pjgPassword + pjgEmail + pjgNoHp + pjgAlamat + 19;
		string baris(pjgBaris, '=');
		if (pjgBaris %2 == 0){
			string satuPerDuaBaris((pjgBaris/2)-6, '=');
			cout<<" "<< endl;
			cout<<baris<<endl;
			cout<< left << satuPerDuaBaris << " ";
			cout<< left << setw(9) << "DATA USER =";system("color 01");
			cout<< left << satuPerDuaBaris << endl;
			cout<<baris<<endl;
			cout<<"| " << left << setw(pjgId) << "No" << " ";
			cout<<"| " << left << setw(pjgNama) << "Nama Lengkap" << " ";
			cout<<"| " << left << setw(pjgPassword) << "Password" << " ";
			cout<<"| " << left << setw(pjgEmail) << "Email" << " ";
			cout<<"| " << left << setw(pjgNoHp) << "No Hp" << " ";
			cout<<"| " << left << setw(pjgAlamat) << "Alamat" << " |" << endl;
			cout<<baris<<endl;
		}
		else {
			string satuPerDuaBaris((pjgBaris/2)-5, '=');
			cout<<" "<< endl;
			cout<<baris<<endl;
			cout<< left << satuPerDuaBaris << " ";
			cout<< left << setw(9) << "DATA USER ";system("color 01");
			cout<< left << satuPerDuaBaris << endl;
			cout<<baris<<endl;
			cout<<"| " << left << setw(pjgId) << "No" << " ";
			cout<<"| " << left << setw(pjgNama) << "Nama Lengkap" << " ";
			cout<<"| " << left << setw(pjgPassword) << "Password" << " ";
			cout<<"| " << left << setw(pjgEmail) << "Email" << " ";
			cout<<"| " << left << setw(pjgNoHp) << "No Hp" << " ";
			cout<<"| " << left << setw(pjgAlamat) << "Alamat" << " |" << endl;
			cout<<baris<<endl;
		}

		int nomor = 1;
		while(sementara != NULL){
			cout<<"| " << left << setw(pjgId) << nomor << " ";
			cout<<"| " << left << setw(pjgNama) << sementara->data.nama_lengkap << " ";
			cout<<"| " << left << setw(pjgPassword) << sementara->data.password << " ";
			cout<<"| " << left << setw(pjgEmail) << sementara->data.email << " ";
			cout<<"| " << left << setw(pjgNoHp) << sementara->data.no_hp << " ";
			cout<<"| " << left << setw(pjgAlamat) << sementara->data.alamat << " |" << endl;
			cout<<baris<<endl;
			nomor++;
			sementara = sementara->next;
		}
	}

	if (jenis == "jadwal"){
		quickSort(&HEAD_JADWAL);
		NodeJadwal *head = HEAD_JADWAL;
		if (head == NULL){
			cout<< "" << endl;
			cout<< "Data Jadwal Kosong" << endl;
			return;
		}

		NodeJadwal *sementara = head;
		int pjgId = 0;
		int pjgMaskapai = panjangData("jadwal", "maskapai");
		int pjgAsal = panjangData("jadwal", "asal");
		int pjgTujuan = panjangData("jadwal", "tujuan");
		int pjgJadwal = panjangData("jadwal", "jadwalPenerbangan");
		int pjgKapasitas = panjangData("jadwal", "kapasitas");
		if (pjgId < 2){
			pjgId = 2;
		}
		if (pjgMaskapai < 16){
			pjgMaskapai = 16;
		}
		if (pjgAsal < 12){
			pjgAsal = 12;
		}
		if (pjgTujuan < 12){
			pjgTujuan = 12;
		}
		if (pjgJadwal < 10){
			pjgJadwal = 10;
		}
		if (pjgKapasitas < 9){
			pjgKapasitas = 9;
		}
		int pjgBaris = pjgId + pjgMaskapai + pjgAsal + pjgTujuan + pjgJadwal + pjgKapasitas + 19;
		string baris(pjgBaris, '=');
		if (pjgBaris %2 == 0){
			string satuPerDuaBaris((pjgBaris/2)-10, '=');
			cout<<" "<< endl;
			cout<<baris<<endl;
			cout<< left << satuPerDuaBaris << " ";
			cout<< left << setw(9) << "JADWAL PENERBANGAN ";
			cout<< left << satuPerDuaBaris << endl;
			cout<<baris<<endl;
			cout<<"| " << left << setw(pjgId) << "No" << " ";
			cout<<"| " << left << setw(pjgMaskapai) << "Maskapai" << " ";
			cout<<"| " << left << setw(pjgAsal) << "Asal" << " ";
			cout<<"| " << left << setw(pjgTujuan) << "Tujuan" << " ";
			cout<<"| " << left << setw(pjgJadwal) << "Jadwal" << " ";
			cout<<"| " << left << setw(pjgKapasitas) << "Kapasitas" << " |" << endl;
			cout<<baris<<endl;
		}
		else {
			string satuPerDuaBaris((pjgBaris/2)-10, '=');
			cout<<" "<< endl;
			cout<<baris<<endl;
			cout<< left << satuPerDuaBaris << " ";
			cout<< left << setw(9) << "JADWAL PENERBANGAN =";
			cout<< left << satuPerDuaBaris << endl;
			cout<<baris<<endl;
			cout<<"| " << left << setw(pjgId) << "No" << " ";
			cout<<"| " << left << setw(pjgMaskapai) << "Maskapai" << " ";
			cout<<"| " << left << setw(pjgAsal) << "Asal" << " ";
			cout<<"| " << left << setw(pjgTujuan) << "Tujuan" << " ";
			cout<<"| " << left << setw(pjgJadwal) << "Jadwal" << " ";
			cout<<"| " << left << setw(pjgKapasitas) << "Kapasitas" << " |" << endl;
			cout<<baris<<endl;
		}

		int nomor = 1;
		while(sementara != NULL){
			cout<<"| " << left << setw(pjgId) << nomor << " ";
			cout<<"| " << left << setw(pjgMaskapai) << sementara->data.maskapai << " ";
			cout<<"| " << left << setw(pjgAsal) << sementara->data.asal << " ";
			cout<<"| " << left << setw(pjgTujuan) << sementara->data.tujuan << " ";
			cout<<"| " << left << setw(pjgJadwal) << sementara->data.jadwal << " ";
			cout<<"| " << left << setw(pjgKapasitas) << sementara->data.kapasitas << " |" << endl;
			cout<<baris<<endl;
			nomor++;
			sementara = sementara->next;
		}
	}

	if (jenis == "pesanan"){
		NodePesanan *head = HEAD_PESANAN;
		if (head == NULL){
			cout<< "" << endl;
			cout<< "Data Pemesanan Kosong" << endl;
			return;
		}

		NodePesanan *sementara = head;
		int pjgId = 0;
		int pjgUser = panjangData("pesanan", "user");
		int pjgTiket = panjangData("pesanan", "jumlahTiket");
		int pjgMaskapai = panjangData("pesanan", "maskapai");
		int pjgJadwal = panjangData("pesanan", "jadwalPenerbangan");
		int pjgStatus = panjangData("pesanan", "status");
		if (pjgId < 2){
			pjgId = 2;
		}
		if (pjgUser < 16){
			pjgUser = 16;
		}
		if (pjgTiket < 5){
			pjgTiket = 5;
		}
		if (pjgMaskapai < 12){
			pjgMaskapai = 12;
		}
		if (pjgJadwal < 10){
			pjgJadwal = 10;
		}
		if (pjgStatus < 8){
			pjgStatus = 8;
		}
		int pjgBaris = pjgId + pjgUser + pjgTiket + pjgMaskapai + pjgJadwal + pjgStatus + 19;
		string baris(pjgBaris, '=');
		if (pjgBaris %2 == 0){
			string satuPerDuaBaris((pjgBaris/2)-11, '=');
			cout<<" "<< endl;
			cout<<baris<<endl;
			cout<< left << satuPerDuaBaris << " ";
			cout<< left << setw(9) << "INFORMASI PEMESANAN =";
			cout<< left << satuPerDuaBaris << endl;
			cout<<baris<<endl;
			cout<<"| " << left << setw(pjgId) << "No" << " ";
			cout<<"| " << left << setw(pjgUser) << "Nama Lengkap" << " ";
			cout<<"| " << left << setw(pjgTiket) << "Tiket" << " ";
			cout<<"| " << left << setw(pjgMaskapai) << "Maskapai" << " ";
			cout<<"| " << left << setw(pjgJadwal) << "Jadwal" << " ";
			cout<<"| " << left << setw(pjgStatus) << "Status" << " |" << endl;
			cout<<baris<<endl;
		}
		else {
			string satuPerDuaBaris((pjgBaris/2)-10, '=');
			cout<<" "<< endl;
			cout<<baris<<endl;
			cout<< left << satuPerDuaBaris << " ";
			cout<< left << setw(9) << "INFORMASI PEMESANAN ";
			cout<< left << satuPerDuaBaris << endl;
			cout<<baris<<endl;
			cout<<"| " << left << setw(pjgId) << "No" << " ";
			cout<<"| " << left << setw(pjgUser) << "Nama Lengkap" << " ";
			cout<<"| " << left << setw(pjgTiket) << "Tiket" << " ";
			cout<<"| " << left << setw(pjgMaskapai) << "Maskapai" << " ";
			cout<<"| " << left << setw(pjgJadwal) << "Jadwal" << " ";
			cout<<"| " << left << setw(pjgStatus) << "Status" << " |" << endl;
			cout<<baris<<endl;
		}

		int nomor = 1;
		while(sementara != NULL){
			cout<<"| " << left << setw(pjgId) << nomor << " ";
			cout<<"| " << left << setw(pjgUser) << sementara->data.user << " ";
			cout<<"| " << left << setw(pjgTiket) << sementara->data.jumlahTiket << " ";
			cout<<"| " << left << setw(pjgMaskapai) << sementara->data.maskapai << " ";
			cout<<"| " << left << setw(pjgJadwal) << sementara->data.jadwalPenerbangan << " ";
			cout<<"| " << left << setw(pjgStatus) << sementara->data.status << " |" << endl;
			cout<<baris<<endl;
			nomor++;
			sementara = sementara->next;
		}
	}
}

// Registrasi Start
NodeUser *newUser(){
	NodeUser *newUser = new NodeUser;
	string nama_lengkap, password, konfirmasi, email, no_hp, alamat;
	bool ulangi = true;
	while (ulangi){
		cout << "" << endl;
		cout << "REGISTRASI USER" << endl;
		cout << "" << endl;
		cout << "Nama Lengkap  >> ";
		getline(cin, nama_lengkap);
		cout << "Password     >> ";
		getline(cin, password);
		cout << "Konfirmasi Password >> ";
		getline(cin, konfirmasi);
		if (konfirmasi != password){
			cout<<""<<endl;
			cout<<"Konfirmasi Password Anda Tidak Sesuai"<<endl;
			cout<<""<<endl;
			cout<<"Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			menuAwal();
			continue;
		}
		cout << "Email >> ";
		getline(cin, email);
		cout << "No HP >> ";
		getline(cin, no_hp);
		cout << "Alamat >> ";
		getline(cin, alamat);
		newUser->data.nama_lengkap = nama_lengkap;
		newUser->data.password = password;
		newUser->data.email = email;
		newUser->data.no_hp = no_hp;
		newUser->data.alamat = alamat;
		return newUser;
	}
}

void registrasi(NodeUser **head, NodeUser **tail){
	NodeUser *node = newUser();
	NodeUser *sementara = *head;
	if (node->data.email.find('@') == -1){
		cout<<""<<endl;
		cout<<"Email Anda Tidak Benar (Memerlukan Simbol @)"<<endl;
		cout<<""<<endl;
		cout<<"Silahkan Tekan Enter Untuk Melanjutkan...";
		getchar();
		return;
	}

	while (sementara != NULL){
		if (sementara->data.email == node->data.email){
			cout << "" << endl;
			cout<<"Email Telah Digunakan"<<endl;
			cout << "" << endl;
			cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			return;
		}
		sementara = sementara->next;
	}

	if (isNumber(node->data.no_hp) == false){
		cout<<""<<endl;
		cout<<"No HP Anda Tidak Benar (Harus Angka 0-9)"<<endl;
		cout<<""<<endl;
		cout<<"Silahkan Tekan Enter Untuk Melanjutkan...";
		getchar();
		return;
	}
	if (node->data.no_hp.find('-') != -1){
		cout<<""<<endl;
		cout<<"No HP Anda Tidak Benar (Tidak Boleh Negatif)"<<endl;
		cout<<""<<endl;
		cout<<"Silahkan Tekan Enter Untuk Melanjutkan...";
		getchar();
		return;
	}

  node->prev = *tail;
  node->next = NULL;
  if (*head == NULL && *tail == NULL)
  {
    *head = node;
    *tail = node;
  }
  else
  {
    (*tail)->next = node;
    *tail = node;
  }
  cout << "" << endl;
  cout << "Registrasi Berhasil" << endl;
  cout << "" << endl;
  cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
  getchar();
}
// Registrasi End

// Login Start
void login(NodeUser *head){
	bool ulangi = true;
	string email, password;
	while (ulangi){
		cout << "\nLOGIN USER" << endl;
		cout<<"\nEmail >> ";
		getline(cin, email);
		cout<<"Password >> ";
		getline(cin, password);

		while (head != NULL){
			if (head->data.email == email && head->data.password == password){
				cout<<""<<endl;
				cout<<"Login Berhasil"<<endl;
				cout<<""<<endl;
				cout<<"Silahkan Tekan Enter Untuk Melanjutkan...";
				getchar();
				// Untuk menambah data user didalam dictionary userAktif
				userAktif.insert({"user aktif", head->data.nama_lengkap});
				menuUser();
			}
			head = head->next;
		}
		cout<<""<<endl;
		cout<<"Login Gagal"<<endl;
		cout<<""<<endl;
		cout<<"Silahkan Tekan Enter Untuk Melanjutkan...";
		getchar();
		menuAwal();
	}
}
// Login End

// Menu Awal Start
void menuAwal(){
	bool ulangi = true;
	while (ulangi)
	{
		clearScreen();

		string pilihan;
		cout << "Menu Awal" << endl;
		cout << "[1] Register" << endl;
		cout << "[2] Login User" << endl;
		cout << "[3] Login Admin" << endl;
		cout << "[4] Keluar" << endl;
		cout << "" << endl;
		cout << "Silahkan Pilih >> ";
		getline(cin, pilihan);

		if (pilihan == "1")
		{
			registrasi(&HEAD_USER, &TAIL_USER);
		}
		else if (pilihan == "2")
		{
			login(HEAD_USER);
		}
		else if (pilihan == "3")
		{	
			string username, password;
				cout << "" << endl;
				cout << "LOGIN ADMIN" << endl;
				cout << "" << endl;
				cout<<"Username >> ";
				getline(cin, username);
				cout<<"Password >> ";
				getline(cin, password);
				if (username == "admin" && password == "admin"){
					cout<<""<<endl;
					cout<<"Login Berhasil"<<endl;
					cout<<""<<endl;
					cout<<"Silahkan Tekan Enter Untuk Melanjutkan...";
					getchar();
					menuAdmin();
				}
				else {
					cout<<""<<endl;
					cout<<"Login Gagal"<<endl;
					cout<<""<<endl;
					cout<<"Silahkan Tekan Enter Untuk Melanjutkan...";
					getchar();
					menuAwal();
				}
			
		}
		else if (pilihan == "4")
		{
			ulangi = false;
			cout << "" << endl;
			cout << "Silahkan Tekan Enter Untuk Kaluar...";
			getchar();
			break;
		}
		else
		{
			cout << "" << endl;
			cout << "Silahkan Coba Lagi" << endl;
			cout << "" << endl;
			cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
		}
	}
	clearScreen();
	cout << "" << endl;
	cout << "  ########  ##    ##   ######   ##    ##  ##    ##    ##    ##  ########  ##    ##" << endl;
	cout << "     ##     ##    ##  ##    ##  ####  ##  ##  ##       ##  ##   ##    ##  ##    ##" << endl;
	cout << "     ##     ########  ########  ## ## ##  ####          ####    ##    ##  ##    ##" << endl;
	cout << "     ##     ##    ##  ##    ##  ##  ####  ##  ##         ##     ##    ##  ##    ##" << endl;
	cout << "     ##     ##    ##  ##    ##  ##    ##  ##    ##       ##     ########  ########" << endl;
	exit(0);
}
// Menu Awal End

// Menu User Start
void menuUser()
{
	clearScreen();

	string pilihan;
	cout << "Menu User" << endl;
	cout << "[1] Melihat Jadwal" << endl;
	cout << "[2] Mencari Jadwal" << endl;
	cout << "[3] Daftar Pesanan" << endl;
	cout << "[4] Pemesanan Tiket" << endl;
	cout << "[0] Kembali" << endl;
	cout << "" << endl;
	cout << "Silahkan Pilih >> ";
	getline(cin, pilihan);


	if (pilihan == "1"){
		lihatJadwal();
		menuUser();
	}
	else if (pilihan == "2"){
		// cari
		cout<<"Nanti Dulu"<<endl;
	}
	else if (pilihan == "3"){
		daftarPesananUser();
	}
	else if (pilihan == "4"){
		pemesanan(&HEAD_PESANAN, &TAIL_PESANAN);
	}
	else if (pilihan == "0"){
		cout << "" << endl;
		cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
		getchar();
		// Untuk menghapus data user didalam dictionary userAktif
		userAktif.clear();
		menuAwal();
	}
	else
	{
		cout << "" << endl;
		cout << "Silahkan Coba Lagi" << endl;
		cout << "" << endl;
		cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
		getchar();
		menuUser();
	}
}
// Menu User End

// Lihat Jadwal Admin dan User Start
void lihatJadwal(){
	clearScreen();
	// quickSort(&HEAD_JADWAL);
	tabel("jadwal");
	cout<<""<<endl;
	cout<<"Silahkan Tekan Enter Untuk Kembali...";
	getchar();
}
// Lihat Jadwal Admin dan User End

// Mencari Jadwal Admin dan User Start
// OTW
// Mencari Jadwal Admin dan User End

// Daftar Pesanan User Start
void daftarPesananUser(){
	NodePesanan *panjangData = HEAD_PESANAN;
	int pjgId = 0, 
			pjgUser = 0, 
			pjgTiket = 0, 
			pjgMaskapai = 0, 
			pjgJadwal = 0, 
			pjgStatus = 0;
	while (panjangData != NULL)
	{	
		if (panjangData->data.user.length() > pjgUser){
			pjgUser = panjangData->data.user.length();
		}
		if (to_string(panjangData->data.jumlahTiket).length() > pjgTiket){
			pjgTiket = to_string(panjangData->data.jumlahTiket).length();
		}
		if (panjangData->data.maskapai.length() > pjgMaskapai){
			pjgMaskapai = panjangData->data.maskapai.length();
		}
		if (panjangData->data.jadwalPenerbangan.length() > pjgJadwal){
			pjgJadwal = panjangData->data.jadwalPenerbangan.length();
		}
		if (panjangData->data.status.length() > pjgStatus){
			pjgStatus = panjangData->data.status.length();
		}
		panjangData = panjangData->next;
	}
	NodePesanan *head = HEAD_PESANAN;
	NodePesanan *sementara = head;
	if (head == NULL){
		cout<< "" << endl;
		cout<< "Data Pemesanan Kosong" << endl;
		cout << "" << endl;
		cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
		getchar();
		menuUser();
		return;
	}
	if (pjgId < 2){
		pjgId = 2;
	}
	if (pjgUser < 16){
		pjgUser = 16;
	}
	if (pjgTiket < 5){
		pjgTiket = 5;
	}
	if (pjgMaskapai < 12){
		pjgMaskapai = 12;
	}
	if (pjgJadwal < 10){
		pjgJadwal = 10;
	}
	if (pjgStatus < 8){
		pjgStatus = 8;
	}
	int pjgBaris = pjgId + pjgUser + pjgTiket + pjgMaskapai + pjgJadwal + pjgStatus + 19;
	string baris(pjgBaris, '=');
	if (pjgBaris %2 == 0){
		string satuPerDuaBaris((pjgBaris/2)-11, '=');
		cout<<" "<< endl;
		cout<<baris<<endl;
		cout<< left << satuPerDuaBaris << " ";
		cout<< left << setw(9) << "INFORMASI PEMESANAN =";
		cout<< left << satuPerDuaBaris << endl;
		cout<<baris<<endl;
		cout<<"| " << left << setw(pjgId) << "No" << " ";
		cout<<"| " << left << setw(pjgUser) << "Nama Lengkap" << " ";
		cout<<"| " << left << setw(pjgTiket) << "Tiket" << " ";
		cout<<"| " << left << setw(pjgMaskapai) << "Maskapai" << " ";
		cout<<"| " << left << setw(pjgJadwal) << "Jadwal" << " ";
		cout<<"| " << left << setw(pjgStatus) << "Status" << " |" << endl;
		cout<<baris<<endl;
	}
	else {
		string satuPerDuaBaris((pjgBaris/2)-10, '=');
		cout<<" "<< endl;
		cout<<baris<<endl;
		cout<< left << satuPerDuaBaris << " ";
		cout<< left << setw(9) << "INFORMASI PEMESANAN ";
		cout<< left << satuPerDuaBaris << endl;
		cout<<baris<<endl;
		cout<<"| " << left << setw(pjgId) << "No" << " ";
		cout<<"| " << left << setw(pjgUser) << "Nama Lengkap" << " ";
		cout<<"| " << left << setw(pjgTiket) << "Tiket" << " ";
		cout<<"| " << left << setw(pjgMaskapai) << "Maskapai" << " ";
		cout<<"| " << left << setw(pjgJadwal) << "Jadwal" << " ";
		cout<<"| " << left << setw(pjgStatus) << "Status" << " |" << endl;
		cout<<baris<<endl;
	}

	string namaUser = userAktif["user aktif"];
	int nomor = 1;
	while(sementara != NULL){
		if (sementara->data.user == namaUser){
			cout<<"| " << left << setw(pjgId) << nomor << " ";
			cout<<"| " << left << setw(pjgUser) << sementara->data.user << " ";
			cout<<"| " << left << setw(pjgTiket) << sementara->data.jumlahTiket << " ";
			cout<<"| " << left << setw(pjgMaskapai) << sementara->data.maskapai << " ";
			cout<<"| " << left << setw(pjgJadwal) << sementara->data.jadwalPenerbangan << " ";
			cout<<"| " << left << setw(pjgStatus) << sementara->data.status << " |" << endl;
			cout<<baris<<endl;
			nomor++;
		}
		sementara = sementara->next;
	}
	cout << "" << endl;
	cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
	getchar();
	menuUser();
}
// Daftar Pesanan User End

// Pemesanan Tiket User Start
NodePesanan *newPesanan(){
	clearScreen();
	NodePesanan *newPesanan = new NodePesanan;
	string target_jadwal, jumlahTiket;
	bool ulangi = true;
	while (ulangi){
		tabel("jadwal");
		cout << "" << endl;
		cout << "PEMESANAN TIKET" << endl;
		cout << "" << endl;
		cout << "Silahkan Pilih ID Jadwal >> ";
		getline(cin, target_jadwal);
		if (isNumber(target_jadwal) == false){
			cout<<""<<endl;
			cout<<"ID Jadwal Salah (Harus Angka)"<<endl;
			cout<<""<<endl;
			cout<<"Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			clearScreen();
			continue;
		}
		if (target_jadwal > to_string(jumlahNode("jadwal")) || target_jadwal <= "0"){
			cout<<""<<endl;
			cout<<"ID Jadwal Tidak Ada (ID Jadwal Harus Sesuai Tabel)"<<endl;
			cout<<""<<endl;
			cout<<"Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			clearScreen();
			continue;
		}
		cout << "Jumlah Tiket     >> ";
		getline(cin, jumlahTiket);
		if (isNumber(jumlahTiket) == false){
			cout<<""<<endl;
			cout<<"Jumlah Tiket Salah (Harus Angka)"<<endl;
			cout<<""<<endl;
			cout<<"Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			clearScreen();
			continue;
		}
		if (jumlahTiket <= "0"){
			cout<<""<<endl;
			cout<<"Jumlah Tiket Salah (Harus Lebih Dari 0)"<<endl;
			cout<<""<<endl;
			cout<<"Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			clearScreen();
			continue;
		}
		int id_jadwal, jumlahTiket_valid;
		stringstream swapIdJadwal(target_jadwal);
		stringstream swapJumlahTiket(jumlahTiket);
		swapIdJadwal >> id_jadwal;
		swapJumlahTiket >> jumlahTiket_valid;
		newPesanan->data.user = userAktif["user aktif"];
		newPesanan->data.jumlahTiket = jumlahTiket_valid;
		NodeJadwal *head = HEAD_JADWAL;
    for (int i=1; i<id_jadwal; i++){
      head = head->next;
    }
    newPesanan->data.maskapai = head->data.maskapai;
    newPesanan->data.jadwalPenerbangan = head->data.jadwal;
    newPesanan->data.status = "Menunggu";
    return newPesanan;
	}
}

void pemesanan(NodePesanan **head, NodePesanan **tail){
	clearScreen();
	NodePesanan *node = newPesanan();
	NodePesanan *sementara = *head;

	node->prev = *tail;
  node->next = NULL;
  if (*head == NULL && *tail == NULL)
  {
    *head = node;
    *tail = node;
  }
  else
  {
    (*tail)->next = node;
    *tail = node;
  }
  cout << "" << endl;
  cout << "Pemesanan Berhasil" << endl;
  cout << "" << endl;
  cout << "Tagihan Dikirim Melalui Email" << endl;
  cout << "" << endl;
  cout << "Silahkan Lakukan Pembayaran" << endl;
  cout << "" << endl;
  cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
  getchar();
	menuUser();
}
// Pemesanan Tiket User End

// Menu Admin Start
void menuAdmin()
{
	clearScreen();

	string pilihan;
	cout << "Menu Admin" << endl;
	cout << "[1] Melihat Data User" << endl;
	cout << "[2] Konfirmasi Pesanan" << endl;
	cout << "[3] Pesanan Terkonfirmasi" << endl;
	cout << "[4] Melihat Jadwal" << endl;
	cout << "[5] Menambah Jadwal" << endl;
	cout << "[6] Mengubah Jadwal" << endl;
	cout << "[7] Menghapus Jadwal" << endl;
	cout << "[8] Mencari Jadwal" << endl;
	cout << "[0] Kembali" << endl;
	cout << "" << endl;
	cout << "Silahkan Pilih >> ";
	getline(cin, pilihan);

	if (pilihan == "1"){
		lihatUser();
	}
	else if (pilihan == "2"){
    konfirmasi();
	}
	else if (pilihan == "3"){

	}
	else if (pilihan == "4"){
		lihatJadwal();
		menuAdmin();
	}
	else if (pilihan == "5"){
		tambahJadwal(&HEAD_JADWAL, &TAIL_JADWAL);
    menuAdmin();
	}
	else if (pilihan == "6"){
		editJadwal(&HEAD_JADWAL, &TAIL_JADWAL);
		menuAdmin();
	}
	else if (pilihan == "7"){
		hapusJadwal(&HEAD_JADWAL, &TAIL_JADWAL);
		menuAdmin();
	}
	else if (pilihan == "8"){

	}
	else if (pilihan == "0"){
		cout<<""<<endl;
		cout<<"Silahkan Tekan Enter Untuk Kembali...";
		getchar();
		menuAwal();
	}
	else
	{
		cout << "" << endl;
		cout << "Silahkan Coba Lagi" << endl;
		cout << "" << endl;
		cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
		getchar();
		menuAdmin();
	}
}
// Menu Admin End

// Lihat User Start
void lihatUser()
{
	clearScreen();
	tabel("user");
	cout<<""<<endl;
	cout<<"Silahkan Tekan Enter Untuk Kembali...";
	getchar();
	menuAdmin();
}
// Lihat User End

// Konfirmasi Pesanan Start
void hapusAwal(NodePesanan **head, NodePesanan **tail){
  if ((*head)->next == NULL)
  {
    NodePesanan *del = *head;
    *head = NULL;
    *tail = NULL;
    delete del;
  }
  else {
    NodePesanan *del = *head;
    *head = (*head)->next;
    (*head)->prev = NULL;
    delete del;
  }
  cout << "" << endl;
  cout << "Konfirmasi Berhasil" << endl;
  cout << "" << endl;
  cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
  getchar();
  menuAdmin();
}

void konfirmasi()
{
	clearScreen();
	tabel("pesanan");
  if (HEAD_PESANAN == NULL && TAIL_PESANAN == NULL){
    cout<<""<<endl;
    cout<<"Silahkan Tekan Enter Untuk Melanjutkan..."<<endl;
    getchar();
    menuAdmin();
    return;
  }
	cout<<""<<endl;
  cout<<"[1] Konfirmasi Data Pesanan Nomor 1"<<endl;
  cout<<"[2] Kembali"<<endl;
	cout<<""<<endl;
  string pilihan;
  cout<<"Silahkan Pilih >> ";
  getline(cin, pilihan);

  if (pilihan == "1"){
    cout<<""<<endl;
    cout<<"Status Pembayaran"<<endl;
    cout<<"[1] Berhasil"<<endl;
    cout<<"[2] Gagal"<<endl;
    cout<<"[3] Kembali"<<endl;
    string respon;
    cout<<""<<endl;
    cout<<"Silahkan Pilih >> ";
    getline(cin, respon);
    if (respon == "1" || respon == "2"){
      hapusAwal(&HEAD_PESANAN, &TAIL_PESANAN);
    }
    else if (pilihan == "3"){
      cout<<""<<endl;
      cout<<"Silahkan Tekan Enter Untuk Kembali...";
      getchar();
      konfirmasi();
    }
  }
  if (pilihan == "2"){
    cout<<""<<endl;
    cout<<"Silahkan Tekan Enter Untuk Kembali...";
    getchar();
    menuAdmin();
  }
  else {
    cout << "" << endl;
		cout << "Silahkan Coba Lagi" << endl;
		cout << "" << endl;
		cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
		getchar();
		konfirmasi();
  }
}
// Konfirmasi Pesanan End

// Pesanan Terkonfirmasi Start
// OTW
// Pesanan Terkonfirmasi End

// Menambah Jadwal Start
NodeJadwal *newJadwal(){
	NodeJadwal *NodeBaru = new NodeJadwal;
	bool loop = true;
  string tanggal, kapasitas;
  while (loop){
    cout << "Nama Maskapai >> "; 
    getline(cin, NodeBaru->data.maskapai);
    cout << "Asal Keberangkatan >> "; 
    getline(cin, NodeBaru->data.asal);
    cout << "Tujuan Keberangkatan >> "; 
    getline(cin, NodeBaru->data.tujuan);
    cout << "Jadwal Penerbangan >> ";
    getline(cin, tanggal);

    bool valid = true;
    if (tanggal[4] != '-' || tanggal[7] != '-' || tanggal.length() != 10){
      cout<<""<<endl;
      cout<<"Format Tanggal Salah (Wajib YYYY-MM-DD)"<<endl;
      cout<<""<<endl;
      cout<<"Silahkan Tekan Enter Untuk Melanjutkan...";
      getchar();
      clearScreen();
      continue;
    }
    for (int i=0; i<tanggal.length(); i++){
      if (i == 4 || i == 7){
        continue;
      }
      if (isdigit(tanggal[i]) == 0){
        valid = false;
        break;
      }
    }
    if (!valid){
      cout<<""<<endl;
      cout<<"Jadwal Penerbangan Salah (Harus Angka)"<<endl;
      cout<<""<<endl;
      cout<<"Silahkan Tekan Enter Untuk Melanjutkan...";
      getchar();
      continue;
    }
    cout << "Kapasitas Pesawat >> "; 
    getline(cin, kapasitas);
    if (isNumber(kapasitas) == false){
			cout<<""<<endl;
			cout<<"Jumlah Kapasitas Salah (Harus Angka)"<<endl;
			cout<<""<<endl;
			cout<<"Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			clearScreen();
			continue;
		}
		if (kapasitas <= "0"){
			cout<<""<<endl;
			cout<<"Jumlah Kapasitas Salah (Harus Lebih Dari 0)"<<endl;
			cout<<""<<endl;
			cout<<"Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			clearScreen();
			continue;
		}
    int kapasitasValid;
    stringstream swapKapasitas(kapasitas);
    swapKapasitas >> kapasitasValid;
		// DIsini
    NodeBaru->data.jadwal = tanggal;
    NodeBaru->data.kapasitas = kapasitasValid;
    return NodeBaru;
  }
}

void tambahJadwal(NodeJadwal **head, NodeJadwal **tail){
  clearScreen();
  NodeJadwal *NodeBaru = newJadwal();
  NodeBaru->prev = *tail;
  NodeBaru->next = NULL;
  if (*head == NULL && *tail == NULL)
  {
    *head = NodeBaru;
    *tail = NodeBaru;
  }
  else
  {
    (*tail)->next = NodeBaru;
    *tail = NodeBaru;
  }
  cout << "" << endl;
  cout << "Jadwal Berhasil Ditambah" << endl;
  cout << "" << endl;
  cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
  getchar();
}
// Menambah Jadwal End

// Mengubah Jadwal Start
void editJadwal(NodeJadwal **head, NodeJadwal **tail){
  clearScreen();
  NodeJadwal *temp = *head;
  if (*head == NULL && *tail == NULL)
  {
    cout << "" << endl;
    cout << "Tidak Ada Jadwal" << endl;
    cout << "" << endl;
    cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
    getchar();
    return;
  }
	tabel("jadwal");
  string pilihan;
  cout<<""<<endl;
  cout<<"Silahkan Pilih >> ";
  getline(cin, pilihan);
  
  if (pilihan > to_string(jumlahNode("jadwal")) || pilihan <= "0"){
    cout << "" << endl;
    cout << "Pilihan Anda Tidak Ada" << endl;
    cout << "" << endl;
    cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
    getchar();
    return;
  }
  int pilihanValid;
  stringstream swapPilihan(pilihan);
  swapPilihan >> pilihanValid;
  for (int i=1; i<pilihanValid; i++){
    temp = temp->next;
  }

	NodePesanan *cekJadwal = HEAD_PESANAN;
	while (cekJadwal != NULL){
		if (cekJadwal->data.maskapai == temp->data.maskapai){
			cout << "" << endl;
			cout << "Jadwal Tidak Dapat Diedit" << endl;
			cout << "" << endl;
			cout << "Jadwal Sedang Ada Pada Pesanan" << endl;
			cout << "" << endl;
			cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			return;
		}
		cekJadwal = cekJadwal->next;
	}

  bool loop = true;
  string tanggal, kapasitas;
  while (loop){
    cout << "Nama Maskapai >> "; 
    getline(cin, temp->data.maskapai);
    cout << "Asal Keberangkatan >> "; 
    getline(cin, temp->data.asal);
    cout << "Tujuan Keberangkatan >> "; 
    getline(cin, temp->data.tujuan);
    cout << "Jadwal Penerbangan >> ";
    getline(cin, tanggal);

    bool valid = true;
    if (tanggal[4] != '-' || tanggal[7] != '-' || tanggal.length() != 10){
      cout<<""<<endl;
      cout<<"Format Tanggal Salah (Wajib YYYY-MM--DD)"<<endl;
      cout<<""<<endl;
      cout<<"Silahkan Tekan Enter Untuk Melanjutkan...";
      getchar();
      clearScreen();
      continue;
    }
    for (int i=0; i<tanggal.length(); i++){
      if (i == 4 || i == 7){
        continue;
      }
      if (isdigit(tanggal[i]) == 0){
        valid = false;
        break;
      }
    }
    if (!valid){
      cout<<""<<endl;
      cout<<"Jadwal Penerbangan Salah (Harus Angka)"<<endl;
      cout<<""<<endl;
      cout<<"Silahkan Tekan Enter Untuk Melanjutkan...";
      getchar();
      continue;
    }
    cout << "Kapasitas Pesawat >> "; 
    getline(cin, kapasitas);
    if (isNumber(kapasitas) == false){
			cout<<""<<endl;
			cout<<"Jumlah Kapasitas Salah (Harus Angka)"<<endl;
			cout<<""<<endl;
			cout<<"Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			clearScreen();
			continue;
		}
		if (kapasitas <= "0"){
			cout<<""<<endl;
			cout<<"Jumlah Kapasitas Salah (Harus Lebih Dari 0)"<<endl;
			cout<<""<<endl;
			cout<<"Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			clearScreen();
			continue;
		}
    int tanggalValid, kapasitasValid;
    stringstream swapTanggal(tanggal);
    stringstream swapKapasitas(kapasitas);
    swapTanggal >> tanggalValid;
    swapKapasitas >> kapasitasValid;
    temp->data.jadwal = tanggalValid;
    temp->data.kapasitas = kapasitasValid;
    cout << "" << endl;
    cout << "Jadwal Berhasil Diubah" << endl;
    cout << "" << endl;
    cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
    getchar();
    return;
  }
}
// Mengubah Jadwal End

// Menghapus Jadwal Start
void hapusJadwal(NodeJadwal **head, NodeJadwal **tail){
  clearScreen();
  NodeJadwal *temp = *head;
  if (*head == NULL && *tail == NULL)
  {
    cout << "" << endl;
    cout << "Tidak Ada Jadwal" << endl;
    cout << "" << endl;
    cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
    getchar();
    return;
  }
	tabel("jadwal");
  string pilihan;
  cout<<""<<endl;
  cout<<"Silahkan Pilih >> ";
  getline(cin, pilihan);

  if (pilihan > to_string(jumlahNode("jadwal")) || pilihan <= "0"){
    cout << "" << endl;
    cout << "Pilihan Anda Tidak Ada" << endl;
    cout << "" << endl;
    cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
    getchar();
    return;
  }
  int pilihanValid;
  stringstream swapPilihan(pilihan);
  swapPilihan >> pilihanValid;
  if (pilihanValid == 1)
  {
    if ((*head)->next == NULL)
    {
      NodeJadwal *del = *head;
			NodePesanan *cekJadwal = HEAD_PESANAN;
			while (cekJadwal != NULL){
				if (cekJadwal->data.maskapai == del->data.maskapai){
					cout << "" << endl;
					cout << "Jadwal Tidak Dapat Dihapus" << endl;
					cout << "" << endl;
					cout << "Jadwal Sedang Ada Pada Pesanan" << endl;
					cout << "" << endl;
					cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
					getchar();
					return;
				}
				cekJadwal = cekJadwal->next;
			}
      *head = NULL;
      *tail = NULL;
      delete del;
    }
    else
    {
      NodeJadwal *del = *head;
			NodePesanan *cekJadwal = HEAD_PESANAN;
			while (cekJadwal != NULL){
				if (cekJadwal->data.maskapai == del->data.maskapai){
					cout << "" << endl;
					cout << "Jadwal Tidak Dapat Dihapus" << endl;
					cout << "" << endl;
					cout << "Jadwal Sedang Ada Pada Pesanan" << endl;
					cout << "" << endl;
					cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
					getchar();
					return;
				}
				cekJadwal = cekJadwal->next;
			}
      *head = (*head)->next;
      (*head)->prev = NULL;
      delete del;
    }
  }
  else if (pilihanValid == jumlahNode("jadwal") && pilihanValid > 1)
  {
    if ((*head)->next == NULL)
    {
      NodeJadwal *del = *head;
			NodePesanan *cekJadwal = HEAD_PESANAN;
			while (cekJadwal != NULL){
				if (cekJadwal->data.maskapai == del->data.maskapai){
					cout << "" << endl;
					cout << "Jadwal Tidak Dapat Dihapus" << endl;
					cout << "" << endl;
					cout << "Jadwal Sedang Ada Pada Pesanan" << endl;
					cout << "" << endl;
					cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
					getchar();
					return;
				}
				cekJadwal = cekJadwal->next;
			}
      *head = NULL;
      *tail = NULL;
      delete del;
    }
    else
    {
			NodeJadwal *del = *tail;
			NodePesanan *cekJadwal = HEAD_PESANAN;
			while (cekJadwal != NULL){
				if (cekJadwal->data.maskapai == del->data.maskapai){
					cout << "" << endl;
					cout << "Jadwal Tidak Dapat Dihapus" << endl;
					cout << "" << endl;
					cout << "Jadwal Sedang Ada Pada Pesanan" << endl;
					cout << "" << endl;
					cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
					getchar();
					return;
				}
				cekJadwal = cekJadwal->next;
			}
			*tail = (*tail)->prev;
      (*tail)->next = NULL;
      delete del;
			tabel("jadwal");
			getchar();
    }
  }
  else {
		int nomor = 1;
    NodeJadwal *temporary = *head;
    NodeJadwal *before;
    NodeJadwal *data;
		while (nomor <= pilihanValid)
    {
      if (nomor == pilihanValid - 1)
      {
        before = temporary;
      }
      if (nomor == pilihanValid)
      {
        data = temporary;
      }
      temporary = temporary->next;
      nomor++;
    }

		NodePesanan *cekJadwal = HEAD_PESANAN;
		while (cekJadwal != NULL){
			if (cekJadwal->data.maskapai == data->data.maskapai){
				cout << "" << endl;
				cout << "Jadwal Tidak Dapat Dihapus" << endl;
				cout << "" << endl;
				cout << "Jadwal Sedang Ada Pada Pesanan" << endl;
				cout << "" << endl;
				cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
				getchar();
				return;
			}
			cekJadwal = cekJadwal->next;
		}
		before->next = temporary;
    temporary->prev = before;
    delete data;
  }
  cout << "" << endl;
  cout << "Jadwal Berhasil Dihapus" << endl;
  cout << "" << endl;
  cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
  getchar();
}
// Menghapus Jadwal End

int main()
{
	user1.prev = NULL;
	user1.data.nama_lengkap = "Asep";
	user1.data.password = "123";
	// @ untuk testing aja
	user1.data.email = "@";
	user1.data.no_hp = "0812";
	user1.data.alamat = "Jalan Jakarta";
	user1.next = NULL;

  pesanan1.prev = NULL;
  pesanan1.data.user = "Asep";
  pesanan1.data.jumlahTiket = 3;
  pesanan1.data.maskapai = "Batik Air";
  pesanan1.data.jadwalPenerbangan = "2022-09-10";
  pesanan1.data.status = "Menunggu";
  pesanan1.next = NULL;

	jadwal1.prev = NULL;
	jadwal1.data.maskapai = "Lion Air";
	jadwal1.data.asal = "Jakarta";
	jadwal1.data.tujuan = "Balikpapan";
	jadwal1.data.jadwal = "2022-09-10";
	jadwal1.data.kapasitas = 50;
	jadwal1.next = &jadwal2;

	jadwal2.prev = &jadwal1;
	jadwal2.data.maskapai = "Batik Air";
	jadwal2.data.asal = "Bali";
	jadwal2.data.tujuan = "Singapura";
	jadwal2.data.jadwal = "2022-11-11";
	jadwal2.data.kapasitas = 70;
	jadwal2.next = &jadwal3;

	jadwal3.prev = &jadwal2;
	jadwal3.data.maskapai = "Sriwijaya Air";
	jadwal3.data.asal = "Samarinda";
	jadwal3.data.tujuan = "Padang";
	jadwal3.data.jadwal = "2022-10-09";
	jadwal3.data.kapasitas = 40;
	jadwal3.next = &jadwal4;

	jadwal4.prev = &jadwal3;
	jadwal4.data.maskapai = "Sriwijayaasas Air";
	jadwal4.data.asal = "Samarinasada";
	jadwal4.data.tujuan = "Padasang";
	jadwal4.data.jadwal = "2022-11-09";
	jadwal4.data.kapasitas = 40;
	jadwal4.next = NULL;
	nextIdJadwal = jumlahNode("jadwal");

	// quickSort(&HEAD_JADWAL);
	// tabel("jadwal");
  // Menu Awal [DONE]
	// menuAwal();

  // Menu User [-1]
  // menuUser();

  // Menu Admin [-2]
  menuAdmin();
	return 0;
}