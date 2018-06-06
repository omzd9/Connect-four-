#include "connect4.h"
#include <iostream>
using namespace std;
const int DEPTH_MAX=5;
const int DEPTH_MAX_ALPPHA_BETA=6;
connect4::connect4()
{
    for(int i=0;i<row;i++)
        for(int j=0;j<column;j++)
            board[i][j]=0;
}
bool secondThreat(int joueur,int a,int b,int c,int z);
void connect4::printBoard()
{
   cout<<endl<<"    ****Connect Four****"<<endl;
   for(int i = row-1; i >=0; i--){
      for(int j = 0; j < column; j++){
        if(board[i][j]==-1)
            cout<<"  |  2";
        else
            cout<<"  |  "<<board[i][j];
      }
      cout<<"  |"<<endl;
      cout<<"---------------------------------------------"<<endl;

   }

   cout<<"     1     2     3     4     5     6     7"<<endl;

}
int maximisre(int x, int y)
{
    if(x>y)
        return x;
    return y;
}
 void connect4::jouer(int x,int y,int player)
 {
     board[x][y]=player;
 }
bool connect4::jeuFini()
{
    for (int i = 0; i<column; i++)
        for (int j = 0; j<row; j++)
            if (board[j][i]==0)
                return false;
    return true;
}
inline bool checkFour(int a,int b,int c,int z)
{
    return ( !(a==0) && a==b && b==c && c==z);
}

bool connect4::checkHorizontale()
{
    for(int i=0;i<6;i++)
        for(int j=0;j<4;j++)
            if(checkFour(board[i][j],board[i][j+1],board[i][j+2],board[i][j+3]))
                return true;
    return false;
}
bool connect4::checkVertical()
{
    for(int j=0;j<7;j++)
        for(int i=0;i<3;i++)
            if(checkFour(board[i][j],board[i+1][j],board[i+2][j],board[i+3][j]))
                return true;
    return false;
}
bool connect4::diagonaleSensDroite()
{
    for(int i=5;i>2;i--)
        for(int j=0;j<4;j++)
            if(checkFour(board[i][j],board[i-1][j+1],board[i-2][j+2],board[i-3][j+3]))
                return true ;
    return false;
}
bool connect4::diagonaleSensGauche()
{
    for(int i=5;i>2;i--)
        for(int j=6;j>2;j--)
            if(checkFour(board[i][j],board[i-1][j-1],board[i-2][j-2],board[i-3][j-3]))
                return true ;
    return false;
}
bool connect4::checkDiagonale()
{
    return (this->diagonaleSensDroite()||this->diagonaleSensGauche());
}
bool connect4::check()
{
    return (this->checkDiagonale()||this->checkHorizontale()||this->checkVertical());
}

int connect4::evaluate1(int player) ///return 1000 si x gagnera /return -1000 si O gagnera / return 0 si aucun des deux a gagné
{
    if(this->check())
        {if( player==1)/// 1=machine -1=opponent
            return 1000;
        else
            return -1000;}

     return 0;/// jeu continue
}
int connect4::evaluate(int player) ///return 1000 si x gagnera /return -1000 si O gagnera / return 0 si aucun des deux a gagné
{
    if(this->check())
        {if( player==-1)/// 1=machine -1=opponent
            return 1000;
        else
            return -1000;}

     return 0;/// jeu continue
}

int connect4::returnRowVide(int j)
{
    for(int i=0;i<row;i++)
    {
        if(board[i][j]==0)
            return i;
    }
    return 7;

}


int connect4::minimax(int depth,int player,int &c)
{

    int score = this->evaluate1(player);
    if (score == 1000)
        return score-depth;
    if (score == -1000)
        return score+depth;
    if (this->jeuFini())
        return 0; /// egalité

    if (depth==DEPTH_MAX)
        {
          return this->heuristic1AlphaBeta(player);
          }//state(board);
    int best=-2000;
    for (int j = 0; j < column; j++)
            {
                // Check if cell is empty
                int rowVide=this->returnRowVide(j);
                if (rowVide!=7)
                {
                    // Make the move
                    board[rowVide][j] = player;
                    c++;
                    // Call minimax recursively and choose
                    // the maximum value
                    best = -this->minimax(depth+1,-player,c);

                    // Undo the move
                    board[rowVide][j] = 0;
                }
            }//For all moves,

        return best;
    }


