#include <iostream>
#include <string>
#include "enemy_Stats.h"

enemy_Stats::enemy_Stats(int max_Health, int health,  int damage, int enemy_Block, int burn, int poison, int buff, std::string name ) {
    set_Max_Health(max_Health);
    set_Health(health);
    set_Damage(damage);
    set_Block(enemy_Block);
    set_Name(name);
    set_Burn(burn);
    set_Poison(poison);
    set_Buff(buff);
}

void enemy_Stats::set_Damage(int damage) {
    enemy_Damage = damage;
}
void enemy_Stats::set_Health(int health) {
    enemy_Health = health;
}
void enemy_Stats::set_Max_Health(int max_Health) {
    enemy_Max_Health = max_Health;
}
void enemy_Stats::set_Name(std::string name) {
    enemy_Name = name;
}

void enemy_Stats::set_Block(int block) {
    enemy_Block = block;
}

void enemy_Stats::set_Burn(int burn) {
    this->burn = burn;
}
void enemy_Stats::set_Poison(int poison) {
    this->poison = poison;
}
void enemy_Stats::set_Buff(int buff) {
    this->buff = buff;
}