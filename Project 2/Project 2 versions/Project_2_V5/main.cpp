/* 
 * File:   main.cpp
 * Author: Samuel Anderson
 * Created on June 4, 2024, 12:16 PM
 * Purpose:  Black jack Game Project 2 V4
 */

//System Libraries

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
using namespace std;

//User Libraries

//Global Constants - Math/Science/Conversions only
const int col=13; 
//Function Prototypes
void welcome(string &name, float &bet, float &total); //starts / welcomes player to the game

int  rndcard(int cards[][col], string suit[], string num[], bool player,bool show);//grabs a random number for reference

bool check(int points,float &total, float bet,bool player);//checks to see if someone goes bust 

void outcome(int points, int dealer, float bet, float &total, string name); //compares scores and outputs the outcome and changes the total score

void msg(string name = "guest"); // greets player 
void msg(int x);//tell player bye 
void monbet(vector<float> &numbers,float bet);//tacks bets made by player and outs into 
int print(vector<float> &numbers, int turns);//prints and organizes vector

void bubble(int arr[], int size);//bubble sort 
void selec(int arr[], int size);//section sort 
int linear(int arr[], int size, int key);//linear search 
void printA(int arr[], int size);//print sort 

//Execution Begins Here
int main(int argc, char** argv) {
    //Set random seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare Variables
    
    string name;//name/nickname the player, decided at start of game
    int row=2,//amount of rows in 2d array 
        points,//total points from cards
        option,// allows the player to pick from 3 options 
        temp,//temp var 
        turns,// counts the amount of turns played during a run 
        at,//@converter 
        taunt,//option for taunting player    
        dealer,//dealers points 
        key;    //key for lucky number
    int luksiz = 5;
    int lucky[luksiz]={28,16,39,32,15};  //lucky numbers    
    //                              card                 suit     
    int cards[row][col]={{1,2,3,4,5,6,7,8,9,10,11,12},{1,2,3,4}}; 
    
    string suit[4]={"Spades","Diamonds","Clubs","Hearts"};//suit names 
    string num[13]={"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"}; //card names
    
    float total, //total amount of money player has
          bet;   //amount user wants to bet
    
    bool player,  //checks player or dealer turn
         run, //checks if code should run
         hit, //checks if player wants to keep on hitting 
         error, //checks for error 
         show;  //checks if it should show the dealers card drawn 
    
    vector<float> numbers(0);//vector to put amount bet each game 
    
    char end;//sign  
    
    
    
    //Initialize Variables
    
    key = 32;
    end=36;//outputs "$"
    at=64;//@converter
    total=100;
    bet=0;
    run=true; 
    error = false; 
    taunt=0; 
    msg(); 
    welcome(name, bet, total);
    // Open a file to log results
    ofstream outFile;
    outFile.open("game_results.txt", ios::app);  // Opens file
    
    //The Process -> Map Inputs to Outputs
    do {
        //init points
        turns++; //add a turn every cycle 
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
        //if user hits the wrong option
        while(option>3){
            cout<<"please input a correct number\n1 = Hit | 2 = Stand | 3 = Double Down\n";
            cin>>option;
        }
        //user decides to hit 
        if (option == 1){
            hit=true; 
            while(hit==true){
                //draw the card for player 
                player=true; 
                points+=rndcard(cards,suit,num,player,show);
                //tell them their points
                cout<<"Your point total is now = "<<points<<endl;
                //check if player goes over 
                hit=check(points, total, bet, player); 
                //dealers turn if player under 21 & if dealer under 22
                if(hit==true){
                    cout<<"Dealer will now draw a card"<<endl;
                    //draw card for dealer
                    player=false; 
                    dealer+=rndcard(cards,suit,num,player,show);
                    //check if dealer goes bust
                    hit=check(dealer, total, bet, player);
                }  
                //checks if both players are under 21 and gives player an option 
                if(hit==true){
                    cout<<"The turn has not ended, nobody has gone bust"<<endl;
                    cout<<"\nPlease pick pick an option"<<endl;
                    cout<<"---------------------------------------------------"<<endl;
                    cout<<"1 = Hit | 2 = Stand"<<endl;
                    cout<<"---------------------------------------------------"<<endl;
                    cin>>temp; 
                    //if player picks an option that's not available 
                    while(temp>2){
                        cout<<"Please pick a valid option"<<endl;
                        cout<<"---------------------------------------------------"<<endl;
                        cout<<"1 = Hit | 2 = Stand"<<endl;
                        cout<<"---------------------------------------------------"<<endl;
                        cin>>temp; 
                    } 
                    //if user stands 
                    if(temp==2){
                        cout<<"You have chosen to Stand\nmatch will now continue"<<endl;
                        hit=false;
                    }else if(temp==1){
                        //if user hits start up the loop again 
                        cout<<"You have chosen to Hit"<<endl;
                    }else{
                        // Exit the loop if either the player or dealer goes bust
                        cout<<"ERROR"<<endl;
                        hit=false;
                    }
                }
            }
            //player hit is done checking if dealer has a score higher than 17
            if(points <= 21 && dealer <= 21){
                while(dealer<17){
                    cout<<"Dealer will now draw a card"<<endl;
                    //draw card for dealer
                    player=false; 
                    dealer+=rndcard(cards,suit,num,player,show);
                    //check if dealer goes bust
                    check(dealer, total, bet, player);
                }
            }    
            //After the player stand and the dealer is at 17 or over 
            //Check both scores and see who wins
            if(points <= 21 && dealer <= 21){
                outcome(points,dealer,bet,total,name);
            }
            
        }
        //user stands
        if (option == 2){
            //check if dealer is under 17 then draw
            while(dealer<17){
                cout<<"Dealer will now draw a card"<<endl;
                //draw card for dealer
                player=false; 
                dealer+=rndcard(cards,suit,num,player,show);
                //check if dealer goes bust
                player = false;
                check(dealer, total, bet, player);
            }
            //After the player stand and the dealer is at 17 or over 
            //Check both scores and see who wins
            if(points <= 21 && dealer <= 21){
                outcome(points,dealer,bet,total,name);
            }
        }
        //user doubles down
        if (option == 3){
            //double the bet by 2
            bet*=2;
            //draw a card for the player 
            //draw the card for player 
            player=true; 
            points+=rndcard(cards,suit,num,player,show);
            //tell them their points
            cout<<"Your point total is now = "<<points<<endl;
            //check if player goes over 
            hit=check(points, total, bet, player); 
            //player cant draw anymore 
            //draw cards for dealer till 17+
            while(dealer<17){
                cout<<"Dealer will now draw a card"<<endl;
                //draw card for dealer
                player=false; 
                dealer+=rndcard(cards,suit,num,player,show);
                //check if dealer goes bust
                player = false; 
                check(dealer, total, bet, player);
            }
            //After the player stand and the dealer is at 17 or over 
            //Check both scores and see who wins
            if(points <= 21 && dealer <= 21){
                outcome(points,dealer,bet,total,name);
            }
        }
        //final parr
        //Tell player their new total
        cout<<"\nYour new total is now = $"<<total<<endl;
        //check if player is negative
        if (total < 1){
            cout<<"You are now in debt/broke and can not play anymore\n";
            run=false;
        }else {
            //checks to see if player wants to go again
            cout<<"Do you want to play again?"<<endl;
            cout<<"1 = play again | 2 = Exit Game"<<endl;
            cin>>temp;
            //if user inputs an invalid option 
            while(temp>2){
                cout<<"INVALID INPUT PLEASE TRY AGAIN"<<endl; 
                cout<<"1 = play again | 2 = Exit Game"<<endl;
                cin>>temp;
            }
            //if user exits game stop running game 
            if(temp == 2){
                run=false; 
            }
            //if user wants to continue with game 
            if (temp == 1){
                cout<<"Please place a new bet"<<endl;
                cout<<"$";
                cin>>bet;
                while(bet>total){
                    cout<<"$"<<bet<<" is greater than your total amount of $"<<total<<"\nPlease input a number lower\n"; 
                    cin>>bet;
                }
                taunt = (bet > 75) ? 2 : 1;
                switch(taunt) {
                    case 1:
                      cout<<"Being cautious?"<<endl;// code block
                      break;
                    case 2:
                      cout<<"That's a lot of cash to be flaunting around!"<<endl;// code block
                      break;
                    default:
                        cout<<"error"; 
                }
                cout<<"Your new bet is = $"<<bet<<"\nGood Luck :)"<<endl;
                cout<<"---------------------------------------------------"<<endl;
                cout<<"New Round Begins"<<endl;
                cout<<"---------------------------------------------------"<<endl;
            }
        }
        //stops running if error is detected 
        if (error == true ){
            cout<<"ERROR PROGRAM IS BEING TERMINATED"<<endl; 
            exit(EXIT_FAILURE);
        }
        //adds the amount bet by player into the vector
        monbet(numbers,bet); 
        //Logs bets made
        outFile << "Bet made: " <<bet<< endl;
    }        
    while(run==true); 
    //Display Inputs/Outputs
    msg(bet); 
    cout<<(char)at<<name<<endl;
    cout<<fixed<<setprecision(2)<<showpoint;
    cout<<"Your final total is now = "<<end<<total<<endl;
    //Stats 
    cout<<"Rounded Total : $"<<round(total)<<endl;
    print(numbers,turns);
    //bubble sort 
    bubble(lucky, luksiz);
    cout << "Good fortune  : ";
    printA(lucky, luksiz);
    // Selection Sort
    selec(lucky, luksiz);
    cout << "Great fortune : ";
    printA(lucky, luksiz);
    int res = linear(lucky, luksiz, key);
    if (res != -1) {
        cout<<"Amazing fortune : "<<key<<" at "<<res<<"\n";
    } else {
        cout<<"Amazing fortune : "<<key<<" not found\n";
    }
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
    //cout << "rand1: " << rand1 << endl;
    //cout << "rand2: " << rand2 << endl;
    
    // Init 
    int pass1 = rand2; 
    int pass2 = rand1; 
    int points = 0; 
    bool ace = true; 
    // Static variable to count the number of card draws
    static int drawn = 0; // Initialized only once, it tells players how many cards they have drawn 
    drawn++; // Incremented every time the function is called
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
        cout<<"You are given a "<<num[pass1]<<" of "<<suit[pass2]<<endl;
        cout<<"Total cards drawn during execution : "<<drawn<<endl;
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
            cout<<"The dealer places a "<<num[pass1]<<" of "<<suit[pass2]<<" face up."<<endl;
        }
    }

    return points;
}

