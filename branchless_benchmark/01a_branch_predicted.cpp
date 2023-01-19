#include <benchmark/benchmark.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <random>

static void BM_01a_branch_predicted(benchmark::State& state) {
  static constexpr int kDefaultSeed{1};
  std::mt19937 gen(kDefaultSeed);  // repeatable results
  std::uniform_int_distribution<> distribution{};
  auto const N = static_cast<size_t>(state.range(0));
  std::vector<int64_t> v1(static_cast<size_t>(N)), v2(static_cast<size_t>(N));
  std::vector<int> c1(static_cast<size_t>(N));
  for (size_t i = 0; i < N; ++i) {
    v1[i] = distribution(gen);
    v2[i] = distribution(gen);
    c1[i] = distribution(gen) >= 0;
  }
  auto* p1 = v1.data();
  auto* p2 = v2.data();
  int* b1 = c1.data();
  for (auto _ : state) {
    int64_t a1 = 0;
    int64_t a2 = 0;
    for (size_t i = 0; i < N; ++i) {
      if (b1[i]) {    // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        a1 += p1[i];  // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
      } else {
        a1 *= p2[i];  // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
      }
    }
    benchmark::DoNotOptimize(a1);
    benchmark::DoNotOptimize(a2);
    benchmark::ClobberMemory();
  }
  state.SetItemsProcessed(static_cast<int64_t>(N) * state.iterations());
}

// clang-format off
static constexpr int SHIFT_FACTOR{22};
BENCHMARK(BM_01a_branch_predicted)->Arg(1 << SHIFT_FACTOR);  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory,clang-diagnostic-global-constructors)
// clang-format on
