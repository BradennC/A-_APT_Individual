
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

class Tile {
public:
   /**
   * @brief constructor
   *
   * @param colour colour of tile to be defined
   * @param shape shape of tile to be defined
   */
   Tile(char colour, int shape);
   /**
   * @brief constructor
   * 
   * Initialises variables to default values
   * 
   */
   Tile();

   // colour value to be stored
   char colour;
   // shape value to be stored
   int  shape;
};

#endif // ASSIGN2_TILE_H