// This will return the best possible move for the player
Case* connect4::findBestMove()
{
    int bestVal = -1001;
    Case* bestMove;
    bestMove=new Case;
    bestMove->ligne = -1;
    int a=0;
    bestMove->cologne = -1;
    int &c=a;
      for (int j = 0; j<column; j++)
        {
            // Check if celll is empty
            int rowVide=this->returnRowVide(j);
            if (rowVide!=7)
            {
                board[rowVide][j] = 1;

                int moveVal = -this->minimax(0,-1,c);

                board[rowVide][j] = 0;

                if (moveVal > bestVal)
                {
                    bestMove->ligne = rowVide;
                    bestMove->cologne = j;
                    bestVal = moveVal;
                }
            }
        }
        cout<<"nombre de noeud explore est : "<<c<<endl;
return bestMove;

}
Case* connect4::findBestMoveHard()
{
    int bestVal = -2001;
    Case* bestMove;
    bestMove=new Case;
    int a=0;
    bestMove->ligne = -1;
    bestMove->cologne = -1;
int &c=a;
      for (int j = 0; j<column; j++)
        {
            // Check if celll is empty
            int rowVide=this->returnRowVide(j);
            if (rowVide!=7)
            {
                board[rowVide][j] = 1;

                int moveVal = this->alphabeta(0,-2000,2000,-1,c);

                board[rowVide][j] = 0;

                if (moveVal > bestVal)
                {
                    bestMove->ligne = rowVide;
                    bestMove->cologne = j;
                    bestVal = moveVal;
                }
            }
        }
        cout<<"nombre de noeud explore est : "<<c<<endl;
return bestMove;

}
Case* connect4::findBestMoveEasy()
{
    int bestVal = -1001;
    Case* bestMove;
    bestMove=new Case;
    int a=0;
    int &c=a;
    bestMove->ligne = -1;
    bestMove->cologne = -1;

      for (int j = 0; j<column; j++)
        {
            // Check if celll is empty
            int rowVide=this->returnRowVide(j);
            if (rowVide!=7)
            {
                board[rowVide][j] = 1;

                int moveVal = -this->minimaxEasy(0,-1,c);

                board[rowVide][j] = 0;

                if (moveVal > bestVal)
                {
                    bestMove->ligne = rowVide;
                    bestMove->cologne = j;
                    bestVal = moveVal;
                }
            }
        }
        cout<<"nombre de noeud explore :"<<c<<endl;
return bestMove;

}
int connect4::minimaxEasy(int depth,int player,int& c)
{
     int score = this->evaluate1(player);
    if (score == 1000)
        return score-depth;
    if (score == -1000)
        return score+depth;
    if (this->jeuFini())
        return 0; /// egalité

    if (depth==DEPTH_MAX)
        {
          return player*this->heuristic3();
          }//state(board);
    int best=-2000;
    for (int j = 0; j < column; j++)
            {
                // Check if cell is empty
                int rowVide=this->returnRowVide(j);
                if (rowVide!=7)
                {
                    // Make the move
                    board[rowVide][j] = player;
                    c++;
                    // Call minimax recursively and choose
                    // the maximum value
                    best = -this->minimax(depth+1,-player,c);

                    // Undo the move
                    board[rowVide][j] = 0;
                }
            }//For all moves,

        return best;
}
 void connect4::vider()
 {
     for(int i=0;i<row;i++)
        for(int j=0;j<column;j++)
            board[i][j]=0;
 }
