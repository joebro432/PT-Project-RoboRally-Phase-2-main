#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition()
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;
}

CellPosition::CellPosition(int v, int h)
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition(int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
											   // from the passed (cellNum)
											   // (*this) = ... --> this will copy the returned (vCell and hCell)
											   //                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v)
{
	///TODO: Implement this function as described in the .h file (don't forget the validation)
	///TODO: Implement this function as described in the .h file (don't forget the validation)
	if (v >= 0 && v < NumVerticalCells) {
		vCell = v;
		return true;
	}
	return false; // this line sould be changed with your implementation


}

bool CellPosition::SetHCell(int h)
{
	if (h >= 0 && h < NumHorizontalCells) {
		hCell = h;
		return true;
	}
	///TODO: Implement this function as described in the .h file (don't forget the validation)

	return false; // this line sould be changed with your implementation
}

int CellPosition::VCell() const
{
	return vCell;
}

int CellPosition::HCell() const
{
	return hCell;
}

bool CellPosition::IsValidCell() const
{
	if (vCell >= 0 && vCell < NumVerticalCells && hCell >= 0 && hCell < NumHorizontalCells)
	{
		return true;
	}	///TODO: Implement this function as described in the .h file

	return false; // this line sould be changed with your implementation
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
										  // which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition & cellPosition)
{

	if (!cellPosition.IsValidCell()) { return -1; }
	return(NumVerticalCells - cellPosition.VCell() - 1) * NumHorizontalCells + (cellPosition.HCell() + 1);
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;
	if (cellNum < 1 || cellNum > NumVerticalCells * NumHorizontalCells) {
		return position; // invalid (-1,-1)
	}

	int v = NumVerticalCells - ((cellNum - 1) / NumHorizontalCells) - 1;
	int h = (cellNum - 1) % NumHorizontalCells;

	position.SetVCell(v);
	position.SetHCell(h);
	/// TODO: Implement this function as described in the .h file

	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it


	return position;
}

void CellPosition::AddCellNum(int addedNum, Direction direction)
{

	int cellNum = GetCellNum();
	if (cellNum == -1) return;
	switch (direction) {
	case UP:
		cellNum += addedNum * NumHorizontalCells;
		break;
	case DOWN:
		cellNum -= addedNum * NumHorizontalCells;
		break;
	case LEFT:
		cellNum -= addedNum;
		break;
	case RIGHT:
		cellNum += addedNum;
		break;
	}
	if (cellNum < 1 || cellNum > NumVerticalCells * NumHorizontalCells) {
		vCell = -1;
		hCell = -1;
		return;
	}
	*this = GetCellPositionFromNum(cellNum);

}