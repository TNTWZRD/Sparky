#include "static_sprite.h"

namespace sparky{ namespace graphics {

	StaticSprite::StaticSprite(float x, float y, float width, float height, const maths::vec4& color, Shader& shader) 
		: Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), color), m_Shader(shader)
	{
		m_VertexArray = new VertexArray();
		GLfloat vertices[] =
		{
			0, 0, 0,
			0, height, 0,
			width, height, 0,
			width, 0, 0,
		};

		GLfloat colors[] =
		{
			m_Color.x, m_Color.y, m_Color.z, m_Color.w,
			m_Color.x, m_Color.y, m_Color.z, m_Color.w,
			m_Color.x, m_Color.y, m_Color.z, m_Color.w,
			m_Color.x, m_Color.y, m_Color.z, m_Color.w
		};

		m_VertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
		m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

		GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
		m_IndexBuffer = new IndexBuffer(indices, 6);
	}

	StaticSprite::~StaticSprite()
	{
		delete m_VertexArray;
		delete m_IndexBuffer;
	}

} }