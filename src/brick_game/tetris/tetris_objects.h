#ifndef BRICK_GAME_TETRIS_TETRIS_OBJECTS_H_
#define BRICK_GAME_TETRIS_TETRIS_OBJECTS_H_

typedef struct figure_s {
  int shape;
  int x;
  int y;
} figure_t;

typedef enum {
  START,
  PAUSE,
  TERMINATE,
  LEFT,
  RIGHT,
  UP,
  DOWN,
  ACTION,
} user_action_t;

typedef struct game_info_s{
  int **field;
  int (*next)[2];
  int score;
  int high_score;
  int level;
  int lines;
  int speed;
  int pause;
} game_info_t;

#endif  // BRICK_GAME_TETRIS_TETRIS_OBJECTS_H_
