#include <iostream> 
#include <fstream>
#include <vector>
using namespace std;
class  Game {
public:
	enum class Category { SHOOTER, RACE, SURVIVAL, UNDEFINED };
private:
	static const int str_size = 255;
	char name[str_size];
	int popularity;
	Category category;
public:
	Game(const char* name = "NoName", const int& popularity = 0, const Category& category = Category::UNDEFINED)
		:popularity(popularity), category(category)
	{
		if ((strlen(name) + 1) == 0 || (strlen(name) + 1) > 255)
		{
			throw "Incorrect strlen";
		}
		strcpy_s(this->name, strlen(name) + 1, name);
		this->category = category;
	}
	void print()const {
		cout << "Name : " << name << endl;
		cout << "Popularity: " << popularity << endl;
		cout << "Category : ";
	}
	string getName() const {
		return name;
	}
	const int getCategory() const {
		return (int)category;
	}
};

class ReadingGame {
public:
	static void watchAllGames(const string& fileName)
	{
		Game value, temp;
		ifstream in(fileName, ios_base::binary);
		if (!in)
		{
			throw exception("Error opening file for read");
		}
		in.read(reinterpret_cast<char*>(&value), sizeof(Game));
		while (!in.eof()) {
			value.print();
			in.read(reinterpret_cast<char*>(&value), sizeof(Game));
		}
	}
	static void addNewGame(const Game& value, const string& fileName)
	{
		ofstream out(fileName, ios_base::binary | ios_base::app);
		if (!out)
		{
			cerr << "Error opening\n";
			return;
		}
		out.write((char*)&value, sizeof(Game));
		out.close();
	}
	static void findGameByName(const string& name, const string& fileName) {
		Game value, temp;
		ifstream in(fileName, ios_base::binary);
		if (!in)
		{
			throw exception("Error opening file for read");
		}
		in.read(reinterpret_cast<char*>(&value), sizeof(Game));
		while (!in.eof()) {

			if (value.getName() == name)
			{
				cout << "Your game with name " << name << " is on the list." << endl;
				return;
			}
			in.read(reinterpret_cast<char*>(&value), sizeof(Game));
		}
		cout << "Your game is nowhere to be found" << endl;
	}
	static void findNameByCategory(const int category, const string& fileName) {
		if (category > 3 || category < 0)
		{
			cout << "Incorrect category" << endl;
			return;
		}
		Game value, temp;
		ifstream in(fileName, ios_base::binary);
		if (!in)
		{
			throw exception("Error opening file for read");
		}
		in.read(reinterpret_cast<char*>(&value), sizeof(Game));
		while (!in.eof()) {

			if (value.getCategory() == category)
			{
				cout << "You game with your category have name : " << value.getName() << endl;
			}
			in.read(reinterpret_cast<char*>(&value), sizeof(Game));
		}
		cout << "No game with your category" << endl;
	}
	static void editGameWithName(const string& name, const string& fileName) {
		Game value, temp;
		int index = -1;
		ifstream in(fileName, ios_base::binary);
		if (!in)
		{
			throw exception("Error opening file!!!");
		}
		in.read(reinterpret_cast<char*>(&value), sizeof(Game));
		while (!in.eof()) {

			if (value.getName() == name)
			{
				cout << "Your game with your category : " << value.getName() << endl;
			}
			in.read(reinterpret_cast<char*>(&value), sizeof(Game));
			++index;
		}
		cout << "No game with your category" << endl;
	}
	static void deleteGame(const string& name, const string& fileName) {
		Game value, temp;
		vector<string> lines;
		ifstream in(fileName, ios_base::binary);
		if (!in)
		{
			throw exception("Error opening file!!!");
		}
		in.read(reinterpret_cast<char*>(&value), sizeof(Game));
		while (!in.eof()) {

			if (value.getName() == name)
			{
				cout << "Your game with name " << name << " is on the list." << endl;
				return;
			}
			in.read(reinterpret_cast<char*>(&value), sizeof(Game));
		}
		cout << "Your game is nowhere to be found" << endl;
	}
	static void clearBase()
	{

	}
};

int main() {
	Game game("CS:GO", 5432724, Game::Category::SHOOTER);
	ReadingGame::addNewGame(game, "game.dat");
	Game game1("Valorant", 476584, Game::Category::SHOOTER);
	ReadingGame::addNewGame(game1, "game.dat");
	ReadingGame::watchAllGames("game.dat");
	ReadingGame::findGameByName("CS:GO", "game.dat");
	ReadingGame::findGameByName("Valorant", "game.dat");
	ReadingGame::findNameByCategory(0, "game.dat");
}