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
	MyDrawEngine *pTheDrawEngine = MyDrawEngine::GetInstance();
	pTheDrawEngine->Flip();
	pTheDrawEngine->ClearBackBuffer();

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
	if (FAILED(MySoundEngine::Start(hwnd)))
	{
		ErrorLogger::Writeln(L"Failed to start MySoundEngine");
		return FAILURE;
	}
	if (FAILED(MyInputs::Start(hinstance, hwnd)))
	{
		ErrorLogger::Writeln(L"Failed to start MyInputs");
		return FAILURE;
	}
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
	MySoundEngine* pSE = MySoundEngine::GetInstance();
	pSE->StopAllSounds();

	// Code for a basic pause menu

	MyDrawEngine::GetInstance()->WriteText(450, 220, L"Paused", MyDrawEngine::WHITE);

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
		MyDrawEngine::GetInstance()->WriteText(450, 300 + 50 * i, options[i], colour);
	}

	MyInputs *pInputs = MyInputs::GetInstance();

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
	MySoundEngine* pSE = MySoundEngine::GetInstance();
	pSE->StopAllSounds();

	MyDrawEngine::GetInstance()->WriteText(450, 220, L"Main menu", MyDrawEngine::WHITE);

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
		MyDrawEngine::GetInstance()->WriteText(450, 300 + 50 * i, options[i], colour);
	}

	// Get keyboard input
	MyInputs *pInputs = MyInputs::GetInstance();

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

// required variables
PictureIndex backgroundImage;
PictureIndex playerSmiley;
PictureIndex playerScared;
PictureIndex playerConfused;
PictureIndex playerDead;

SoundIndex backgroundMusic;
SoundIndex playerBounce;
SoundIndex playerPoint;
SoundIndex playerWin;
SoundIndex playerDeath;

Vector2D backgroundPos;
Vector2D playerPosition;
Vector2D gravity;
Vector2D playerXVelocity;
Vector2D playerYVelocity;
Vector2D playerYAcceleration;


// Called at the start of the game - when changing state from MENU to RUNNING
// Use this to initialise the core game
ErrorType Game::StartOfGame()
{
	// Code to setup your game *********************************************
	// **********************************************************************

	// get all pointers to engines 
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	MySoundEngine* pSE = MySoundEngine::GetInstance();

	// setup camera
	pDE->UseCamera(true);
	pDE->theCamera.PlaceAt(Vector2D(0, 0));
	pDE->theCamera.SetZoom(1);


	// load images
	playerSmiley = pDE->LoadPicture(L"assets/character/image/smiley.png");
	playerScared = pDE->LoadPicture(L"assets/character/image/scared.png");
	playerConfused = pDE->LoadPicture(L"assets/character/image/confused.png");
	playerDead = pDE->LoadPicture(L"assets/character/image/dead.png");

	// load sounds
	// backgroundMusic = pSE->LoadWav(L"assets/background/sound/backgroundMusic.wav"); DOES NOT EXIST YET
	playerBounce = pSE->LoadWav(L"assets/character/sound/bounce.wav");
	playerPoint = pSE->LoadWav(L"assets/character/sound/point.wav");
	playerWin = pSE->LoadWav(L"assets/character/sound/win.wav");
	playerDeath = pSE->LoadWav(L"assets/character/sound/death.wav");


	// setup physics
	gravity = Vector2D(0, -100);

	// setup player physics
	playerPosition = Vector2D(0, 0);
	playerXVelocity = Vector2D(0, 0);
	playerYVelocity = Vector2D(0, 0);
	playerYAcceleration = Vector2D(0, 0);


	gt.mark();
	gt.mark();

	return SUCCESS;
}

