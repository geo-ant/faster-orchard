#include "game.hpp"
#include <cstdint>
#include <functional>
#include <random>
#include <thread>

/**
 * generate uniform random numbers in a thread safe fashion
 * see: https://stackoverflow.com/questions/21237905/how-do-i-generate-thread-safe-uniform-random-numbers?answertab=active#tab-top
*/
inline uint8_t get_uniform_random_number(uint8_t minimum, uint8_t maximum)
{
	using thread_id_hash = std::hash<std::thread::id>;
	static thread_local std::random_device rd;
	static thread_local auto seed = rd() + std::chrono::system_clock::now().time_since_epoch().count() + thread_id_hash()(std::this_thread::get_id());
	static thread_local std::mt19937 generator(seed);
	std::uniform_int_distribution<uint8_t> distribution(minimum,maximum);
	return distribution(generator);
}

DiceThrow throw_dice() noexcept{
	auto number = get_uniform_random_number(0,5);
  return static_cast<DiceThrow>(number);
}
