#pragma once

#include <cstdint>

constexpr const uint8_t MAX_RAVENS = 9;
constexpr const uint8_t INITIAL_FRUITS = 10;

struct GameState {
  uint8_t ravens =  0;
  uint8_t fruits[4] = {INITIAL_FRUITS, INITIAL_FRUITS, INITIAL_FRUITS, INITIAL_FRUITS};
  bool is_won() const noexcept{
    return (ravens < MAX_RAVENS) && (fruits[0] + fruits[1] + fruits[2] + fruits[3]) == 0;
  }

  bool is_lost() const noexcept{
    return ravens >= MAX_RAVENS;
  }

  bool is_over() const noexcept{
    return ravens >= MAX_RAVENS || (fruits[0] + fruits[1] + fruits[2] + fruits[3]) == 0;
  }
};

enum DiceThrow : uint8_t{
  RED = 0,
  YELLOW = 1,
  GREEN = 2,
  BLUE = 3,
  BASKET = 4,
  RAVEN = 5
};

struct GameResult {
  bool won = false;
  uint8_t turns = 0;
};

DiceThrow throw_dice() noexcept;
uint8_t get_uniform_random_number(uint8_t minimum, uint8_t maximum);


template<typename S>
GameResult play_to_finish(GameState game, S strategy) noexcept{
  auto result = GameResult{};
  while (!game.is_over()) {
    auto dice = throw_dice();
    result.turns++;
    switch (dice) {
      case RED:
      case YELLOW:
      case GREEN:
      case BLUE:
        if (game.fruits[dice] > 0) {
          game.fruits[dice]--;
        }
        break;
      case BASKET:
        game = strategy(game);
      break;
      case RAVEN:
        game.ravens++;
        break;
    }
  }

  result.won = game.is_won();
  return result;
}

  
