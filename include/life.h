#ifndef LIFE_H
#define LIFE_H

#include <iostream>
#include <vector>
#include "quadboard.h"

enum Cell{
	CELL_ALIVE = 1,
	CELL_DIED = 0
};

class Life {
	private:
		std::vector<std::vector<Cell>> grid;
		int rows;
		int cols;
        std::vector<int> id; // identity Vector - Formart [#n, start_x, start_y, distance_1, distance_2, ... , distance_n]
        QuadBoard *board;
	public:
	Life(int nLin, int nCol);
	~Life();
	Life & operator=(const Life& lf);
    /// sobrecarga do operador ==
	bool operator==(const Life& lf) const;
	//set_alive();	
    //update();
    void set_id();
	void print();
    void load_config();
	//stable();
	//extinct)_;

	int get_rows(){
		return this->rows;
	}
	int get_columns(){
		return this->cols;
	}
};
#endif
