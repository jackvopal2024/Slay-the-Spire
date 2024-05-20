#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <random>
#include "all_Cards.h"
#include "enemy_Stats.h"



int next_Slot = 8;
int poison_Value;
int aegis;


//player's stats
int player_Max_Health = 100;
int player_Current_Health = 100;
int player_Current_Block = 0;
//card related
int card_Plays = 3;
int max_Card_Plays = 3;
int card_Draws = 5;
int card_Played_Holder;
bool is_Players_Turn = true;



//enemy related variables
int enemy_Intention;
int current_Enemy_Block;
int encounter_Num;
int enemy_Intention3;

bool buff_Cout;
bool burn_Cout;
bool poison_Cout;
// max health, current health, damage, and block




enum card_Names {
    Strike = 0,
    Block = 1,
    Iron_Wave = 2,
    Flex = 3,
    Poison_Coat = 4,
    Shield_Bash = 5,
    Cripple = 6,
    Cinderstorm = 7,
    Magnetize = 8,
    Hydra_Strike = 9,
    Devour = 10,
    Heavy_Slash = 11,
    Reap = 12,
    Seismic_Slam = 13,
    Twincast = 14,
    Blighted_Blade = 15,
    Fester = 16,
    Aegis = 17

};
enum player_Cards {
    Strike1 = 0,
    Strike2 = 1,
    Strike3 = 2,
    Strike4 = 3,
    Block1 = 4,
    Block2 = 5,
    Block3 = 6,
    Block4 = 7,

};


int card_Choice;
int* random_Card = new int[3];
// this is the cards the player has in their deck
all_Cards player_Deck[20];
//these are all the cards in the game
all_Cards cards[18];

int cards_Drawn[5];

int discard_Pile[15];
int cards_In_Discard;
int cards_In_Draw;
int card_Play;



//status effect related variables
int burn_Counter;
int burn_Timer;
int poison_Counter;
int flex_Counter;
int cripple_Counter;
int magnetize_Counter;
int poison_Coat;
int twincast_Counter;
int aegis_Counter;

int enemy_Buff_Counter;

//status effect inflicted upon the player
int player_Burn_Counter;
int player_Burn_Timer;
int player_Poison_Counter;

//status effect functions

//this preforms what the different status effects are supposed to do, then reduce them as needed
void enemy_Stats::end_of_Turn_Statuses() {
    poison_Coat = 0;
    if (poison_Counter > 0) {
        enemy_Health -= poison_Counter;
    }
    if (burn_Timer == 0) {
        burn_Counter = 0;
    }
    else if (burn_Timer > 0) {
        enemy_Health -= burn_Counter;
        burn_Timer -= 1;
    }

}
//for after combat when most statuses wear off
void end_Statuses() {
    flex_Counter = 0;
    cripple_Counter = 0;
    magnetize_Counter = 0;
    poison_Counter = 0;
    burn_Timer = 0;
    burn_Counter = 0;
    aegis_Counter = 0;
    cripple_Counter = 0;
}

void start_of_Turn_Statuses() {
    player_Current_Block += magnetize_Counter;
    if (magnetize_Counter > 0) {
        //check_For_Shield();
    }


    enemy_Buff_Counter = 0;
}

void inflict_Poison(int poison) {
    player_Poison_Counter += poison;
    poison_Cout = true;
}
void inflict_Burn(int burn) {
    player_Burn_Counter += burn;
    player_Burn_Timer = 3;
    burn_Cout = true;
}
void inflict_Buff(int buff) {
    cripple_Counter += buff;
    buff_Cout = true;
}



//displaying information
void display_Player_Stats() {

    std::cout << "Health: " << player_Current_Health << "/" << player_Max_Health << std::endl;
    std::cout << "Block: " << player_Current_Block << std::endl;
    std::cout << std::endl;
}
void display_Piles() {
    std::cout << std::endl;
    std::cout << "Draw Pile: " << cards_In_Draw << "/" << next_Slot << std::endl;
    std::cout << "Discard Pile: " << cards_In_Discard << "/" << next_Slot << std::endl;
    std::cout << std::endl;
}
void display_Card_Plays() {

    std::cout << "You have " << card_Plays << " card plays left" << std::endl;
    std::cout << std::endl;
}

