#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <functional>
#include <cstdlib>

using namespace std;

// ! INFO Definisi struct sama fungsi biar bisa diakses sama fungsi lain walaupun belum ada isinya
struct Room;
struct Customer;

vector<Room> readFileToRooms();
vector<Customer> readFileToCustomers();

void changeRoomBooked(int idCustomer, int roomId, bool status);
void changeRoomFilled(int idCustomer, bool status);

void roomMenu();
void mainMenu();

// ! INFO listRoom sama listCustomer datanya diisi waktu di fungsi main dan datanya di read dari file masing-masing
vector<Room> listRoom;
vector<Customer> listCustomer;

// ! INFO Constant nama file buat mudahin misalnya filenya ganti nama
const string roomFileTxt = "roomfile.txt";
const string customerFileTxt = "customerfile.txt";

// ! INFO: Buat mapping bedType dan roomType
string bedTypeStr[] = {"Single Bed", "Twin Bed", "Double Bed"};
string roomTypeStr[] = {"Standard Room", "Deluxe Room", "Suite Room", "Presidential Suite Room"};

struct Room
{
    int id = -1;
    int roomType = -1;
    int bedType = -1;
    int price = -1;

    // 0=default, 1=booked, 2=filled
    int status = 0;

    Room(){};

    Room(int id_, int bedType_, int roomType_, int price_)
    {
        id = id_;
        bedType = bedType_;
        roomType = roomType_;
        price = price_;
    }

    string toString()
    {
        return "ID Kamar\t: " + to_string(id) + "\n\tTipe Kamar\t: " + roomTypeStr[roomType] + "\n\tTipe Kasur\t: " + bedTypeStr[bedType] + "\n\tHarga\t\t: " + to_string(price);
    }
};

struct Customer
{
    int id = -1;
    string name = "_";
    string phoneNumber = "_";
    int days = -1;
    string checkIn = "_";
    string checkOut = "_";
    int roomId = -1;

    Customer(){};

    Customer(int id_, string name_, string phoneNumber_, int days_)
    {
        id = id_;
        name = name_;
        phoneNumber = phoneNumber_;
        days = days_;
    }

    int total(int price)
    {
        return price * days;
    }

    string toString()
    {
        return "ID User\t\t\t: " + to_string(id) + "\n\tNama\t\t\t: " + name + "\n\tNomor Telpon\t: " + phoneNumber + "\n\tWaktu Check In\t: " + checkIn + "\n\tWaktu Check Out\t: " + checkOut + "\n\tID Kamar\t\t: " + to_string(roomId);
    }
};

// ! INFO clear screen untuk windows dan unix(linux/macos)
void clearscr()
{
#ifdef WINDOWS
    system("cls");
#else
    system("clear");
#endif
}

void pausescr()
{
    cin.ignore(256, '\n');
    string dummy;
    cout << "\n\nEnter to continue...";
    getline(cin, dummy);
}

// ! INFO ngecek file yang mau diread apakah kosong
bool isFileEmpty(fstream &pFile)
{
    return pFile.peek() == ifstream::traits_type::eof();
}

vector<Room> readFileToRooms()
{
    vector<Room> lr;

    fstream roomFile(roomFileTxt, fstream::in | fstream::out);

    // ! INFO cek kalo open file gagal
    if (!roomFile.fail())
    {
        if (!isFileEmpty(roomFile))
        {
            while (!roomFile.eof())
            {
                Room nr;
                roomFile >> nr.id;
                roomFile >> nr.roomType;
                roomFile >> nr.bedType;
                roomFile >> nr.price;
                roomFile >> nr.status;

                // ! INFO di cek id nya -1 soalnya default value nya -1
                // di cek sebelum di push soalnya ada case si data dari file empty tapi tetep ke push
                if (nr.id > -1)
                {
                    lr.push_back(nr);
                }
            }
        }
    }

    roomFile.close();

    return lr;
}

