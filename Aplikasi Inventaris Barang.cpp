#include <iostream>
#include <array>
#include <cstdlib>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

string TBLUser = "inventaris_data-user.txt";
string TBLBarang = "inventaris_data-barang.txt";

struct BarangRecord {
	string kode_barang;
	string nama_barang;
    int jumlah_barang;
};

struct UserRecord {
	string username;
	string password;
    string level;
};


void mainHeader();
string login(string username, string password);
void adminMenu();
void stafMenu();

void addDataUser(UserRecord user);
void inputDataUser();
void readDataUser();
void saveDBUser(struct UserRecord sortRecord[], int size);
void updateDataUser();
void deleteDataUser();

string inReplace(string str_replace);
string outReplace(string str_replace);
void addDataBarang(BarangRecord barang);
int barangDataSize(fstream &Database);
void inputDataBarang();
void barangTableHeader();
void readDataBarang();
void sortData(int x);
void saveDBBarang(struct BarangRecord sortRecord[], int size);
void searchData();
void updateDataBarang();
void deleteDataBarang();

int main(){
    awal:
    string username, password;

    mainHeader();
    cout<<"\n Login Ke Aplikasi"<<endl;
    //cin.ignore(1, '\n');
    cout<<" Masukan Username\t: ";
    getline(cin,username);
    cout<<" Masukkan Password\t: ";
    getline(cin, password);

    if(login(username, password) == "Admin"){
        system("cls");
        mainHeader();
        adminMenu();
    }else if(login(username, password) == "Staf"){
        system("cls");
        mainHeader();
        stafMenu();
    }else{
        system("cls");
        cout<<" ==================================="<<endl;
        cout<<"           Login gagal"<<endl;
        cout<<" ===================================\n\n"<<endl;
        goto awal;
    }
	return 0;
}

string login(string username, string password){
    int size;
    fstream Database;
    size = barangDataSize(Database);
    Database.open(TBLUser);
    UserRecord* array = new UserRecord[size];

    mainHeader();
    for(int i = 0; i<size; i++){
        Database>>array[i].username;
        Database>>array[i].password;
        Database>>array[i].level;
    }
    Database.close();

    username = regex_replace(username, regex("\\ "), "~");
    password = regex_replace(password, regex("\\ "), "~");
    int jmlFound = 0;
    for(int i=0;i<size;i++) {
        if(array[i].username == username && array[i].password == password) {
            return array[i].level;
            jmlFound++;
        }
    }
    cout<<"\n\n";
    if(jmlFound == 0){
        return " ";
    }
}

void mainHeader(){
    cout<<"\n Nama\t: Dadan Abdilah \n NIM\t: 20210810091 \n Kelas\t: TINFC-2021-02 / TI 2021 B"<<endl;
    cout<<" ===================================================================================="<<endl;
    cout<<"                              Program Inventaris Barang             "<<endl;
    cout<<" ===================================================================================="<<endl;
}

