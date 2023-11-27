#include"Timer.h"
using namespace Goat2d::core;

void Timer::start()
{
	start_point = std::chrono::steady_clock::now();
}
void Timer::stop()
{
	end_point = std::chrono::steady_clock::now();
}
double Timer::get_elapsed_ticks()
{
	auto current_time = std::chrono::high_resolution_clock::now();
	auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_point);
	return diff.count();
}