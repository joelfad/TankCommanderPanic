/*
 * Project: Tank Commander Panic
 * File: tankpiece.cpp
 * Author: Kurtis Jantzen
 * Description: Models a tank.
 */

#include "tankpiece.hpp"

game_model::TankPiece::TankPiece(GamePlayer& commander, protocol::TankModel model) : commander(commander), model(model) {
    set_max_health(TankPiece::model_max_health[static_cast<char>(model)]);
}

protocol::PieceType game_model::TankPiece::get_piece_type() const noexcept {
    return protocol::tank_type(this->get_color(), this->model);
}

protocol::PieceType protocol::tank_type(TeamColor color, TankModel model) {
    return static_cast<protocol::PieceType>(
            static_cast<protocol::ServerMsgType>(16) +
            static_cast<protocol::ServerMsgType>(color) +
            static_cast<protocol::ServerMsgType>(model)
    );
}

constexpr int game_model::TankPiece::model_max_health[];
