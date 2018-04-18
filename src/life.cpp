#include "life.h"

Life::Life(int rows, int cols)
{
    init(rows, cols);
}
Life::Life(std::string filename)
{
    std::ifstream file;
    file.open(filename);
    if(!file.is_open()){
        init(20, 60);
        return;
    }
    int rows, cols;
    char ca, cr; // char: active and char: read
    file >> rows >> cols >> ca;
    init(rows, cols);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            file >> cr;
            if(cr == ca)
                this->board->set_active(i, j);
        }
    }
}
void Life::init(int rows, int cols)
{
    this->rows = rows;
    this->cols = cols;
    this->grid.resize(rows+2, {CELL_DIED});
    for(int i = 0; i < rows+2; ++i)
        this->grid[i].resize(cols+2, CELL_DIED);
    this->board = new QuadBoard(20, cols, rows, 2);
}
Life::~Life()
{
    this->grid.resize(0);
    for(int i = 0; i < this->rows; ++i)
        this->grid[i].resize(0);
}
Life & Life::operator=(const Life& lf) 
{
    this->rows = lf.rows;					    // !
    this->cols = lf.cols;					    // | iguala propriedades
    this->grid.resize(lf.rows);	 			    // altera quantidade de linhas
    for(int i = 0; i < lf.rows+2; ++i) 			// percorre cada linha
    {
        this->grid[i].resize(lf.cols+2);			// redimensiona linha
        for(int j = 0; j < lf.cols+2; ++j)		// percorred as colunas
        {
            this->grid[i][j] = lf.grid[i][j]; 	// realiza a atribuição
        }
    }	
    return *this; 						        // permite atribuição em cascata 
    // TODO: traduzir comentarios
}
bool Life::operator==(std::vector<int> id) const 
{
    int n = this->id[0];                // number of elements: number of distances + 1 + start_x + start_y + distance_1 + ... + distance_n
    for(int i = 0; i < n+3; ++i){         // if the sizes are different the loop will break at first time
        if(this->id[i] != id[i]) // different data
            return false;
    }
    return true;
}
void Life::set_id()
{
    int n = 0;
    int distance = 0;
    this->id.push_back(0);
    for(int i = 0; i < this->rows; ++i)       // percorre cada linha    
    { 			
        for(int j = 0; j < this->cols; ++j)   // percorre as colunas
        {
            if(grid[i][j] == CELL_ALIVE)
            {
                this->id.push_back(distance); // store distance
                n++;                          // increase distance count
                distance = 0;                 // reset distance
            }
            else
            {
                distance++;                   // increase distance count
            }
        }
    }
    this->id[0] = n;
}
void Life::update()
{
    this->set_id();
    this->ids.push_back(this->id);
    Life lf = *this;
    int rows = this->get_rows();
    int cols = this->get_columns();
    for( auto i(1); i < rows+1 ; i++){
        for( auto j(1) ; j < cols+1; j++){
            // Contabiliza os vizinhos vivos de cada célula.
            int cont = 0;
            if(lf.get_value(i-1, j-1) == 1)
                cont++;
            if(lf.get_value(i-1, j)  == 1)
                cont++;
            if(lf.get_value(i-1, j+1) == 1)
                cont++;
            if(lf.get_value(i, j-1) == 1)
                cont++;
            if(lf.get_value(i, j+1) == 1)
                cont++;
            if(lf.get_value(i+1, j-1) == 1)
                cont++;
            if(lf.get_value(i+1, j) == 1)
                cont++;
            if(lf.get_value(i+1, j+1) == 1)
                cont++;
            
            // Aplica as regras.
            if(this->get_value(i, j) == 1){
                if(cont <= 1 || cont >= 4)
                    this->set_value(i, j, 0);
                
            } else{
                if(cont == 3)
                    this->set_value(i, j, 1);
            }
        }
    }
}
int Life::get_value( int x, int y ){
    return this->grid[x][y];
}

void Life::set_value(int x, int y, int value ){
    if(value == 0)
        this->board->set_default(x-1, y-1);
    else
        this->board->set_active(x-1, y-1);
    this->grid[x][y] = value;
}

int Life::get_rows(){
    return this->rows;
}

int Life::get_columns(){
    return this->cols;
}

bool Life::is_extinct(){
    if(this->id[0] == 0)
        return true;
    return false;
}
bool Life::is_stable()
{
    int size = this->ids.size();
    for(int i = 0; i < size-1; i++)
        if(*this == this->ids[i])
            return true;
    return false;
}

void Life::load_from_board()
{
    this->board->backup();
    for( auto i(0) ; i < this->rows; i++ ){
        for( auto j(0) ; j < this->cols; j++ ){
            if(this->board->get_active(i, j))
                this->grid[i+1][j+1] = CELL_ALIVE;
            else
                this->grid[i+1][j+1] = CELL_DIED;
        }
    }
}

void Life::clear_ids()
{
    this->ids.clear();
}






















