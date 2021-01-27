#include <iostream>
#include <cstdlib>
using namespace std;

//basic functions prototype
void main_menu(bool);
void secondary_menu(int**, int, int, bool);
void play(bool);
int** load();
void save(int**, int, int, int);
void scoreboard();
void exit();

//secondary functions prototype

//play:
void play_menu(int &, int &);
void play_move(int**, int , int, char);
void play_sum(int**, int, int, char, int &);
void play_print(int**, int, int, int);
bool play_rand_num(int**, int, int, char);
bool play_over(int**, int, int);
void play_sort(int*);

//swapper
void swapper(int**, int**, int, int);

// variable
int sum;

//main function
int main()
{
    //variables
    bool loaded = false;
    // welcome ,toturial and menu
    cout << "This is 2048 game."<< endl;
    cout << "Toturial:" << endl;
    cout << "Use W for up, S for down, D for right, and A for left, esc for pause and also U for undo." << endl;
    // call main_menu function
    main_menu(loaded);
    
    return 0;
}

//main_menu function
void main_menu(bool loaded)
{
    int option;
    bool first_try = true;
    while (first_try || option > 4)
    {
        first_try = false;
        cout << "What do you want to do?" << endl;
        cout << "1.New game     2.Load game     3.Scoreboard    4.Exit" << endl;
        cout << "Enter the number of your option: ";
        cin >> option;

        //clear the screen
        printf("\e[1;1H\e[2J");
        
        //which one is selected?
        switch (option)
        {
        case 1:
            play(loaded);
            break;
        case 2:
            loaded = true;
            play(loaded);
            break;
        case 3:
            scoreboard();
            break;
        case 4:
            exit();
            break;
        default:
            cout << "Wrong input!!!";
            cout << endl;
            break;
        }
    }
    
    cout << "What do you want to do?" << endl;
    cout << "1.New game     2.Load game     3.Scoreboard    4.Exit" << endl;
    cout << "Enter the number of your option: ";
    cin >> option;

    //clear the screen
    printf("\e[1;1H\e[2J");
    
    //which one is selected?
    switch (option)
    {
    case 1:
        play(loaded);
        break;
    case 2:
         loaded = true;
         play(loaded);
         break;
    case 3:
        scoreboard();
        break;
    case 4:
        exit();
        break;
    default:
        cout << "Wrong input!!!";
        cout << endl;
        break;
    }

    return;
}

//secondary_menu function
void secondary_menu(int **table, int row, int col, bool loaded)
{
    bool first_try = true;
    int option;
    while (first_try || option > 6)
    {
        first_try = false;
        cout << "What do you want to do?" << endl;
        cout << "1.Play again     2.Load game     3.Save game     4.Scoreboard    5.Exit to main menu     6.Exit" << endl;
        cout << "Enter the number of your option: ";
        cin >> option;

        //clear the screen
        printf("\e[1;1H\e[2J");
    
        //which one is selected?
        switch (option)
        {
            case 1:
                play(loaded);
                break;
            case 2:
                loaded = true;
                play(loaded);
                break;
            case 3:
                save(table, row, col, sum);
                break;
            case 4:
                scoreboard();
                break;
            case 5:
                main_menu(loaded);
                break;
            case 6:
                exit();
                break;
            default:
                cout << "Wrong input!!!";
                cout << endl;
                break;
        }
    }
    
    return;
}

