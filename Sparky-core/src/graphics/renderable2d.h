#pragma once


#include "buffers\bufferin.h"
#include "../maths/maths.h"

#include "shader.h"

namespace sparky{ namespace graphics {

	struct VertexData
	{
		maths::vec3 vertex;
		// maths::vec4 color;
		unsigned int color;
	};

	class Renderable2D
	{
	protected:
		maths::vec2 m_Size;
		maths::vec3 m_Position;
		maths::vec4 m_Color;

	public:
		
		Renderable2D(maths::vec3 pos, maths::vec2 size, maths::vec4 color) 
			: m_Size(size), m_Position(pos), m_Color(color)
		{ }

		virtual ~Renderable2D(){}

		inline const maths::vec2& getSize()     const { return m_Size; }
		inline const maths::vec3& getPosition() const { return m_Position; }
		inline const maths::vec4& getColor()    const { return m_Color; }

	};

} }