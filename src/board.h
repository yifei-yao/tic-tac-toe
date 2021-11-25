#ifndef TIC_TAC_TOE_BOARD_H
#define TIC_TAC_TOE_BOARD_H

#include <cstdint>
#include <array>
#include <ostream>
#include "move.h"


namespace board {

  struct Result {

    static constexpr int max = std::numeric_limits<int>::max();
    static constexpr int min = std::numeric_limits<int>::min();
    static constexpr int draw = 0;

    bool is_ended;
    int val;
  };

  class Board {
    friend std::ostream &operator<<(std::ostream &os, const Board &board);

  public:
    Board();

    [[nodiscard]] Result GetResult(role::Role role) const;

    Board(const Board &, move::Move);

    void ApplyMove(move::Move);

    [[nodiscard]] bool IsEmptyAt(int address) const;

  private:
    [[nodiscard]] char GetChar(int address) const;

    static bool Matched(int, role::Role);

    static constexpr int kEmpty = 0;
    static constexpr int kCross = 1;
    static constexpr int kNought = 2;

    std::array<int, 9> repr{};
  };

}
#endif //TIC_TAC_TOE_BOARD_H
