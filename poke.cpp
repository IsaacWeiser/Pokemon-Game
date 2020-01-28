/* Name: Isaac Weiser
Date: 7/30/18
Section: 0002
Assignment: homework 7
Due Date: 7/30/18
About this project: this project will allow you to catch pokemon, view your catching statitics, view ball inventory and
 sort the pokemon by their type.
Assumptions: this program will take your input and will force you enter the correct filename, and allow you to choose
 your name and will ask for a menu selection in which you can hunt for pokemon, all while it collects the stats in the
 background.

All work below was performed by Isaac Weiser */


#include <iostream>
#include <fstream>
#include <iomanip>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstring>


using namespace std;

struct pokemon {
    int number;
    string name;
    string type;
    double catchpct;
    int seen;
    int caught;
};


void printmenu();
void hunt (pokemon mon[], int &random, int &pball, int &gball, int &uball, int ballchoice, int &capture, int &seen, int &caught, char &selection);
void stats (int size, pokemon mon[], int caught, int seen, double pct);
void inventory (int pball, int gball, int uball);
void sort (pokemon mon[], int size);

int main ()
{


//declare variables
int length,size, ballchoice, capture,random;
char selection;
int pball=10, gball =10, uball =10, seen = 0, caught =0;
double pct=0.0;
ifstream info;
    char trainer [41];
    char filename [9];

//set up randmom number generator
srand((unsigned int) time(0));

//ask for file name and read in answer
cout << "please enter a file name: ";
cin >> filename;

//open file
info.open(filename);


// requires you to put in valid filename and opens the file
    while (!info) {

        cout << "please enter a valid file name> ";
        cin >> filename;
        info.open(filename);
    }




// stores the size of the list
info >> size;


//declare pointer of type poke
    pokemon *mon = new pokemon [size];

    // assign values to array
            for(int i =0; i<size; i++) {
                info >> mon[i].number;
                info >> mon[i].name;
                info >>mon[i].type;
                info >>mon[i].catchpct;
                mon[i].seen = 0;
                mon[i].caught = 0;
            }

//closes file
info.close();



cin.ignore();

// ask trainer for name
cout << "\nWhat's your name, trainer? > ";
cin.getline(trainer,40, '\n');
length = (int) strlen(trainer);


//welcome trainer and explain game
cout << "\nWelcome, ";
for (int i = 0;i<length;i++)
    cout << trainer[i];
cout<< ", to the COP3014 Safari Zone!\n"
       "You'll have 30 chances to catch Pokemon, make them count!\n"
       "The game will end once you run out of balls or if you choose to quit early\n";


    do {
// assigns random numbers to to the variables in a loop
        random = rand() % size;
        capture = rand()%100+1;

        //print out menu
        printmenu();

        //choose menu option
        cin>> selection;
        cout << "\n";

        //this determines what to do with your menu selection
        switch (selection)
        {
            case '1':
                hunt ( mon,  random, pball, gball,  uball,  ballchoice, capture,  seen, caught, selection);
                break;
            case '2':
                stats ( size, mon, caught, seen, pct);
                break;
            case '3':
                inventory (pball, gball, uball);
                break;
            case '4':
                sort (mon,size);
                break;
            case 'q':
            case 'Q':
                // prints out final stats and cleans up dynamically allocated space
                cout<<"Final Stats:\n ";
                stats ( size, mon, caught, seen, pct);
                delete [] mon;
                mon = 0;
                exit (0);
            default:
                //makes ypu re enter selection when selection is invalid
                cout<<"invalid entry\n";

        }
    }while (selection != 'q' || selection != 'Q');



    return 0;
}



//this function prints the menu to the screen
void printmenu()
{
    cout << "\n1 - Hunt for a Pokemon!\n"
            "2 - Pokedex Statistics.\n"
            "3 - Print Inventory.\n"
            "4 - Sort Pokedex by Type \n"
            "Q - Quit\n";
    cout << "Selection > ";
}




