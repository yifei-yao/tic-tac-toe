#include "role.h"
#include <set>
#include <iostream>

namespace role {
  bool IsValidRole(char input) {
    static const std::set<char> kValidChars = {'o', 'O', 'x', 'X'};
    if (kValidChars.find(input) != kValidChars.end()) {
      return true;
    } else {
      return false;
    }
  }

  Role::Role(char input) {
    switch (input) {
      case 'o':
      case 'O':
        repr = kNought;
        return;
      case 'x':
      case 'X':
        repr = kCross;
        return;
      default:
        std::cerr << "Invalid char input for Role!\n";
        repr = kNought;
        return;
    }

  }

  Role Role::operator!() const {
    return Role(!repr);
  }

  Role::Role(bool repr) : repr(repr) {}

  [[nodiscard]] bool Role::GetType() const {
    return repr;
  }

  bool operator==(const Role &lhs, const Role &rhs) {
    return lhs.repr == rhs.repr;
  }
}