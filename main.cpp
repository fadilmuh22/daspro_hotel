#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<functional>
#include <cstdlib>

using namespace std;

const string roomFileTxt = "roomfile.txt";
const string customerFileTxt = "customerfile.txt";

// ! INFO: Buat mapping bedType
string bedTypeStr[] = {"Single Bed", "Twin Bed", "Double Bed"};
// ! INFO: Buat mapping roomType
string roomTypeStr[] = {"Standard Room", "Deluxe Room", "Suite Room", "Presidential Suite Room"};

struct Room {
	int id = -1;
    int roomType = -1;
	int bedType = -1;
	int price = -1;

    // 0=default, 1=booked, 2=filled 
    int status = 0;

	Room(){};

	Room(int id_, int bedType_, int roomType_, int price_) {
		id = id_;
		bedType = bedType_;
		roomType = roomType_;
		price = price_;
	}

    string toString() {
        return "ID Kamar\t: " + to_string(id) + "\n\tTipe Kamar\t: " + roomTypeStr[roomType] + "\n\tTipe Kasur\t: " + bedTypeStr[bedType] + "\n\tHarga\t\t: " + to_string(price);
    }
};

struct Customer {
	int id = -1;
	string name = "_";
	string phoneNumber = "_";
	int days = -1;
	string checkIn = "_";
	string checkOut = "_";
	int roomId = -1;

	Customer(){};

	Customer(int id_, string name_, string phoneNumber_, int days_) {
		id = id_;
		name = name_;
		phoneNumber = phoneNumber_;
		days = days_;
	}

    int total(int price) {
        return price * days;
    }

    string toString() {
        return "ID User\t\t\t: " + to_string(id) + "\n\tNama\t\t\t: " + name + "\n\tNomor Telpon\t: " + phoneNumber + "\n\tWaktu Check In\t: " + checkIn + "\n\tWaktu Check Out\t: " + checkOut + "\n\tID Kamar\t\t: " + to_string(roomId);
    }
};

vector<Room> readFileToRooms();
vector<Customer> readFileToCustomers();

void changeRoomBooked(vector<Room> * listRoom, vector<Customer> * listCustomer, int idCustomer, int roomId, bool status);
void changeRoomFilled(vector<Room> * listRoom, vector<Customer> * listCustomer, int idCustomer, bool status);

void roomMenu(vector<Room> * listRoom);
void mainMenu(vector<Room> * listRoom, vector<Customer> * listCustomer);

void clearscr() {
    #ifdef WINDOWS
        system("cls");
    #else
        system ("clear");
    #endif
}

void pausescr() {
    cin.ignore(256, '\n');
    string dummy;
    cout << "\n\nEnter to continue...";
    getline(cin, dummy);
}

// ! ALUR:
// 0. Tambah Login (Optional)
// 1. Muncul Menu Utama Aplikasi (Register Customer, Checkin, Checkout, Cari Kamar)
// 2. Setelah selesai di menu utama akan balik lagi ke menu utama
int main() {
	vector<Customer> listCustomer = readFileToCustomers();
    vector<Room> listRoom = readFileToRooms();

    mainMenu(&listRoom, &listCustomer);
}

bool isFileEmpty(fstream& pFile)
{
    return pFile.peek() == ifstream::traits_type::eof();
}

vector<Room> readFileToRooms() {
    vector<Room> lr;

    fstream roomFile(roomFileTxt, fstream::in | fstream::out);

    if (roomFile.fail()) {
        roomFile.open(roomFileTxt, fstream::in | fstream::out);
        // roomFile.seekp(0, fstream::beg);
    } else {
        if (!isFileEmpty(roomFile)) {
            while(!roomFile.eof()) {
                Room nr;
                roomFile >> nr.id; 
                roomFile >> nr.roomType; 
                roomFile >> nr.bedType; 
                roomFile >> nr.price; 
                roomFile >> nr.status;

                if (nr.id > -1) {
                    lr.push_back(nr); 
                }
            }
        }
    }

    roomFile.close();

    return lr;
}

