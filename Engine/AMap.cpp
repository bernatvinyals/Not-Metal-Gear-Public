#include "AMap.h"
#include "Video.h"
#include "ResourceManager.h"
#include <stdio.h>

AMap::AMap(const char* tilemap, int tileset, Camera* _cam)
{
	cameraRef = _cam;
	listOfObjectsInMap = std::vector<Actor*>();
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(tilemap) != tinyxml2::XML_SUCCESS)
	{
		printf("Error XML: %s", doc.ErrorStr());
		return;
	}
	m_image = tileset;
	root = doc.FirstChildElement("map");
	TW = std::stoi(root->FirstChildElement("tileset")->FindAttribute("tilewidth")->Value());
	TH = std::stoi(root->FirstChildElement("tileset")->FindAttribute("tileheight")->Value());
	WTW = std::stoi(root->FindAttribute("width")->Value());
	WTH = std::stoi(root->FindAttribute("height")->Value());
	tileSetSpacing = 0;
	if (root->FirstChildElement("tileset")->FindAttribute("spacing"))
	{
		tileSetSpacing = std::stoi(root->FirstChildElement("tileset")->FindAttribute("spacing")->Value());
	}
	map.resize(WTH);
	colision.resize(WTH);
	for (size_t i = 0; i < map.size(); i++)
	{
		map[i].resize(WTW);
		colision[i].resize(WTW);
	}
	for (tinyxml2::XMLElement* element = root->FirstChildElement("layer");
		element;
		element = element->NextSiblingElement())
	{
		//save text
			std::string tempstr = element->FirstChildElement("data")->GetText();
		//transform text
		int x = 0;
		int y = -1;
		std::string tempintstr = "";
		tinyxml2::XMLAttribute* nameOfMap = (tinyxml2::XMLAttribute*)element->FindAttribute("name");
		std::string name = nameOfMap->Value();
		printf("\n Saved Layer: %s", name.c_str());
		for (int i = 0; i < tempstr.size(); i++)
		{
			if (tempstr[i] == '\n')
			{
				y++;
				x = 0;
			}
			if ((tempstr[i] == ',') && i != 0)
			{
				
				if (name == "Map")
				{
					map[y][x] = std::stoi(tempintstr);
				}
				if (name == "Colision")
				{
					colision[y][x] = std::stoi(tempintstr);
				}
				x++;
				tempintstr = "";
			}
			else if (tempstr[i] != '\n')
			{
				tempintstr.append(1, tempstr[i]);
			}
		}
	}
	tileID = 0;

	tilesetSelectedColumn = 0;
	tilesetSelectedRow = 0;

	tilesetAmountColumns = std::stoi(root->FirstChildElement("tileset")->FindAttribute("columns")->Value());

}
AMap::~AMap()
{
}

void AMap::Update()
{
	for (unsigned int i = 0; i < listOfObjectsInMap.size(); i++)
	{
		listOfObjectsInMap[i]->Update();
	}
}

void AMap::Render()
{

	int CTW = SCREEN_WIDTH / TW;
	int CTH = SCREEN_HEIGHT / TH;
	int TileInicialPintatX = cameraRef->GetX() / TW;
	int TileInicialPintatY = cameraRef->GetY() / TH;
	//printf("\n Camera x: %d  ::  y: %d", cameraRef->GetX(), cameraRef->GetY());
	for (int i = 0; i < WTH; i++)		//Vertical  Fins Tile Count Height
	{
		if ((i >= TileInicialPintatY) && (i<= TileInicialPintatY + CTH + 1))
		{
			for (int j = 0; j < WTW; j++)	//Horizontal Fins Tile Count Width
			{
				//TODO: 
				if ((j >= TileInicialPintatX) && (j <= TileInicialPintatX + CTW + 1))
				{

					rectT.x = ((j * TW) - cameraRef->GetX());
					rectT.y = ((i * TH) - cameraRef->GetY());
					rectT.w = TW;
					rectT.h = TH;
					tileID = map[i][j] - 1;
					if (tileID >= 0)
					{
						tilesetSelectedRow = tileID % 32;  //Cambiar la posicio de on estem en el tileset
						tilesetSelectedColumn = tileID / 32;
						rectS.x = tilesetSelectedRow * TW + tileSetSpacing * tilesetSelectedRow;
						rectS.y = tilesetSelectedColumn * TW + tileSetSpacing * tilesetSelectedColumn;
						rectS.w = TW;
						rectS.h = TH;
						Video::getInstance()->renderGraphic(m_image, rectT.x, rectT.y, rectT.w, rectT.h, rectS.x, rectS.y);
					}
				}
			}
		}
	}

	for (unsigned int i = 0; i < listOfObjectsInMap.size(); i++)
	{
		listOfObjectsInMap[i]->Render();
	}
}

int AMap::GetTileFromMap(int _map, int _x, int _y)
{


	int TileX = _x / TW;
	int TileY = _y / TH;
	if ((TileX < 0 && TileX > WTW) || (TileY < 0 && TileY > WTH))
	{
		return 0;
	}
	switch (_map)
	{
	case 0:
		return map[TileY][TileX];
		break;
	case 1:
		return colision[TileY][TileX];
		break;
	default:
		break;
	}
	return 0;
}
