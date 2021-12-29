#include <iostream>
#include <string>
#include <list> //linked list

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::list;

#define CODE_SIZE 4
#define INSTRUCTIONS_FILE "instructions.txt"
//bcolors
#define BCOLORS_GREEN "\033[32m"
#define BCOLORS_ENDC "\033[0m"

string getCodeGuess();
string getSecretCode();
bool isDigits(const std::string &str);
bool uniqueCharacters(const std::string &str);
int randint(int min, int max);
bool printFile(char* fileName);

int main()
{
    /* set variables */
    string secretCode, codeGuess;
    bool win = false;
    unsigned int attempts = 0;
    unsigned int samePlaceCounter = 0;
    unsigned int digitExistsCounter = 0;
    int i = 0;
    /* initialize */
    //print instructions
    printFile(INSTRUCTIONS_FILE);
    srand (time(NULL)); //initialize random
    secretCode = getSecretCode();
    /* main code */
    while (!win)
    {
        attempts++;
        printf("Attempt %d: ", attempts);
        codeGuess = getCodeGuess();
        cout << BCOLORS_GREEN << codeGuess << endl;
        digitExistsCounter = 0;
        samePlaceCounter = 0;
        for (i = 0; i < CODE_SIZE; i++)
        {
            //if the digit is in the right place
            if (secretCode[i] == codeGuess[i])
            {
                samePlaceCounter++;
            }
            //if the digit is not in the right place exists
            else if (codeGuess.find(secretCode[i]) != std::string::npos)
            {
                digitExistsCounter++;
            }
        }
        if (samePlaceCounter == CODE_SIZE){
            win = true;
            printf("You won! After %d attempts.\n", attempts);
        }
        else
        {
            printf("Direct hits:      %d\n", samePlaceCounter);
            printf("Not direct hits:  %d\n", digitExistsCounter);
        }
        //restore print color
        cout << BCOLORS_ENDC;
    }
    return 0;
}

//returns a random secret code
string getSecretCode()
{
    /* set variables */
    string result;
    list <char> digits;
    list <char>::iterator digitsIt;
    int i = 0, digitIndex = 0;
    /* initialize */
    for (i = '0'; i <= '9'; i++) digits.push_back(i);
    /* main code */
    for (i = 0; i < CODE_SIZE; i++)
    {
        digitIndex = randint(0, 9 - i);
        digitsIt = std::next(digits.begin(), digitIndex);
        result += *digitsIt;
        digits.erase(digitsIt);
    }
    return result;
}

//get a code guess from the user, if user guess invalid try again
string getCodeGuess()
{
    /* set variables */
    bool errorFlag = true;
    string codeGuess;
    /* main code */
    while (errorFlag)
    {
        errorFlag = false;
        cout << "Enter a guess (Example: 1234):";
        cin >> codeGuess;
        //check errors
        if (codeGuess.length() != CODE_SIZE)
        {
            errorFlag = true;
            cout << "Guess length is not 4 digits, Try again." << endl;
        }
        else if (!isDigits(codeGuess))
        {
            errorFlag = true;
            cout << "Guess does not contain only digits, Try again." << endl;
        }
        else if (!uniqueCharacters(codeGuess))
        {
            errorFlag = true;
            cout << "Guess does not contain only unique digits, Try again." << endl;
        }
    }
    return codeGuess;
}

//is the sring made only of digits
bool isDigits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

//checks if all the characters in the string are present only once.
bool uniqueCharacters(const std::string &str)
{
    // If at any time we encounter 2 same characters, return false
    for (int i = 0; i < str.length() - 1; i++) {
        for (int j = i + 1; j < str.length(); j++) {
            if (str[i] == str[j]) {
                return false;
            }
        }
    }
    // If no duplicate characters encountered return true
    return true;
}

//get a random integer
int randint(int min, int max)
{
    return min + rand() % (max + 1 - min);
}

//print all the contant of a file
bool printFile(char* fileName)
{
    FILE *fptr;
    char s;
    fptr = fopen(fileName,"r");
    if (fptr)
    {
        while((s=fgetc(fptr))!=EOF) {
            printf("%c",s);
        }
        fclose(fptr);
    }
    return (bool)fptr;
}