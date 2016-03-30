/*
 * Project: Tank Commander Panic
 * File: tankpiece.hpp
 * Author: Kurtis Jantzen
 * Description: Models a tank.
 */

#ifndef SERVER_TANKPIECE_HPP
#define SERVER_TANKPIECE_HPP

#include "solidpiece.hpp"
#include "gameplayer.hpp"
#include "../protocol/protocoldefs.hpp"

namespace game_model {

class TankPiece : public SolidPiece {
public:

    TankPiece(GamePlayer& commander, protocol::TankModel model);

    auto get_power() const noexcept { return model_power[static_cast<char>(model)]; }

    auto get_range() const noexcept { return model_range[static_cast<char>(model)]; }

    auto get_speed() const noexcept { return model_speed[static_cast<char>(model)]; }

    auto get_color() const noexcept { return commander.get_team_color(); }

    protocol::PieceType get_piece_type() const noexcept override;

private:
    //                                      commander, interceptor, eliminator, negotiator
    static constexpr int model_max_health[] = { 50,  30, 100,  20}; // hit points
    static constexpr int model_power[]      = { 30,  30,  80,  50}; // hit points
    static constexpr int model_range[]      = {  6,   6,   3,  12}; // tiles
    static constexpr int model_speed[]      = {  2,   4,   1,   1}; // tiles per second

    protocol::TankModel model;
    /* the model of the tank determines its gameplay characteristics */

    GamePlayer& commander;
    /* the GamePlayer that commands this tank */

};

}

#endif //SERVER_TANKPIECE_HPP