void adminMenu(){
    menu:
    cout<<" Menu Utama"<<endl;
    cout<<" 1. Tambah Data Barang"<<endl;
    cout<<" 2. Tampilkan Data Barang"<<endl;
    cout<<" 3. Urutkan Data Berdasarkan Kode Barang"<<endl;
    cout<<" 4. Urutkan Data Berdasarkan Jumlah Barang Terkecil"<<endl;
    cout<<" 5. Cari Data Barang"<<endl;
    cout<<" 6. Update Data Barang"<<endl;
    cout<<" 7. Hapus Data Barang"<<endl;
    cout<<" 8. Tambah Data User"<<endl;
    cout<<" 9. Tampilkan Data User"<<endl;
    cout<<" 10. Update Data User"<<endl;
    cout<<" 11. Hapus Data User"<<endl;
    cout<<" 12. Keluar"<<endl;
    cout<<endl;

    string jwb;
    cout<<" Pilih Menu [1-12]: ";
    cin>>jwb;

    if (jwb == "1"){
        inputDataBarang();
        system("cls");
        mainHeader();
        goto menu;
    } else if ( jwb=="2"){
        readDataBarang();
        goto menu;
    } else if (jwb =="3" ) {
        sortData(1);
        goto menu;
    } else if (jwb == "4"){
        sortData(2);
        goto menu;
    } else if (jwb =="5") {
        system("cls");
        mainHeader();
        searchData();
        goto menu;
    } else if (jwb == "6"){
        updateDataBarang();
        system("cls");
        mainHeader();
        goto menu;
    } else if (jwb== "7") {
        deleteDataBarang();
        system("cls");
        mainHeader();
        cout<<"Penghapusan Data Sukses"<<endl;
        goto menu;
    } else if (jwb == "8"){
        inputDataUser();
        system("cls");
        mainHeader();
        goto menu;
    } else if ( jwb=="9"){
        readDataUser();
        goto menu;
    } else if (jwb == "10"){
        updateDataUser();
        system("cls");
        mainHeader();
        goto menu;
    } else if (jwb== "11") {
        deleteDataUser();
        system("cls");
        mainHeader();
        cout<<"Penghapusan Data Sukses"<<endl;
        goto menu;
    } else if (jwb == "12") {
        system("cls");
        atexit;
    } else {
        system ("cls");
        cout<<"\nInput Tidak Valid !!! \n"<<endl;
        goto menu;
    }
}

void stafMenu(){
    menu:
    cout<<" Menu Utama"<<endl;
    cout<<" 1. Tambah Data Barang"<<endl;
    cout<<" 2. Tampilkan Data Barang"<<endl;
    cout<<" 3. Urutkan Data Berdasarkan Kode Barang"<<endl;
    cout<<" 4. Urutkan Data Berdasarkan Jumlah Barang Terkecil"<<endl;
    cout<<" 5. Cari Data Barang"<<endl;
    cout<<" 6. Keluar"<<endl;
    cout<<endl;

    string jwb;
    cout<<" Pilih Menu [1-6]: ";
    cin>>jwb;

    if (jwb == "1"){
        inputDataBarang();
        system("cls");
        mainHeader();
        goto menu;
    } else if ( jwb=="2"){
        readDataBarang();
        goto menu;
    } else if (jwb =="3" ) {
        sortData(1);
        goto menu;
    } else if (jwb == "4"){
        sortData(2);
        goto menu;
    } else if (jwb =="5") {
        system("cls");
        mainHeader();
        searchData();
        goto menu;
    } else if (jwb == "6") {
        system("cls");
        atexit;
    } else {
        system ("cls");
        cout<<"\nInput Tidak Valid !!! \n"<<endl;
        goto menu;
    }
}

// user
void tableUserHeader(){
    cout<<" ============================================================================"<<endl;
    cout<<" Username\t\t"<<"Password\t\t\t\t\t"<<"Level"<<endl;
    cout<<" ============================================================================"<<endl;
}

void inputDataUser() {
    UserRecord user;

    system("cls");
    mainHeader();
    cout<<"\n Input Data User"<<endl;

    cin.ignore(1, '\n');
    cout<<" Masukkan Username\t: ";
    getline(cin, user.username);
    cout<<" Masukkan Password\t: ";
    getline(cin, user.password);
    cout<<" Masukkan Level [Admin/Staf] \t: ";
    cin>>user.level;

    addDataUser(user);

    cout<<endl;
}

void addDataUser(UserRecord user){
    fstream data;
    data.open(TBLUser, ios::app);
    data <<user.username<<"   "<<user.password<<"   "<<user.level<<endl;
    data.close();
}

int userDataSize(fstream &Database) {
    UserRecord dataSize;
    int size;

    Database.open(TBLUser);
    while (getline(Database, dataSize.username))
        size++;

    Database.close();
    return size ;
}

