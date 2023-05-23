#include "strategies.hpp"
#include "game.hpp"
#include <cstdint>


//@todo this seems to have a bug, but maybe my calculations were wrong
GameState pick_from_fullest(GameState game) {
  uint8_t max = game.fruits[0];
  uint8_t max_index = 0;
  uint8_t second_max = game.fruits[1];
  uint8_t second_max_index = 1;
  for (uint8_t i = 0; i < 4; i++) {
    if (game.fruits[i] > max) {
      second_max = max;
      second_max_index = max_index;
      max = game.fruits[i];
      max_index = i;
    }
  }
  
  if (max-second_max >= 2) {
    game.fruits[max_index]-=2;
  } else if (max>0 && second_max>0) {
    game.fruits[max_index]--;
    game.fruits[second_max_index]--;
  } else if (max>0) {
    game.fruits[max_index]--;
  } else {}

  return game;
}

GameState pick_in_order(GameState game) {
  for(int j = 0; j < 2; ++j) { 
    for (uint8_t i = 0; i < 4; i++) {
      if (game.fruits[i] > 0) {
        game.fruits[i]--;
        break;
      }
    }
  }
  return game;
}