int display_Statuses() {
    std::cout << "STATUS EFFECTS:" << std::endl;
    if (player_Poison_Counter == 0 && player_Burn_Timer == 0 && flex_Counter == 0 && poison_Coat == 0 && magnetize_Counter == 0 && aegis_Counter == 0 && twincast_Counter == 0) {
        std::cout << "None" << std::endl;

    }
    if (player_Poison_Counter > 0) {
        std::cout << player_Poison_Counter << " Poison" << std::endl;
    }
    if (player_Burn_Timer > 0) {
        std::cout << player_Burn_Counter << " Burn for " << player_Burn_Timer << " turns" << std::endl;
    }
    if (flex_Counter > 0) {
        std::cout << " +" << flex_Counter << " damage" << std::endl;
    }
    if (poison_Coat > 0) {
        std::cout << " Poison Coat " << std::endl;
    }
    if (magnetize_Counter > 0) {
        std::cout << magnetize_Counter << " armor per turn " << std::endl;
    }
    if (aegis_Counter > 0) {
        std::cout << aegis_Counter << " Aegis " << std::endl;
    }
    if (twincast_Counter > 0) {
        std::cout << " Twincast" << std::endl;
    }
    std::cout << std::endl;
    std::cout << " ENEMY STATUS EFFECTS: " << std::endl;
    if (poison_Counter == 0 && burn_Timer == 0 && cripple_Counter == 0) {
        std::cout << "None" << std::endl;
        return 0;
    }
    if (poison_Counter > 0) {
        std::cout << poison_Counter << " Poison" << std::endl;
    }
    if (burn_Timer > 0) {
        std::cout << burn_Counter << " Burn for " << burn_Timer << " turns" << std::endl;
    }
    if (cripple_Counter < 0) {
        std::cout << " -" << cripple_Counter << " damage" << std::endl;
    }
    else if (cripple_Counter > 0) {
        std::cout << " +" << cripple_Counter << " damage" << std::endl;
    }


    return 0;
}

void display_Enemy_Stats(int& enemy_Health, int& enemy_Max_Health, std::string name) {

    std::cout << name << " Health: " << enemy_Health << "/" << enemy_Max_Health << std::endl;
    std::cout << name << " Block: " << current_Enemy_Block << std::endl << std::endl;
}

//adding new cards to your deck
void declare_Cards() {
    cards[card_Names::Strike].card_Name = "Strike";
    cards[card_Names::Strike].card_Effect = "Deal 10 damage";
    cards[card_Names::Strike].damage = 10;

    cards[card_Names::Block].card_Name = "Block";
    cards[card_Names::Block].card_Effect = "Gain 10 block";
    cards[card_Names::Block].block = 10;
    //1
    cards[card_Names::Iron_Wave].card_Name = "Iron Wave";
    cards[card_Names::Iron_Wave].card_Effect = "Deal 7 damage and gain block equal to damage dealt";
    cards[card_Names::Iron_Wave].damage = 7;
    cards[card_Names::Iron_Wave].multistrike = 1;
    cards[card_Names::Iron_Wave].is_Iron_Wave = true;
    //done

    cards[card_Names::Flex].card_Name = "Flex";
    cards[card_Names::Flex].card_Effect = "This combat, your attacks will deal +2 damage ";
    cards[card_Names::Flex].flex = 2;
    //done

    cards[card_Names::Poison_Coat].card_Name = "Poison Coat";
    cards[card_Names::Poison_Coat].card_Effect = "This turn, each time you deal damage you will inflict 2 poison";
    cards[card_Names::Poison_Coat].poison_Coat = 2;
    //done

    cards[card_Names::Shield_Bash].card_Name = "Brace";
    cards[card_Names::Shield_Bash].card_Effect = "Gain 20 block, and your attacks will deal +1 damage";
    cards[card_Names::Shield_Bash].flex = 1;
    cards[card_Names::Shield_Bash].block = 20;


    //2
    cards[card_Names::Cripple].card_Name = "Cripple";
    cards[card_Names::Cripple].card_Effect = "Target will deal 5 less damage this combat ";
    cards[card_Names::Cripple].cripple = 5;
    //done i think

    cards[card_Names::Cinderstorm].card_Name = "Cinderstorm";
    cards[card_Names::Cinderstorm].card_Effect = "Apply 8 burn";
    cards[card_Names::Cinderstorm].burn_Value = 8;
    //done

    cards[card_Names::Magnetize].card_Name = "Magnetize";
    cards[card_Names::Magnetize].card_Effect = "You gain 5 block at the beginning of every turn for the rest of combat";
    cards[card_Names::Magnetize].magnetize = 5;
    //done i think, but not tested

    cards[card_Names::Hydra_Strike].card_Name = "Hydra Strike";
    cards[card_Names::Hydra_Strike].card_Effect = "Deals 2 damage eight times";
    cards[card_Names::Hydra_Strike].damage = 2;
    cards[card_Names::Hydra_Strike].multistrike = 8;
    //done

    //3
    cards[card_Names::Devour].card_Name = "Devour";
    cards[card_Names::Devour].card_Effect = "Consume all the status effect counters and deal 2 damage for each counter";
    cards[card_Names::Devour].devour = 2;
    cards[card_Names::Devour].multistrike = 0;
    //done i think, but not tested

    cards[card_Names::Heavy_Slash].card_Name = "Heavy Slash";
    cards[card_Names::Heavy_Slash].card_Effect = "Deals 15 damage, any damage increase applies 5 times to this attack";
    cards[card_Names::Heavy_Slash].damage = 15;
    cards[card_Names::Heavy_Slash].multistrike = 1;
    cards[card_Names::Heavy_Slash].heavy_Slash = 5;
    //done i think, but not tested

    cards[card_Names::Reap].card_Name = "Reap";
    cards[card_Names::Reap].card_Effect = "Deal 15 damage and heal all of the damage you deal";
    cards[card_Names::Reap].damage = 15;
    cards[card_Names::Reap].multistrike = 1;
    cards[card_Names::Reap].is_Reap = true;
    //done i think, but not tested

    cards[card_Names::Seismic_Slam].card_Name = "Seismic Slam";
    cards[card_Names::Seismic_Slam].card_Effect = "Deal damage equal to your current block";
    cards[card_Names::Seismic_Slam].multistrike = 1;
    cards[card_Names::Seismic_Slam].is_Seismic_Slam = true;
    //done i think
    //4
    cards[card_Names::Twincast].card_Name = "Twincast";
    cards[card_Names::Twincast].card_Effect = "Your next card will be played again";
    cards[card_Names::Twincast].is_Twincast = true;
    //done i think, but not tested

    cards[card_Names::Blighted_Blade].card_Name = "Blighted Blade";
    cards[card_Names::Blighted_Blade].card_Effect = "Deal 5 damage, if the target has poison deal +30 damage ";
    cards[card_Names::Blighted_Blade].multistrike = 1;
    cards[card_Names::Blighted_Blade].blighted_Blade = 30;
    //done i think, but not tested

    cards[card_Names::Fester].card_Name = "Fester";
    cards[card_Names::Fester].card_Effect = "Triple amount of poison counters on target ";
    cards[card_Names::Fester].fester = 3;
    //done i think

    cards[card_Names::Aegis].card_Name = "Aegis";
    cards[card_Names::Aegis].card_Effect = "Gain 40 block, this block will not disappear after your turn ends";
    cards[card_Names::Aegis].block = 40;
    cards[card_Names::Aegis].aegis = 40;
    //done i think, but not tested

}