void writeRoomsToFile()
{
    fstream roomFile(roomFileTxt, fstream::in | fstream::out | fstream::trunc);

    // ! INFO write ke file setelah tiap variable dikasih spasi dan setelah tiap data dikasih line baru
    for (int i = 0; i < listRoom.size(); i++)
    {
        if (listRoom[i].id > -1)
        {
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

vector<Customer> readFileToCustomers()
{
    vector<Customer> lc;

    fstream customerFile(customerFileTxt, fstream::in | fstream::out);

    if (!customerFile.fail())
    {
        if (!isFileEmpty(customerFile))
        {
            while (!customerFile.eof())
            {
                Customer nc;
                customerFile >> nc.id;
                customerFile >> nc.name;
                customerFile >> nc.phoneNumber;
                customerFile >> nc.days;
                customerFile >> nc.checkIn;
                customerFile >> nc.checkOut;
                customerFile >> nc.roomId;

                // ! INFO mirip kaya readFileToRooms
                if (nc.id > -1)
                {
                    lc.push_back(nc);
                }
            }
        }
    }

    customerFile.close();

    return lc;
}

void writeCustomersToFile()
{
    fstream customerFile(customerFileTxt, fstream::in | fstream::out | fstream::trunc);

    // ! INFO mirip kaya writeRoomsToFile
    for (int i = 0; i < listCustomer.size(); i++)
    {
        if (listCustomer[i].id > -1)
        {
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

const string currentDateTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

// ! TODO: print array, template ini gunanya biar bisa naro vector tipe apa aja kesini, soalnya vector<Room> sama vector<Customer> itu beda tipe
template <typename T>
void printArray(vector<T> list)
{
    for (int i = 0; i < list.size(); i++)
    {
        cout << i << ".\t" << list[i].toString() << "\n\n";
    }
}

// ! TODO: ini register customer dan daftarin ke room yang ingin di book
void registerCustomer()
{
    Customer newCustomer;
    cout << "\nMasukan nama\t\t: ";
    cin >> newCustomer.name;
    cout << "Masukan nomor telpon: ";
    cin >> newCustomer.phoneNumber;
    cout << "Berapa lama\t\t\t: ";
    cin >> newCustomer.days;
    newCustomer.id = time(NULL);

    cout << endl;

    listCustomer.push_back(newCustomer);

    cout << "Data customer berhasil dibuat\n";
    cout << "1.\t" << newCustomer.toString() << "\n\n\n";

    roomMenu();

    int roomId = -1;
    cout << "\nPilih ID Kamar\t: ";
    cin >> roomId;
    if (roomId != -1)
    {
        changeRoomBooked(listCustomer[listCustomer.size() - 1].id, roomId, true);

        cout << "\n\nPesan kamar selesai\n";
        pausescr();
    }
}

// ! INFO: cari index dari customer yang dicari
int findCustomerIndex(int idCustomer)
{
    int findIndex = -1;
    for (int i = 0; i < listCustomer.size(); i++)
    {
        if (listCustomer[i].id == idCustomer)
        {
            findIndex = i;
        }
    }

    return findIndex;
}

// ! INFO: cari index dari room yang dicari
int findRoomIndex(int idRoom)
{
    int findIndex = -1;
    for (int i = 0; i < listRoom.size(); i++)
    {
        if (listRoom[i].id == idRoom)
        {
            findIndex = i;
        }
    }

    return findIndex;
}

// ! INFO: ini untuk validasi waktu book sama checkin/checkout room
bool roomOcValidation(Room r, int valCase)
{
    bool valid = true;
    switch (valCase)
    {
    case 1:
        if (r.status != 0)
        {
            cout << "Gagal booking room, room sudah di booked sebelumnya";
            valid = false;
        }
        break;
    case 2:
        if (r.status == 2)
        {
            cout << "Gagal check in room, room sudah di check in sebelumnya";
            valid = false;
        }
        break;
    case 3:
        if (r.status != 2)
        {
            cout << "Gagal check out room, room belum di check in sebelumnya";
            valid = false;
        }
        break;
    }
    return valid;
}

// ! ini buat ubah status room yang mau di checkin/checkout, nantinya mau direfactor/diubah jadi satu fungsi sama buat book room
void changeRoomFilled(int idCustomer, int status)
{
    int customerIndex = findCustomerIndex(idCustomer);

    cout << "\n";
    if (customerIndex == -1)
    {
        cout << "Customer dengan id: " << idCustomer << " tidak dapat ditemukan";
    }
    else
    {
        int roomIndex = findRoomIndex(listCustomer[customerIndex].roomId);

        if (roomIndex == -1)
        {
            cout << "Room dengan id: " << idCustomer << " tidak dapat ditemukan";
        }
        else
        {
            if (roomOcValidation(listRoom[roomIndex], status))
            {
                if (status == 2)
                {
                    listRoom[roomIndex].status = status;
                    listCustomer[customerIndex].checkIn = currentDateTime();
                }
                else
                {
                    listCustomer[customerIndex].checkOut = currentDateTime();
                    listRoom[roomIndex].status = 0;

                    cout << "1.\t" << listCustomer[customerIndex].toString();
                    cout << "\n\tDengan total\t: " << listCustomer[customerIndex].total(listRoom[roomIndex].price) << "\n\n";
                    
                    listCustomer.erase(listCustomer.begin() + customerIndex);
                }

                cout << "Room dengan id: " << listRoom[roomIndex].id << " telah berhasil di " << (status == 2 ? "Check In" : "Check Out") << " oleh customer dengan id: " << idCustomer;
            }
        }
    }
}

// ! TODO: refactor fungsi ini, pake satu fungsi yang sama buat book dan checkin/checkout
void changeRoomBooked(int idCustomer, int roomId, bool status)
{
    int customerIndex = findCustomerIndex(idCustomer);

    cout << "\n";
    if (customerIndex == -1)
    {
        cout << "Customer dengan id: " << idCustomer << " tidak dapat ditemukan";
    }
    else
    {
        int roomIndex = findRoomIndex(roomId);

        if (roomIndex == -1)
        {
            cout << "Room dengan id: " << idCustomer << " tidak dapat ditemukan";
        }
        else
        {
            if (roomOcValidation(listRoom[roomIndex], 1))
            {
                listCustomer[listCustomer.size() - 1].roomId = roomId;
                listRoom[roomIndex].status = 1;
                cout << "Room dengan id: " << listRoom[roomIndex].id << " telah berhasil di booked oleh customer dengan id: " << idCustomer;
            }
        }
    }
}

void checkIn()
{
    int idCustomer;
    cout << "Masukan id customer yang ingin check in: ";
    cin >> idCustomer;

    changeRoomFilled(idCustomer, 2);
    pausescr();
}

void checkOut()
{
    int idCustomer;
    cout << "Masukan id customer yang ingin check out: ";
    cin >> idCustomer;

    changeRoomFilled(idCustomer, 3);
    pausescr();
}

// ! INFO: sorting room berdasarkan harga terkecil
void roomsSortByPrice(int roomType, int bedType)
{
    int countRoom = 0;
    vector<Room> matchedRoom;

    // ! INFO: buat array baru untuk room yang sesuai berdasarkan bedType dan roomType
    for (int i = 0; i < listRoom.size(); i++)
    {
        if ((listRoom[i].status == 0) && (listRoom[i].roomType == roomType) && (listRoom[i].bedType == bedType))
        {
            matchedRoom.push_back(listRoom[i]);
        }
    }

    // ! INFO: bubble sort room berdasarkan harga terkecil
    for (int i = 0; i < matchedRoom.size(); i++)
    {
        for (int j = 0; j < matchedRoom.size() - i - 1; j++)
        {
            if (matchedRoom[j].price > matchedRoom[j + 1].price)
            {
                Room tr = matchedRoom[j];
                matchedRoom[j] = matchedRoom[j + 1];
                matchedRoom[j + 1] = tr;
            }
        }
    }

    for (int i = 0; i < matchedRoom.size(); i++)
    {
        cout << countRoom+1 << ".\t" << matchedRoom[i].toString() << "\n\n";
        countRoom++;
    }

    if (countRoom > 0) {
        pausescr();
    }

    if (countRoom == 0)
    {
        cout << "Room dengan tipe tersebut tidak tersedia silahkan pilih kembali\n\n";
        pausescr();
        clearscr();
        roomMenu();
    }
}

void roomMenu()
{
    int roomType, bedType;
    cout << "1. Standard Room" << endl;
    cout << "2. Deluxe Room" << endl;
    cout << "3. Suite Room" << endl;
    cout << "4. Presidential Suite Room" << endl;
    cout << "Pilih tipe kamar yang diinginkan: ";
    cin >> roomType;

    cout << "\n\n1. Single Bed" << endl;
    cout << "2. Twin Bed" << endl;
    cout << "3. Double Bed" << endl;
    cout << "Pilih tipe kasur yang diinginkan: ";
    cin >> bedType;

    cout << "\n\n";
    cout << "List kamar yang sesuai pilihan:\n";

    roomsSortByPrice(roomType - 1, bedType - 1);
}

// ! TODO: Implement menu lain
void mainMenu()
{
    int pilihanMenu;

    clearscr();
    cout << "\n\n===============================\n";
    cout << "Booking Hotel – Kelompok 5 – 1B\n\n";
    cout << "Pilih Menu (1-5)\n";
    cout << "1. Register Customer\n2. Menu Kamar\n3. Check In\n4. Check Out\n5. Keluar\n";
    cout << "\nPilihan : ";
    cin >> pilihanMenu;
    cout << "\n===============================\n\n";
    cin.ignore(256, '\n');
    clearscr();

    switch (pilihanMenu)
    {
    case 1:
        registerCustomer();
        break;
    case 2:
        roomMenu();
        break;
    case 3:
        checkIn();
        break;
    case 4:
        checkOut();
        break;
    case 5:
        return;
    default:
        return;
    }

    writeRoomsToFile();
    writeCustomersToFile();

    mainMenu();
}

// ! ALUR:
// 0. Tambah Login (Optional)
// 1. Muncul Menu Utama Aplikasi (Register Customer, Checkin, Checkout, Cari Kamar)
// 2. Setelah selesai di menu utama akan balik lagi ke menu utama
int main()
{
    listCustomer = readFileToCustomers();
    listRoom = readFileToRooms();

    mainMenu();
}
