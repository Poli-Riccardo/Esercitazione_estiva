#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
struct Cliente {
    string nome , cognome;
    bool posto = false;
};
const int FILA = 5 , COLONNE = 11;
void menu (){
    cout<<"Scrivere 1 per inserire una nuova prenotazione "<<endl;
    cout<<"Scrivere 2 per mostrare la sala a schermo " <<endl;
    cout<<"Scrivere 3 per importare le prenotazioni precedenti " <<endl;
    cout<<"Scrivere 4 per eliminare delle prenotazioni " <<endl;
    cout<<"Scrivere 0 per uscire dal programma "<<endl;
}
void stampa_biglietto(int n ,int fila , int posto , string nome , string cognome){

    string nome_file="Biglietto_"+ to_string(n) ;
    ofstream out (nome_file);
    int spazi_esterni=4;
    int spazi_interni=16;
    for (int i = 0; i < spazi_esterni; ++i) {
        out<<" ";
    }
    for (int i = 0; i < 16; ++i) {
        out<<"_";
    }
    out<<endl;
    spazi_esterni-=1;
    for (int i = 0; i < spazi_esterni; ++i) {
        out<<" ";
    }
    out<<"/";
    for (int i = 0; i < spazi_interni ; ++i) {
        out<<" ";
    }
    out<<"\\"<<endl;
    spazi_esterni-=1;
    for (int i = 0; i < spazi_esterni; ++i) {
        out<<" ";
    }
    out<<"/";
    for (int i = 0; i < (spazi_interni/2)-2; ++i) {
        out<<" ";
    }
    out<<"Cinema";
    for (int i = 0; i < (spazi_interni/2)-2; ++i) {
        out<<" ";
    }
    out<<"\\"<<endl;
    spazi_esterni-=1;
    spazi_interni+=2;
    for (int i = 0; i < spazi_esterni; ++i) {
        out<<" ";
    }
    out<<"/";
    for (int i = 0; i < (spazi_interni/2)-3; ++i) {
        out<<" ";
    }
    out<<"Paradiso";
    for (int i = 0; i < (spazi_interni/2)-3; ++i) {
        out<<" ";
    }
    out<<"\\"<<endl;
    spazi_esterni-=1;
    spazi_interni+=2;
    out<<"/";
    out<<" ";
    out<<"Nome:";
    out<<nome;
    for (int i = 0; i <spazi_interni-4-nome.size(); ++i) {
        out<<" ";
    }
    out<<"\\"<<endl;
    for (int i = 0; i < spazi_esterni; ++i) {
        out<<" ";
    }
    out<<"\\";
    out<<" ";
    out<<"Cognome:";
    out<<cognome;
    for (int i = 0; i < spazi_interni-7-cognome.size(); ++i) {
        out<<" ";
    }
    out<<"/"<<endl;
    spazi_esterni+=1;
    spazi_interni-=2;
    for (int i = 0; i < spazi_esterni; ++i) {
        out<<" ";
    }
    out<<"\\";
    out<<" ";
    out<<"Fila:";
    out<<fila;
    for (int i = 0; i < spazi_interni-5; ++i) {
        out<<" ";
    }
    out<<"/"<<endl;
    spazi_esterni+=1;
    spazi_interni-=2;
    for (int i = 0; i < spazi_esterni; ++i) {
        out<<" ";
    }
    out<<"\\";
    out<<" ";
    out<<"Posto:";
    out<<posto;
    for (int i = 0; i < spazi_interni-6; ++i) {
        out<<" ";
    }
    out<<"/"<<endl;
    spazi_esterni+=1;
    spazi_interni-=2;
    for (int i = 0; i < spazi_esterni; ++i) {
        out<<" ";
    }
    out<<"\\";
    for (int i = 0; i < spazi_interni+2; ++i) {
        out<<"_";
    }
    out<<"/";
}
void elimina_prenotazione(Cliente prenotazione [FILA][COLONNE] ,ofstream &out ){
    string nome , cognome;
    bool presente=false;
    out.close();
    out.open("prenotazioni.txt",ios::out |ios::trunc);
    cout<<"Inserisci il nome del cliente che vuole annullare la prenotazione "<<endl;
    cin>>nome;
    cout<<"Inserisci il cognome del cliente che vuole annullare la prenotazione "<<endl;
    cin>>cognome;
    for (int i = 0; i < FILA; ++i) {
        for (int j = 0; j < COLONNE; ++j) {
            if (prenotazione[i][j].posto==true){
                if (prenotazione[i][j].nome!=nome ||prenotazione[i][j].cognome!=cognome ){
                    out << prenotazione[i][j].nome << ";" << prenotazione[i][j].cognome << ";" << i+1 << ";" << j+1
                        << ";" << endl;
                }
                else{
                    prenotazione[i][j].posto=false;
                    prenotazione[i][j].nome="";
                    prenotazione[i][j].cognome="";
                    presente= true;

                }
            }
        }
    }
    if (presente==true) cout<<"Annullamento eseguito con successo "<<endl;
    else cout<<"La persona inserita non e' presente!"<<endl;
}
int posti_cosigliati(Cliente prenotazione [FILA][COLONNE] , int &fila , int &posto) {
    int fila_posto_contrale = (FILA / 2) ;
    int colonna_posto_centrale = (COLONNE / 2) ;
    if (prenotazione[fila_posto_contrale][colonna_posto_centrale].posto == false) {
        fila=fila_posto_contrale;
        posto= colonna_posto_centrale;
        return 1;
    }
    else for (int j = 0; j < (COLONNE/4)+1; ++j) {
            for (int i = 0; i < (FILA/4)+1; ++i) {
                if (prenotazione[fila_posto_contrale+i][colonna_posto_centrale+j].posto == false) {
                    fila= fila_posto_contrale+i;
                    posto=colonna_posto_centrale+j;
                    return 1;
                }
                else if (prenotazione[fila_posto_contrale-i][colonna_posto_centrale+j].posto == false){

                    fila=fila_posto_contrale-i;
                    posto=colonna_posto_centrale+j;
                    return 1;
                }
            }

            for (int i = 0; i < (FILA / 4)+1; ++i) {
                if (prenotazione[fila_posto_contrale+i][colonna_posto_centrale-j].posto == false) {
                    fila = fila_posto_contrale+i;
                    posto=colonna_posto_centrale-j;
                    return 1;
                }
                else if (prenotazione[fila_posto_contrale-i][colonna_posto_centrale-j].posto == false){
                    fila=fila_posto_contrale-i;
                    posto=colonna_posto_centrale-j;
                    return 1;
                }
            }

        }
    return 0;
}
void aggiunta_prenotazione (Cliente prenotazione [FILA][COLONNE] ,ofstream &out){
    int fila , posto;
    bool occupato=true;
    int scelta;
    int n=0;
    for (int i = 0; i < FILA; ++i) {
        for (int j = 0; j < COLONNE; ++j) {
            if (prenotazione[i][j].posto==true){
                n++;
            }
        }
    }
    string nome , cognome;
    cout<<"Inserisci 0 se vuoi inserire il posto manualmente ,1 se vuoi che il posto venga inserito autamaticamente nei posti centrali, "
          "2 se vuoi fare una prenotazione multipla"<<endl;
    cin>>scelta;
    if (scelta==1){
        if (posti_cosigliati(prenotazione , fila , posto)==1){
            prenotazione[fila][posto].posto = true;
            cout<<"Inserisci il nome del cliente " <<endl;
            cin>>nome;
            prenotazione[fila][posto].nome=nome;
            cout<<"Inserisci il cognome del cliente " <<endl;
            cin>>cognome;
            prenotazione[fila][posto].cognome=cognome;
            out << prenotazione[fila][posto].nome << ";" << prenotazione[fila][posto].cognome << ";" << fila+1 << ";" << posto+1
                << ";" << endl;
            stampa_biglietto(n+1,fila+1,posto+1,nome,cognome);
            cout<<"Prenotazione eseguita con successo "<<endl;
        }
        else cout<<"Posti centrali non piu' disponibili"<<endl;
    }
    else if (scelta==0){
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
        cin>>nome;
        prenotazione[fila][posto].nome=nome;
        cout<<"Inserisci il cognome del cliente " <<endl;
        cin>>cognome;
        prenotazione[fila][posto].cognome=cognome;
        out << prenotazione[fila][posto].nome << ";" << prenotazione[fila][posto].cognome << ";" << fila+1 << ";" << posto+1
            << ";" << endl;
        stampa_biglietto(n+1,fila+1,posto+1,nome,cognome);
        cout<<"Prenotazione eseguita con successo "<<endl;
    }
    else if (scelta==2){
        string nome , cognome;
        int posto_iniziale , posto_finale;
        cout<<"Inserisci la fila"<<endl;
        cin>>fila;
        fila-=1;
        cout<<"Inserisci da che posto a che posto vuoi prenotare"<<endl;
        cin>>posto_iniziale>>posto_finale;
        posto_iniziale-=1;
        posto_finale-=1;
        cout<<"inserisci il nome"<<endl;
        cin>>nome;
        cout<<"inserisci il cognome "<<endl;
        cin>>cognome;
        occupato=false;
        for (int i = 0; i < (posto_finale-posto_iniziale)+1; ++i) {
            if (prenotazione[fila][posto_iniziale+i].posto == true){
                cout<<"Il posto "<<posto_iniziale+i<<" e' gia' occupato!"<<endl;
                occupato=true;
            }
        }
        if (occupato==false ){
            for (int i = 0; i < (posto_finale-posto_iniziale)+1; ++i) {
                n+=1;
                prenotazione[fila][posto_iniziale+i].posto =true;
                prenotazione[fila][posto_iniziale+i].nome = nome;
                prenotazione[fila][posto_iniziale+i].cognome=cognome;
                out << prenotazione[fila][posto_iniziale+i].nome << ";" << prenotazione[fila][posto_iniziale+i].cognome << ";" << fila+1 << ";" << posto_iniziale+i+1
                    << ";" << endl;
                stampa_biglietto(n,fila+1,posto_iniziale+i+1,nome,cognome);


            }
        }


        cout<<"Prenotazione eseguita con successo "<<endl;
    }
    else cout<<"Scelta non valida"<<endl;
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
void importa_prenotazioni (Cliente prenotazione [FILA][COLONNE] , ifstream &in ,ofstream &out ){
    string riga, nome , cognome;
    int fila , posto , pos;
    int n=0;
    while(getline(in,riga)){
        for (int i = 0; i < FILA; ++i) {
            for (int j = 0; j < COLONNE; ++j) {
                if (prenotazione[i][j].posto==true){
                    n++;
                }
            }
        }
        pos=riga.find(';');
        nome=riga.substr(0,pos);
        riga.erase(0,nome.size()+1);
        pos=riga.find(';');
        cognome=riga.substr(0,pos);
        riga.erase(0,cognome.size()+1);
        pos=riga.find(';');
        fila= stoi(riga.substr(0,pos))-1;
        riga.erase(0,pos+1);
        pos=riga.find(';');
        posto= stoi(riga.substr(0,pos))-1;
        prenotazione[fila][posto].nome=nome;
        prenotazione[fila][posto].cognome=cognome;
        prenotazione[fila][posto].posto=true;
        out << prenotazione[fila][posto].nome << ";" << prenotazione[fila][posto].cognome << ";" << fila+1 << ";" << posto+1
            << ";" << endl;
        stampa_biglietto(n+1,fila+1,posto+1,nome,cognome);

    }
}

int main() {
    Cliente posti [FILA][COLONNE];
    ofstream out ("prenotazioni.txt");
    ifstream in ("prenotazioni_precedenti.txt");
    if (!out){
        cout<<"Errore nella creazione del file " <<endl;
        return 1;
    }
    int scelta=5;
    while (scelta!=0){
        cout<<endl;
        menu();
        cin>>scelta;
        if (scelta==1) aggiunta_prenotazione(posti , out);
        else if (scelta==2) mostra_prenotazioni(posti);
        else if (scelta==3) {
            if(!in){
                cout<<"Errore nell'apertura del file "<<endl;
                return 1;
            }
            importa_prenotazioni(posti,in , out);
        }
        else if (scelta==4) elimina_prenotazione(posti , out);
        else if (scelta!=0) cout<<"Scelta non valida! "<<endl;
    }
    in.close();
    remove("prenotazioni_precedenti.txt");
    out.close();
    rename("prenotazioni.txt","prenotazioni_precedenti.txt");
    return 0;
}