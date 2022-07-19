#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
struct Cliente {
    string nome , cognome;
    bool posto = false;
};
const int FILA = 5 , COLONNE = 9;
void menu (){
    cout<<"Scrivere 1 per inserire una nuova prenotazione "<<endl;
    cout<<"Scrivere 2 per mostrare la sala a schermo " <<endl;
    cout<<"Scrivere 3 per importare le prenotazioni precedenti " <<endl;
    cout<<"Scrivere 0 per uscire dal programma "<<endl;
}

void aggiunta_prenotazione (Cliente prenotazione [FILA][COLONNE] ,ofstream &out){
    int fila , posto;
    bool occupato=true;
    cout<<"inserisci la fila " <<endl;
    do {
        cin>>fila;
        fila-=1;
        for (int i = 0; i < COLONNE; ++i) {
            if (prenotazione [fila][i].posto==false) occupato=false;
        }
        if (occupato== true) cout<<"La fila è tutta occupata , prova con un altra fila " <<endl;
    } while (occupato ==true);
    occupato=true;
    cout<<"inserisci il posto "<<endl;
    do {
        cin>>posto;
        posto-=1;
        if (prenotazione [fila][posto].posto == false) occupato=false;
        if (occupato==true) cout<<"Il posto e' occupato provane un altro"<<endl;
    } while (occupato== true);
    prenotazione[fila][posto].posto = true;
    cout<<"Inserisci il nome del cliente " <<endl;
    cin>>prenotazione[fila][posto].nome;
    cout<<"Inserisci il cognome del cliente " <<endl;
    cin>>prenotazione[fila][posto].cognome;
  out << prenotazione[fila][posto].nome << ";" << prenotazione[fila][posto].cognome << ";" << fila << ";" << posto
       << ";" << endl;
}
void mostra_prenotazioni (Cliente prenotazione [FILA][COLONNE]){
    cout<<"Le O indicano posto vuoto , Le X indicano posto occupato :"<<endl<<endl;
    for (int i = 0; i < FILA ; ++i) {
        cout<<" ";
        for (int j = 0; j < COLONNE; ++j) {
            if (prenotazione[i][j].posto == false ) cout<<"O";
            else cout<<"X";
        }
    cout<<endl;
    }
    cout<<endl<<endl;
}
void importa_prenotazioni (Cliente prenotazione [FILA][COLONNE] , ifstream &in ){
    string riga;
    int fila , posto , pos;
    while(getline(in,riga)){
        pos=riga.find(';');
        fila= stoi(riga.substr(0,pos));
        riga.erase(0,fila+1);
        pos=riga.find(';');
        posto= stoi(riga.substr(0,pos));
        riga.erase(0,posto+1);
        pos=riga.find(';');
        prenotazione[fila][posto].nome=riga.substr(0,pos);
        riga.erase(0,prenotazione[fila][posto].nome.size()+1);
        pos=riga.find(';');
        prenotazione[fila][posto].cognome=riga.substr(0,pos);
        prenotazione[fila][posto].posto=true;
    }
}
int main() {
    Cliente posti [FILA][COLONNE];
    ofstream out ("Prenotazioni.txt");
    ifstream in ("Prenotazioni_precedenti.txt");
    if (!out){
        cout<<"Errore nella creazione del file " <<endl;
        return 1;
    }
    int scelta=5;
    while (scelta!=0){
        menu();
        cin>>scelta;
        if (scelta==1) aggiunta_prenotazione(posti , out);
        else if (scelta==2) mostra_prenotazioni(posti);
        else if (scelta==3) {
            if(!in){
                cout<<"Errore nell'apertura del file "<<endl;
                return 1;
            }
            importa_prenotazioni(posti,in);
        }

    }
    return 0;
}
