// GameCode.cpp

#include <time.h>
#include <math.h>

#include "gamecode.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "myinputs.h"
#include "gametimer.h"
#include "errorlogger.h"
#include "shapes.h"
#include "camera.h"
#include "Components.h"
#include "AssetManager.h"
#include "LevelManager.h"
#include "Levels.h"

Game::Game()
{
	// No-op
}

Game::~Game()
{
	// No-op
}

Game Game::instance; // Singleton instance

// This is repeated, called every frame.
// It will run either Update( ), MainMenu() or PauseMenu() depending on the
// game state
ErrorType Game::Main()
{
	// Flip and clear the back buffer
	pDE->Flip();
	pDE->ClearBackBuffer();

	ErrorType err = SUCCESS;

	switch (m_currentState)
	{
	case MENU:
		err = MainMenu(); // Menu at start of game
		break;
	case LEVEL:
		err = LevelMenu(); // Menu for level select
		break;
	case PAUSED:
		err = PauseMenu(); // Player has paused the game
		break;
	case RUNNING: // Playing the actual game
		err = Update();
		break;
	case GAMEOVER:
		err = FAILURE; // Error return causes the window loop to exit
	default:
		// Not a valid state
		err = FAILURE; // Error return causes the window loop to exit
	}

	return err;
}

// Use to change the state of the game. Private function
void Game::ChangeState(GameState newState)
{
	// Very crude state system
	
	// Change the state
	m_currentState = newState;
	m_menuOption = 0;

	switch (m_currentState)
	{
	case MENU:
		// Not needed
		break;
	case LEVEL:
		// Not needed
		break;
	case PAUSED:
		// Not needed
		break;
	case RUNNING:
		gt.mdGameRate = 0.1f; // slows down the game for a few moments on start / resume
		break;
	}

}

// Starts the game engines - Draw Engine, Sound Engine, Input Engine - singletons
// This is called soon after the program runs
ErrorType Game::Setup(bool bFullScreen, HWND hwnd, HINSTANCE hinstance)
{
	// Create the engines - this should be done before creating other DDraw objects
	if (FAILED(MyDrawEngine::Start(hwnd, bFullScreen)))
	{
		ErrorLogger::Writeln(L"Failed to start MyDrawEngine");
		return FAILURE;
	}
	pDE = MyDrawEngine::GetInstance();
	if (FAILED(MySoundEngine::Start(hwnd)))
	{
		ErrorLogger::Writeln(L"Failed to start MySoundEngine");
		return FAILURE;
	}
	pDE->AddFont(L"Ariel", 48, false, false);
	pDE->AddFont(L"Ariel", 96, true, false);
	pSE = MySoundEngine::GetInstance();
	if (FAILED(MyInputs::Start(hinstance, hwnd)))
	{
		ErrorLogger::Writeln(L"Failed to start MyInputs");
		return FAILURE;
	}
	pInputs	= MyInputs::GetInstance();
	return (SUCCESS);
}

// Terminates the game engines - Draw Engine, Sound Engine, Input Engine
// This is called just before the program exits
void Game::Shutdown()

{
	// Any clean up code here

	// (engines must be terminated last)
	MyDrawEngine::Terminate();
	MySoundEngine::Terminate();
	MyInputs::Terminate();
}

// **********************************************************************************************
// Placeholder menus  ***************************************************************************
// **********************************************************************************************

