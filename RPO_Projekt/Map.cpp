#include "Map.h"


bool hasLineOfSight(const sf::Vector2f& start, const sf::Vector2f& end) {
	sf::Vector2f direction = end - start;
	float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction /= distance;

	float increment = 0.5f;

	for (float t = 0.0f; t < distance; t += increment) {
		int mapX = static_cast<int>(start.x + direction.x * t);
		int mapY = static_cast<int>(start.y + direction.y * t);

		if (glb::consts::worldMap[mapX][mapY] > 0) {
			return false;
		}
	}

	return true;
}

void Map::handleDoor(Player& pInfo) {
	if (glb::consts::worldMap[int(pInfo.getPos().x + pInfo.getDir().x)][int(pInfo.getPos().y + pInfo.getDir().y)] == 5) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			glb::consts::worldMap[int(pInfo.getPos().x + pInfo.getDir().x)][int(pInfo.getPos().y + pInfo.getDir().y)] = 0;
		}
	}
}

Map::Map() {

	spriteManager.addNewTexture("Assets/Enemy/Enemy.png");
	spriteManager.addNewTexture("Assets/Projectile/projectile.png");

	std::filesystem::path folder("Assets/WallTex");

	if (std::filesystem::exists(folder) && std::filesystem::is_directory(folder)) {
		for (const auto& it : std::filesystem::directory_iterator(folder)) {
			if (std::filesystem::is_regular_file(it)) {
				sf::Image img;
				textures.push_back(sf::Texture());
				textures.at(textures.size() - 1).loadFromFile(it.path().string());
				if (img.loadFromFile(it.path().string())) {
					sf::Image darkImg;
					darkImg.create(64, 64, sf::Color::Transparent);
					texture.push_back(std::vector<sf::Color>());
					texture[texture.size() - 1].resize(texHeight * texWidth);

					int x = 0;
					for (int i = 0; i < texWidth; i++) {
						for (int j = 0; j < texHeight; j++) {
							texture[texture.size() - 1][x] = img.getPixel(j, i);
							darkImg.setPixel(j, i, sf::Color(img.getPixel(j, i).r / 1.7f, img.getPixel(j, i).g / 1.7f, img.getPixel(j, i).b / 1.7f));
							x++;
						}
					}

					darkTextures.push_back(sf::Texture());
					darkTextures.at(darkTextures.size() - 1).loadFromImage(darkImg);
				}
				else {
					std::cout << "Failed to load image: " << it.path().string() << std::endl;
				}
			}
		}
	}
	else {
		std::cout << "Folder does not exist or is not a directory." << std::endl;
	}
}

void Map::draw(sf::RenderTarget* window, Player& pInfo, std::vector<Enemy*> eInfo, std::vector<Projectile*> prInfo, std::vector<Item*> itemStartPos) {

	rayCastDraw(window, pInfo, eInfo, prInfo, itemStartPos);
	draw2D(window, pInfo, eInfo, prInfo, itemStartPos);
}

