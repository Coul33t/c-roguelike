#include "stats.h"

Job get_mercenary() {
    Job job;
    strcpy(job.name, "Mercenary");
    StatGrowth growth;
    growth.str_g = 1;
    growth.agi_g = 1;
    growth.inte_g = 0;

    job.stats_g = growth;
    return job;
}