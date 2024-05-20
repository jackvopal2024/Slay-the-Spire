#pragma once
#include <iostream>

struct all_Cards {

    std::string card_Name;
    std::string card_Effect;
    int damage;
    int block;
    int multistrike;

    bool is_Used;
    bool in_Hand;

    int burn_Value;
    bool is_Iron_Wave;
    int flex;
    int poison_Coat;
    int heavy_Slash;
    int magnetize;
    int devour;
    int blighted_Blade;
    bool is_Reap;
    bool is_Twincast;
    int aegis;
    int cripple;
    int fester;
    bool is_Seismic_Slam;

    bool is_Shield_Bash;
};

struct player_Card {

    std::string card_Name;
    std::string card_Effect;
    int damage;
    int block;
    int multistrike;

    bool is_Used;
    bool in_Hand;

    int burn_Value;
    bool is_Iron_Wave;
    int flex;
    int poison_Coat;
    int heavy_Slash;
    int magnetize;
    int devour;
    int blighted_Blade;
    bool is_Reap;
    bool is_Twincast;
    int aegis;
    int cripple;
    int fester;
    bool is_Seismic_Slam;

    bool is_Shield_Bash;
};