bool vraiThreat(int joueur,int a,int b,int c,int z)
{
    if(a==0)
        return ( b==joueur && c==b && z==c);
    if(b==0)
        return ( a==joueur  && c==a && z==c);
    if(c==0)
        return ( b==joueur  && a==b && z==a);
    if(z==0)
        return ( b==joueur && c==b && a==c);
    return false;
}
int connect4::heuristic1()
 /// quatre case adjacent avec 3 case de meme valeur et la quatrieme vide
{
    int coutDeconnect4=0;
    ///horizontale
    for(int i=0;i<6;i++)
        for(int j=0;j<4;j++)
            {if(vraiThreat(1,board[i][j],board[i][j+1],board[i][j+2],board[i][j+3]))
                coutDeconnect4+=55;

                 //coutDeconnect4+=cout4(1,board[i][j],board[i][j+1],board[i][j+2],board[i][j+3]);
                 }
    ///verticale
     for(int j=0;j<7;j++)
        for(int i=0;i<3;i++)
            {if(vraiThreat(1,board[i][j],board[i+1][j],board[i+2][j],board[i+3][j]))
                coutDeconnect4+=55;

                // coutDeconnect4+=cout4(1,board[i][j],board[i+1][j],board[i+2][j],board[i+3][j]);
                }


    ///diagonaleSensDroite(int board[row][column])
    for(int i=5;i>2;i--)
        for(int j=0;j<4;j++)
            {if(vraiThreat(1,board[i][j],board[i-1][j+1],board[i-2][j+2],board[i-3][j+3]))
                coutDeconnect4+=55;

              // coutDeconnect4+=cout4(1,board[i][j],board[i-1][j+1],board[i-2][j+2],board[i-3][j+3]);
              }



    for(int i=5;i>2;i--)
        for(int j=6;j>2;j--)
            {if(vraiThreat(1,board[i][j],board[i-1][j-1],board[i-2][j-2],board[i-3][j-3]))
                coutDeconnect4+=55;

                // coutDeconnect4+=cout4(1,board[i][j],board[i-1][j-1],board[i-2][j-2],board[i-3][j-3]);
                }

        /// calcule for opponent
        ///horizontale
    for(int i=0;i<6;i++)
        for(int j=0;j<4;j++)
            {if(vraiThreat(-1,board[i][j],board[i][j+1],board[i][j+2],board[i][j+3]))
                coutDeconnect4-=60;

                // coutDeconnect4-=cout4(-1,board[i][j],board[i][j+1],board[i][j+2],board[i][j+3]);
                }

    ///verticale
     for(int j=0;j<7;j++)
        for(int i=0;i<3;i++)
            {if(vraiThreat(-1,board[i][j],board[i+1][j],board[i+2][j],board[i+3][j]))
                coutDeconnect4-=60;

                 //coutDeconnect4-=cout4(-1,board[i][j],board[i+1][j],board[i+2][j],board[i+3][j]);
                 }

    ///diagonaleSensDroite(int board[row][column])
    for(int i=5;i>2;i--)
        for(int j=0;j<4;j++)
           {if(vraiThreat(-1,board[i][j],board[i-1][j+1],board[i-2][j+2],board[i-3][j+3]))
                coutDeconnect4-=60;

                //coutDeconnect4-=cout4(-1,board[i][j],board[i-1][j+1],board[i-2][j+2],board[i-3][j+3]);
                }

    ///diagonaleSensGauche(int board[row][column])

    for(int i=5;i>2;i--)
        for(int j=6;j>2;j--)
            {if(vraiThreat(-1,board[i][j],board[i-1][j-1],board[i-2][j-2],board[i-3][j-3]))
                coutDeconnect4-=60;

                //coutDeconnect4-=cout4(-1,board[i][j],board[i-1][j-1],board[i-2][j-2],board[i-3][j-3]);
                }

return coutDeconnect4;
}

