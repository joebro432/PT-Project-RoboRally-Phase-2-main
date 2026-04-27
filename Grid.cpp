#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Belt.h"
#include "Player.h"
#include "GameState.h"

Grid::Grid(Input* pIn, Output* pOut) : pIn(pIn), pOut(pOut)
{
	// Allocate every Cell on the board (bottom-up so cell numbers are assigned correctly)
	for (int i = NumVerticalCells - 1; i >= 0; i--)
		for (int j = 0; j < NumHorizontalCells; j++)
			CellList[i][j] = new Cell(i, j);

	Clipboard = NULL;
}


// ========== Board Operations ==========


bool Grid::AddObjectToCell(GameObject* pNewObject)
{
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell())
	{
		GameObject* pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if (pPrevObject) // cell already has an object
			return false;

		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true;
	}
	return false;
}

void Grid::RemoveObjectFromCell(const CellPosition& pos)
{
	if (pos.IsValidCell())
	{
		// Note: deallocate the object here before NULLing if ownership requires it
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
	}
}

void Grid::UpdatePlayerCell(Player* player, const CellPosition& newPosition)
{
	player->ClearDrawing(pOut);
	Cell* newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);
	player->Draw(pOut);
}

Belt* Grid::GetNextBelt(const CellPosition& position)
{
	int startH = position.HCell(); // represents the start hCell in the current row to search for the belt in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			///TODO: Check if CellList[i][j] has a belt, if yes return it
		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}


// ========== Setters / Getters ==========


Input* Grid::GetInput() const  { return pIn; }
Output* Grid::GetOutput() const { return pOut; }

void Grid::SetClipboard(GameObject* gameObject) { Clipboard = gameObject; } // to be used in copy/cut
GameObject* Grid::GetClipboard() const          { return Clipboard; }       // to be used in paste

Cell* Grid::GetStartCell() const
{
	// Players start at the bottom-left cell of the board
	return CellList[NumVerticalCells - 1][0];
}


// ========== User Interface ==========


void Grid::UpdateInterface(const GameState* pState) const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw every cell (background colour, water pits, danger zones)
		for (int i = NumVerticalCells - 1; i >= 0; i--)
			for (int j = 0; j < NumHorizontalCells; j++)
				CellList[i][j]->DrawCellOrWaterPitOrDangerZone(pOut);

		// 2- Draw other game objects on top (belts, flags, gears, etc.)
		for (int i = NumVerticalCells - 1; i >= 0; i--)
			for (int j = 0; j < NumHorizontalCells; j++)
				CellList[i][j]->DrawGameObject(pOut);

		// 3- Draw all player tokens (delegated to GameState -- Grid does not own players)
		pState->DrawAllPlayers(pOut);
	}
	else // Play mode
	{
		// Print the players info bar on the right side of the toolbar.
		// GameState builds the string because it owns the player data.
		string playersInfo = "";
		pState->AppendPlayersInfo(playersInfo);
		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() already redraws players step-by-step during Play mode.
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}


Grid::~Grid()
{
	delete pIn;
	delete pOut;

	for (int i = NumVerticalCells - 1; i >= 0; i--)
		for (int j = 0; j < NumHorizontalCells; j++)
			delete CellList[i][j];

	// Players are owned by GameState -- do NOT delete them here.
}