void declare_Player_Cards() {
    player_Deck[player_Cards::Strike1].card_Name = "Strike";
    player_Deck[player_Cards::Strike1].card_Effect = "Deal 10 damage";
    player_Deck[player_Cards::Strike1].damage = 10;
    player_Deck[player_Cards::Strike1].multistrike = 1;

    player_Deck[player_Cards::Strike2].card_Name = "Strike1";
    player_Deck[player_Cards::Strike2].card_Effect = "Deal 10 damage";
    player_Deck[player_Cards::Strike2].damage = 10;
    player_Deck[player_Cards::Strike2].multistrike = 1;

    player_Deck[player_Cards::Strike3].card_Name = "Strike2";
    player_Deck[player_Cards::Strike3].card_Effect = "Deal 10 damage";
    player_Deck[player_Cards::Strike3].damage = 10;
    player_Deck[player_Cards::Strike3].multistrike = 1;

    player_Deck[player_Cards::Strike4].card_Name = "Strike3";
    player_Deck[player_Cards::Strike4].card_Effect = "Deal 10 damage";
    player_Deck[player_Cards::Strike4].damage = 10;
    player_Deck[player_Cards::Strike4].multistrike = 1;

    player_Deck[player_Cards::Block1].card_Name = "Block";
    player_Deck[player_Cards::Block1].card_Effect = "Gain 10 block";
    player_Deck[player_Cards::Block1].block = 10;

    player_Deck[player_Cards::Block2].card_Name = "Block1";
    player_Deck[player_Cards::Block2].card_Effect = "Gain 10 block";
    player_Deck[player_Cards::Block2].block = 10;

    player_Deck[player_Cards::Block3].card_Name = "Block2";
    player_Deck[player_Cards::Block3].card_Effect = "Gain 10 block";
    player_Deck[player_Cards::Block3].block = 10;

    player_Deck[player_Cards::Block4].card_Name = "Block3";
    player_Deck[player_Cards::Block4].card_Effect = "Gain 10 block";
    player_Deck[player_Cards::Block4].block = 10;
}

