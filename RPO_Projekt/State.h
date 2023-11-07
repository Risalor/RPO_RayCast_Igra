#include <SFML/Graphics.hpp>
class State {
protected:
	virtual void initState() = 0;
public:
	State();

	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderTarget* window) = 0;
};
