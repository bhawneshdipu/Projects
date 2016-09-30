#include<iostream>
#include<cstdlib>
#include<windows.h>
#include <conio.h>
 
using namespace std;
class Snake
{
	public:
	char M[20][60];   // 20 down, 60 wide is appropriate screen size
	int past[1000][2]; //second bracket: 0 is up, 1 is side
    int len; //number of snake pieces
    
    int pastCounter;  //used in the use of past
    int direction;
    int apples;
    int score;
    int quit;
		
		
		
		
		public:
			
			Snake()
		{

		   len=3; 
    		 pastCounter = 1;  
     		direction = 0;
     		apples = 0;
     		score = 0;
     		quit = 0;
			
			
			
			
			
			
			for(int i=0;i<20;i++)
			{
				for(int j=0;j<60;j++)
				{
					M[i][j]=' ';
				}
			}
			
		
			
			 for(int x=0;x<500;x++)
				{
        			for(int y=0;y<2;y++)
        			{
            			past [x][y] = 0;
        			}
    			}
				  past[pastCounter][0] = 1; //keep the game from crashing because if you hit the wall it kicks you from the wall
  				  past[pastCounter][1] = 1;
		}
		
			
			
/*----------------------------------------------------------------------*/
			
			
	void check (int &direction)
	{//checks if there has been user input
   		int key = 0;
		if (kbhit())
		{
        key = -getch();
       	 switch (key)
        {
        case -72:
            direction = 2;
            break;  //up
        case -77:
            direction = 0;
            break; //right
        case -80:
            direction = 3;
            break; //down
        case -75:
            direction = 1;
            break; //left
        }
    }
}
    
		void show()
		{
			for(int i=0;i<20;i++)
			{
				for(int j=0;j<60;j++)
				{
					cout<<M[i][j];
				}
				cout<<"\n";
			}
		}
		
/*---------------------------------------------------------------------------*/




void directionn(int direction, int &pastCounter, int past[][2])
{//based on user input, detects which directing the snake head should be going
    int right;//adding to the array itself did not work, so i worked around it.
    int down;
    right = past[pastCounter][1];
    down = past[pastCounter][0];
    switch (direction)
    {  //directs the snake based on direction
    case 0:
        right ++;
        break;
    case 1:
        right --;
        break;
    case 2:
        down --;
        break;
    case 3:
        down ++;
    }
 
    pastCounter ++;
    past[pastCounter][0] = down;
    past[pastCounter][1] = right;
}





/*----------------------------------------------------------------------------*/
void reset(char main[][60])
{//resets the array to keep it from being filled with parts of snake that shouldn't be there after the snake has moved on
    for (int x = 0; x <20; x++)
        {
            for (int y = 0; y <60; y++)
            {
                if (main[x][y] == '@')
                {  //doesn't reset the apples
                    main[x][y] == '@';
                }
                else
                {
                    if (x == 0 || x == 19 || y == 0 || y == 59)
                    {//doesnt reset the border
                        main[x][y] = '#';
                    }
                    else
                    {
                        main[x][y] = ' ';
                    }
                }
            }
        }
}
 
	
	
/*--------------------------------------------------------------------------------*/
		
void move(char main[][60], int &parts, int pastCounter, int past[][2], int &apples, int &score, int &quit)
{//moves the snake head, and has the body follow it
    if (past[pastCounter][0] == 19 || past[pastCounter][0] == 0)
    {  //if te snake is on the border of the game you loose
        quit = 1;
    }
    if (past[pastCounter][1] == 59 || past[pastCounter][1] == 0)
    {
        quit = 1;
    }
 
    for (int x = 0; x < parts; x++)
    {
        if (main[past[pastCounter - x][0]][past[pastCounter - x][1]] == '@')
        {  //if the snake (technically any part of the snake) eats and apple...
            apples--;
            parts++;
            score += 10;
        }
        if (main[past[pastCounter - x][0]][past[pastCounter - x][1]] == 'o')
        {  //if the snake eats itself
            quit = 1;
        }
        else
        {  //else the snakes new location is determined
        main[past[pastCounter - x][0]][past[pastCounter - x][1]] = 'o';
        }
    }
}
/*--------------------------------------------------------------------------------*/


void apple (int &apples, char main[][60])
{//places apples on the screen
    int up = 0;
    int left = 0;
    apples = 3;
 
    for (int x = 0; x < apples; x ++)
    { //places appples, only if theres no border of part of the snake already in the space
        up = (rand() % 19);
        left = (rand() % 58);
 
        if (main[up][left] == 'o')
        {
            apple(apples, main);
        }
        /*if (main[up][left] == '*')
        {
            apple(apples, main);
        }*/
        else
        {
            main[up][left] = '@';
        }
    }
}


/*---------------------------------------------------------------------------------*/	

void quitGame (int score)
{//quits and displays score
    int quit = 0;
    system ("cls");
    cout<<"GAME OVER!!!!\n\n";
    cout<<"You got score of "<<score<<endl;
 
 
}




};
int main()
{

Snake s;

int x;
cout<<"       Welcome to Snake Game:\n";
cout<<"       -------------------------\n";
cout<<"BY:---\n Amit Kumar\nBhawnesh Dipu\n\n\n";
cout<<"1: To Play Game:\n2:Exit\n";
cin>>x;
if(x==1)
    {
    while(s.quit == 0)
    {  //main rotation through all the game's functions.
    	system("cls");
    
    	
        s.show();
        s.check(s.direction);
        s.directionn(s.direction,s.pastCounter,s.past);
        s.reset(s.M);
    	s.move(s.M,s.len,s.pastCounter,s.past,s.apples,s.score,s.quit);
        Sleep(25); //pause to keep the game a normal speed...
        if (s.apples == 0)
        {  //place more apples only if they are all gone
            s.apple(s.apples,s.M);
        }
        
       
    }
    s.quitGame(s.score);
	}else
	s.quitGame(s.score);
	cout<<"Good Bye\n";
 
}
