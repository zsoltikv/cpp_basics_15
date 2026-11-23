#include <iostream> // include the input output stream library for cin and cout
#include <iomanip>  // include iomanip library for formatted output like setw
#include <fstream>  // include fstream library for file input and output
#include <string>   // include string library for storing competitor names
#include <ctime>    // include ctime library for accessing the current system time
#include <cstdlib>  // include cstdlib library for random number generation
#include <vector>   // include vector library for dynamic arrays

using namespace std; // use the standard namespace to avoid writing std constantly

// -------------------------------------------------------------------------------
// --- STRUCTURE DEFINITION AND FUNCTION DECLARATIONS ---
// -------------------------------------------------------------------------------

// define a structure to store all information about one competitor
struct vs
{
    int szakitas; // store the competitor clean and jerk result
    int lokes;    // store the competitor snatch result
    int rszam;    // store the competitor identification number
    int suly;     // store the competitor body weight
    string nev;   // store the competitor name
};

// declare a function that reads competitor data from a text file into a vector
int adatbe(vector<vs>& tomb, string fn);

// declare a function that displays all competitor information
void kiir(const vector<vs>& tomb);

// declare a function that counts competitors with a combined result above 350 kg
int tobb350(const vector<vs>& tomb);

// declare a function that finds the competitor with the highest combined result
int nyert(const vector<vs>& tomb);

// declare a function that checks whether any competitor achieved exactly 150 kg
bool volt150(const vector<vs>& tomb);

// declare a function that selects competitors weighing more than 100 kg
int st100(const vector<vs>& tomb, vector<vs>& tomb1);

// declare a function that sorts competitors and writes the final results into a file
void vegeredmeny(vector<vs>& tomb);


// -------------------------------------------------------------------------------
// --- 1 MAIN PROGRAM AND COMPETITOR DATA INITIALIZATION ---
// -------------------------------------------------------------------------------

int main()
{
    // set the locale to support Hungarian characters in the console output
    setlocale(LC_ALL, "hu_HU.UTF-8");

    // create an empty dynamic vector to store all competitors
    vector<vs> verseny;

    // declare the name of the input text file
    string fnev = "versenyzok.txt";

    // read competitor data from the input file
    // store the number of registered competitors
    int letszam = adatbe(verseny, fnev);

    // display the total number of competitors
    cout << "\nA versenyen " << letszam
        << " versenyző indult." << endl;

    // display all competitor information
    kiir(verseny);

    // -------------------------------------------------------------------------------
    // --- 2 COUNTING COMPETITORS WITH A COMBINED RESULT ABOVE 350 KG ---
    // -------------------------------------------------------------------------------

    // count and display competitors whose combined result exceeds 350 kg
    cout << tobb350(verseny)
        << " versenyző összetett eredménye több mint 350 kg"
        << endl;

    // -------------------------------------------------------------------------------
    // --- 3 FINDING AND DISPLAYING THE WINNER ---
    // -------------------------------------------------------------------------------

    // find the index of the competitor with the highest combined result
    int gyoztes = nyert(verseny);

    // display the winner name and their combined result
    cout << "A versenyt " << verseny[gyoztes].nev
        << " nyerte "
        << verseny[gyoztes].szakitas + verseny[gyoztes].lokes
        << " eredménnyel" << endl;

    // -------------------------------------------------------------------------------
    // --- 4 CHECKING WHETHER A 150 KG RESULT WAS ACHIEVED ---
    // -------------------------------------------------------------------------------

    // check whether any competitor achieved exactly 150 kg in clean and jerk
    if (volt150(verseny))
    {
        // display a positive message if the result was found
        cout << "volt";
    }
    else
    {
        // display a negative message if the result was not found
        cout << "nem volt";
    }

    // complete the result checking message
    cout << " 150-es eredmény lökésből" << endl;

    // -------------------------------------------------------------------------------
    // --- 5 SELECTING COMPETITORS WEIGHING MORE THAN 100 KG ---
    // -------------------------------------------------------------------------------

    // create an empty vector for storing competitors weighing more than 100 kg
    vector<vs> t100;

    // select competitors heavier than 100 kg and count them
    int db100 = st100(verseny, t100);

    // display all selected competitors
    kiir(t100);

    // display the number of selected competitors
    cout << db100
        << " versenyző volt nehezebb 100 kg-nál"
        << endl;

    // -------------------------------------------------------------------------------
    // --- 6 SORTING COMPETITORS AND WRITING FINAL RESULTS INTO A FILE ---
    // -------------------------------------------------------------------------------

    // sort competitors by their combined results in descending order
    // save the sorted results into an output text file
    vegeredmeny(verseny);

    // return zero to indicate successful program execution
    return 0;
}


