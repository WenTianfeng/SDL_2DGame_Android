#include <fstream>
#include"../HeaderFiles/TerrainMap.h"
#include"../Components/ComponentTile.h"
#include"../Components/ComponentTransform.h"

/*
 * TileMap类
 * */

TerrainMap::TerrainMap(std::string textureID, int scale, int tileSize) {
	this->scale = scale;
	this->textureID = textureID;
	this->tileSize = tileSize;
}

TerrainMap::~TerrainMap() {

}


//从Map文本文件中加载地图信息，根据地图排布生成Tilemap
void TerrainMap::LoadTilemap(std::string filePath, int mapSizeX, int mapSizeY) {

	//SDL文件加载方法
	SDL_RWops *io = SDL_RWFromFile(filePath.c_str(), "r");
	if(!io){
		SDL_Quit();
	}

    char raw_nums[(mapSizeX*3)*mapSizeY];
	io->read(io,raw_nums,1, sizeof(raw_nums));

	for (int y = 0; y < mapSizeY; y++)
	{
		for (int x = 0; x < mapSizeX; x++)
		{

				int sourceRectY = (((int)raw_nums[(y*mapSizeX+x)*3])-48)*tileSize;
				int sourceRectX = (((int)raw_nums[(y*mapSizeX+x)*3+1])-48)*tileSize;

				AddTile(sourceRectX, sourceRectY, x * (scale * tileSize), y * (scale * tileSize));
		}
	}



}

//生成单个Tile实体
void TerrainMap::AddTile(int sourceX, int sourceY, int x, int y) {
	Entity& tileEntity(Game::getInstance()->entityManager->AddEntity("Tile",LAYER_TILEMAP));
	tileEntity.AddComponent<ComponentTransform>(x,y,0,0,tileSize*scale,tileSize*scale,1);
	tileEntity.AddComponent<ComponentTile>(sourceX, sourceY, x, y,tileSize, scale, textureID);

}