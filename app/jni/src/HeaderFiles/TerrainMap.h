#ifndef TERRAIN_MAP_H
#define TERRAIN_MAP_H

#include<string>

class TerrainMap {
	private:
		std::string textureID;
		int scale;
		int tileSize;

	public:
		TerrainMap(std::string textureID, int scale, int tileSize);
		~TerrainMap();
		void LoadTilemap(std::string filePath, int mapSizeX, int mapSizeY);
		void AddTile(int sourceX, int sourceY, int x, int y);

};


#endif // !TERRAIN_MAP_H

