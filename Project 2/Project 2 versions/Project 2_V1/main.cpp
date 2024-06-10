/* 
 * File:   main.cpp
 * Author: Samuel Anderson
 * Created on May 28, 2024, 12:16 PM
 * Purpose:  Black jack Game Project 2 V1 
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

//Function Prototypes
void welcome(string &name); 
int
bool
//Execution Begins Here
int main(int argc, char** argv) {
    //Set random seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare Variables
    string name,//name/nickname the player, decided at start of game
           suit,//suit for card
           card;//card number 
    float total, //total amount of money player has
          bet;   //amount user wants to bet
    
    char slink;  //random number seed link
    int  clink,  //random number seed link
         cpoints,//points for current card
         points,//total points from cards 
         dealer,//dealers points 
         temp,//temp
         option,//hit, stand, or duoble down
         at,//@converter
         turns;//turn counter
    bool run,//checks if game is going on
         ace,//checks if player pulls ace 
         hit; //boolean to check if game should keep on going
    //Initialize Variables
    welcome(name);
    //The Process -> Map Inputs to Outputs
    
    //Display Inputs/Outputs

    //Exit the Program
    return 0;
}
void welcome(string &name){
     cout<<"Welcome to Blackjack\nFor the purpose of this simulation you will be given $100 to start the game\n";
    cout<<"Please insert name/nickname to start\n";
    //prompts user to input name/nickname
    cin>>name;
    cout<<"Hello "<<name<<". How much would you like to bet for your first game?\nPlease do not exceed the total amount\n$";
}