// Called each frame when in the pause state. Manages the pause menu
// which is currently a basic placeholder
ErrorType Game::PauseMenu()
{
	pSE->StopAllSounds();

	// Code for a basic pause menu

	pDE->WriteText(450, 220, L"Paused", MyDrawEngine::WHITE, 1);

	const int NUMOPTIONS = 2;
	wchar_t options[NUMOPTIONS][11] = { L"Resume", L"Main menu" };

	// Display menu options
	for (int i = 0; i < NUMOPTIONS; i++)
	{
		int colour = MyDrawEngine::GREY; // If not selected, should be grey
		if (i == m_menuOption)
		{
			colour = MyDrawEngine::WHITE; // Current selection is white
		}
		pDE->WriteText(450, 300 + 50 * i, options[i], colour);
	}

	// Get user input
	pInputs->SampleKeyboard();

	// Move choice up and down
	if (pInputs->NewKeyPressed(DIK_UP) || pInputs->NewKeyPressed(DIK_W))
	{
		m_menuOption--;
	}
	if (pInputs->NewKeyPressed(DIK_DOWN) || pInputs->NewKeyPressed(DIK_S))
	{
		m_menuOption++;
	}
	if (m_menuOption < 0)
	{
		m_menuOption = 0;
	}
	else if (m_menuOption >= NUMOPTIONS)
	{
		m_menuOption = NUMOPTIONS - 1;
	}

	// If player chooses an option ....
	if (pInputs->NewKeyPressed(DIK_RETURN) || pInputs->NewKeyPressed(DIK_SPACE))
	{
		if (m_menuOption == 0) // Resume
		{
			ChangeState(RUNNING); // Go back to running the game
		}
		if (m_menuOption == 1) // Quit
		{
			EndOfGame();	   // Clear up the game
			ChangeState(MENU); // Go back to the menu
		}
	}

	return SUCCESS;
}

// Called each frame when in the level state. Manages the level selector menu
ErrorType Game::LevelMenu()
{
	pSE->StopAllSounds();

	// Code for a basic  menu

	pDE->WriteText(450, 220, L"Level Select", MyDrawEngine::WHITE, 1);

	const int NUMOPTIONS = 4;
	wchar_t options[NUMOPTIONS][15] = { L"Level 0", L"Level 1", L"Level 2", L"Main Menu" };

	// Display the options
	for (int i = 0; i < NUMOPTIONS; i++)
	{
		int colour = MyDrawEngine::GREY;
		if (i == m_menuOption)
		{
			colour = MyDrawEngine::WHITE;
		}
		pDE->WriteText(450, 300 + 50 * i, options[i], colour);
	}

	// Get keyboard input
	pInputs->SampleKeyboard();

	if (pInputs->NewKeyPressed(DIK_UP) || pInputs->NewKeyPressed(DIK_W))
	{
		m_menuOption--;
	}
	if (pInputs->NewKeyPressed(DIK_DOWN) || pInputs->NewKeyPressed(DIK_S))
	{
		m_menuOption++;
	}
	if (m_menuOption < 0)
	{
		m_menuOption = 0;
	}
	else if (m_menuOption >= NUMOPTIONS)
	{
		m_menuOption = NUMOPTIONS - 1;
	}

	// User selects an option
	if (pInputs->NewKeyPressed(DIK_RETURN) || pInputs->NewKeyPressed(DIK_SPACE))
	{
		if (m_menuOption == 0) // Play
		{
			StartOfGame(Level0);		  // Level select
			ChangeState(RUNNING); // Move to level select
		}
		if (m_menuOption == 1) // Play
		{
			StartOfGame(Level1);		  // Level select
			ChangeState(RUNNING); // Move to level select
		}
		if (m_menuOption == 2) // Play
		{
			StartOfGame(Level2);		  // Level select
			ChangeState(RUNNING); // Move to level select
		}
		if (m_menuOption == 3) // Menu
		{
			ChangeState(MENU); // Go back to the menu
		}
	}

	return SUCCESS;
}

