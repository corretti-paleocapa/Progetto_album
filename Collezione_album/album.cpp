#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

struct album {
    int id;
    string titolo;
    string artista;
    string genere;
    int anno;
    int num_tracce;
    string formato;
    int voto;
};

void stampascelta() {
    cout << "COLLEZIONE DEI TUOI ALBUM MUSICALI: COSA VUOI FARE?" << endl;
    cout << "1. Visualizzare e cercare i tuoi album" << endl;
    cout << "2. Aggiungere degli album nuovi" << endl;
    cout << "SELEZIONA UN'OPZIONE" << endl;
}

album inserisci(album inserimento) {

    cin.ignore();

    cout << "Inserisci il titolo dell'album: ";
    getline(cin, inserimento.titolo);

    cout << "Inserisci artista o band: ";
    getline(cin, inserimento.artista);

    cout << "Inserisci il genere musicale: ";
    getline(cin, inserimento.genere);

    cout << "Inserisci il formato dell'album: ";
    getline(cin, inserimento.formato);

    cout << "Inserisci l'anno di uscita dell'album: ";
    cin >> inserimento.anno;

    cout << "Inserisci il numero di tracce dell'album: ";
    cin >> inserimento.num_tracce;

    cout << "Inserisci un voto personale (1-10): ";
    cin >> inserimento.voto;

    cout << endl;

    return inserimento;
}

void inserisci_album(int quanti_album, vector<album>& ALBUM, album inserimento) {

    for (int i = 0; i < quanti_album; i++) {
        cout << "\nALBUM N° " << i + 1 << "\n";
        ALBUM.push_back(inserisci(inserimento));
    }
}

int assegnaID(vector<album>& ALBUM) {

    srand(time(0));

    ifstream file_id_lettura("id.txt");

    int id = 1000;
    int num_album = 0;

    if (file_id_lettura.is_open()) {

        file_id_lettura >> id;
        file_id_lettura >> num_album;
        file_id_lettura.close();
    }

    int partenza = num_album;

    for (int i = 0; i < ALBUM.size(); i++) {

        id += (rand() % 10) + 1;

        ALBUM[i].id = id;

        num_album++;
    }

    ofstream file_id_scrittura("id.txt");

    if (!file_id_scrittura.is_open()) {

        cout << "Errore: impossibile scrivere su id.txt" << endl;

        return 0;
    }

    file_id_scrittura << id << " " << num_album;

    file_id_scrittura.close();

    return partenza;
}

void menuVisualizzaERicerca() {

    cout<< "\nMENU:" << endl;
    cout<<"1. Lista completa della collezione, ordinata per artista" << endl;
    cout<<"2. Ricerca di un album per titolo, artista o ID" << endl;
    cout<<"3. Filtro per genere musicale o formato" << endl;
    cout<<"4. Tutti gli album di un determinato artista" << endl;
    cout<<"5. Top 5 album" << endl;
    cout<<"6. Modifica un album" << endl;
    cout<<"7. Rimuovi un album" << endl;
    cout<<"8. Aggiungi album"<<endl;
    cout<<"9. Chiudi programma"<<endl;
    cout<<"SELEZIONA UN SERVIZIO: ";
}

void leggiAlbum(vector<album>& lettura) {

    ifstream file("collezione.txt");
    if (!file.is_open()) {
        cout << "Errore apertura file.\n";
        return;
    }

    string riga;

    while (getline(file, riga)) {

        if (riga.find("ID:") == string::npos)
            continue;

        album a;
        string campo;
        stringstream ss(riga);

        auto leggiCampo = [](string& campo) -> string {
            size_t p = campo.find(':');
            return campo.substr(p + 1);
        };

        // ID
        getline(ss, campo, '|');
        a.id = stoi(leggiCampo(campo));

        // Titolo
        getline(ss, campo, '|');
        a.titolo = leggiCampo(campo);

        // Artista
        getline(ss, campo, '|');
        a.artista = leggiCampo(campo);

        // Genere
        getline(ss, campo, '|');
        a.genere = leggiCampo(campo);

        // Anno
        getline(ss, campo, '|');
        a.anno = stoi(leggiCampo(campo));

        // Tracce
        getline(ss, campo, '|');
        a.num_tracce = stoi(leggiCampo(campo));

        // Formato
        getline(ss, campo, '|');
        a.formato = leggiCampo(campo);

        // Voto
        getline(ss, campo);
        a.voto = stoi(leggiCampo(campo));

        lettura.push_back(a);
    }

    file.close();
}

void mostraAlbum(album a) {

    cout << "\nID: " << a.id << endl;
    cout << "Titolo: " << a.titolo << endl;
    cout << "Artista: " << a.artista << endl;
    cout << "Genere: " << a.genere << endl;
    cout << "Anno: " << a.anno << endl;
    cout << "Numero tracce: " << a.num_tracce << endl;
    cout << "Formato: " << a.formato << endl;
    cout << "Voto: " << a.voto << endl;
}

void lista_completa(vector<album>& lettura) {

    sort(lettura.begin(), lettura.end(),

    [](album a, album b) {

        return a.artista < b.artista;
    });

    for (int i = 0; i < lettura.size(); i++) {

        mostraAlbum(lettura[i]);
    }
}