void writeRoomsToFile(vector<Room> listRoom) {
    fstream roomFile(roomFileTxt, fstream::in | fstream::out | fstream:: trunc);
    
    // roomFile.seekg(0, fstream::beg);
    for (int i = 0; i < listRoom.size(); i++) {
        if (listRoom[i].id > -1) {
            roomFile << listRoom[i].id << " ";
            roomFile << listRoom[i].roomType << " ";
            roomFile << listRoom[i].bedType << " ";
            roomFile << listRoom[i].price << " ";
            roomFile << listRoom[i].status;
            roomFile << "\n";
        }
    }

    roomFile.close();
}

vector<Customer> readFileToCustomers() {
    vector<Customer> lc;

    fstream customerFile(customerFileTxt, fstream::in | fstream::out);

    if (customerFile.fail()) {
        customerFile.open(customerFileTxt, fstream::in | fstream::out);
    } else {
        if (!isFileEmpty(customerFile)) {
            // roomFile.seekp(0, fstream::beg);
            while(!customerFile.eof()) {
                Customer nc;
                customerFile >> nc.id; 
                customerFile >> nc.name; 
                customerFile >> nc.phoneNumber; 
                customerFile >> nc.days; 
                customerFile >> nc.checkIn;
                customerFile >> nc.checkOut;
                customerFile >> nc.roomId;

                if (nc.id > -1) {
                    lc.push_back(nc); 
                }
            }
        }
    }

    customerFile.close();

    return lc;
}

void writeCustomersToFile(vector<Customer> listCustomer) {
    fstream customerFile(customerFileTxt, fstream::in | fstream::out | fstream:: trunc);
    
    // customerFile.seekg(0, fstream::beg);
    for (int i = 0; i < listCustomer.size(); i++) {
        if (listCustomer[i].id > -1) {
            customerFile << listCustomer[i].id << " "; 
            customerFile << listCustomer[i].name << " "; 
            customerFile << listCustomer[i].phoneNumber << " "; 
            customerFile << listCustomer[i].days << " "; 
            customerFile << listCustomer[i].checkIn << " ";
            customerFile << listCustomer[i].checkOut << " ";
            customerFile << listCustomer[i].roomId;
            customerFile << "\n";
        }
    }

    customerFile.close();
}

const string currentDateTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}


// ! TODO: Implement printArray()
template <typename T>
void printArray(vector<T> list) {
    for (int i = 0; i < list.size(); i++) {
        cout << i << ".\t" << list[i].toString() << "\n\n";
    }
}

// ! TODO: Implement registerCustomer()
Customer * registerCustomer(vector<Room> * listRoom, vector<Customer> *listCustomer) {
    Customer newCustomer;
    cout << "\nMasukan nama\t\t: ";cin >> newCustomer.name; 
    cout << "Masukan nomor telpon: ";cin >> newCustomer.phoneNumber; 
    cout << "Berapa lama\t\t\t: ";cin >> newCustomer.days;
    newCustomer.id = time(NULL);
    
    cout << endl;

    (*listCustomer).push_back(newCustomer);

    roomMenu(listRoom);

    int roomId = -1;
    cout << "\nPilih ID Kamar\t: "; cin >> roomId;
    if (roomId != -1) {
        changeRoomBooked(listRoom, listCustomer,(*listCustomer)[(*listCustomer).size()-1].id, roomId, true);

        cout << "\n\nPesan kamar selesai\n";
        pausescr();
    }


    return &(*listCustomer)[(*listCustomer).size()-1];
}

int findCustomerIndex(vector<Customer> listCustomer, int idCustomer) {
    int findIndex = -1;
    for (int i = 0; i < listCustomer.size(); i++) {
        if (listCustomer[i].id == idCustomer) {
            findIndex = i;
        }
    }

    return findIndex;
}

int findRoomIndex(vector<Room> listRoom, int idRoom) {
    int findIndex = -1;
    for (int i = 0; i < listRoom.size(); i++) {
        if (listRoom[i].id == idRoom) {
            findIndex = i;
        }
    }

    return findIndex;
}

bool roomOcValidation(Room r, int valCase) {
    bool valid = true;
    switch(valCase) {
        case 1:
            if (r.status == 1) {
                cout << "Gagal book room, room sudah di booked sebelumnya";
                valid = false;
            }
            break;
        case 2:
            if (r.status == 2) {
                cout << "Gagal check in room, room sudah di check in sebelumnya";
                valid = false;
            }
            break;
    }
    return valid;
}

