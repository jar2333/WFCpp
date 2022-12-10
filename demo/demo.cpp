/*******************************************************************************************
*
*   raylib [textures] example - Texture loading and drawing
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
#include <iostream>

#include "raylib/src/raylib.h"

#include <Solver.h> 
#include <Synthesizer.h>

#include <BMPImage.h>
#include <Tile.h>

#include <Direction.h>

template <typename T>
void print(T a, std::string container) {
    std::cout << container << ": ";
    for (auto k : a) {
        std::cout << k << ", ";
    }
    std::cout << std::endl;
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main() {

    auto corner  = std::make_shared<BMPImage>("./tilesets/Knots/corner.png");
    auto corner2 = std::make_shared<BMPImage>("./tilesets/Knots/corner2.png");
    auto corner3 = std::make_shared<BMPImage>("./tilesets/Knots/corner3.png");
    auto corner4 = std::make_shared<BMPImage>("./tilesets/Knots/corner4.png");

    auto cross  = std::make_shared<BMPImage>("./tilesets/Knots/cross.png");
    auto cross2 = std::make_shared<BMPImage>("./tilesets/Knots/cross2.png");

    auto line  = std::make_shared<BMPImage>("./tilesets/Knots/line.png");
    auto line2 = std::make_shared<BMPImage>("./tilesets/Knots/line2.png");

    auto empty = std::make_shared<BMPImage>("./tilesets/Knots/empty.png");

    std::map<Solver::TileKey, std::shared_ptr<Tile>> tileMap {
        {1, std::make_shared<Tile>(corner)},
        {2, std::make_shared<Tile>(corner2)},
        {3, std::make_shared<Tile>(corner3)},
        {4, std::make_shared<Tile>(corner4)},
        {5, std::make_shared<Tile>(cross)},
        {6, std::make_shared<Tile>(cross2)},
        {7, std::make_shared<Tile>(empty)},
        {8, std::make_shared<Tile>(line)},
        {9, std::make_shared<Tile>(line2)}
    };

    SolverGrid grid(3, tileMap);

    int s;
    std::cout << "Seed: ";
    std::cin >> s;

    Solver solver(tileMap, s);

    solver.addAdjacencyConstraint(1, Direction::RIGHT, {3,4, 5,6, 8});
    solver.addAdjacencyConstraint(1, Direction::LEFT,  {3,4, 7, 9});
    solver.addAdjacencyConstraint(1, Direction::UP,    {2,3, 5,6, 9});
    solver.addAdjacencyConstraint(1, Direction::DOWN,  {2,3, 7, 8});

    solver.addAdjacencyConstraint(2, Direction::RIGHT, {3,4, 5,6, 8});
    solver.addAdjacencyConstraint(2, Direction::LEFT,  {3,4, 7, 9});
    solver.addAdjacencyConstraint(2, Direction::UP,    {1,4, 7, 8});
    solver.addAdjacencyConstraint(2, Direction::DOWN,  {1,4, 5,6, 9});

    solver.addAdjacencyConstraint(3, Direction::RIGHT, {1,2, 7, 9});
    solver.addAdjacencyConstraint(3, Direction::LEFT,  {1,2, 5,6, 8});
    solver.addAdjacencyConstraint(3, Direction::UP,    {1,4, 7, 8});
    solver.addAdjacencyConstraint(3, Direction::DOWN,  {1,4, 5,6, 9});

    solver.addAdjacencyConstraint(4, Direction::RIGHT, {1,2, 7, 9});
    solver.addAdjacencyConstraint(4, Direction::LEFT,  {1,2, 5,6, 8});
    solver.addAdjacencyConstraint(4, Direction::UP,    {2,3, 5,6, 9});
    solver.addAdjacencyConstraint(4, Direction::DOWN,  {2,3, 7, 8});

    solver.addAdjacencyConstraint(5, Direction::RIGHT, {3,4, 5,6, 8});
    solver.addAdjacencyConstraint(5, Direction::LEFT,  {1,2, 5,6, 8});
    solver.addAdjacencyConstraint(5, Direction::UP,    {2,3, 5,6, 9});
    solver.addAdjacencyConstraint(5, Direction::DOWN,  {1,4, 5,6, 9});

    solver.addAdjacencyConstraint(6, Direction::RIGHT, {3,4, 5,6, 8});
    solver.addAdjacencyConstraint(6, Direction::LEFT,  {1,2, 5,6, 8});
    solver.addAdjacencyConstraint(6, Direction::UP,    {2,3, 5,6, 9});
    solver.addAdjacencyConstraint(6, Direction::DOWN,  {1,4, 5,6, 9});

    solver.addAdjacencyConstraint(7, Direction::RIGHT, {1,2, 9, 7});
    solver.addAdjacencyConstraint(7, Direction::LEFT,  {3,4, 9, 7});
    solver.addAdjacencyConstraint(7, Direction::UP,    {1,4, 8, 7});
    solver.addAdjacencyConstraint(7, Direction::DOWN,  {2,3, 8, 7});

    solver.addAdjacencyConstraint(8, Direction::RIGHT, {3,4, 5,6, 8});
    solver.addAdjacencyConstraint(8, Direction::LEFT,  {1,2, 5,6, 8});
    solver.addAdjacencyConstraint(8, Direction::UP,    {1,4, 7, 8});
    solver.addAdjacencyConstraint(8, Direction::DOWN,  {2,3, 7, 8});
    
    solver.addAdjacencyConstraint(9, Direction::RIGHT, {1,2, 7, 9});
    solver.addAdjacencyConstraint(9, Direction::LEFT,  {3,4, 7, 9});
    solver.addAdjacencyConstraint(9, Direction::UP,    {2,3, 5,6, 9});
    solver.addAdjacencyConstraint(9, Direction::DOWN,  {1,4, 5,6, 9});

    solver.registerOnCollapse([](const auto& k, Position p){
        auto [i, j] = p;
        std::cout << "Collapse! at Position: (" << i << ", " << j << "), tile: " << k << std::endl;
    });

    solver.registerOnPropagate([](const auto& k, Position p){
        auto [i, j] = p;
        std::cout << "Propagate! at Position: (" << i << ", " << j << "), ";
        print(k, "tiles: ");
    });

    solver.solve(3, grid);

    Synthesizer synthesizer;

    synthesizer.exportGridToFile(grid, "export.png", FileType::png);


    // // Initialization
    // //--------------------------------------------------------------------------------------
    // const int screenWidth = 800;
    // const int screenHeight = 450;

    // InitWindow(screenWidth, screenHeight, "raylib [textures] example - texture loading and drawing");

    // // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    // Texture2D texture = LoadTexture("resources/raylib_logo.png");        // Texture loading
    // //---------------------------------------------------------------------------------------

    // // Main game loop
    // while (!WindowShouldClose())    // Detect window close button or ESC key
    // {
    //     // Update
    //     //----------------------------------------------------------------------------------
    //     // TODO: Update your variables here
    //     //----------------------------------------------------------------------------------

    //     // Draw
    //     //----------------------------------------------------------------------------------
    //     BeginDrawing();

    //         ClearBackground(RAYWHITE);

    //         DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2, WHITE);

    //         DrawText("this IS a texture!", 360, 370, 10, GRAY);

    //     EndDrawing();
    //     //----------------------------------------------------------------------------------
    // }

    // // De-Initialization
    // //--------------------------------------------------------------------------------------
    // UnloadTexture(texture);       // Texture unloading

    // CloseWindow();                // Close window and OpenGL context
    // //--------------------------------------------------------------------------------------

    return 0;
}