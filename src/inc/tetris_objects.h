#ifndef TETRIS_OBJECTS_H_
#define TETRIS_OBJECTS_H_

#include <time.h>

typedef struct figure_s {
  int **shape;
  int id;
  int x;
  int y;
} figure_t;

enum shapes { O = 0, I, S, Z, T, L, J };

enum colors {
  O_COLOR = 1,
  I_COLOR,
  S_COLOR,
  Z_COLOR,
  T_COLOR,
  L_COLOR,
  J_COLOR,
  NO_COLOR
};

typedef enum signals {
  NOTHING,
  START,
  PAUSE,
  QUIT,
  LEFT,
  RIGHT,
  UP,
  DOWN,
  ACTION,
  YES,
  NO
} user_action_t;

typedef enum states {
  STARTED,
  PLAYING,
  PAUSED,
  STOPPED,
  TERMINATED,
  OVER,
} game_states_t;

typedef struct game_info_s {
  int ***shapes_list;
  int **field;
  int **next;
  int next_id;
  int score;
  int high_score;
  int level;
  int lines;
  long speed;
  game_states_t state;
  struct timespec start;
} game_info_t;

#endif  // TETRIS_OBJECTS_H_
