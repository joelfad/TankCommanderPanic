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

protocol::TankModel protocol::tank_model(PieceType type) {
    return static_cast<TankModel>((static_cast<int>(type) - 16) % 4);
}

constexpr int game_model::TankPiece::model_max_health[];
constexpr int game_model::TankPiece::model_power[];
constexpr int game_model::TankPiece::model_range[];
constexpr int game_model::TankPiece::model_speed[];
