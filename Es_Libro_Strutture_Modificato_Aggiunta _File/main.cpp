#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;
struct Voti {
    float matematica, italiano , inglese;
};
struct  Studente {
    string nome , sesso;
    string anno_nascita;
    Voti  voti;
};
string scomponimento_riga(string s ) {
    int pos=s.find(';');
    return s.substr(0,pos);
}
void disciplina_media_piu_elevata(Studente alunni[] , int n , ofstream &Out){
    float media_matematica=0 , media_italiano=0 , media_inglese=0;
    for (int i = 0; i < n; ++i) {
        media_matematica+=alunni[i].voti.matematica;
        media_italiano+=alunni[i].voti.italiano;
        media_inglese+=alunni[i].voti.inglese;
    }
    media_matematica/=n;
    media_italiano/=n;
    media_inglese/=n;
    if (media_matematica>media_inglese && media_matematica>media_italiano)
        Out<<"la media dei voti piu' elevata e' "<<media_matematica<<" ed e' della disciplina matematica "<<endl;
    else if (media_italiano>media_inglese)
        Out<<"la media dei voti piu' elevata e' "<<media_italiano<<" ed e' della disciplina italiano "<<endl;
    else Out<<"la media dei voti piu' elevata e' "<<media_inglese<<" ed e' della disciplina inglese "<<endl;
}
void voto_piu_alto(Studente alunni[] , int n , ofstream &Out ){
    float voto_max = alunni[0].voti.matematica;
    for (int i = 0; i < n; ++i) {
        if (alunni[i].voti.matematica>voto_max) voto_max=alunni[i].voti.matematica;
        if (alunni[i].voti.inglese>voto_max) voto_max=alunni[i].voti.inglese;
        if (alunni[i].voti.italiano>voto_max) voto_max=alunni[i].voti.italiano;
    }
    Out<<"Gli alunni con il voto piu' alto sono: "<<endl;
    for (int i = 0; i < n; ++i)
        if (alunni[i].voti.matematica==voto_max || alunni[i].voti.italiano==voto_max || alunni[i].voti.inglese==voto_max ) Out<<alunni[i].nome<<endl;
}
int main() {
    ifstream In("Registro_Alunni.txt");
    if(!In ){
        cout<<"Errore nella apertura del file"<<endl;
        return 1;
    }
    const int N_STUDENTI_MAX = 30;
    int n_studenti=0;

    Studente alunni[N_STUDENTI_MAX];
    string riga;
    while (getline(In,riga) && n_studenti<30 ){
        alunni[n_studenti].nome = scomponimento_riga(riga);
        riga.erase(0 ,alunni[n_studenti].nome.size()+1);
        alunni[n_studenti].anno_nascita =scomponimento_riga(riga);
        riga.erase(0 ,alunni[n_studenti].anno_nascita.size()+1);
        alunni[n_studenti].sesso =scomponimento_riga(riga);
        riga.erase(0 ,alunni[n_studenti].sesso.size()+1);
        alunni[n_studenti].voti.matematica =stof(scomponimento_riga(riga));
        riga.erase(0 ,2);
        alunni[n_studenti].voti.inglese =stof(scomponimento_riga(riga));
        riga.erase(0 ,2);
        alunni[n_studenti].voti.italiano =stof(scomponimento_riga(riga));
        n_studenti++;
        if (n_studenti==30) cout<<"il numero di studenti ha superato il massimo (30) "<<endl;
    }
    In.close();
    ofstream Out("Votazioni.txt");
    if(!Out ){
        cout<<"Errore nella creazione del file"<<endl;
        return 1;
    }
    voto_piu_alto(alunni , n_studenti , Out);
    disciplina_media_piu_elevata(alunni , n_studenti , Out);
    Out.close();
    return 0;
}
