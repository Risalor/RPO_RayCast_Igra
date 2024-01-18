//#include "Map.h"
#include "Button.h"
enum StateTrigger { START_GAME, END_STATE, END_GAME, NO_TRIGGER, START_EDITOR, START_OPTIONS };

class State {
protected:
	virtual void initState() = 0;
	StateTrigger trigger;
public:
	State();
	StateTrigger getTrigger();
	virtual void update(float dt, sf::Vector2f mousePos) = 0;
	virtual void draw(sf::RenderTarget* window) = 0;
	void setTrigger(StateTrigger trigger);
};