int cout4(int joueur,int a,int b,int c,int d)
{

int k=0;
    if(joueur==a )
        k++;
    if(joueur==b)
       k++;
    if(joueur==c)
        k++;
    if(joueur==d)
        k++;
    if(k==4)
        return 1000;
    if(k==3)
        return 20;
    if(k==2)
        return 5;
    return 0;

}
int connect4::heuristic3()
{
       int coutDeconnect4=0;
    ///horizontale
    for(int i=0;i<6;i++)
        for(int j=0;j<4;j++)
            coutDeconnect4+=cout4(1,board[i][j],board[i][j+1],board[i][j+2],board[i][j+3]);

    ///verticale
     for(int j=0;j<6;j++)
        for(int i=0;i<3;i++)
            coutDeconnect4+=cout4(1,board[i][j],board[i+1][j],board[i+2][j],board[i+3][j]);


    ///diagonaleSensDroite(int board[row][column])
    for(int i=5;i>2;i--)
        for(int j=0;j<4;j++)
            coutDeconnect4+=cout4(1,board[i][j],board[i-1][j+1],board[i-2][j+2],board[i-3][j+3]);


    ///diagonaleSensGauche(int board[row][column])
    for(int i=5;i>2;i--)
        for(int j=6;j>2;j--)
            coutDeconnect4+=cout4(1,board[i][j],board[i-1][j-1],board[i-2][j-2],board[i-3][j-3]);

        /// calcule for opponent
        ///horizontale
    for(int i=0;i<6;i++)
        for(int j=0;j<4;j++)
           coutDeconnect4-=cout4(-1,board[i][j],board[i][j+1],board[i][j+2],board[i][j+3]);

    ///verticale
     for(int j=0;j<6;j++)
        for(int i=0;i<3;i++)
            coutDeconnect4-=cout4(-1,board[i][j],board[i+1][j],board[i+2][j],board[i+3][j]);


    ///diagonaleSensDroite(int board[row][column])
    for(int i=5;i>2;i--)
        for(int j=0;j<4;j++)
            coutDeconnect4-=cout4(-1,board[i][j],board[i-1][j+1],board[i-2][j+2],board[i-3][j+3]);


    ///diagonaleSensGauche(int board[row][column])

    for(int i=5;i>2;i--)
        for(int j=6;j>2;j--)
           coutDeconnect4-=cout4(-1,board[i][j],board[i-1][j-1],board[i-2][j-2],board[i-3][j-3]);

return coutDeconnect4;
}

int connect4::alphabeta(int depth,int alpha, int beta,int joueur,int& c)

