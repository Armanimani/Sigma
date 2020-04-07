#include "Editor.hpp"

#include "Common/Resources/StyleSheetManager.hpp"

namespace sigma::editor
{
	Editor::Editor(QWidget* parent)
		: QMainWindow(parent)
	{
		m_ui.setupUi(this);

		setStyleSheet(StyleSheetManager::get_style_sheet(StyleSheetType::dark));
	}
}
