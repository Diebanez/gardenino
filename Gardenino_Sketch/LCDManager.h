#include "Collection.h"
#include "LCDPage.h"


class LCDManager
{
public:
	LCDManager(uint8_t address, uint8_t cols, uint8_t rows, LCDPage* firstPage);
	void Init();
	void AddPage(LCDPage* page);
	void RemovePage(int pageIndex);
	void SwapPage();
	void Update();
	void SetVisualizedPage(const int& Page);
	void DisplayError(const String& Message);

private:
	LiquidCrystal_I2C Display;
	int ActivePage;
	Collection<LCDPage> Pages;
};