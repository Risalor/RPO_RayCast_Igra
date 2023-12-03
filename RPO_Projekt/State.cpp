
#include "State.h"

State::State() : trigger(StateTrigger::NO_TRIGGER) {

}

StateTrigger State::getTrigger() {
	return trigger;
}

void State::setTrigger(StateTrigger trigger) {
	this->trigger = trigger;
}