// -------------------------------------------------------------------------------
// --- 7 READING COMPETITOR DATA FROM A TEXT FILE ---
// -------------------------------------------------------------------------------

int adatbe(vector<vs>& tomb, string fn)
{
    // initialize the counter for registered competitors
    int lsz = 0;

    // open the input file for reading
    ifstream fajl(fn);

    // initialize the random number generator using the current system time
    srand((unsigned)time(NULL));

    // read at most fifteen competitors while the file contains valid data
    for (int i = 0; i < 15 && fajl; i++)
    {
        // create a temporary structure for the current competitor
        vs uj;

        // read the clean and jerk result
        fajl >> uj.szakitas;

        // read the snatch result
        fajl >> uj.lokes;

        // read the competitor name while skipping leading whitespace
        getline(fajl >> ws, uj.nev);

        // generate a random two digit identification number between 10 and 99
        uj.rszam = rand() % 90 + 10;

        // ask for the competitor weight until a valid value is entered
        do
        {
            // display the name of the competitor
            cout << "Adja meg a "
                << uj.nev
                << " versenyző súlyát [90;120]"
                << endl;

            // read the competitor weight from the keyboard
            cin >> uj.suly;

            // check whether the entered weight is within the allowed range
            if (uj.suly < 90 || uj.suly > 120)
            {
                // display an error message if the entered weight is invalid
                cout << "Hibas adat [90;120] lehet a versenyző súlya"
                    << endl;
            }

            // repeat the input process while the weight is invalid
        } while (uj.suly < 90 || uj.suly > 120);

        // add the completed competitor structure to the end of the vector
        tomb.push_back(uj);

        // increase the number of registered competitors
        lsz++;
    }

    // close the input file after reading all available data
    fajl.close();

    // return the number of registered competitors
    return lsz;
}


// -------------------------------------------------------------------------------
// --- 8 DISPLAYING ALL COMPETITOR INFORMATION ---
// -------------------------------------------------------------------------------

void kiir(const vector<vs>& tomb)
{
    // align all displayed text to the left
    cout << left;

    // iterate through every competitor in the vector
    for (int i = 0; i < tomb.size(); i++)
    {
        // display the competitor name and identification number
        cout << setw(20) << tomb[i].nev
            << " rszam " << tomb[i].rszam

            // display the competitor body weight
            << " tsuly " << setw(3) << tomb[i].suly

            // display the individual results
            << " szakitas " << setw(3) << tomb[i].szakitas
            << " lokes " << setw(3) << tomb[i].lokes

            // calculate and display the combined result
            << " ossz "
            << tomb[i].szakitas + tomb[i].lokes
            << endl;
    }
}


// -------------------------------------------------------------------------------
// --- 9 COUNTING COMPETITORS WITH A COMBINED RESULT ABOVE 350 KG ---
// -------------------------------------------------------------------------------

int tobb350(const vector<vs>& tomb)
{
    // display the section heading
    cout << "Osszetett eredmenye tobb mint 350 kg"
        << endl;

    // initialize the counter for qualifying competitors
    int db = 0;

    // check every competitor stored in the vector
    for (int i = 0; i < tomb.size(); i++)
    {
        // check whether the combined result exceeds 350 kg
        if (tomb[i].lokes + tomb[i].szakitas > 350)
        {
            // increase the counter
            db++;

            // display the competitor name
            cout << tomb[i].nev << endl;
        }
    }

    // return the number of competitors with a combined result above 350 kg
    return db;
}


