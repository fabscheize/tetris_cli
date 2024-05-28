#ifndef BRICK_GAME_TETRIS_TETRIS_H_
#define BRICK_GAME_TETRIS_TETRIS_H_

#include "../../gui/cli/cli_frontend.h"

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();

#endif  // BRICK_GAME_TETRIS_TETRIS_H_
