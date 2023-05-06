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
	// Close old state
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
		// Not needed
		break;
	}

	// Change the state
	m_currentState = newState;
	m_menuOption = 0;

	// Transition to new state
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
		// Not needed
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

	pDE->WriteText(450, 220, L"Paused", MyDrawEngine::WHITE);

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

	pDE->WriteText(450, 220, L"Level Select", MyDrawEngine::WHITE);

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

	pDE->WriteText(450, 220, L"Main menu", MyDrawEngine::WHITE);

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
bool won = false;
bool lost = false;

// game area
float playerY;
float offset;
float gameAreaWidth;
float gameAreaHeight;
float midX;
float midY;
Rectangle2D topRectangle;
Rectangle2D bottomRectangle;

// Asset Manager + Level Manager
AssetManager assetManager;
LevelManager levelManager;

// ECS manager + vital entites
EntityManager entityManager;
Entity* background;
Entity* player;
std::vector<Entity*> collidersVector;


// Called at the start of the game - when changing state from LEVEL to RUNNING
// Use this to initialise the core game
ErrorType Game::StartOfGame(Levels selectedLevel)
{
	// Code to setup your game *********************************************
	// **********************************************************************

	// load assets
	assetManager.init(pDE, pSE);
	
	assetManager.LoadCharacterImage(L"assets/character/image/smiley.png", "playerSmiley");
	assetManager.LoadCharacterImage(L"assets/character/image/scared.png", "playerScared");
	assetManager.LoadCharacterImage(L"assets/character/image/confused.png", "playerConfused");
	assetManager.LoadCharacterImage(L"assets/character/image/dead.png", "playerDead");

	assetManager.LoadCharacterSound(L"assets/character/sound/land.wav", "playerLand");
	assetManager.LoadCharacterSound(L"assets/character/sound/point.wav", "playerPoint");
	assetManager.LoadCharacterSound(L"assets/character/sound/win.wav", "playerWin");
	assetManager.LoadCharacterSound(L"assets/character/sound/death.wav", "playerDeath");

	// assetManager.LoadBackgroundImage(L"assets/background/image/background.png", "backgroundImage0");

	// assetManager.LoadBackgroundMusic(L"assets/background/music/level0.wav", "backgroundMusic0");

	assetManager.LoadWorldImage(L"assets/world/image/platform.png", "platform");
	assetManager.LoadWorldImage(L"assets/world/image/trappedPlatform.png", "trappedPlatform");
	assetManager.LoadWorldImage(L"assets/world/image/trap.png", "trap");
	assetManager.LoadWorldImage(L"assets/world/image/destroyed.png", "destroyed");
	assetManager.LoadWorldImage(L"assets/world/image/destroyedEdge.png", "destroyedEdge");
	assetManager.LoadWorldImage(L"assets/world/image/exit.png", "exit");
	assetManager.LoadWorldImage(L"assets/world/image/point.png", "point");

	// assetManager.LoadWorldSound(L"assets/world/image/TODO0.wav", "TODO0");


	// load level
	levelManager.init(selectedLevel);
	levelManager.loadLevel(&entityManager, pDE, &assetManager);


	//background entity + components
	Entity& newBackground = entityManager.getEntity(-1);
	background = &newBackground;
	background->addComponent<TransformComponent>(Vector2D(0, 0), 0.0f, 1.0f);
	background->addComponent<ImageComponent>(pDE, &assetManager);
	background->getComponent<ImageComponent>().setImage("empty");
	background->addComponent<SoundComponent>(pSE, &assetManager);


	// player enitity + components
	Entity& newPlayer = entityManager.getEntity(0);
	player = &newPlayer;
	player->addComponent<GameComponent>();
	player->addComponent<TransformComponent>(Vector2D(0, 1), 0.0f, 1.0f);
	player->addComponent<ImageComponent>(pDE, &assetManager);
	player->addComponent<SoundComponent>(pSE, &assetManager);
	player->addComponent<PhysicsComponent>(256.0f, 10240.0f, -128.0f);
	player->addComponent<AnimationComponent>();
	player->addComponent<CollisionComponent>();
	player->addComponent<InputComponent>(pInputs);


	// setup collision
	for (auto& e : entityManager.getAllEntities())
	{
		if (e->getID() != -1 && e->getID() != 0 && e->hasComponent<CollisionComponent>() == true)
		{
			Entity& collider = *e;
			collidersVector.emplace_back(&collider);
		}
	}


	// setup camera + game area
	pDE->UseCamera(true);
	pDE->theCamera.PlaceAt(Vector2D(0, player->getComponent<TransformComponent>().getPosition().YValue + 192));
	pDE->theCamera.SetZoom(pDE->GetScreenHeight() / 800.0f);

	playerY = player->getComponent<TransformComponent>().getPosition().YValue;
	gameAreaWidth = 768;
	gameAreaHeight = 576;
	gameAreaWidth = pDE->theCamera.Transform(gameAreaWidth);
	gameAreaHeight = pDE->theCamera.Transform(gameAreaHeight);
	midX = pDE->GetScreenWidth() / 2.0f;
	midY = pDE->GetScreenHeight() / 2.0f;
	topRectangle.PlaceAt(Vector2D((midX - gameAreaWidth / 2.0f)-0.5f, ((midY - gameAreaHeight / 2.0f)-1.5f)), Vector2D((midX + gameAreaWidth / 2.0f)+0.5f, -pDE->GetScreenHeight()));
	bottomRectangle.PlaceAt(Vector2D((midX - gameAreaWidth / 2.0f)-0.5f, ((midY + gameAreaHeight / 2.0f)+1.5f)), Vector2D((midX + gameAreaWidth / 2.0f)+0.5f, pDE->GetScreenHeight()));


	gt.mark();
	gt.mark();

	entityManager.updateTime(gt.mdFrameTime);

	return SUCCESS;
}

