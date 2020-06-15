#ifndef TERRAIN_MAP
#define TERRAIN_MAP

#include<string>

class TerrainMap {
	private:
		std::string textureID;
		int scale;
		int tileSize;

	public:
		TerrainMap(std::string textureID, int scale, int tileSize);
		~TerrainMap();
		void LoadMapCSV(std::string filePath, int mapSizeX, int mapSizeY);
		void AddTile(int sourceX, int sourceY, int x, int y);



};


#endif // !TERRAIN_MAP

