#include"../HeaderFiles/Animation.h"



Animation::Animation() {


}

Animation::Animation(int index, int numFrame, int animationSpeed) {
	this->index = index;
	this->animationSpeed = animationSpeed;
	this->numFrame = numFrame;

}