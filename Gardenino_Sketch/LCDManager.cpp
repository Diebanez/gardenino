#include "LCDManager.h"

LCDManager::LCDManager(uint8_t address, uint8_t cols, uint8_t rows, LCDPage* firstPage)
	: Display(address, cols, rows), ActivePage(0), Pages()
{
	Pages.AddElement(firstPage);
}

void LCDManager::Init()
{
	Display.begin();
	Display.backlight();
	Pages.GetElement(ActivePage)->PrintPage(Display);
}

void LCDManager::AddPage(LCDPage* page)
{
	Pages.AddElement(page);
}

void LCDManager::RemovePage(int pageIndex)
{
	Pages.RemoveElement(pageIndex);

	if (ActivePage >= pageIndex)
	{
		ActivePage = ActivePage > 0 ? ActivePage - 1 : 0;
		Pages.GetElement(ActivePage)->PrintPage(Display);
	}
}

void LCDManager::SwapPage()
{
	ActivePage++;
	if (ActivePage >= Pages.GetElementsCount())
	{
		ActivePage = 0;
	}
	Pages.GetElement(ActivePage)->PrintPage(Display);
}

void LCDManager::Update()
{
	Pages.GetElement(ActivePage)->Update(Display);
}

void LCDManager::SetVisualizedPage(const int& Page)
{
	if (ActivePage < 0 || ActivePage >= Pages.GetElementsCount())
	{
		return;
	}
	ActivePage = Page;
	Pages.GetElement(ActivePage)->PrintPage(Display);
}

void LCDManager::DisplayError(const String& Message)
{
	Display.clear();
	Display.setCursor(0, 0);
	Display.print("ERROR");
	Display.setCursor(0, 1);
	Display.print(Message);
}