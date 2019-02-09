
# Life Game  
Essa é uma versão do autómato celular Conway's Game of Life. A implementação foi feita em C++ 11 usando as 
bibliotecas SFML e pthread (para que os eventos sejam processados junto com a simulação). O projeto foi feito em 
dupla, sendo eu o responsável pela parte visual. O jogo cria padrões baseados na entrada do usuário e, a cada 
iterão, uma nova tela é gerada até que todas as celúlas "morram".

# Desafios  
Esse foi meu primeiro contato com a biblioteca SFML, então tive que aprender como ela funciona e criar minhas 
próprias partes visuais - que foram aproveitadas em outros projetos, como 
[Esse!](https://github.com/pabloufrn/Snaze/).

# Como usar
Depois de compilado ou baixado, você pode executar passando um arquivo de entrada ou o tamanho da matriz, assim:  
`./life entrada.dat`, onde entrada.dat é o caminho do arquivo de entrada; ou  
`./life -s colunas linhas`, para começar com uma matriz vazia de tamanho linhas x colunas.  
Com o programa aberto, use os botões direito e esquerdo do mouse para preparar a board, depois use os botões da 
parte inferior da tela.  

# Exemplos
- `./life data/cfg1.dat`  
- `./life -s 30 20`