void generate_Card(int cards) {

    int j = 0;
    //this is a generator to generate the random 3 cards for the player to select, but it makes sure there are no repeats
    //the three values generated correspond to a specific card and are added to the random cards array
    for (int i = 0; i < 3; i += 1) {

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distribution(2, (5 + (cards * 4)));
        int next_Card_in_Pack = distribution(gen);


        while (j < 3) {
            bool is_Not_Used = true;
            for (int i = 0; i <= j; i += 1) {
                if (next_Card_in_Pack == random_Card[i]) {
                    is_Not_Used = false;
                    break;
                }
            }

            if (is_Not_Used) {
                random_Card[j] = next_Card_in_Pack;
                j += 1;

            }
            next_Card_in_Pack = distribution(gen);
        }
    }
}

void card_Promt(int card) {
    if (card >= 0) {
        generate_Card(card);


        std::cout << "Congratulations! To pick a card, enter 1, 2, 3 or 0 to skip" << std::endl;
        std::cout << "1. " << cards[random_Card[0]].card_Name << ": " << cards[random_Card[0]].card_Effect << std::endl;
        std::cout << "2. " << cards[random_Card[1]].card_Name << ": " << cards[random_Card[1]].card_Effect << std::endl;
        std::cout << "3. " << cards[random_Card[2]].card_Name << ": " << cards[random_Card[2]].card_Effect << std::endl;
        std::cin >> card_Choice;
        while (card_Choice < 0 || card_Choice > 3) {
            std::cout << "Invalid choice. Please enter 1, 2, 3, or 0 to skip: " << std::endl;
            std::cin >> card_Choice;
        }

    }
    system("cls");
}

void add_Card(int num, int card) {

    player_Deck[num].card_Name = cards[card].card_Name;
    player_Deck[num].card_Effect = cards[card].card_Effect;
    player_Deck[num].damage = cards[card].damage;
    player_Deck[num].block = cards[card].block;
    player_Deck[num].burn_Value = cards[card].burn_Value;
    player_Deck[num].multistrike = cards[card].multistrike;
    player_Deck[num].is_Iron_Wave = cards[card].is_Iron_Wave;
    player_Deck[num].heavy_Slash = cards[card].heavy_Slash;
    player_Deck[num].magnetize = cards[card].magnetize;
    player_Deck[num].devour = cards[card].devour;
    player_Deck[num].blighted_Blade = cards[card].blighted_Blade;
    player_Deck[num].is_Reap = cards[card].is_Reap;
    player_Deck[num].poison_Coat = cards[card].poison_Coat;
    player_Deck[num].flex = cards[card].flex;
    player_Deck[num].is_Twincast = cards[card].is_Twincast;
    player_Deck[num].aegis = cards[card].aegis;
    player_Deck[num].cripple = cards[card].cripple;
    player_Deck[num].is_Shield_Bash= cards[card].is_Shield_Bash;
    player_Deck[num].fester = cards[card].fester;
    player_Deck[num].is_Seismic_Slam = cards[card].is_Seismic_Slam;
    next_Slot += 1;
}




void card_Pack(int next_Slot, int cards) {

    if (cards >= 0) {
        card_Promt(cards);

        if (card_Choice == 0) {
            std::cout << "You chose not to add any new cards to your deck" << std::endl;
        }
        if (card_Choice == 1) {
            //num is the value of the slot in the player deck the new card will replace, and the second value is for the random cards array
            //add_Cards(num, 0);
            add_Card(next_Slot, random_Card[0]);
        }
        if (card_Choice == 2) {
            add_Card(next_Slot, random_Card[1]);
            //add_Cards(num, 1);
        }
        if (card_Choice == 3) {
            //add_Cards(num, 2);
            add_Card(next_Slot, random_Card[2]);
        }
    }
    //system("cls");
}

//drawing cards
void reshuffle_Cards(std::string draw_Or_Discard) {
    bool is_Used = false;
    if (cards_In_Draw <= 0) {
        cards_In_Draw = cards_In_Discard;
        cards_In_Discard = 0;
        for (int i = 0; i < next_Slot; i += 1) {
            if (player_Deck[i].in_Hand == false) {
                player_Deck[i].is_Used = false;
            }
        }
    }
    if (draw_Or_Discard == "Draw") {
        cards_In_Draw -= 1;
    }
    else if (draw_Or_Discard == "Discard") {
        cards_In_Discard += 1;
    }
}
void shuffle_Remaining_Cards() {

    for (int i = 0; i < card_Draws; i += 1) {
        if (cards_Drawn[i] >= 0) {

            reshuffle_Cards("Discard");
            (cards_Drawn[i] - 1) * -1;
            player_Deck[cards_Drawn[i]].is_Used = true;
            player_Deck[cards_Drawn[i]].in_Hand = false;
            cards_Drawn[i] = -1;
        }
    }
}

