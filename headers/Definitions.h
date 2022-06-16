//
// Created by Jakub Górski on 11/06/2022.
//

#ifndef BATTLESHIPS_GAME_DEFINITIONS_H
#define BATTLESHIPS_GAME_DEFINITIONS_H

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#define SCREEN_TITLE "sonho poor"
#define FPS 60
#define FRAME_DELAY (1000/FPS)

// Tilemap definitions

enum TEX {
    water = 0,
    gridtl = 1,
    gridt = 2,
    gridtr = 3,
    gridml = 4,
    gridm = 5,
    gridmr = 6,
    gridbl = 7,
    gridb = 8,
    gridbr = 9,
    sand = 10,
    sandtl = 11,
    sandt = 12,
    sandtr = 13,
    sandml = 14,
    sandmr = 15,
    sandbl = 16,
    sandb = 17,
    sandbr = 18
};

static int DEF_BG[15][25]{
        { TEX::sandtl, TEX::sandt, TEX::sandt, TEX::sandt, TEX::sandt, TEX::sandt, TEX::sandt, TEX::sandt, TEX::sandt, TEX::sandt, TEX::sandt, TEX::sandtr, TEX::sand, TEX::sandtl, TEX::sandt, TEX::sandt, TEX::sandt, TEX::sandt, TEX::sandt, TEX::sandt, TEX::sandt, TEX::sandt, TEX::sandt, TEX::sandt, TEX::sandtr},
        { TEX::sandml, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::sandmr, TEX::sand, TEX::sandml, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::sandmr},
        { TEX::sandml, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::sandmr, TEX::sand, TEX::sandml, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::sandmr},
        { TEX::sandml, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::sandmr, TEX::sand, TEX::sandml, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::sandmr},
        { TEX::sandml, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::sandmr, TEX::sand, TEX::sandml, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::sandmr},
        { TEX::sandml, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::sandmr, TEX::sand, TEX::sandml, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::sandmr},
        { TEX::sandml, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::sandmr, TEX::sand, TEX::sandml, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::sandmr},
        { TEX::sandml, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::sandmr, TEX::sand, TEX::sandml, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::sandmr},
        { TEX::sandml, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::sandmr, TEX::sand, TEX::sandml, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::sandmr},
        { TEX::sandml, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::sandmr, TEX::sand, TEX::sandml, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::sandmr},
        { TEX::sandml, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::sandmr, TEX::sand, TEX::sandml, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::water, TEX::sandmr},
        { TEX::sandbl, TEX::sandb, TEX::sandb, TEX::sandb, TEX::sandb, TEX::sandb, TEX::sandb, TEX::sandb, TEX::sandb, TEX::sandb, TEX::sandb, TEX::sandbr, TEX::sand, TEX::sandbl, TEX::sandb, TEX::sandb, TEX::sandb, TEX::sandb, TEX::sandb, TEX::sandb, TEX::sandb, TEX::sandb, TEX::sandb, TEX::sandb, TEX::sandbr},
        { TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand},
        { TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand},
        { TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand, TEX::sand}
};

static int DEF_GRID_L[15][25]{
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, TEX::gridtl, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridtr, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, TEX::gridbl, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridbr, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};

static int DEF_GRID_R[15][25]{
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, TEX::gridtl, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridtr, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, TEX::gridbl, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridbr, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};


#endif //BATTLESHIPS_GAME_DEFINITIONS_H
