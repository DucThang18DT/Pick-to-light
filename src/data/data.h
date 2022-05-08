#pragma once

struct Data
{
    Data(char inID, char inNumber);
    ~Data();
    char    id;
    char    number;
    bool    confirm;
};
