// GameCode.cpp

#include "gamecode.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "myinputs.h"
#include <time.h>
#include "gametimer.h"
#include "errorlogger.h"
#include <math.h>
#include "shapes.h"
#include "camera.h"
#include "Components.h"

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
	wchar_t options[NUMOPTIONS][11] = {L"Resume", L"Main menu"};

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
			StartOfGame();		  // Initialise the game
			ChangeState(RUNNING); // Run it
		}

		if (m_menuOption == 1) // Quit
		{
			ChangeState(GAMEOVER);
		}
	}

	return SUCCESS;
}

// **********************************************************************************************
// The game !!! *********************************************************************************
// **********************************************************************************************

// required variables - move all to asset manager
PictureIndex playerSmiley;
PictureIndex playerScared;
PictureIndex playerConfused;
PictureIndex playerDead;

SoundIndex backgroundMusic;
SoundIndex playerBounce;
SoundIndex playerPoint;
SoundIndex playerWin;
SoundIndex playerDeath;


// game area
float gameAreaWidth;
float gameAreaHeight;
float midX;
float midY;


// ECS manager + entities
Manager entityManager;
auto& player(entityManager.addEntity());

// Called at the start of the game - when changing state from MENU to RUNNING
// Use this to initialise the core game
ErrorType Game::StartOfGame()
{
	// Code to setup your game *********************************************
	// **********************************************************************

	// player enitity + components
	player.addComponent<TransformComponent>(Vector2D(0, 0), 0, 1, true, 200, 10000, -100);
	playerSmiley = pDE->LoadPicture(L"assets/character/image/smiley.png");
	player.addComponent<ImageComponent>(pDE);
	player.getComponent<ImageComponent>().setImage(playerSmiley);
	player.addComponent<SoundComponent>(pSE);
	player.addComponent<InputComponent>(pInputs);


	// setup camera + game area
	pDE->UseCamera(true);
	pDE->theCamera.PlaceAt(Vector2D(0, 0));
	pDE->theCamera.SetZoom(pDE->GetScreenHeight() / 800.0f);

	gameAreaWidth = 770;
	gameAreaHeight = 578;
	gameAreaWidth = pDE->theCamera.Transform(gameAreaWidth);
	gameAreaHeight = pDE->theCamera.Transform(gameAreaHeight);
	midX = pDE->GetScreenWidth() / 2.0f;
	midY = pDE->GetScreenHeight() / 2.0f;


	// CREATE ASSET MANAGER - create a map for every group and media type: backgroundSoundMap, characterImageMap, world... etc

	//// load images
	//playerSmiley = pDE->LoadPicture(L"assets/character/image/smiley.png");
	//playerScared = pDE->LoadPicture(L"assets/character/image/scared.png");
	//playerConfused = pDE->LoadPicture(L"assets/character/image/confused.png");
	//playerDead = pDE->LoadPicture(L"assets/character/image/dead.png");

	//// load sounds
	//// backgroundMusic = pSE->LoadWav(L"assets/background/sound/backgroundMusic.wav"); DOES NOT EXIST YET
	//playerBounce = pSE->LoadWav(L"assets/character/sound/bounce.wav");
	//playerPoint = pSE->LoadWav(L"assets/character/sound/point.wav");
	//playerWin = pSE->LoadWav(L"assets/character/sound/win.wav");
	//playerDeath = pSE->LoadWav(L"assets/character/sound/death.wav");


	gt.mark();
	gt.mark();

	player.getComponent<TransformComponent>().setFrameTime(gt.mdFrameTime);

	return SUCCESS;
}

