#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Struct untuk menyimpan informasi tentang film,waktu penayangan,dan ruangan penayangan 
struct Film {
    string judul;
    string genre;
    int durasi;
    string pukul_penayangan;
    string ruanganpenayangan; 
};
//sturct untuk tempat duduk
struct Seat {
    int nomor;
    bool tersedia;
};

// Node untuk linked list
struct Node {
    Film data;
    Node* next;
};
class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void tambahFilm(const Film& film) {
        Node* newNode = new Node;
        newNode->data = film;
        newNode->next = nullptr;
        
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void tampilkanFilm() {
        Node* current = head;
        int count = 1;
        while (current != nullptr) {
            cout << count << ". Judul: " << current->data.judul << endl;
            cout << "   Genre: " << current->data.genre << endl;
            cout << "   Durasi: " << current->data.durasi << " menit" << endl;
            cout << "   Pukul Penayangan: " << current->data.pukul_penayangan << endl; 
            cout << "   Ruangan Penayangan: " << current->data.ruanganpenayangan << endl; 
            cout << endl;
            current = current->next;
            count++;
        }
    }

    bool filmTersedia(int index) {
        Node* current = head;
        int count = 0;
        while (current != nullptr) {
            if (count == index) {
                return true;
            }
            current = current->next;
            count++;
        }
        return false;
    }
    Film getFilm(int index) {
        Node* current = head;
        int count = 0;
        while (current != nullptr) {
            if (count == index) {
                return current->data;
            }
            current = current->next;
            count++;
        }
        
        return {"", "", 0};
    }
};

void bayar(double total) {
    double uangMasuk;
    int metode;
    cout << "Total pembayaran: Rp." << fixed << setprecision(2) << total << endl;
    cout << "Pilih Metode Pembayaran : " << endl;
    cout << "1. Cash" << endl;
    cout << "2. Debit" << endl;
    cout << "Masukan Pilihan: ";
    cin >> metode;

    if (metode != 1 && metode != 2) {
        cout << "Input tidak valid. Pembayaran dibatalkan. Silahkan pilih kembali." << endl;
        return;
    }

    cout << "Masukkan jumlah uang yang akan dibayarkan: Rp.";
    cin >> uangMasuk;

    if (uangMasuk >= total) {
        cout << "Pembayaran berhasil. Terima kasih." << endl;
        if (uangMasuk > total) {
            cout << "Kembalian Anda: Rp." << fixed << setprecision(2) << uangMasuk - total << endl;
        }
    } else {
        cout << "Maaf uang yang anda berikan tidak cukup. Pembayaran dibatalkan." << endl;
    }
}

int main() {
    // Array untuk menyimpan data film yang tersedia 
    Film daftarFilm[] = {
        {"Avengers: Endgame", "Action", 181, "10:00", "A1"},
        {"IT", "Thriller", 132, "13:00", "B2"},
        {"The Dark Knight", "Crime", 152, "15:30", "C3"},
        {"Incridibles", "Animasi", 125, "18:00", "D4"},
        {"True Beuty", "Drama", 142, "20:00", "E5"}
    };

    // Linked list untuk menyimpan film-film yang tersedia
    LinkedList filmList;

    // Menambahkan film-film dari array ke linked list
    for (const Film& film : daftarFilm) {
        filmList.tambahFilm(film);
    }
    const int jumlahRuangan = 5;
    const int jumlahTempatDudukPerRuangan = 50;
    bool ketersediaanTempatDuduk[jumlahRuangan][jumlahTempatDudukPerRuangan];
    for (int i = 0; i < jumlahRuangan; ++i) {
        for (int j = 0; j < jumlahTempatDudukPerRuangan; ++j) {
            ketersediaanTempatDuduk[i][j] = true;
        }
    }

    int pilihan;
    do {
        cout << "===============================" << endl;
        cout << "| Selamat Datang di Bioskop XIX|" << endl;
        cout << "===============================" << endl;
        cout << "| 1. Daftar Film               |" << endl;
        cout << "| 2. Pilih Film                |" << endl;
        cout << "| 3. Keluar                    |" << endl;
        cout << "===============================" << endl;
        cout << "\nPilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                // Menampilkan daftar film dari linked list
                cout << "\nDaftar Film:\n";
                filmList.tampilkanFilm();
                break;
            case 2: {
                int nomorFilm;
                cout << "Film yang bisa ditonton:" << endl;
                filmList.tampilkanFilm();
                cout << "\nMasukkan nomor film yang ingin Anda tonton: ";
                cin >> nomorFilm;

                if (filmList.filmTersedia(nomorFilm - 1)) {
                    Film filmTerpilih = filmList.getFilm(nomorFilm - 1);
                    cout << "\nFilm: " << filmTerpilih.judul << endl;
                    cout << "Waktu Penayangan: " << filmTerpilih.pukul_penayangan << endl; 
                    cout << "Ruangan: " << filmTerpilih.ruanganpenayangan << endl; 

                    int jumlahTiket;
                    cout << "Jumlah tiket yang ingin dibeli: ";
                    cin >> jumlahTiket;

                    if (jumlahTiket <= 0) {
                        cout << "Jumlah tiket tidak valid. Silakan pilih jumlah tiket yang lebih dari 0.\n";
                        break;
                    }

                    cout << "Pilih Tempat duduk (1-50): " << endl;
                    for (int i = 0; i < jumlahTiket; ++i) {
                        int nomorTempatDuduk;
                        cin >> nomorTempatDuduk;

                        if (nomorTempatDuduk < 1 || nomorTempatDuduk > jumlahTempatDudukPerRuangan) {
                            cout << "Nomor tempat duduk tidak valid. Silakan pilih lagi.\n";
                            --i; 
                            continue;
                        }

                       
                        if (ketersediaanTempatDuduk[nomorFilm - 1][nomorTempatDuduk - 1]) {
                            ketersediaanTempatDuduk[nomorFilm - 1][nomorTempatDuduk - 1] = false;  
                        } else {
                            cout << "Tempat duduk telah terisi. Silakan pilih tempat duduk yang lain.\n";
                            --i;
                            continue;
                        }
                    }

                    double hargaTiket = 30.0000; 
                    double totalPembayaran = hargaTiket * jumlahTiket; 
                    bayar(totalPembayaran); 
                } else {
                    cout << "\nInput tidak valid. Silakan pilih lagi.\n";
                }
                break;
            }
            case 3:
                cout << "Terima kasih telah datang.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan pilih lagi.\n";
                break;
        }
    } while (pilihan != 3);

    return 0;
} 

