#ifndef COMPONENT_PROJECTILE_LAUNCHER_H
#define COMPONENT_PROJECTILE_LAUNCHER_H

#include"../HeaderFiles/Game.h"
#include"../../UtilLib/glm/glm.hpp"
#include"ComponentJoystickControl.h"
#include"ComponentTransform.h"
#include"ComponentProjectile.h"

extern EntityManager manager;
/*
弹丸发射器组件
继承自组件基类和轮盘可控接口
*/
class ComponentProjectileLauncher:public Component,public IControlledByJoystick {

private:
	SDL_Texture* projectileTexture;// 弹丸使用的贴图
	int attackRate;//发射速率
	int preTicks;//发射上一颗弹丸对应的时间，用来控制发射间隔
	glm::vec2 emissionOrigin;//发射起始点
	std::vector<Entity*> projectiles;//存储所有发射出去的弹丸
	ComponentTransform* transform;

public:

	ComponentProjectileLauncher(std::string assetProjectileTextureID) {

		projectileTexture = Game::assetManager->GetTexture(assetProjectileTextureID);//设置弹丸贴图
		attackRate = 2;
	}

	~ComponentProjectileLauncher() {
	}

	void Initialize() override {

		transform = owner->GetComponent<ComponentTransform>();
		
	}


	void Update(float deltaTime) override {

        //遍历列表所有弹丸并调用其更新函数
        if (projectiles.size() > 0) {

            //遍历列表所有弹丸对象,如果其生命值结束，则从manager当中删除该弹丸

            for (int i = 0; i < projectiles.size(); ++i) {
                if (projectiles[i]->GetComponent<ComponentProjectile>()->lifeTime >1000) {
                    projectiles[i]->SetActive(false);
					projectiles.erase(projectiles.begin()+i);
                }
            }
        }




    }



	void Render() override {
	}
	
	//发射弹丸方法
	void EmitProjectiles(glm::vec2 emissionOrigin, glm::vec2 emissionDir) {

		int newTicks = SDL_GetTicks();

		if ((newTicks - preTicks) >= 1000/ attackRate) {//控制发射间隔

			Entity& projectile_entity(manager.AddEntity("projectile",LAYER_PROJECTILE));
			projectile_entity.AddComponent<ComponentTransform>(emissionOrigin.x,emissionOrigin.y,0,0,8,8,1);
			projectile_entity.AddComponent<ComponentProjectile>(projectileTexture,emissionOrigin,emissionDir,16,16);
			projectiles.push_back(&projectile_entity);
			preTicks = newTicks;
		}

	}

	//由轮盘控制的部分
	virtual void UpdateByJoystick(glm::vec2 normalizedDir) {
		emissionOrigin = glm::vec2(transform->position.x + transform->width / 2, transform->position.y + transform->height / 2);//设置发射起始点位置
		EmitProjectiles(emissionOrigin, normalizedDir);

	}

	virtual void OnJoystickInvalid() {

	}

};


#endif // ! COMPONENT_PROJECTILE_LAUNCHER_H