// Called each frame when in the RUNNING state.
// Checks for user pressing escape (which puts the game in the PAUSED state)
// Flips and clears the back buffer
// Gameplay programmer will develop this to create an actual game
ErrorType Game::Update()
{
	pInputs->SampleKeyboard();
	// Check for entry to pause menu
	static bool escapepressed = true;
	if (KEYPRESSED(VK_ESCAPE))
	{
		if (!escapepressed)
			ChangeState(PAUSED);
		escapepressed = true;
	}
	else
		escapepressed = false;

	// Your code goes here *************************************************
	// *********************************************************************

	// check if entities need to be removed
	// update remaining entities
	entityManager.refresh();
	entityManager.update();

	// gravity against "solid" surface
	if (player.getComponent<TransformComponent>().getPosition().YValue <= 0)
	{
		player.getComponent<TransformComponent>().stableGround();
	}

	// example level layout
	pDE->DrawLine(Vector2D(-384, -32), Vector2D(384, -32), MyDrawEngine::WHITE);
	pDE->DrawLine(Vector2D(-384, -40), Vector2D(384, -40), MyDrawEngine::WHITE);
	pDE->DrawLine(Vector2D(-384, -48), Vector2D(384, -48), MyDrawEngine::WHITE);

	pDE->DrawLine(Vector2D(-384, 16), Vector2D(-256, 16), MyDrawEngine::WHITE);
	pDE->DrawLine(Vector2D(-384, 24), Vector2D(-256, 24), MyDrawEngine::WHITE);
	pDE->DrawLine(Vector2D(-384, 32), Vector2D(-256, 32), MyDrawEngine::WHITE);

	pDE->DrawLine(Vector2D(-256, 80), Vector2D(-128, 80), MyDrawEngine::WHITE);
	pDE->DrawLine(Vector2D(-256, 88), Vector2D(-128, 88), MyDrawEngine::WHITE);
	pDE->DrawLine(Vector2D(-256, 96), Vector2D(-128, 96), MyDrawEngine::WHITE);

	pDE->DrawLine(Vector2D(-128, 144), Vector2D(0, 144), MyDrawEngine::WHITE);
	pDE->DrawLine(Vector2D(-128, 152), Vector2D(0, 152), MyDrawEngine::WHITE);
	pDE->DrawLine(Vector2D(-128, 160), Vector2D(0, 160), MyDrawEngine::WHITE);

	pDE->DrawLine(Vector2D(0, 208), Vector2D(128, 208), MyDrawEngine::WHITE);
	pDE->DrawLine(Vector2D(0, 216), Vector2D(128, 216), MyDrawEngine::WHITE);
	pDE->DrawLine(Vector2D(0, 224), Vector2D(128, 224), MyDrawEngine::WHITE);

	pDE->DrawLine(Vector2D(128, 272), Vector2D(256, 272), MyDrawEngine::WHITE);
	pDE->DrawLine(Vector2D(128, 280), Vector2D(256, 280), MyDrawEngine::WHITE);
	pDE->DrawLine(Vector2D(128, 288), Vector2D(256, 288), MyDrawEngine::WHITE);

	pDE->DrawLine(Vector2D(256, 336), Vector2D(384, 336), MyDrawEngine::WHITE);
	pDE->DrawLine(Vector2D(256, 344), Vector2D(384, 344), MyDrawEngine::WHITE);
	pDE->DrawLine(Vector2D(256, 352), Vector2D(384, 352), MyDrawEngine::WHITE);
	

	// position camera to follow player so player is 192px below center of screen
	// new cam pos = -2/3 * 576 * levelHeight(rows*64) 
	// could do levelHeight(rows*64) - 12*64 and do if levelHeight < first6*64 or > last6*64 = 192/-192
	// draw all entities
	pDE->theCamera.PlaceAt(Vector2D(0, -(player.getComponent<TransformComponent>().getPosition().YValue + 192)));
	entityManager.draw();

	// draw game area box 770x578 (interior measurement = 768x576)  - 64x64 tiles fit 12x9
	pDE->DrawLine(pDE->theCamera.ReverseTransform(Vector2D(midX - gameAreaWidth / 2.0f, midY - gameAreaHeight / 2.0f)), pDE->theCamera.ReverseTransform(Vector2D(midX - gameAreaWidth / 2.0f, midY + gameAreaHeight / 2.0f)), MyDrawEngine::DARKBLUE);
	pDE->DrawLine(pDE->theCamera.ReverseTransform(Vector2D(midX + gameAreaWidth / 2.0f, midY - gameAreaHeight / 2.0f)), pDE->theCamera.ReverseTransform(Vector2D(midX + gameAreaWidth / 2.0f, midY + gameAreaHeight / 2.0f)), MyDrawEngine::DARKBLUE);
	pDE->DrawLine(pDE->theCamera.ReverseTransform(Vector2D(midX - gameAreaWidth / 2.0f, midY - gameAreaHeight / 2.0f)), pDE->theCamera.ReverseTransform(Vector2D(midX + gameAreaWidth / 2.0f, midY - gameAreaHeight / 2.0f)), MyDrawEngine::DARKBLUE);
	pDE->DrawLine(pDE->theCamera.ReverseTransform(Vector2D(midX - gameAreaWidth / 2.0f, midY + gameAreaHeight / 2.0f)), pDE->theCamera.ReverseTransform(Vector2D(midX + gameAreaWidth / 2.0f, midY + gameAreaHeight / 2.0f)), MyDrawEngine::DARKBLUE);


	gt.mark();

	player.getComponent<TransformComponent>().setFrameTime(gt.mdFrameTime);

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

	return SUCCESS;
}