//play function
void play(bool loaded)
{
    
    int row, col, x1, x2, y1, y2;
    bool first_try = true;
    char dir;
    sum = 0;

    //create high scores array and file
    FILE *pointer3 = fopen("scoreboard3x3.txt", "a");
    FILE *pointer4 = fopen("scoreboard4x4.txt", "a");
    FILE *pointer5 = fopen("scoreboard5x5.txt", "a");
    FILE *pointer0 = fopen("scoreboard_Other.txt", "a");
    int score3[3] = {0};
    int score4[3] = {0};
    int score5[3] = {0};
    int scoreo[3] = {0};

    int** table;
    int** undo;

    if (loaded)
    {
        FILE *ptr = fopen("saves.txt", "r");
        if (ptr == NULL)
        {
            //clear the screen
            printf("\e[1;1H\e[2J");
            cout << "You haven't any save! you should play first..." << endl;
            secondary_menu(table, row, col, false);
        }
        fscanf(ptr,"%d", &row);
        fscanf(ptr,"%d", &col);
        fscanf(ptr, "%d", &sum);
        fclose(ptr);
        table = new int *[row];
        for (int i = 0; i < row; i++)
        {
            table[i] = new int[col];
        }
        
        table = load();
    }
    else
    {
        //call play menu
        play_menu(row, col);

        //clear the screen
        printf("\e[1;1H\e[2J");
        // generating the table
        table = new int*[row];
        for (int i = 0; i < row; i++)
        {
        table[i] = new int[col];
        }
        x1 = rand() % row;
        x2 = rand() % row;
        y1 = rand() % col;
        y2 = rand() % col;

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if ((i == x1 && j == y1) || (i == x2 && j == y2))
                {
                    table[i][j] = 2;
                }
                else
                {
                    table[i][j] = 0;
                }
            }
        }
    }

    //generating undo table
    undo = new int*[row];
    for (int i = 0; i < col; i++)
    {
        undo[i] = new int[col];
    }
    
    
    play_print(table, row, col, sum);

    while (play_over(table, row, col) || first_try)
    {
        first_try = false;
        cin >> dir;
        //if esc pressed
        if (dir == 27)
        {
            //clear the screen
            printf("\e[1;1H\e[2J");
            break;
        }

        //clear the screen
        printf("\e[1;1H\e[2J");
        if (dir == 'u')
        {
            swapper(table, undo, row, col);
        }
        else
        {
            swapper(undo, table, row, col);
        }
        
        play_move(table, row, col, dir);
        play_sum(table, row, col, dir, sum);
        play_rand_num(table, row, col, dir);
        play_over(table, row, col);
        play_print(table, row, col, sum);
        
    }
    //clear the screen
    printf("\e[1;1H\e[2J");

    // if loses
    if (!play_over(table, row, col))
    {
        cout << "Game Over!!!" << endl;
        cout << "Your score is: " << sum << endl;
        
        if (col == 3 && row == 3)
        {
            for (int i = 0; i < 3; i++)
            {
                if (score3[i] < sum)
                {
                    score3[i] = sum;
                    fprintf(pointer3, "%d\n", sum);
                    break;
                }
                
            }
            
        }
        else if (col == 4 && row == 4)
        {
            for (int i = 0; i < 3; i++)
            {
                if (score4[i] < sum)
                {
                    score4[i] = sum;
                    fprintf(pointer4, "%d\n", sum);
                    break;
                }
                
            }
        }
        else if (col == 5 && row == 5)
        {
            for (int i = 0; i < 3; i++)
            {
                if (score5[i] < sum)
                {
                    score5[i] = sum;
                    fprintf(pointer5, "%d\n", sum);
                    break;
                }
                
            }
        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                if (scoreo[i] < sum)
                {
                    scoreo[i] = sum;
                    fprintf(pointer0, "%d\n", sum);
                    break;
                }
                
            }
        }
        
        fclose(pointer3);
        fclose(pointer4);
        fclose(pointer5);
        fclose(pointer0);
    }
    
    //esc pressed
    secondary_menu(table, row, col, false);
    
    return;
}

//load function
int** load()
{
    int num;
    int row, col;
    FILE *ptr = fopen("saves.txt", "r");
    fscanf(ptr,"%d", &row);
    fscanf(ptr,"%d", &col);
    fscanf(ptr,"%d", &num);
    int **table = new int *[row];
    for (int i = 0; i < row; i++)
    {
        table[i] = new int[col];
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            fscanf(ptr,"%d", &num);
            table[i][j] = num;
        }
        
    }
    
    fclose(ptr);
    return table;
}

//save function
void save(int **table, int row, int col, int sum)
{
    FILE *ptr = fopen("saves.txt", "w");
    fprintf(ptr, "%d\n", row);
    fprintf(ptr, "%d\n", col);
    fprintf(ptr, "%d\n", sum);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            fprintf(ptr,"%d\n", table[i][j]);
        }
    }
    fclose(ptr);
    secondary_menu(table, row, col, false);
    return;
}

