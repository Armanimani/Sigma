#pragma once

#include <QtWidgets>

namespace sigma::editor
{
	class EngineWidget final: public QWidget
	{
		Q_OBJECT
	public:
		explicit EngineWidget(QWidget* parent);

		[[nodsicard]] WId get_window_handle() const noexcept;
	protected:
		QPaintEngine* paintEngine() const override;
	};
}
