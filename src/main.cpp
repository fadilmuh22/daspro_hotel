#include <iostream>
#include <conio.h>

#include "main.hpp"

using namespace std;

// ! ALUR:
// 0. Tambah Login (Optional)
// 1. Muncul Menu Utama Aplikasi (Register Customer, Checkin, Checkout, Cari Kamar)
// 2. Setelah selesai di menu utama akan balik lagi ke menu utama

int main()
{
    vector<Customer> listCustomer = readFileToCustomers();
    vector<Room> listRoom = readFileToRooms();

    mainMenu(&listRoom, &listCustomer);
}