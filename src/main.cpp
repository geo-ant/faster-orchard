#include <iostream>
#include "game.hpp"
#include "strategies.hpp"

int main() {
  using std::cout;
  
  const auto NGAMES = 100000;

  uint32_t total_turns = 0;
  uint32_t total_wins = 0;

  for (auto i = 0; i < NGAMES; i++) {
    auto result = play_to_finish(GameState{}, pick_from_fullest);
    total_turns += result.turns;
    if (result.won) {
      total_wins++;
    }
  }

  cout << "Total games: " << NGAMES << "\n";
  cout << "Total turns: " << total_turns << "\n";
  cout << "Total wins: " << total_wins << "\n";
  return 0;
}
