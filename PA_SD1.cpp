#include <iostream>
#include <string>
#include <iomanip>
#include <map>
#include <stdlib.h>
using namespace std;

struct user
{
	int id_user;
	string nama_lengkap;
	string password;
	string email;
	string no_hp;
	string alamat;
};

struct jadwal
{
	int id_jadwal;
	string maskapai;
	string asal;
	string tujuan;
	string jadwal;
	int kapasitas;
};

struct pesanan
{
	int id_pesanan;
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
NodePesanan *HEAD_PESANAN = NULL;
NodePesanan *TAIL_PESANAN = NULL;

// Program dimulai dengan 3 data jadwal
NodeJadwal data1;
NodeJadwal data2;
NodeJadwal data3;
NodeJadwal *HEAD_JADWAL = &data1;
NodeJadwal *TAIL_JADWAL = &data3;

void registrasi(NodeUser, NodeUser);
void menuAwal();
void menuAdmin();
void menuUser();

void lihatUser();
void lihatJadwal();
map<string, string> userAktif;

// Untuk membersihkan layar
void clearScreen()
{
	system("cls");
}

// Untuk mengecek apakah inputan adalah angka valid
bool isNumber(string data)
{
	for (int i = 0; i < data.length(); i++)
		if (isdigit(data[i]) == false)
			// Berarti bukan angka valid
			return false;
	// Berarti angka valid
	return true;
}

// Untuk mengetahui jumlah node setiap struct
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

// Untuk mengetahui data terpanjang pada suatu atribut setiap struct
int panjangData(string jenis, string data){
	int panjang = 0;
	if (jenis == "user"){
		NodeUser *head = HEAD_USER;
		while (head != NULL)
		{	
			int id_user, nama_lengkap, password, email, no_hp, alamat;
			if (to_string(head->data.id_user).length() > panjang){
				id_user = to_string(head->data.id_user).length();
			}
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
			if (data == "id_user"){
				panjang = id_user;
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
			int id_pesanan, user, jumlahTiket, maskapai, jadwalPenerbangan, status;
			if (to_string(head->data.id_pesanan).length() > panjang){
				id_pesanan = to_string(head->data.id_pesanan).length();
			}
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
			if (data == "id_pesanan"){
				panjang = id_pesanan;
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
			int id_jadwal, maskapai, asal, tujuan, jadwalPenerbangan, kapasitas;
			if (to_string(head->data.id_jadwal).length() > panjang){
				id_jadwal = to_string(head->data.id_jadwal).length();
			}
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
			if (data == "id_jadwal"){
				panjang = id_jadwal;
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

// Untuk membuat tabel berdasarkan struct
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
		int pjgId = panjangData("user", "id_user");
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
			cout<< left << setw(9) << "DATA USER =";
			cout<< left << satuPerDuaBaris << endl;
			cout<<baris<<endl;
			cout<<"| " << setiosflags(ios::left) << setw(pjgId) << "Id" << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgNama) << "Nama Lengkap" << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgPassword) << "Password" << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgEmail) << "Email" << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgNoHp) << "No Hp" << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgAlamat) << "Alamat" << " |" << endl;
			cout<<baris<<endl;
		}
		else {
			string satuPerDuaBaris((pjgBaris/2)-5, '=');
			cout<<" "<< endl;
			cout<<baris<<endl;
			cout<< left << satuPerDuaBaris << " ";
			cout<< left << setw(9) << "DATA USER ";
			cout<< left << satuPerDuaBaris << endl;
			cout<<baris<<endl;
			cout<<"| " << setiosflags(ios::left) << setw(pjgId) << "Id" << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgNama) << "Nama Lengkap" << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgPassword) << "Password" << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgEmail) << "Email" << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgNoHp) << "No Hp" << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgAlamat) << "Alamat" << " |" << endl;
			cout<<baris<<endl;
		}

		while(sementara != NULL){
			cout<<"| " << setiosflags(ios::left) << setw(pjgId) << sementara->data.id_user << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgNama) << sementara->data.nama_lengkap << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgPassword) << sementara->data.password << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgEmail) << sementara->data.email << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgNoHp) << sementara->data.no_hp << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgAlamat) << sementara->data.alamat << " |" << endl;
			cout<<baris<<endl;
			sementara = sementara->next;
		}
	}

	if (jenis == "jadwal"){
		NodeJadwal *head = HEAD_JADWAL;
		if (head == NULL){
			cout<< "" << endl;
			cout<< "Data Jadwal Kosong" << endl;
			return;
		}

		NodeJadwal *sementara = head;
		int pjgId = panjangData("jadwal", "id_jadwal");
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
		if (pjgKapasitas < 12){
			pjgKapasitas = 12;
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
			cout<<"| " << setiosflags(ios::left) << setw(pjgId) << "Id" << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgMaskapai) << "Maskapai" << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgAsal) << "Asal" << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgTujuan) << "Tujuan" << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgJadwal) << "Jadwal" << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgKapasitas) << "Kapasitas" << " |" << endl;
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
			cout<<"| " << setiosflags(ios::left) << setw(pjgId) << "Id" << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgMaskapai) << "Maskapai" << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgAsal) << "Asal" << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgTujuan) << "Tujuan" << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgJadwal) << "Jadwal" << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgKapasitas) << "Kapasitas" << " |" << endl;
			cout<<baris<<endl;
		}

		while(sementara != NULL){
			cout<<"| " << setiosflags(ios::left) << setw(pjgId) << sementara->data.id_jadwal << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgMaskapai) << sementara->data.maskapai << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgAsal) << sementara->data.asal << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgTujuan) << sementara->data.tujuan << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgJadwal) << sementara->data.jadwal << " ";
			cout<<"| " << setiosflags(ios::left) << setw(pjgKapasitas) << sementara->data.kapasitas << " |" << endl;
			cout<<baris<<endl;
			sementara = sementara->next;
		}
	}
}

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
	cin.sync();

	if (pilihan == "1"){
		lihatJadwal();
	}
	else if (pilihan == "2"){
		
	}
	else if (pilihan == "3"){

	}
	else if (pilihan == "4"){

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
	}
}