void readDataUser() {
    fstream Database;
    int size;

    size = userDataSize(Database);

    Database.open(TBLUser);

    UserRecord* sortRecord = new UserRecord[size];

    for(int i = 0; i<size; i++){

        Database>>sortRecord[i].username;
        Database>>sortRecord[i].password;
        Database>>sortRecord[i].level;
    }

    Database.close();

    system("cls");
    mainHeader();
    cout<<"\n Menampilkan Semua Data User"<<endl;
    tableUserHeader();
    for ( int i=0; i<size; i++) {\
        cout<<" "<<sortRecord[i].username<<"\t\t\t"<<sortRecord[i].password<<"\t\t\t\t"<<sortRecord[i].level<<endl;
    }
    cout<<endl;
}

void saveDBUser(struct UserRecord sortRecord[], int size) {

    fstream Database;
    Database.open(TBLUser, ios::trunc | ios::out);

    for (int i=0; i < size; i++){
        Database<<sortRecord[i].username<<"   "<<sortRecord[i].password<<"   "<<sortRecord[i].level<<endl;
    }

    Database.close();
}

void updateDataUser() {
    string keyword;
    int size;

    fstream Database;

    size = userDataSize(Database);

    Database.open(TBLUser);

    UserRecord* array = new UserRecord[size];

    for(int i = 0; i<size; i++){
        Database>>array[i].username;
        Database>>array[i].password;
        Database>>array[i].level;
    }

    Database.close();

    readDataUser();

    cout<<" Masukkan Username Untuk Update Data : ";
    cin>>keyword;

    for(int i=0;i<size;i++) {
        if(array[i].username == keyword) {
            tableUserHeader();
            cout<<" "<<array[i].username<<"\t\t\t"<<array[i].password<<"\t\t\t\t"<<array[i].level<<endl;

            cout<<"\n Masukkan Data Baru"<<endl;
            cin.ignore(1, '\n');
            cout<<" Masukkan Username\t: ";
            getline(cin, array[i].username);
            cout<<" Masukkan Password\t: ";
            getline(cin, array[i].password);
            cout<<" Masukkan Level [Admin/Staf] \t: ";
            cin>>array[i].level;

            saveDBUser(array, size);

            cout<<endl;
            return;
        }
    }
}

void deleteDataUser() {
    string keyword;
    int size;
    fstream Database;
    size = userDataSize(Database);

    Database.open(TBLUser);
    UserRecord* array = new UserRecord[size];

    for(int i = 0; i<size; i++){
        Database>>array[i].username;
        Database>>array[i].password;
        Database>>array[i].level;
    }

    Database.close();

    readDataUser();

    cout<<" Masukkan Username Yang Akan Dihapus : ";
    cin>>keyword;

    for(int i=0;i<size;i++) {
        if(array[i].username == keyword) {
            for(int j=i; j<size-1; j++) {
                array[j].username = array[j+1].username;
                array[j].password = array[j+1].password;
                array[j].level = array[j+1].level;
            }
            size--;

            saveDBUser(array, size);
            return;
        }
    }
}
// end user


// barang
string inReplace(string str_replace){
    string data;
    data = regex_replace(str_replace, regex("\\ "), "~");
    return data;
}

string outReplace(string str_replace){
    string data;
    data = regex_replace(str_replace, regex("\\~"), " ");
    return data;
}

void inputDataBarang() {
    string kode_brg, nama_brg;
    int jumlah_brg;
    BarangRecord barang;

    system("cls");
    mainHeader();
    cout<<"\n Input Data Barang"<<endl;

    cin.ignore(1, '\n');
    cout<<" Masukkan Kode Barang\t: ";
    getline(cin,kode_brg);
    cout<<" Masukkan Nama Barang\t: ";
    getline(cin, nama_brg);
    cout<<" Masukkan Jumlah Barang\t: ";
    cin>>jumlah_brg;

    barang.nama_barang = inReplace(nama_brg);
    barang.kode_barang = kode_brg;
    barang.jumlah_barang = jumlah_brg;
    addDataBarang(barang);

    cout<<endl;
}

