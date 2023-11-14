// Include important C++ libraries here
	#include <SFML/Graphics.hpp>
	#include <sstream>
	#include <SFML/Audio.hpp>


// Make code easier to type with "using namespace"
	using namespace sf;
	using namespace std;

// Function declaration


// Where is the player/branch?
// Left or Right
	const int MaxWidth = 1920;
	const int MaxHeight = 1080;
	const int PosTimeBar = 980;
	const int NUM_BRANCHES = 6;

	// Where is the player/branch?
	
	// Left or Right

	enum class side { LEFT, RIGHT, NONE };

	// Cloud data
	struct Cloud {
		bool active;
		sf::Sprite sprite;
		int speed;
	};

int main()
{
	Sprite branches[NUM_BRANCHES];
	side branchPositions[NUM_BRANCHES];
	srand((int)time(0) * 10);

	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game
	RenderWindow window(vm, "JOC DE KEVIN" , Style::Fullscreen);

	// Create a texture to hold a graphic on the GPU
	Texture textureBackground;

	// Load a graphic into the texture
	textureBackground.loadFromFile("graphics/background.png");

	// Create a sprite
	Sprite spriteBackground;

	// Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);

	// Set the spriteBackground to cover the screen
	spriteBackground.setPosition(0, 0);

	// Make a tree sprite
	Sprite sprite1, sprite2, sprite3;
	Texture texture1, texture2, texture3;

	texture1.loadFromFile("graphics/tree.png"); 
	sprite1.setTexture(texture1);
	sprite1.setPosition(1400, 0);

	texture2.loadFromFile("graphics/tree.png"); 
	sprite2.setTexture(texture2);
	sprite2.setPosition(810, 0);

	texture3.loadFromFile("graphics/tree.png"); 
	sprite3.setTexture(texture3);
	sprite3.setPosition(200, 0);

	// Prepare the bee
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);

	// Define a structure for representing bees
	struct Bee {
		bool active;
		Sprite sprite;
		float speed;
	};

	const int numBees = 3;
	Bee spriteBees[numBees];

	// Initialize bee data
	for (int i = 0; i < numBees; ++i) {
		spriteBees[i].active = false;
		spriteBees[i].sprite.setTexture(textureBee);
		spriteBees[i].sprite.setPosition(0, 800);
		spriteBees[i].speed = 0.0f;
	}

	// Is the bee currently moving?
	bool beeActive = false;

	// How fast can the bee fly
	float beeSpeed = 0.0f;

	// Is the bee currently moving?

	// How fast can the bee fly

	// make 3 cloud sprites from 1 texture
	Texture textureCloud;

	// Load 1 new texture
	textureCloud.loadFromFile("graphics/cloud.png");

	// at different heights

	
	// Variables to control time itself
	Clock clock;

	// Cloud data array
	const int numClouds = 6;
	const int distance = 150;
	Cloud spriteCloud[numClouds];
	for (int i = 0; i < numClouds; ++i) {
		spriteCloud[i].active = false;
		spriteCloud[i].sprite.setTexture(textureCloud);
		spriteCloud[i].sprite.setPosition(0, 0 * distance);
		spriteCloud[i].speed = 0.0f;
	}

	//Score Hub
	RectangleShape rectangleBackground;
	rectangleBackground.setSize(Vector2f(530, 150)); // Ample i altura
	rectangleBackground.setPosition(10, 10); // Posició x i y
	rectangleBackground.setFillColor(Color(0, 0, 255, 150)); // RGB i alfa

	// Time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((MaxWidth / 2) - timeBarStartWidth / 2, PosTimeBar);
	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	// Track whether the game is running


	//Draw some text
	int score = 0;
	Text messageText;
	Text scoreText;

	// We need to choose a font
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	// Set the font to our message
	messageText.setFont(font);
	scoreText.setFont(font);
	// Assign the actual message
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");
	// Make it really big
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);
	// Choose a color
	messageText.setFillColor(Color::Blue);
	scoreText.setFillColor(Color::Red);

	// Choose a color
	messageText.setFillColor(Color::Red);
	Text fpsText;
	fpsText.setFont(font);
	fpsText.setCharacterSize(24);
	fpsText.setFillColor(Color::Blue);
	fpsText.setPosition(MaxWidth - 100, 10);

	// Position the text
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);

	// Prepare 5 branches
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");
	// Set the texture for each branch sprite
	for (int i = 0; i < NUM_BRANCHES; i++) {
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		// Set the sprite's origin to dead centre
		// We can then spin it round without changing its position
		branches[i].setOrigin(220, 20);
	}


	// Set the texture for each branch sprite

	// Prepare the Player
		Texture texturePlayer;
		texturePlayer.loadFromFile("graphics/player.png");
		Sprite spritePlayer;
		spritePlayer.setTexture(texturePlayer);
		spritePlayer.setPosition(MaxWidth / 3, MaxHeight - 350);
		spritePlayer.setScale(0.25, 0.25);

	// The player starts on the left
		side playerSide = side::LEFT;

	// Prepare the gravestone
		Sprite spriteGrave;
		Texture textureGrave;
		textureGrave.loadFromFile("graphics/rip.png");
		spriteGrave.setTexture(textureGrave);
		spriteGrave.setPosition(600, 860);
		// Line the axe up with the tree
		const float AXE_POSITION_LEFT = 700;
		const float AXE_POSITION_RIGHT = 1075;

	// Prepare the flying log
		Sprite spriteLog;
		Texture textureLog;
		textureLog.loadFromFile("graphics/log.png");
		spriteLog.setTexture(textureLog);
		spriteLog.setPosition(810, 730);// Some other useful log related variables
		bool logActive = false;
		float logSpeedX = 1000;
		float logSpeedY = -1500;
		// Prepare the axe
		Sprite spriteAxe;
		Texture textureAxe;
		textureAxe.loadFromFile("graphics/axe.png");
		spriteAxe.setTexture(textureAxe);
		spriteAxe.setPosition(755,845);

		// Some other useful log related variables

		// Control the player input
		bool acceptInput = false;

		// Prepare the sound
		SoundBuffer Chop;
		Chop.loadFromFile("sound/chop.WAV");
		Sound Chop_sound;
		Chop_sound.setBuffer(Chop);

		SoundBuffer Death;
		Death.loadFromFile("sound/death.WAV");
		Sound Death_sound;
		Chop_sound.setBuffer(Death);

		SoundBuffer Out_of_timeBuffer;
		Out_of_timeBuffer.loadFromFile("sound/out_of_time.WAV");
		Sound Out_of_time_sound;
		Out_of_time_sound.setBuffer(Out_of_timeBuffer);

	// Track whether the game is running
	bool paused = true;
	for(int seed = 1; seed <= 5; seed++)
	{
		for (int j = NUM_BRANCHES - 1; j > 0; j--) {
			branchPositions[j] = branchPositions[j - 1];
		} 

	// Spawn a new branch at position 0
	// LEFT, RIGHT or NONE
	srand((int)time(0) + seed);
	int r = (rand() % 5);
	switch (r) {
	case 0:
		branchPositions[0] = side::LEFT;
		break;
	case 1:
		branchPositions[0] = side::RIGHT;
		break;
	default:
		branchPositions[0] = side::NONE;
		break;
	}
	}

	//game loop
	while (window.isOpen())
	{



		/*
		****************************************
		Handle the players input
		****************************************
		*/

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !paused)
			{
				// Listen for key presses again
				acceptInput = true;
				// hide the axe
				spriteAxe.setPosition(2000,
				spriteAxe.getPosition().y);
			}
		}



		// Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;
			// Reset the time and the score
			score = 0;
			timeRemaining = 6;


			// Make all the branches disappear
			// starting in the second Position
			for (int i = 1; i < NUM_BRANCHES; i++)
			{
				branchPositions[i] = side::NONE;
			}

			// Make sure the gravestone is hidden
			spriteGrave.setPosition(675, 2000);

			// Move the player into position
			spritePlayer.setPosition(580, 720);
			acceptInput = true;
		}
		// Wrap the player controls to
		// Make sure we are accepting input
			if (acceptInput)
			{
				// More code here next...
	
		
		// First handle pressing the right cursor key
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					// Make sure the player is on the right
					playerSide = side::RIGHT;
						score++;
					// Add to the amount of time remaining
					timeRemaining += (2 / score) + .15;
					spriteAxe.setPosition(AXE_POSITION_RIGHT,
						spriteAxe.getPosition().y);
					spritePlayer.setPosition(1200, 720);
					// Update the branches
					for (int j = NUM_BRANCHES - 1; j > 0; j--) {
						branchPositions[j] = branchPositions[j - 1];
					}// Spawn a new branch at position 0
					// LEFT, RIGHT or NONE
					int r = (rand() % 5);
					switch (r) {
					case 0:
						branchPositions[0] = side::LEFT;
						break;
					case 1:
						branchPositions[0] = side::RIGHT;
						break;
					default:
						branchPositions[0] = side::NONE;
						break;
					}
					// Set the log flying to the left
					spriteLog.setPosition(810, 720);
					logSpeedX = -5000;
					logActive = true;
					acceptInput = false;
					Chop_sound.play();
				}

			// First handle pressing the left cursor key 
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					// El jugador ha premut la tecla de la fletxa esquerra

					//Estableix la posició del jugador al costat esquerre (LEFT).
					playerSide = side::LEFT;

					// Incrementa la puntuació del joc.
					score++;

					// Afegeix temps al temps restant basat en la puntuació actual.
					timeRemaining += (2 / score) + 0.15;

					// Actualitza la posició de l'herba talladora (axe) a l'esquerra.
					spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);

					// Actualitza la posició del jugador.
					spritePlayer.setPosition(580, 720);

					// Actualitza les posicions de les branques (branches), movent-les una posició cap avall.
					for (int j = NUM_BRANCHES - 1; j > 0; j--) {
						branchPositions[j] = branchPositions[j - 1];
					}

					// Genera una nova branca aleatòria a la posició 0 (ESQUERRA).
					int r = (rand() % 5);
					switch (r) {
					case 0:
						branchPositions[0] = side::LEFT;
						break;
					case 1:
						branchPositions[0] = side::RIGHT;
						break;
					default:
						branchPositions[0] = side::NONE;
						break;
					}

					// Configura el tronc (log) per començar a moure's cap a l'esquerra.
					spriteLog.setPosition(810, 720);
					logSpeedX = 5000;
					logActive = true;

					// Marca que el jugador no pot realitzar més accions per ara.
					acceptInput = false;
				}

		}
		// More code here next...
		// Play a chop sound

		// Handle the left cursor key

		// Make sure the player is on the left

		// Add to the amount of time remaining

		// update the branches

		// set the log flying

		/*
		****************************************
		Update the scene
		****************************************
		*/

		if (!paused)
		{
			// Measure time


			Time dt = clock.restart();

			//Config FPS
			Time elapsedTime = dt;
			float fps = 1.0f / elapsedTime.asSeconds();
			stringstream ss;
			ss << "FPS: " << fps;
			fpsText.setString(ss.str());

			// End if(!paused)

			// Subtract from the amount of time remaining
			timeRemaining -= dt.asSeconds();

			// size up the time bar
			timeBar.setSize(Vector2f(timeBarWidthPerSecond *
				timeRemaining, timeBarHeight));

			// Pause the game
			if (timeRemaining <= 0.0f) {
				paused = true;
				// Change the message shown to the player
				messageText.setString("Out of time!!");
				//Reposition the text based on its new size
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);
				messageText.setPosition(MaxWidth / 2.0f, MaxHeight / 2.0f);
				// Out of time
				Out_of_time_sound.play();

			}

			// Play the out of time sound


			// Setup the bee
			if (!beeActive)
			{
				//How fast is the bee
				beeSpeed = (rand() % 200) + 200;

				//How high is the bee
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}
			else
			{

				// Move the bee
				spriteBee.setPosition(
					spriteBee.getPosition().x -
					(beeSpeed * dt.asSeconds()),
					spriteBee.getPosition().y);

				// Has the bee reached the right hand edge of the screen?
				if (spriteBee.getPosition().x < -100)
				{
					// Set it up ready to be a whole new cloud next frame
					beeActive = false;
				}
			}

			// Manage the bee
			for (int i = 0; i < numBees; ++i) {
				if (!spriteBees[i].active) {
					spriteBees[i].speed = static_cast<float>(rand() % 200 + 200);
					float height = static_cast<float>(rand() % 500 + 500);
					spriteBees[i].sprite.setPosition(2000, height);
					spriteBees[i].active = true;
				}
				else {
					spriteBees[i].sprite.setPosition(
						spriteBees[i].sprite.getPosition().x - (spriteBees[i].speed * dt.asSeconds()),
						spriteBees[i].sprite.getPosition().y);

					if (spriteBees[i].sprite.getPosition().x < -100) {
						spriteBees[i].active = false;
					}
				}
			}

			// Manage the clouds
			for (int i = 0; i < numClouds; ++i) {
				if (!spriteCloud[i].active) {
					spriteCloud[i].speed = rand() % 200;
					float height = rand() % (distance * (i + 1));
					spriteCloud[i].sprite.setPosition(-200, height);
					spriteCloud[i].active = true;

				}
				else {
					spriteCloud[i].sprite.setPosition(
						spriteCloud[i].sprite.getPosition().x + (spriteCloud[i].speed * dt.asSeconds()), spriteCloud[i].sprite.getPosition().y);
					if (spriteCloud[i].sprite.getPosition().x > MaxWidth) {
						spriteCloud[i].active = false;

					}

				}

			}

			// How fast is the cloud

			// How high is the cloud

			// Has the cloud reached the right hand edge of the screen?

			// Set it up ready to be a whole new cloud next frame
					// update the branch sprites
			for (int i = 0; i < NUM_BRANCHES; i++)
			{
				float height = i * 150;
				if (branchPositions[i] == side::LEFT)
				{
					// Move the sprite to the left side
					branches[i].setPosition(610, height);
					// Flip the sprite round the other way
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT)
				{
					// Move the sprite to the right side
					branches[i].setPosition(1330, height);
					// Set the sprite rotation to normal
					branches[i].setRotation(0);
				}
				else
				{
					// Hide the branch
					branches[i].setPosition(3000, height);
				}
			}

			// Update the score text

			int currentScore = 0;

			if (score != currentScore) {
				stringstream ss;
				ss << "Score = " << score;
				scoreText.setString(ss.str());
				currentScore = score;
			}

			// update the branch sprites

			// Handle a flying log
				if (logActive)
				{
					// This section of code is executed when the flying log is active.

					// Move the log
					spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
						spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));

					// Check if the log has gone off the screen
					if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > MaxWidth + 100 ||
						spriteLog.getPosition().y > MaxHeight)
					{
						logActive = false;
					}

					// Check for collisions with the player character
					if (spriteLog.getGlobalBounds().intersects(spritePlayer.getGlobalBounds()))
					{
						// Log has hit the player character, handle the collision (e.g., game over).
						// You might set a game over state or perform other actions here.
						logActive = false;
					}
				}

				// has the player been squished by a branch?
				if (branchPositions[5] == playerSide)
				{
					//death 
					paused = true;
					acceptInput = false;
					//draw the gravestone
					spriteGrave.setPosition(525, 760);
					//hide the player
					spritePlayer.setPosition(2000, 600);
					//change the text of the message 
					messageText.setString("SQUISHED !!");
					// Center it on the screen
					FloatRect textRect = messageText.getLocalBounds();
					messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
					messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
					// play the death sound 
					Death_sound.play();
				}
		}
		
		// End if(!paused)

		/*
		****************************************
		Draw the scene
		****************************************
		*/

		// Clear everything from the last frame
		window.clear();

		// Draw our game scene here
		window.draw(spriteBackground);

		// Draw the clouds

		for (int i = 0; i < numClouds; i++)
		{
			window.draw(spriteCloud[i].sprite);
		}
		// Draw the tree
		window.draw(sprite1);
		window.draw(sprite2);
		window.draw(sprite3);
		// Draw the branches
		for (int i = 0; i < NUM_BRANCHES; i++) {
			window.draw(branches[i]);
		}





		// Draw the axe
		window.draw(spriteAxe);

		// Draraw the flying log
		window.draw(spriteLog);
		// Draw the player
		window.draw(spritePlayer);
		// Draw the gravestone
		window.draw(spriteGrave);

		// Draw the bee
		for (int i = 0; i < numBees; i++)
		{
			window.draw(spriteBees[i].sprite);
		}

		//Draw the hub 
		window.draw(rectangleBackground);

		// Draw the score
		window.draw(scoreText);
		if (paused)
		{
			// Draw our message
			window.draw(messageText);
		}

		// Draw the fps
		window.draw(fpsText);

		// Draw the timebar
		window.draw(timeBar);

		// Show everything we just drew
		window.display();


	}

	return 0;
}
