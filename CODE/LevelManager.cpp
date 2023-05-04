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
#include "AssetManager.h"

void LevelManager::init(Levels selectedLevel)
{
	currentLevel = selectedLevel;
	switch (currentLevel)
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
				newEmpty.addComponent<TransformComponent>(Vector2D(gameX, gameY), 0, 1);
				newEmpty.addComponent<ImageComponent>(pDE, pAM);
				// collision component - TODO - used to check if the player is collidng with the entity
				// modify component - TODO - used to change worldType to 'destroyedEdge' or 'destroyed'
				// modify component - needs rowNumber passed in to determine when to change it
				break;
			}
			case '-':
			{
				// platform
				Entity& newPlatform(pEM->addEntity( ((LevelWidth * rowNumber) + (x + 1)), World, Platform ));
				newPlatform.addComponent<TransformComponent>(Vector2D(gameX, gameY), 0, 1);
				newPlatform.addComponent<ImageComponent>(pDE, pAM);
				newPlatform.getComponent<ImageComponent>().setImage("platform");
				// collision component - TODO - used to check if the player is collidng with the entity
				// modify component - TODO - used to change worldType to 'destroyedEdge' or 'destroyed'
				// modify component - needs rowNumber passed in to determine when to change it
				break;
			}
			case '^':
			{
				// trappedPlatform
				Entity& newTrappedPlatform(pEM->addEntity( ((LevelWidth * rowNumber) + (x + 1)), World, TrappedPlatform ));
				newTrappedPlatform.addComponent<TransformComponent>(Vector2D(gameX, gameY), 0, 1);
				newTrappedPlatform.addComponent<ImageComponent>(pDE, pAM);
				newTrappedPlatform.getComponent<ImageComponent>().setImage("trappedPlatform");
				// animation component - TODO - used to rotate the component
				// collision component - TODO - used to check if the player is collidng with the entity
				// modify component - TODO - used to change worldType to 'destroyedEdge' or 'destroyed'
				// modify component - needs rowNumber passed in to determine when to change it
				break;
			}
			case 'H':
			{
				// trapHorizontal
				Entity& newTrapHorizontal(pEM->addEntity( ((LevelWidth * rowNumber) + (x + 1)), World, Trap ));
				newTrapHorizontal.addComponent<TransformComponent>(Vector2D(gameX, gameY), 0, 1);
				newTrapHorizontal.addComponent<ImageComponent>(pDE, pAM);
				newTrapHorizontal.getComponent<ImageComponent>().setImage("trap");
				// collision component - TODO - used to check if the player is collidng with the entity
				// modify component - TODO - used to change worldType to 'destroyedEdge' or 'destroyed'
				// modify component - needs rowNumber passed in to determine when to change it
				break;
			}
			case 'I':
			{
				// trapHorizontal
				Entity& newTrapVertical(pEM->addEntity( ((LevelWidth * rowNumber) + (x + 1)), World, Trap ));
				newTrapVertical.addComponent<TransformComponent>(Vector2D(gameX, gameY), 1.571f, 1);
				newTrapVertical.addComponent<ImageComponent>(pDE, pAM);
				newTrapVertical.getComponent<ImageComponent>().setImage("trap");
				// collision component - TODO - used to check if the player is collidng with the entity
				// modify component - TODO - used to change worldType to 'destroyedEdge' or 'destroyed'
				// modify component - needs rowNumber passed in to determine when to change it
				break;
			}
			case '~':
			{
				// destroyedEdge
				Entity& newDestroyedEdge(pEM->addEntity( ((LevelWidth * rowNumber) + (x + 1)), World, DestroyedEdge ));
				newDestroyedEdge.addComponent<TransformComponent>(Vector2D(gameX, gameY), 0, 1);
				newDestroyedEdge.addComponent<ImageComponent>(pDE, pAM);
				newDestroyedEdge.getComponent<ImageComponent>().setImage("destroyedEdge");
				// collision component - TODO - used to check if the player is collidng with the entity
				// modify component - TODO - used to change worldType to 'destroyedEdge' or 'destroyed'
				// modify component - needs rowNumber passed in to determine when to change it
				break;
			}
			case 'x':
			{
				// destroyed
				Entity& newDestroyed(pEM->addEntity( ((LevelWidth * rowNumber) + (x + 1)), World, Destroyed ));
				newDestroyed.addComponent<TransformComponent>(Vector2D(gameX, gameY), 0, 1);
				newDestroyed.addComponent<ImageComponent>(pDE, pAM);
				newDestroyed.getComponent<ImageComponent>().setImage("destroyed");
				// collision component - TODO - used to check if the player is collidng with the entity
				// modify component - TODO - used to change worldType to 'destroyedEdge' or 'destroyed'
				// modify component - needs rowNumber passed in to determine when to change it
				break;
			}
			case '=':
			{
				// exit
				Entity& newExit(pEM->addEntity( ((LevelWidth * rowNumber) + (x + 1)), World, Exit ));
				newExit.addComponent<TransformComponent>(Vector2D(gameX, gameY), 0, 1);
				newExit.addComponent<ImageComponent>(pDE, pAM);
				newExit.getComponent<ImageComponent>().setImage("exit");
				// collision component - TODO - used to check if the player is collidng with the entity
				// modify component - TODO - used to change worldType to 'destroyedEdge' or 'destroyed'
				// modify component - needs rowNumber passed in to determine when to change it
				break;
			}
			case '+':
			{
				// point
				Entity& newPoint(pEM->addEntity(((LevelWidth* rowNumber) + (x + 1)), World, Point ));
				newPoint.addComponent<TransformComponent>(Vector2D(gameX, gameY - (tileSize / 4)), 0, 1);
				newPoint.addComponent<ImageComponent>(pDE, pAM);
				newPoint.getComponent<ImageComponent>().setImage("point");
				// collision component - TODO - used to check if the player is collidng with the entity
				// if collided with, change to empty and change positionY (+tileSize/4) - change to destoyed later
				// modify component - TODO - used to change worldType to 'destroyedEdge' or 'destroyed'
				// modify component - needs rowNumber passed in to determine when to change it

				break;
			}
			default:
				break;
			}
			gameX = gameX + tileSize;
		}
		y++;
		gameY = gameY - tileSize;
		rowNumber--;

	}
	myFile.close();
}