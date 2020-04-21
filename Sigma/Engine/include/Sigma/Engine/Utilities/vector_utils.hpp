#pragma once

#include <vector>

namespace sigma
{
	template<typename ElementType>
	void safe_assignment(std::vector<ElementType>& vector, std::size_t index, const ElementType& element)
	{
		if (vector.size() <= index)
		{
			vector.resize(index + 1);
		}
		vector[index] = element;
	}
}