// Called each frame when in the menu state. Manages the menu
// which is currently a basic placeholder
ErrorType Game::MainMenu()
{
	pSE->StopAllSounds();

	pDE->WriteText(450, 220, L"Main Menu", MyDrawEngine::WHITE, 1);

	const int NUMOPTIONS = 2;
	wchar_t options[NUMOPTIONS][15] = {L"Start game", L"Exit"};

	// Display the options
	for (int i = 0; i < NUMOPTIONS; i++)
	{
		int colour = MyDrawEngine::GREY;
		if (i == m_menuOption)
		{
			colour = MyDrawEngine::WHITE;
		}
		pDE->WriteText(450, 300 + 50 * i, options[i], colour);
	}

	// Get keyboard input
	pInputs->SampleKeyboard();

	if (pInputs->NewKeyPressed(DIK_UP) || pInputs->NewKeyPressed(DIK_W))
	{
		m_menuOption--;
	}
	if (pInputs->NewKeyPressed(DIK_DOWN) || pInputs->NewKeyPressed(DIK_S))
	{
		m_menuOption++;
	}
	if (m_menuOption < 0)
	{
		m_menuOption = 0;
	}
	else if (m_menuOption >= NUMOPTIONS)
	{
		m_menuOption = NUMOPTIONS - 1;
	}

	// User selects an option
	if (pInputs->NewKeyPressed(DIK_RETURN) || pInputs->NewKeyPressed(DIK_SPACE))
	{
		if (m_menuOption == 0) // Play
		{
			LevelMenu();		  // Level select
			ChangeState(LEVEL); // Move to level select
		}

		if (m_menuOption == 1) // Quit
		{
			EndOfGame();
			ChangeState(GAMEOVER);
		}
	}

	return SUCCESS;
}

// **********************************************************************************************
// The game !!! *********************************************************************************
// **********************************************************************************************

// game
bool slowStarted;
double slowTime;
bool won;
bool lost;
bool gameStarted;
bool finalSFX;
bool backgroudMusicPlaying;

// game area
float zoom;
float playerY;
float offset;
float gameAreaWidth;
float gameAreaHeight;
float midX;
float midY;
Rectangle2D topRectangle;
Rectangle2D bottomRectangle;
Rectangle2D leftRectangle;
Rectangle2D rightRectangle;

// Asset Manager + Level Manager
AssetManager assetManager;
LevelManager levelManager;

// ECS manager + vital entites
EntityManager entityManager;
Entity* background;
Entity* player;
std::unordered_map<int, std::vector<Entity*>> collidersMap;

// UI
const wchar_t* FPSlabel;
const wchar_t* scoreLabel;
const wchar_t* welcomeMessage;
const wchar_t* winMessage;
const wchar_t* loseMessage;


