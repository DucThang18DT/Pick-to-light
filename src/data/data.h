#pragma once

struct Data
{
    Data();
    Data(int inID, int inNumber);
    ~Data();
    int    id;
    int    number;
    bool    confirm;
};
