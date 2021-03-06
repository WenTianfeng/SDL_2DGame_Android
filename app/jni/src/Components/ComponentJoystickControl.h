#ifndef COMPONENT_JOYSTICK_CONTROL_H
#define COMPONENT_JOYSTICK_CONTROL_H

#include<list>
#include"../HeaderFiles/Game.h"
#include"../../UtilLib/glm/glm.hpp"
#include "./HeaderFiles/Interfaces.h"






/*
轮盘控制组件
*/
class ComponentJoystickControl :public Component {

private:
	glm::vec2 slide_area_center;//滑动区域中心位置
	bool isValidTouch;//目前是否处于触摸状态
	std::list<IControlledByJoystick*> controlledThings;//被该轮盘控制的物体
	int m_fingerId = -1;
	SDL_TouchID  m_touchId = 0;

public:

	//贴图对象
	SDL_Texture* slidingAreaTexture;
	SDL_Texture* buttonTexture;

	//滑动区域rect
	SDL_Rect slidingAreaSourceRect;
	SDL_Rect slidingAreaDestRect;
	//按钮 Rect
	SDL_Rect buttonSourceRect;
	SDL_Rect buttonDestRect;



	//构造函数
	//param：按钮贴图资源；按钮rect位置，宽高
	//param：滑动区域贴图资源；滑动区域rect位置，宽高
	ComponentJoystickControl(std::string assetButtonTextureID,int buttonWidth,int buttonHeight,
		std::string assetSlideAreaTextureID,int slideAreaX,int slideAreaY,int slideAreaWidth,int slideAreaHeight) {


		slidingAreaTexture = Game::getInstance()->assetManager->GetTexture(assetSlideAreaTextureID);
		buttonTexture = Game::getInstance()->assetManager->GetTexture(assetButtonTextureID);

		//SourceRect读取参数设定，目前固定，只应输入128x128的滑动区域贴图和64x64的button贴图

		slidingAreaSourceRect.x = 0;
		slidingAreaSourceRect.y = 0;
		slidingAreaSourceRect.w = 128;
		slidingAreaSourceRect.h = 128;

		buttonSourceRect.x = 0;
		buttonSourceRect.y = 0;
		buttonSourceRect.w = 64;
		buttonSourceRect.h = 64;

		//初始化滑动区域的位置和宽高
		slidingAreaDestRect.x = slideAreaX;
		slidingAreaDestRect.y = slideAreaY;
		slidingAreaDestRect.w = slideAreaWidth;
		slidingAreaDestRect.h = slideAreaHeight;

		slide_area_center = glm::vec2(slidingAreaDestRect.x + slidingAreaDestRect.w / 2, slidingAreaDestRect.y + slidingAreaDestRect.h / 2);

		//初始化button的位置和宽高

		buttonDestRect.w = buttonWidth;
		buttonDestRect.h = buttonHeight;
		buttonDestRect.x = slide_area_center.x - buttonDestRect.w / 2;
		buttonDestRect.y = slide_area_center.y - buttonDestRect.h / 2;

		isValidTouch = false;


	}

	//初始化
	void Initialize() override {

	}



	//根据输入状态得到输入结果，并改变轮盘的显示
	void Update(float deltaTime) override {

		SDL_Event input_event = Game::getInstance()->event;
		UpdateAccordingEvent(input_event);
	

	}


	void Render(float offsetX,float offsetY) override {

		//根据位置渲染滑动区域
		TextureManager::DrawTexture(slidingAreaTexture, slidingAreaSourceRect, slidingAreaDestRect, SDL_FLIP_NONE);
		//根据位置渲染button
		TextureManager::DrawTexture(buttonTexture, buttonSourceRect, buttonDestRect, SDL_FLIP_NONE);

	
	}

