#include <iostream>
#include <string>
#include <iomanip>
#include <map>
#include <fstream>
#include <sstream>
#include <Windows.h>
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
void mencariJadwal();
void tampilkanHasilSearching(int index);

// Hanya dapat diakses Admin
void menuAdmin();
void lihatUser();
void konfirmasi();
void hapusAwal(NodePesanan **head, NodePesanan **tail, string);
void tambahJadwal(NodeJadwal **head, NodeJadwal **tail);
void editJadwal(NodeJadwal **head, NodeJadwal **tail);
void hapusJadwal(NodeJadwal **head, NodeJadwal **tail);

// Untuk Pesanan Terkonfirmasi (Menu Admin)
int getIndex();
void ambilData();
void simpanData();
void pesananSelesai();
// Array untuk menyimpan data sementara dari file external
pesanan pesananTerkonfirmasi[999] = {};

// Hanya dapat diakses User
void menuUser();
void daftarPesananUser();
void pemesanan(NodePesanan **head, NodePesanan **tail);

// Dictionary untuk mengetahui User yang aktif
map<string, string> userAktif;

// Quick Sort Start (Untuk Atribut Jadwal)
void swap(NodeJadwal *data1, NodeJadwal *data2)
{
	NodeJadwal t;
	t = *data1;
	*data1 = *data2;
	*data2 = t;
}

NodeJadwal *lastNode(NodeJadwal *root)
{
	while (root->next != NULL)
		root = root->next;
	return root;
}

NodeJadwal *partition(NodeJadwal *head, NodeJadwal *tail)
{
	// Set pivot as head element
	string pivot = tail->data.jadwal;
	// Similar to i = l-1 for array implementation
	NodeJadwal *i = head->prev;
	// Similar to "for (int j = l; j <= h- 1; j++)"
	for (NodeJadwal *j = head; j != tail; j = j->next)
	{
		if (j->data.jadwal <= pivot)
		{
			// Similar to i++ for array
			i = (i == NULL) ? head : i->next;
			swap((i->data), (j->data));
		}
	}
	i = (i == NULL) ? head : i->next; // Similar to i++
	swap((i->data), (tail->data));
	return i;
}

void quickSortRecursive(NodeJadwal *head, NodeJadwal *tail)
{
	if (tail != NULL && head != tail && head != tail->next)
	{
		NodeJadwal *partisi = partition(head, tail);
		quickSortRecursive(head, partisi->prev);
		quickSortRecursive(partisi->next, tail);
	}
}

void quickSort(NodeJadwal *head)
{
	// Find last node
	NodeJadwal *tail = lastNode(head);

	// Call the recursive QuickSort
	quickSortRecursive(head, tail);
}
// Quick Sort End (Untuk Atribut Jadwal)

// Merge Sort Start (Untuk Atribut Maskapai)
void FrontBackSplit(NodeJadwal *source, NodeJadwal **frontRef, NodeJadwal **backRef)
{
	NodeJadwal *fast;
	NodeJadwal *slow;
	slow = source;
	fast = source->next;

	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}

NodeJadwal *SortedMergeMaskapai(NodeJadwal *a, NodeJadwal *b)
{
	NodeJadwal *result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (a->data.maskapai <= b->data.maskapai)
	{
		result = a;
		result->next = SortedMergeMaskapai(a->next, b);
	}
	else
	{
		result = b;
		result->next = SortedMergeMaskapai(a, b->next);
	}
	return (result);
}

void MergeSortMaskapai(NodeJadwal **headRef)
{
	NodeJadwal *head = *headRef;
	NodeJadwal *a;
	NodeJadwal *b;
	if ((head == NULL) || (head->next == NULL))
	{
		return;
	}
	FrontBackSplit(head, &a, &b);
	MergeSortMaskapai(&a);
	MergeSortMaskapai(&b);
	*headRef = SortedMergeMaskapai(a, b);
}
// Merge Sort End (Untuk Atribut Maskapai)

// Fibonacci Search Start
int fibonacciSearchMaskapai(NodeJadwal *node, string x, int n)
{
	int F0 = 0;
	int F1 = 1;
	int F = F0 + F1;
	while (F < n)
	{
		F0 = F1;
		F1 = F;
		F = F0 + F1;
	}
	int offset = -1;
	int trv = 0;
	while (F > 1)
	{
		NodeJadwal *temp = node;
		int i = min(offset + F0, n - 1);
		while (temp->next != NULL && trv < i)
		{
			temp = temp->next;
			trv++;
		}
		if (temp->data.maskapai < x)
		{
			F = F1;
			F1 = F0;
			F0 = F - F1;
			offset = i;
		}
		else if (temp->data.maskapai > x)
		{
			F = F0;
			F1 = F1 - F0;
			F0 = F - F1;
		}
		else{
			return i;
		}
		trv = 0;
	}
	NodeJadwal *temp2 = node;
	while (temp2->next != NULL && trv < offset + 1)
	{
		temp2 = temp2->next;
		trv++;
	}
	if (F1 && temp2->data.maskapai == x)
		return offset+1;
	return -1;
}
// Fibonacci Search End

// Baca dan Tulis File External Start
// Untuk mengambil data dari file pesananTerkonfirmasi.txt
void ambilData()
{
	fstream myFile;
	myFile.open("pesananTerkonfirmasi.txt", ios::in);
	string baris;
	int index = 0;
	int indexBaris = 0;
	while (!myFile.eof())
	{
		getline(myFile, baris);
		if (baris == "==========")
		{
			continue;
		}
		if (indexBaris == 0)
		{
			pesananTerkonfirmasi[index].user = baris;
		}
		if (indexBaris == 1)
		{
			int jumlahTiket;
			stringstream swapJumlahTiket(baris);
			swapJumlahTiket >> jumlahTiket;
			pesananTerkonfirmasi[index].jumlahTiket = jumlahTiket;
		}
		if (indexBaris == 2)
		{
			pesananTerkonfirmasi[index].maskapai = baris;
		}
		if (indexBaris == 3)
		{
			pesananTerkonfirmasi[index].jadwalPenerbangan = baris;
		}
		if (indexBaris == 4)
		{
			pesananTerkonfirmasi[index].status = baris;
		}
		indexBaris++;
		if (indexBaris % 5 == 0)
		{
			index++;
			indexBaris = 0;
		}
	}
	myFile.close();
}

// Untuk menyimpan data ke file pesananTerkonfirmasi.txt
void simpanData()
{
	fstream myFile;
	myFile.open("pesananTerkonfirmasi.txt", ios::out | ios::trunc);
	for (int i = 0; i < 999; i++)
	{
		if (pesananTerkonfirmasi[i].user == "")
		{
			break;
		}
		myFile << "==========" << endl;
		myFile << pesananTerkonfirmasi[i].user << endl;
		myFile << pesananTerkonfirmasi[i].jumlahTiket << endl;
		myFile << pesananTerkonfirmasi[i].maskapai << endl;
		myFile << pesananTerkonfirmasi[i].jadwalPenerbangan << endl;
		myFile << pesananTerkonfirmasi[i].status << endl;
		myFile.close();
	}
}
// Baca dan Tulis File External End

// Untuk membersihkan layar
void clearScreen()
{
	system("cls");
}

// Untuk mengubah warna pada terminal
void changeColor(int angka){
  // 7 = Putih (default)
  // 10 = Hijau
  // 12 = Merah
  // 14 = Kuning
  // 15 = Putih Cerah (Warna yang digunakan didalam program)
  HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(color, angka);
}

