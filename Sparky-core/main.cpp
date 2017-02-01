#include "src\graphics\window.h"
#include "src\graphics\shader.h"
#include "src\maths\maths.h"

#include "src\graphics\buffers\bufferin.h"

#include "src\graphics\renderer2d.h"
#include "src\graphics\simple2DRenderer.h"

#include "src\graphics\sprite.h"
#include "src\graphics\batchrenderer2D.h"

#include "src\utils\timer.h"

#include <time.h>
#include <ctime>

#define BATCH 1

int main()
{
	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window("Sparky!", 960, 540);
	glClearColor(0, 0, 1, 0);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniform2f("light_pos", vec2(8, 4.5));

	std::vector<Renderable2D*> sprites;
	
	srand(time(NULL));


	for (float y = 0; y < 9.0f; y += 0.1)
	{
		for (float x = 0; x < 16.0f; x += 0.1)
		{
#if BATCH
			sprites.push_back(new Sprite(x, y, 0.1f, 0.1f, maths::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1)));
#else 
			sprites.push_back(new StaticSprite(x, y, 0.1f, 0.1f, maths::vec4(rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1), shader));
#endif
		}
	}

	std::cout << sprites.size() << std::endl;

#if BATCH
	Sprite sprite (0, 0, 2, 2, maths::vec4(1, 0, 1, 1));
	Sprite sprite1(2, 2, 2, 2, maths::vec4(1, 1, 1, 1));
	Sprite sprite2(4, 4, 2, 2, maths::vec4(1, 0, 0, 1));
	BatchRenderer2D renderer;

#else
	StaticSprite sprite(0, 0, 2, 2, maths::vec4(1, 0, 1, 1), shader);
	StaticSprite sprite1(2, 2, 2, 2, maths::vec4(1, 1, 1, 1), shader);
	StaticSprite sprite2(4, 4, 2, 2, maths::vec4(1, 0, 0, 1), shader);
	Simple2DRenderer renderer;
#endif

	Timer time;
	float seconds = 0;
	int fps = 0;

	while (!window.closed())
	{
		window.clear();

		double x, y;
		window.getMousePos(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));

#if BATCH
		renderer.begin();
#endif
		for (int i = 0; i < sprites.size(); i++)
			renderer.submit(sprites[i]);
#if BATCH
		renderer.end();
#endif
		renderer.flush();
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