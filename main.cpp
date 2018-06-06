#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "connect4.h"
using namespace std;
int IA(SDL_Window* win,SDL_Renderer *ren,int Hardest);
int multiGamer(SDL_Window* win,SDL_Renderer *ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL,&dst);
}
void afficheinCenter(SDL_Texture *tex, SDL_Renderer *ren)
{
    SDL_Rect dst;
	dst.x = 640;
	dst.y = 360;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	renderTexture(tex,ren,640- dst.w/2,360-dst.h/2);
	SDL_RenderPresent(ren);
}
void logSDLError(ostream &os,char* msg)
{
	os << msg << " error: " << SDL_GetError() << endl;
}
SDL_Texture* loadTexture(char* chaine, SDL_Renderer *ren)
{

	SDL_Texture *texture = NULL ;
	SDL_Surface* Image = IMG_Load( chaine );
	if (Image != NULL)
    {
		texture = SDL_CreateTextureFromSurface(ren, Image);
		SDL_FreeSurface(Image);
		//Make sure converting went ok too
        if (texture ==NULL){
			logSDLError(cout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(cout, "Loadjpg");
	}
	return texture;
}

int returnRowVide(int board[row][column],int j)
{
    for(int i=0;i<row;i++)
    {
        if(board[i][j]==0)
            return i;
    }
    return 7;

}
void printBoard(int board[row][column]){


   //system("clear");
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
int main(int argc , char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        logSDLError(cout,"SDL_Init");
    }


    SDL_Window *win = SDL_CreateWindow("jeu de puissance 4!",10,22, 1340, 720, SDL_WINDOW_SHOWN);
    if(win==NULL)
    {
        logSDLError(cout,"SDL_Window");
        SDL_Quit();
    }
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


    if(ren==NULL)
    {
         logSDLError(cout,"SDL_Init");
         SDL_DestroyWindow(win);
        SDL_Quit();
    }
    SDL_Texture *tex=NULL;
    const int DELAY_Render=400;
    SDL_Surface* icon = IMG_Load("icon.png" );
    SDL_SetWindowIcon(win, icon);
    SDL_FreeSurface(icon);
for(int i=0;i<2;i++)
{
    SDL_RenderClear(ren);
    tex= loadTexture("back.jpg", ren);
    renderTexture(tex,ren,0,0);
    tex= loadTexture("1.jpg", ren);
	afficheinCenter(tex, ren);

	SDL_Delay(DELAY_Render);
	 //SDL_RenderClear(ren);
    tex= loadTexture("2.jpg", ren);
	afficheinCenter(tex, ren);
	SDL_Delay(DELAY_Render);
	 //SDL_RenderClear(ren);
    tex= loadTexture("3.jpg", ren);
	afficheinCenter(tex, ren);

	SDL_Delay(DELAY_Render);
	 //SDL_RenderClear(ren);
   tex= loadTexture("4.jpg", ren);
	afficheinCenter(tex, ren);
	SDL_Delay(DELAY_Render);
	//SDL_RenderClear(ren);
   tex= loadTexture("5.jpg", ren);
	afficheinCenter(tex, ren);
	SDL_Delay(DELAY_Render);
	//SDL_RenderClear(ren);
   tex= loadTexture("6.jpg", ren);
	afficheinCenter(tex, ren);
	SDL_Delay(DELAY_Render);
}

SDL_Event e;

SDL_Rect dst;
bool keep=true;
while (keep)
{
    menu1:
    SDL_RenderClear(ren);
    tex= loadTexture("menu1.jpg", ren);
    renderTexture(tex,ren,0,0);
    SDL_RenderPresent(ren);
    while (SDL_WaitEvent(&e))
    {
        if (e.type == SDL_MOUSEBUTTONDOWN)
            {

        if(e.button.x < 862 && e.button.x > 484 && e.button.y < 265 && e.button.y > 215 )
        {
            menu2:
            SDL_RenderClear(ren);
            tex= loadTexture("menu2.jpg", ren);
            renderTexture(tex,ren,0,0);
            SDL_RenderPresent(ren);
            SDL_Event event;
             while (SDL_WaitEvent(&event))
                {
                    if (event.type == SDL_MOUSEBUTTONDOWN)
                        {
                            if(event.button.x < 862 && event.button.x > 484 && event.button.y < 357 && event.button.y > 310 )
                            {

                                            int res=IA(win,ren,2);
                                            if(res==1)
                                                {
                                                    SDL_DestroyTexture(tex);
                                                    SDL_DestroyRenderer(ren);
                                                    SDL_DestroyWindow(win);
                                                    SDL_Quit();
                                                    return 0;
                                                }
                                            if(res==2)
                                                goto menu2;
                            }


                            if(event.button.x < 862 && event.button.x > 484 && event.button.y < 265 && event.button.y > 215 )

                                  {

                                            int res=IA(win,ren,1);
                                            if(res==1)
                                                {
                                                    SDL_DestroyTexture(tex);
                                                    SDL_DestroyRenderer(ren);
                                                    SDL_DestroyWindow(win);
                                                    SDL_Quit();
                                                    return 0;
                                                }
                                            if(res==2)
                                                goto menu2;
                                                }

                             if(event.button.x< 862&& event.button.x >484 && event.button.y< 449 && event.button.y > 400 )
                                 {
                                                    int res=IA(win,ren,3);
                                            if(res==1)
                                                {
                                                    SDL_DestroyTexture(tex);
                                                    SDL_DestroyRenderer(ren);
                                                    SDL_DestroyWindow(win);
                                                    SDL_Quit();
                                                    return 0;
                                                }
                                            if(res==2)
                                                goto menu2;
                                    }
                             if(event.button.x < 862 && event.button.x > 484 && event.button.y<541 && event.button.y > 494)
                              {
                                                    SDL_RenderClear(ren);
                                                    goto menu1;
                                                }
                        }
                             if (event.type == SDL_QUIT)
                                        {
                                            SDL_DestroyTexture(tex);
                                        SDL_DestroyRenderer(ren);
                                        SDL_DestroyWindow(win);
                                        SDL_Quit();
                                        return 0;
                                        }

                            if (event.type == SDL_KEYDOWN)
                                            {
                                                SDL_DestroyTexture(tex);
                                                SDL_DestroyRenderer(ren);
                                                SDL_DestroyWindow(win);
                                                SDL_Quit();
                                                return 0;
                                            }

                }
        }


        if(e.button.x < 862 && e.button.x > 484 && e.button.y < 357 && e.button.y > 310 )
        {
                int res=multiGamer(win,ren);
                                            if(res==1)
                                                {
                                                    SDL_DestroyTexture(tex);
                                                    SDL_DestroyRenderer(ren);
                                                    SDL_DestroyWindow(win);
                                                    SDL_Quit();
                                                    return 0;
                                                }
                                            if(res==2)
                                                goto menu1;
        }
    if(e.button.x< 862&& e.button.x >484 && e.button.y< 449 && e.button.y > 400 )
         {
             SDL_RenderClear(ren);
            tex= loadTexture("regles.jpg", ren);
            renderTexture(tex,ren,0,0);
            SDL_RenderPresent(ren);

            while(SDL_WaitEvent(&e))
            {
                if (e.type == SDL_QUIT)
                                        {
                                        SDL_DestroyTexture(tex);
                                        SDL_DestroyRenderer(ren);
                                        SDL_DestroyWindow(win);
                                        SDL_Quit();
                                        return 0;
                                        }

                if (e.type == SDL_KEYDOWN)
                                            {
                                                SDL_DestroyTexture(tex);
                                                SDL_DestroyRenderer(ren);
                                                SDL_DestroyWindow(win);
                                                SDL_Quit();
                                                return 0;
                                            }
                if (e.type == SDL_MOUSEBUTTONDOWN)
                        {
                            if(e.button.x < 1307 && e.button.x > 1224 && e.button.y < 687 && e.button.y > 622 )
                            {
                                SDL_RenderClear(ren);
                                goto menu1;
                            }
            }
         }
         }
    if(e.button.x < 862 && e.button.x > 484 && e.button.y<541 && e.button.y > 494)
         {
            SDL_DestroyTexture(tex);
            SDL_DestroyRenderer(ren);
            SDL_DestroyWindow(win);
            SDL_Quit();
            return 0;
         }
        }
    if (e.type == SDL_QUIT)
			{
            SDL_DestroyTexture(tex);
            SDL_DestroyRenderer(ren);
            SDL_DestroyWindow(win);
            SDL_Quit();
            keep=false;
			}

		if (e.type == SDL_KEYDOWN)
		    {
		        SDL_DestroyTexture(tex);
                SDL_DestroyRenderer(ren);
                SDL_DestroyWindow(win);
                SDL_Quit();
                keep=false;
		    }
    }
}


    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}



///party
bool jeuFini(int board[row][column])
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
bool checkHorizontale(int mat[row][column])
{
    for(int i=0;i<6;i++)
        for(int j=0;j<4;j++)
            if(checkFour(mat[i][j],mat[i][j+1],mat[i][j+2],mat[i][j+3]))
                return true;
    return false;
}
bool checkVertical(int mat[row][column])
{
    for(int j=0;j<7;j++)
        for(int i=0;i<3;i++)
            if(checkFour(mat[i][j],mat[i+1][j],mat[i+2][j],mat[i+3][j]))
                return true;
    return false;
}
bool vraiThreat(int a,int b,int c,int z);
bool diagonaleSensDroite(int mat[row][column])
{
    for(int i=5;i>2;i--)
        for(int j=0;j<4;j++)
            if(checkFour(mat[i][j],mat[i-1][j+1],mat[i-2][j+2],mat[i-3][j+3]))
                return true ;
    return false;
}
void vider(int board[row][column])
{
     for(int i=0;i<row;i++)
        for(int j=0;j<column;j++)
            board[i][j]=0;
}
bool diagonaleSensGauche(int mat[row][column])
{
    for(int i=5;i>2;i--)
        for(int j=6;j>2;j--)
            if(checkFour(mat[i][j],mat[i-1][j-1],mat[i-2][j-2],mat[i-3][j-3]))
                return true ;
    return false;
}
bool checkDiagonale(int mat[row][column])
{
    return (diagonaleSensDroite(mat)||diagonaleSensGauche(mat));
}
bool check(int mat[row][column])
{
    return (checkDiagonale(mat)||checkHorizontale(mat)||checkVertical(mat));
}


int IA(SDL_Window* win,SDL_Renderer *ren,int Hardest)
{

            SDL_Event event;
            connect4 board;
            int y=602;int i=100;
            int x=258,player=1,nb=0,son=1;
            bool continuer = true;
            SDL_Rect dst;
            nouvelleparty:
            SDL_Texture* tex ;
            Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024); //Initialisation de l'API Mixer
            Mix_Music *musique;
            musique = Mix_LoadMUS("pion.mp3");
            tex= loadTexture("board.jpg", ren);
            renderTexture(tex,ren,0,0);
            if(son==-1)
            {
                tex= loadTexture("sonOff.png", ren);
                renderTexture(tex,ren,0,0);
            }
            SDL_RenderPresent(ren);

            while (continuer)
            {
                if(player==1)
                {
                    if(nb < 2 && (Hardest==1 || Hardest==2))
                    {
                        nb++;
                        int rowVide=board.returnRowVide(3);
                        board.jouer(rowVide,3,1);
                        player=-1;
                        dst.y= y-(rowVide*86);
                        dst.x=x+i*3;
                        tex= loadTexture("test1.png", ren);
                        renderTexture(tex,ren,dst.x-100,dst.y-100);
                        SDL_RenderPresent(ren);

                    }
                    else
                    {
                    tex= loadTexture("player1.png", ren);
                    renderTexture(tex,ren,1056,450);
                    SDL_RenderPresent(ren);
                    Case* col=new Case;
                    if(Hardest==3)
                        col=board.findBestMoveHard();
                    if(Hardest==2)
                        col=board.findBestMove();
                    if(Hardest==1)
                        col=board.findBestMoveEasy();
                    board.jouer(col->ligne,col->cologne,1);
                    player=-1;


                    if(col->cologne==0)
                        {dst.y= y-(col->ligne*86);
                        dst.x=x;
                        }
                    else if(col->cologne==1)
                        {dst.y= y-(col->ligne*86);
                        dst.x=x+i;
                        }
                    else if(col->cologne==2)
                        {dst.y= y-(col->ligne*86);
                        dst.x=x+i*2;
                       }
                    else if(col->cologne==3)
                        {dst.y= y-(col->ligne*86);
                        dst.x=x+i*3;
                        }
                    else if(col->cologne==4)
                        {dst.y= y-(col->ligne*86);
                        dst.x=x+i*4;
                        }
                    else if(col->cologne==5)
                        {dst.y= y-(col->ligne*86);
                        dst.x=x+i*5;
                        }
                    else if(col->cologne==6)
                        {dst.y= y-(col->ligne*86);
                        dst.x=x+i*6;
                        }


                        tex= loadTexture("test1.png", ren);
                        renderTexture(tex,ren,dst.x-100,dst.y-100);
                        SDL_RenderPresent(ren);
                     if(board.check())
                        {
                           if(son==1)
                            { musique = Mix_LoadMUS("losing.mp3");
                            Mix_PlayMusic(musique, 1);}
                            tex= loadTexture("lost.png", ren);
                            afficheinCenter(tex,ren);
                            bool keep1=true;
                            while(keep1){
                                     while (SDL_PollEvent(&event))
                                        {

                                        if (event.type == SDL_QUIT)
                                                {
                                                    SDL_DestroyTexture(tex);


                                                    return 1;
                                                }


                                        if (event.type == SDL_KEYDOWN)
                                            if(event.key.keysym.sym==SDLK_ESCAPE)
                                                {
                                                    SDL_DestroyTexture(tex);
                                                    return 1;}
                                        if(event.type==SDL_MOUSEBUTTONUP)
                                            {
                                                dst.x=event.button.x; dst.y=event.button.y;
                                                    if(dst.x< 1110&& dst.x >1023 && dst.y< 78 && dst.y > 8 )
                                                       {
                                                           son=-son;

                                                                                         if(son==-1)
                                                                                         {
                                                                                              tex= loadTexture("sonOff.png", ren);
                                                                                                renderTexture(tex,ren,0,0);
                                                                                                SDL_RenderPresent(ren);
                                                                                         }
                                                                                         else
                                                                                         {
                                                                                                tex= loadTexture("sonOn.png", ren);
                                                                                                renderTexture(tex,ren,0,0);
                                                                                                SDL_RenderPresent(ren);

                                                                                         }

                                                        }
                                                if(dst.x<631&& dst.x >440 && dst.y< 418 && dst.y > 396 )
                                                        {
                                                             SDL_DestroyTexture(tex);
                                                             return 2;
                                                        }
                                                if(dst.x< 1326&& dst.x >1223 && dst.y< 78 && dst.y > 8 )
                                                        {
                                                             SDL_DestroyTexture(tex);
                                                             return 2;
                                                        }
                                                if(dst.x< 1210&& dst.x >1123 && dst.y< 78 && dst.y > 8 )
                                                {
                                                        board.vider();
                                                        player=1;
                                                        nb=0;
                                                        SDL_RenderClear(ren);
                                                        tex= loadTexture("board.jpg", ren);
                                                        renderTexture(tex,ren,0,0);
                                                        if(son==-1)
                                                        {tex= loadTexture("sonOff.png", ren);
                                                        renderTexture(tex,ren,0,0);}
                                                        SDL_RenderPresent(ren);

                                                        keep1=false;
                                                }
                                            }
                                        }
                                }
                        }

                }
            }
            if(player==-1)
            {
                    tex= loadTexture("player2.png", ren);
                    renderTexture(tex,ren,1056,450);
                    SDL_RenderPresent(ren);
                bool keep=true;
                while(keep)
                {
                while(SDL_PollEvent(&event))
                {

                    if (event.type == SDL_QUIT)
                    {
                            SDL_DestroyTexture(tex);
                            return 1;
                    }


                if (event.type == SDL_KEYDOWN)
                    if(event.key.keysym.sym==SDLK_ESCAPE)
                      {

                            {
                                                    SDL_DestroyTexture(tex);

                                                    return 1;}

                        }


            if (event.type == SDL_MOUSEBUTTONDOWN)

            {

            dst.x=event.button.x;
            dst.y=event.button.y;
            if(dst.x< 1110&& dst.x >1023 && dst.y< 78 && dst.y > 8 )
                                                       {
                                                           son=-son;

                                                                                         if(son==-1)
                                                                                         {
                                                                                              tex= loadTexture("sonOff.png", ren);
                                                                                                renderTexture(tex,ren,0,0);
                                                                                                SDL_RenderPresent(ren);
                                                                                         }
                                                                                         else
                                                                                         {
                                                                                                tex= loadTexture("sonOn.png", ren);
                                                                                                renderTexture(tex,ren,0,0);
                                                                                                SDL_RenderPresent(ren);

                                                                                         }

                                                        }
            if(dst.x< 1326&& dst.x >1241  && dst.y< 78 && dst.y > 8 )
            {

                 SDL_DestroyTexture(tex);
                 return 2;
            }
            else if(dst.x<1235 && dst.x > 1123  && dst.y< 78 && dst.y > 8 )
                    {
                        board.vider();
                        player=1;
                        nb=0;
                        SDL_RenderClear(ren);

                        goto nouvelleparty;
                    }

            else if(dst.x < 291 && dst.x > 199) ///cologne 1
            {

                int rowVide=board.returnRowVide(0);

                dst.y= y-(rowVide*86);
                dst.x=x;
                if(rowVide!=7)
                {
                  if(son==1)
                    {musique = Mix_LoadMUS("pion.mp3");
                  Mix_PlayMusic(musique, 1);}
                  player=1;
                  board.jouer(rowVide,0,-1);
                  tex= loadTexture("test2.png", ren);
                  renderTexture(tex,ren,dst.x-100,dst.y-100);
                  SDL_RenderPresent(ren);
                  board.printBoard();
                  keep=false;
                }

            }
             else if(dst.x < 393 && dst.x >321) /// cologne 2
            {

                int rowVide=board.returnRowVide(1);
                dst.y= y-(rowVide*86);
                dst.x=x+i;
                if(rowVide!=7)
                {
                if(son==1)
                            {musique = Mix_LoadMUS("pion.mp3");
                  Mix_PlayMusic(musique, 1);}
                player=1;
                 board.jouer(rowVide,1,-1);
                  tex= loadTexture("test2.png", ren);

                  renderTexture(tex,ren,dst.x-100,dst.y-100);
                  SDL_RenderPresent(ren);

                board.printBoard();
                keep=false;
                }

            }
             else if(dst.x < 490 && dst.x > 420) /// cologne 3
            {

                int rowVide=board.returnRowVide(2);


                dst.y= y-(rowVide*86);
                dst.x=x+i*2 ;
                if(rowVide!=7)
                {
                    if(son==1)
                            {musique = Mix_LoadMUS("pion.mp3");
                  Mix_PlayMusic(musique, 1);}
                player=1;
                board.jouer(rowVide,2,-1);
                  tex= loadTexture("test2.png", ren);

                  renderTexture(tex,ren,dst.x-100,dst.y-100);
                  SDL_RenderPresent(ren);

                board.printBoard();
                keep=false;
                }

            }
             else if(dst.x < 586 && dst.x > 520)/// cologne 4
                {

                int rowVide=board.returnRowVide(3);

                dst.y= y-(rowVide*86);
                dst.x=x+i*3;
                if(rowVide!=7)
                {
                    if(son==1)
                            {musique = Mix_LoadMUS("pion.mp3");
                    Mix_PlayMusic(musique, 1);}
                    player=1;
                    board.jouer(rowVide,3,-1);
                    tex= loadTexture("test2.png", ren);
                    renderTexture(tex,ren,dst.x-100,dst.y-100);
                    SDL_RenderPresent(ren);

                board.printBoard();
                keep=false;
                }

            }
             else if(dst.x < 690 && dst.x > 623)/// cologne 5
            {

                int rowVide=board.returnRowVide(4);

                dst.y= y-(rowVide*86);
                dst.x=x+i*4;
                if(rowVide!=7)
                {
                   if(son==1)
                            { musique = Mix_LoadMUS("pion.mp3");
                            Mix_PlayMusic(musique, 1);}
                    player=1;
                    board.jouer(rowVide,4,-1);
                    tex= loadTexture("test2.png", ren);
                    renderTexture(tex,ren,dst.x-100,dst.y-100);
                    SDL_RenderPresent(ren);

                board.printBoard();
                keep=false;
                }

            }
            else  if(dst.x < 790 && dst.x > 720) ///cologne 6
            {

                int rowVide=board.returnRowVide(5);

                dst.y= y-(rowVide*86);
                dst.x=x+i*5;
                if(rowVide!=7)
                {
                    if(son==1)
                            {musique = Mix_LoadMUS("pion.mp3");
                            Mix_PlayMusic(musique, 1);}
                    player=1;
                    board.jouer(rowVide,5,-1);
                    tex= loadTexture("test2.png", ren);
                    renderTexture(tex,ren,dst.x-100,dst.y-100);
                    SDL_RenderPresent(ren);

                board.printBoard();
                keep=false;
                }

            }
            else if(dst.x < 895 && dst.x > 821) /// cologne 7
            {

                int rowVide=board.returnRowVide(6);

                dst.y= y-(rowVide*86);
                dst.x=x+i*6;
                if(rowVide!=7)
                {
                    if(son==1)
                    {musique = Mix_LoadMUS("pion.mp3");
                  Mix_PlayMusic(musique, 1);}
                    player=1;
                    board.jouer(rowVide,6,-1);
                    tex= loadTexture("test2.png", ren);
                    renderTexture(tex,ren,dst.x-100,dst.y-100);
                    SDL_RenderPresent(ren);

                    board.printBoard();
                    keep=false;
                }

            }
            }

                }
            }
             if(board.jeuFini())
                    {
                     tex= loadTexture("drawn.png", ren);
                            afficheinCenter(tex,ren);
                            bool keep1=true;
                            while(keep1){
                                     while (SDL_PollEvent(&event))
                                        {

                                        if (event.type == SDL_QUIT)
                                                {
                                                    SDL_DestroyTexture(tex);


                                                    return 1;
                                                }


                                        if (event.type == SDL_KEYDOWN)
                                            if(event.key.keysym.sym==SDLK_ESCAPE)
                                                {
                                                    SDL_DestroyTexture(tex);
                                                    return 1;}
                                        if(event.type==SDL_MOUSEBUTTONUP)
                                            {
                                                dst.x=event.button.x; dst.y=event.button.y;
                                                    if(dst.x< 1110&& dst.x >1023 && dst.y< 78 && dst.y > 8 )
                                                       {
                                                           son=-son;

                                                                                         if(son==-1)
                                                                                         {
                                                                                              tex= loadTexture("sonOff.png", ren);
                                                                                                renderTexture(tex,ren,0,0);
                                                                                                SDL_RenderPresent(ren);
                                                                                         }
                                                                                         else
                                                                                         {
                                                                                                tex= loadTexture("sonOn.png", ren);
                                                                                                renderTexture(tex,ren,0,0);
                                                                                                SDL_RenderPresent(ren);

                                                                                         }

                                                        }
                                                if(dst.x<631&& dst.x >440 && dst.y< 418 && dst.y > 396 )
                                                        {
                                                             SDL_DestroyTexture(tex);
                                                             return 2;
                                                        }
                                                if(dst.x< 1326&& dst.x >1123 && dst.y< 78 && dst.y > 8 )
                                                        {
                                                             SDL_DestroyTexture(tex);
                                                             return 2;
                                                        }
                                                if(dst.x< 1210&& dst.x >1123 && dst.y< 78 && dst.y > 8 )
                                                {
                                                        board.vider();
                                                        player=1;
                                                        nb=0;
                                                        SDL_RenderClear(ren);
                                                        tex= loadTexture("board.jpg", ren);
                                                        renderTexture(tex,ren,0,0);
                                                        if(son==-1)
                                                        {tex= loadTexture("sonOff.png", ren);
                                                        renderTexture(tex,ren,0,0);}
                                                        SDL_RenderPresent(ren);

                                                        keep1=false;
                                                }
                                            }
                                        }
                                }
                        }
                    if(board.check())
                    {
                        if(son==1)
                            {musique = Mix_LoadMUS("winning.mp3");
                            Mix_PlayMusic(musique, 1);}
                            tex= loadTexture("win.png", ren);
                            afficheinCenter(tex,ren);
                            bool keep2=true;
                            while(keep2){
                                     while (SDL_PollEvent(&event))
                                        {

                                        if (event.type == SDL_QUIT)
                                                {
                                                    SDL_DestroyTexture(tex);


                                                    return 1;
                                                }


                                        if (event.type == SDL_KEYDOWN)
                                            if(event.key.keysym.sym==SDLK_ESCAPE)
                                                {
                                                    SDL_DestroyTexture(tex);
                                                    return 1;}
                                        if(event.type==SDL_MOUSEBUTTONUP)
                                            {
                                                dst.x=event.button.x; dst.y=event.button.y;
                                                    if(dst.x< 1110&& dst.x >1023 && dst.y< 78 && dst.y > 8 )
                                                       {
                                                           son=-son;

                                                                                         if(son==-1)
                                                                                         {
                                                                                              tex= loadTexture("sonOff.png", ren);
                                                                                                renderTexture(tex,ren,0,0);
                                                                                                SDL_RenderPresent(ren);
                                                                                         }
                                                                                         else
                                                                                         {
                                                                                                tex= loadTexture("sonOn.png", ren);
                                                                                                renderTexture(tex,ren,0,0);
                                                                                                SDL_RenderPresent(ren);

                                                                                         }

                                                        }
                                                if(dst.x<631&& dst.x >440 && dst.y< 418 && dst.y > 396 )
                                                        {
                                                             SDL_DestroyTexture(tex);
                                                             return 2;
                                                        }
                                                if(dst.x< 1326&& dst.x >1223 && dst.y< 78 && dst.y > 8 )
                                                        {
                                                             SDL_DestroyTexture(tex);
                                                             return 2;
                                                        }
                                                if(dst.x< 1210&& dst.x >1123 && dst.y< 78 && dst.y > 8 )
                                                {
                                                        board.vider();
                                                        player=1;
                                                        nb=0;
                                                        SDL_RenderClear(ren);
                                                        tex= loadTexture("board.jpg", ren);
                                                        renderTexture(tex,ren,0,0);
                                                        if(son==-1)
                                                        {tex= loadTexture("sonOff.png", ren);
                                                        renderTexture(tex,ren,0,0);}
                                                        SDL_RenderPresent(ren);
                                                        keep2=false;
                                                }
                                            }
                                        }
                                }
                        }


            }
            }
}
int multiGamer(SDL_Window* win,SDL_Renderer *ren)
{

            SDL_Event event;
            connect4 board;
            int y=602;int i=100;
            int x=258,player=1,nb=0,son=1;
            bool continuer = true;
            SDL_Rect dst;
            nouvelleparty:
            SDL_Texture* tex ;
            Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024); //Initialisation de l'API Mixer
            Mix_Music *musique;
            musique = Mix_LoadMUS("pion.mp3");
            tex= loadTexture("board.jpg", ren);
            renderTexture(tex,ren,0,0);
            if(son==-1)
            {
                tex= loadTexture("sonOff.png", ren);
                renderTexture(tex,ren,0,0);
            }
            SDL_RenderPresent(ren);

            while (continuer)
            {
                if(player==1)
                {
                tex= loadTexture("player1.png", ren);
                renderTexture(tex,ren,1056,450);
                SDL_RenderPresent(ren);
                bool keep=true;
                while(keep)
                {
                while(SDL_PollEvent(&event))
                {

                    if (event.type == SDL_QUIT)
                    {
                            SDL_DestroyTexture(tex);
                            return 1;
                    }


                if (event.type == SDL_KEYDOWN)
                    if(event.key.keysym.sym==SDLK_ESCAPE)
                      {

                            {
                                                    SDL_DestroyTexture(tex);

                                                    return 1;}

                        }


            if (event.type == SDL_MOUSEBUTTONDOWN)

            {

            dst.x=event.button.x;
            dst.y=event.button.y;
            if(dst.x< 1110&& dst.x >1023 && dst.y< 78 && dst.y > 8 )
                                                       {
                                                           son=-son;

                                                                                         if(son==-1)
                                                                                         {
                                                                                              tex= loadTexture("sonOff.png", ren);
                                                                                                renderTexture(tex,ren,0,0);
                                                                                                SDL_RenderPresent(ren);
                                                                                         }
                                                                                         else
                                                                                         {
                                                                                                tex= loadTexture("sonOn.png", ren);
                                                                                                renderTexture(tex,ren,0,0);
                                                                                                SDL_RenderPresent(ren);

                                                                                         }

                                                        }
            if(dst.x< 1326&& dst.x >1241  && dst.y< 78 && dst.y > 8 )
            {

                 SDL_DestroyTexture(tex);
                 return 2;
            }
            else if(dst.x<1235 && dst.x > 1123  && dst.y< 78 && dst.y > 8 )
                    {
                        board.vider();
                        player=1;
                        nb=0;
                        SDL_RenderClear(ren);

                        goto nouvelleparty;
                    }

            else if(dst.x < 291 && dst.x > 199) ///cologne 1
            {

                int rowVide=board.returnRowVide(0);

                dst.y= y-(rowVide*86);
                dst.x=x;
                if(rowVide!=7)
                {
                  if(son==1)
                    {musique = Mix_LoadMUS("pion.mp3");
                  Mix_PlayMusic(musique, 1);}
                  player=-1;
                  board.jouer(rowVide,0,1);
                  tex= loadTexture("test1.png", ren);
                  renderTexture(tex,ren,dst.x-100,dst.y-100);
                  SDL_RenderPresent(ren);
                  board.printBoard();
                  keep=false;
                }

            }
             else if(dst.x < 393 && dst.x >321) /// cologne 2
            {

                int rowVide=board.returnRowVide(1);
                dst.y= y-(rowVide*86);
                dst.x=x+i;
                if(rowVide!=7)
                {
                if(son==1)
                            {musique = Mix_LoadMUS("pion.mp3");
                  Mix_PlayMusic(musique, 1);}
                player=-1;
                 board.jouer(rowVide,1,1);
                  tex= loadTexture("test1.png", ren);

                  renderTexture(tex,ren,dst.x-100,dst.y-100);
                  SDL_RenderPresent(ren);

                board.printBoard();
                keep=false;
                }

            }
             else if(dst.x < 490 && dst.x > 420) /// cologne 3
            {

                int rowVide=board.returnRowVide(2);


                dst.y= y-(rowVide*86);
                dst.x=x+i*2 ;
                if(rowVide!=7)
                {
                    if(son==1)
                            {musique = Mix_LoadMUS("pion.mp3");
                  Mix_PlayMusic(musique, 1);}
                player=-1;
                board.jouer(rowVide,2,1);
                  tex= loadTexture("test1.png", ren);

                  renderTexture(tex,ren,dst.x-100,dst.y-100);
                  SDL_RenderPresent(ren);

                board.printBoard();
                keep=false;
                }

            }
             else if(dst.x < 586 && dst.x > 520)/// cologne 4
                {

                int rowVide=board.returnRowVide(3);

                dst.y= y-(rowVide*86);
                dst.x=x+i*3;
                if(rowVide!=7)
                {
                    if(son==1)
                            {musique = Mix_LoadMUS("pion.mp3");
                    Mix_PlayMusic(musique, 1);}
                    player=-1;
                    board.jouer(rowVide,3,1);
                    tex= loadTexture("test1.png", ren);
                    renderTexture(tex,ren,dst.x-100,dst.y-100);
                    SDL_RenderPresent(ren);

                board.printBoard();
                keep=false;
                }

            }
             else if(dst.x < 690 && dst.x > 623)/// cologne 5
            {

                int rowVide=board.returnRowVide(4);

                dst.y= y-(rowVide*86);
                dst.x=x+i*4;
                if(rowVide!=7)
                {
                   if(son==1)
                            { musique = Mix_LoadMUS("pion.mp3");
                            Mix_PlayMusic(musique, 1);}
                    player=-1;
                    board.jouer(rowVide,4,1);
                    tex= loadTexture("test1.png", ren);
                    renderTexture(tex,ren,dst.x-100,dst.y-100);
                    SDL_RenderPresent(ren);

                board.printBoard();
                keep=false;
                }

            }
            else  if(dst.x < 790 && dst.x > 720) ///cologne 6
            {

                int rowVide=board.returnRowVide(5);

                dst.y= y-(rowVide*86);
                dst.x=x+i*5;
                if(rowVide!=7)
                {
                    if(son==1)
                            {musique = Mix_LoadMUS("pion.mp3");
                            Mix_PlayMusic(musique, 1);}
                    player=-1;
                    board.jouer(rowVide,5,1);
                    tex= loadTexture("test1.png", ren);
                    renderTexture(tex,ren,dst.x-100,dst.y-100);
                    SDL_RenderPresent(ren);

                board.printBoard();
                keep=false;
                }

            }
            else if(dst.x < 895 && dst.x > 821) /// cologne 7
            {

                int rowVide=board.returnRowVide(6);

                dst.y= y-(rowVide*86);
                dst.x=x+i*6;
                if(rowVide!=7)
                {
                    if(son==1)
                    {musique = Mix_LoadMUS("pion.mp3");
                  Mix_PlayMusic(musique, 1);}
                    player=-1;
                    board.jouer(rowVide,6,1);
                    tex= loadTexture("test1.png", ren);
                    renderTexture(tex,ren,dst.x-100,dst.y-100);
                    SDL_RenderPresent(ren);

                    board.printBoard();
                    keep=false;
                }

            }
            }

                }
            }
             if(board.jeuFini())
                    {
                     tex= loadTexture("drawn.png", ren);
                            afficheinCenter(tex,ren);
                            bool keep1=true;
                            while(keep1){
                                     while (SDL_PollEvent(&event))
                                        {

                                        if (event.type == SDL_QUIT)
                                                {
                                                    SDL_DestroyTexture(tex);


                                                    return 1;
                                                }


                                        if (event.type == SDL_KEYDOWN)
                                            if(event.key.keysym.sym==SDLK_ESCAPE)
                                                {
                                                    SDL_DestroyTexture(tex);
                                                    return 1;}
                                        if(event.type==SDL_MOUSEBUTTONUP)
                                            {
                                                dst.x=event.button.x; dst.y=event.button.y;
                                                    if(dst.x< 1110&& dst.x >1023 && dst.y< 78 && dst.y > 8 )
                                                       {
                                                           son=-son;

                                                                                         if(son==-1)
                                                                                         {
                                                                                              tex= loadTexture("sonOff.png", ren);
                                                                                                renderTexture(tex,ren,0,0);
                                                                                                SDL_RenderPresent(ren);
                                                                                         }
                                                                                         else
                                                                                         {
                                                                                                tex= loadTexture("sonOn.png", ren);
                                                                                                renderTexture(tex,ren,0,0);
                                                                                                SDL_RenderPresent(ren);

                                                                                         }

                                                        }
                                                if(dst.x<631&& dst.x >440 && dst.y< 418 && dst.y > 396 )
                                                        {
                                                             SDL_DestroyTexture(tex);
                                                             return 2;
                                                        }
                                                if(dst.x< 1326&& dst.x >1123 && dst.y< 78 && dst.y > 8 )
                                                        {
                                                             SDL_DestroyTexture(tex);
                                                             return 2;
                                                        }
                                                if(dst.x< 1210&& dst.x >1123 && dst.y< 78 && dst.y > 8 )
                                                {
                                                        board.vider();
                                                        player=1;
                                                        SDL_RenderClear(ren);
                                                        tex= loadTexture("board.jpg", ren);
                                                        renderTexture(tex,ren,0,0);
                                                        if(son==-1)
                                                        {tex= loadTexture("sonOff.png", ren);
                                                        renderTexture(tex,ren,0,0);}
                                                        SDL_RenderPresent(ren);

                                                        keep1=false;
                                                }
                                            }
                                        }
                                }
                        }
                    if(board.check())
                    {
                        if(son==1)
                            {musique = Mix_LoadMUS("winning.mp3");
                            Mix_PlayMusic(musique, 1);}
                            tex= loadTexture("win1.png", ren);
                            afficheinCenter(tex,ren);
                            bool keep2=true;
                            while(keep2){
                                     while (SDL_PollEvent(&event))
                                        {

                                        if (event.type == SDL_QUIT)
                                                {
                                                    SDL_DestroyTexture(tex);


                                                    return 1;
                                                }


                                        if (event.type == SDL_KEYDOWN)
                                            if(event.key.keysym.sym==SDLK_ESCAPE)
                                                {
                                                    SDL_DestroyTexture(tex);
                                                    return 1;}
                                        if(event.type==SDL_MOUSEBUTTONUP)
                                            {
                                                dst.x=event.button.x; dst.y=event.button.y;
                                                    if(dst.x< 1110&& dst.x >1023 && dst.y< 78 && dst.y > 8 )
                                                       {
                                                           son=-son;

                                                                                         if(son==-1)
                                                                                         {
                                                                                              tex= loadTexture("sonOff.png", ren);
                                                                                                renderTexture(tex,ren,0,0);
                                                                                                SDL_RenderPresent(ren);
                                                                                         }
                                                                                         else
                                                                                         {
                                                                                                tex= loadTexture("sonOn.png", ren);
                                                                                                renderTexture(tex,ren,0,0);
                                                                                                SDL_RenderPresent(ren);

                                                                                         }

                                                        }
                                                if(dst.x<631&& dst.x >440 && dst.y< 418 && dst.y > 396 )
                                                        {
                                                             SDL_DestroyTexture(tex);
                                                             return 2;
                                                        }
                                                if(dst.x< 1326&& dst.x >1223 && dst.y< 78 && dst.y > 8 )
                                                        {
                                                             SDL_DestroyTexture(tex);
                                                             return 2;
                                                        }
                                                if(dst.x< 1210&& dst.x >1123 && dst.y< 78 && dst.y > 8 )
                                                {
                                                        board.vider();
                                                        player=1;

                                                        SDL_RenderClear(ren);
                                                        tex= loadTexture("board.jpg", ren);
                                                        renderTexture(tex,ren,0,0);
                                                        if(son==-1)
                                                        {tex= loadTexture("sonOff.png", ren);
                                                        renderTexture(tex,ren,0,0);}
                                                        SDL_RenderPresent(ren);
                                                        keep2=false;
                                                }
                                            }
                                        }
                                }
                        }


            }

            if(player==-1)
            {

                tex= loadTexture("player2.png", ren);
                renderTexture(tex,ren,1056,450);
                SDL_RenderPresent(ren);
                bool keep=true;
                while(keep)
                {
                while(SDL_PollEvent(&event))
                {

                    if (event.type == SDL_QUIT)
                    {
                            SDL_DestroyTexture(tex);
                            return 1;
                    }


                if (event.type == SDL_KEYDOWN)
                    if(event.key.keysym.sym==SDLK_ESCAPE)
                      {

                            {
                                                    SDL_DestroyTexture(tex);

                                                    return 1;}

                        }


            if (event.type == SDL_MOUSEBUTTONDOWN)

            {

            dst.x=event.button.x;
            dst.y=event.button.y;
            if(dst.x< 1110&& dst.x >1023 && dst.y< 78 && dst.y > 8 )
                                                       {
                                                           son=-son;

                                                                                         if(son==-1)
                                                                                         {
                                                                                              tex= loadTexture("sonOff.png", ren);
                                                                                                renderTexture(tex,ren,0,0);
                                                                                                SDL_RenderPresent(ren);
                                                                                         }
                                                                                         else
                                                                                         {
                                                                                                tex= loadTexture("sonOn.png", ren);
                                                                                                renderTexture(tex,ren,0,0);
                                                                                                SDL_RenderPresent(ren);

                                                                                         }

                                                        }
            if(dst.x< 1326&& dst.x >1241  && dst.y< 78 && dst.y > 8 )
            {

                 SDL_DestroyTexture(tex);
                 return 2;
            }
            else if(dst.x<1235 && dst.x > 1123  && dst.y< 78 && dst.y > 8 )
                    {
                        board.vider();
                        player=1;
                        nb=0;
                        SDL_RenderClear(ren);

                        goto nouvelleparty;
                    }

            else if(dst.x < 291 && dst.x > 199) ///cologne 1
            {

                int rowVide=board.returnRowVide(0);

                dst.y= y-(rowVide*86);
                dst.x=x;
                if(rowVide!=7)
                {
                  if(son==1)
                    {musique = Mix_LoadMUS("pion.mp3");
                  Mix_PlayMusic(musique, 1);}
                  player=1;
                  board.jouer(rowVide,0,-1);
                  tex= loadTexture("test2.png", ren);
                  renderTexture(tex,ren,dst.x-100,dst.y-100);
                  SDL_RenderPresent(ren);
                  board.printBoard();
                  keep=false;
                }

            }
             else if(dst.x < 393 && dst.x >321) /// cologne 2
            {

                int rowVide=board.returnRowVide(1);
                dst.y= y-(rowVide*86);
                dst.x=x+i;
                if(rowVide!=7)
                {
                if(son==1)
                            {musique = Mix_LoadMUS("pion.mp3");
                  Mix_PlayMusic(musique, 1);}
                player=1;
                 board.jouer(rowVide,1,-1);
                  tex= loadTexture("test2.png", ren);

                  renderTexture(tex,ren,dst.x-100,dst.y-100);
                  SDL_RenderPresent(ren);

                board.printBoard();
                keep=false;
                }

            }
             else if(dst.x < 490 && dst.x > 420) /// cologne 3
            {

                int rowVide=board.returnRowVide(2);


                dst.y= y-(rowVide*86);
                dst.x=x+i*2 ;
                if(rowVide!=7)
                {
                    if(son==1)
                            {musique = Mix_LoadMUS("pion.mp3");
                  Mix_PlayMusic(musique, 1);}
                player=1;
                board.jouer(rowVide,2,-1);
                  tex= loadTexture("test2.png", ren);

                  renderTexture(tex,ren,dst.x-100,dst.y-100);
                  SDL_RenderPresent(ren);

                board.printBoard();
                keep=false;
                }

            }
             else if(dst.x < 586 && dst.x > 520)/// cologne 4
                {

                int rowVide=board.returnRowVide(3);

                dst.y= y-(rowVide*86);
                dst.x=x+i*3;
                if(rowVide!=7)
                {
                    if(son==1)
                            {musique = Mix_LoadMUS("pion.mp3");
                    Mix_PlayMusic(musique, 1);}
                    player=1;
                    board.jouer(rowVide,3,-1);
                    tex= loadTexture("test2.png", ren);
                    renderTexture(tex,ren,dst.x-100,dst.y-100);
                    SDL_RenderPresent(ren);

                board.printBoard();
                keep=false;
                }

            }
             else if(dst.x < 690 && dst.x > 623)/// cologne 5
            {

                int rowVide=board.returnRowVide(4);

                dst.y= y-(rowVide*86);
                dst.x=x+i*4;
                if(rowVide!=7)
                {
                   if(son==1)
                            { musique = Mix_LoadMUS("pion.mp3");
                            Mix_PlayMusic(musique, 1);}
                    player=1;
                    board.jouer(rowVide,4,-1);
                    tex= loadTexture("test2.png", ren);
                    renderTexture(tex,ren,dst.x-100,dst.y-100);
                    SDL_RenderPresent(ren);

                board.printBoard();
                keep=false;
                }

            }
            else  if(dst.x < 790 && dst.x > 720) ///cologne 6
            {

                int rowVide=board.returnRowVide(5);

                dst.y= y-(rowVide*86);
                dst.x=x+i*5;
                if(rowVide!=7)
                {
                    if(son==1)
                            {musique = Mix_LoadMUS("pion.mp3");
                            Mix_PlayMusic(musique, 1);}
                    player=1;
                    board.jouer(rowVide,5,-1);
                    tex= loadTexture("test2.png", ren);
                    renderTexture(tex,ren,dst.x-100,dst.y-100);
                    SDL_RenderPresent(ren);

                board.printBoard();
                keep=false;
                }

            }
            else if(dst.x < 895 && dst.x > 821) /// cologne 7
            {

                int rowVide=board.returnRowVide(6);

                dst.y= y-(rowVide*86);
                dst.x=x+i*6;
                if(rowVide!=7)
                {
                    if(son==1)
                    {musique = Mix_LoadMUS("pion.mp3");
                  Mix_PlayMusic(musique, 1);}
                    player=1;
                    board.jouer(rowVide,6,-1);
                    tex= loadTexture("test2.png", ren);
                    renderTexture(tex,ren,dst.x-100,dst.y-100);
                    SDL_RenderPresent(ren);

                    board.printBoard();
                    keep=false;
                }

            }
            }

                }
            }
             if(board.jeuFini())
                    {
                     tex= loadTexture("drawn.png", ren);
                            afficheinCenter(tex,ren);
                            bool keep1=true;
                            while(keep1){
                                     while (SDL_PollEvent(&event))
                                        {

                                        if (event.type == SDL_QUIT)
                                                {
                                                    SDL_DestroyTexture(tex);


                                                    return 1;
                                                }


                                        if (event.type == SDL_KEYDOWN)
                                            if(event.key.keysym.sym==SDLK_ESCAPE)
                                                {
                                                    SDL_DestroyTexture(tex);
                                                    return 1;}
                                        if(event.type==SDL_MOUSEBUTTONUP)
                                            {
                                                dst.x=event.button.x; dst.y=event.button.y;
                                                    if(dst.x< 1110&& dst.x >1023 && dst.y< 78 && dst.y > 8 )
                                                       {
                                                           son=-son;

                                                                                         if(son==-1)
                                                                                         {
                                                                                              tex= loadTexture("sonOff.png", ren);
                                                                                                renderTexture(tex,ren,0,0);
                                                                                                SDL_RenderPresent(ren);
                                                                                         }
                                                                                         else
                                                                                         {
                                                                                                tex= loadTexture("sonOn.png", ren);
                                                                                                renderTexture(tex,ren,0,0);
                                                                                                SDL_RenderPresent(ren);

                                                                                         }

                                                        }
                                                if(dst.x<631&& dst.x >440 && dst.y< 418 && dst.y > 396 )
                                                        {
                                                             SDL_DestroyTexture(tex);
                                                             return 2;
                                                        }
                                                if(dst.x< 1326&& dst.x >1123 && dst.y< 78 && dst.y > 8 )
                                                        {
                                                             SDL_DestroyTexture(tex);
                                                             return 2;
                                                        }
                                                if(dst.x< 1210&& dst.x >1123 && dst.y< 78 && dst.y > 8 )
                                                {
                                                        board.vider();
                                                        player=1;
                                                        nb=0;
                                                        SDL_RenderClear(ren);
                                                        tex= loadTexture("board.jpg", ren);
                                                        renderTexture(tex,ren,0,0);
                                                        if(son==-1)
                                                        {tex= loadTexture("sonOff.png", ren);
                                                        renderTexture(tex,ren,0,0);}
                                                        SDL_RenderPresent(ren);

                                                        keep1=false;
                                                }
                                            }
                                        }
                                }
                        }
                    if(board.check())
                    {
                        if(son==1)
                            {musique = Mix_LoadMUS("winning.mp3");
                            Mix_PlayMusic(musique, 1);}
                            tex= loadTexture("win2.png", ren);
                            afficheinCenter(tex,ren);
                            bool keep2=true;
                            while(keep2){
                                     while (SDL_PollEvent(&event))
                                        {

                                        if (event.type == SDL_QUIT)
                                                {
                                                    SDL_DestroyTexture(tex);


                                                    return 1;
                                                }


                                        if (event.type == SDL_KEYDOWN)
                                            if(event.key.keysym.sym==SDLK_ESCAPE)
                                                {
                                                    SDL_DestroyTexture(tex);
                                                    return 1;}
                                        if(event.type==SDL_MOUSEBUTTONUP)
                                            {
                                                dst.x=event.button.x; dst.y=event.button.y;
                                                    if(dst.x< 1110&& dst.x >1023 && dst.y< 78 && dst.y > 8 )
                                                       {
                                                           son=-son;

                                                                                         if(son==-1)
                                                                                         {
                                                                                              tex= loadTexture("sonOff.png", ren);
                                                                                                renderTexture(tex,ren,0,0);
                                                                                                SDL_RenderPresent(ren);
                                                                                         }
                                                                                         else
                                                                                         {
                                                                                                tex= loadTexture("sonOn.png", ren);
                                                                                                renderTexture(tex,ren,0,0);
                                                                                                SDL_RenderPresent(ren);

                                                                                         }

                                                        }
                                                if(dst.x<631&& dst.x >440 && dst.y< 418 && dst.y > 396 )
                                                        {
                                                             SDL_DestroyTexture(tex);
                                                             return 2;
                                                        }
                                                if(dst.x< 1326&& dst.x >1223 && dst.y< 78 && dst.y > 8 )
                                                        {
                                                             SDL_DestroyTexture(tex);
                                                             return 2;
                                                        }
                                                if(dst.x< 1210&& dst.x >1123 && dst.y< 78 && dst.y > 8 )
                                                {
                                                        board.vider();
                                                        player=1;
                                                        nb=0;
                                                        SDL_RenderClear(ren);
                                                        tex= loadTexture("board.jpg", ren);
                                                        renderTexture(tex,ren,0,0);
                                                        if(son==-1)
                                                        {tex= loadTexture("sonOff.png", ren);
                                                        renderTexture(tex,ren,0,0);}
                                                        SDL_RenderPresent(ren);
                                                        keep2=false;
                                                }
                                            }
                                        }
                                }
                        }


            }
            }
}
