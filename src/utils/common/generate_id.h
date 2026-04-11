#include <string>
#include <chrono>
#include <atomic>
#include <random>
#include <algorithm>

const std::string BASE36 = "0123456789abcdefghijklmnopqrstuvwxyz";

std::string toBase36(uint64_t num){
    if (num == 0) return "0";
    std::string result;
    while(num > 0){
        result += BASE36[num % 36];
        num /= 36;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

static std::atomic<uint32_t> counter(0);

// thread-local RNG 
thread_local std::mt19937 rng(std::random_device{}());

uint32_t fastRandom(){
    return rng();
}

std::string generateId(){
    uint64_t timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();

    uint32_t count = counter.fetch_add(1, std::memory_order_relaxed);

    uint32_t rnd = fastRandom();

    return toBase36(timestamp) +
           toBase36(count) +
           toBase36(rnd).substr(0, 4) + "_";
}