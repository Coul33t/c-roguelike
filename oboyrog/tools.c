#include "tools.h"

int get_1d_idx_from_2d_coord(int x, int y, int w) {
    return (x * w) + y;
}