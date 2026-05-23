#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <limits>

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

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do {
        cout << "Inserisci il titolo dell'album: ";
        getline(cin, inserimento.titolo);

        if (inserimento.titolo.empty())
            cout << "Errore: il titolo non può essere vuoto.\n";

    } while (inserimento.titolo.empty());

    do {
        cout << "Inserisci artista o band: ";
        getline(cin, inserimento.artista);

        if (inserimento.artista.empty())
            cout << "Errore: l'artista non può essere vuoto.\n";

    } while (inserimento.artista.empty());

    do {
        cout << "Inserisci il genere musicale: ";
        getline(cin, inserimento.genere);

        if (inserimento.genere.empty())
            cout << "Errore: il genere non può essere vuoto.\n";

    } while (inserimento.genere.empty());

    do {
        cout << "Inserisci il formato dell'album (CD, vinile, digitale, Cassetta): ";
        getline(cin, inserimento.formato);

        if (inserimento.formato.empty())
            cout << "Errore: il formato non può essere vuoto.\n";

    } while (inserimento.formato.empty());

    do {
        cout << "Inserisci l'anno di uscita dell'album (1900-2100): ";

        cin >> inserimento.anno;

        if (cin.fail() || inserimento.anno < 1900 || inserimento.anno > 2026) {
            cout << "Errore: anno non valido.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    } while (inserimento.anno < 1900 || inserimento.anno > 2026);

    do {
        cout << "Inserisci il numero di tracce (>0): ";
        cin >> inserimento.num_tracce;

        if (cin.fail() || inserimento.num_tracce <= 0) {
            cout << "Errore: numero non valido.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    } while (inserimento.num_tracce <= 0);

    do {
        cout << "Inserisci un voto personale (1-10): ";
        cin >> inserimento.voto;

        if (cin.fail() || inserimento.voto < 1 || inserimento.voto > 10) {
            cout << "Errore: voto non valido.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    } while (inserimento.voto < 1 || inserimento.voto > 10);

    cout << endl;

    return inserimento;
}

void inserisci_album(int quanti_album, vector<album>& ALBUM, album inserimento) {

    for (int i = 0; i < quanti_album; i++) {
        cout << "\nALBUM N° " << i + 1 << "\n";
        ALBUM.push_back(inserisci(inserimento));
    }
}

void assegnaID(vector<album>& ALBUM) {

    ifstream file_id_lettura("id.txt");

    int id=1000;

    if (file_id_lettura.is_open()) {

        file_id_lettura >> id;
        file_id_lettura.close();
    }

    for (int i = 0; i < ALBUM.size(); i++) {

        id += (rand() % 10) + 1;
        ALBUM[i].id = id;
    }

    ofstream file_id_scrittura("id.txt");

    if (!file_id_scrittura.is_open()) {

        cout << "Errore: impossibile scrivere su id.txt" << endl;
        return;
    }

    file_id_scrittura << id;
    file_id_scrittura.close();
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
        cout << "Nessuna lista oppure Errore apertura file.\n";
        return;
    }

    string riga;

    while (getline(file, riga)) {

        if (riga.find("ID:") == string::npos)
            continue;

        album a;
        string campo;
        stringstream ss(riga);

        auto leggiCampo = [](string campo) -> string {
            size_t p = campo.find(':');
            string res = campo.substr(p + 1);

            // elimina spazi iniziali
            while (!res.empty() && res[0] == ' ')
                res.erase(0, 1);

            return res;
        };

        getline(ss, campo, '|');
        a.id = stoi(leggiCampo(campo));

        getline(ss, campo, '|');
        a.titolo = leggiCampo(campo);

        getline(ss, campo, '|');
        a.artista = leggiCampo(campo);

        getline(ss, campo, '|');
        a.genere = leggiCampo(campo);

        getline(ss, campo, '|');
        a.anno = stoi(leggiCampo(campo));

        getline(ss, campo, '|');
        a.num_tracce = stoi(leggiCampo(campo));

        getline(ss, campo, '|');
        a.formato = leggiCampo(campo);

        getline(ss, campo);
        a.voto = stoi(leggiCampo(campo));

        lettura.push_back(a);
    }

    file.close();
}

void mostraAlbum(album a) {
    cout << "\nID: " << a.id << "|";
    cout << "Titolo: " << a.titolo << "|";
    cout << "Artista/band: " << a.artista << "|";
    cout << "Genere: " << a.genere << "|";
    cout << "Anno: " << a.anno << "|";
    cout << "Numero tracce: " << a.num_tracce << "|";
    cout << "Formato: " << a.formato << "|";
    cout << "Voto personale: " << a.voto << endl;
}

void lista_completa(vector<album> lettura) {

    sort(lettura.begin(), lettura.end(),

    [](album a, album b) {

        return a.artista < b.artista;
    });

    for (int i = 0; i < lettura.size(); i++) {

            cout<<"Album n° "<<i+1;
            mostraAlbum(lettura[i]);
            cout<<endl;

    }
}

void ricercaAlbum(vector<album>& lettura) {

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string ricerca;
    cout << "Inserisci titolo, artista o ID: ";
    getline(cin, ricerca);

    for (int i = 0; i < lettura.size(); i++) {

        if (lettura[i].titolo == ricerca || lettura[i].artista == ricerca || to_string(lettura[i].id) == ricerca) {

            cout<<"Album n° "<<i+1;
            mostraAlbum(lettura[i]);
            cout<<endl;

        }
    }
}

void filtro(vector<album>& lettura) {

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string filtro;
    cout << "Inserisci genere o formato: ";
    getline(cin, filtro);

    for (int i = 0; i < lettura.size(); i++) {

        if (lettura[i].genere == filtro || lettura[i].formato == filtro) {

            cout<<"Album n° "<<i+1;
            mostraAlbum(lettura[i]);
            cout<<endl;

        }
    }
}

void albumArtista(vector<album>& lettura) {

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string artista;
    cout << "Inserisci artista: ";
    getline(cin, artista);

    for (int i = 0; i < lettura.size(); i++) {

        if (lettura[i].artista == artista) {

            cout<<"Album n° "<<i+1;
            mostraAlbum(lettura[i]);
            cout<<endl;
        }
    }
}

void top5(vector<album> lettura) {

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

        cout<<"Album n° "<<i+1;
        mostraAlbum(lettura[i]);
        cout<<endl;
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

void aggiungiAlbum() {

    vector<album> lettura;
    leggiAlbum(lettura);
    vector<album> nuovi;
    album inserimento;

    int quanti_album;
    cout << "Quanti album vuoi inserire?" << endl;
    cin >> quanti_album;

    inserisci_album(quanti_album, nuovi, inserimento);

    assegnaID(nuovi);

    for (int i = 0; i < nuovi.size(); i++) {

        lettura.push_back(nuovi[i]);
    }

    salvaFile(lettura);

    cout << "\nAlbum salvati correttamente\n";
}

int main() {

    srand(time(0));

    bool programma = true;

    while (programma) {

        stampascelta();
        int scelta;
        cin >> scelta;

        if (scelta == 1) {

            ifstream file("collezione.txt");

            if (!file.is_open()) {

                cout << "Errore: impossibile leggere collezione.txt" << endl;
                cout << "PRIMA DEVI CREARE LA TUA LISTA-->INSERISCI 2\n\n";

                continue;
            }

            vector<album> lettura;

            leggiAlbum(lettura);

            int servizio;

            do {

                menuVisualizzaERicerca();
                cin >> servizio;
                cout<<endl;

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
                        aggiungiAlbum();
                        leggiAlbum(lettura);
                        break;

                    case 9:
                        programma = false;
                        break;

                    default:
                        break;
                }

            } while(servizio >= 1 && servizio <= 8);
        }

        else if (scelta == 2) {

            aggiungiAlbum();
        }
    }

    return 0;
}
