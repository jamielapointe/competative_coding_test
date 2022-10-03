#include <iostream>
#include <memory>
#include <vector>

using std::vector;

class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    auto buy_it{prices.begin()};
    auto sell_it{buy_it};
    auto curr_it{buy_it + 1};
    auto sell_price{0};
    int  tmp_sell{0};

    while (curr_it != prices.end()) {
      if (*curr_it < *buy_it) {
        buy_it  = curr_it;
        sell_it = curr_it;
      } else if (*curr_it > *sell_it) {
        sell_it = curr_it;
      }
      tmp_sell = *sell_it - *buy_it;
      if (tmp_sell > sell_price) {
        sell_price = tmp_sell;
      }
      ++curr_it;
    }

    return sell_price;
  }
};

int main() {
  std::unique_ptr<Solution> solution = std::make_unique<Solution>();
  vector<int>               prices{7, 1, 5, 3, 6, 4};  // NOLINT ignore "magic" numbers
  auto                      my_answer = solution->maxProfit(prices);
  static constexpr int      expected_answer{5};
  if (my_answer != expected_answer) {
    std::cout << "WRONG; "
              << "expected answer = " << expected_answer << ", my answer: " << my_answer << std::endl;
  } else {
    std::cout << "Correct!" << std::endl;
  }
  return 0;
}
