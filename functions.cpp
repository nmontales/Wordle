#include "functions.h"

int tries = 6; //global variable for tries
int currentTry = 0; //global variable for current try
std::string allCharacters = "abcdefghijklmnopqrstuvwxyz"; //global variable for every letter in the alphabet

std::string getWord()
{
    srand(time(0));
    std::string actualWord;
    std::string filename = "word.txt";
    std::vector<std::string> wordList = getWords(filename);
    actualWord = wordList[rand() % wordList.size()];
    return actualWord;
}

std::vector<std::string> getWords(std::string filename)
{
    std::ifstream fin;
    fin.open(filename);
    if (fin.fail())
    {
        std::cout << "File couldn't be open ";
        exit (15);
    }
    std::string word;
    std::vector<std::string> wordList;
    while (fin >> word)
    {
        wordList.push_back(word);
    }
    fin.close();
    return wordList;
}

std::vector<std::string> createBoard()
{
    currentTry = 0;//set tries back to 0 if the player wants to play again
    allCharacters = "abcdefghijklmnopqrstuvwxyz";//resets the available characters
    return std::vector<std::string> (6, "*****");//creates the outline

}

void printBoard(std::vector<std::string> board)
{
    for(int i = 0; i < board.size(); i++)
    {
        std::cout << board[i] << std::endl; //prints out the board
    }
}

void printAvailableCharacters()
{
    for(int i = 0; i < allCharacters.length(); i++)
    {
        std::cout << allCharacters[i] << " "; //prints out all the letters in the alphabet and indexes them so that there can be a space in between each one
    }
    std::cout << std::endl;//starts on a new line every guess
}

std::string getInput()
{
    std::string input;
    std::cin >> input;

    return input;
}

int inWord(std::string input, std::string answer, std::vector<std::string> &board)
{
    for(int i=0; i<5; i++)//check if each character in the input is in the actual word
    {
        answer[i] = tolower(answer[i]);//set answer to always start lowercase
        input[i] = tolower(input[i]);//set input to always start lowercase
        size_t found = answer.find(input[i]);//search the string for the first appearance of character at index i

        if(found != std::string::npos)//if it was found
        {
            allCharacters[input[i] - 'a'] = toupper(input[i]);//getting the index of the character in the alphabet and capitalizing it
        }
        else
        {
            allCharacters[input[i] - 'a'] = '_';//the character doesn't exist and changes the character on the bottom to an underscore
        }
    }

    int lettersInWord = 0;//counts how many letters there are
    int lettersInWordIndex[5] = {0};//tracks the indices of the correct letters

    for(int i=0; i<5; i++)//sets the correct letters
    {
        if(input[i] == (answer[i]))//if the letter is in the right place and is the correct letter
        {
            board[currentTry][i] = toupper(input[i]);//setting the character on the board to be uppercase to show that it is correct
            answer[i] = '_';//replace the character so it isn't matched again
            lettersInWordIndex[i] = 1;//index i is correct
            lettersInWord ++;//increment correct letters
        }

    }
    for(int i=0; i < 5; i++)//set the letters that are in the word but not in the right spot
    {
        if(lettersInWordIndex[i])//if the index is already correct skip
        {
            continue;
        }
        size_t first = answer.find(input[i]);//search the string for the first appearance of character at index i
        if(first != std::string::npos)
        {
            board[currentTry][i] = (input[i]);//if the string is found add it to the board as lowercase
            answer[first] = '_';//replace the character so it isn't matched again
        }
        else
        {
            board[currentTry][i] = '_';//letter not found
        }
    }

    currentTry ++;//incrementing the amount of tries the user is on
    return lettersInWord;
}

void playWordle()
{
    char repeat;
    do{
        std::string actualWord = getWord();//setting the getWord function to a variable
        std::vector<std::string> board = createBoard();//printing the board
        bool won = false;//set to false so that we can make the win condition

        for(int i=0; i < tries; i++)//loops the amount of tries the user gets
        {
            printBoard(board);//prints the board
            printAvailableCharacters();//shows the characters the user can use

            std::string input = getInput();//takes the user input
            if(inWord(input, actualWord, board) == 5)//if all 5 characters match
            {
                won = true;//user wins
                break;
            }

        }

        printBoard(board);
        printAvailableCharacters();

        if(won)
        {
            std::cout << "congrats you guessed the word! \n";
        }
        else
        {
            std::cout << "You have no more tries the correct word was " << actualWord << std::endl;
        }

        std::cout << "Would you like to play again? (y/n) \n";
        std::cin >> repeat;
        repeat = tolower(repeat);

    }while(repeat == 'y');
}