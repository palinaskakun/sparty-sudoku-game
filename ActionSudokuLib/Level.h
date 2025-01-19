/**
 * @file Level.h
 * @author Team Syceus
 *
 * A class that has all of the items for a level
 */

#ifndef PROJECT1_ACTIONSUDOKULIB_LEVEL_H
#define PROJECT1_ACTIONSUDOKULIB_LEVEL_H

#include "Sparty.h"

#include <vector>

#include <map>

/**
 * A class that has all of the items for a level
 */
class Level
{
private:
	///a 9x9 vector of ints with all zeros for game solution
	std::vector<std::vector<int>> mSolutionMatrix;

	/// The main collection of pointers to the declarations.
	std::vector<std::shared_ptr<Item>> mDeclarations;

	/// The main collection of pointers to the items.
	std::vector<std::shared_ptr<Item>> mItems;

	/// Map of id to declarations
	std::map<std::string, std::shared_ptr<Item>> mIdItemMap;

	/// Height
	int mHeight = 0;
	/// Width
	int mWidth = 0;
	/// Tile width
	int mTileWidth = 0;
	/// Tile Height
	int mTileHeight = 0;
	/// File name
	std::string mLevelFileName;

	///Size with height and width that is passed to Game
	wxSize mGameSize;

	///Solution starts at column
	int mSolCol = 0;
	///Solution starts at row
	int mSolRow = 0;

    bool CellMatchesSolution(int row, int col, Item* item);

    //void MoveDigitTo(Item *digit, int targetRow, int targetCol);
    ///loading the first digit from Game Tag 
    int firstDigitFromGameTag;
    /**
     * Getting the container the digits are going to be in
     * @return
     */
    Container* getContainerToBeIn();
    /**
     * Getting sparty in items
     * @return
     */
    Sparty* GetSpartyInItems();
public:
	Level() {};
	Level(const std::wstring &filename);

	void Load(const std::wstring &filename);
	void XmlItem(wxXmlNode* node, bool declaration, bool isInContainer );
	void OnDraw(std::shared_ptr<wxGraphicsContext> graphics);
	//std::shared_ptr<Item> HitTest(double x, double y);
	void SetLevel();
	void ResetLevel();

	virtual void Update(double elapsed);

	void MoveSpartyTo(double x, double y);
    void SpartyHeadButt();
    /**
     * Vomiting digit
     * @param keycode
     */
    void SpartyVomit(char keycode);

    void Accept(ItemVisitor *visitor);
    /**
     * Loading the game
     * @param node
     */
	void XmlGame(wxXmlNode *node);

	/**
	 * getter for level size
	 * @return mGameSize member variable
	 */
	wxSize GetLevelSize() const {return mGameSize;}
	void MakeMatrix(const wxString &data);

    void Solve();

    void Remove(std::shared_ptr<Item> item);
	void SpartyEat();
    void Add(std::shared_ptr<Item> item);
    /**
     * Getting ID
     * @return
     */
	std::map<std::string, std::shared_ptr<Item>> GetIdItemMap() const {return mIdItemMap;}
    /**
     * getting tile width
     * @return
     */
	int GetTileWidth() const {return mTileWidth;}
    /**
     * getting height
     * @return
     */
	int GetTileHeight() const {return mTileHeight;}

    /// Destructor.
    ~Level();

	void ResetXray();
};

#endif //PROJECT1_ACTIONSUDOKULIB_LEVEL_H