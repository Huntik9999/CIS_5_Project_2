/* 
 * File:   main.cpp
 * Author: Samuel Anderson
 * Created on May 29, 2024, 12:16 PM
 * Purpose:  Black jack Game Project 2 V2
 */

//System Libraries
#include <iostream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

//User Libraries

//Global Constants - Math/Science/Conversions only
const int col=13; 
//Function Prototypes
void welcome(string &name, float &bet, float &total); //starts / welcomes player to the game
int  rndcard(int cards[][col], string suit[], string num[]);//grabs a random number for reference

//bool agin(); //ask the player if they want another turn
//Execution Begins Here
int main(int argc, char** argv) {
    //Set random seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare Variables
    
    string name;//name/nickname the player, decided at start of game
    int row=2,//amount of rows in 2d array 
        points;//total points from cards    
    //                              card                 suit     
    int cards[row][col]={{1,2,3,4,5,6,7,8,9,10,11,12},{1,2,3,4}}; 
    
    string suit[4]={"Spades","Diamonds","Clubs","Hearts"};//suit names 
    string num[13]={"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"}; //card names
    
    float total, //total amount of money player has
          bet;   //amount user wants to bet
    
    bool run; 
    
    
    
    //Initialize Variables
    total=100;
    bet=0; 
    points=0; 
    run=true; 
    welcome(name, bet, total);
    //The Process -> Map Inputs to Outputs
    do {
        cout<<"Cards will now be handed out"<<endl;
        //pull a first card
        points+=rndcard(cards,suit,num); 
        //pull a second card
        points+=rndcard(cards,suit,num); 
        //tell player their points 
        cout<<"Your point total is now = "<<points<<endl;
        
        run = false; 
    }
    while(run==true); 
    //Display Inputs/Outputs

    //Exit the Program
    return 0;
}
void welcome(string &name, float &bet, float &total){
     cout<<"Welcome to Blackjack\nFor the purpose of this simulation you will be given $100 to start the game\n";
    cout<<"Please insert name/nickname to start\n";
    //prompts user to input name/nickname
    cin>>name;
    cout<<"Hello "<<name<<". How much would you like to bet for your first game?\nPlease do not exceed the total amount\n$";
    cin>>bet;
    //if bet is greater than total amount of money held by player ask for input again
    while(bet > total){
        cout<<"Bet exceeds total number please enter a number lower than $"<<total<<"\n$";
        cin>>bet; 
    }
    cout<<"\nYou have decided to bet $"<<bet<<"\nLets get started with the game.\n";  
    cout<<"---------------------------------------------------"<<endl;
    cout<<"First Round Begins"<<endl;
    cout<<"---------------------------------------------------"<<endl;
}

int  rndcard(int cards[][col],string suit[], string num[]){
    int rand1=rand()%4+1;; //random number for suit 
    int rand2=rand()%13+1; //random number for car 
    int pass1 = 0; 
    int pass2 = 0; 
    int points = 0; 
    bool ace=true; 
    //pass  random values to 2-d array
    pass1=cards[0][rand2];
    pass2=cards[1][rand1];
    //calculate points
    if(rand2==1){
         while(ace == true){
            cout<<"An ace has been added to your hand.\nPlease select how many points you want your ace to be worth\n";
            cout<<"1 = 1 points | 10 = 10 points\n";
            cin>>points;
            if(points==1||points==10){
                cout<<"Points have been added to total\n";
                ace=false; 
            }else{
                cout<<"Please input a correct number\n";
            }
        }
    }else if (rand2 < 10){
        points=10;
    }else{
        points=rand2; 
    }
    //output the card gotten 
    cout<<"You are given a "<<num[pass2]<<" of "<<suit[pass1]<<endl;
    return points; 
    
}