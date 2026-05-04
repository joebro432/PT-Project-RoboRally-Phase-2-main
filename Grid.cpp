#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Belt.h"
#include "Player.h"
#include "GameState.h"
#include<iostream>
Grid::Grid(Input* pIn, Output* pOut) : pIn(pIn), pOut(pOut)
{
	// Allocate every Cell on the board (bottom-up so cell numbers are assigned correctly)
	for (int i = NumVerticalCells - 1; i >= 0; i--)
		for (int j = 0; j < NumHorizontalCells; j++)
			CellList[i][j] = new Cell(i, j);

	Clipboard = NULL;
	IsClipboardCut = false;
	CutSourcePosition = CellPosition();
}


// ========== Board Operations ==========


bool Grid::AddObjectToCell(GameObject* pNewObject)
{
	CellPosition pos = pNewObject->GetPosition();
	if (!pos.IsValidCell())// invalid cell position
	{
		return false;
	}
	
		if (pos.GetCellNum() == 1 || pos.GetCellNum() == 55)
		{
			return false;
		}// players start at cell 1, so we should not allow adding objects there; also, cell 55 is the end cell, so we should not allow adding objects ther
		GameObject* pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();// get the game object in the cell of the new object position
		if (pPrevObject) // cell already has an object
		{
			return false;
		}

		
			CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);// add the new object to the cell
			return true;
	
	
	//FIXED
}

void Grid::RemoveObjectFromCell(const CellPosition& pos)
{
	if (pos.IsValidCell())
	{
		// Note: deallocate the object here before NULLing if ownership requires it

		GameObject* pObj = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if (pObj!=nullptr) {
			delete pObj; 
			CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL); 
		}
		//FIXED
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
			GameObject* pObj = CellList[i][j]->GetGameObject(); // get the game object in the current cell
			Belt* pBelt = dynamic_cast<Belt*>(pObj);  //if the game object is a belt, pBelt will point to it; if not, pBelt will be NULL
			if (pBelt)
				return pBelt;
			//DONE
		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}


// ========== Setters / Getters ==========


Input* Grid::GetInput() const  { return pIn; }
Output* Grid::GetOutput() const { return pOut; }

void Grid::SetClipboard(GameObject* gameObject, bool isCut, const CellPosition& sourcePos) 
{ 
	Clipboard = gameObject;
	IsClipboardCut = isCut;
	CutSourcePosition = sourcePos;
}

GameObject* Grid::GetClipboard() const { return Clipboard; }

bool Grid::IsClipboardFromCut() const { return IsClipboardCut; }

CellPosition Grid::GetCutSourcePosition() const { return CutSourcePosition; }

void Grid::ClearClipboard()
{
	Clipboard = NULL;
	IsClipboardCut = false;
	CutSourcePosition = CellPosition();
}

Cell* Grid::GetStartCell() const
{
	// Players start at the bottom-left cell of the board
	return CellList[NumVerticalCells - 1][0];
}

Cell* Grid::GetCell(const CellPosition& pos) const
{
	if (!pos.IsValidCell()){
		return nullptr;
}
	return CellList[pos.VCell()][pos.HCell()];
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
		if (pState->GetEndGame() == true) {
			pOut->PrintMessage("Click new Game...");
			pOut->ClearCommandsBar();
			return;
		}
		if (pState->GetCurrentPlayer()->GetHealth() == 0) {
			pOut->PrintMessage("Player " + to_string(pState->GetCurrentPlayer()->getPlayerNum() + 1) + " wins! Click new game to start a new game!");
			pOut->ClearCommandsBar();
			return;
		}
		pOut->CreateCommandsBar(pState->GetCurrentPlayer()->GetSavedCommands(), pState->GetCurrentPlayer()->GetSavedCommandCount(),
			pState->GetCurrentPlayer()->GetAvailableCommands(), pState->GetCurrentPlayer()->GetAvailableCommandCount());

		// Note: UpdatePlayerCell() already redraws players step-by-step during Play mode.
		Player*currPlayer = pState->GetCurrentPlayer();
		//UpdatePlayerCell(currPlayer, );
	}
	
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}

void Grid::SaveAll(ofstream& OutFile) const
{
	for (int i = NumVerticalCells - 1; i >= 0; i--) //moving from the top row to the bottom row(saving the cells as drawn)
	{
		for (int j = 0; j < NumHorizontalCells; j++)//moving from the left cell to the right cell in the current row
		{
			if (CellList[i][j]->GetGameObject()) //save if only there is a game object in the cell
			{
				CellList[i][j]->GetGameObject()->Save(OutFile);
			}
		}
	}
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


bool Grid::GridHasFlag() const
{
	for (int i = 0; i < NumVerticalCells; i++)
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->HasFlag())
				return true;
		}
	return false;
}
bool Grid::GridHasAntenna() const
{
	for (int i = 0; i < NumVerticalCells; i++)
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->HasAntenna())
				return true;
		}
	return false;
}

GameObject* Grid::GetAntenna() const
{
	for (int i = 0; i < NumVerticalCells; i++)
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->HasAntenna())
				return CellList[i][j]->GetGameObject();
		}
	return nullptr;
}