void Map::rayCastDraw(sf::RenderTarget* window, Player& pInfo, std::vector<Enemy*> eInfo, std::vector<Projectile*> prInfo, std::vector<Item*> itemStartPos) {
	sf::Image buffer;
	buffer.create(screenWidth, screenHeight, sf::Color::Transparent);

	handleDoor(pInfo);

	sf::Vector2f rayL(pInfo.getDir().x - pInfo.getPlane().x, pInfo.getDir().y - pInfo.getPlane().y), rayR(pInfo.getDir().x + pInfo.getPlane().x, pInfo.getDir().y + pInfo.getPlane().y);
	float vertPoz = screenHeight / 2;
	for (int i = screenHeight / 2; i < screenHeight - 1; i++) {

		int centerPoz = i - vertPoz;

		float camPoz = vertPoz / centerPoz;

		sf::Vector2f step(camPoz * (rayR.x - rayL.x) / screenWidth, camPoz * (rayR.y - rayL.y) / screenWidth);
		sf::Vector2f floor(pInfo.getPos().x + camPoz * rayL.x, pInfo.getPos().y + camPoz * rayL.y);

		for (int j = 0; j < screenWidth; j++) {
			sf::Vector2i cell(floor.x, floor.y);

			sf::Vector2i tex((int)(texWidth * (floor.x - cell.x)) & (texWidth - 1), (int)(texWidth * (floor.y - cell.y)) & (texWidth - 1));

			floor.x += step.x;
			floor.y += step.y;

			buffer.setPixel(j, i, texture[3][texWidth * tex.y + tex.x]);
			buffer.setPixel(j, screenHeight - i - 1, texture[1][texWidth * tex.y + tex.x]);

		}
	}

	sf::Texture tex;
	tex.loadFromImage(buffer);
	sf::RectangleShape shp(sf::Vector2f(screenWidth, screenHeight));
	shp.setTexture(&tex);

	window->draw(shp);

	for (int i = 0; i < 720; i++) {
		double cameraX = 2 * i / 720.0 - 1;
		sf::Vector2f rayDir;
		rayDir.x = pInfo.getDir().x + pInfo.getPlane().x * cameraX;
		rayDir.y = pInfo.getDir().y + pInfo.getPlane().y * cameraX;

		sf::Vector2i map;
		map.x = static_cast<int>(pInfo.getPos().x);
		map.y = static_cast<int>(pInfo.getPos().y);

		sf::Vector2f sideDist;

		sf::Vector2f deltaDist;
		deltaDist.x = std::abs(1 / rayDir.x);
		deltaDist.y = std::abs(1 / rayDir.y);

		float wallDist;
		sf::Vector2i step;

		bool hit = false;
		int side;

		if (rayDir.x < 0) {
			step.x = -1;
			sideDist.x = (pInfo.getPos().x - map.x) * deltaDist.x;
		}
		else {
			step.x = 1;
			sideDist.x = (map.x + 1.f - pInfo.getPos().x) * deltaDist.x;
		}

		if (rayDir.y < 0) {
			step.y = -1;
			sideDist.y = (pInfo.getPos().y - map.y) * deltaDist.y;
		}
		else {
			step.y = 1;
			sideDist.y = (map.y + 1.f - pInfo.getPos().y) * deltaDist.y;
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
			wallDist = (map.x - pInfo.getPos().x + (1 - step.x) / 2) / rayDir.x;
		}
		else {
			wallDist = (map.y - pInfo.getPos().y + (1 - step.y) / 2) / rayDir.y;
		}

		int lineHeight = static_cast<int>(screenHeight / wallDist);
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;

		//_____CALC_TEXTURE___//

		int texNum = glb::consts::worldMap[map.x][map.y] - 1;
		double wallHit;

		if (side == 0) {
			wallHit = pInfo.getPos().y + wallDist * rayDir.y;
		}
		else {
			wallHit = pInfo.getPos().x + wallDist * rayDir.x;
		}

		wallHit -= floor(wallHit);

		int texHit = int(wallHit * double(texWidth));

		if (side == 0 && rayDir.x > 0) {
			texHit = texWidth - texHit - 1;
		}

		if (side == 1 && rayDir.y < 0) {
			texHit = texWidth - texHit - 1;
		}

		sf::Sprite sp;

		if (side == 0) {
			if (texNum > 6) {
				sp.setTexture(textures.at(4));
			} else {
				sp.setTexture(textures.at(texNum));
			}
		} else {
			if (texNum > 6) {
				sp.setTexture(darkTextures.at(4));
			} else {
				sp.setTexture(darkTextures.at(texNum));
			}
		}
		
		if (lineHeight <= screenHeight) {
			sp.setTextureRect(sf::IntRect(texHit, 0, 1, 64));
			sp.setScale(1.f / sp.getGlobalBounds().width, lineHeight / sp.getGlobalBounds().height);
			sp.setPosition(i, drawStart);
			window->draw(sp);
		} else {
			sp.setTextureRect(sf::IntRect(texHit, 0, 1, 64));
			sp.setScale(1.f / sp.getGlobalBounds().width, lineHeight / sp.getGlobalBounds().height);
			sp.setPosition(i, -(lineHeight - screenHeight) / 2.f);
			window->draw(sp);
		}
	}
	
	spriteManager.createSprite(0);
	for (size_t i = 0; i < eInfo.size(); ++i) {
		sf::Vector2f enemyPos = eInfo[i]->getPos();
		sf::Vector2f relativePos = enemyPos - pInfo.getPos();

		float invDet = 1.0f / (pInfo.getPlane().x * pInfo.getDir().y - pInfo.getDir().x * pInfo.getPlane().y);
		float transformX = invDet * (pInfo.getDir().y * relativePos.x - pInfo.getDir().x * relativePos.y);
		float transformY = invDet * (-pInfo.getPlane().y * relativePos.x + pInfo.getPlane().x * relativePos.y);

		if (transformY <= 0) {
			continue;
		}

		if (!hasLineOfSight(pInfo.getPos(), enemyPos)) {
			continue;
		}

		int spriteScreenX = static_cast<int>((screenWidth / 2) * (1 + transformX / transformY));

		int spriteHeight = std::abs(static_cast<int>(screenHeight / transformY));
		int spriteScreenY = screenHeight / 2 - spriteHeight / 2;

		sf::Sprite* enemySprite = spriteManager.getSprite(0);
		enemySprite->setPosition(spriteScreenX, spriteScreenY);

		float scale = static_cast<float>(spriteHeight) / enemySprite->getTextureRect().width;
		enemySprite->setScale(scale, scale);

		window->draw(*enemySprite);
	}

	spriteManager.createSprite(1);
	for (size_t i = 0; i < prInfo.size(); ++i) {
		sf::Vector2f prPos = prInfo[i]->getPos();
		sf::Vector2f relativePos = prPos - pInfo.getPos();

		float invDet = 1.0f / (pInfo.getPlane().x * pInfo.getDir().y - pInfo.getDir().x * pInfo.getPlane().y);
		float transformX = invDet * (pInfo.getDir().y * relativePos.x - pInfo.getDir().x * relativePos.y);
		float transformY = invDet * (-pInfo.getPlane().y * relativePos.x + pInfo.getPlane().x * relativePos.y);

		if (transformY <= 0) {
			continue;
		}

		int spriteScreenX = static_cast<int>((screenWidth / 2) * (1 + transformX / transformY));

		int spriteHeight = std::abs(static_cast<int>(screenHeight / transformY));
		int spriteScreenY = screenHeight / 2 - spriteHeight / 2 + 20; 

		sf::Sprite* projectileSprite = spriteManager.getSprite(1);
		projectileSprite->setPosition(spriteScreenX, spriteScreenY);

		float scale = static_cast<float>(spriteHeight) / projectileSprite->getTextureRect().width;
		projectileSprite->setScale(scale / 4, scale / 4);

		window->draw(*projectileSprite);
	}


	sf::Texture pistolTexture;
	sf::Texture shotgunTexture;
	sf::Texture machinegunTexture;
	if (!pistolTexture.loadFromFile("Assets/Weapon_icons/pistol.png") ||
		!shotgunTexture.loadFromFile("Assets/Weapon_icons/shotgun.png") ||
		!machinegunTexture.loadFromFile("Assets/Weapon_icons/machinegun.png")) {
		std::cout << "Napaka pri nalaganju tekstur orožij!" << std::endl;
	}

	
	int baseOffset = 0; // Osnovna višina nad tlemi za vse ikone.

	// ... [prejšnja koda] ...

	for (auto& item : itemStartPos) {
		if (item->getPickedStatus()) continue; // Preskoči, če je predmet že pobran

		sf::Sprite itemSprite;
		if (item->getName() == "pistol1") {
			itemSprite.setTexture(pistolTexture);
		}
		else if (item->getName() == "shotgun") {
			itemSprite.setTexture(shotgunTexture);
		}
		else if (item->getName() == "machinegun") {
			itemSprite.setTexture(machinegunTexture);
		}
		else {
			continue; // Preskoči, če predmet ni orožje
		}

		// Izračunaj transformacijo pozicije predmeta glede na igralčevo perspektivo
		sf::Vector2f relativePos = item->getStartPos() - pInfo.getPos();
		float invDet = 1.0f / (pInfo.getPlane().x * pInfo.getDir().y - pInfo.getDir().x * pInfo.getPlane().y);
		float transformX = invDet * (pInfo.getDir().y * relativePos.x - pInfo.getDir().x * relativePos.y);
		float transformY = invDet * (-pInfo.getPlane().y * relativePos.x + pInfo.getPlane().x * relativePos.y);

		// Preskoči, če predmet ni znotraj vidnega polja
		if (transformY <= 0) continue;

		// Izračunaj pravilno velikost in položaj za izris predmeta
		int itemScreenX = int((screenWidth / 2) * (1 + transformX / transformY));
		int itemScreenY = int((screenHeight / 2) - (baseOffset / transformY));

		// Nastavi položaj in velikost sprite-a
		itemSprite.setPosition(itemScreenX, itemScreenY);
		itemSprite.setOrigin(itemSprite.getGlobalBounds().width / 2, itemSprite.getGlobalBounds().height / 2); // Origin na sredini
		itemSprite.setScale(1 / transformY, 1 / transformY); // Skaliraj glede na razdaljo od igralca

		// Izris sprite-a
		window->draw(itemSprite);
	}

}

