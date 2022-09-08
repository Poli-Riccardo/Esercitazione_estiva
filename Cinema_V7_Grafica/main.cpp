

/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <iostream>
#include <cstring>
#include "fstream"
using namespace std;

const int RIGHE = 20;
const int COLONNE = 19;
void disegna_posto(int x, int y, bool prenotato,Texture2D posto)
{
    if (prenotato)
        DrawTexture(posto,x + 10, y + 10, RED);
    else
        DrawTexture(posto,x + 10, y + 10, GREEN);

}
void disegna_sala(bool posti[][COLONNE], int righe,int w, int h, Texture2D posto)
{
    for (int i = 0; i < righe-2; ++i) {
        for (int j = 0; j < COLONNE; ++j) {
            int x = w / COLONNE * j;
            int y = h / righe * i;
            disegna_posto(x ,y ,posti[i][j], posto);
        }
    }
}
string stampa_posto(int riga, int colonna)
{
    string posto = "";
    posto += (char)('A' + riga);
    posto += " - ";
    posto += to_string(colonna + 1);

    return posto;
}

void importa_prenotazioni (bool posti [][COLONNE] , ifstream &in ,ofstream &out ){
    string riga, nome , cognome;
    int fila , posto , pos;
    while(getline(in,riga)){
        pos=riga.find(';');
        fila= stoi(riga.substr(0,pos));
        riga.erase(0,pos+1);
        pos=riga.find(';');
        posto= stoi(riga.substr(0,pos));
       posti[fila][posto]=true;
        out << fila << ";" << posto << ";" <<endl;
    }
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1200;
    const int screenHeight = 800;
    int x = (screenWidth / COLONNE * 9)+10;
    int y = (screenHeight / RIGHE * 19)-10;
    ofstream out ("prenotazioni_sala1.txt");
    ifstream in ("prenotazioni_precedenti_sala1.txt");
    ofstream out_2 ("prenotazioni_sala2.txt");
    ifstream in_2 ("prenotazioni_precedenti_sala2.txt");
    if (!out){
        cout<<"Errore nella creazione del file " <<endl;
        return 1;
    }
    if (!in){
        cout<<"Errore nell'apertura del file "<<endl;
        return 1;
    }
    if (!out_2){
        cout<<"Errore nella creazione del file " <<endl;
        return 1;
    }
    if (!in_2){
        cout<<"Errore nell'apertura del file "<<endl;
        return 2;
    }
    bool posti[RIGHE][COLONNE];
    bool sala_2=false;

    for (int i = 0; i < RIGHE; ++i) {
        for (int j = 0; j < COLONNE; ++j) {
            posti[i][j] = false;
        }
    }
    importa_prenotazioni(posti , in ,out);

    InitWindow(screenWidth, screenHeight, "Cinema");
    Texture2D posto = LoadTexture("img/posto.png");
    Texture2D button = LoadTexture("img/button.png");
    Texture2D next = LoadTexture("img/next.png");
    Texture2D back = LoadTexture("img/back.png");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    Vector2 posizioneMouse;
    int deltaX = screenWidth / COLONNE;
    int deltaY = screenHeight / RIGHE;
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        posizioneMouse=GetMousePosition();
        int colonna = posizioneMouse.x / deltaX;
        int riga = posizioneMouse.y / deltaY;
        string posizione = stampa_posto(riga, colonna);
        char stringa_c[20];

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                if(riga<18){
                    if (!posti[riga][colonna] && !sala_2){
                        out<<riga<<";"<<colonna<<";"<<endl;
                        posti[riga][colonna] =true;
                    }
                    else if (!posti[riga][colonna] && sala_2){
                        out_2<<riga<<";"<<colonna<<";"<<endl;
                        posti[riga][colonna] =true;
                    }

                }
            }
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                if(riga<18){

                    if (posti[riga][colonna] && !sala_2){
                        posti[riga][colonna] = false ;
                        out.close();
                        out.open("prenotazioni_sala1.txt",ios::out |ios::trunc);
                        for (int i = 0; i < RIGHE; ++i) {
                            for (int j = 0; j < COLONNE; ++j) {
                                if (posti[i][j]) out<<i<<";"<<j<<";"<<endl;
                            }
                        }
                    }
                    else if (posti[riga][colonna] && sala_2){
                        posti[riga][colonna] = false ;
                        out_2.close();
                        out_2.open("prenotazioni_sala2.txt",ios::out |ios::trunc);
                        for (int i = 0; i < RIGHE; ++i) {
                            for (int j = 0; j < COLONNE; ++j) {
                                if (posti[i][j]) out_2<<i<<";"<<j<<";"<<endl;
                            }
                        }
                    }
                }
            }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&& riga==19 &&colonna==10){
            if (sala_2){
                sala_2=false;
                for (int i = 0; i < RIGHE; ++i) {
                    for (int j = 0; j < COLONNE; ++j) {
                        posti[i][j] = false;
                    }
                }
                importa_prenotazioni(posti , in , out);


            }
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&& riga==19 &&colonna==9){
                for (int i = 0; i < RIGHE; ++i) {
                    for (int j = 0; j < COLONNE; ++j) {
                        posti[i][j] = false;
                    }
                }
                if(!sala_2){
                    out.close();
                    out.open("prenotazioni_sala1.txt",ios::out |ios::trunc);
                }
                else{
                    out_2.close();
                    out_2.open("prenotazioni_sala2.txt",ios::out |ios::trunc);
                }

        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&& riga==19 &&colonna==8){
                if (!sala_2){
                    sala_2=true;
                    for (int i = 0; i < RIGHE; ++i) {
                        for (int j = 0; j < COLONNE; ++j) {
                            posti[i][j] = false;
                        }
                    }
                    importa_prenotazioni(posti , in_2 , out_2);
                }

            }
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(button,x,y,RAYWHITE);
        DrawTexture(next,x-55,y+7,RAYWHITE);
        DrawTexture(back,x+70,y+7,RAYWHITE);
        strcpy(stringa_c, posizione.c_str());
        disegna_sala(posti, RIGHE, screenWidth, screenHeight, posto);




        if (riga<18){
            DrawRectangle(posizioneMouse.x - 4, posizioneMouse.y - 44,130,40,WHITE);
            DrawText(stringa_c, posizioneMouse.x, posizioneMouse.y - 40,40,BLACK);
        }
        if (riga==19 && colonna ==9){
            DrawRectangle(posizioneMouse.x - 4, posizioneMouse.y - 44,170,40,WHITE);
            DrawText("Restart", posizioneMouse.x, posizioneMouse.y - 40,40,BLACK);
        }
        if (riga==19 && colonna ==8){
            DrawRectangle(posizioneMouse.x - 4, posizioneMouse.y - 44,170,40,WHITE);
            DrawText("Sala 2", posizioneMouse.x, posizioneMouse.y - 40,40,BLACK);
        }
        if (riga==19 && colonna ==10){
            DrawRectangle(posizioneMouse.x - 4, posizioneMouse.y - 44,170,40,WHITE);
            DrawText("Sala 1", posizioneMouse.x, posizioneMouse.y - 40,40,BLACK);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    in.close();
    remove("prenotazioni_precedenti_sala1.txt");
    in_2.close();
    remove("prenotazioni_precedenti_sala2.txt");
    out.close();
    rename("prenotazioni_sala1.txt","prenotazioni_precedenti_sala1.txt");
    out_2.close();
    rename("prenotazioni_sala2.txt","prenotazioni_precedenti_sala2.txt");
    return 0;
}