{

    int score = this->evaluate(joueur);
    if (score == 1000)
        return score-depth;
    if (score == -1000)
        return score+depth;
    if (this->jeuFini())
        return 0; /// egalité

    if (depth==DEPTH_MAX_ALPPHA_BETA)
        {
          return this->heuristic1AlphaBeta(joueur);
        }//state(board);
    if(joueur==1)
            {

            for (int j = 0; j < column; j++){
                // Check if cell is empty
                int rowVide=this->returnRowVide(j);
                if (rowVide!=7)
                {
                    // Make the move
                    board[rowVide][j] = joueur;
                    c++;
                    alpha = maximisre(alpha,this->alphabeta(depth+1,alpha,beta,-1,c));
                    board[rowVide][j] = 0;
                    if(alpha>=beta)
                        break;

                }
            }//For all moves,
            return alpha;
            }
        if(joueur==-1)
            {
            for (int j = 0; j < column; j++){
                // Check if cell is empty
                int rowVide=returnRowVide(j);
                if (rowVide!=7)
                {
                    // Make the move
                    board[rowVide][j] = joueur;
                    c++;
                    // Call minimax recursively and choose
                    // the maximum value
                    beta = -maximisre(-beta,-this->alphabeta(depth+1,alpha,beta,1,c));
                    board[rowVide][j] = 0;
                    if(alpha>=beta)
                        break;

                }

            }
        return beta;
    }
}
int connect4::heuristic1AlphaBeta(int player)
 /// quatre case adjacent avec 3 case de meme valeur et la quatrieme vide
{
    int coutDeconnect4=0;
    ///horizontale
    for(int i=0;i<6;i++)
        for(int j=0;j<4;j++)
            {if(vraiThreat(1,board[i][j],board[i][j+1],board[i][j+2],board[i][j+3]))
                coutDeconnect4+=60;
            if(secondThreat(1,board[i][j],board[i][j+1],board[i][j+2],board[i][j+3]))
                coutDeconnect4+=20;

                 //coutDeconnect4+=cout4(1,board[i][j],board[i][j+1],board[i][j+2],board[i][j+3]);
                 }
    ///verticale
     for(int j=0;j<7;j++)
        for(int i=0;i<3;i++)
            {if(vraiThreat(1,board[i][j],board[i+1][j],board[i+2][j],board[i+3][j]))
                coutDeconnect4+=60;
            if(secondThreat(1,board[i][j],board[i+1][j],board[i+2][j],board[i+3][j]))
                coutDeconnect4+=20;

                // coutDeconnect4+=cout4(1,board[i][j],board[i+1][j],board[i+2][j],board[i+3][j]);
                }


    ///diagonaleSensDroite(int board[row][column])
    for(int i=5;i>2;i--)
        for(int j=0;j<4;j++)
            {if(vraiThreat(1,board[i][j],board[i-1][j+1],board[i-2][j+2],board[i-3][j+3]))
                coutDeconnect4+=60;
            if(secondThreat(1,board[i][j],board[i-1][j+1],board[i-2][j+2],board[i-3][j+3]))
                coutDeconnect4+=20;

              // coutDeconnect4+=cout4(1,board[i][j],board[i-1][j+1],board[i-2][j+2],board[i-3][j+3]);
              }



    for(int i=5;i>2;i--)
        for(int j=6;j>2;j--)
            {if(vraiThreat(1,board[i][j],board[i-1][j-1],board[i-2][j-2],board[i-3][j-3]))
                coutDeconnect4+=60;
            if(secondThreat(1,board[i][j],board[i-1][j-1],board[i-2][j-2],board[i-3][j-3]))
                coutDeconnect4+=20;

                // coutDeconnect4+=cout4(1,board[i][j],board[i-1][j-1],board[i-2][j-2],board[i-3][j-3]);
                }

        /// calcule for opponent
        ///horizontale
    for(int i=0;i<6;i++)
        for(int j=0;j<4;j++)
            {if(vraiThreat(-1,board[i][j],board[i][j+1],board[i][j+2],board[i][j+3]))
                coutDeconnect4-=60;
            if(secondThreat(-1,board[i][j],board[i][j+1],board[i][j+2],board[i][j+3]))
                coutDeconnect4-=20;

                // coutDeconnect4-=cout4(-1,board[i][j],board[i][j+1],board[i][j+2],board[i][j+3]);
                }

    ///verticale
     for(int j=0;j<7;j++)
        for(int i=0;i<3;i++)
            {if(vraiThreat(-1,board[i][j],board[i+1][j],board[i+2][j],board[i+3][j]))
                coutDeconnect4-=60;
            if(secondThreat(-1,board[i][j],board[i+1][j],board[i+2][j],board[i+3][j]))
                coutDeconnect4-=20;
                 //coutDeconnect4-=cout4(-1,board[i][j],board[i+1][j],board[i+2][j],board[i+3][j]);
                 }

    ///diagonaleSensDroite(int board[row][column])
    for(int i=5;i>2;i--)
        for(int j=0;j<4;j++)
           {if(vraiThreat(-1,board[i][j],board[i-1][j+1],board[i-2][j+2],board[i-3][j+3]))
                coutDeconnect4-=60;
            if(secondThreat(-1,board[i][j],board[i-1][j+1],board[i-2][j+2],board[i-3][j+3]))
                coutDeconnect4-=20;

                //coutDeconnect4-=cout4(-1,board[i][j],board[i-1][j+1],board[i-2][j+2],board[i-3][j+3]);
                }

    ///diagonaleSensGauche(int board[row][column])

    for(int i=5;i>2;i--)
        for(int j=6;j>2;j--)
            {if(vraiThreat(-1,board[i][j],board[i-1][j-1],board[i-2][j-2],board[i-3][j-3]))
                coutDeconnect4-=60;
            if(secondThreat(-1,board[i][j],board[i-1][j-1],board[i-2][j-2],board[i-3][j-3]))
                coutDeconnect4-=20;

                //coutDeconnect4-=cout4(-1,board[i][j],board[i-1][j-1],board[i-2][j-2],board[i-3][j-3]);
                }

if(player==1)
    return -coutDeconnect4;
return coutDeconnect4;
}
bool secondThreat(int joueur,int a,int b,int c,int z)
{
    int i=0;
    if(a==joueur)
        i+=10;
    else if(a==-joueur)
        i-=3;
     if(b==joueur)
        i+=10;
    else if(b==-joueur)
        i-=3;
     if(c==joueur)
        i+=10;
    else if(c==-joueur)
        i-=3;
    if(z==joueur)
        i+=10;
    else if(z==-joueur)
        i-=3;
    if(i==20)
        return true;
    return false;


}

