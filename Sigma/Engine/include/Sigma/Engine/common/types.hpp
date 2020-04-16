#pragma once

#include <DirectXMath.h>

namespace sigma
{
	using Int8 = __int8;
	using Int16 = __int16;
	using Int32 = __int32;
	using Int64 = __int64;

	using UInt8 = unsigned __int8;
	using UInt16 = unsigned __int16;
	using UInt32 = unsigned __int32;
	using UInt64 = unsigned __int64;

	using Float = float;
	using Double = double;

	using Bool = bool;

	using Vector2i = DirectX::XMINT2;
	using Vector3i = DirectX::XMINT3;
	using Vector4i = DirectX::XMINT4;
	
	using Vector2 = DirectX::XMFLOAT2;
	using Vector3 = DirectX::XMFLOAT3;
	using Vector4 = DirectX::XMFLOAT4;

	using Matrix3x3 = DirectX::XMFLOAT3X3;
	
	using Matrix4x4 = DirectX::XMFLOAT4X4;
	using Matrix3x4 = DirectX::XMFLOAT3X4;
	using Matrix4x3 = DirectX::XMFLOAT4X3;
}