	//Joystick根据事件做出反应
	void UpdateAccordingEvent(SDL_Event input_event){
		switch(input_event.type){

			case SDL_FINGERDOWN:{

				glm::vec2 touch_pos;
				touch_pos.x = input_event.tfinger.x * static_cast<float>(WINDOW_WIDTH);
				touch_pos.y = input_event.tfinger.y * static_cast<float>(WINDOW_HEIGHT);

				auto distance = std::sqrt(std::pow(touch_pos.x - slide_area_center.x, 2) + std::pow(touch_pos.y - slide_area_center.y, 2));

				if (m_fingerId == -1 && distance <= slidingAreaDestRect.w / 2) {

					m_fingerId = input_event.tfinger.fingerId;
					m_touchId = input_event.tfinger.touchId;
					isValidTouch = true;

					//设定按钮位置为点击位置
					buttonDestRect.x = touch_pos.x - buttonDestRect.w / 2;
					buttonDestRect.y = touch_pos.y - buttonDestRect.h / 2;

				}
				break;
			}
			case SDL_FINGERMOTION:{

				if (isValidTouch&&input_event.tfinger.fingerId==m_fingerId) {


					SDL_Finger* finger = SDL_GetTouchFinger(m_touchId,m_fingerId);

					if(!finger){
						return;;
					}

					glm::vec2 touch_pos;
					//touch_pos.x = input_event.tfinger.x * static_cast<float>(WINDOW_WIDTH);
					//touch_pos.y = input_event.tfinger.y * static_cast<float>(WINDOW_HEIGHT);
					touch_pos.x = finger->x * static_cast<float>(WINDOW_WIDTH);
					touch_pos.y = finger->y * static_cast<float>(WINDOW_HEIGHT);

					auto distance = std::sqrt(std::pow(touch_pos.x - slide_area_center.x, 2) +
											  std::pow(touch_pos.y - slide_area_center.y, 2));

					glm::vec2 dir(touch_pos.x - slide_area_center.x,
								  touch_pos.y - slide_area_center.y);

					glm::vec2 normalizedDir = glm::normalize(dir);

					glm::vec2 aimPos(
							normalizedDir.x * slidingAreaDestRect.w / 2 + slide_area_center.x,
							normalizedDir.y * slidingAreaDestRect.w / 2 + slide_area_center.y);

					//如果目前处于触摸阶段，那么按钮向对应方向移动

					if (distance <= slidingAreaDestRect.w / 2)    //如果位置位于滑动区域之内，按钮位置即为触摸位置
					{
						buttonDestRect.x = touch_pos.x - buttonDestRect.w / 2;
						buttonDestRect.y = touch_pos.y - buttonDestRect.h / 2;
					} else {                                                            //如果位置位于滑动区域之外，按钮位置为朝向触摸位置的滑动区域边界位置

						buttonDestRect.x = aimPos.x - buttonDestRect.w / 2;
						buttonDestRect.y = aimPos.y - buttonDestRect.h / 2;
					}

					//改变绑定对象的运动状态
					UpdateControlledThings(normalizedDir);
				}
				break;
			}
			case SDL_FINGERUP:{
				SDL_FingerID id = Game::getInstance()->event.tfinger.fingerId;

				if (m_fingerId == id){
					isValidTouch = false;

					//button回到初始位置
					buttonDestRect.x = slide_area_center.x - buttonDestRect.w / 2;
					buttonDestRect.y = slide_area_center.y - buttonDestRect.h / 2;

					m_fingerId = -1;
					m_touchId = 0;

					ToDoOnJoystickInvalid();

				}
				break;
			}

		}

	}

	//根据轮盘输入得到的方向向量改变接收者状态
	void UpdateControlledThings(glm::vec2 normalizedDir) {
		std::list<IControlledByJoystick*>::iterator itor= controlledThings.begin();

		for (;itor != controlledThings.end(); itor++) {
			(*itor)->UpdateByJoystick(normalizedDir);
		}
	
	}

	void ToDoOnJoystickInvalid() {
		std::list<IControlledByJoystick*>::iterator itor = controlledThings.begin();

		for (;itor != controlledThings.end(); itor++) {
			(*itor)->OnJoystickInvalid();
		}
	}

	void AttachControlledThing(IControlledByJoystick* thing) {
		controlledThings.push_back(thing);
	
	}

	void DetachControlledThing(IControlledByJoystick* thing) {
		controlledThings.remove(thing);
	}


};


#endif // !COMPONENT_JOYSTICK_CONTROL_H

