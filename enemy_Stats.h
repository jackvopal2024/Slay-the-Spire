#pragma once
#include <iostream>

struct enemy_Stats  {


    int enemy_Health;
    int enemy_Max_Health;
    int enemy_Damage;
    int enemy_Block;
    std::string enemy_Name;
    int burn;
    int poison;
    int buff;

    enemy_Stats(int max_Health, int health, int damage, int enemy_Block, int burn, int poison, int buff, std::string name);
    void set_Block(int block);
    void set_Damage(int damage);
    void set_Health(int health);
    void set_Max_Health(int max_Health);
    void set_Name(std::string name);
    void set_Burn(int burn);
    void set_Poison(int poison);
    void set_Buff(int buff);

    int combat(int rarity);
    void inflict_Player_Damage(int played_Card, int blighted, int heavy_Slash);
    void enemy_Action();
    void enemy_Action_Cout();
    void end_of_Turn_Statuses();
    void card_Actions(int card_Played);
};