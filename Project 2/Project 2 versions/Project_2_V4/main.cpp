/* 
 * File:   main.cpp
 * Author: Samuel Anderson
 * Created on June 5, 2024, 12:16 PM
 * Purpose:  Black jack Game Project 2 V4
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
int  rndcard(int cards[][col], string suit[], string num[], bool player,bool show);//grabs a random number for reference


//bool agin(); //ask the player if they want another turn
//Execution Begins Here
int main(int argc, char** argv) {
    //Set random seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare Variables
    
    string name;//name/nickname the player, decided at start of game
    int row=2,//amount of rows in 2d array 
        points,//total points from cards
        option, 
        dealer;//dealers points 
    //                              card                 suit     
    int cards[row][col]={{1,2,3,4,5,6,7,8,9,10,11,12},{1,2,3,4}}; 
    
    string suit[4]={"Spades","Diamonds","Clubs","Hearts"};//suit names 
    string num[13]={"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"}; //card names
    
    float total, //total amount of money player has
          bet;   //amount user wants to bet
    
    bool player,  
         run, 
         show; 
    
    
    
    //Initialize Variables
    total=100;
    bet=0;
    run=true; 
    welcome(name, bet, total);
    //The Process -> Map Inputs to Outputs
    do {
        //init points
        points=0;
        dealer=0;
        cout<<"Cards will now be handed out"<<endl;
        //player turn 
        player = true; 
        //pull a first card
        points+=rndcard(cards,suit,num,player,show);
        //tell player their points 
        cout<<"Your point total is now = "<<points<<endl;
        //pull a second card
        points+=rndcard(cards,suit,num,player,show); 
        //tell player their points 
        cout<<"Your point total is now = "<<points<<endl;
        //dealer draws a card
        player=false; 
        show=false; 
        //draw the dealers card
        dealer+=rndcard(cards,suit,num,player,show); 
        //dealer draws a second card face up
        show=true; 
        dealer+=rndcard(cards,suit,num,player,show); 
        //Ask the user for a decision
        cout<<"Please press a corresponding number to complete an action\n";
        cout<<"---------------------------------------------------"<<endl;
        cout<<"1 = Hit | 2 = Stand | 3 = Double Down\n";
        cout<<"---------------------------------------------------"<<endl;
        cin>>option;
        while(option>3){
            cout<<"please input a correct number\n1 = Hit | 2 = Stand | 3 = Double Down\n";
            cin>>option;
        }
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

int rndcard(int cards[][col], string suit[], string num[], bool player, bool show) {
    int rand1 = rand() % 4; // random number for suit 
    int rand2 = rand() % 13; // random number for card 

    // Debug check
    cout << "rand1: " << rand1 << endl;
    cout << "rand2: " << rand2 << endl;
    
    // Init 
    int pass1 = rand2; 
    int pass2 = rand1; 
    int points = 0; 
    bool ace = true; 

    // Calculate points for player 
    if(player == true) {
        if(pass1 == 0) { // Ace
            while(ace == true) {
                cout << "An Ace has been added to your hand.\nPlease select how many points you want your Ace to be worth\n";
                cout << "1 = 1 point | 11 = 11 points\n";
                cin >> points;
                if(points == 1 || points == 11) {
                    cout << "Points have been added to total\n";
                    ace = false; 
                } else {
                    cout << "Please input a correct number\n";
                }
            }
        } else if (pass1 >= 10) { // Face cards
            points = 10;
        } else {
            points = pass1 + 1; // Number cards
        }
        // Output the card gotten 
        cout << "You are given a " << num[pass1] << " of " << suit[pass2] << endl;
    }
    // Calculate points for dealer
    if(player == false) {
        if(pass1 == 0) { // Ace
            while(ace == true){
            if(points>8){
                points=10;
                ace=false;
            }else{
                points=1;
                ace=false;
            }
        }
        } else if (pass1 >= 10) { // Face cards
            points = 10;
        } else {
            points = pass1 + 1; // Number cards
        }
        // Output the card gotten 
        if(show==true){
            cout << "The dealer place a " << num[pass1] << " of " << suit[pass2] <<" face up."<< endl;
        }
    }

    return points;
}