// allows you to hunt for pokemon
void hunt (pokemon mon[], int &random, int &pball, int &gball, int &uball, int ballchoice, int &capture, int &seen, int &caught, char &selection) {

    // lets you know what pokemon you are to catch
    cout << "A wild " << mon[random].name << " has appeared!\n";
    seen++;
    mon[random].seen++;
    //view available balls and choose one to throw
    cout << "\nChoose a ball to throw:\n"
            "1 - Poke Ball\t(You have: " << pball << ")\n"
            "2 - Great Ball\t(You have: " << gball << ")\n"
            "3 - Ultra Ball\t(You have: "
         << uball << ")\n"
                     "Selection > ";
    cin >> ballchoice;
    cout<<endl;
    // makes sure you enter a valid ball
    while (ballchoice < 1 && ballchoice > 3) {
        cout << "please re enter your ball choice: ";
        cin >> ballchoice;
    }
    // determines wheteher you caught pokemon using pokeball
    if (ballchoice == 1) {
        if (pball > 0) {

            if (mon[random].catchpct <= capture) {
                cout << mon[random].name << " has ran away. :-(\n";
            } else {
                cout << "Congratulations! you caught " << mon[random].name << "!\n";
                mon[random].caught++;
                caught++;
            }
        } else
            {
                //requires you to choose a new ball
                do
                {
                    cout << "you have none of them!" << endl;
                    cout << "Selection > ";
                    cin >> ballchoice;
                    cout << endl;
                    if (uball > 0 && ballchoice == 3) {
                    } else if (gball > 0 && ballchoice == 2) {}
                }
                while (pball == 0 && ballchoice == 1);

//determines what happens when you are out of pokeballs and choose greatball
                if (ballchoice == 2 && gball >0) {

                    if (mon[random].catchpct + 20 <= capture) {
                        cout << mon[random].name << " has ran away. :-(\n";
                    } else {
                        cout << "Congratulations! you caught " << mon[random].name << "!\n";
                        mon[random].caught++;
                        caught++;


                    }
                }
                    //determines what happens when you are out of pokeballs and choose ultraball
                else if (ballchoice ==3 && uball>0)
                {
                    if (mon[random].catchpct + 40 <= capture) {
                        cout << mon[random].name << " has ran away. :-(\n";
                    } else {
                        cout << "Congratulations! you caught " << mon[random].name << "!\n";
                        mon[random].caught++;
                        caught++;
                    }

                }
                    // determines what to do when you are out of  pokeballs and another ball and need to choose a ball you have
                else if ((ballchoice ==2 && gball < 1) || (ballchoice ==3 && uball<1))
                {
                    do
                    {
                        cout << "you have none of them!" << endl;
                        cout << "Selection > ";
                        cin >> ballchoice;
                    }
                    while ((ballchoice ==2 && gball < 1) || (ballchoice ==3 && uball<1));
                }
                    // determines what to do when you are out of all balls
                else
                {
                    cout << " You are out of balls and the game is now over, thank you for playing\n";
                    selection = 'q';
                }
            }
        pball--;
        // stops pokeball count from being a negative number
        if (pball < 1)
            pball=0;
    }




    //determines whether you caught the pokemon using a great ball
    else if (ballchoice == 2) {
        if (gball > 0) {
            if (mon[random].catchpct + 20 <= capture) {
                cout << mon[random].name << " has ran away. :-(\n";
            } else {
                cout << "Congratulations! you caught " << mon[random].name << "!\n";
                mon[random].caught++;
                caught++;
            }
        } else if (gball < 1)
            {
                do
                {
                    //allows you to change ball selection when you run out of greatballs
                    cout << "you have none of them!" << endl;
                    cout << "Selection > ";
                    cin >> ballchoice;
                    if (pball > 0 && ballchoice == 1) {
                    } else if (uball > 0 && ballchoice == 3) {}
                }
                while (gball == 0 && ballchoice == 2);

//determines what happens when you are out of greatballs and choose ultraball
                if (ballchoice == 3) {

                    if (mon[random].catchpct + 40 <= capture) {
                        cout << mon[random].name << " has ran away. :-(\n";
                    } else {
                        cout << "Congratulations! you caught " << mon[random].name << "!\n";
                        mon[random].caught++;
                        caught++;
                    }
                }
                    //determines what happens when you are out of greatballs and choose pokeball
                else if (ballchoice ==1)
                {
                    if (mon[random].catchpct <= capture) {
                        cout << mon[random].name << " has ran away. :-(\n";
                    } else {
                        cout << "Congratulations! you caught " << mon[random].name << "!\n";
                        mon[random].caught++;
                        caught++;
                    }
                }
                    // determines what to do when you are out of  greatballs and another ball and need to choose a ball you have
                else if ((ballchoice ==1 && pball < 1) || (ballchoice ==3 && uball<1))
                {
                    do
                    {
                        cout << "you have none of them!" << endl;
                        cout << "Selection > ";
                        cin >> ballchoice;
                        if (pball > 0 && ballchoice == 1) {
                        } else if (uball > 0 && ballchoice == 3) {}
                    }
                    while ((ballchoice ==1 && pball < 1) || (ballchoice ==3 && uball<1));
                }
                // determines what to do when you are out of all balls
                else
                {
                    cout << " You are out of balls and the game is now over, thank you for playing\n";
                    selection = 'q';
                }
            }
        gball--;
        //stops greatball count from being  negative number
        if (gball<1)
            gball=0;
    }





    else if (ballchoice == 3)
        {
            //determines whether you caught pokemon with ultraball
        if (uball > 0) {
            if (mon[random].catchpct + 40 <= capture) {
                cout << mon[random].name << " has ran away. :-(\n";
                uball--;
            } else {
                cout << "Congratulations! you caught " << mon[random].name << "!\n";
                mon[random].caught++;
                caught++;
                uball--;
            }
        } else
            {
                // makes you choose new ball when you run out of ultraballs
            do
                {
                cout << "you have none of them!" << endl;
                cout << "Selection > ";
                cin >> ballchoice;
                if (pball > 0 && ballchoice == 1) {
                } else if (gball > 0 && ballchoice == 2) {}
            }
            while (uball == 0 && ballchoice == 3);

//determines what happens when you are out of ultraballs and choose greatball
            if (ballchoice == 2 && gball > 0) {

                if (mon[random].catchpct + 20 <= capture) {
                    cout << mon[random].name << " has ran away. :-(\n";
                } else {
                    cout << "Congratulations! you caught " << mon[random].name << "!\n";
                    mon[random].caught++;
                    caught++;


                }
            }
                //determines what happens when you are out of ultraballs and choose pokeball
            else if (ballchoice ==1 && pball > 0)
            {
                if (mon[random].catchpct <= capture) {
                    cout << mon[random].name << " has ran away. :-(\n";
                } else {
                    cout << "Congratulations! you caught " << mon[random].name << "!\n";
                    mon[random].caught++;
                    caught++;
                }

            }
            // determines what to do when you are out of  ultraballs and another ball and need to choose a ball you have
            else if ((ballchoice ==1 && pball < 1) || (ballchoice ==2 && gball<1))
            {
                do
                {
                    cout << "you have none of them!" << endl;
                    cout << "Selection > ";
                    cin >> ballchoice;
                    if (pball > 0 && ballchoice == 1) {
                    } else if (gball > 0 && ballchoice == 2) {}
                }
                while ((ballchoice ==1 && pball < 1) || (ballchoice ==2 && gball<1));
            }
            else
            {
                cout << " You are out of balls and the game is now over, thank you for playing\n";
                selection = 'q';
            }
        }
       // stops ultra ball count from being a negative number
            if (uball < 1)
                uball = 0;

    }






    // determines what happens if you enter an in valid ball
    else
    {
        do {
            cout << "invalid ball please choose again\n";
            cout << "Selection > ";
            cin >> ballchoice;
           } while (ballchoice > 3 || ballchoice < 1);


        if (ballchoice ==1 && pball>0)
        {

            if (mon[random].catchpct <= capture) {
                cout << mon[random].name << " has ran away. :-(\n";
            } else {
                cout << "Congratulations! you caught " << mon[random].name << "!\n";
                mon[random].caught++;
                caught++;
            }
        }
        else if (ballchoice == 2 && gball > 0)
        {
            if (mon[random].catchpct + 20 <= capture) {
                cout << mon[random].name << " has ran away. :-(\n";
            } else {
                cout << "Congratulations! you caught " << mon[random].name << "!\n";
                mon[random].caught++;
                caught++;
            }
        }
        else if (ballchoice ==3 && uball>0)
        {
            if (mon[random].catchpct + 40 <= capture) {
                cout << mon[random].name << " has ran away. :-(\n";
            } else {
                cout << "Congratulations! you caught " << mon[random].name << "!\n";
                mon[random].caught++;
                caught++;
            }
        } else {
            cout << " You are out of balls and the game is now over, thank you for playing\n";
            selection = 'q';
        }


    }
}

