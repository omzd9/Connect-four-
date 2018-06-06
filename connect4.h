#ifndef connect4_H
#define connect4_H
#include <iostream>
using namespace std;
const int row=6;
const int column=7;
typedef struct
{
int ligne;
int cologne;
}Case;

class connect4
{
    public:
        connect4();
        bool jeuFini();
        bool checkHorizontale();
        bool checkVertical();
        bool diagonaleSensDroite();
        bool diagonaleSensGauche();
        bool checkDiagonale();
        bool check();
        int heuristic1(); /// meduim
        int heuristic3();/// easy
        int heuristic1AlphaBeta(int joueur); ///Hard
        void vider();
        int returnRowVide(int j);
        int minimax(int depth,int player,int& c);
        int minimaxEasy(int depth,int player,int& c);
        int alphabeta(int depth,int alpha, int beta,int player,int& c);
        Case* findBestMove();
        Case* findBestMoveEasy();
        Case* findBestMoveHard();
        void printBoard();
        int players()const;
        int evaluate(int player);
        int evaluate1(int player);
        void jouer(int ,int,int);

        /*if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
                    {
                       cout<<Mix_GetError()<<endl;
                    }
                Mix_Music *musique;
                 musique = Mix_LoadMUS("run.mp3");


                 Mix_PlayMusic(musique, 1);
                musique = Mix_LoadMUS("musique.mp3");

                Mix_CloseAudio();*/
        private:

        int board[row][column];

};

#endif // connect4_H