//scoreboard function
void scoreboard()
{
    FILE *ptr3 = fopen("scoreboard3x3.txt", "r");
    FILE *ptr4 = fopen("scoreboard4x4.txt", "r");
    FILE *ptr5 = fopen("scoreboard5x5.txt", "r");
    FILE *ptr0 = fopen("scoreboard_Other.txt", "r");
    if (ptr3 == NULL)
    {
        //clear the screen
        printf("\e[1;1H\e[2J");
        cout << "There are no records, you should play...." << endl;
        main_menu(false);
    }
    

    int arr3[3] = {0};
    int arr4[3] = {0};
    int arr5[3] = {0};
    int arr0[3] = {0};
    cout << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "3x3: " << endl;
    for (int i = 0; i < 3; i++)
    {
        fscanf(ptr3, "%d", &arr3[i]);
    }
    play_sort(arr3);
    for (int i = 0; i < 3; i++)
    {
        cout << i+1 << "." << arr3[i] << endl;
    }
    cout << "4x4: " << endl;
    for (int i = 0; i < 3; i++)
    {
        fscanf(ptr4, "%d", &arr4[i]);
    }
    play_sort(arr4);
    for (int i = 0; i < 3; i++)
    {
        cout << i+1 << "." << arr4[i] << endl;
    }
    
    cout << "5x5: " << endl;
    for (int i = 0; i < 3; i++)
    {
        fscanf(ptr5, "%d", &arr5[i]);
    }
    play_sort(arr5);
    for (int i = 0; i < 3; i++)
    {
        cout << i+1 << "." << arr5[i] << endl;
    }
    cout << "other formats: " << endl;
    for (int i = 0; i < 3; i++)
    {
        fscanf(ptr0, "%d", &arr0[i]);
    }
    play_sort(arr0);
    for (int i = 0; i < 3; i++)
    {
        cout << i+1 << "." << arr0[i] << endl;
    }

    fclose(ptr3);
    fclose(ptr4);
    fclose(ptr5);
    fclose(ptr0);


    cout << "Press esc the enter for going to the menu...." << endl;
    char key;
    cin >> key;

    while (key != 27)
    {
        cin >> key;
    }

    //clear the screen
    printf("\e[1;1H\e[2J");

    main_menu(false);

    return;
}

//exit function
void exit()
{
    char key;
    cout << "Press esc then enter to exit...";
    while (1 > 0)
    {
        cin >> key;
        if (key == 27)
        {
            exit(1);
        }
    }
    return;
}

//play : menu function
void play_menu(int &row, int &col)
{
    int opt;
    bool first_try = true;
    while (opt > 4 || first_try)
    {
        cout << "Select the size of table: " << endl;
        cout << "1. 3x3     2. 4x4      3. 5x5      4. custom" << endl;
        cout << "Enter your choice number: ";
        cin >> opt;
        first_try = false;
        switch (opt)
        {
        case 1:
            row = 3;
            col = 3;
            break;
        case 2:
            row = 4;
            col = 4;
            break;
        case 3:
            row = 5;
            col = 5;
            break;
        case 4:
            cout << "Enter the number of rows: ";
            cin >> row;
            while (row > 10)
            {
                cout << "Too high enter a lower number: ";
                cin >> row;
            }
            
            cout << "Enter the number of columns: ";
            cin >> col;
            while (col > 10)
            {
                cout << "Too high enter a lower number: ";
                cin >> col;
            }
            
            break;
        default:
            //clear the screen
            printf("\e[1;1H\e[2J");
            cout << "Wrong input! try again." << endl;
            break;
        }
    }
}

//play : move function
void play_move(int** table, int row, int col, char dir)
{
    int temp;
    switch (dir)
    {
    // w for up
    case 'w':
        for (int i = 1; i < row; i++)
        {
            temp = i;
            for (int j = 0; j < col; j++)
            {
                while (temp > 0 && table[temp][j] != 0 && table[temp-1][j] == 0)
                {
                    table[temp-1][j] = table[temp][j];
                    table[temp][j] = 0;
                    temp--;
                }
                temp = i;
            }

        }
        
        break;
    // s for down
    case 's':
        for (int i = row - 2; i >= 0; i--)
        {
            temp = i;
            for (int j = 0; j < col; j++)
            {
                while (temp < row - 1 && table[temp][j] != 0 && table[temp+1][j] == 0)
                {
                    table[temp+1][j] = table[temp][j];
                    table[temp][j] = 0;
                    temp++;
                }
                temp = i;
            }
            
        }
        
        break;
    // a for left
    case 'a':
        for (int i = 0; i < row; i++)
        {
            for (int j = 1; j < col; j++)
            {
                temp = j;
                while (temp > 0 && table[i][temp] != 0 && table[i][temp-1] == 0)
                {
                    table[i][temp-1] = table[i][temp];
                    table[i][temp] = 0;
                    temp--;
                }
                
            }
            
        }
        
        break;

    // d for right
    case 'd':
        for (int i = 0; i < row; i++)
        {
            for (int j = col-2; j >= 0; j--)
            {
                temp = j;
                while (temp < col - 1 && table[i][temp] != 0 && table[i][temp+1] == 0)
                {
                    table[i][temp+1] = table[i][temp];
                    table[i][temp] = 0;
                    temp++;
                }
                
            }
            
        }
        
        break;
    case 'u':
        
        break;
    default:
        cout << "Wrong input! try again." << endl;
        break;
    }
}