// -------------------------------------------------------------------------------
// --- 10 FINDING THE COMPETITOR WITH THE HIGHEST COMBINED RESULT ---
// -------------------------------------------------------------------------------

int nyert(const vector<vs>& tomb)
{
    // assume that the first competitor is the winner
    int nyi = 0;

    // compare the results of all remaining competitors
    for (int i = 1; i < tomb.size(); i++)
    {
        // check whether the current competitor has a higher combined result
        if (tomb[i].lokes + tomb[i].szakitas >
            tomb[nyi].lokes + tomb[nyi].szakitas)
        {
            // update the winner index if a better result is found
            nyi = i;
        }
    }

    // return the index of the competitor with the highest combined result
    return nyi;
}


// -------------------------------------------------------------------------------
// --- 11 CHECKING WHETHER A COMPETITOR ACHIEVED EXACTLY 150 KG ---
// -------------------------------------------------------------------------------

bool volt150(const vector<vs>& tomb)
{
    // initialize the search index at the beginning of the vector
    int i = 0;

    // continue searching while the current result is not equal to 150 kg
    while (i < tomb.size() && tomb[i].szakitas != 150)
    {
        // move to the next competitor
        i++;
    }

    // check whether a competitor with the required result was found
    if (i < tomb.size())
    {
        // return true if the result exists
        return true;
    }
    else
    {
        // return false if the result does not exist
        return false;
    }
}


// -------------------------------------------------------------------------------
// --- 12 SELECTING COMPETITORS WEIGHING MORE THAN 100 KG ---
// -------------------------------------------------------------------------------

int st100(const vector<vs>& tomb, vector<vs>& tomb1)
{
    // initialize the counter for selected competitors
    int j = 0;

    // check every competitor in the original vector
    for (int i = 0; i < tomb.size(); i++)
    {
        // check whether the current competitor weighs more than 100 kg
        if (tomb[i].suly > 100)
        {
            // copy the complete competitor structure into the destination vector
            tomb1.push_back(tomb[i]);

            // increase the counter
            j++;
        }
    }

    // return the number of selected competitors
    return j;
}


// -------------------------------------------------------------------------------
// --- 13 SORTING COMPETITORS AND WRITING FINAL RESULTS INTO A FILE ---
// -------------------------------------------------------------------------------

void vegeredmeny(vector<vs>& tomb)
{
    // create a temporary structure for exchanging competitor information
    vs seged;

    // sort the vector in descending order using the combined results
    for (int i = 0; i < tomb.size() - 1; i++)
    {
        // compare the current competitor with all competitors after them
        for (int j = i + 1; j < tomb.size(); j++)
        {
            // check whether the current competitor has a lower combined result
            if (tomb[i].szakitas + tomb[i].lokes <
                tomb[j].szakitas + tomb[j].lokes)
            {
                // temporarily store the current competitor
                seged = tomb[i];

                // move the competitor with the higher result to the current position
                tomb[i] = tomb[j];

                // move the previously stored competitor to the other position
                tomb[j] = seged;
            }
        }
    }

    // create the output file for storing the sorted results
    ofstream ki("veredm.txt");

    // iterate through all competitors in the sorted vector
    for (int i = 0; i < tomb.size(); i++)
    {
        // write the competitor name identification number and body weight
        ki << tomb[i].nev << " "
            << tomb[i].rszam << " "
            << tomb[i].suly << " "

            // write the individual competition results
            << tomb[i].szakitas << " "
            << tomb[i].lokes << " "

            // calculate and write the combined result
            << tomb[i].szakitas + tomb[i].lokes
            << endl;
    }

    // close the output file after writing all competitor data
    ki.close();
}