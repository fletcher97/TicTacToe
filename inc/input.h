#if !defined(INPUT_H)
#define INPUT_H

#include "board.h"

typedef int (*getInputFunc)(char player, int i, int quad, board_t *game);

int playerInput(char player, int i, int quad, board_t *game);
int firstInput(char player, int i, int quad, board_t *game);
int nextInput(char player, int i, int quad, board_t *game);

int getInput(char player, int i, int quad, board_t *game);

void setInoutFunction1 (getInputFunc f);
void setInoutFunction2 (getInputFunc f);

#endif // INPUT_H
