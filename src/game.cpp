#include "game.h"
#include "role.h"
#include "board.h"
#include "minimax.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

namespace game {
  void MainGameLoop() {
    do {
      const role::Role player_role = AskPlayerRole();
      const role::Role ai_role = !player_role;
      role::Role turn('x');
      board::Board game_board;
      std::cout << game_board << "\n";
      do {
        if (turn == player_role) {
          move::Move move = AskPlayerMove(player_role, game_board);
          game_board.ApplyMove(move);
        } else {
          move::Move move = AskAIMove(ai_role, game_board);
          game_board.ApplyMove(move);
        }
        turn = !turn;
        std::cout << game_board << "\n\n";
      } while (!IsGameEnded(game_board, player_role));
    } while (AskPlayAgain());
  }

  role::Role AskPlayerRole() {
    while (true) {
      std::cout << "You play 'X' or 'O'?\n";
      std::string input;
      std::cin >> input;
      if (role::IsValidRole(input[0])) {
        return role::Role(input[0]);
      }
      std::cout << "Illegal input. Please try again.\n";
    }
  }

  bool AskPlayAgain() {
    while (true) {
      std::cout << "Play again? (y/n)\n";
      char input;
      std::cin >> input;
      switch (input) {
        case 'y':
        case 'Y':
          return true;
        case 'n':
        case 'N':
          return false;
        default:
          std::cout << "I'll take that as a NO.\n";
          return false;
      }
    }
  }

  bool IsGameEnded(const board::Board &board, role::Role role) {
    board::Result result = board.GetResult(role);
    if (!result.is_ended) {
      return false;
    } else {
      std::cout << "Game Over\n";
      if (result.val == board::Result::draw) {
        std::cout << "DRAW!\n";
      } else if (result.val == board::Result::min) {
        std::cout << "You LOST!\n";
      } else {
        std::cout << "You WON!\n";
      }
      return true;
    }
  }

  move::Move AskPlayerMove(role::Role role, const board::Board &board) {
    int location;
    do {
      int row;
      do {
        std::cout << "Row number (1-3):\n";
        std::string input;
        std::cin >> input;
        std::stringstream ss(input);
        int number;
        if ((ss >> number).fail()) {
          continue;
        }
        row = number;
      } while (row < 1 || row > 3);
      int col;
      do {
        std::cout << "Column number (1-3):\n";
        std::string input;
        std::cin >> input;
        std::stringstream ss(input);
        int number;
        if ((ss >> number).fail()) {
          continue;
        }
        col = number;
      } while (col < 1 || col > 3);
      location = (row - 1) * 3 + col - 1;
    } while (!board.IsEmptyAt(location));
    return {location, role};
  }

  move::Move AskAIMove(role::Role role, const board::Board &board) {
    std::vector<minimax::Minimax> children;
    for (int i = 0; i < 9; ++i) {
      if (board.IsEmptyAt(i)) {
        children.push_back({board, {i, role}, true, role});
      }
    }
    int maximum = std::numeric_limits<int>::min();
    move::Move *pmove = nullptr;
    for (minimax::Minimax child: children) {
      if (int val = child.GetVal(); val >= maximum) {
        maximum = val;
        delete pmove;
        pmove = new move::Move(child.GetMove());
      }
    }
    move::Move move = *pmove;
    delete pmove;
    return move;
  }
}