// function shows your pokemon catching statistics
        void stats(int size, pokemon mon[], int caught, int seen, double pct) {
    if (seen > 30)
        seen = 30;
    cout << "\n";
            for (int i = 0; i < size; i++) {

                cout.setf(ios::right);
                cout << "NO " << mon[i].number;
                cout.width(15);
                cout << mon[i].name;
                cout.width(15);
                cout << "seen: " << mon[i].seen;
                cout.width(15);
                cout << " caught: " << mon[i].caught << endl;
            }
            cout << "Total overall pokemon caught: " << caught << " Total pokemon seen: " << seen << endl;
            pct = 0.00;
            // calculates pokemon catch percentage
            double temp1 =(double)seen;
            double temp2 = (double)caught;
            pct = (temp2 / temp1) * 100.0;
            cout << "Overall Catch Rate: ";
            cout << fixed << showpoint << setprecision(2) << pct;
            cout << "%" << endl;
        }

// this function shows pokeball inventory
        void inventory(int pball, int gball, int uball) {
            cout << "\nYou have: \n"
                 << pball << " PokeBalls\n"
                 << gball << " Great Balls\n"
                 << uball << " Ultra Balls" << endl;
        }

// this function sorts the pokemon by their type and displays them to the screen
        void sort(pokemon mon[], int size) {

            cout << "\nGrass: Baulbasaur";
            for (int i = 1; i < size; i++) {
                if (mon[i].type == "grass" || mon[i].type == "GRASS" || mon[i].type == "Grass")
                    cout << ", " << mon[i].name;
            }
            cout << endl;
            cout << "Fire: Charmander";
            for (int i = 4; i < size; i++) {
                if (mon[i].type == "fire" || mon[i].type == "FIRE" || mon[i].type == "Fire")
                    cout << ", " << mon[i].name;
            }
            cout << endl;
            cout << "Water: Squirtle";
            for (int i = 7; i < size; i++) {
                if (mon[i].type == "water" || mon[i].type == "Water" || mon[i].type == "Water")
                    cout << ", " << mon[i].name;
            }
            cout << endl;
            cout << "Bug: Caterpie";
            for (int i = 10; i < size; i++) {
                if (mon[i].type == "bug" || mon[i].type == "BUG" || mon[i].type == "Bug")
                    cout << ", " << mon[i].name;
            }
            cout << endl;
            cout << "Normal: Pidgey";
            for (int i = 16; i < size; i++) {
                if (mon[i].type == "normal" || mon[i].type == "NORMAL" || mon[i].type == "Normal")
                    cout << ", " << mon[i].name;
            }
            cout << endl;
            cout << "Poison: Ekans";
            for (int i = 23; i < size; i++) {
                if (mon[i].type == "poison" || mon[i].type == "POISON" || mon[i].type == "Poison")
                    cout << ", " << mon[i].name;
            }
            cout << endl;
            cout << "Electric: Pikachu";
            for (int i = 25; i < size; i++) {
                if (mon[i].type == "electric" || mon[i].type == "ELECTRIC" || mon[i].type == "Electric")
                    cout << ", " << mon[i].name;
            }
            cout << endl;
            cout << "Ground: Sandshrew";
            for (int i = 27; i < size; i++) {
                if (mon[i].type == "ground" || mon[i].type == "GROUND" || mon[i].type == "Ground")
                    cout << ", " << mon[i].name;
            }
            cout << endl;
            cout << "Fairy: Clefairy";
            for (int i = 35; i < size; i++) {
                if (mon[i].type == "fairy" || mon[i].type == "FAIRY" || mon[i].type == "Fairy")
                    cout << ", " << mon[i].name;
            }
            cout << endl;
            cout << "Fighting: Mankey";
            for (int i = 56; i < size; i++) {
                if (mon[i].type == "fighting" || mon[i].type == "Fighting" || mon[i].type == "FIGHTING")
                    cout << ", " << mon[i].name;
            }
            cout << endl;
            cout << "Psychic: Abra";
            for (int i = 63; i < size; i++) {
                if (mon[i].type == "psychic" || mon[i].type == "PSYCHIC" || mon[i].type == "Psychic")
                    cout << ", " << mon[i].name;
            }
            cout << endl;
            cout << "Rock: Geodude";
            for (int i = 74; i < size; i++) {
                if (mon[i].type == "rock" || mon[i].type == "ROCK" || mon[i].type == "Rock")
                    cout << ", " << mon[i].name;
            }
            cout << endl;
            cout << "Ghost: Gastly";
            for (int i = 92; i < size; i++) {
                if (mon[i].type == "ghost" || mon[i].type == "GHOST" || mon[i].type == "Ghost")
                    cout << ", " << mon[i].name;
            }
            cout << endl;
            cout << "Ice: Pikachu";
            for (int i = 124; i < size; i++) {
                if (mon[i].type == "ice" || mon[i].type == "ICE" || mon[i].type == "Ice")
                    cout << ", " << mon[i].name;
            }
            cout << endl;
            cout << "Dragon: Dratini";
            for (int i = 147; i < size; i++) {
                if (mon[i].type == "dragon" || mon[i].type == "DRAGON" || mon[i].type == "Dragon")
                    cout << ", " << mon[i].name;
            }
cout << endl;
        }
