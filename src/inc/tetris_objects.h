#ifndef BRICK_GAME_TETRIS_TETRIS_OBJECTS_H_
#define BRICK_GAME_TETRIS_TETRIS_OBJECTS_H_

typedef struct figure_s {
  int **shape;
  int id;
  int x;
  int y;
} figure_t;

typedef enum signals {
  START,
  PAUSE,
  TERMINATE,
  LEFT,
  RIGHT,
  UP,
  DOWN,
  ACTION,
} user_action_t;

typedef enum states {
  STARTED,
  PLAYING,
  STOPPED,
  QUIT,
  OVER,
} game_states_t;

typedef struct game_info_s{
  int ***shapes_list;
  int **field;
  int **next;
  int next_id;
  int score;
  int high_score;
  int level;
  int lines;
  int speed;
  game_states_t state;
  int ticks_left;
} game_info_t;

#endif  // BRICK_GAME_TETRIS_TETRIS_OBJECTS_H_