void Map::draw2D(sf::RenderTarget* window, Player& pInfo, std::vector<Enemy*> eInfo, std::vector<Projectile*> prInfo, std::vector<Item*> itemStartPos) {
	sf::CircleShape pl(5.f);
	pl.setFillColor(sf::Color::Green);
	pl.setPosition(sf::Vector2f((pInfo.getPos().y * 17.14f + screenWidth) - 2.5f, (pInfo.getPos().x * 17.14f) - 2.5f));

	std::vector<sf::CircleShape> enCircles;
	for (int i = 0; i < eInfo.size(); i++) {
		sf::CircleShape en(5.f);
		en.setFillColor(sf::Color::Red);
		en.setPosition(sf::Vector2f((eInfo[i]->getPos().y * 17.14f + screenWidth) - 2.5f, (eInfo[i]->getPos().x * 17.14f) - 2.5f));
		enCircles.push_back(en);
	}

	std::vector<sf::CircleShape> ItemCircles;
	for (int i = 0; i < itemStartPos.size(); i++) {
		sf::CircleShape item(5.f);
		if (itemStartPos[i]->getPickedStatus() == false) {
			item.setFillColor(sf::Color{ 0x87CEEBFF });
		}
		else {
			item.setFillColor(sf::Color(255, 255, 255, 0));
		}
		item.setPosition(sf::Vector2f((itemStartPos[i]->getStartPos().y * 17.14f + screenWidth) - 2.5f, (itemStartPos[i]->getStartPos().x * 17.14f) - 2.5f));
		enCircles.push_back(item);
	}


	std::vector<sf::CircleShape> prCircles;
	for (int i = 0; i < prInfo.size(); i++) {
		sf::CircleShape pr(2.f);
		if (prInfo[i] != nullptr) {
			pr.setFillColor(sf::Color::Blue);
			pr.setPosition(sf::Vector2f((prInfo[i]->getPos().y * 17.14f + screenWidth) - 2.5f, (prInfo[i]->getPos().x * 17.14f) - 2.5f));
			prCircles.push_back(pr);
		}		
	}

	for (int i = 0; i < glb::consts::worldMap.at(0).size(); i++) {
		for (int j = 0; j < glb::consts::worldMap.size(); j++) {
			sf::Texture tex;
			sf::RectangleShape rect(sf::Vector2f(17.14f, 17.14f));
			rect.setOutlineThickness(1.f);
			rect.setOutlineColor(sf::Color::Transparent);
			if (glb::consts::worldMap[j][i] > 0 && glb::consts::worldMap[j][i] < 7) {
				rect.setTexture(&textures.at(glb::consts::worldMap[j][i] - 1));
			}
			else {
				rect.setFillColor(sf::Color::Black);
			}
			rect.setPosition((float)i * 17.14f + screenWidth, (float)j * 17.14f);
			window->draw(rect);
		}
	}

	window->draw(pl);
	for (int i = 0; i < enCircles.size(); i++) {
		window->draw(enCircles[i]);
	}
	for (int i = 0; i < prCircles.size(); i++) {
		window->draw(prCircles[i]);
	}
}

