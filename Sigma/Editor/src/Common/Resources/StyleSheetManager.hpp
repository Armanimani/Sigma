#pragma once

#include <unordered_map>

#include <QtCore/QFile>

#include "constants.hpp"

namespace sigma::editor
{
	enum class StyleSheetType
	{
		dark
	};
	
	
	class StyleSheetManager
	{
	public:
		static QString get_style_sheet(StyleSheetType type);
	private:
		static std::unordered_map<StyleSheetType, QString> m_registry;
	};
	

	inline QString StyleSheetManager::get_style_sheet(const StyleSheetType type)
	{
		QFile style_file(m_registry.at(type));
		style_file.open(QFile::ReadOnly);

		return QString(style_file.readAll());
	}
	
	std::unordered_map<StyleSheetType, QString> StyleSheetManager::m_registry =
	{
		{StyleSheetType::dark, k_stylesheet_dark}
	};
}