void draw_Cards(int card_Amount) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(0, next_Slot - 1);
    int j = 0;
    while (j < card_Amount) {

        int next_Card_Drawn = distribution(gen);
        if (cards_In_Draw <= 0) {
            cards_In_Draw = cards_In_Discard;
            cards_In_Discard = 0;
            for (int i = 0; i < next_Slot; i += 1) {
                if (player_Deck[i].in_Hand == false) {
                    player_Deck[i].is_Used = false;
                }
            }

        }

        if (player_Deck[next_Card_Drawn].is_Used == false && player_Deck[next_Card_Drawn].in_Hand == false) {
            player_Deck[next_Card_Drawn].in_Hand = true;
            cards_In_Draw -= 1;
            cards_Drawn[j] = next_Card_Drawn;
            j += 1;
        }
    }
}

void reset_Deck() {
    for (int i = 0; i < next_Slot; i += 1) {
        player_Deck[i].is_Used = false;
        player_Deck[i].in_Hand = false;
    }
}

int display_Cards_Drawn(int card_Amount) {

    if (card_Plays == 0) {
        std::cout << "You have 0 card plays left, please enter 0 to end your turn" << std::endl;
        std::cin >> card_Play;
        is_Players_Turn = false;
        return 0;
    }
    else if (card_Plays > 0) {
        std::cout << "Select which card you would like to play, or if you would like to end your turn enter 0" << std::endl;
        for (int i = 0; i < card_Amount; i += 1) {
            if (cards_Drawn[i] >= 0) {
                if (player_Deck[cards_Drawn[i]].damage > 0 && flex_Counter > 0) {
                    std::cout << (i + 1) << ". " << player_Deck[cards_Drawn[i]].card_Name << ": " << player_Deck[cards_Drawn[i]].card_Effect << " +" << flex_Counter << " damage" << std::endl;
                }
                else {
                    std::cout << (i + 1) << ". " << player_Deck[cards_Drawn[i]].card_Name << ": " << player_Deck[cards_Drawn[i]].card_Effect << std::endl;
                }
            }
        }
    }
    std::cin >> card_Play;
    return 0;
}


