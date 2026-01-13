/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include <vector>

const int screenWidth = 800;
const int screenHeight = 800;

const int gridWidth = 100;
const int gridHeight = 100;

const float cellWidth = (float)screenWidth / gridWidth;
const float cellHeight = (float)screenHeight / gridHeight;

using Cells = std::vector<bool>;

bool ReadCell(int x, int y, const Cells& cells)
{
	if (x < 0) x = gridWidth - 1;
	else if (x > gridWidth - 1) x = 0;

	if (y < 0) y = gridHeight - 1;
	else if (y > gridHeight - 1) y = 0;

	return cells[x + (y * gridWidth)];
}

void WriteCell(int x, int y, bool write, Cells& cells)
{
	if (x < 0) x = gridWidth - 1;
	else if (x > gridWidth - 1) x = 0;

	if (y < 0) y = gridHeight - 1;
	else if (y > gridHeight - 1) y = 0;

	cells[x + (y * gridWidth)] = write;
}

void RandomizeCells(Cells& cells)
{
	for (auto& cell : cells)
	{
		cell = GetRandomValue(0, 1);
	}
}

int CountLiveNeighbors(int x, int y, const Cells& cells)
{
	int neighbors = 0;

	if (ReadCell(x - 1, y - 1, cells)) neighbors++;
	if (ReadCell(x + 0, y - 1, cells)) neighbors++;
	if (ReadCell(x + 1, y - 1, cells)) neighbors++;
	if (ReadCell(x - 1, y + 0, cells)) neighbors++;
	if (ReadCell(x + 1, y + 0, cells)) neighbors++;
	if (ReadCell(x - 1, y + 1, cells)) neighbors++;
	if (ReadCell(x + 0, y + 1, cells)) neighbors++;
	if (ReadCell(x + 1, y + 1, cells)) neighbors++;

	return neighbors;
}

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(screenWidth, screenHeight, "Game Of Life");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	
	Cells currentGeneration(gridWidth * gridHeight);
	Cells nextGeneration(gridWidth * gridHeight);

	RandomizeCells(currentGeneration);

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		std::fill(nextGeneration.begin(), nextGeneration.end(), false);

		if (IsKeyDown(KEY_SPACE)) RandomizeCells(currentGeneration);
		
		// Set next generation from current states
		for (int y = 0; y < gridHeight; y++)
		{
			for (int x = 0; x < gridWidth; x++)
			{
				int count = CountLiveNeighbors(x, y, currentGeneration);
				bool isAlive = ReadCell(x, y, currentGeneration);

				// Conway's Game of Life rules:
				// 1. Live cell with 2-3 neighbors survives
				// 2. Dead cell with exactly 3 neighbors becomes alive
				// 3. All other cells die or stay dead

				if (isAlive)
				{
					// Set next generation to true if stays alive
					if (count == 2 || count == 3) WriteCell(x, y, true, nextGeneration);
				}
				else
				{
					if (count == 3) WriteCell(x, y, true, nextGeneration);
				}
			}
		}

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// Draw Cells
		for (int y = 0; y < gridHeight; y++)
		{
			for (int x = 0; x < gridWidth; x++)
			{
				if (ReadCell(x, y, currentGeneration)) DrawRectangle((int)x * cellWidth, (int)y * cellHeight, cellWidth, cellHeight, WHITE);
			}
		}

		DrawText("Space: Randomize", 20, 10, 20, WHITE);
		DrawFPS(20, 30);

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
		currentGeneration = nextGeneration;
	}

	// cleanup

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