void ricercaAlbum(vector<album>& lettura) {

    cin.ignore();

    string ricerca;

    cout << "Inserisci titolo, artista o ID: ";

    getline(cin, ricerca);

    for (int i = 0; i < lettura.size(); i++) {

        if (lettura[i].titolo == ricerca ||
            lettura[i].artista == ricerca ||
            to_string(lettura[i].id) == ricerca) {

            mostraAlbum(lettura[i]);
        }
    }
}

void filtro(vector<album>& lettura) {

    cin.ignore();

    string filtro;

    cout << "Inserisci genere o formato: ";

    getline(cin, filtro);

    for (int i = 0; i < lettura.size(); i++) {

        if (lettura[i].genere == filtro ||
            lettura[i].formato == filtro) {

            mostraAlbum(lettura[i]);
        }
    }
}

void albumArtista(vector<album>& lettura) {

    cin.ignore();

    string artista;

    cout << "Inserisci artista: ";

    getline(cin, artista);

    for (int i = 0; i < lettura.size(); i++) {

        if (lettura[i].artista == artista) {

            mostraAlbum(lettura[i]);
        }
    }
}

void top5(vector<album>& lettura) {

    sort(lettura.begin(), lettura.end(),

    [](album a, album b) {

        return a.voto > b.voto;
    });

    int limite;

    if (lettura.size() < 5)
        limite = lettura.size();
    else
        limite = 5;

    for (int i = 0; i < limite; i++) {

        mostraAlbum(lettura[i]);
    }
}

void salvaFile(vector<album>& lettura) {

    ofstream file("collezione.txt");

    for (int i = 0; i < lettura.size(); i++) {

        file << "Album n°" << i + 1 << "\n";
        file << "ID: " << lettura[i].id << "|";
        file << "Titolo: " << lettura[i].titolo << "|";
        file << "Artista/band: " << lettura[i].artista << "|";
        file << "Genere: " << lettura[i].genere << "|";
        file << "Anno: " << lettura[i].anno << "|";
        file << "Numero tracce: " << lettura[i].num_tracce << "|";
        file << "Formato: " << lettura[i].formato << "|";
        file << "Voto personale: " << lettura[i].voto;

        file << "\n\n";
    }

    file.close();
}

void modificaAlbum(vector<album>& lettura) {

    int id;

    cout << "Inserisci ID album da modificare: ";

    cin >> id;

    for (int i = 0; i < lettura.size(); i++) {

        if (lettura[i].id == id) {

            cout << "Album trovato.\n";

            lettura[i] = inserisci(lettura[i]);

            lettura[i].id = id;

            salvaFile(lettura);

            cout << "Album modificato.\n";

            return;
        }
    }

    cout << "Album non trovato.\n";
}

void eliminaAlbum(vector<album>& lettura) {

    int id;

    cout << "Inserisci ID album da eliminare: ";

    cin >> id;

    for (int i = 0; i < lettura.size(); i++) {

        if (lettura[i].id == id) {

            lettura.erase(lettura.begin() + i);

            salvaFile(lettura);

            cout << "Album eliminato.\n";

            return;
        }
    }

    cout << "Album non trovato.\n";
}

int main() {

    stampascelta();

    int scelta;

    cin >> scelta;

    if (scelta == 1) {

        ifstream file("collezione.txt");

        if (!file.is_open()) {

            cout << "Errore: impossibile leggere collezione.txt" << endl;
            cout << "Prima devi creare la tua lista\n";

            goto creazionealbum;
        }

        vector<album> lettura;

        leggiAlbum(lettura);

        int servizio;
        do {
            menuVisualizzaERicerca();
            cin >> servizio;
            switch (servizio) {

                case 1:
                    lista_completa(lettura);
                    break;

                case 2:
                    ricercaAlbum(lettura);
                    break;

                case 3:
                    filtro(lettura);
                    break;

                case 4:
                    albumArtista(lettura);
                    break;

                case 5:
                    top5(lettura);
                    break;

                case 6:
                    modificaAlbum(lettura);
                    break;

                case 7:
                    eliminaAlbum(lettura);
                    break;

                case 8:
                    goto creazionealbum;
                    break;
                default:
                    break;
            }
        } while(servizio >= 1 && servizio <=8);
    }

    else {

        creazionealbum:

        ofstream file("collezione.txt", ios::app);

        if (!file.is_open()) {

            cout << "Errore: impossibile modificare collezione.txt" << endl;

            return 1;
        }

        vector<album> ALBUM;
        album inserimento;
        int quanti_album;
        cout << "Quanti album vuoi inserire?" << endl;
        cin >> quanti_album;

        inserisci_album(quanti_album, ALBUM, inserimento);

        int posizione = assegnaID(ALBUM);

        for (int i = 0; i < ALBUM.size(); i++) {

            posizione++;

            file << "Album n°" << posizione << "\n";

            file << "ID: " << ALBUM[i].id << "|";
            file << "Titolo: " << ALBUM[i].titolo << "|";
            file << "Artista/band: " << ALBUM[i].artista << "|";
            file << "Genere: " << ALBUM[i].genere << "|";
            file << "Anno: " << ALBUM[i].anno << "|";
            file << "Numero tracce: " << ALBUM[i].num_tracce << "|";
            file << "Formato: " << ALBUM[i].formato << "|";
            file << "Voto personale: " << ALBUM[i].voto;

            file << "\n\n";
        }

        file.close();

        cout << "\nAlbum salvati correttamente!\n";
    }

    return 0;
}