// Called each frame when in the RUNNING state.
// Checks for user pressing escape (which puts the game in the PAUSED state)
// Flips and clears the back buffer
// Gameplay programmer will develop this to create an actual game
ErrorType Game::Update()
{
	// check for input
	pInputs->SampleKeyboard();

	// if ESC pressed -> pause game
	static bool escapepressed = true;
	if (KEYPRESSED(VK_ESCAPE))
	{
		if (!escapepressed)
			ChangeState(PAUSED);
		escapepressed = true;
	}
	else
	{
		escapepressed = false;
	}

	// Your code goes here *************************************************
	// *********************************************************************

	player->getComponent<InputComponent>().checkForInputs();

	// check if entities need to be removed
	// update remaining entities
	entityManager.refresh();
	entityManager.update();

	player->getComponent<CollisionComponent>().checkCollision(collidersVector);


	// check if player has won or lost
	if (player->getComponent<GameComponent>().getWin() == true)
	{
		// win code
		won = true;
	}
	if (player->getComponent<GameComponent>().getLose() == true)
	{
		// lose code
		lost = true;
	}


	// position camera
	playerY = player->getComponent<TransformComponent>().getPosition().YValue;
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


	// draw all entities
	entityManager.draw();


	// draw game area box 768x576 - 64x64 tiles fit 12x9
	pDE->DrawLine(pDE->theCamera.ReverseTransform(Vector2D(midX - gameAreaWidth / 2.0f, (midY - gameAreaHeight / 2.0f)-1)), pDE->theCamera.ReverseTransform(Vector2D(midX + gameAreaWidth / 2.0f, (midY - gameAreaHeight / 2.0f)-1)), MyDrawEngine::DARKBLUE); // TOP
	pDE->DrawLine(pDE->theCamera.ReverseTransform(Vector2D((midX - gameAreaWidth / 2.0f)-1, midY - gameAreaHeight / 2.0f)), pDE->theCamera.ReverseTransform(Vector2D((midX - gameAreaWidth / 2.0f)-1, midY + gameAreaHeight / 2.0f)), MyDrawEngine::DARKBLUE); // LEFT
	pDE->DrawLine(pDE->theCamera.ReverseTransform(Vector2D((midX + gameAreaWidth / 2.0f)+1, midY - gameAreaHeight / 2.0f)), pDE->theCamera.ReverseTransform(Vector2D((midX + gameAreaWidth / 2.0f)+1, midY + gameAreaHeight / 2.0f)), MyDrawEngine::DARKBLUE); // RIGHT
	pDE->DrawLine(pDE->theCamera.ReverseTransform(Vector2D(midX - gameAreaWidth / 2.0f, (midY + gameAreaHeight / 2.0f)+1)), pDE->theCamera.ReverseTransform(Vector2D(midX + gameAreaWidth / 2.0f, (midY + gameAreaHeight / 2.0f)+1)), MyDrawEngine::DARKBLUE); // BOTTOM
	pDE->FillRect(pDE->theCamera.ReverseTransform(topRectangle), MyDrawEngine::BLACK, 0.0f);
	pDE->FillRect(pDE->theCamera.ReverseTransform(bottomRectangle), MyDrawEngine::BLACK, 0.0f);
	

	// welcome message
	bool started = false;;
	const wchar_t welcomeMessage[] = L"Press ENTER To Start";
	if (player->getComponent<InputComponent>().getFirstInput() == false)
	{
		pDE->WriteText(pDE->theCamera.ReverseTransform(Vector2D(midX - 64, midY + gameAreaHeight / 2.0f)), welcomeMessage, MyDrawEngine::WHITE);
	}
	if (player->getComponent<InputComponent>().getFirstInput() == true)
	{
		if (started == false)
		{
			for (auto& e : entityManager.getAllEntities())
			{
				if (e->hasComponent<ModifyComponent>())
				{
					e->getComponent<ModifyComponent>().setActive(true);
				}
			}
		}
		started = true;
	}


	// win message
	const wchar_t winMessage[] = L"You WIN!";
	if (won == true)
	{
		pDE->WriteText(pDE->theCamera.ReverseTransform(Vector2D(midX - 64, midY + gameAreaHeight / 2.0f)), winMessage, MyDrawEngine::WHITE);
	}


	// lose message
	const wchar_t loseMessage[] = L"You Lose!";
	if (lost == true)
	{
		pDE->WriteText(pDE->theCamera.ReverseTransform(Vector2D(midX - 64, midY + gameAreaHeight / 2.0f)), loseMessage, MyDrawEngine::WHITE);
	}


	// write fps to screen
	const wchar_t FPSlabel[] = L"FPS:";
	int FPS = (1 / gt.mdFrameTime);
	pDE->WriteText(pDE->theCamera.ReverseTransform(Vector2D((midX - gameAreaWidth / 2.0f)-80, midY - gameAreaHeight / 2.25f)), FPSlabel, MyDrawEngine::WHITE);
	pDE->WriteInt(pDE->theCamera.ReverseTransform(Vector2D((midX - gameAreaWidth / 2.0f)-40, midY - gameAreaHeight / 2.25f)), FPS, MyDrawEngine::WHITE);


	gt.mark();

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
	won = NULL;
	lost = NULL;
	collidersVector.clear();
	entityManager.deleteAll();
	entityManager.refresh();
	assetManager.clearAll();


	return SUCCESS;
}