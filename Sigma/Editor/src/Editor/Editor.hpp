#pragma once

#include <QtCore>
#include <QtWidgets>

#include "ui_Editor.h"

namespace sigma::editor
{
	class Editor final : public QMainWindow
	{
		Q_OBJECT
	public:
		explicit Editor(QWidget* parent = nullptr);
	private:
		Ui::MainWindow m_ui{};
	};
}
