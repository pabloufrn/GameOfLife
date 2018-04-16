#include "life.h"

Life::Life(int nLin = 20, int nCol = 60)
{
	this->rows = nLin;
	this->rows = nCol;
	this->grid.resize(nLin, {{CELL_DIED}});
	for(int i = 0; i < nLin; ++i)
	{
		this->grid[i].resize(nCol, CELL_DIED);
		for(int j = 0; j < nCol; ++j)
		{
			this->grid[i][j] = CELL_DIED;
		}
	}

}
Life::~Life()
{
	this->grid.resize(0);
	for(int i = 0; i < this->rows; ++i)
		this->grid[i].resize(0);
}
//set_alive();
//update();
void Life::print(){
	for(int i = 0; i < this->rows; ++i)
    {
		for(int j = 0; j < this->cols; ++j)
        {
			if(this->grid[i][j] == CELL_ALIVE)
				std::cout << '*';
			else
				std::cout << ' ';
		}
		std::cout << std::endl;
	}
}
//stable();
//extinct();
Life & Life::operator=(const Life& lf) 
{
	this->rows = lf.rows;					    // !
	this->cols = lf.cols;					    // | iguala propriedades
	this->grid.resize(lf.rows);	 			    // altera quantidade de linhas
	for(int i = 0; i < lf.rows; ++i) 			// percorre cada linha
    {
		this->grid[i].resize(lf.cols);			// redimensiona linha
		for(int j = 0; j < lf.cols; ++j)		// percorred as colunas
        {
			this->grid[i][j] = lf.grid[i][j]; 	// realiza a atribuição
		}
	}	
	this->set_id();                             // seta Vetor de identidade
	return *this; 						        // permite atribuição em cascata 
	// TODO: traduzir comentarios
}
bool Life::operator==(const Life& lf) const 
{
    int n = this->id[0];            // number of elements: number of distances + start_x + start_y + distance_1 + ... + distance_n
    for(int i = 0; i < n+3; ++i)         // if the sizes are different the loop will break at first time
    {
        if(this->id[i] != lf.id[i]) // different data
            return false;
    }
	return true;
}
void Life::set_id()
{
    int n = 0;
    int distance = 0;
    bool first_pos = true;
    this->id.reserve(3);
    
	for(int i = 0; i < this->rows; ++i)       // percorre cada linha    
    { 			
		for(int j = 0; j < this->cols; ++j)   // percorre as colunas
        {
			if(grid[i][j] == CELL_ALIVE)
            {
                if(first_pos)              // aren't start_x and start_y stored?
                {
                    this->id[1] = i;       // store start_x position
                    this->id[2] = j;       // store start_y position
                    first_pos = false;     // start_x and start_y stored
                }
                else                       // start coords are stored 
                {
                    this->id.push_back(distance); // store new distance
                    n++;                          // increase number of distances count
                }
                distance = 0;                     // reset distance
            }
            else
            {
                distance++; // increase distance count
            }
		}
	}
	this->id[0] = n;
}
























