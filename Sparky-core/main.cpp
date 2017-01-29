#include "src\graphics\window.h"
#include "src\graphics\shader.h"
#include "src\maths\maths.h"

#include "src\graphics\buffers\bufferin.h"

#include "src\graphics\renderer2d.h"
#include "src\graphics\simple2DRenderer.h"

int main()
{
	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window("Sparky!", 960, 540);
	glClearColor(0, 0, 0, 0);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);

	shader.setUniform2f("light_pos", vec2(8, 4.5));

	Renderable2D sprite(maths::vec3(0, 0, 0), maths::vec2(1, 1), maths::vec4(1, 0, 1, 1), shader);
	Renderable2D sprite1(maths::vec3(1, 1, 0), maths::vec2(1, 1), maths::vec4(1, 1, 1, 1), shader);
	Renderable2D sprite2(maths::vec3(2, 2, 0), maths::vec2(1, 1), maths::vec4(1, 0, 0, 1), shader);
	Simple2DRenderer renderer;

	while (!window.closed())
	{
		window.clear();

		double x, y;
		window.getMousePos(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));

		renderer.submit(&sprite);
		renderer.submit(&sprite1);
		renderer.submit(&sprite2);
		renderer.flush();

		window.update();
	}

	return 0;
}