int plays_Card() {
    bool is_Used = false;
    if (card_Play == 0) {
        is_Players_Turn = false;
        return 0;
    }
    if (cards_Drawn[card_Play - 1] < 0) {
        is_Used = true;
    }
    while (card_Play < 0 || card_Play > card_Draws || is_Used || cards_Drawn[card_Play - 1] < 0) {
        std::cout << "Please try again. Select which card you would like to play, or if you would like to end your turn enter 0" << std::endl;
        std::cin >> card_Play;
        is_Used = false;
        if (card_Play == 0) {
            is_Players_Turn = false;
            return 0;
        }
        else if (cards_Drawn[card_Play - 1] < 0) {
            is_Used = true;
        }
    }


    if (cards_Drawn[card_Play - 1] >= 0) {
        card_Played_Holder = cards_Drawn[card_Play - 1];
        player_Deck[cards_Drawn[card_Play - 1]].is_Used = true;
        player_Deck[cards_Drawn[card_Play - 1]].in_Hand = false;
        cards_Drawn[card_Play - 1] = (cards_Drawn[card_Play - 1] + 1) * -1;
        card_Plays -= 1;
        reshuffle_Cards("Discard");
    }
    if (card_Play == 0) {
        is_Players_Turn = false;
    }
    is_Used = false;
    return 0;
}
//inflicts card damage
void enemy_Stats::inflict_Player_Damage(int played_Card, int blighted, int heavy_Slash) {
    for (int i = player_Deck[played_Card].multistrike; i > 0; i -= 1) {
        if (current_Enemy_Block > 0) {
            current_Enemy_Block -= (player_Deck[played_Card].damage) + (flex_Counter * heavy_Slash) + blighted;
        }
        else if (current_Enemy_Block == 0) {
            enemy_Health -= (player_Deck[played_Card].damage) + (flex_Counter * heavy_Slash) + blighted;
        }
        if (current_Enemy_Block < 0) {
            enemy_Health += current_Enemy_Block;
            current_Enemy_Block = 0;
        }

        if (player_Deck[played_Card].is_Reap) {
            for (int i = 0; i < player_Deck[played_Card].damage + flex_Counter && player_Current_Health < player_Max_Health; i += 1) {
                player_Current_Health += 1;
            }
        }
        else if (player_Deck[played_Card].is_Iron_Wave) {
            player_Current_Block += (player_Deck[played_Card].damage + flex_Counter);
        }

        if (poison_Coat > 0) {
            poison_Counter += poison_Coat;
        }
    }
}
// function for each time the player plays a card, will do specific things based on the fields of player_Card struct
void enemy_Stats::card_Actions(int played_Card) {
    for (int i = 0; i < twincast_Counter + 1; i += 1) {
        if (card_Play > 0) {
            if (player_Deck[played_Card].blighted_Blade > 0) {
                if (poison_Counter > 0) {
                    inflict_Player_Damage( played_Card, player_Deck[played_Card].blighted_Blade, 1);

                }
                else {
                    inflict_Player_Damage( played_Card, 0, 1);
                }
            }
            else if (player_Deck[played_Card].heavy_Slash > 0) {
                inflict_Player_Damage( played_Card, 0, player_Deck[played_Card].heavy_Slash);
            }
            else if (player_Deck[played_Card].devour > 0) {
                player_Deck[played_Card].multistrike = (poison_Counter + burn_Counter);
                player_Deck[played_Card].damage = player_Deck[played_Card].devour;
                inflict_Player_Damage( played_Card, 0, 1);
                burn_Timer = 0;
                burn_Counter = 0;
                poison_Counter = 0;
                player_Deck[played_Card].multistrike = 0;
                player_Deck[played_Card].damage = 0;

            }
            else if (player_Deck[played_Card].damage > 0) {
                inflict_Player_Damage( played_Card, 0, 1);

            }
            if (player_Deck[played_Card].block > 0) {
                player_Current_Block += player_Deck[played_Card].block;
                //check_For_Shield();
                if (player_Deck[played_Card].aegis > 0) {
                    aegis_Counter += player_Deck[played_Card].aegis;
                }
            }

            if (player_Deck[played_Card].burn_Value > 0) {
                burn_Counter += player_Deck[played_Card].burn_Value;
                burn_Timer = 3;
            }

            else if (player_Deck[played_Card].flex > 0) {
                flex_Counter += player_Deck[played_Card].flex;
            }
            else if (player_Deck[played_Card].magnetize > 0) {
                magnetize_Counter += player_Deck[played_Card].magnetize;
            }

            else if (player_Deck[played_Card].poison_Coat > 0) {
                poison_Coat += player_Deck[played_Card].poison_Coat;
            }
            else if (player_Deck[played_Card].cripple > 0) {
                for (int i = 0; i < player_Deck[played_Card].cripple && cripple_Counter < enemy_Damage; i += 1) {
                    cripple_Counter -= 1;
                }
            }
            else if (player_Deck[played_Card].fester > 0) {
                poison_Counter = poison_Counter * player_Deck[played_Card].fester;
            }
            else if (player_Deck[played_Card].is_Seismic_Slam) {
                player_Deck[played_Card].damage = player_Current_Block;
                inflict_Player_Damage( played_Card, player_Deck[played_Card].blighted_Blade, 1);
                player_Deck[played_Card].damage = 0;
            }




        }
    }
    if (twincast_Counter > 0) {
        twincast_Counter -= 1;
    }
    else if (player_Deck[played_Card].is_Twincast) {
        twincast_Counter += 1;
    }

}


// enemy actions and intentions
void random_Enemy_Intention() {
    int num_Intentions = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    if (encounter_Num >= 5) {
        num_Intentions = 1;
    }
    std::uniform_int_distribution<> distribution(1, 3 + num_Intentions);
    enemy_Intention = distribution(gen);

}

void enemy_Intention_Cout() {
    //function for telling the player if the enemy will attack, block, or something else. This is not for the enemy action
    if (enemy_Intention == 1) {
        std::cout << "This enemy intends to attack " << std::endl << std::endl;
    }
    else if (enemy_Intention == 2) {
        std::cout << "This enemy intends to block " << std::endl << std::endl;
    }
    else if (enemy_Intention == 3) {
        std::cout << "This enemy intends to preform a special action" << std::endl << std::endl;
    }
    else if (enemy_Intention == 4) {
        std::cout << "This enemy intends to preform a special attack" << std::endl << std::endl;
    }
}


