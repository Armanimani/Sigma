#pragma once

#include <QtCore>
#include <QtWidgets>

namespace sigma::editor
{
	class Editor final : public QMainWindow
	{
		Q_OBJECT
	public:
		Editor(QWidget* parent = nullptr);
	};
}
