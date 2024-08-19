#pragma once // Include guard to prevent multiple inclusion of header

#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include "Player.h" 
#include "GptApi.h"

class GptAPi;

class CommandInterpreter {
public:
    Player* player_;
    CommandInterpreter(Player* player);
    bool commandSpliter(std::string command);
    void commandExecutor(std::vector<std::string> command);
};

