#include "strategies.hpp"
#include "game.hpp"
#include <cstdint>
#include <tuple>

std::tuple<uint8_t,uint8_t> max_idx(GameState game) {
  uint8_t max = game.fruits[0];
  uint8_t idx = 0;
  for (uint8_t i = 1; i < 4; i++) {
    if (game.fruits[i] > max) {
      max = game.fruits[i];
      idx = i;
    }
  }
  return std::make_tuple(max, idx);
}


//@todo this seems to have a bug, but maybe my calculations were wrong
GameState pick_from_fullest(GameState game) {
   auto [max, idx] = max_idx(game); 
   if (max > 0) {
     game.fruits[idx]--;
     auto [max, idx] = max_idx(game);
     if (max > 0) {
       game.fruits[idx]--;
     }
   }
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
