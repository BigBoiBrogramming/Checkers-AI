#include <string>

using namespace std;
 
class AlreadyHasPieceException : public exception
{
	public:
		AlreadyHasPieceException(int x, int y) : xCoord(x), yCoord(y)
		{
		}
		
		virtual const char* what() const throw()
		{
			string message = "Tile at location (" + to_string(xCoord) + ", " + to_string(yCoord) + ") already has a piece.";
			return message.c_str();
		}
	
	private:
		int xCoord;
		int yCoord;
};