void lihatUser()
{
	clearScreen();
	tabel("user");
	cout<<""<<endl;
	cout<<"Silahkan Tekan Enter Untuk Kembali...";
	getchar();
	menuAdmin();
}

void lihatJadwal(){
	clearScreen();
	tabel("jadwal");
	cout<<""<<endl;
	cout<<"Silahkan Tekan Enter Untuk Kembali...";
	getchar();
	menuAdmin();
}

NodeJadwal *tambahJadwal(NodeJadwal *HEAD_JADWAL){
	NodeJadwal *NodeBaru = new NodeJadwal;
	bool loop = true;
	NodeJadwal *temp = HEAD_JADWAL;
	while (loop){
        cout << "Masukkan ID >> "; cin >> NodeBaru->data.id_jadwal;
        while (temp->next != NULL){
            if (temp->data.id_jadwal == NodeBaru->data.id_jadwal){
                cout << "ID Sudah Terdaftar, Silakan Gunakan ID Yang Lain" << endl;
                break;
            } else {
                temp = temp->next;
            }
            if (temp->next == NULL){
                loop = false;
            }
        }
    }
	cout << "Masukkan Maskapai >> "; fflush(stdin); getline(cin, NodeBaru->data.maskapai); cin.sync();
	cout << "Masukkan Asal Keberangkatan >> "; fflush(stdin); getline(cin, NodeBaru->data.asal); cin.sync();
	cout << "Masukkan Tujuan >> "; fflush(stdin); getline(cin, NodeBaru->data.tujuan); cin.sync();
	cout << "Masukkan Jadwal Penerbangan >> "; fflush(stdin); getline(cin, NodeBaru->data.jadwal); cin.sync();
	cout << "Masukkan Kapasitas >> "; cin >> NodeBaru->data.kapasitas;
	return NodeBaru;
}

void addjadwal(NodeJadwal **HEAD_JADWAL, NodeJadwal **TAIL_JADWAL){
    NodeJadwal *NodeBaru = tambahJadwal(*HEAD_JADWAL);
    NodeBaru->prev = *TAIL_JADWAL;
    NodeBaru->next = NULL;
    (*TAIL_JADWAL)->next = NodeBaru;
    *TAIL_JADWAL = NodeBaru;
}

