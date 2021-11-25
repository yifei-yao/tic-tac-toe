#ifndef TIC_TAC_TOE_MOVE_H
#define TIC_TAC_TOE_MOVE_H

#include "cstdint"
#include "role.h"

namespace move {
  struct Move {
    int location;
    role::Role role;
  };

}

#endif //TIC_TAC_TOE_MOVE_H
