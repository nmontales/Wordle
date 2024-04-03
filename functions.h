#ifndef WORDLE_FUNCTIONS_H
#define WORDLE_FUNCTIONS_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

std::string getWord();
std::vector<std::string> getWords(std::string filename);
std::vector<std::string> createBoard();
void printBoard(std::vector<std::string> board);
void printAvailableCharacters();
std::string getInput();
int inWord(std::string input, std::string answer, std::vector<std::string> &board);
void playWordle();
#endif //WORDLE_FUNCTIONS_H