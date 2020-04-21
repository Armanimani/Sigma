#pragma once

#include <vector>

namespace sigma
{
	template<typename ElementType, typename SizeType = std::size_t>
	void safe_assignment(std::vector<ElementType>& vector, SizeType index, const ElementType& element)
	{
		if (vector.size() <= index)
		{
			vector.resize(index + 1);
		}
		vector[index] = element;
	}
}
