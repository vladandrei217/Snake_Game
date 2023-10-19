#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<ctime>

using namespace std;

#define mgSus 10
#define mgJos 20
#define mgSt 15
#define mgDr 35

void gotoxy(int column, int line);
void printChenar();

class Snake
{
private:
    class Nod
    {
    public:
        int x;
        int y;
        char corp;
        Nod* next;
    };
    int headx = 0; // head coordinates before the current move
    int heady = 0;
    int xf = 0;
    int yf = 0;
    Nod* head;
    Nod* end;
    Nod* curent;
    int lungime = 0;
    char fruits = 'o';
    bool easy = true;
    char direction;
public:
    void fruit()
    {
        bool overlap;
        do {
            overlap = false;
            srand(time(nullptr));
            srand(time(nullptr));
            xf = rand() % 100 + 1;
            yf = rand() % 100 + 1;
            while (xf <= mgSt || xf >= mgDr)
                xf = rand() % 100;
            while (yf <= mgSus || yf >= mgJos)
                yf = rand() % 100;

            curent = head;
            while (curent->next != NULL)
            {
                if (curent->x == xf && curent->y == yf)
                {
                    overlap = true;
                    break;
                }
                curent = curent->next;
            }
        } while (overlap);

        gotoxy(xf, yf);
        cout << fruits;
    }
    void remove()
    {
        curent = head;
        while (curent->next != NULL)
        {
            gotoxy(curent->x, curent->y);
            cout << ' ';
            if (curent->next->next == NULL)
                break;
            curent = curent->next;
        }
    }
    void youLost()
    {
        curent = head->next;
        while (curent->next != NULL)
        {
            if (head->x == curent->x && head->y == curent->y)
            {
                curent->next = end;
                break;
            }
            curent = curent->next;
        }
    }
    bool lost()
    {
        bool lost = false;
        curent = head->next;
        while (curent->next != NULL)
        {
            if (head->x == curent->x && head->y == curent->y)
            {
                lost = true;
                gotoxy(curent->x, curent->y);
                cout << 'X';
                break;
            }
            curent = curent->next;
        }
        return lost;
    }
    Snake()
    {
        char game = 49;
        do {
            gotoxy(0, 0);
            printChenar();
            gotoxy(0, 0);
            cout << "\t\t\tSNAKE" << endl;
            cout << "Choose game mode:" << endl;
            cout << "Casual: press 1..." << endl;
            cout << "Hardcore: press 2..." << endl;
            if (game != 49 && game != 50)
                cout << "Wrong input, choose between the two game modes..." << endl << "Your input was: " << game << endl;
            game = _getch();
        } while (game != 49 && game != 50);
        gotoxy(0, 0);
        printChenar();
        gotoxy(0, 0);
        cout << "\t\t\tSNAKE" << endl;
        if (game == 49)
        {
            easy = true;
            cout << "You are now playing casual mode!" << endl;
            cout << "Have fun eating fruits('o'), eating your own tail will only shorten your snakes lenght!" << endl;
            cout << "To move the snake use 'w''a''s''d'                                                  " << endl;
            cout << "To quit the game press 'q'                                                          " << endl;
        }
        else
        {
            easy = false;
            cout << "You are now playing hardcore mode!" << endl;
            cout << "Try to score as much as possible by eating fruits('o')!" << endl;
            cout << "Be careful, if you eat your own tail you will lose!" << endl;
            cout << "To move the snake use 'w''a''s''d'                                          " << endl;
            cout << "To quit the game press 'q'                                                " << endl;
        }
        cout << "Enjoy!";
        lungime = 0;
        head = new Nod();
        end = new Nod();
        head->next = end;
        end->next = NULL;
        head->corp = 254;
        head->x = mgSt + 10;
        head->y = mgSus + 5;
        curent = head;
        gotoxy(curent->x, curent->y);
        cout << curent->corp;
        fruit();
    }
    void moveHead(char dir)
    {
        headx = head->x;
        heady = head->y;
        remove();
        switch (dir)
        {
        case 'W':
            if (direction == 'S' && lungime > 1)
            {
                head->y++;
                dir = 'S';
            }
            else
                head->y--;
            break;
        case 'S':
            if (direction == 'W' && lungime > 1)
            {
                head->y--;
                dir = 'W';
            }
            else
                head->y++;
            break;
        case 'A':
            if (direction == 'D' && lungime > 1)
            {
                head->x++;
                dir = 'D';
            }
            else
                head->x--;
            break;
        case 'D':
            if (direction == 'A' && lungime > 1)
            {
                head->x--;
                dir = 'A';
            }
            else
                head->x++;
            break;
        }
        direction = dir;
        if (head->x == mgSt)
            head->x = mgDr - 1;
        if (head->x == mgDr)
            head->x = mgSt + 1;
        if (head->y == mgSus)
            head->y = mgJos - 1;
        if (head->y == mgJos)
            head->y = mgSus + 1;
    }
    void addTail()
    {
        lungime++;
        Nod* tail;
        tail = new Nod();
        tail->next = curent->next;
        curent->next = tail;
        tail->corp = 254;
        tail->x = curent->x;
        tail->y = curent->x;
        curent = tail;
    }
    void updateAndPrint()
    {
        int prevx = 0;
        int prevy = 0;
        int curx;
        int cury;
        curent = head;
        gotoxy(curent->x, curent->y);
        cout << curent->corp;
        curent = curent->next;
        prevx = headx;
        prevy = heady;
        while (curent->next != NULL)
        {
            curx = curent->x;
            cury = curent->y;
            curent->x = prevx;
            curent->y = prevy;
            gotoxy(curent->x, curent->y);
            cout << curent->corp;
            prevx = curx;
            prevy = cury;
            curent = curent->next;
        }
    }
    void game()
    {
        bool endGame = false;
        char dir;
        char prev;
        dir = _getch();
        dir = toupper(dir);
        direction = dir;
        while (dir != 'Q')
        {
            do {
                moveHead(dir);

                if (head->x == xf && head->y == yf)
                {
                    addTail();
                    fruit();
                }
                if (easy == true)
                    youLost();
                updateAndPrint();
                if (easy == false)
                {
                    gotoxy(0, 7);
                    cout << "Score: " << lungime * 100 << " points";
                }
                if (easy == false && lost())
                {
                    gotoxy(0, mgJos + 2);
                    cout << "Game over, you lost!" << endl;
                    cout << " You scored: " << lungime * 100 << " points" << endl;
                    endGame = true;
                    break;
                }

                Sleep(250);
            } while (!_kbhit());
            if (endGame)
                break;
            dir = _getch();
            dir = toupper(dir);
        }
    }
    void printare()
    {
        curent = head;
        while (curent->next != NULL)
        {
            cout << curent->corp << ' ';
            curent = curent->next;
        }
    }
};

int main()
{
    system("color A5");
    Snake joc;
    joc.game();
    gotoxy(0, mgJos + 2);
    cout << "Thank you for playing!" << endl;
    cout << "Press any key to quit..." << endl;
    _getch();
    return 0;
}

void gotoxy(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void printChenar()
{
    char sus = 220;
    char jos = 223;
    char lateral = 219;
    for (int i = 0; i <= mgJos; i++)
    {
        for (int j = 0; j <= mgDr; j++)
        {
            if (i == mgSus && j >= mgSt)
                cout << sus;
            else if (i == mgJos && j >= mgSt)
                cout << jos;
            else if (i > mgSus && (j == mgDr || j == mgSt))
                cout << lateral;
            else
                cout << ' ';
        }
        cout << endl;
    }
}