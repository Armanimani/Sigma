#include "EngineWidget.hpp"

namespace sigma::editor
{
	EngineWidget::EngineWidget(QWidget* parent)
		: QWidget(parent){}

	QPaintEngine* EngineWidget::paintEngine() const
	{
		// TODO: This need to be overwritten if context is DirectX otherwise need to be here for OpenGL
		return nullptr;
	}

	WId EngineWidget::get_window_handle() const noexcept
	{
		return winId();
	}
}
