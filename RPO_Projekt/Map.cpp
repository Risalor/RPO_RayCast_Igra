#include "Map.h"

Map::Map() {
	playerPos.x = 22;
	playerPos.y = 12;
	playerDir.x = -1;
	playerDir.y = 0;
	plane.x = 0;
	plane.y = 0.66f;
}

void Map::draw(sf::RenderTarget* window) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (glb::consts::worldMap[int(playerPos.x + playerDir.x)][int(playerPos.y)] == false) playerPos.x += playerDir.x * 0.1f;
		if (glb::consts::worldMap[int(playerPos.x)][int(playerPos.y + playerDir.y)] == false) playerPos.y += playerDir.y * 0.1f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (glb::consts::worldMap[int(playerPos.x - playerDir.y)][int(playerPos.y)] == false) playerPos.x -= playerDir.x * 0.1f;
		if (glb::consts::worldMap[int(playerPos.x)][int(playerPos.y - playerDir.y)] == false) playerPos.y -= playerDir.y * 0.1f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		sf::Vector2f oldDir(playerDir);
		playerDir.x = playerDir.x * cos(-0.1f) - playerDir.y * sin(-0.1f);
		playerDir.y = oldDir.x * sin(-0.1f) + playerDir.y * cos(-0.1f);
		sf::Vector2f oldPlane(plane);
		plane.x = plane.x * cos(-0.1f) - plane.y * sin(-0.1f);
		plane.y = oldPlane.x * sin(-0.1f) + plane.y * cos(-0.1f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		sf::Vector2f oldDir(playerDir);
		playerDir.x = playerDir.x * cos(0.1f) - playerDir.y * sin(0.1f);
		playerDir.y = oldDir.x * sin(0.1f) + playerDir.y * cos(0.1f);
		sf::Vector2f oldPlane(plane);
		plane.x = plane.x * cos(0.1f) - plane.y * sin(0.1f);
		plane.y = oldPlane.x * sin(0.1f) + plane.y * cos(0.1f);
	}

	sf::Image img;
	img.create(screenWidth, screenHeight, sf::Color::Black);

	for (int i = 0; i < 720; i++) {
		double cameraX = 2 * i / 720.0 - 1;
		sf::Vector2f rayDir;
		rayDir.x = playerDir.x + plane.x * cameraX;
		rayDir.y = playerDir.y + plane.y * cameraX;

		sf::Vector2i map;
		map.x = static_cast<int>(playerPos.x);
		map.y = static_cast<int>(playerPos.y);

		sf::Vector2f sideDist;

		sf::Vector2f deltaDist;
		deltaDist.x = (rayDir.y == 0) ? 1e30 : std::abs(1 / rayDir.x);
		deltaDist.y = (rayDir.x == 0) ? 1e30 : std::abs(1 / rayDir.y);

		float wallDist;
		sf::Vector2i step;

		bool hit = false;
		int side;

		if (rayDir.x < 0) {
			step.x = -1;
			sideDist.x = (playerPos.x - map.x) * deltaDist.x;
		}
		else {
			step.x = 1;
			sideDist.x = (map.x + 1.f - playerPos.x) * deltaDist.x;
		}

		if (rayDir.y < 0) {
			step.y = -1;
			sideDist.y = (playerPos.y - map.y) * deltaDist.y;
		}
		else {
			step.y = 1;
			sideDist.y = (map.y + 1.f - playerPos.y) * deltaDist.y;
		}

		while (!hit) {
			if (sideDist.x < sideDist.y) {
				sideDist.x += deltaDist.x;
				map.x += step.x;
				side = 0;
			}
			else {
				sideDist.y += deltaDist.y;
				map.y += step.y;
				side = 1;
			}

			if (glb::consts::worldMap[map.x][map.y] > 0) {
				hit = true;
			}
		}

		if (side == 0) {
			wallDist = (map.x - playerPos.x + (1 - step.x) / 2) / rayDir.x;
		}
		else {
			wallDist = (map.y - playerPos.y + (1 - step.y) / 2) / rayDir.y;
		}

		int lineHeight = static_cast<int>(screenHeight / wallDist);
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;

		sf::Color col;

		if (side == 1) {
			col = sf::Color::Magenta;
		} else {
			col = sf::Color::Blue;
		}

		for (int u = drawStart; u < drawEnd; u++) {
			/*for (int c = i * 6; c < i * 6 + 6; c++) {
				img.setPixel(c, u, col);
			}*/

			img.setPixel(i, u, col);
		}
	}

	sf::Texture tex;
	tex.loadFromImage(img);
	sf::RectangleShape shp(sf::Vector2f(screenWidth, screenHeight));
	shp.setTexture(&tex);

	window->draw(shp);
}
