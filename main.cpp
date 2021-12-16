#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const std::string currentDateTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

// ! INFO: Buat mapping bedType
string bedTypeStr[] = {"Single Bed", "Twin Bed", "Double Bed"};

struct Room {
	int id;
	int bedType;
	int price;
	int total;

	Room(){};

	Room(int id_, int bedType_, int price_) {
		id = id_;
		bedType = bedType_;
		price = price_;
	}
};

struct Costumer {
	string id;
	string name;
	string phoneNumber;
	int days;
	string checkIn;
	string checkOut;

	int roomId;

	Costumer(){};

	Costumer(int id_, string name_, string phoneNumber_, int days_) {
		id = id_;
		name = name_;
		phoneNumber = phoneNumber_;
		days = days_;
	}
};


// ! TODO: Implement hotelMainMenu()
void mainMenu(vector<Room> listKamar, vector<Costumer> listCostumer) {

}

// ! TODO: Implement kamarMenu()
void kamarMenu(vector<Room> listKamar) {

}

// ! TODO: Implement formCustomer()
void formCustomer(vector<Costumer> listCostumer) {

}

int main() {
	// ! TODO: Bikin data Room, bikin data yang lumayan banyak contoh nya dibawah
	vector<Room> listKamar{
		Room(1, 1, 200),
		Room(2, 1, 200),
		Room(3, 1, 200),
	};

  // ! INFO: Data costumer akan ditambah on the fly
	vector<Costumer> listCostumer;

	char resepsionis[30], customer[30], alamat[30], YT = 'Y';
	std::string hp, checkin, checkout, ruang;
	int kamar, bed, harga, lama, bayar, total;

	// Buat array kamar kosong (belum dibuat)

utama:

	system("cls");

	std::cout << "================" << std::endl;
	std::cout << "Reservasi Hotel " << std::endl;
	std::cout << "================" << std::endl << std::endl;

	// Resersionis Checkin
	std::cout << "Nama resepsionis :";
	std::cin >> resepsionis;
	std::cout << "Nama customer :";
	std::cin >> customer;
	std::cout << "No. Telp :";
	std::cin >> hp;
	std::cout << "Alamat :";
	std::cin >> alamat;
	std::cout << "Lama Menginap :";
	std::cin >> lama;
	std::cout << "Tanggal Check In :";
	std::cin >> checkin;
	std::cout << "Tanggal Check Out :";
	std::cin >> checkout;

menu:
	system("cls");

	// Searching Kamar Kosong

	// Pilih Kamar
	std::cout << "Pilih Kamar" << std::endl;
	std::cout << "1.Standard Room" << std::endl;
	std::cout << "2.Deluxe Room" << std::endl;
	std::cout << "3. Suite Room" << std::endl;
	std::cout << "4. Presidential Suite Room" << std::endl;
	std::cout << "Masukkan Pilihan = ";
	std::cin >> kamar;
	std::cout << std::endl;

	if (kamar == 4) {
		harga = 1000000;
		ruang = "Presidential Suite Room Beb";
		goto akhir;
	}

	// Pilih Kasur
	std::cout << "Pilih Kasur" << std::endl;
	std::cout << "1.Single Bed" << std::endl;
	std::cout << "2.Twin Bed" << std::endl;
	std::cout << "3. Double Bed" << std::endl;

	std::cout << "Masukkan Pilihan = ";
	std::cin >> bed;
	std::cout << std::endl;
	if (kamar == 1 && bed == 1) {
		harga = 300000;
		ruang = "Standard Room Dengan Twin Bed";

	} else if (kamar == 1 && bed == 2) {
		harga = 500000;
		ruang = "Standard Room Dengan Twin Bed";

	}

	else if (kamar == 1 && bed == 3) {
		harga = 500000;
		ruang = "Standart Room Dengan double Bed";
	}

	else if (kamar == 2 && bed == 1) {
		harga = 300000;
		ruang = "Deluxe Room Dengan Twin Bed";

	} else if (kamar == 2 && bed == 2) {
		harga = 500000;
		ruang = "Deluxe Room Dengan Twin Bed";

	}

	else if (kamar == 2 && bed == 3) {
		harga = 500000;
		ruang = "Deluxe Room Dengan double Bed";
	}

	else if (kamar == 3 && bed == 1) {
		harga = 300000;
		ruang = "Suite Room Dengan Twin Bed";

	} else if (kamar == 3 && bed == 2) {
		harga = 500000;
		ruang = "Suite Room Dengan Twin Bed";

	}

	else if (kamar == 3 && bed == 3) {
		harga = 500000;
		ruang = "Suite Room Dengan double Bed";
	} else {
		std::cout << "Inputan Salah" << std::endl;
		getch();

		goto menu;
	}

akhir:
	system("cls");

	// Hitung Bayar Total #kalo mau ada
	total = harga * lama;

	// Ini Hasil Akhir Guys
	std::cout << "Nama resepsionis :" << resepsionis << std::endl;
	std::cout << "Nama customer :" << customer << std::endl;
	std::cout << "No. Telp :" << hp << std::endl;
	std::cout << "Alamat :" << alamat << std::endl;
	std::cout << "Tipe Kamar :" << kamar << std::endl;
	std::cout << "Lama Menginap :" << lama << std::endl;
	std::cout << "Tanggal Check In :" << checkin << std::endl;
	std::cout << "Tanggal Check Out :" << checkout << std::endl;
	std::cout << "Total =" << total << std::endl;
}