void changeRoomFilled(vector<Room> * listRoom, vector<Customer> * listCustomer, int idCustomer, int status) {
    int customerIndex = findCustomerIndex(*listCustomer, idCustomer);
    
    cout << "\n";
    if (customerIndex == -1) {
        cout << "Customer dengan id: " << idCustomer << " tidak dapat ditemukan";
    } else {
        int roomIndex = findRoomIndex(*listRoom, (*listCustomer)[customerIndex].roomId);

        if (roomIndex == -1) {
            cout << "Room dengan id: " << idCustomer << " tidak dapat ditemukan";
        } else {
            if (roomOcValidation((*listRoom)[roomIndex], 2)) {
                if (status == 2) {
                    (*listRoom)[roomIndex].status = status;
                    (*listCustomer)[customerIndex].checkIn = currentDateTime();
                } else {
                    (*listCustomer)[customerIndex].checkOut = currentDateTime();
                    (*listRoom)[roomIndex].status = 0;
                    cout << "1.\t" << (*listCustomer)[customerIndex].toString();
                    cout << "\n\tDengan total\t:" << (*listCustomer)[customerIndex].total((*listRoom)[roomIndex].price) << "\n\n";
                }

                cout << "Room dengan id: " << (*listRoom)[roomIndex].id << " telah berhasil di " << (status == 2 ? "Check In" : "Check Out") << " oleh customer dengan id: " << idCustomer;
            }
        }
    }
}

void changeRoomBooked(vector<Room> * listRoom, vector<Customer> * listCustomer, int idCustomer, int roomId, bool status) {
    int customerIndex = findCustomerIndex(*listCustomer, idCustomer);

    cout << "\n";
    if (customerIndex == -1) {
        cout << "Customer dengan id: " << idCustomer << " tidak dapat ditemukan";
    } else {
        int roomIndex = findRoomIndex(*listRoom, roomId);

        if (roomIndex == -1) {
            cout << "Room dengan id: " << idCustomer << " tidak dapat ditemukan";
        } else {
            if (roomOcValidation((*listRoom)[roomIndex], 1)) {
                (*listCustomer)[(*listCustomer).size()-1].roomId = roomId;
                (*listRoom)[roomIndex].status = 1;
                cout << "Room dengan id: " << (*listRoom)[roomIndex].id << " telah berhasil di booked oleh customer dengan id: " << idCustomer;
            }
        }
    }
}

// ! TODO: Implement checkIn()
void checkIn(vector<Room> * listRoom, vector<Customer> * listCustomer) {
    int idCustomer;
    cout << "Masukan id customer yang ingin check in: "; cin >> idCustomer;

    changeRoomFilled(listRoom, listCustomer, idCustomer, 2);
    pausescr();
}

// ! TODO: Implement checkOut()
void checkOut(vector<Room> * listRoom, vector<Customer> * listCustomer) {
    int idCustomer;
    cout << "Masukan id customer yang ingin check out: "; cin >> idCustomer;

    changeRoomFilled(listRoom, listCustomer, idCustomer, 0);
    pausescr();
}

void roomsSortByPrice(vector<Room> * listRoom, int bedType, int roomType) {
    int countRoom = 1;
    vector<Room> matchedRoom;

    for (int i = 0; i < (*listRoom).size(); i++) {
        if (((*listRoom)[i].status == 0) && ((*listRoom)[i].roomType == roomType - 1) && ((*listRoom)[i].bedType == bedType - 1)) {
            matchedRoom.push_back((*listRoom)[i]);
        }
    }

    for (int i = 0; i < matchedRoom.size(); i++) {
        for (int j = 0; j < matchedRoom.size()-i-1; j++) {
            if (matchedRoom[j].price > matchedRoom[j+1].price) {
                Room tr = matchedRoom[j];
                matchedRoom[j] = matchedRoom[j+1];
                matchedRoom[j+1] = tr;
            }
        }
    }

    for (int i = 0; i < matchedRoom.size(); i++) {
        cout << countRoom << ".\t" <<  matchedRoom[i].toString() << "\n\n";
        countRoom++;
    }
}

