#include "inputcomponent.h"
#include "simulator.h"
InputComponent::InputComponent(Entity* entity) : Component(*entity)
{
	enable();
}
InputComponent::~InputComponent() {}

void InputComponent::onInitialize() { 
	using namespace std::placeholders;
	InputManager& input = Simulator::getInstance().getInput();
	input.bind("Move right", std::bind(&InputComponent::moveRight, this, _1), 1, new KeyTrigger(SDLK_d));
	input.bind("Move left", std::bind(&InputComponent::moveLeft, this, _1), 1, new KeyTrigger(SDLK_a));
	input.bind("Move down", std::bind(&InputComponent::moveDown, this, _1), 1, new KeyTrigger(SDLK_s));
	input.bind("Move up", std::bind(&InputComponent::moveUp, this, _1), 1, new KeyTrigger(SDLK_w));
}

void InputComponent::moveRight(InputArgs& args) {
	if (args.state == InputState::RELEASED) return;
	Entity& e = getOwner();
	e.setPosition(glm::vec2(e.getPosition().x + 1, e.getPosition().y));
}

void InputComponent::moveLeft(InputArgs& args) {
	if (args.state == InputState::RELEASED) return;
	Entity& e = getOwner();
	e.setPosition(glm::vec2(e.getPosition().x - 1, e.getPosition().y));
}

void InputComponent::moveDown(InputArgs& args) {
	if (args.state == InputState::RELEASED) return;
	Entity& e = getOwner();
	e.setPosition(glm::vec2(e.getPosition().x, e.getPosition().y + 1));
}

void InputComponent::moveUp(InputArgs& args) {
	if (args.state == InputState::RELEASED) return;
	Entity& e = getOwner();
	e.setPosition(glm::vec2(e.getPosition().x, e.getPosition().y - 1));
}