// Called at the start of the game - when changing state from LEVEL to RUNNING
// Use this to initialise the core game
ErrorType Game::StartOfGame(Levels selectedLevel)
{
	// Code to setup your game *********************************************
	// **********************************************************************

	// game
	slowStarted = false;
	slowTime = 0.0;
	won = false;
	lost = false;
	gameStarted = false;
	finalSFX = false;
	backgroudMusicPlaying = false;


	// setup camera + game area
	pDE->UseCamera(true);
	pDE->theCamera.PlaceAt(Vector2D(0, 0));
	zoom = pDE->GetScreenHeight() / 800.0f;
	pDE->theCamera.SetZoom(zoom);

	playerY = 0;
	gameAreaWidth = 768;
	gameAreaHeight = 576;
	gameAreaWidth = pDE->theCamera.Transform(gameAreaWidth);
	gameAreaHeight = pDE->theCamera.Transform(gameAreaHeight);
	midX = pDE->GetScreenWidth() / 2.0f;
	midY = pDE->GetScreenHeight() / 2.0f;
	topRectangle.PlaceAt(Vector2D((midX - gameAreaWidth / 2.0f) - 0.5f, ((midY - gameAreaHeight / 2.0f) - 1.5f)), Vector2D((midX + gameAreaWidth / 2.0f) + 0.5f, -pDE->GetScreenHeight()));
	bottomRectangle.PlaceAt(Vector2D((midX - gameAreaWidth / 2.0f) - 0.5f, ((midY + gameAreaHeight / 2.0f) + 1.5f)), Vector2D((midX + gameAreaWidth / 2.0f) + 0.5f, pDE->GetScreenHeight()));
	leftRectangle.PlaceAt(Vector2D(((midX - gameAreaWidth / 2.0f) - 1.5f), pDE->GetScreenHeight()), Vector2D(-pDE->GetScreenWidth(), -pDE->GetScreenHeight()));
	rightRectangle.PlaceAt(Vector2D(((midX + gameAreaWidth / 2.0f) + 1.5f), pDE->GetScreenHeight()), Vector2D(pDE->GetScreenWidth(), -pDE->GetScreenHeight()));


	// UI
	FPSlabel = L"FPS:";
	scoreLabel = L"Score:";
	welcomeMessage = L"Press ENTER To Start";
	winMessage = L"YOU WIN!";
	loseMessage = L"YOU LOSE!";


	// load assets
	assetManager.init(pDE, pSE);
	assetManager.loadAll();


	// load level
	levelManager.init(selectedLevel);
	levelManager.loadLevel(&entityManager, pDE, &assetManager);
	collidersMap = levelManager.getCollidersMap();


	//background entity + components
	Entity& newBackground = entityManager.getEntity(-1);
	background = &newBackground;
	background->addComponent<TransformComponent>(Vector2D(0, 0), 0.0f, 1.0f);
	background->addComponent<ImageComponent>(pDE, &assetManager);
	background->getComponent<ImageComponent>().setImage("backgroundImage");
	background->addComponent<SoundComponent>(pSE, &assetManager);
	background->getComponent<SoundComponent>().setSound("backgroundMusic", true);
	backgroudMusicPlaying = false;


	// player enitity + components
	Entity& newPlayer = entityManager.getEntity(0);
	player = &newPlayer;
	player->addComponent<GameComponent>();
	player->addComponent<TransformComponent>(Vector2D(0, 5), 0.0f, 1.0f);
	player->addComponent<ImageComponent>(pDE, &assetManager);
	player->addComponent<SoundComponent>(pSE, &assetManager);
	player->addComponent<PhysicsComponent>(256.0f, 6144.0f, -128.0f);
	player->addComponent<AnimationComponent>();
	player->addComponent<CollisionComponent>();
	player->addComponent<InputComponent>(pInputs);

	gt.setMinimumFrameTime(0.0164);
	gt.mark();
	gt.mark();

	// send the frame time to each entity
	entityManager.updateTime(gt.mdFrameTime);

	return SUCCESS;
}

