#ifndef LIFE_H
#define LIFE_H

#include <iostream>
#include <fstream>
#include <vector>
#include "quadboard.h"

enum Cell{
	CELL_ALIVE = 1,
	CELL_DIED = 0
};

class Life {
	private:
		std::vector<std::vector<int>> grid;
		int rows;
		int cols;
        std::vector<int> id;
        std::vector<std::vector<int>> ids;
        /// constructor aux
        void init(int rows, int cols);
	public:
    QuadBoard *board;
	/// construtor
	Life(int rows = 20, int cols = 60);
    /// construtor
    Life(std::string filename);
    ///destructor
	~Life();
	/// sobrecarga do operador =
	Life & operator=(const Life& lf);
	bool operator==(std::vector<int> id) const; 
    void update();
	void add_data_vector(std::vector<int> vetor);
    void load_from_board();
	/// Imprime para o usuário como está a organização das células.
	int get_value( int x, int y );
	void set_value( int x, int y, int value );
	int get_rows();
	/// Retorna a quantidade de colunas da matriz
	int get_columns();
	void set_rows(int row);
	void set_columns(int column);
	char get_caractere();
	void set_caractere(char carac);
	bool is_extinct();
    bool is_stable();
    void clear_ids();
    void set_id();
    void save_file(std::string filename);
};
#endif