//enemy action based on enemy intention
void enemy_Stats::enemy_Action() {
    //attack
    if (enemy_Intention == 1) {
        if (player_Current_Block > 0) {
            player_Current_Block -= (enemy_Damage + cripple_Counter);

        }
        else if (player_Current_Block == 0) {
            player_Current_Health -= (enemy_Damage + cripple_Counter);
        }
        if (player_Current_Block < 0) {
            player_Current_Health += player_Current_Block;
            player_Current_Block = 0;
        }

    }
    //block
    if (enemy_Intention == 2) {
        current_Enemy_Block += enemy_Block;
    }
    //other
    if (enemy_Intention == 3) {
        if (burn > 0 && poison > 0) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distribution(1, 2);
            enemy_Intention3 = distribution(gen);
            if (enemy_Intention3 == 1) {
                inflict_Poison(poison);
            }
            if (enemy_Intention3 == 2) {
                inflict_Burn(burn);
            }

        }
        else if (burn > 0 && buff > 0) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distribution(1, 2);
            enemy_Intention3 = distribution(gen);
            if (enemy_Intention3 == 1) {
                inflict_Burn(burn);
            }
            if (enemy_Intention3 == 2) {
                inflict_Buff(buff);

            }
        }
        else if (poison > 0 && buff > 0) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distribution(1, 2);
            enemy_Intention3 = distribution(gen);
            if (enemy_Intention3 == 1) {
                inflict_Poison(poison);
            }
            if (enemy_Intention3 == 2) {
                inflict_Buff(buff);

            }
        }
        else if (poison > 0 && burn > 0 && buff > 0) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distribution(1, 3);
            enemy_Intention3 = distribution(gen);
            if (enemy_Intention3 == 1) {
                inflict_Poison(poison);
            }
            else if (enemy_Intention3 == 1) {
                inflict_Burn(burn);
            }
            else if (enemy_Intention3 == 3) {
                inflict_Buff(buff);
            }

        }
        else if (burn > 0) {
            inflict_Burn(burn);
        }
        else if (poison > 0) {
            inflict_Poison(poison);
        }
        else if (buff > 0){
            inflict_Buff(buff);
        }

    }
    // block and attack
    if (enemy_Intention == 4) {
        int damage = (enemy_Damage / 1.5);
        int block = (enemy_Block / 1.5);

        current_Enemy_Block += enemy_Block;

        if (player_Current_Block > 0) {
            player_Current_Block -= (damage + enemy_Buff_Counter);
        }
        else if (player_Current_Block == 0) {
            player_Current_Health -= (damage + enemy_Buff_Counter);
        }
        if (player_Current_Block < 0) {
            player_Current_Health += player_Current_Block;
        }
    }

}

void enemy_Stats::enemy_Action_Cout() {
    if (enemy_Intention == 1) {
        std::cout << "This enemy dealt " << (enemy_Damage+cripple_Counter) << " damage" << std::endl;
    }
    if (enemy_Intention == 2) {
        std::cout << "This enemy gained " << enemy_Block << " block" << std::endl;
    }
    if (enemy_Intention == 3) {
        if (poison_Cout) {
            std::cout << "This enemy inflicted " << poison << " poison" << std::endl;
        }
        if (burn_Cout) {
            std::cout << "This enemy inflicted " << burn << " burn" << std::endl;
        }
        if (buff_Cout) {
            std::cout << "This enemy deals +" << buff << " more damage" << std::endl;
        }
    }
    if (enemy_Intention == 4) {
        std::cout << "This enemy dealt " << (enemy_Damage/1.5) << ", and gained " << (enemy_Block/1.5) << " block" << std::endl;
    }
    std::cout << std::endl;
    enemy_Intention3 = 0;
    poison_Cout = false;
    burn_Cout = false;
    buff_Cout = false;
}


//player combat functions



void press_X_to_Continue() {
    std::cout << "Press 'x' to continue" << std::endl;
    std::string x;
    std::cin >> x;
    while (x != "x") {
        std::cout << "Error, press 'x' to continue" << std::endl;
        std::cin >> x;
    }
    system("cls");
}
void heal_Or_Cure() {
    std::cout << "Press 1 to heal to full health, or press 2 to remove poison" << std::endl;
    int choice;
    std::cin >> choice;
    while (choice < 1 || choice > 2) {
        std::cout << "Error, press 1 to heal to full health, or press 2 to remove poison" << std::endl;
        std::cin >> choice;
    }
    if (choice == 1) {
        for (int i = 0; player_Current_Health < player_Max_Health; i += 1) {
            player_Current_Health += 1;
        }
        std::cout << "You were healed to full health!" << std::endl;
    }
    else if (choice == 2) {
        player_Poison_Counter = 0;
        std::cout << "Your poison was cured!" << std::endl;
    }
    press_X_to_Continue();
}

void you_Have_Died() {
    system("cls");
    for (int i = 0; i < 50; i += 1) {
        std::cout << "YOU HAVE DIED" << std::endl;
    }
}