// Called each frame when in the RUNNING state.
// Checks for user pressing escape (which puts the game in the PAUSED state)
// Flips and clears the back buffer
// Gameplay programmer will develop this to create an actual game
ErrorType Game::Update()
{
	// if ESC pressed -> pause game
	static bool escapepressed = true;
	if (KEYPRESSED(VK_ESCAPE))
	{
		if (!escapepressed)
		{
			ChangeState(PAUSED);
		}
		escapepressed = true;
	}
	else
	{
		escapepressed = false;
	}

	// Your code goes here *************************************************
	// *********************************************************************

	// ensure starting or resuming the game does not mess with the physics
	// also continues to play the background music
	if (gt.mdGameRate != 1)
	{
		if (slowStarted == false)
		{
			slowStarted = true;
			slowTime = 0.5;
		}
		else if (slowStarted == true)
		{
			if (slowTime > 0)
			{
				slowTime = slowTime - gt.mdFrameTime;
			}
			else if (slowTime <= 0)
			{
				slowStarted = false;
				slowTime = 0.0;
				gt.mdGameRate = 1;
				backgroudMusicPlaying = false;
				background->getComponent<SoundComponent>().setSound("backgroundMusic", true);
			}
		}
	}


	// play background music
	if (gt.mdGameRate == 1)
	{
		if (backgroudMusicPlaying == false)
		{
			background->getComponent<SoundComponent>().play();
			backgroudMusicPlaying = true;
		}
	}

	// check if the player uses the keyboard
	player->getComponent<InputComponent>().checkForInputs();


	// check if entities need to be removed
	// update remaining entities
	entityManager.removeInactiveEntities();
	entityManager.update();


	// get player position
	playerY = player->getComponent<TransformComponent>().getPosition().YValue;


	// check if player has collided with anything
	// narrow number of entities to check by getting 24/36 entities closest to player
	// more efficient than checking all 360 entities every frame
	if (player->getComponent<CollisionComponent>().isActive() == true)
	{
		if (playerY >= -200 && playerY < -136)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(30));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(29));
		}
		if (playerY >= -136 && playerY < -72)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(30));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(29));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(28));
		}
		if (playerY >= -72 && playerY < -8)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(29));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(28));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(27));
		}
		if (playerY >= -8 && playerY < 56)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(28));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(27));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(26));
		}
		if (playerY >= 56 && playerY < 120)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(27));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(26));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(25));
		}
		if (playerY >= 120 && playerY < 184)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(26));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(25));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(24));
		}
		if (playerY >= 184 && playerY < 248)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(25));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(24));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(23));
		}
		if (playerY >= 248 && playerY < 312)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(24));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(23));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(22));
		}
		if (playerY >= 312 && playerY < 376)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(23));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(22));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(21));
		}
		if (playerY >= 376 && playerY < 440)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(22));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(21));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(20));
		}
		if (playerY >= 440 && playerY < 504)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(21));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(20));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(19));
		}
		if (playerY >= 504 && playerY < 568)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(20));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(19));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(18));
		}
		if (playerY >= 568 && playerY < 632)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(19));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(18));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(17));
		}
		if (playerY >= 632 && playerY < 696)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(18));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(17));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(16));
		}
		if (playerY >= 696 && playerY < 760)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(17));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(16));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(15));
		}
		if (playerY >= 760 && playerY < 824)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(16));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(15));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(14));
		}
		if (playerY >= 824 && playerY < 888)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(15));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(14));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(13));
		}
		if (playerY >= 888 && playerY < 952)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(14));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(13));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(12));
		}
		if (playerY >= 952 && playerY < 1016)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(13));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(12));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(11));
		}
		if (playerY >= 1016 && playerY < 1080)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(12));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(11));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(10));
		}
		if (playerY >= 1080 && playerY < 1144)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(11));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(10));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(9));
		}
		if (playerY >= 1144 && playerY < 1208)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(10));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(9));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(8));
		}
		if (playerY >= 1208 && playerY < 1272)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(9));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(8));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(7));
		}
		if (playerY >= 1272 && playerY < 1336)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(8));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(7));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(6));
		}
		if (playerY >= 1336 && playerY < 1400)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(7));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(6));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(5));
		}
		if (playerY >= 1400 && playerY < 1464)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(6));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(5));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(4));
		}
		if (playerY >= 1464 && playerY < 1528)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(5));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(4));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(3));
		}
		if (playerY >= 1528 && playerY < 1592)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(4));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(3));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(2));
		}
		if (playerY >= 1592 && playerY < 1656)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(3));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(2));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(1));
		}
		if (playerY >= 1656 && playerY < 1720)
		{
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(2));
			player->getComponent<CollisionComponent>().checkCollision(collidersMap.at(1));
		}
	}


	// check if player has won or lost
	if (player->getComponent<GameComponent>().getWin() == true)
	{
		// if player has won
		won = true;
		lost = false;
		player->getComponent<PhysicsComponent>().setActive(false);
		player->getComponent<TransformComponent>().addPosition(Vector2D(0, 1));
		player->getComponent<AnimationComponent>().playerWin();
		player->getComponent<SoundComponent>().setSound("playerWin");
		if (finalSFX == false)
		{
			player->getComponent<SoundComponent>().play();
			finalSFX = true;
		}
	}
	if (player->getComponent<GameComponent>().getLose() == true)
	{
		// if player has lost
		won = false;
		lost = true;
		player->getComponent<PhysicsComponent>().setActive(false);
		player->getComponent<TransformComponent>().addPosition(Vector2D(0, -1));
		player->getComponent<AnimationComponent>().playerLose();
		player->getComponent<SoundComponent>().setSound("playerDeath");
		if (finalSFX == false)
		{
			player->getComponent<SoundComponent>().play();
			finalSFX = true;
		}
	}


	// position camera
	// camera follows player if the player is within the level area
	// if the player is outside the level area, the camera stays at the edge of the level area
	// if the player is at the bottom of the level, the player is below the center of the screen
	// if the player is at the top of the level, the player is above the center of the screen
	// if the player is between the inter quatile of the level, the player is slowly moved from -192 to 192 of the camera coordinates
	if (playerY < -104)
	{
		pDE->theCamera.PlaceAt(Vector2D(0, -88));
	}
	if (playerY >= -104 && playerY < 440)
	{
		pDE->theCamera.PlaceAt(Vector2D(0, -(playerY + 192)));
	}
	if (playerY >= 440 && playerY < 1320)
	{
		offset = ((((2.0f / 3.0f) * -576.0f) / ((1320.0f + 440.0f) / 2.0f)) * (playerY - ((1320.0f + 440.0f) / 2.0f)));
		pDE->theCamera.PlaceAt(Vector2D(0, -(playerY + offset)));
	}
	if (playerY >= 1320 && playerY < 1624)
	{
		pDE->theCamera.PlaceAt(Vector2D(0, -(playerY - 192)));
	}
	if (playerY >= 1624)
	{
		pDE->theCamera.PlaceAt(Vector2D(0, -1432));
	}
	background->getComponent<TransformComponent>().setPosition(pDE->theCamera.ReverseTransform(Vector2D(midX,midY)));


	// draw all entities
	for (auto& e : entityManager.getAllEntities())
	{
		if (e->hasComponent<ImageComponent>() == true)
		{
			e->getComponent<ImageComponent>().draw();
		}
	}


	// draw game area box 768x576 - 64x64 tiles fit 12x9
	pDE->DrawLine(pDE->theCamera.ReverseTransform(Vector2D(midX - gameAreaWidth / 2.0f, (midY - gameAreaHeight / 2.0f)-1)), pDE->theCamera.ReverseTransform(Vector2D(midX + gameAreaWidth / 2.0f, (midY - gameAreaHeight / 2.0f)-1)), MyDrawEngine::DARKBLUE); // TOP
	pDE->DrawLine(pDE->theCamera.ReverseTransform(Vector2D((midX - gameAreaWidth / 2.0f)-0.5f, midY - gameAreaHeight / 2.0f)), pDE->theCamera.ReverseTransform(Vector2D((midX - gameAreaWidth / 2.0f)-0.5f, midY + gameAreaHeight / 2.0f)), MyDrawEngine::DARKBLUE); // LEFT
	pDE->DrawLine(pDE->theCamera.ReverseTransform(Vector2D((midX + gameAreaWidth / 2.0f)+0.5f, midY - gameAreaHeight / 2.0f)), pDE->theCamera.ReverseTransform(Vector2D((midX + gameAreaWidth / 2.0f)+0.5f, midY + gameAreaHeight / 2.0f)), MyDrawEngine::DARKBLUE); // RIGHT
	pDE->DrawLine(pDE->theCamera.ReverseTransform(Vector2D(midX - gameAreaWidth / 2.0f, (midY + gameAreaHeight / 2.0f)+1)), pDE->theCamera.ReverseTransform(Vector2D(midX + gameAreaWidth / 2.0f, (midY + gameAreaHeight / 2.0f)+1)), MyDrawEngine::DARKBLUE); // BOTTOM
	pDE->FillRect(pDE->theCamera.ReverseTransform(topRectangle), MyDrawEngine::BLACK, 0.0f);
	pDE->FillRect(pDE->theCamera.ReverseTransform(bottomRectangle), MyDrawEngine::BLACK, 0.0f);
	pDE->FillRect(pDE->theCamera.ReverseTransform(leftRectangle), MyDrawEngine::BLACK, 0.0f);
	pDE->FillRect(pDE->theCamera.ReverseTransform(rightRectangle), MyDrawEngine::BLACK, 0.0f);
	

	// welcome message
	if (player->getComponent<InputComponent>().getFirstInput() == false)
	{
		pDE->WriteText(pDE->theCamera.ReverseTransform(Vector2D(midX - 192, midY + gameAreaHeight / 2.0f)), welcomeMessage, MyDrawEngine::WHITE, 1);
	}


	// start game - if the first input is pressed->activate the modify component
	// slowly destroys the level from the bottom to the top - chases the player
	if (player->getComponent<InputComponent>().getFirstInput() == true)
	{
		if (gameStarted == false)
		{
			for (auto& e : entityManager.getAllEntities())
			{
				if (e->hasComponent<ModifyComponent>() == true)
				{
					e->getComponent<ModifyComponent>().setActive(true);
				}
			}
		}
		gameStarted = true;
	}


	// win message
	if (won == true)
	{
		pDE->WriteText(pDE->theCamera.ReverseTransform(Vector2D(midX - 96, midY + gameAreaHeight / 2.0f)), winMessage, MyDrawEngine::WHITE, 1);
	}


	// lose message
	if (lost == true)
	{
		pDE->WriteText(pDE->theCamera.ReverseTransform(Vector2D(midX - 96, midY + gameAreaHeight / 2.0f)), loseMessage, MyDrawEngine::WHITE, 1);
	}

	// write score to screen
	int score = player->getComponent<GameComponent>().getScore();
	pDE->WriteText(pDE->theCamera.ReverseTransform(Vector2D((midX + gameAreaWidth / 2.0f) + 10, midY - gameAreaHeight / 2.25f)), scoreLabel, MyDrawEngine::WHITE);
	pDE->WriteInt(pDE->theCamera.ReverseTransform(Vector2D((midX + gameAreaWidth / 2.0f) + 70, midY - gameAreaHeight / 2.25f)), score, MyDrawEngine::WHITE);


	// write fps to screen
	int FPS = (1 / gt.mdFrameTime);
	pDE->WriteText(pDE->theCamera.ReverseTransform(Vector2D((midX - gameAreaWidth / 2.0f)-80, midY - gameAreaHeight / 2.25f)), FPSlabel, MyDrawEngine::WHITE);
	pDE->WriteInt(pDE->theCamera.ReverseTransform(Vector2D((midX - gameAreaWidth / 2.0f)-35, midY - gameAreaHeight / 2.25f)), FPS, MyDrawEngine::WHITE);


	// write countdown to screen
	if (slowTime > 0)
	{
		pDE->WriteInt(pDE->theCamera.ReverseTransform(Vector2D(midX - 24, midY - 48)), (10.0 * slowTime), MyDrawEngine::WHITE, 2);
	}

	gt.mark();

	// send the frame time to each entity
	entityManager.updateTime(gt.mdFrameTime);

	// *********************************************************************
	// *********************************************************************

	return SUCCESS;
}

// Called when the player ends the game
// Currently this is done from the PAUSED state, when returning to the main menu
// but could be done by the gameplay programmer in other situations
// This will be used by the gameplay programmer to clean up
ErrorType Game::EndOfGame()
// called when the game ends by returning to main menu
{
	// Add code here to tidy up ********************************************
	// *********************************************************************

	// clear all entities
	// collidersVector.clear();
	entityManager.deleteAll();
	entityManager.removeInactiveEntities();
	assetManager.clearAll();

	return SUCCESS;
}