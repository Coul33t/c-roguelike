typedef struct SingleStat {
    char name[30];
    int max, val;
} SingleStat;

typedef struct Stats {
    SingleStat hp;
    SingleStat stamina;
    SingleStat mana;
    int dmg;
    int def;
    int xp;
    int xp_value;
} Stats;