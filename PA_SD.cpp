#include <iostream>
#include <string>
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
	string jenis;
	string asal;
	string tujuan;
	string jadwal;
	int kapasitas;
};

struct pesanan {
	int id_pesanan;
	int id_user;
	int id_jadwal;
};

struct NodeUser {
	user data;
	NodeUser *prev = NULL;
	NodeUser *next = NULL;
};

struct NodeJadwal {
	jadwal data;
	NodeJadwal *prev = NULL;
	NodeJadwal *next = NULL;
};

struct NodePesanan {
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

// Untuk membuat id setiap struct
int createId(string jenis){
	int idTerakhir = 0;
	if (jenis == "user"){
		NodeUser *head = HEAD_USER;
		while (head != NULL)
		{
			idTerakhir++;
			head = head->next;
		}
	}
	if (jenis == "pesanan"){
		NodePesanan *head = HEAD_PESANAN;
		while (head != NULL)
		{
			idTerakhir++;
			head = head->next;
		}
	}
	if (jenis == "jadwal"){
		NodeJadwal *head = HEAD_JADWAL;
		while (head != NULL)
		{
			idTerakhir++;
			head = head->next;
		}
	}
	return idTerakhir+1;
}

// Untuk mengetahui jumlah node setiap struct
int jumlahNode(string jenis){
	int jumlah = 0;
	if (jenis == "user"){
		NodeUser *head = HEAD_USER;
		while (head != NULL)
		{
			jumlah++;
			head = head->next;
		}
	}
	if (jenis == "pesanan"){
		NodePesanan *head = HEAD_PESANAN;
		while (head != NULL)
		{
			jumlah++;
			head = head->next;
		}
	}
	if (jenis == "jadwal"){
		NodeJadwal *head = HEAD_JADWAL;
		while (head != NULL)
		{
			jumlah++;
			head = head->next;
		}
	}
	return jumlah;
}

void menuUser(){
	clearScreen();

	string pilihan;
	cout<<"Menu Awal"<<endl;
	cout<<"[1] Register"<<endl;
	cout<<"[2] Login"<<endl;
	cout<<"[3] Keluar"<<endl;
	cout<<""<<endl;
	cout<<"Silahkan Pilih >> ";
	getline(cin, pilihan); cin.sync();
}

void menuAdmin(){
	clearScreen();

	string pilihan;
	cout<<"Menu Awal"<<endl;
	cout<<"[1] Register"<<endl;
	cout<<"[2] Login"<<endl;
	cout<<"[3] Keluar"<<endl;
	cout<<""<<endl;
	cout<<"Silahkan Pilih >> ";
	getline(cin, pilihan); cin.sync();
}

int main() {
	user1.prev = NULL;
	user1.data.id_user = 1;
	user1.data.nama_lengkap = "Asep";
	user1.data.password = "123";
	user1.data.email = "A@gmail.com";
	user1.data.no_hp = "0812";
	user1.data.alamat = "Jalan Jakarta";
	user1.next = NULL;

	// Baris dibawah ini untuk uji coba createId dan jumlahNode setiap struct
	// int jmlUser = jumlahNode("user");
	// cout<<"jumlah user sekarang : "<<jmlUser<<endl;
	// int idNextUser = createId("user");
	// cout<<"id next User: "<<idNextUser<<endl;
	// cout<<""<<endl;

	// int jmlPesanan = jumlahNode("pesanan");
	// cout<<"jumlah pesanan sekarang : "<<jmlPesanan<<endl;
	// int idNextPesanan = createId("pesanan");
	// cout<<"id next Pesanan : "<<idNextPesanan<<endl;
	// cout<<""<<endl;

	// int jmlJadwal = jumlahNode("jadwal");
	// cout<<"jumlah jadwal sekarang : "<<jmlJadwal<<endl;
	// int idNextJadwal = createId("jadwal");
	// cout<<"id next Jadwal : "<<idNextJadwal<<endl;
	// cout<<""<<endl;
	// getchar();
	// exit(0)
	// Stop!, Baris terakhir dari uji coba createId dan jumlahNode setiap struct

  data1.prev = NULL;
  data1.data.maskapai = "Lion Air";
  data1.data.jenis = "Domestik";
  data1.data.asal = "Jakarta";
  data1.data.tujuan = "Balikpapan";
  data1.data.jadwal = "2022-09-10";
  data1.data.kapasitas = 50;
  data1.next = &data2;

  data2.prev = &data1;
  data2.data.maskapai = "Batik Air";
  data2.data.jenis = "Internasional";
  data2.data.asal = "Bali";
  data2.data.tujuan = "Singapura";
  data2.data.jadwal = "2022-10-11";
  data2.data.kapasitas = 70;
  data2.next = &data3;

  data3.prev = &data2;
  data3.data.maskapai = "Sriwijaya Air";
  data3.data.jenis = "Domestik";
  data3.data.asal = "Bali";
  data3.data.tujuan = "Padang";
  data3.data.jadwal = "2022-10-09";
  data3.data.kapasitas = 40;
  data3.next = NULL;
	// bool ulangi = true;
	bool ulangi = false;
	while (ulangi){
		clearScreen();

		string pilihan;
		cout<<"Menu Awal"<<endl;
		cout<<"[1] Register"<<endl;
		cout<<"[2] Login"<<endl;
		cout<<"[3] Keluar"<<endl;
		cout<<""<<endl;
		cout<<"Silahkan Pilih >> ";
		getline(cin, pilihan); cin.sync();

		if (pilihan == "1"){
			// registrasi();
		}
		else if (pilihan == "2"){
			// login()
		}
		else if (pilihan == "3"){
			ulangi = false;
			cout<<""<<endl;
			cout <<"Silahkan Tekan Enter Untuk Melanjutkan...";
      getchar();
      break;
		}
		else {
			cout<<""<<endl;
			cout<<"Silahkan Coba Lagi"<<endl;
			cout<<""<<endl;
			cout <<"Silahkan Tekan Enter Untuk Melanjutkan...";
      getchar();
		}
	}

	clearScreen();
  cout << "" << endl;
  cout << "\t  ########  ##    ##   ######   ##    ##  ##    ##    ##    ##  ########  ##    ##" << endl;
  cout << "\t     ##     ##    ##  ##    ##  ####  ##  ##  ##       ##  ##   ##    ##  ##    ##" << endl;
  cout << "\t     ##     ########  ########  ## ## ##  ####          ####    ##    ##  ##    ##" << endl;
  cout << "\t     ##     ##    ##  ##    ##  ##  ####  ##  ##         ##     ##    ##  ##    ##" << endl;
  cout << "\t     ##     ##    ##  ##    ##  ##    ##  ##    ##       ##     ########  ########" << endl;
  exit(0);
}