void updatejadwal(NodeJadwal **HEAD_JADWAL){
	int ID ;
	NodeJadwal *temp = *HEAD_JADWAL;
	clearScreen();
	tabel("jadwal");
	cout<<"\nSilahkan Tekan Enter Untuk Kembali...";
	getchar();
	masukkanID:
		cout << "Masukkan ID >> "; cin >> ID;
		if (ID <= jumlahNode("jadwal") && ID > 0){
		for (int i = 1; i < ID; i++){
			temp = temp->next;
		}
			cout << "Masukkan Maskapai >> "; fflush(stdin); getline(cin, temp->data.maskapai); cin.sync();
			cout << "Masukkan Asal Keberangkatan >> "; fflush(stdin); getline(cin, temp->data.asal); cin.sync();
			cout << "Masukkan Tujuan >> "; fflush(stdin); getline(cin, temp->data.tujuan); cin.sync();
			cout << "Masukkan Jadwal Penerbangan >> "; fflush(stdin); getline(cin, temp->data.jadwal); cin.sync();
			cout << "Masukkan Kapasitas >> "; cin >> temp->data.kapasitas;
			cout<<"Silahkan Tekan Enter Untuk Melanjutkan..."; getchar();
		} else {
			system("pause");
			cout << "ID Tidak Terdaftar, Silakan Gunakan ID Yang Sudah Terdaftar" << endl;
			cout<<"Silahkan Tekan Enter Untuk Melanjutkan..."; getchar();
			updatejadwal(HEAD_JADWAL);
		}
			
			
		
}

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
	cin.sync();

	if (pilihan == "1"){
		lihatUser();
	}
	else if (pilihan == "2"){

	}
	else if (pilihan == "3"){

	}
	else if (pilihan == "4"){
		lihatJadwal();
	}
	else if (pilihan == "5"){
		addjadwal(&HEAD_JADWAL, &TAIL_JADWAL);
	}
	else if (pilihan == "6"){
		updatejadwal(&HEAD_JADWAL);
	}
	else if (pilihan == "7"){

	}
	else if (pilihan == "8"){

	}
	else if (pilihan == "0"){
		cout<<""<<endl;
		cout<<"Silahkan Tekan Enter Untuk Kembali...";
		getchar();
		menuAdmin();
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

void pemesanan(){
	tabel("jadwal");
}

void login(NodeUser *head){
	bool ulangi = true;
	string email, password;
	while (ulangi){
		cout << "" << endl;
		cout << "LOGIN USER" << endl;
		cout << "" << endl;
		cout<<"Email >> ";
		getline(cin, email); cin.sync();
		cout<<"Password >> ";
		getline(cin, password); cin.sync();

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

NodeUser *newUser(){
	NodeUser *newUser = new NodeUser;
	string nama_lengkap, password, konfirmasi, email, no_hp, alamat;
	bool ulangi = true;
	while (ulangi){
		cout << "" << endl;
		cout << "REGISTRASI USER" << endl;
		cout << "" << endl;
		cout << "Nama Lengkap  >> ";
		getline(cin, nama_lengkap); cin.sync();
		cout << "Password     >> ";
		getline(cin, password); cin.sync();
		cout << "Konfirmasi Password >> ";
		getline(cin, konfirmasi); cin.sync();
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
		getline(cin, email); cin.sync();
		cout << "No HP >> ";
		getline(cin, no_hp); cin.sync();
		cout << "Alamat >> ";
		getline(cin, alamat); cin.sync();
		newUser->data.id_user = jumlahNode("user")+1;
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
		cin.sync();

		if(pilihan == "5"){
			tabel("user");
			getchar();
			menuAwal();
		}

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
				getline(cin, username); cin.sync();
				cout<<"Password >> ";
				getline(cin, password); cin.sync();
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

int main()
{
	user1.prev = NULL;
	user1.data.id_user = 1;
	user1.data.nama_lengkap = "Asep";
	user1.data.password = "123";
	user1.data.email = "A@gmail.com";
	user1.data.no_hp = "0812";
	user1.data.alamat = "Jalan Jakarta";
	user1.next = NULL;

	data1.prev = NULL;
	data1.data.id_jadwal = 1;
	data1.data.maskapai = "Lion Air";
	data1.data.asal = "Jakarta";
	data1.data.tujuan = "Balikpapan";
	data1.data.jadwal = "2022-09-10";
	data1.data.kapasitas = 50;
	data1.next = &data2;

	data2.prev = &data1;
	data2.data.id_jadwal = 2;
	data2.data.maskapai = "Batik Air";
	data2.data.asal = "Bali";
	data2.data.tujuan = "Singapura";
	data2.data.jadwal = "2022-10-11";
	data2.data.kapasitas = 70;
	data2.next = &data3;

	data3.prev = &data2;
	data3.data.id_jadwal = 3;
	data3.data.maskapai = "Sriwijaya Air";
	data3.data.asal = "Bali";
	data3.data.tujuan = "Padang";
	data3.data.jadwal = "2022-10-09";
	data3.data.kapasitas = 40;
	data3.next = NULL;
	menuAwal();
	return 0;
}