void addDataBarang(BarangRecord barang){
    fstream data;
    data.open(TBLBarang, ios::app);
    data <<barang.kode_barang<<"   "<<barang.nama_barang<<"   "<<barang.jumlah_barang<<endl;
    data.close();
}

int barangDataSize(fstream &Database) {
    BarangRecord dataSize;
    int size;

    Database.open(TBLBarang);
    while (getline(Database, dataSize.kode_barang))
        size++;

    Database.close();

    return size ;
}

void readDataBarang() {
    fstream Database;
    int size;

    size = barangDataSize(Database);

    Database.open(TBLBarang);

    BarangRecord* sortRecord = new BarangRecord[size];

    for(int i = 0; i<size; i++){

        Database>>sortRecord[i].kode_barang;
        Database>>sortRecord[i].nama_barang;
        Database>>sortRecord[i].jumlah_barang;
    }

    Database.close();

    system("cls");
    mainHeader();
    cout<<"\n Menampilkan Semua Data Barang"<<endl;
    barangTableHeader();
    for ( int i=0; i<size; i++) {\
        cout<<" "<<sortRecord[i].kode_barang<<"\t\t"<<outReplace(sortRecord[i].nama_barang)<<"\t\t\t\t\t"<<sortRecord[i].jumlah_barang<<endl;
    }
    cout<<endl;
}

void barangTableHeader(){
    cout<<" ============================================================================"<<endl;
    cout<<" Kode Barang\t"<<"Nama Barang\t\t\t\t\t"<<"Jumlah Barang"<<endl;
    cout<<" ============================================================================"<<endl;
}

void sortAsc(struct BarangRecord arr[], int n){
    int i, j;
    struct BarangRecord key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j].kode_barang > key.kode_barang) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
            arr[j + 1] = key;
    }
}

void sortByQty(struct BarangRecord arr[], int n) {
    int i, j;
    struct BarangRecord key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j].jumlah_barang > key.jumlah_barang) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void sortData(int x) {
    fstream Database;
    int size;

    size = barangDataSize(Database);

    Database.open(TBLBarang);

    BarangRecord* sortRecord = new BarangRecord[size];

    for(int i = 0; i<size; i++){
        Database>>sortRecord[i].kode_barang;
        Database>>sortRecord[i].nama_barang;
        Database>>sortRecord[i].jumlah_barang;
    }

    Database.close();

    if (x == 1) {
        sortAsc(sortRecord, size);
        saveDBBarang(sortRecord, size);
    }
    else if ( x== 2) {
        sortByQty(sortRecord, size);
        saveDBBarang(sortRecord, size);
    }

    system("cls");
    mainHeader();
    cout<<"\n Hasil Pengurutan Data : "<<endl;
    barangTableHeader();
    for ( int i=0; i<size; i++) {
        cout<<" "<<sortRecord[i].kode_barang<<"\t\t"<<outReplace(sortRecord[i].nama_barang)<<"\t\t\t\t"<<sortRecord[i].jumlah_barang<<endl;
    }

    cout<<endl;
}

void saveDBBarang(struct BarangRecord sortRecord[], int size) {

    fstream Database;
    Database.open(TBLBarang, ios::trunc | ios::out);

    for (int i=0; i < size; i++){

        Database<<sortRecord[i].kode_barang<<"   "<<sortRecord[i].nama_barang<<"   "<<sortRecord[i].jumlah_barang<<endl;
    }

    Database.close();
}

void printErr () {
    system ("cls");
    cout <<"\n\n Keyword Invalid / Data Tidak Ada\n\n"<<endl;
}

void printSearch (BarangRecord array) {
    //system ("cls");
    cout<<"\n Hasil Pencarian Data "<<endl;
    barangTableHeader();
    cout<<" "<< array.kode_barang<<"\t\t"<<outReplace(array.nama_barang)<<"\t\t\t\t"<<array.jumlah_barang<<endl;
    cout<<endl;
}