// Untuk membuat loading
void loading(){
  cout<<""<<endl;
  char kalimat[] = "Sedang Diproses... ";
  for (int i=0; i<strlen(kalimat); i++){
    for (int satu=0; satu<88888; satu++){
      for (int dua=0; dua<888; dua++){
      }
    }
    cout<<kalimat[i];
  }
  cout<<""<<endl;
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

int getIndex()
{
	for (int i = 0; i < 999; i++)
	{
		if (pesananTerkonfirmasi[i].user == "")
		{
			return i;
		}
	}
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

// Untuk mengubah menjadi huruf kapital setiap kata
string ubahHurufKapitalPerKata(string text)
{
	for (int i = 0; i < text.length(); i++)
	{
		if (i == 0)
		{
			text[i] = toupper(text[i]);
		}
		else if (text[i - 1] == ' ')
		{
			text[i] = toupper(text[i]);
		}
		else
		{
			text[i] = tolower(text[i]);
		}
	}
	return text;
}

// Untuk mendapatkan jumlah data didalam suatu atribut setiap struct
int panjangData(string jenis, string data)
{
	int panjang = 0;
	if (jenis == "user")
	{
		NodeUser *head = HEAD_USER;
		while (head != NULL)
		{
			int nama_lengkap, password, email, no_hp, alamat;
			if (head->data.nama_lengkap.length() > panjang)
			{
				nama_lengkap = head->data.nama_lengkap.length();
			}
			if (head->data.password.length() > panjang)
			{
				password = head->data.password.length();
			}
			if (head->data.email.length() > panjang)
			{
				email = head->data.email.length();
			}
			if (head->data.no_hp.length() > panjang)
			{
				no_hp = head->data.no_hp.length();
			}
			if (head->data.alamat.length() > panjang)
			{
				alamat = head->data.alamat.length();
			}
			if (data == "nama_lengkap")
			{
				panjang = nama_lengkap;
			}
			if (data == "password")
			{
				panjang = password;
			}
			if (data == "email")
			{
				panjang = email;
			}
			if (data == "no_hp")
			{
				panjang = no_hp;
			}
			if (data == "alamat")
			{
				panjang = alamat;
			}
			head = head->next;
		}
	}

	if (jenis == "pesanan")
	{
		NodePesanan *head = HEAD_PESANAN;
		while (head != NULL)
		{
			int user, jumlahTiket, maskapai, jadwalPenerbangan, status;
			if (head->data.user.length() > panjang)
			{
				user = head->data.user.length();
			}
			if (to_string(head->data.jumlahTiket).length() > panjang)
			{
				jumlahTiket = to_string(head->data.jumlahTiket).length();
			}
			if (head->data.maskapai.length() > panjang)
			{
				maskapai = head->data.maskapai.length();
			}
			if (head->data.jadwalPenerbangan.length() > panjang)
			{
				jadwalPenerbangan = head->data.jadwalPenerbangan.length();
			}
			if (head->data.status.length() > panjang)
			{
				status = head->data.status.length();
			}
			if (data == "user")
			{
				panjang = user;
			}
			if (data == "jumlahTiket")
			{
				panjang = jumlahTiket;
			}
			if (data == "maskapai")
			{
				panjang = maskapai;
			}
			if (data == "jadwalPenerbangan")
			{
				panjang = jadwalPenerbangan;
			}
			if (data == "status")
			{
				panjang = status;
			}
			head = head->next;
		}
	}

	if (jenis == "jadwal")
	{
		NodeJadwal *head = HEAD_JADWAL;
		while (head != NULL)
		{
			int maskapai, asal, tujuan, jadwalPenerbangan, kapasitas;
			if (head->data.maskapai.length() > panjang)
			{
				maskapai = head->data.maskapai.length();
			}
			if (head->data.asal.length() > panjang)
			{
				asal = head->data.asal.length();
			}
			if (head->data.tujuan.length() > panjang)
			{
				tujuan = head->data.tujuan.length();
			}
			if (head->data.jadwal.length() > panjang)
			{
				jadwalPenerbangan = head->data.jadwal.length();
			}
			if (to_string(head->data.kapasitas).length() > panjang)
			{
				kapasitas = to_string(head->data.kapasitas).length();
			}
			if (data == "maskapai")
			{
				panjang = maskapai;
			}
			if (data == "asal")
			{
				panjang = asal;
			}
			if (data == "tujuan")
			{
				panjang = tujuan;
			}
			if (data == "jadwalPenerbangan")
			{
				panjang = jadwalPenerbangan;
			}
			if (data == "kapasitas")
			{
				panjang = kapasitas;
			}
			head = head->next;
		}
	}
	// cout<<head->data.maskapai<<endl;
	// Untuk mengembalikan data terpanjang pada suatu atribut
	return panjang;
}

// Untuk membuat tabel setiap struct
void tabel(string jenis)
{
	if (jenis == "user")
	{
		NodeUser *head = HEAD_USER;
		if (head == NULL)
		{
			cout << "" << endl;
			cout << "Data User Kosong" << endl;
			return;
		}
		NodeUser *sementara = head;
		int pjgId = 0;
		int pjgNama = panjangData("user", "nama_lengkap");
		int pjgPassword = panjangData("user", "password");
		int pjgEmail = panjangData("user", "email");
		int pjgNoHp = panjangData("user", "no_hp");
		int pjgAlamat = panjangData("user", "alamat");
		if (pjgId < 2)
		{
			pjgId = 2;
		}
		if (pjgNama < 16)
		{
			pjgNama = 16;
		}
		if (pjgPassword < 16)
		{
			pjgPassword = 16;
		}
		if (pjgEmail < 16)
		{
			pjgEmail = 16;
		}
		if (pjgNoHp < 16)
		{
			pjgNoHp = 16;
		}
		if (pjgAlamat < 16)
		{
			pjgAlamat = 16;
		}
		int pjgBaris = pjgId + pjgNama + pjgPassword + pjgEmail + pjgNoHp + pjgAlamat + 19;
		string baris(pjgBaris, '=');
		if (pjgBaris % 2 == 0)
		{
			string satuPerDuaBaris((pjgBaris / 2) - 6, '=');
			cout << " " << endl;
			cout << baris << endl;
			cout << left << satuPerDuaBaris << " ";
			cout << left << setw(9) << "DATA USER =";
			cout << left << satuPerDuaBaris << endl;
			cout << baris << endl;
			cout << "| " << left << setw(pjgId) << "No"
					 << " ";
			cout << "| " << left << setw(pjgNama) << "Nama Lengkap"
					 << " ";
			cout << "| " << left << setw(pjgPassword) << "Password"
					 << " ";
			cout << "| " << left << setw(pjgEmail) << "Email"
					 << " ";
			cout << "| " << left << setw(pjgNoHp) << "No Hp"
					 << " ";
			cout << "| " << left << setw(pjgAlamat) << "Alamat"
					 << " |" << endl;
			cout << baris << endl;
		}
		else
		{
			string satuPerDuaBaris((pjgBaris / 2) - 5, '=');
			cout << " " << endl;
			cout << baris << endl;
			cout << left << satuPerDuaBaris << " ";
			cout << left << setw(9) << "DATA USER ";
			cout << left << satuPerDuaBaris << endl;
			cout << baris << endl;
			cout << "| " << left << setw(pjgId) << "No"
					 << " ";
			cout << "| " << left << setw(pjgNama) << "Nama Lengkap"
					 << " ";
			cout << "| " << left << setw(pjgPassword) << "Password"
					 << " ";
			cout << "| " << left << setw(pjgEmail) << "Email"
					 << " ";
			cout << "| " << left << setw(pjgNoHp) << "No Hp"
					 << " ";
			cout << "| " << left << setw(pjgAlamat) << "Alamat"
					 << " |" << endl;
			cout << baris << endl;
		}

		int nomor = 1;
		while (sementara != NULL)
		{
			cout << "| " << left << setw(pjgId) << nomor << " ";
			cout << "| " << left << setw(pjgNama) << sementara->data.nama_lengkap << " ";
			cout << "| " << left << setw(pjgPassword) << sementara->data.password << " ";
			cout << "| " << left << setw(pjgEmail) << sementara->data.email << " ";
			cout << "| " << left << setw(pjgNoHp) << sementara->data.no_hp << " ";
			cout << "| " << left << setw(pjgAlamat) << sementara->data.alamat << " |" << endl;
			cout << baris << endl;
			nomor++;
			sementara = sementara->next;
		}
	}

	if (jenis == "jadwal")
	{
		quickSort(HEAD_JADWAL);
		NodeJadwal *head = HEAD_JADWAL;
		if (head == NULL)
		{
			cout << "" << endl;
			cout << "Data Jadwal Kosong" << endl;
			return;
		}

		NodeJadwal *sementara = head;
		int pjgId = 0;
		int pjgMaskapai = panjangData("jadwal", "maskapai");
		int pjgAsal = panjangData("jadwal", "asal");
		int pjgTujuan = panjangData("jadwal", "tujuan");
		int pjgJadwal = panjangData("jadwal", "jadwalPenerbangan");
		int pjgKapasitas = panjangData("jadwal", "kapasitas");
		if (pjgId < 2)
		{
			pjgId = 2;
		}
		if (pjgMaskapai < 16)
		{
			pjgMaskapai = 16;
		}
		if (pjgAsal < 12)
		{
			pjgAsal = 12;
		}
		if (pjgTujuan < 12)
		{
			pjgTujuan = 12;
		}
		if (pjgJadwal < 10)
		{
			pjgJadwal = 10;
		}
		if (pjgKapasitas < 9)
		{
			pjgKapasitas = 9;
		}
		int pjgBaris = pjgId + pjgMaskapai + pjgAsal + pjgTujuan + pjgJadwal + pjgKapasitas + 19;
		string baris(pjgBaris, '=');
		if (pjgBaris % 2 == 0)
		{
			string satuPerDuaBaris((pjgBaris / 2) - 10, '=');
			cout << " " << endl;
			cout << baris << endl;
			cout << left << satuPerDuaBaris << " ";
			cout << left << setw(9) << "JADWAL PENERBANGAN ";
			cout << left << satuPerDuaBaris << endl;
			cout << baris << endl;
			cout << "| " << left << setw(pjgId) << "No"
					 << " ";
			cout << "| " << left << setw(pjgMaskapai) << "Maskapai"
					 << " ";
			cout << "| " << left << setw(pjgAsal) << "Asal"
					 << " ";
			cout << "| " << left << setw(pjgTujuan) << "Tujuan"
					 << " ";
			cout << "| " << left << setw(pjgJadwal) << "Jadwal"
					 << " ";
			cout << "| " << left << setw(pjgKapasitas) << "Kapasitas"
					 << " |" << endl;
			cout << baris << endl;
		}
		else
		{
			string satuPerDuaBaris((pjgBaris / 2) - 10, '=');
			cout << " " << endl;
			cout << baris << endl;
			cout << left << satuPerDuaBaris << " ";
			cout << left << setw(9) << "JADWAL PENERBANGAN =";
			cout << left << satuPerDuaBaris << endl;
			cout << baris << endl;
			cout << "| " << left << setw(pjgId) << "No"
					 << " ";
			cout << "| " << left << setw(pjgMaskapai) << "Maskapai"
					 << " ";
			cout << "| " << left << setw(pjgAsal) << "Asal"
					 << " ";
			cout << "| " << left << setw(pjgTujuan) << "Tujuan"
					 << " ";
			cout << "| " << left << setw(pjgJadwal) << "Jadwal"
					 << " ";
			cout << "| " << left << setw(pjgKapasitas) << "Kapasitas"
					 << " |" << endl;
			cout << baris << endl;
		}

		int nomor = 1;
		while (sementara != NULL)
		{
			cout << "| " << left << setw(pjgId) << nomor << " ";
			cout << "| " << left << setw(pjgMaskapai) << sementara->data.maskapai << " ";
			cout << "| " << left << setw(pjgAsal) << sementara->data.asal << " ";
			cout << "| " << left << setw(pjgTujuan) << sementara->data.tujuan << " ";
			cout << "| " << left << setw(pjgJadwal) << sementara->data.jadwal << " ";
			cout << "| " << left << setw(pjgKapasitas) << sementara->data.kapasitas << " |" << endl;
			cout << baris << endl;
			nomor++;
			sementara = sementara->next;
		}
	}

	if (jenis == "pesanan")
	{
		NodePesanan *head = HEAD_PESANAN;
		if (head == NULL)
		{
			cout << "" << endl;
			cout << "Data Pemesanan Kosong" << endl;
			return;
		}

		NodePesanan *sementara = head;
		int pjgId = 0;
		int pjgUser = panjangData("pesanan", "user");
		int pjgTiket = panjangData("pesanan", "jumlahTiket");
		int pjgMaskapai = panjangData("pesanan", "maskapai");
		int pjgJadwal = panjangData("pesanan", "jadwalPenerbangan");
		int pjgStatus = panjangData("pesanan", "status");
		if (pjgId < 2)
		{
			pjgId = 2;
		}
		if (pjgUser < 16)
		{
			pjgUser = 16;
		}
		if (pjgTiket < 5)
		{
			pjgTiket = 5;
		}
		if (pjgMaskapai < 12)
		{
			pjgMaskapai = 12;
		}
		if (pjgJadwal < 10)
		{
			pjgJadwal = 10;
		}
		if (pjgStatus < 8)
		{
			pjgStatus = 8;
		}
		int pjgBaris = pjgId + pjgUser + pjgTiket + pjgMaskapai + pjgJadwal + pjgStatus + 19;
		string baris(pjgBaris, '=');
		if (pjgBaris % 2 == 0)
		{
			string satuPerDuaBaris((pjgBaris / 2) - 11, '=');
			cout << " " << endl;
			cout << baris << endl;
			cout << left << satuPerDuaBaris << " ";
			cout << left << setw(9) << "INFORMASI PEMESANAN =";
			cout << left << satuPerDuaBaris << endl;
			cout << baris << endl;
			cout << "| " << left << setw(pjgId) << "No"
					 << " ";
			cout << "| " << left << setw(pjgUser) << "Nama Lengkap"
					 << " ";
			cout << "| " << left << setw(pjgTiket) << "Tiket"
					 << " ";
			cout << "| " << left << setw(pjgMaskapai) << "Maskapai"
					 << " ";
			cout << "| " << left << setw(pjgJadwal) << "Jadwal"
					 << " ";
			cout << "| " << left << setw(pjgStatus) << "Status"
					 << " |" << endl;
			cout << baris << endl;
		}
		else
		{
			string satuPerDuaBaris((pjgBaris / 2) - 10, '=');
			cout << " " << endl;
			cout << baris << endl;
			cout << left << satuPerDuaBaris << " ";
			cout << left << setw(9) << "INFORMASI PEMESANAN ";
			cout << left << satuPerDuaBaris << endl;
			cout << baris << endl;
			cout << "| " << left << setw(pjgId) << "No"
					 << " ";
			cout << "| " << left << setw(pjgUser) << "Nama Lengkap"
					 << " ";
			cout << "| " << left << setw(pjgTiket) << "Tiket"
					 << " ";
			cout << "| " << left << setw(pjgMaskapai) << "Maskapai"
					 << " ";
			cout << "| " << left << setw(pjgJadwal) << "Jadwal"
					 << " ";
			cout << "| " << left << setw(pjgStatus) << "Status"
					 << " |" << endl;
			cout << baris << endl;
		}

		int nomor = 1;
		while (sementara != NULL)
		{
			cout << "| " << left << setw(pjgId) << nomor << " ";
			cout << "| " << left << setw(pjgUser) << sementara->data.user << " ";
			cout << "| " << left << setw(pjgTiket) << sementara->data.jumlahTiket << " ";
			cout << "| " << left << setw(pjgMaskapai) << sementara->data.maskapai << " ";
			cout << "| " << left << setw(pjgJadwal) << sementara->data.jadwalPenerbangan << " ";
			cout << "| ";
			changeColor(14);
			cout << "| " << left << setw(pjgStatus) << sementara->data.status;
			changeColor(15);
			cout << " |" << endl;
			cout << baris << endl;
			nomor++;
			sementara = sementara->next;
		}
	}
}

// Registrasi Start
NodeUser *newUser()
{
	NodeUser *newUser = new NodeUser;
	string nama_lengkap, password, konfirmasi, email, no_hp, alamat;
	bool ulangi = true;
	while (ulangi)
	{
		cout << "" << endl;
		cout << "REGISTRASI USER" << endl;
		cout << "" << endl;
		cout << "Nama Lengkap        >> ";
		getline(cin, nama_lengkap);
		cout << "Password            >> ";
		getline(cin, password);
		cout << "Konfirmasi Password >> ";
		getline(cin, konfirmasi);
		if (konfirmasi != password)
		{
			cout << "" << endl;
			cout << "Konfirmasi Password Anda Tidak Sesuai" << endl;
			cout << "" << endl;
			cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			menuAwal();
			continue;
		}
		cout << "Email               >> ";
		getline(cin, email);
		cout << "No HP               >> ";
		getline(cin, no_hp);
		cout << "Alamat              >> ";
		getline(cin, alamat);
		newUser->data.nama_lengkap = nama_lengkap;
		newUser->data.password = password;
		newUser->data.email = email;
		newUser->data.no_hp = no_hp;
		newUser->data.alamat = alamat;
		return newUser;
	}
}

void registrasi(NodeUser **head, NodeUser **tail)
{
	NodeUser *node = newUser();
	NodeUser *sementara = *head;
	if (node->data.email.find('@') == -1)
	{
		cout << "" << endl;
		changeColor(12);
		cout << "Email Anda Tidak Benar (Memerlukan Simbol @)" << endl;
		changeColor(15);
		cout << "" << endl;
		cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
		getchar();
		return;
	}

	while (sementara != NULL)
	{
		if (sementara->data.email == node->data.email)
		{
			cout << "" << endl;
			changeColor(12);
			cout << "Email Telah Digunakan" << endl;
			changeColor(15);
			cout << "" << endl;
			cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			return;
		}
		sementara = sementara->next;
	}

	if (isNumber(node->data.no_hp) == false)
	{
		cout << "" << endl;
		changeColor(12);
		cout << "No HP Anda Tidak Benar (Harus Angka 0-9)" << endl;
		changeColor(15);
		cout << "" << endl;
		cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
		getchar();
		return;
	}
	if (node->data.no_hp.find('-') != -1)
	{
		cout << "" << endl;
		changeColor(12);
		cout << "No HP Anda Tidak Benar (Tidak Boleh Negatif)" << endl;
		changeColor(15);
		cout << "" << endl;
		cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
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

	loading();
	clearScreen();
	cout << "" << endl;
	changeColor(10);
	cout << "Registrasi Berhasil" << endl;
	changeColor(15);
	cout << "" << endl;
	cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
	getchar();
}
// Registrasi End

// Login Start
void login(NodeUser *head)
{
	bool ulangi = true;
	string email, password;
	while (ulangi)
	{
		cout << "" << endl;
		cout << "LOGIN USER" << endl;
		cout << "Email    >> ";
		getline(cin, email);
		cout << "Password >> ";
		getline(cin, password);
		loading();

		clearScreen();
		while (head != NULL)
		{
			if (head->data.email == email && head->data.password == password)
			{
				cout << "" << endl;
				changeColor(10);
				cout << "Login Berhasil" << endl;
				changeColor(15);
				cout << "" << endl;
				cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
				getchar();
				// Untuk menambah data user didalam dictionary userAktif
				userAktif.insert({"user aktif", head->data.nama_lengkap});
				menuUser();
			}
			head = head->next;
		}
		cout << "" << endl;
		changeColor(12);
		cout << "Login Gagal" << endl;
		changeColor(15);
		cout << "" << endl;
		cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
		getchar();
		menuAwal();
	}
}
// Login End

// Menu Awal Start
void menuAwal()
{
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
			cout << "Username >> ";
			getline(cin, username);
			cout << "Password >> ";
			getline(cin, password);
			loading();

			clearScreen();
			if (username == "admin" && password == "admin")
			{
				cout << "" << endl;
				changeColor(10);
				cout << "Login Berhasil" << endl;
				changeColor(15);
				cout << "" << endl;
				cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
				getchar();
				menuAdmin();
			}
			else
			{
				cout << "" << endl;
				changeColor(12);
				cout << "Login Gagal" << endl;
				changeColor(15);
				cout << "" << endl;
				cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
				getchar();
				menuAwal();
			}
		}
		else if (pilihan == "4")
		{
			ulangi = false;
			loading();
			clearScreen();
			cout << "" << endl;
			cout << "Silahkan Tekan Enter Untuk Keluar...";
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
	loading();

	if (pilihan == "1")
	{
		lihatJadwal();
		loading();
		menuUser();
	}
	else if (pilihan == "2")
	{
		mencariJadwal();
		loading();
		menuUser();
	}
	else if (pilihan == "3")
	{
		daftarPesananUser();
		loading();
		menuUser();
	}
	else if (pilihan == "4")
	{
		pemesanan(&HEAD_PESANAN, &TAIL_PESANAN);
		loading();
		menuUser();
	}
	else if (pilihan == "0")
	{
		cout << "" << endl;
		cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
		getchar();
		// Untuk menghapus data user didalam dictionary userAktif
		userAktif.clear();
		loading();
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
void lihatJadwal()
{
	clearScreen();
	tabel("jadwal");
	cout << "" << endl;
	cout << "Silahkan Tekan Enter Untuk Kembali...";
	getchar();
}
// Lihat Jadwal Admin dan User End

void tampilkanHasilSearching(int index)
{
	NodeJadwal *panjangData = HEAD_JADWAL;
	int pjgId = 0,
			pjgMaskapai = 0,
			pjgAsal = 0,
			pjgTujuan = 0,
			pjgJadwal = 0,
			pjgKapasitas = 0;
	while (panjangData != NULL)
	{
		if (panjangData->data.maskapai.length() > pjgMaskapai)
		{
			pjgMaskapai = panjangData->data.maskapai.length();
		}
		if (panjangData->data.asal.length() > pjgAsal)
		{
			pjgAsal = panjangData->data.asal.length();
		}
		if (panjangData->data.tujuan.length() > pjgTujuan)
		{
			pjgTujuan = panjangData->data.tujuan.length();
		}
		if (panjangData->data.jadwal.length() > pjgJadwal)
		{
			pjgJadwal = panjangData->data.jadwal.length();
		}
		if (to_string(panjangData->data.kapasitas).length() > pjgKapasitas)
		{
			pjgKapasitas = to_string(panjangData->data.kapasitas).length();
		}
		panjangData = panjangData->next;
	}
	NodeJadwal *head = HEAD_JADWAL;
	NodeJadwal *sementara = head;
	if (pjgId < 2)
	{
		pjgId = 2;
	}
	if (pjgMaskapai < 16)
	{
		pjgMaskapai = 16;
	}
	if (pjgAsal < 12)
	{
		pjgAsal = 12;
	}
	if (pjgTujuan < 12)
	{
		pjgTujuan = 12;
	}
	if (pjgJadwal < 10)
	{
		pjgJadwal = 10;
	}
	if (pjgKapasitas < 9)
	{
		pjgKapasitas = 9;
	}
	int pjgBaris = pjgId + pjgMaskapai + pjgAsal + pjgTujuan + pjgJadwal + pjgKapasitas + 19;
	string baris(pjgBaris, '=');
	if (pjgBaris % 2 == 0)
	{
		string satuPerDuaBaris((pjgBaris / 2) - 10, '=');
		cout << " " << endl;
		cout << baris << endl;
		cout << left << satuPerDuaBaris << " ";
		cout << left << setw(9) << "JADWAL PENERBANGAN ";
		cout << left << satuPerDuaBaris << endl;
		cout << baris << endl;
		cout << "| " << left << setw(pjgId) << "No"
				 << " ";
		cout << "| " << left << setw(pjgMaskapai) << "Maskapai"
				 << " ";
		cout << "| " << left << setw(pjgAsal) << "Asal"
				 << " ";
		cout << "| " << left << setw(pjgTujuan) << "Tujuan"
				 << " ";
		cout << "| " << left << setw(pjgJadwal) << "Jadwal"
				 << " ";
		cout << "| " << left << setw(pjgKapasitas) << "Kapasitas"
				 << " |" << endl;
		cout << baris << endl;
	}
	else
	{
		string satuPerDuaBaris((pjgBaris / 2) - 10, '=');
		cout << " " << endl;
		cout << baris << endl;
		cout << left << satuPerDuaBaris << " ";
		cout << left << setw(9) << "JADWAL PENERBANGAN =";
		cout << left << satuPerDuaBaris << endl;
		cout << baris << endl;
		cout << "| " << left << setw(pjgId) << "No"
				 << " ";
		cout << "| " << left << setw(pjgMaskapai) << "Maskapai"
				 << " ";
		cout << "| " << left << setw(pjgAsal) << "Asal"
				 << " ";
		cout << "| " << left << setw(pjgTujuan) << "Tujuan"
				 << " ";
		cout << "| " << left << setw(pjgJadwal) << "Jadwal"
				 << " ";
		cout << "| " << left << setw(pjgKapasitas) << "Kapasitas"
				 << " |" << endl;
		cout << baris << endl;
	}

	int nomor = 1;
	for (int i = 0; i < index; i++)
	{
		sementara = sementara->next;
	}
	cout << "| " << left << setw(pjgId) << nomor << " ";
	cout << "| " << left << setw(pjgMaskapai) << sementara->data.maskapai << " ";
	cout << "| " << left << setw(pjgAsal) << sementara->data.asal << " ";
	cout << "| " << left << setw(pjgTujuan) << sementara->data.tujuan << " ";
	cout << "| " << left << setw(pjgJadwal) << sementara->data.jadwal << " ";
	cout << "| " << left << setw(pjgKapasitas) << sementara->data.kapasitas << " |" << endl;
	cout << baris << endl;
}

// Daftar Pesanan User Start
void daftarPesananUser()
{
	clearScreen();
	NodePesanan *panjangData = HEAD_PESANAN;
	int pjgId = 0,
			pjgUser = 0,
			pjgTiket = 0,
			pjgMaskapai = 0,
			pjgJadwal = 0,
			pjgStatus = 0;
	while (panjangData != NULL)
	{
		if (panjangData->data.user.length() > pjgUser)
		{
			pjgUser = panjangData->data.user.length();
		}
		if (to_string(panjangData->data.jumlahTiket).length() > pjgTiket)
		{
			pjgTiket = to_string(panjangData->data.jumlahTiket).length();
		}
		if (panjangData->data.maskapai.length() > pjgMaskapai)
		{
			pjgMaskapai = panjangData->data.maskapai.length();
		}
		if (panjangData->data.jadwalPenerbangan.length() > pjgJadwal)
		{
			pjgJadwal = panjangData->data.jadwalPenerbangan.length();
		}
		if (panjangData->data.status.length() > pjgStatus)
		{
			pjgStatus = panjangData->data.status.length();
		}
		panjangData = panjangData->next;
	}
	NodePesanan *head = HEAD_PESANAN;
	NodePesanan *sementara = head;
	if (head == NULL && pesananTerkonfirmasi[0].user == "")
	{
		cout << "" << endl;
		cout << "Data Pemesanan Kosong" << endl;
		cout << "" << endl;
		cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
		getchar();
		menuUser();
		return;
	}
	if (pjgId < 2)
	{
		pjgId = 2;
	}
	if (pjgUser < 16)
	{
		pjgUser = 16;
	}
	if (pjgTiket < 5)
	{
		pjgTiket = 5;
	}
	if (pjgMaskapai < 12)
	{
		pjgMaskapai = 12;
	}
	if (pjgJadwal < 10)
	{
		pjgJadwal = 10;
	}
	if (pjgStatus < 8)
	{
		pjgStatus = 8;
	}
	int pjgBaris = pjgId + pjgUser + pjgTiket + pjgMaskapai + pjgJadwal + pjgStatus + 19;
	string baris(pjgBaris, '=');
	if (pjgBaris % 2 == 0)
	{
		string satuPerDuaBaris((pjgBaris / 2) - 11, '=');
		cout << " " << endl;
		cout << baris << endl;
		cout << left << satuPerDuaBaris << " ";
		cout << left << setw(9) << "INFORMASI PEMESANAN =";
		cout << left << satuPerDuaBaris << endl;
		cout << baris << endl;
		cout << "| " << left << setw(pjgId) << "No"
				 << " ";
		cout << "| " << left << setw(pjgUser) << "Nama Lengkap"
				 << " ";
		cout << "| " << left << setw(pjgTiket) << "Tiket"
				 << " ";
		cout << "| " << left << setw(pjgMaskapai) << "Maskapai"
				 << " ";
		cout << "| " << left << setw(pjgJadwal) << "Jadwal"
				 << " ";
		cout << "| " << left << setw(pjgStatus) << "Status"
				 << " |" << endl;
		cout << baris << endl;
	}
	else
	{
		string satuPerDuaBaris((pjgBaris / 2) - 10, '=');
		cout << " " << endl;
		cout << baris << endl;
		cout << left << satuPerDuaBaris << " ";
		cout << left << setw(9) << "INFORMASI PEMESANAN ";
		cout << left << satuPerDuaBaris << endl;
		cout << baris << endl;
		cout << "| " << left << setw(pjgId) << "No"
				 << " ";
		cout << "| " << left << setw(pjgUser) << "Nama Lengkap"
				 << " ";
		cout << "| " << left << setw(pjgTiket) << "Tiket"
				 << " ";
		cout << "| " << left << setw(pjgMaskapai) << "Maskapai"
				 << " ";
		cout << "| " << left << setw(pjgJadwal) << "Jadwal"
				 << " ";
		cout << "| " << left << setw(pjgStatus) << "Status"
				 << " |" << endl;
		cout << baris << endl;
	}

	string namaUser = userAktif["user aktif"];
	int index = 0;
	while (pesananTerkonfirmasi[index].user != "")
	{
		if (pesananTerkonfirmasi[index].status == "Berhasil"){
			cout << "| " << left << setw(pjgId) << index + 1 << " ";
			cout << "| " << left << setw(pjgUser) << pesananTerkonfirmasi[index].user << " ";
			cout << "| " << left << setw(pjgTiket) << pesananTerkonfirmasi[index].jumlahTiket << " ";
			cout << "| " << left << setw(pjgMaskapai) << pesananTerkonfirmasi[index].maskapai << " ";
			cout << "| " << left << setw(pjgJadwal) << pesananTerkonfirmasi[index].jadwalPenerbangan << " ";
			cout << "| ";
			changeColor(10);
			cout << left << setw(pjgStatus) << pesananTerkonfirmasi[index].status;
			changeColor(15);
			cout << " |" << endl;
			cout << baris << endl;
			index++;
		}
		if (pesananTerkonfirmasi[index].status == "Gagal"){
			cout << "| " << left << setw(pjgId) << index + 1 << " ";
			cout << "| " << left << setw(pjgUser) << pesananTerkonfirmasi[index].user << " ";
			cout << "| " << left << setw(pjgTiket) << pesananTerkonfirmasi[index].jumlahTiket << " ";
			cout << "| " << left << setw(pjgMaskapai) << pesananTerkonfirmasi[index].maskapai << " ";
			cout << "| " << left << setw(pjgJadwal) << pesananTerkonfirmasi[index].jadwalPenerbangan << " ";
			cout << "| ";
			changeColor(12);
			cout << left << setw(pjgStatus) << pesananTerkonfirmasi[index].status;
			changeColor(15);
			cout << " |" << endl;
			cout << baris << endl;
			index++;
		}
		if (pesananTerkonfirmasi[index].status == "Menunggu"){
			cout << "| " << left << setw(pjgId) << index + 1 << " ";
			cout << "| " << left << setw(pjgUser) << pesananTerkonfirmasi[index].user << " ";
			cout << "| " << left << setw(pjgTiket) << pesananTerkonfirmasi[index].jumlahTiket << " ";
			cout << "| " << left << setw(pjgMaskapai) << pesananTerkonfirmasi[index].maskapai << " ";
			cout << "| " << left << setw(pjgJadwal) << pesananTerkonfirmasi[index].jadwalPenerbangan << " ";
			cout << "| ";
			changeColor(14);
			cout << left << setw(pjgStatus) << pesananTerkonfirmasi[index].status;
			changeColor(15);
			cout << " |" << endl;
			cout << baris << endl;
			index++;
		}
	}
	while (sementara != NULL)
	{
		if (sementara->data.user == namaUser)
		{
			if (sementara->data.status == "Berhasil"){
				cout << "| " << left << setw(pjgId) << index + 1 << " ";
				cout << "| " << left << setw(pjgUser) << sementara->data.user << " ";
				cout << "| " << left << setw(pjgTiket) << sementara->data.jumlahTiket << " ";
				cout << "| " << left << setw(pjgMaskapai) << sementara->data.maskapai << " ";
				cout << "| " << left << setw(pjgJadwal) << sementara->data.jadwalPenerbangan << " ";
				cout << "| ";
				changeColor(10);
				cout << left << setw(pjgStatus) << sementara->data.status;
				changeColor(15);
				cout << " |" << endl;
				cout << baris << endl;
				index++;
			}
			if (sementara->data.status == "Gagal"){
				cout << "| " << left << setw(pjgId) << index + 1 << " ";
				cout << "| " << left << setw(pjgUser) << sementara->data.user << " ";
				cout << "| " << left << setw(pjgTiket) << sementara->data.jumlahTiket << " ";
				cout << "| " << left << setw(pjgMaskapai) << sementara->data.maskapai << " ";
				cout << "| " << left << setw(pjgJadwal) << sementara->data.jadwalPenerbangan << " ";
				cout << "| ";
				changeColor(12);
				cout << left << setw(pjgStatus) << sementara->data.status;
				changeColor(15);
				cout << " |" << endl;
				cout << baris << endl;
				index++;
			}
			if (sementara->data.status == "Menunggu"){
				cout << "| " << left << setw(pjgId) << index + 1 << " ";
				cout << "| " << left << setw(pjgUser) << sementara->data.user << " ";
				cout << "| " << left << setw(pjgTiket) << sementara->data.jumlahTiket << " ";
				cout << "| " << left << setw(pjgMaskapai) << sementara->data.maskapai << " ";
				cout << "| " << left << setw(pjgJadwal) << sementara->data.jadwalPenerbangan << " ";
				cout << "| ";
				changeColor(14);
				cout << left << setw(pjgStatus) << sementara->data.status;
				changeColor(15);
				cout << " |" << endl;
				cout << baris << endl;
				index++;
			}
		}
		sementara = sementara->next;
	}
	cout << "" << endl;
	cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
	getchar();
}
// Daftar Pesanan User End

// Pemesanan Tiket User Start
NodePesanan *newPesanan()
{
	clearScreen();
	NodePesanan *newPesanan = new NodePesanan;
	string target_jadwal, jumlahTiket;
	bool ulangi = true;
	while (ulangi)
	{
		tabel("jadwal");
		cout << "" << endl;
		cout << "PEMESANAN TIKET" << endl;
		cout << "" << endl;
		cout << "Silahkan Pilih ID Jadwal >> ";
		getline(cin, target_jadwal);
		if (isNumber(target_jadwal) == false)
		{
			cout << "" << endl;
			changeColor(12);
			cout << "ID Jadwal Salah (Harus Angka dan Tidak Boleh Negatif)" << endl;
			changeColor(15);
			cout << "" << endl;
			cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			clearScreen();
			continue;
		}
		if (target_jadwal > to_string(jumlahNode("jadwal")) || target_jadwal <= "0")
		{
			cout << "" << endl;
			changeColor(12);
			cout << "ID Jadwal Tidak Ada (ID Jadwal Harus Sesuai Tabel)" << endl;
			changeColor(15);
			cout << "" << endl;
			cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			clearScreen();
			continue;
		}
		cout << "Jumlah Tiket             >> ";
		getline(cin, jumlahTiket);
		if (isNumber(jumlahTiket) == false)
		{
			cout << "" << endl;
			changeColor(12);
			cout << "Jumlah Tiket Salah (Harus Angka dan Tidak Boleh Negatif)" << endl;
			changeColor(15);
			cout << "" << endl;
			cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
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
		for (int i = 1; i < id_jadwal; i++)
		{
			head = head->next;
		}
		newPesanan->data.maskapai = head->data.maskapai;
		newPesanan->data.jadwalPenerbangan = head->data.jadwal;
		newPesanan->data.status = "Menunggu";
		return newPesanan;
	}
}

void pemesanan(NodePesanan **head, NodePesanan **tail)
{
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
	changeColor(10);
	cout << "Pemesanan Berhasil" << endl;
	changeColor(15);
	cout << "" << endl;
	cout << "Tagihan Dikirim Melalui Email" << endl;
	cout << "" << endl;
	cout << "Silahkan Lakukan Pembayaran" << endl;
	cout << "" << endl;
	cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
	getchar();
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
	loading();

	if (pilihan == "1")
	{
		lihatUser();
		loading();
		menuAdmin();
	}
	else if (pilihan == "2")
	{
		konfirmasi();
		loading();
		menuAdmin();
	}
	else if (pilihan == "3")
	{
		pesananSelesai();
		loading();
		menuAdmin();
	}
	else if (pilihan == "4")
	{
		lihatJadwal();
		loading();
		menuAdmin();
	}
	else if (pilihan == "5")
	{
		tambahJadwal(&HEAD_JADWAL, &TAIL_JADWAL);
		loading();
		menuAdmin();
	}
	else if (pilihan == "6")
	{
		editJadwal(&HEAD_JADWAL, &TAIL_JADWAL);
		loading();
		menuAdmin();
	}
	else if (pilihan == "7")
	{
		hapusJadwal(&HEAD_JADWAL, &TAIL_JADWAL);
		loading();
		menuAdmin();
	}
	else if (pilihan == "8")
	{
		mencariJadwal();
		loading();
		menuAdmin();
	}
	else if (pilihan == "0")
	{
		cout << "" << endl;
		cout << "Silahkan Tekan Enter Untuk Kembali...";
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
	cout << "" << endl;
	cout << "Silahkan Tekan Enter Untuk Kembali...";
	getchar();
}
// Lihat User End

// Konfirmasi Pesanan Start
void hapusAwal(NodePesanan **head, NodePesanan **tail, string status)
{
	NodePesanan *del = *head;
	if ((*head)->next == NULL)
	{
		*head = NULL;
		*tail = NULL;
	}
	else
	{
		*head = (*head)->next;
		(*head)->prev = NULL;
	}

	int index = getIndex();
	pesananTerkonfirmasi[index].user = del->data.user;
	pesananTerkonfirmasi[index].jumlahTiket = del->data.jumlahTiket;
	pesananTerkonfirmasi[index].maskapai = del->data.maskapai;
	pesananTerkonfirmasi[index].jadwalPenerbangan = del->data.jadwalPenerbangan;
	pesananTerkonfirmasi[index].status = status;
	simpanData();
	delete del;
	cout << "" << endl;
	cout << "Konfirmasi Berhasil" << endl;
	cout << "" << endl;
	cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
	getchar();
}

void konfirmasi()
{
	clearScreen();
	tabel("pesanan");
	if (HEAD_PESANAN == NULL && TAIL_PESANAN == NULL)
	{
		cout << "" << endl;
		cout << "Silahkan Tekan Enter Untuk Melanjutkan..." << endl;
		getchar();
		menuAdmin();
		return;
	}
	cout << "" << endl;
	cout << "[1] Konfirmasi Data Pesanan Nomor 1" << endl;
	cout << "[2] Kembali" << endl;
	cout << "" << endl;
	string pilihan;
	cout << "Silahkan Pilih >> ";
	getline(cin, pilihan);

	if (pilihan == "1")
	{
		cout << "" << endl;
		cout << "Status Pembayaran" << endl;
		cout << "[1] Berhasil" << endl;
		cout << "[2] Gagal" << endl;
		cout << "[3] Kembali" << endl;
		string respon;
		cout << "" << endl;
		cout << "Silahkan Pilih >> ";
		getline(cin, respon);
		if (respon == "1")
		{
			hapusAwal(&HEAD_PESANAN, &TAIL_PESANAN, "Berhasil");
			loading();
			menuAdmin();
		}
		else if (respon == "2")
		{
			hapusAwal(&HEAD_PESANAN, &TAIL_PESANAN, "Gagal");
			loading();
			menuAdmin();
		}
		else if (pilihan == "3")
		{
			cout << "" << endl;
			cout << "Silahkan Tekan Enter Untuk Kembali...";
			getchar();
			konfirmasi();
		}
	}
	if (pilihan == "2")
	{
		cout << "" << endl;
		cout << "Silahkan Tekan Enter Untuk Kembali...";
		getchar();
	}
	else
	{
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
void pesananSelesai()
{
	ambilData();
	clearScreen();
	int pjgId = 0,
			pjgUser = 0,
			pjgTiket = 0,
			pjgMaskapai = 0,
			pjgJadwal = 0,
			pjgStatus = 0;

	if (pesananTerkonfirmasi[0].user == "")
	{
		cout << "" << endl;
		cout << "Tidak Ada Pesanan Terkonfirmasi" << endl;
		cout << "" << endl;
		cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
		getchar();
		menuAdmin();
		return;
	}

	for (int i = 0; i < 999; i++)
	{
		if (pesananTerkonfirmasi[i].user == "")
		{
			break;
		}
		if (pesananTerkonfirmasi[i].user.length() > pjgUser)
		{
			pjgUser = pesananTerkonfirmasi[i].user.length();
		}
		if (to_string(pesananTerkonfirmasi[i].jumlahTiket).length() > pjgTiket)
		{
			pjgTiket = to_string(pesananTerkonfirmasi[i].jumlahTiket).length();
		}
		if (pesananTerkonfirmasi[i].maskapai.length() > pjgMaskapai)
		{
			pjgMaskapai = pesananTerkonfirmasi[i].maskapai.length();
		}
		if (pesananTerkonfirmasi[i].jadwalPenerbangan.length() > pjgJadwal)
		{
			pjgJadwal = pesananTerkonfirmasi[i].jadwalPenerbangan.length();
		}
		if (pesananTerkonfirmasi[i].status.length() > pjgStatus)
		{
			pjgStatus = pesananTerkonfirmasi[i].status.length();
		}
	}
	if (pjgId < 2)
	{
		pjgId = 2;
	}
	if (pjgUser < 16)
	{
		pjgUser = 16;
	}
	if (pjgTiket < 5)
	{
		pjgTiket = 5;
	}
	if (pjgMaskapai < 12)
	{
		pjgMaskapai = 12;
	}
	if (pjgJadwal < 10)
	{
		pjgJadwal = 10;
	}
	if (pjgStatus < 8)
	{
		pjgStatus = 8;
	}
	int pjgBaris = pjgId + pjgUser + pjgTiket + pjgMaskapai + pjgJadwal + pjgStatus + 19;
	string baris(pjgBaris, '=');
	if (pjgBaris % 2 == 0)
	{
		string satuPerDuaBaris((pjgBaris / 2) - 12, '=');
		cout << " " << endl;
		cout << baris << endl;
		cout << left << satuPerDuaBaris << " ";
		cout << left << setw(9) << "PESANAN TERKONFIRMASI =";
		cout << left << satuPerDuaBaris << endl;
		cout << baris << endl;
		cout << "| " << left << setw(pjgId) << "No"
				 << " ";
		cout << "| " << left << setw(pjgUser) << "Nama Lengkap"
				 << " ";
		cout << "| " << left << setw(pjgTiket) << "Tiket"
				 << " ";
		cout << "| " << left << setw(pjgMaskapai) << "Maskapai"
				 << " ";
		cout << "| " << left << setw(pjgJadwal) << "Jadwal"
				 << " ";
		cout << "| " << left << setw(pjgStatus) << "Status"
				 << " |" << endl;
		cout << baris << endl;
	}
	else
	{
		string satuPerDuaBaris((pjgBaris / 2) - 11, '=');
		cout << " " << endl;
		cout << baris << endl;
		cout << left << satuPerDuaBaris << " ";
		cout << left << setw(9) << "PESANAN TERKONFIRMASI ";
		cout << left << satuPerDuaBaris << endl;
		cout << baris << endl;
		cout << "| " << left << setw(pjgId) << "No"
				 << " ";
		cout << "| " << left << setw(pjgUser) << "Nama Lengkap"
				 << " ";
		cout << "| " << left << setw(pjgTiket) << "Tiket"
				 << " ";
		cout << "| " << left << setw(pjgMaskapai) << "Maskapai"
				 << " ";
		cout << "| " << left << setw(pjgJadwal) << "Jadwal"
				 << " ";
		cout << "| " << left << setw(pjgStatus) << "Status"
				 << " |" << endl;
		cout << baris << endl;
	}
	for (int i = 0; i < 999; i++)
	{
		if (pesananTerkonfirmasi[i].user == "")
		{
			break;
		}
		if (pesananTerkonfirmasi[i].status == "Berhasil"){
			cout << "| " << left << setw(pjgId) << i + 1 << " ";
			cout << "| " << left << setw(pjgUser) << pesananTerkonfirmasi[i].user << " ";
			cout << "| " << left << setw(pjgTiket) << pesananTerkonfirmasi[i].jumlahTiket << " ";
			cout << "| " << left << setw(pjgMaskapai) << pesananTerkonfirmasi[i].maskapai << " ";
			cout << "| " << left << setw(pjgJadwal) << pesananTerkonfirmasi[i].jadwalPenerbangan << " ";
			cout << "| ";
			changeColor(10);
			cout << left << setw(pjgStatus) << pesananTerkonfirmasi[i].status;
			changeColor(15);
			cout << " |" << endl;
			cout << baris << endl;
		}
		if (pesananTerkonfirmasi[i].status == "Gagal"){
			cout << "| " << left << setw(pjgId) << i + 1 << " ";
			cout << "| " << left << setw(pjgUser) << pesananTerkonfirmasi[i].user << " ";
			cout << "| " << left << setw(pjgTiket) << pesananTerkonfirmasi[i].jumlahTiket << " ";
			cout << "| " << left << setw(pjgMaskapai) << pesananTerkonfirmasi[i].maskapai << " ";
			cout << "| " << left << setw(pjgJadwal) << pesananTerkonfirmasi[i].jadwalPenerbangan << " ";
			cout << "| ";
			changeColor(12);
			cout << left << setw(pjgStatus) << pesananTerkonfirmasi[i].status;
			changeColor(15);
			cout << " |" << endl;
			cout << baris << endl;
		}
	}
	cout << "" << endl;
	cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
	getchar();
}
// Pesanan Terkonfirmasi End

// Menambah Jadwal Start
NodeJadwal *newJadwal()
{
	NodeJadwal *NodeBaru = new NodeJadwal;
	bool loop = true;
	string tanggal, kapasitas;
	while (loop)
	{
		cout << "Nama Maskapai >> ";
		getline(cin, NodeBaru->data.maskapai);
		cout << "Asal Keberangkatan >> ";
		getline(cin, NodeBaru->data.asal);
		cout << "Tujuan Keberangkatan >> ";
		getline(cin, NodeBaru->data.tujuan);
		cout << "Jadwal Penerbangan >> ";
		getline(cin, tanggal);

		bool valid = true;
		if (tanggal[4] != '-' || tanggal[7] != '-' || tanggal.length() != 10)
		{
			cout << "" << endl;
			changeColor(12);
			cout << "Format Tanggal Salah (Wajib YYYY-MM-DD)" << endl;
			changeColor(15);
			cout << "" << endl;
			cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			clearScreen();
			continue;
		}
		for (int i = 0; i < tanggal.length(); i++)
		{
			if (i == 4 || i == 7)
			{
				continue;
			}
			if (isdigit(tanggal[i]) == 0)
			{
				valid = false;
				break;
			}
		}
		if (!valid)
		{
			cout << "" << endl;
			changeColor(12);
			cout << "Jadwal Penerbangan Salah (Harus Angka)" << endl;
			changeColor(15);
			cout << "" << endl;
			cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			continue;
		}
		cout << "Kapasitas Pesawat >> ";
		getline(cin, kapasitas);
		if (isNumber(kapasitas) == false)
		{
			cout << "" << endl;
			changeColor(12);
			cout << "Jumlah Kapasitas Salah (Harus Angka)" << endl;
			changeColor(15);
			cout << "" << endl;
			cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			clearScreen();
			continue;
		}
		if (kapasitas <= "0")
		{
			cout << "" << endl;
			changeColor(12);
			cout << "Jumlah Kapasitas Salah (Harus Lebih Dari 0)" << endl;
			changeColor(15);
			cout << "" << endl;
			cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
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

void tambahJadwal(NodeJadwal **head, NodeJadwal **tail)
{
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
	changeColor(10);
	cout << "Jadwal Berhasil Ditambah" << endl;
	changeColor(15);
	cout << "" << endl;
	cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
	getchar();
}
// Menambah Jadwal End

// Mengubah Jadwal Start
void editJadwal(NodeJadwal **head, NodeJadwal **tail)
{
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
	cout << "" << endl;
	cout << "Silahkan Pilih >> ";
	getline(cin, pilihan);

	if (pilihan > to_string(jumlahNode("jadwal")) || pilihan <= "0")
	{
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
	for (int i = 1; i < pilihanValid; i++)
	{
		temp = temp->next;
	}

	NodePesanan *cekJadwal = HEAD_PESANAN;
	while (cekJadwal != NULL)
	{
		if (cekJadwal->data.maskapai == temp->data.maskapai)
		{
			cout << "" << endl;
			changeColor(12);
			cout << "Jadwal Tidak Dapat Diedit" << endl;
			changeColor(15);
			cout << "" << endl;
			changeColor(14);
			cout << "Jadwal Sedang Ada Pada Pesanan" << endl;
			changeColor(15);
			cout << "" << endl;
			cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			return;
		}
		cekJadwal = cekJadwal->next;
	}

	bool loop = true;
	string tanggal, kapasitas;
	while (loop)
	{
		cout << "" << endl;
		cout << "Nama Maskapai >> ";
		getline(cin, temp->data.maskapai);
		cout << "Asal Keberangkatan >> ";
		getline(cin, temp->data.asal);
		cout << "Tujuan Keberangkatan >> ";
		getline(cin, temp->data.tujuan);
		cout << "Jadwal Penerbangan >> ";
		getline(cin, tanggal);

		bool valid = true;
		if (tanggal[4] != '-' || tanggal[7] != '-' || tanggal.length() != 10)
		{
			cout << "" << endl;
			cout << "Format Tanggal Salah (Wajib YYYY-MM--DD)" << endl;
			cout << "" << endl;
			cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			clearScreen();
			continue;
		}
		for (int i = 0; i < tanggal.length(); i++)
		{
			if (i == 4 || i == 7)
			{
				continue;
			}
			if (isdigit(tanggal[i]) == 0)
			{
				valid = false;
				break;
			}
		}
		if (!valid)
		{
			cout << "" << endl;
			changeColor(12);
			cout << "Jadwal Penerbangan Salah (Harus Angka)" << endl;
			changeColor(15);
			cout << "" << endl;
			cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			continue;
		}
		cout << "Kapasitas Pesawat >> ";
		getline(cin, kapasitas);
		if (isNumber(kapasitas) == false)
		{
			cout << "" << endl;
			changeColor(12);
			cout << "Jumlah Kapasitas Salah (Harus Angka)" << endl;
			changeColor(15);
			cout << "" << endl;
			cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			clearScreen();
			continue;
		}
		if (kapasitas <= "0")
		{
			cout << "" << endl;
			changeColor(12);
			cout << "Jumlah Kapasitas Salah (Harus Lebih Dari 0)" << endl;
			changeColor(15);
			cout << "" << endl;
			cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
			getchar();
			clearScreen();
			continue;
		}
		int kapasitasValid;
		stringstream swapKapasitas(kapasitas);
		swapKapasitas >> kapasitasValid;
		temp->data.jadwal = tanggal;
		temp->data.kapasitas = kapasitasValid;
		cout << "" << endl;
		changeColor(10);
		cout << "Jadwal Berhasil Diubah" << endl;
		changeColor(15);
		cout << "" << endl;
		cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
		getchar();
		return;
	}
}
// Mengubah Jadwal End

// Menghapus Jadwal Start
void hapusJadwal(NodeJadwal **head, NodeJadwal **tail)
{
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
	cout << "" << endl;
	cout << "Silahkan Pilih >> ";
	getline(cin, pilihan);

	if (pilihan > to_string(jumlahNode("jadwal")) || pilihan <= "0")
	{
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
			while (cekJadwal != NULL)
			{
				if (cekJadwal->data.maskapai == del->data.maskapai)
				{
					cout << "" << endl;
					changeColor(12);
					cout << "Jadwal Tidak Dapat Dihapus" << endl;
					changeColor(15);
					cout << "" << endl;
					changeColor(14);
					cout << "Jadwal Sedang Ada Pada Pesanan" << endl;
					changeColor(15);
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
			while (cekJadwal != NULL)
			{
				if (cekJadwal->data.maskapai == del->data.maskapai)
				{
					cout << "" << endl;
					changeColor(12);
					cout << "Jadwal Tidak Dapat Dihapus" << endl;
					changeColor(15);
					cout << "" << endl;
					changeColor(14);
					cout << "Jadwal Sedang Ada Pada Pesanan" << endl;
					changeColor(15);
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
	else if (pilihanValid == jumlahNode("jadwal"))
	{
		NodeJadwal *del = *tail;
		NodePesanan *cekJadwal = HEAD_PESANAN;
		while (cekJadwal != NULL)
		{
			if (cekJadwal->data.maskapai == del->data.maskapai)
			{
				cout << "" << endl;
				changeColor(12);
				cout << "Jadwal Tidak Dapat Dihapus" << endl;
				changeColor(15);
				cout << "" << endl;
				changeColor(14);
				cout << "Jadwal Sedang Ada Pada Pesanan" << endl;
				changeColor(15);
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
	}
	else
	{
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
		while (cekJadwal != NULL)
		{
			if (cekJadwal->data.maskapai == data->data.maskapai)
			{
				cout << "" << endl;
				changeColor(12);
				cout << "Jadwal Tidak Dapat Dihapus" << endl;
				changeColor(15);
				cout << "" << endl;
				changeColor(14);
				cout << "Jadwal Sedang Ada Pada Pesanan" << endl;
				changeColor(15);
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
	changeColor(10);
	cout << "Jadwal Berhasil Dihapus" << endl;
	changeColor(15);
	cout << "" << endl;
	cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
	getchar();
}
// Menghapus Jadwal End

// Mencari Jadwal Start
void mencariJadwal()
{
	clearScreen();
	MergeSortMaskapai(&HEAD_JADWAL);
	string cari;
	int panjangJadwal = panjangData("jadwal", "maskapai");
	cout << "Masukkan Nama Maskapai >> ";
	getline(cin, cari);
	cari = ubahHurufKapitalPerKata(cari);
	int index = fibonacciSearchMaskapai(HEAD_JADWAL, cari, panjangJadwal);
	cout<<index<<endl;
	getchar();
	if (index >= 0)
	{
		tampilkanHasilSearching(index);
	}
	else
	{
		cout << "Hasil Cari Nama Maskapai " << cari << " tidak ada dalam jadwal";
	}
	cout << "" << endl;
	cout << "Silahkan Tekan Enter Untuk Melanjutkan...";
	getchar();
}
// Mencari Jadwal End

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
	pesanan1.data.maskapai = "Garuda Indonesia";
	pesanan1.data.jadwalPenerbangan = "2022-09-10";
	pesanan1.data.status = "Menunggu";
	pesanan1.next = NULL;

	jadwal1.prev = NULL;
	jadwal1.data.maskapai = "Garuda Indonesia";
	jadwal1.data.asal = "Jakarta";
	jadwal1.data.tujuan = "Balikpapan";
	jadwal1.data.jadwal = "2022-09-10";
	jadwal1.data.kapasitas = 50;
	jadwal1.next = &jadwal2;

	jadwal2.prev = &jadwal1;
	jadwal2.data.maskapai = "Batik Air";
	jadwal2.data.asal = "Denpasar";
	jadwal2.data.tujuan = "Bengkulu";
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
	jadwal4.data.maskapai = "Citilink";
	jadwal4.data.asal = "Surabaya";
	jadwal4.data.tujuan = "Pontianak";
	jadwal4.data.jadwal = "2022-10-10";
	jadwal4.data.kapasitas = 40;
	jadwal4.next = NULL;

	ambilData();
	changeColor(15);
	// Menu Awal [DONE]
	// menuAwal();

	// Menu User [DONE]
	// menuUser();

	// Menu Admin [DONE]
	// menuAdmin();
	mencariJadwal();
	// menuAdmin();
	return 0;
}