// ! TODO: Implement kamarMenu()
void roomMenu(vector<Room> * listRoom) {
    int roomType, bedType;
	cout << "1. Standard Room" << endl;
	cout << "2. Deluxe Room" << endl;
	cout << "3. Suite Room" << endl;
	cout << "4. Presidential Suite Room" << endl;
    cout << "Pilih tipe kamar yang diinginkan: ";cin >> roomType;

	cout << "\n\n1. Single Bed" << endl;
	cout << "2. Twin Bed" << endl;
	cout << "3. Double Bed" << endl;
    cout << "Pilih tipe kasur yang diinginkan: ";cin >> bedType;

    cout << "\n\n";
    cout << "List kamar yang sesuai pilihan:\n";

    roomsSortByPrice(listRoom, roomType, bedType);
    pausescr();
}

// ! TODO: Implement hotelMainMenu()
void mainMenu(vector<Room> * listRoom, vector<Customer> * listCustomer) {
    int pilihanMenu;

    clearscr();
    cout << "\n\n===============================\n";
    cout << "Booking Hotel – Kelompok 5 – 1B\n\n";
    cout << "Pilih Menu (1-3)\n";
    cout << "1. Register Customer\n2. Menu Kamar\n3. Check In\n4. Check Out\n5. Keluar\n";
    cout << "\nPilihan : ";
    cin >> pilihanMenu;
    cout << "\n===============================\n\n";
    cin.ignore(256, '\n');
    clearscr();
    
    switch (pilihanMenu)
    {
        case 1:
            registerCustomer(listRoom, listCustomer);
            break;
        case 2:
            roomMenu(listRoom);
            break;
        case 3:
            checkIn(listRoom, listCustomer);
            break;
        case 4:
            checkOut(listRoom, listCustomer);
            break;
        case 5:
            return;
        default:
            return;
    }

    writeRoomsToFile((*listRoom));
    writeCustomersToFile((*listCustomer));
    
    mainMenu(listRoom, listCustomer);
}

void contohProgramOrang() {
  char resepsionis[30], customer[30], alamat[30], YT = 'Y';
	string hp, checkin, checkout, ruang;
	int kamar, bed, harga, lama, bayar, total;

	// Buat array kamar kosong (belum dibuat)

utama:
	system("cls");
	cout << "================" << endl;
	cout << "Reservasi Hotel " << endl;
	cout << "================" << endl << endl;

	// Resersionis Checkin
	cout << "Nama resepsionis :";
	cin >> resepsionis;
	cout << "Nama customer :";
	cin >> customer;
	cout << "No. Telp :";
	cin >> hp;
	cout << "Alamat :";
	cin >> alamat;
	cout << "Lama Menginap :";
	cin >> lama;
	cout << "Tanggal Check In :";
	cin >> checkin;
	cout << "Tanggal Check Out :";
	cin >> checkout;

menu:
	system("cls");

	// Searching Kamar Kosong

	// Pilih Kamar
	cout << "Pilih Kamar" << endl;
	cout << "1. Standard Room" << endl;
	cout << "2. Deluxe Room" << endl;
	cout << "3. Suite Room" << endl;
	cout << "4. Presidential Suite Room" << endl;
	cout << "Masukkan Pilihan = ";
	cin >> kamar;
	cout << endl;

	if (kamar == 4) {
		harga = 1000000;
		ruang = "Presidential Suite Room Beb";
		goto akhir;
	}

	// Pilih Kasur
	cout << "Pilih Kasur" << endl;
	cout << "1.Single Bed" << endl;
	cout << "2.Twin Bed" << endl;
	cout << "3. Double Bed" << endl;

	cout << "Masukkan Pilihan = ";
	cin >> bed;
	cout << endl;
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
		cout << "Inputan Salah" << endl;
		// getch();

		goto menu;
	}

akhir:
	system("cls");

	// Hitung Bayar Total #kalo mau ada
	total = harga * lama;

	// Ini Hasil Akhir Guys
	cout << "Nama resepsionis :" << resepsionis << endl;
	cout << "Nama customer :" << customer << endl;
	cout << "No. Telp :" << hp << endl;
	cout << "Alamat :" << alamat << endl;
	cout << "Tipe Kamar :" << kamar << endl;
	cout << "Lama Menginap :" << lama << endl;
	cout << "Tanggal Check In :" << checkin << endl;
	cout << "Tanggal Check Out :" << checkout << endl;
	cout << "Total =" << total << endl;
}
