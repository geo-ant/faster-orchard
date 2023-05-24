#include <cstddef>
#include <cstdint>
#include <iostream>
#include "game.hpp"
#include "strategies.hpp"
#include <thread>
#include <future>
#include <vector>
#include <latch>
#include <new>

struct AccumulatedResult {
  uint32_t total_turns = 0;
  uint32_t total_won = 0;
};

/* struct RandomNumbersUint8 { */
/*   alignas(std::hardware_destructive_interference_size) size_t count; */
/*   size_t current; */
/*   // I don't care about freeing this mem in this program */
/*   // and let the OS do it when the program exits */
/*   // hence no smart pointers */
/*   uint8_t* numbers; */
/* }; */

//split number as evenly as possible into num_chunks
std::vector<size_t> split_num(size_t num, size_t num_chunks);

AccumulatedResult simulate(size_t num_games,std::latch& latch);

int main() {
  using std::cout;
  
  const auto NGAMES = 1000000;

  uint32_t total_turns = 0;
  uint32_t total_wins = 0;

  auto thread_count = 1;//std::thread::hardware_concurrency();
  cout << "Thread count: " << thread_count << "\n";
  
  auto latch = std::latch{thread_count};

  std::vector<std::future<AccumulatedResult>> result_futures{};
  auto sizes  = split_num(NGAMES, thread_count);

  for (auto i = 0; i < thread_count; ++i) {
    result_futures.push_back(std::async(std::launch::async, simulate, sizes[i], std::ref(latch)));
  }

  latch.wait();  

  auto result = AccumulatedResult{};
  for (auto& future : result_futures) {
    auto acc = future.get();
    result.total_turns += acc.total_turns;
    result.total_won += acc.total_won;
  }

  cout << "Total games: " << NGAMES << "\n";
  cout << "Total turns: " << result.total_turns << "\n";
  cout << "Total wins: " << result.total_won << "\n";
  return 0;
}


inline AccumulatedResult simulate(size_t num_games,std::latch& latch) {
  auto acc = AccumulatedResult{}; 
  for (size_t j = 0; j< num_games; j++) {
    auto result = play_to_finish(GameState{}, pick_from_fullest);
    acc.total_turns += result.turns;
    if (result.won) {
      acc.total_won++;
    }
  }
  latch.count_down();
  return acc;
}

std::vector<size_t> split_num(size_t num, size_t num_chunks) {
  auto part_size = num / num_chunks;
  auto remainder = num % num_chunks;
  auto result = std::vector<size_t>(num_chunks, part_size);
  for (;remainder > 0; --remainder) {
    result[remainder - 1]++;
  }
  return result;
}
