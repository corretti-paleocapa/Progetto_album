#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include<ctime>
#include<cstdlib>
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

void stampascelta(){
    cout<<"COLLEZIONE DEI TUOI ALBUM MUSICALI: COSA VUOI FARE?"<<endl;
    cout<<"1.Visualizzare e cercare i tuoi album"<<endl;
    cout<<"2.aggiungere degli album nuovi"<<endl;
    cout<<"SELEZIONA UN'OPZIONE"<<endl;
}

album inserisci(album inserimento){
    cout<<"inserisci il titolo dell'album: ";
    cin>> inserimento.titolo;
    cout<<"inserisci artista o band: ";
    cin>> inserimento.artista;
    cout<<"inserisci il genere musicale: ";
    cin>> inserimento.genere;
    cout<<"inserisci il formato dell'album: ";
    cin>> inserimento.formato;
    cout<<"inserisci l'anno di uscita dell'album: ";
    cin>> inserimento.anno;
    cout<<"inserisci il numero di tracce dell'album: ";
    cin>> inserimento.num_tracce;
    cout<<"inserisci un voto personale: ";
    cin>> inserimento.voto;
    cout<<endl;
    return inserimento;

}

void inserisci_album(int quanti_album,  vector<album>& ALBUM, album inserimento){
    for(int i=0; i < quanti_album; i++){
            ALBUM.push_back(inserisci(inserimento));
    }
}

int assegnaID(vector<album>& ALBUM)
{
    srand(time(0));
    ifstream file_id_lettura("id.txt");
    if (!file_id_lettura.is_open()) {
        cout << "Errore: impossibile leggere id.txt" << endl;
        return 1; // void, non ritorna alcun valore
    }
    
    int id;
    int num_album;
    
    // Legge entrambi i numeri in sequenza dal file
    file_id_lettura >> id;
    file_id_lettura >> num_album;
    file_id_lettura.close();
    
    int partenza = num_album;
    // Il ciclo scorre tutti gli album inseriti nel vettore e assegna i nuovi ID
    for (int i = 0; i < ALBUM.size(); i++)
    {
        id += (rand() % 10) + 1;
        ALBUM[i].id = id;
        num_album ++;
    }
    
    ofstream file_id_scrittura("id.txt");
    if (!file_id_scrittura.is_open()) {
        cout << "Errore: impossibile scrivere su id.txt" << endl;
        return 0;
    }
    
    // Riscrive entrambi i valori aggiornati, separati da uno spazio
    file_id_scrittura << id << " " << num_album;
    file_id_scrittura.close();
    return partenza;
}


void menuVisualizzaERicerca()
{
    cout<<"1. Lista completa della collezione, ordinata per artista"<<endl;
    cout<<"2. Ricerca di un album per titolo, artista o ID"<<endl;
    cout<<"3. Filtro per genere musicale o per formato"<<endl;
    cout<<"4. Tutti gli album di un determinato artista"<<endl;
    cout<<"5. Top 5 album"<<endl;                   //con il voto più alto

    cout<<"6. Modifica un album"<<endl;             //(tramite ID), chiedere conferma
    cout<<"7. Rimuovi un album"<<endl;             //(tramite ID), chiedere conferma

    cout<<"SELEZIONA UN SERVIZIO ";
}

/**/int sceltaServizio(int servizio)
{
    do
    {
        cin>> servizio;
    }while(servizio < 1 || servizio > 7);

    switch (servizio)
    {
        case 1:
            break
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break
        case 6:
            break
        case 7:
            break;
        default:
            return 0;
    }
}

int main() {

    stampascelta();
    int scelta;
    cin>>scelta;
    if(scelta == 1){
        ifstream file("collezione.txt");
        if (!file.is_open()) {
            cout << "Errore: impossibile leggere collezione.txt" << endl;
            cout<<"Prima devi creare la tua lista "<<"⬇"<<"\n\n";
            goto creazionealbum;
        }

        string controllo; 
        file >> controllo; 
        if (controllo.empty() || controllo == "VUOTO") {
            cout << "Prima devi creare la tua lista \x1b[31m\u2193\x1b[0m \n\n"; 
            goto creazionealbum; 
        }



        
    }
    else{
            creazionealbum:
            ofstream file("collezione.txt", ios::app);
            if (!file.is_open()) {
                cout << "Errore: impossibile modificare collezione.txt" << endl;
                return 1;
            }
            vector<album> ALBUM;
            album inserimento;
            int quanti_album;
            cout<<"Quanti album vuoi inserire?"<<endl;
            cin>>quanti_album;

            inserisci_album(quanti_album, ALBUM, inserimento);

            int posizione = assegnaID(ALBUM);
            
            for(int i=0;i < ALBUM.size(); i++){
                    posizione++;
                    file<<"Album n°"<<posizione<<"\n";
                    file<<"ID: "<<ALBUM[i].id<<"|";
                    file<<"Titolo: "<<ALBUM[i].titolo<<"|";
                    file<<"Artista/band: "<<ALBUM[i].artista<<"|";
                    file<<"Genere: "<<ALBUM[i].genere<<"|";
                    file<<"Anno: "<<ALBUM[i].anno<<"|";
                    file<<"Numero tracce: "<<ALBUM[i].num_tracce<<"|";
                    file<<"Formato: "<<ALBUM[i].formato<<"|";
                    file<<"Voto personale: "<<ALBUM[i].voto;
                    file<<"\n\n";
            }
            file.close();
    }
    /*
    ifstream file("libri.txt");
    if (!file.is_open()) {
        cout << "Errore: impossibile aprire il file libri.txt" << endl;
        return 1;
    }
    vector<Libro> libri;

    string riga;
    while (getline(file, riga)) {
        istringstream ss(riga);

        string titolo, autore, anno, prezzo, copie;

        getline(ss, titolo, '|');
        getline(ss, autore, '|');
        getline(ss, anno, '|');
        getline(ss, prezzo, '|');
        getline(ss, copie, '|');

        Libro l;
        l.titolo = titolo;
        l.autore = autore;
        l.anno = stoi(anno);
        l.prezzo = stod(prezzo);
        l.copie = stoi(copie);

        libri.push_back(l);
    }

    file.close();
    */
    return 0;
}