#include <iostream>
using namespace std;
struct Voti {
    float matematica, italiano , inglese;
};
struct  Studente {
    string nome , sesso;
    int anno_nascita;
    Voti  voti;
};
void disciplina_media_piu_elevata(Studente alunni[] , int n){
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
        cout<<"la media dei voti piu' elevata e' "<<media_matematica<<" ed e' della disciplina matematica "<<endl;
    else if (media_italiano>media_inglese)
        cout<<"la media dei voti piu' elevata e' "<<media_italiano<<" ed e' della disciplina italiano "<<endl;
    else cout<<"la media dei voti piu' elevata e' "<<media_inglese<<" ed e' della disciplina inglese "<<endl;
}
void inserisci_alunno(Studente alunno[] , int n ){
    cout<<"Inserisci il nome dell'alunno: "<<endl;
    cin>>alunno[n].nome;
    cout<<"Inserisci l'anno di nascita dell'alunno: "<<endl;
    cin>>alunno[n].anno_nascita;
    cout<<"Inserisci il sesso dell'alunno: "<<endl;
    cin>>alunno[n].sesso;
    cout<<"Inserisci il voto in Italiano: "<<endl;
    cin>>alunno[n].voti.italiano;
    cout<<"Inserisci il voto in Inglese: "<<endl;
    cin>>alunno[n].voti.inglese;
    cout<<"Inserisci il voto in Matematica: "<<endl;
    cin>>alunno[n].voti.matematica;
}
void voto_piu_alto(Studente alunni[] , int n ){
  float voto_max = alunni[0].voti.matematica;
    for (int i = 0; i < n; ++i) {
        if (alunni[i].voti.matematica>voto_max) voto_max=alunni[i].voti.matematica;
        if (alunni[i].voti.inglese>voto_max) voto_max=alunni[i].voti.inglese;
        if (alunni[i].voti.italiano>voto_max) voto_max=alunni[i].voti.italiano;
    }
    cout<<"Gli alunni con il voto piu' alto sono: "<<endl;
    for (int i = 0; i < n; ++i)
        if (alunni[i].voti.matematica==voto_max || alunni[i].voti.italiano==voto_max || alunni[i].voti.inglese==voto_max ) cout<<alunni[i].nome<<endl;
    }
int main() {
    const int N_STUDENTI_MAX = 100;
    int n_studenti;
    cout<<"Inserisci il numero di studenti della scuola :"<<endl;
    do {
        cin>>n_studenti;
        if (n_studenti<=0 || n_studenti>N_STUDENTI_MAX)
            cout<<"Il numero degli studenti deve essere compreso tra 1 e 100"<<endl;
    }while(n_studenti<=0 || n_studenti>N_STUDENTI_MAX);
    Studente alunni[n_studenti];
    for (int i = 0; i < n_studenti; ++i) {
        inserisci_alunno( alunni , i) ;
    }
    disciplina_media_piu_elevata(alunni , n_studenti);
    voto_piu_alto(alunni , n_studenti);
    return 0;
}
