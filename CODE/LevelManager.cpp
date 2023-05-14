#include "LevelManager.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>
#include <vector>
#include <utility>

#include "Components.h"
#include "mydrawengine.h"
#include "Shapes.h"
#include "AssetManager.h"
#include "EntityTypes.h"

void LevelManager::init(Levels l)
{
	selectedLevel = l;
	switch (selectedLevel)
	{
	case Level0:
		levelFile = "Assets/Levels/Level0.txt";
		break;
	case Level1:
		levelFile = "Assets/Levels/Level1.txt";
		break;
	case Level2:
		levelFile = "Assets/Levels/Level2.txt";
		break;
	default:
		break;
	}
}

void LevelManager::loadLevel(EntityManager* pEM, MyDrawEngine* pDE, AssetManager* pAM)
{
	// create background and player
	Entity& newBackground(pEM->addEntity(-1, Background));
	Entity& newPlayer(pEM->addEntity(0, Character));

	std::string line;
	std::fstream myFile;
	myFile.open(levelFile, std::ios::in);

	int x = 0;
	int y = 0;
	float gameX = startPosition.XValue+0.5f;
	float gameY = startPosition.YValue-0.5f;
	int rowNumber = LevelHeight - 1;

	std::vector<Entity*> collidersVector1;
	std::vector<Entity*> collidersVector2;
	std::vector<Entity*> collidersVector3;
	std::vector<Entity*> collidersVector4;
	std::vector<Entity*> collidersVector5;
	std::vector<Entity*> collidersVector6;
	std::vector<Entity*> collidersVector7;
	std::vector<Entity*> collidersVector8;
	std::vector<Entity*> collidersVector9;
	std::vector<Entity*> collidersVector10;
	std::vector<Entity*> collidersVector11;
	std::vector<Entity*> collidersVector12;
	std::vector<Entity*> collidersVector13;
	std::vector<Entity*> collidersVector14;
	std::vector<Entity*> collidersVector15;
	std::vector<Entity*> collidersVector16;
	std::vector<Entity*> collidersVector17;
	std::vector<Entity*> collidersVector18;
	std::vector<Entity*> collidersVector19;
	std::vector<Entity*> collidersVector20;
	std::vector<Entity*> collidersVector21;
	std::vector<Entity*> collidersVector22;
	std::vector<Entity*> collidersVector23;
	std::vector<Entity*> collidersVector24;
	std::vector<Entity*> collidersVector25;
	std::vector<Entity*> collidersVector26;
	std::vector<Entity*> collidersVector27;
	std::vector<Entity*> collidersVector28;
	std::vector<Entity*> collidersVector29;
	std::vector<Entity*> collidersVector30;

	while (std::getline(myFile, line))
	{
		std::vector<char> chars(line.begin(), line.end());
		gameX = startPosition.XValue+0.5f;
		for (unsigned int x = 0; x < chars.size(); x++)
		{
			switch (chars[x])
			{
			case ' ':
			{
				// nothing
				Entity& newEmpty(pEM->addEntity( ((LevelWidth * rowNumber) + (x + 1)), World, Empty ));
				newEmpty.addComponent<TransformComponent>(Vector2D(gameX, gameY), 0.0f, 1.0f);
				newEmpty.addComponent<ImageComponent>(pDE, pAM);
				newEmpty.getComponent<ImageComponent>().setImage("empty");
				newEmpty.addComponent<CollisionComponent>();
				newEmpty.getComponent<CollisionComponent>().setActive(false);
				newEmpty.addComponent<ModifyComponent>(rowNumber);
				break;
			}
			case '-':
			{
				// platform
				Entity& newPlatform(pEM->addEntity( ((LevelWidth * rowNumber) + (x + 1)), World, Platform ));
				newPlatform.addComponent<TransformComponent>(Vector2D(gameX, gameY), 0.0f, 1.0f);
				newPlatform.addComponent<ImageComponent>(pDE, pAM);
				newPlatform.getComponent<ImageComponent>().setImage("platform");
				newPlatform.addComponent<CollisionComponent>();
				newPlatform.addComponent<ModifyComponent>(rowNumber);
				break;
			}
			case '^':
			{
				// trappedPlatform
				Entity& newTrappedPlatform(pEM->addEntity(((LevelWidth * rowNumber) + (x + 1)), World, TrappedPlatform));
				newTrappedPlatform.addComponent<TransformComponent>(Vector2D(gameX, gameY), 0.0f, 1.0f);
				newTrappedPlatform.addComponent<ImageComponent>(pDE, pAM);
				newTrappedPlatform.getComponent<ImageComponent>().setImage("trappedPlatform");
				newTrappedPlatform.addComponent<CollisionComponent>();
				newTrappedPlatform.addComponent<ModifyComponent>(rowNumber);
				break;
			}
			case '<':
			{
				// trappedPlatform
				Entity& newTrappedPlatform(pEM->addEntity(((LevelWidth * rowNumber) + (x + 1)), World, TrappedPlatform));
				newTrappedPlatform.addComponent<TransformComponent>(Vector2D(gameX, gameY), 0.0f, 1.0f);
				newTrappedPlatform.addComponent<ImageComponent>(pDE, pAM);
				newTrappedPlatform.getComponent<ImageComponent>().setImage("trappedPlatform");
				newTrappedPlatform.addComponent<CollisionComponent>();
				newTrappedPlatform.addComponent<AnimationComponent>();
				newTrappedPlatform.addComponent<ModifyComponent>(rowNumber);
				break;
			}
			case '>':
			{
				// trappedPlatform
				Entity& newTrappedPlatform(pEM->addEntity(((LevelWidth * rowNumber) + (x + 1)), World, TrappedPlatform));
				newTrappedPlatform.addComponent<TransformComponent>(Vector2D(gameX, gameY), 3.142f, 1.0f);
				newTrappedPlatform.addComponent<ImageComponent>(pDE, pAM);
				newTrappedPlatform.getComponent<ImageComponent>().setImage("trappedPlatform");
				newTrappedPlatform.addComponent<CollisionComponent>();
				newTrappedPlatform.addComponent<AnimationComponent>();
				newTrappedPlatform.addComponent<ModifyComponent>(rowNumber);
				break;
			}
			case 'H':
			{
				// trapHorizontal
				Entity& newTrapHorizontal(pEM->addEntity( ((LevelWidth * rowNumber) + (x + 1)), World, Trap ));
				newTrapHorizontal.addComponent<TransformComponent>(Vector2D(gameX, gameY), 0.0f, 1.0f);
				newTrapHorizontal.addComponent<ImageComponent>(pDE, pAM);
				newTrapHorizontal.getComponent<ImageComponent>().setImage("trap");
				newTrapHorizontal.addComponent<CollisionComponent>();
				newTrapHorizontal.addComponent<ModifyComponent>(rowNumber);
				break;
			}
			case 'I':
			{
				// trapHorizontal
				Entity& newTrapVertical(pEM->addEntity( ((LevelWidth * rowNumber) + (x + 1)), World, Trap ));
				newTrapVertical.addComponent<TransformComponent>(Vector2D(gameX, gameY), 1.571f, 1.0f);
				newTrapVertical.addComponent<ImageComponent>(pDE, pAM);
				newTrapVertical.getComponent<ImageComponent>().setImage("trap");
				newTrapVertical.addComponent<CollisionComponent>();
				newTrapVertical.addComponent<ModifyComponent>(rowNumber);
				break;
			}
			case '~':
			{
				// destroyedEdge
				Entity& newDestroyedEdge(pEM->addEntity( ((LevelWidth * rowNumber) + (x + 1)), World, DestroyedEdge ));
				newDestroyedEdge.addComponent<TransformComponent>(Vector2D(gameX, gameY), 0.0f, 1.0f);
				newDestroyedEdge.addComponent<ImageComponent>(pDE, pAM);
				newDestroyedEdge.getComponent<ImageComponent>().setImage("destroyedEdge");
				newDestroyedEdge.addComponent<CollisionComponent>();
				newDestroyedEdge.addComponent<ModifyComponent>(rowNumber);
				break;
			}
			case 'x':
			{
				// destroyed
				Entity& newDestroyed(pEM->addEntity( ((LevelWidth * rowNumber) + (x + 1)), World, Destroyed ));
				newDestroyed.addComponent<TransformComponent>(Vector2D(gameX, gameY), 0.0f, 1.0f);
				newDestroyed.addComponent<ImageComponent>(pDE, pAM);
				newDestroyed.getComponent<ImageComponent>().setImage("destroyed");
				newDestroyed.addComponent<CollisionComponent>();
				newDestroyed.getComponent<CollisionComponent>().setActive(false);
				newDestroyed.addComponent<ModifyComponent>(rowNumber);
				break;
			}
			case '=':
			{
				// exit
				Entity& newExit(pEM->addEntity( ((LevelWidth * rowNumber) + (x + 1)), World, Exit ));
				newExit.addComponent<TransformComponent>(Vector2D(gameX, gameY), 0.0f, 1.0f);
				newExit.addComponent<ImageComponent>(pDE, pAM);
				newExit.getComponent<ImageComponent>().setImage("exit");
				newExit.addComponent<CollisionComponent>();
				newExit.addComponent<ModifyComponent>(rowNumber);
				break;
			}
			case '+':
			{
				// point
				Entity& newPoint(pEM->addEntity(((LevelWidth* rowNumber) + (x + 1)), World, Point ));
				newPoint.addComponent<TransformComponent>(Vector2D(gameX, gameY - (tileSize / 4)), 0.0f, 1.0f);
				newPoint.addComponent<ImageComponent>(pDE, pAM);
				newPoint.getComponent<ImageComponent>().setImage("point");
				newPoint.addComponent<CollisionComponent>();
				newPoint.addComponent<ModifyComponent>(rowNumber);
				break;
			}
			default:
				break;
			}
			gameX = gameX + tileSize;

			Entity& newEntity = pEM->getEntity(((LevelWidth * rowNumber) + (x + 1)));
			switch ((rowNumber + 1))
			{
			case 30:
				collidersVector30.emplace_back(&newEntity);
				break;
			case 29:
				collidersVector29.emplace_back(&newEntity);
				break;
			case 28:
				collidersVector28.emplace_back(&newEntity);
				break;
			case 27:
				collidersVector27.emplace_back(&newEntity);
				break;
			case 26:
				collidersVector26.emplace_back(&newEntity);
				break;
			case 25:
				collidersVector25.emplace_back(&newEntity);
				break;
			case 24:
				collidersVector24.emplace_back(&newEntity);
				break;
			case 23:
				collidersVector23.emplace_back(&newEntity);
				break;
			case 22:
				collidersVector22.emplace_back(&newEntity);
				break;
			case 21:
				collidersVector21.emplace_back(&newEntity);
				break;
			case 20:
				collidersVector20.emplace_back(&newEntity);
				break;
			case 19:
				collidersVector19.emplace_back(&newEntity);
				break;
			case 18:
				collidersVector18.emplace_back(&newEntity);
				break;
			case 17:
				collidersVector17.emplace_back(&newEntity);
				break;
			case 16:
				collidersVector16.emplace_back(&newEntity);
				break;
			case 15:
				collidersVector15.emplace_back(&newEntity);
				break;
			case 14:
				collidersVector14.emplace_back(&newEntity);
				break;
			case 13:
				collidersVector13.emplace_back(&newEntity);
				break;
			case 12:
				collidersVector12.emplace_back(&newEntity);
				break;
			case 11:
				collidersVector11.emplace_back(&newEntity);
				break;
			case 10:
				collidersVector10.emplace_back(&newEntity);
				break;
			case 9:
				collidersVector9.emplace_back(&newEntity);
				break;
			case 8:
				collidersVector8.emplace_back(&newEntity);
				break;
			case 7:
				collidersVector7.emplace_back(&newEntity);
				break;
			case 6:
				collidersVector6.emplace_back(&newEntity);
				break;
			case 5:
				collidersVector5.emplace_back(&newEntity);
				break;
			case 4:
				collidersVector4.emplace_back(&newEntity);
				break;
			case 3:
				collidersVector3.emplace_back(&newEntity);
				break;
			case 2:
				collidersVector2.emplace_back(&newEntity);
				break;
			case 1:
				collidersVector1.emplace_back(&newEntity);
				break;
			default:
				break;
			}

		}
		y++;
		gameY = gameY - tileSize;
		rowNumber--;

	}
	myFile.close();

	collidersMap = {
		{30, collidersVector30},
		{29, collidersVector29},
		{28, collidersVector28},
		{27, collidersVector27},
		{26, collidersVector26},
		{25, collidersVector25},
		{24, collidersVector24},
		{23, collidersVector23},
		{22, collidersVector22},
		{21, collidersVector21},
		{20, collidersVector20},
		{19, collidersVector19},
		{18, collidersVector18},
		{17, collidersVector17},
		{16, collidersVector16},
		{15, collidersVector15},
		{14, collidersVector14},
		{13, collidersVector13},
		{12, collidersVector12},
		{11, collidersVector11},
		{10, collidersVector10},
		{9, collidersVector9},
		{8, collidersVector8},
		{7, collidersVector7},
		{6, collidersVector6},
		{5, collidersVector5},
		{4, collidersVector4},
		{3, collidersVector3},
		{2, collidersVector2},
		{1, collidersVector1}
	};	
}

std::unordered_map<int, std::vector<Entity*>> LevelManager::getCollidersMap()
{
	return collidersMap;
}