//play :sum function
void play_sum(int** table, int row, int col, char dir, int &sum)
{
    switch (dir)
    {
    // w for up
    case 'w':
        for (int i = 0; i < row-1; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (table[i][j] != 0 && table[i][j] == table[i+1][j])
                {
                    table[i][j] = 2*table[i][j];
                    sum += table[i][j];
                    table[i+1][j] = 0;
                }
            }
        }
        play_move(table, row, col, dir);
        break;
    // s for down
    case 's':
        for (int i = row-1; i > 0; i--)
        {
            for (int j = 0; j < col; j++)
            {
                if (table[i][j] != 0 && table[i][j] == table[i-1][j])
                {
                    table[i][j] = 2*table[i][j];
                    sum += table[i][j];
                    table[i-1][j] = 0;
                }
            }
            play_move(table, row, col, dir);
        }
        
        break;
    // d for right
    case 'd':
        for (int i = 0; i < row; i++)
        {
            for (int j = col-1; j > 0; j--)
            {
                if (table[i][j] != 0 && table[i][j] == table[i][j-1])
                {
                    table[i][j] = 2*table[i][j];
                    sum += table[i][j];
                    table[i][j-1] = 0;
                }
            }
            play_move(table, row, col, dir);
        }
        
        break;
    // a for left
    case 'a':
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (table[i][j] != 0 && table[i][j] == table[i][j+1])
                {
                    table[i][j] = 2*table[i][j];
                    sum += table[i][j];
                    table[i][j+1] = 0;
                }
            }
            play_move(table, row, col, dir);
        }

        break;
    case 'u':
        
        break;
    default:
        //clear the screen
        printf("\e[1;1H\e[2J");

        cout << "Wrong input! try again." << endl;
        break;
    }
    return;
}

//play : print
void play_print(int** table, int row, int col, int sum)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (table[i][j] < 10)
            {
                cout << table[i][j] << "    ";
            }
            else if(table[i][j] < 100)
            {
                cout <<  table[i][j] << "   ";
            }
            else if(table[i][j] < 1000)
            {
                cout << table[i][j] << "  ";
            }
            else
            {
                cout << table[i][j] << " ";
            }
        }
        cout << endl;
        cout << endl;
        cout << endl;
    }
    cout << "------------------------------" << endl;
    cout << "Your score is: " << sum;
    cout << endl;
    return;
}

//play : random number
bool play_rand_num(int** table, int row, int col, char dir)
{
    int random = rand() % 2 + 1;
    random *= 2;
    bool placed = false;
    switch (dir)
    {
    case 'w':
        for (int i = row - 1; i >= 0; i--)
        {
            for (int j = 0; j < col; j++)
            {
                if (table[i][j] == 0)
                {
                    table[i][j] = random;
                    return true;
                }
            }
        }
        
        break;
    case 's':
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (table[i][j] == 0)
                {
                    table[i][j] = random;
                    return true;
                }
            }
        }
        
        break;
    case 'd':
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (table[i][j] == 0)
                {
                    table[i][j] = random;
                    return true;
                }
            }
        }
        break;

    case 'a':
        for (int i = 0; i < row; i++)
        {
            for (int j = col-1; j >= 0; j--)
            {
                if (table[i][j] == 0)
                {
                    table[i][j] = random;
                    return true;
                }
            }
        }
        break;
        
    default:
        break;
    }
    return false;
}

//play : game over
bool play_over(int** table, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (table[i][j] == 0)
            {
                return true;
            }
            
        }
        
    }
    for (int i = 0; i < row - 1; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (table[i][j] == table[i+1][j])
            {
                return true;
            }
            
        }
        
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col - 1; j++)
        {
            if (table[i][j] == table[i][j+1])
            {
                return true;
            }
            
        }
        
    }
    return false;
}

//play : sort
void play_sort(int* arr)
{
    int max, imax;
    for (int i = 0; i < 3; i++)
    {
        max = arr[i];
        imax = i;
        for (int j = i+1; j < 3; j++)
        {
            if (arr[j] > max)
            {
                max = arr[j];
                imax = j;
            }
            
        }
        arr[imax] = arr[i];
        arr[i] = max;
    }
    
}

//swapper
void swapper(int** a, int** b, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            a[i][j] = b[i][j];
        }
        
    }
    
}