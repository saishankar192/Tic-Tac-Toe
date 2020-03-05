/*
   SUBJECT NUMBER : MA61008
   SUBJECT NAME   : ARTIFICIAL INTELLIGENCE
   ASSIGNMENT 1   : TIC-TAC-TOE

   Group Members:
   1. 16CE10022 - K SAI SHANKAR
   2. 16IE10013 - K KRISHNA PRIYA
   3. 16IE10033 - AADITYA KUMAR SINGH
   4. 18CS30011 - SMAYAN DAS
   5. 19EE91R06 - M RAVI CHANDRA
*/

#include<bits/stdc++.h>
using namespace std;

//Initializing the 3*3 tictactoe board
char tictactoe[3][3]={{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};

//Function to print the tictactoe board
void Print_Tictactoe()
{
    cout<<"Printing current state of TicTacToe: "<<endl;
    cout<<"-------"<<endl;
    for(int i=0;i<3;i++)
    {
        cout<<"|";
        for(int j=0;j<3;j++)
        {
            cout<<tictactoe[i][j]<<"|";
        }
        cout<<endl<<"-------"<<endl;
    }
    return;
}

/*Checks if a particular block of the board is empty and fills the given character
  and return true, in other case returns false*/
bool check_and_fill(int n,char chr)
{
    int r,c;
    //Finding the row of the block number
    if(n<=3)
    {
        r=0;
    }
    else if(n<=6)
    {
        r=1;
    }
    else
    {
        r=2;
    }
    //Finding the column of the block number
    if(n%3==0)
    {
        c=2;
    }
    else
    {
        c = (n%3)-1;
    }
    if(tictactoe[r][c]==' ')
    {
        tictactoe[r][c]=chr;
        return true; /*Successfully filled the given character in given block*/
    }
    return false;/*Given block is not empty*/
}

/*Checks if there is any winning possibility for a given character
  all across the board as per the status of the board */
int winning_slot(char chr)
{
    int i,j,c1,c2,n;
    //Checks horizontal winning possibility
    for(i=0;i<3;i++)
    {
        c1 =0;
        c2 =0;
        for(j=0;j<3;j++)
        {
            if(tictactoe[i][j]==chr)
            {
                c1++;
            }
            else if(tictactoe[i][j]==' ')
            {
                c2++;
                n = (i*3)+j+1;
            }
        }
        if(c1==2 && c2==1)
        {
            return n;
        }
    }
    //Checks vertical winning possibility
    for(i=0;i<3;i++)
    {
        c1 =0;
        c2 =0;
        for(j=0;j<3;j++)
        {
            if(tictactoe[j][i]==chr)
            {
                c1++;
            }
            else if(tictactoe[j][i]==' ')
            {
                c2++;
                n = (j*3)+i+1;
            }
        }
        if(c1==2 && c2==1)
        {
            return n;
        }
    }
    c1=0;
    c2=0;
    //Checks left diagonal winning possibility
    for(i=0;i<3;i++)
    {
        if(tictactoe[i][i]==chr)
        {
            c1++;
        }
        else if(tictactoe[i][i]==' ')
        {
            c2++;
            n = (i*3)+i+1;
        }
        if(c1==2 && c2==1)
        {
            return n;
        }
    }
    c1=0;
    c2=0;
    j=0;
    //Checks right diagonal winning possibility
    for(i=2;i>=0;i--)
    {
        if(tictactoe[j][i]==chr)
        {
            c1++;
        }
        else if(tictactoe[j][i]==' ')
        {
            c2++;
            n = (j*3)+(i+1);
        }
        if(c1==2 && c2==1)
        {
            return n;
        }
        j++;
    }
    return 0;
}

/*In case there is no possible move for CPU either to defend the player's win or to win itself
  then we choose to select any empty block with below preferred order */
void fill_random(char chr)
{
    if(tictactoe[0][0]==' ')
    {
        tictactoe[0][0]=chr;
    }
    else if(tictactoe[0][2]==' ')
    {
        tictactoe[0][2]=chr;
    }
    else if(tictactoe[2][0]==' ')
    {
        tictactoe[2][0]=chr;
    }
    else if(tictactoe[2][2]==' ')
    {
        tictactoe[2][2]=chr;
    }
    else if(tictactoe[0][1]==' ')
    {
        tictactoe[0][1]=chr;
    }
    else if(tictactoe[1][0]==' ')
    {
        tictactoe[1][0]=chr;
    }
    else if(tictactoe[1][2]==' ')
    {
        tictactoe[1][2]=chr;
    }
    else if(tictactoe[2][1]==' ')
    {
        tictactoe[2][1]=chr;
    }
    else
    {
        tictactoe[1][1]=chr;
    }
    return;
}

//Main function
int main()
{
    //Indefinite while loop that breaks on player's choice to quit playing
    while(1)
    {
        int choose_player,chs_block,w,win=0,path=0,cnt=0;
        bool temp;
        //To redirect in case the player chooses something other than 1 or 2 for choose_player variable
        restart:
        cout<<"Choose whether you want to be Player1(press 1) or Player2(press 2): ";
        cin>>choose_player;
        //In case the player chose to go 1st
        if(choose_player==1)
        {
            //As there are 9 moves in total
            while(cnt<9)
            {
                Print_Tictactoe();
                //This condition is satisfied only for the player's turn
                if(!(cnt%2))
                {
                    cout<<"Choose your block(press number between 1-9) out of empty blocks : ";
                    cin>>chs_block;
                    //In case the player selects already filled block he is redirected to select again
                    if(!check_and_fill(chs_block,'X'))
                    {
                        cout<<"Already block is filled. Choose empty one"<<endl;
                        continue;
                    }
                    cnt++;
                }
                //This statement executes for CPUs turn to choose its block
                else
                {
                    /*Since the player is 1st one to choose, CPU gets the board 4 times
                      i.e 1 or 3 or 5 or 7 blocks filled when CPU has to choose its move*/
                    switch(cnt)
                    {
                    //For the 1st turn of the CPU
                    case 1:
                        {
                            /*Since there are only 3 possible ways for the player to choose his 1st move,
                              we maintain a variable 'path' to distinguish */

                            //If player chooses middle block(numbered 5) in his 1st move
                            if(chs_block==5)
                            {
                                path=1;
                                tictactoe[0][2]='O'; //filling a corner as CPU's move
                            }
                            //If player chooses corner block (odd number) in his 1st move
                            else if(chs_block%2)
                            {
                                path=2;
                                tictactoe[1][1]='O'; //filling the middle block as CPU's move
                            }
                            //If player chooses even numbered block in his 1st move
                            else
                            {
                                path=3;
                                if(chs_block==2 || chs_block==4)
                                {
                                    tictactoe[0][0]='O'; //filling the corner block adjacent to blocks 2 and 4 i.e block 1 as CPU's move
                                }
                                else
                                {
                                    tictactoe[2][2]='O'; //filling the corner block adjacent to blocks 6 and 8 i.e block 9 as CPU's move
                                }

                            }
                            break;
                        }
                    //For the 2nd turn of the CPU
                    case 3:
                        {
                            //If player follows path 1
                            if(path==1)
                            {
                                if(chs_block==7)
                                {
                                    //As part of defending strategy CPU chooses block 1
                                    tictactoe[0][0]='O';
                                }
                                else
                                {
                                    w = winning_slot('X');        //Checking winning possibility of player
                                    temp = check_and_fill(w,'O'); //In case of winning possibility of player defending it by choosing the block as CPU's move
                                }
                            }
                            //If player follows path 2
                            else if(path==2)
                            {
                                w = winning_slot('X'); //Checking winning possibility of player
                                //In case of player's possibility of winning
                                if(w)
                                {
                                    temp = check_and_fill(w,'O'); //Defend the player by choosing CPU's move
                                }
                                else
                                {
                                    //As part of defending strategy CPU chooses blocks as per below conditions
                                    if(chs_block==1 || chs_block==3)
                                    {
                                        tictactoe[0][1]='O';
                                    }
                                    else if(chs_block==7 || chs_block==9)
                                    {
                                        tictactoe[2][1]='O';
                                    }
                                    else
                                    {
                                        if(chs_block==2 || chs_block==4)
                                        {
                                            tictactoe[0][0]='O';
                                        }
                                        else
                                        {
                                            tictactoe[2][2]='O';
                                        }
                                    }
                                }
                            }
                            //If player follows path 3
                            else
                            {
                                //In Case middle block is not filled, CPU chooses it
                                if(chs_block!=5)
                                {
                                    tictactoe[1][1]='O';
                                }
                                else
                                {
                                    w = winning_slot('X');         //Checking winning possibility of player
                                    temp = check_and_fill(w,'O');  //In case of winning possibility of player defending it by choosing the block as CPU's move
                                }
                            }
                            break;
                        }
                    //For the 3rd and 4th turn of the CPU logic to win or defend the player remains same
                    default:
                        {
                            //Checking winning possibility of CPU
                            w = winning_slot('O');
                            //In case of CPU's possibility of winning
                            if(w)
                            {
                                temp = check_and_fill(w,'O');           //Filling the winning block
                                Print_Tictactoe();
                                cout<<"CPU won the game"<<endl;//Here ends the game
                                win =1; //'win' variable made true to mark the end of the game
                            }
                            else
                            {
                                //Checking winning possibility of player
                                w = winning_slot('X');
                                //In case of player's possibility of winning
                                if(w)
                                {
                                    temp = check_and_fill(w,'O');     //Defending the player's winning block
                                }
                                //In case no possibility of winning
                                else
                                {
                                    fill_random('O');   //Calling fill_random function to choose CPU's move
                                }
                            }
                            break;
                        }
                    }
                    cnt++; //Count is incremented as CPUs turn is over
                    //In case of CPU's win loop is terminated
                    if(win)
                    {
                        break;
                    }
                }
            }
            Print_Tictactoe();
            //In case loop is terminated without any win(completed 9 moves)
            if(!win)
            {
                cout<<"Match is draw: Neither Player nor CPU win"<<endl;//Game ends and match is declared as draw
            }
        }
        //In case player chooses to go 2nd
        else if(choose_player==2)
        {
            Print_Tictactoe();
            tictactoe[2][0]='X';
            cnt++;
            //As there are 9 moves in total
            while(cnt<9)
            {
                Print_Tictactoe();
                //This condition is satisfied only for the player's turn
                if(cnt%2)
                {
                    cout<<"Choose your block(press number between 1-9) out of empty blocks : ";
                    cin>>chs_block;
                    //In case the player selects already filled block he is redirected to select again
                    if(!check_and_fill(chs_block,'O'))
                    {
                        cout<<"Already block is filled. Choose empty one"<<endl;
                        continue;
                    }
                    cnt++;
                }
                //This condition is satisfied only for the CPU's turn
                else
                {
                    /*Since the player is 1st one to choose, CPU gets the board 5 times(first move is fixed from CPU's side)
                      i.e 2 or 4 or 6 or 8 blocks filled when CPU has to choose its move*/
                    switch(cnt)
                    {
                    //For the 2nd turn of the CPU
                    case 2:
                        {
                            //If player chooses any odd numbered block, we mark the path as 1
                            if(chs_block==5|| chs_block%2)
                            {
                                path =1;
                                /*If the player doesn't choose block 3(CPU's first choice is block 7, diagonally opposite to 3)
                                  CPU's choice is 3 else CPU chooses middle block*/
                                if(!check_and_fill(3,'X'))
                                {
                                    path = 3;  // path is marked as 3
                                    tictactoe[1][1]='X';
                                }
                            }
                            //If player chooses any even numbered block, we mark the path as 2
                            else
                            {
                                path=2;
                                tictactoe[1][1]='X'; //CPU chooses middle block
                            }
                            break;
                        }
                    //For the 3rd turn of the CPU
                    case 4:
                        {
                            //Checking for winning slot of CPU
                            w = winning_slot('X');
                            //If there is any winning slot
                            if(w)
                            {
                                temp = check_and_fill(w,'X');           //Filling the winning block
                                Print_Tictactoe();
                                cout<<"CPU won the game"<<endl;//Here ends the game
                                win =1; //'win' variable made true to mark the end of the game
                            }
                            //Checking for winning slot of player
                            w = winning_slot('O');
                            //If there is any winning slot
                            if(w)
                            {
                                temp = check_and_fill(w,'X'); //Defending the player by choosing CPU's move accordingly
                                break;
                            }
                            //If game is directed in path 1(As per previously taken conventions)
                            if(path==1)
                            {
                                //Defending strategy
                                if(chs_block%2)
                                {
                                    if(!check_and_fill(1,'X'))
                                    {
                                        tictactoe[2][2]='X';
                                    }
                                }
                            }
                            //If game is directed in path 2(As per previously taken conventions)
                            else if(path==2)
                            {
                                //Defending strategy
                                if(tictactoe[1][0]=='O')
                                {
                                    tictactoe[2][2]='X';
                                }
                                else if(tictactoe[2][1]=='O')
                                {
                                        tictactoe[0][0]='X';
                                }
                            }
                            //If game is directed in path 3As per previously taken conventions)
                            else if(path==3)
                            {
                                //Defending Strategy
                                if(chs_block==8)
                                {
                                    tictactoe[0][0]='X';
                                }
                                else if(chs_block==4)
                                {
                                    tictactoe[2][2]='X';
                                }
                            }
                            break;
                        }
                    //For the 4th and 5th turns of the CPU logic remain same
                    default:
                        {
                            //Checking winning possibility of CPU
                            w = winning_slot('X');
                            //In case of CPU's possibility of winning
                            if(w)
                            {
                                temp = check_and_fill(w,'X');           //Filling the winning block
                                Print_Tictactoe();
                                cout<<"CPU won the game"<<endl;//Here ends the game
                                win =1; //'win' variable made true to mark the end of the game
                            }
                            else
                            {
                                //Checking winning possibility of player
                                w = winning_slot('O');
                                //In case of player's possibility of winning
                                if(w)
                                {
                                    temp = check_and_fill(w,'X');     //Defending the player's winning block
                                }
                                //In case no possibility of winning
                                else
                                {
                                    fill_random('X');   //Calling fill_random function to choose CPU's move
                                }
                            }
                            break;
                        }
                    }
                    //Count is incremented as CPUs turn is over
                    cnt++;
                    //In case of CPU's win loop is terminated
                    if(win)
                    {
                        break;
                    }
                }
            }
            //In case loop is terminated without any win(completed 9 moves)
            if(!win)
            {
                Print_Tictactoe();
                cout<<"Match is draw: Neither Player nor CPU win"<<endl; //Game ends and match is declared as draw
            }
        }
        //If player chooses other than 1 or 2
        else
        {
            cout<<"Invalid Input!"<<endl;
            goto restart;
        }
        int t;
        //Asking player whether he wants to continue playing
        cout<<endl<<"IF YOU WANT TO PLAY ONE MORE GAME 'PRESS 1' ELSE 'PRESS 0 : ";
        cin>>t;
        //If player want to quit the game loop breaks
        if(!t)
        {
            break;
        }
        //If player wants to continue then erasing the previous game by making all the blocks as empty
        else
        {
            for(int i=0;i<3;i++)
            {
                for(int j=0;j<3;j++)
                {
                    tictactoe[i][j] = ' ';
                }
            }
        }
    }
}
