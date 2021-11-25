#ifndef TIC_TAC_TOE_GAME_H
#define TIC_TAC_TOE_GAME_H

#include "role.h"
#include "move.h"
#include "board.h"

namespace game {
  void MainGameLoop();

  role::Role AskPlayerRole();

  bool AskPlayAgain();

  bool IsGameEnded(const board::Board &, role::Role);

  move::Move AskPlayerMove(role::Role, const board::Board &);

  move::Move AskAIMove(role::Role, const board::Board &);


}


#endif //TIC_TAC_TOE_GAME_H
