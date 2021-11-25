#ifndef TIC_TAC_TOE_ROLE_H
#define TIC_TAC_TOE_ROLE_H

#include <cstdint>

namespace role {
  static constexpr bool kCross = true;
  static constexpr bool kNought = false;

  class Role {
    friend bool operator==(const Role &lhs, const Role &rhs);

  public:
    explicit Role(char);

    Role operator!() const;

    [[nodiscard]] bool GetType() const;

  private:
    explicit Role(bool repr);

    bool repr; // true for cross, false for nought
  };

  bool IsValidRole(char);


}
#endif //TIC_TAC_TOE_ROLE_H
