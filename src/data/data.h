#pragma once

struct Data
{
    Data();
    Data(char inID, char inNumber);
    ~Data();
    char    id;
    char    number;
    bool    confirm;
};