void searchData() {
    string keyword;
    int size;

    fstream Database;

    size = barangDataSize(Database);

    Database.open(TBLBarang);

    BarangRecord* array = new BarangRecord[size];

    for(int i = 0; i<size; i++){
        Database>>array[i].kode_barang;
        Database>>array[i].nama_barang;
        Database>>array[i].jumlah_barang;
    }

    Database.close();
    cout<<"\n Cari Barang"<<endl;
    cout<<" Masukkan Nama Barang : ";
    cin>>keyword;

    cout<<"\n Hasil Pencarian Data"<<endl;
    barangTableHeader();

    keyword = regex_replace(keyword, regex("\\ "), "~");
    int jmlFound = 0;
    for(int i=0;i<size;i++) {
        if(array[i].nama_barang.find(keyword) != string::npos) {
            //printSearch(array[i]);
            cout<<" "<< array[i].kode_barang<<"\t\t"<<outReplace(array[i].nama_barang)<<"\t\t\t\t"<<array[i].jumlah_barang<<endl;
            jmlFound++;
        }
    }
    cout<<"\n\n";
    if(jmlFound == 0){
        printErr();
    }
}

void updateDataBarang() {
    string keyword, kode_brg, nama_brg;
    int jumlah_brg;
    int size;

    fstream Database;

    size = barangDataSize(Database);

    Database.open(TBLBarang);

    BarangRecord* array = new BarangRecord[size];

    for(int i = 0; i<size; i++){
        Database>>array[i].kode_barang;
        Database>>array[i].nama_barang;
        Database>>array[i].jumlah_barang;
    }

    Database.close();

    readDataBarang();

    cout<<" Masukkan Kode Barang Untuk Update Data : ";
    cin>>keyword;

    for(int i=0;i<size;i++) {
        if(array[i].kode_barang == keyword) {
            // panggil fungsi header tabel
            barangTableHeader();
            cout<<" "<<array[i].kode_barang<<"\t\t"<<outReplace(array[i].nama_barang)<<"\t\t\t\t"<<array[i].jumlah_barang<<endl;

            cout<<"\n Masukkan Data Baru : "<<endl;
            cin.ignore(1, '\n');
            cout<<" Masukkan Kode Barang\t: ";
            getline(cin,kode_brg);
            cout<<" Masukkan Nama Barang\t: ";
            getline(cin, nama_brg);
            cout<<" Masukkan Jumlah Barang\t: ";
            cin>>jumlah_brg;

            array[i].nama_barang = inReplace(nama_brg);
            array[i].kode_barang = kode_brg;
            array[i].jumlah_barang = jumlah_brg;

            saveDBBarang(array, size);

            cout<<endl;
            return;
        }
    }
    printErr();
}

void deleteDataBarang() {
    string keyword, kode_brg, nama_brg;
    int jumlah_brg;
    int size;

    fstream Database;

    size = barangDataSize(Database);

    Database.open(TBLBarang);

    BarangRecord* array = new BarangRecord[size];

    for(int i = 0; i<size; i++){
        Database>>array[i].kode_barang;
        Database>>array[i].nama_barang;
        Database>>array[i].jumlah_barang;
    }

    Database.close();

    readDataBarang();

    cout<<" Masukkan Kode Barang Yang Akan Dihapus : ";
    cin>>keyword;

    for(int i=0;i<size;i++) {
        if(array[i].kode_barang == keyword) {
            for(int j=i; j<size-1; j++) {
                array[j].kode_barang = array[j+1].kode_barang;
                array[j].nama_barang = array[j+1].nama_barang;
                array[j].jumlah_barang = array[j+1].jumlah_barang;
            }
            size--;

            saveDBBarang(array, size);
            return;
        }
    }
    printErr();
}