void victory() {
    system("cls");
    for (int i = 0; i < 50; i += 1) {
        std::cout << "VICTORY" << std::endl;
    }

}
//reseting block


void reset_Block() {

    if (aegis_Counter < player_Current_Block) {
        player_Current_Block -= player_Current_Block - aegis_Counter;
        aegis_Counter = player_Current_Block;
    }
    if (aegis_Counter == 0) {
        player_Current_Block = 0;
    }
    else if (player_Current_Block == 0) {
        aegis_Counter = 0;
    }

}
void reset_Enemy_Block() {
    current_Enemy_Block = 0;
}


//combat
int enemy_Stats::combat(int rarity) {
    cards_In_Draw = next_Slot;
    while (enemy_Health > 0) {
        if (player_Current_Health > 0) {

            card_Plays = max_Card_Plays;
            random_Enemy_Intention();
            draw_Cards(card_Draws);

            start_of_Turn_Statuses();
            std::cout << "------------Beginning of turn--------------" << std::endl << std::endl;
            is_Players_Turn = true;
            while (is_Players_Turn == true) {
                //as long as the player has more than 0 card plays combat will loop
                if (player_Current_Health > 0){
                    if (enemy_Health > 0) {

                        display_Enemy_Stats(enemy_Health, enemy_Max_Health, enemy_Name);
                        display_Player_Stats();
                        display_Statuses();
                        display_Piles();
                        display_Card_Plays();
                        enemy_Intention_Cout();
                        //generates the cards on screen
                        display_Cards_Drawn(card_Draws);
                        //figured out if the played card is valid
                        plays_Card();
                        //card actions like damage, block
                        card_Actions(card_Played_Holder);
                        system("cls");
                    }
                    else {
                        victory();
                        break;
                    }
                }
                else {
                    you_Have_Died();
                    return 1;
                }
            }
            shuffle_Remaining_Cards();

            end_of_Turn_Statuses();
            std::cout << "------------Enemy's turn--------------" << std::endl << std::endl;
            reset_Enemy_Block();
            enemy_Action();
            enemy_Action_Cout();
            reset_Block();

        }
        else {
            you_Have_Died();
            return 1;
        }
    }
    victory();
    press_X_to_Continue();
    encounter_Num += 1;
    end_Statuses();
    reset_Deck();
    card_Pack(next_Slot, rarity);
    return 0;
}


int main() {

    declare_Cards();


    //card_Pack(next_Slot, 1);
    declare_Player_Cards();
    //enemy_Stats(int max_Health, int health,  int damage, int enemy_Block, int burn, int poison, int buff, std::string name )
    enemy_Stats bandit = enemy_Stats(80, 80, 15, 15, 0, 0, 2, "Bandit");
    bandit.combat(0);

    enemy_Stats rogue = enemy_Stats(50, 50, 25, 10, 0, 2, 0, "Rogue");
    rogue.combat(0);

    enemy_Stats wyrmling = enemy_Stats(90, 90, 15, 18, 6, 0, 0, "Wyrmling");
    wyrmling.combat(0);

    heal_Or_Cure();

    enemy_Stats golem = enemy_Stats(170, 170, 5, 35, 0, 0, 5, "Golem");
    golem.combat(1);

    enemy_Stats drake = enemy_Stats(130, 130, 25, 18, 5, 0, 5, "Drake");
    drake.combat(1);

    enemy_Stats slime = enemy_Stats(200, 200, 0, 45, 5, 2, 0, "Alpha Slime");
    slime.combat(1);



    enemy_Stats troll = enemy_Stats(250, 250, 5, 30, 3, 0, 10, "Troll");
    troll.combat(2);

    enemy_Stats spider = enemy_Stats(210, 210, 35, 40, 0, 3, 4, "Grand Spider");
    spider.combat(2);

    enemy_Stats bandit_King = enemy_Stats(190, 190, 20, 50, 0, 3, 10, "Bandit King");
    bandit_King.combat(2);

    heal_Or_Cure();

    enemy_Stats demon = enemy_Stats(240, 240, 40, 20, 9, 0, 5, "Demon");
    demon.combat(3);

    enemy_Stats evil_Wizard = enemy_Stats(180, 180, 30, 20, 14, 7, 0, "Evil Wizard");
    evil_Wizard.combat(3);

    enemy_Stats stone_Monolith= enemy_Stats(400, 400, 1, 60, 0, 0, 5, "Stone Monolith");
    stone_Monolith.combat(3);

    //final boss
    enemy_Stats dragon = enemy_Stats(300, 300, 50, 50, 18, 0, 0, "Dragon");
    dragon.combat(-1);

    return 0;
}