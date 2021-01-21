#include <iostream>
#include <array>
#include <fstream>
#include <string>

void load_sudoku(std::string path, std::array<std::array<int , 9>, 9>& tab)
{
    int i = 0;
    char nb;
    std::ifstream myfile(path);
    if (myfile.is_open())
    {
        while (myfile.get(nb) && !myfile.eof())
        {
            if (nb != '\n' && nb != '\r' && nb != '\0')
            {
                tab[i/9][i%9] = nb - '0';
                i++;
            }   
        }
        myfile.close();
    }

    else std::cout << "Unable to open file"; 
}

bool absentSurLigne (int k, std::array<std::array<int , 9>, 9>& grille, int i)
{
    for (int j=0; j < 9; j++)
        if (grille[i][j] == k)
            return false;
    return true;
}

bool absentSurColonne (int k, std::array<std::array<int , 9>, 9>& grille, int j)
{
    for (int i=0; i < 9; i++)
        if (grille[i][j] == k)
            return false;
    return true;
}

bool absentSurBloc (int k, std::array<std::array<int , 9>, 9>& grille, int i, int j)
{
    int _i = i-(i%3), _j = j-(j%3);
    for (i=_i; i < _i+3; i++)
        for (j=_j; j < _j+3; j++)
            if (grille[i][j] == k)
                return false;
    return true;
}

bool estValide (std::array<std::array<int , 9>, 9>& grille, int position)
{
    if (position == 9*9)
        return true;

    int i = position/9, j = position%9;

    if (grille[i][j] != 0)
        return estValide(grille, position+1);

    for (int k=1; k <= 9; k++)
    {
        if (absentSurLigne(k,grille,i) && absentSurColonne(k,grille,j) && absentSurBloc(k,grille,i,j))
        {
            grille[i][j] = k;

            if ( estValide (grille, position+1) )
                return true;
        }
    }
    grille[i][j] = 0;

    return false;
}

void affichage(std::array<std::array<int , 9>, 9>& grille)
{
    std::cout << "+-------+-------+-------+" << std::endl;
    for (int i = 0; i < 9; i++)
    {
        std::cout << "| ";
        for (int j = 0; j < 9; j++)
        {
            std::cout << grille[i][j] << " ";

            if ((j + 1) % 3 == 0)
                std::cout << "| ";
        }
        if ((i + 1) % 3 == 0)
            std::cout << "\n+-------+-------+-------+" << std::endl;
        else
            std::cout << std::endl;
        
    }
}

int main(int argc, char *argv[])
{
    std::string path = "sudoku1.txt";
    std::array<std::array<int , 9>, 9> tab;

    if (argc > 1)
    {
        path = argv[1];
    }

    load_sudoku(path, tab);

    affichage(tab);

    estValide(tab, 0);

    std::cout << "\nResolu : \n" << std::endl;

    affichage(tab);

    return 0;
}