// Called each frame when in the RUNNING state.
// Checks for user pressing escape (which puts the game in the PAUSED state)
// Flips and clears the back buffer
// Gameplay programmer will develop this to create an actual game
ErrorType Game::Update()
{
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

	// get all pointers to engines + enable input
	MyDrawEngine* pDE = MyDrawEngine::GetInstance();
	MySoundEngine* pSE = MySoundEngine::GetInstance();
	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();

	
	// gravity against solid surface
	if (playerPosition.YValue <= 0)
	{
		playerYAcceleration = -gravity;
		playerYVelocity = Vector2D(0, 0);
	}
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
	

	// jump
	if (pInputs->KeyPressed(DIK_W) || pInputs->KeyPressed(DIK_UP) || pInputs->KeyPressed(DIK_SPACE))
	{
		// only jump if colliding with top of surface
		if (playerPosition.YValue <= 0)
		{
			playerYAcceleration = Vector2D(0, 10000);
		}
	}

	// move left
	if (pInputs->KeyPressed(DIK_A) || pInputs->KeyPressed(DIK_LEFT))
	{
		playerXVelocity = Vector2D(-200, 0);
	}

	// move right
	if (pInputs->KeyPressed(DIK_D) || pInputs->KeyPressed(DIK_RIGHT))
	{
		playerXVelocity = Vector2D(200, 0);
	}

	// apply acceleration to velocity -> apply velocity to position
	// if player reaches X boundries teleport to other side
	// camera Y position follows players Y position - 192px
	// print character at position
	// reset acceleration and velocity
	playerYVelocity = playerYVelocity + (playerYAcceleration + gravity) * gt.mdFrameTime;
	playerPosition = playerPosition + (playerXVelocity + playerYVelocity) * gt.mdFrameTime;
	if (playerPosition.XValue <= -353)
	{
		playerPosition = playerPosition + Vector2D(704, 0);
	}
	if (playerPosition.XValue >= 353)
	{
		playerPosition = playerPosition + Vector2D(-704, 0);
	}
	pDE->theCamera.PlaceAt(Vector2D(0, -(playerPosition.YValue + 192)));
	pDE->DrawAt(playerPosition, playerSmiley);
	playerXVelocity = Vector2D(0, 0);
	playerYAcceleration = Vector2D(0, 0);


	// sound test
	if (pInputs->KeyPressed(DIK_S) || pInputs->KeyPressed(DIK_DOWN))
	{
		pSE->Play(playerBounce);
	}
	if (pInputs->KeyPressed(DIK_SPACE))
	{
		pSE->Play(playerDeath);
	}
	if (pInputs->KeyPressed(DIK_RETURN))
	{
		pSE->Play(playerWin);
	}


	// draw game area box 768x576 - 64x64 tiles fit 12x9
	pDE->DrawLine(pDE->theCamera.ReverseTransform(Vector2D((pDE->GetScreenWidth() / 2) - 385, (pDE->GetScreenHeight() / 2) - 289)), pDE->theCamera.ReverseTransform(Vector2D((pDE->GetScreenWidth() / 2) - 385, (pDE->GetScreenHeight() / 2) + 289)), MyDrawEngine::DARKBLUE);
	pDE->DrawLine(pDE->theCamera.ReverseTransform(Vector2D((pDE->GetScreenWidth() / 2) + 385, (pDE->GetScreenHeight() / 2) - 289)), pDE->theCamera.ReverseTransform(Vector2D((pDE->GetScreenWidth() / 2) + 385, (pDE->GetScreenHeight() / 2) + 289)), MyDrawEngine::DARKBLUE);
	pDE->DrawLine(pDE->theCamera.ReverseTransform(Vector2D((pDE->GetScreenWidth() / 2) - 385, (pDE->GetScreenHeight() / 2) - 289)), pDE->theCamera.ReverseTransform(Vector2D((pDE->GetScreenWidth() / 2) + 385, (pDE->GetScreenHeight() / 2) - 289)), MyDrawEngine::DARKBLUE);
	pDE->DrawLine(pDE->theCamera.ReverseTransform(Vector2D((pDE->GetScreenWidth() / 2) - 385, (pDE->GetScreenHeight() / 2) + 289)), pDE->theCamera.ReverseTransform(Vector2D((pDE->GetScreenWidth() / 2) + 385, (pDE->GetScreenHeight() / 2) + 289)), MyDrawEngine::DARKBLUE);


	gt.mark();

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