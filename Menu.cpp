#include "Menu.h"
#include <CommCtrl.h>
#include "SettingsC.h"

Menu::Menu(HWND parent,HINSTANCE hInstance)
{
	HIMAGELIST g_hImageList = NULL;

	const int ImageListID = 0;
	const int bitmapSize = 16;

	const DWORD buttonStyles = BTNS_AUTOSIZE;


	m_toolbar = CreateWindowEx(CS_HREDRAW | CS_VREDRAW, TOOLBARCLASSNAME, NULL,
		WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX | WS_OVERLAPPED |
		WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, Settings::GetResolutionY()-100, Settings::GetResolutionX(), 100,
		parent, NULL, hInstance, NULL);




	g_hImageList = ImageList_Create(bitmapSize, bitmapSize,
		ILC_COLOR32 | ILC_MASK,
		1, 0);


	SendMessage(m_toolbar, TB_SETIMAGELIST,
		(WPARAM)ImageListID,
		(LPARAM)g_hImageList);


	SendMessage(m_toolbar, TB_LOADIMAGES,
		(WPARAM)IDB_STD_SMALL_COLOR,
		(LPARAM)HINST_COMMCTRL);

	// Initialize button info.
	// IDM_NEW, IDM_OPEN, and IDM_SAVE are application-defined command constants.

	TBBUTTON tbButtons[1] =
	{
	MAKELONG(5, ImageListID), MenuEvents::MENU_EXIT, TBSTATE_ENABLED,               buttonStyles,{ 0 }, 0, (INT_PTR)"Exit"
	};

	// Add buttons.
	SendMessage(m_toolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	SendMessage(m_toolbar, TB_ADDBUTTONS, (WPARAM)1, (LPARAM)&tbButtons);

	// Resize the toolbar, and then show it.
	SendMessage(m_toolbar, TB_AUTOSIZE, 0, 0);
	ShowWindow(m_toolbar, TRUE);
}


Menu::~Menu()
{
}