bool check(int points,float &total, float bet,bool player){
    if (player==true) {
        if (points > 21) {
            // Output player bust information
            cout<<"You have gone bust and lost the game\n";
            cout<<"$"<<bet<<" has been subtracted from your total"<<endl;
            // Subtract bet from total
            total -= bet;
            // Return false to indicate the game should stop
            return false;
        }
    }else {
        if (points > 21) {
            // Output dealer bust information
            cout<<"The dealer has gone BUST\nCONGRATS!!! You have won the match"<<endl;
            cout<<"$"<<bet<<" has been rewarded to you"<<endl;
            // Add bet to total
            total += bet;
            // Return false to indicate the game should stop
            return false;
        }
    }
    // If no one has gone bust, continue the game
    return true;
}

void outcome(int points,int dealer ,float bet ,float &total , string name){
    if (dealer == points){
        //if dealer points are == to player points 
        cout<<"A push has occurred\nNothing has been lost or gained"<<endl;
    }else if (dealer > points){
        //if dealer has more points than player 
        cout<<"The dealer has won with a total of "<<dealer<<" points.\n"; 
        cout<<"You have lost $"<<bet<<endl;
        total = total-bet;
    }else if(dealer < points){
        //if player has more points than dealer
        cout<<"You have more points than the dealer and have won the match"<<endl;
        cout<<"---------------------------------------------------"<<endl;
        cout<<name<<" point total = "<<points<<" > "<<dealer<<" = dealer point total"<<endl;
        cout<<"---------------------------------------------------"<<endl;
        cout<<"Total of $"<<bet<<" has been added to total"; 
        total = total+bet;
    }else{
        //if an error occurs
        cout<<"an error has occurred"<<endl;
    }
}

void msg(string name){
    cout<<"Hello "<<name<<endl;
};
void msg(int bet){
    cout<<"Your final bet was : "<<bet<<endl;
}

void monbet(vector<float> &numbers,float bet){
    numbers.push_back(bet);
}
int print(vector<float> &numbers, int turns){
    //print it
    cout<<"Bets made during the game"<<endl; 
    for(int number:numbers){
        cout<<"$"<<number<<" "; 
    }
    cout<<endl;
  
}

void bubble(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void selec(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIdx = i;
        for (int j = i+1; j < size; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

int linear(int arr[], int size, int key) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            return i; // return the index of the key
        }
    }
    return -1; // key not found
}

void printA(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i < size - 1) {
            cout << ",";
        }
    }
    cout << endl;
}

