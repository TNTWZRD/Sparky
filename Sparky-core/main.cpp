#include "src\graphics\window.h"
#include "src\graphics\shader.h"
#include "src\maths\maths.h"

#include "src\graphics\buffers\bufferin.h"

#include "src\graphics\renderer2d.h"
#include "src\graphics\simple2DRenderer.h"

#include "src\graphics\sprite.h"
#include "src\graphics\batchrenderer2D.h"

#include "src\utils\timer.h"

#include "src\graphics\layers\tilelayer.h"

#include <time.h>
#include <ctime>

int main()
{
	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window("Sparky!", 960, 540);
	glClearColor(0, 0, 0, 0);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader* s2 = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;
	Shader& shader2 = *s2;

	shader.enable();
	shader.setUniform2f("light_pos", vec2(8, 4.5));
	shader2.enable();
	shader2.setUniform2f("light_pos", vec2(8, 4.5));

	TileLayer layer(&shader);
	TileLayer layer2(&shader2);
	layer2.add(new Sprite(0, 0, 4, 4, vec4(1,0,1,1)));

	for (float y = -9.0f; y < 9.0f; y += 0.2)
	{
		for (float x = -16.0f; x < 16.0f; x += 0.2)
		{
			layer.add(new Sprite(x, y, 0.2f, 0.2f, maths::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1)));
		}
	}


	Timer time;
	float seconds = 0;
	int fps = 0;

	while (!window.closed())
	{
		window.clear();

		double x, y;
		window.getMousePos(x, y);
		shader.enable();
		shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));
		shader2.enable();
		shader2.setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));

		layer.render();
		layer2.render();

		window.update();
		fps++;
		if (time.elapsed() - seconds > 1.0f)
		{
			seconds += 1.0f;
			std::cout << fps << " FPS" << std::endl;
			fps = 0;
		}
	}

	return 0;
}