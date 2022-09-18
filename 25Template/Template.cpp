#include <iostream>
#include <memory>

//Step 1
struct Game
{
	virtual void initialize() = 0;
	virtual void startPlay() = 0;
	virtual void endPlay() = 0;
	virtual ~Game() = 0;

	//template method
	virtual void play() final {
		//initialize the game
		initialize();

		//start game
		startPlay();

		//end game
		endPlay();
	}
};

Game::~Game(){};

//Step 2
class Cricket: public Game
{
public:
	void endPlay() override {
		std::cout << "Cricket Game Finished!" << std::endl;
	}

	void initialize() override {
		std::cout << "Cricket Game initialized! Start playing." << std::endl;
	}

	void startPlay() override {
		std::cout << "Cricket Game Started. Enjoy the game!" << std::endl;
	}
};

class Football: public Game
{
public:
	void endPlay() override {
		std::cout << "Football Game Finished!" << std::endl;
	}

	void initialize() override {
		std::cout << "Football Game initialized! Start playing." << std::endl;
	}

	void startPlay() override {
		std::cout << "Football Game Started. Enjoy the game!" << std::endl;
	}
};

//Step 3

int main(int argc, char *argv[])
{
	std::unique_ptr<Game> game = std::make_unique<Cricket>();
	game->play();

	game.release();

	std::cout << std::endl;

	game = std::make_unique<Football>();
	game->play();

	return 0;
}
