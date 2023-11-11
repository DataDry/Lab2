#include <random>
#include <iostream>
#include <chrono>
#include <conio.h>
using namespace std;
const short int N = 100; // Для размеров
int mainArray[N]; // для большинства пунктов
int unsortedArray[N]; // Для пункта 3
int PHWArray[N]; // Для ИДЗ
std::chrono::steady_clock::time_point clockStart;
std::chrono::steady_clock::time_point clockStop;
//
// Реализация quick sort
//
int Partition(int arr[], short int start, short int end) // Дополнительная функция для quick sort (опопрный эл-т)
{

    short int pivot = arr[start];

    short int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }

    // Придаём опорному элементу правильноое положение
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);

    // Сортировка левой и правой частей опорного элемента
    short int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {

        while (arr[i] <= pivot) {
            i++;
        }

        while (arr[j] > pivot) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }

    return pivotIndex;
}

void Quick_Sort(int arr[], short int start, int end) // Реализация quick sort
{

    // Дефолтный случай
    if (start >= end)
        return;

    // Разделение массива
    short int p = Partition(arr, start, end);

    // Сортировка левой части
    Quick_Sort(arr, start, p - 1);

    // Сортировка правой части
    Quick_Sort(arr, p + 1, end);
}

int Max_Min_Search(int mass[], bool needMin) { // Поиск минимального и максимального для пункта 4
    short int max = mass[0];
    short int min = mass[0];
    if (needMin) {
        for (short int i = 1; i < N; i++)
        {
            if (mass[i] < min) {
                min = mass[i];
            }     
        }
        return min;
    }
    else {
        for (short int i = 1; i < N; i++)
        {
            if (mass[i] > max) {
                max = mass[i];
            }
        }
        return max;
    }
}
unsigned short int a = -1;
int Binary_Search(int arr[], short int x, short int low, int high)
{
    short int mid;
    if (low > high)
        return -1;
    else
        mid = (low + high) / 2;
    if (x == arr[mid])
        return mid;
    else if (x > arr[mid])        // x справа
        return Binary_Search(arr, x, mid + 1, high);
    else                               // x слева
        return Binary_Search(arr, x, low, mid - 1);
}
void Insertion_Sort(int arr[], short int n)
{
    short int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        // Переместить элементы arr[0..i-1], которые больше ключа, на одну позицию вперед от их текущей позиции
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
void Task1(){
	//
	// Пункт 1. Создаём целочисленный массив размерности N. Элементы массива должны принимать случайное значение в диапазоне от -99 до 99.
	//
	random_device rd;   // non-deterministic generator
	mt19937 gen(rd());  // to seed mersenne twister.
	uniform_int_distribution<> dist(-99, 99); // distribute results between first and second arguments inclusive.
	for (short int i = 0; i < N; i++) {
		mainArray[i] = dist(gen);
        unsortedArray[i] = dist(gen);
        PHWArray[i] = dist(gen);
	}
}

void Task2() {
	//
	// Пункт 2. Отсортируем заданный в пункте 1 массив (от меньшего к большему). Определить время, затраченное на сортировку, используя библиотеку chrono.
	//
	clockStart = chrono::high_resolution_clock::now();
    Quick_Sort(mainArray, 0, N-1);
	clockStop = chrono::high_resolution_clock::now();
	cout << "Elapsed microseconds (Quick sort): " << (chrono::duration_cast<chrono::microseconds>(clockStop - clockStart).count()) << "us\n\n\nPHW:\n";

    clockStart = chrono::high_resolution_clock::now();
    Insertion_Sort(PHWArray, N);
    clockStop = chrono::high_resolution_clock::now();
    cout << "Elapsed microseconds (Insertion sort(PHW)): " << (chrono::duration_cast<chrono::microseconds>(clockStop - clockStart).count()) << "us\n";
}

int maxx, minn;
void Task3() {
    //
    // Пункт 3. Найдём максимальный и минимальный элемент массива. Подсчитаем время поиска этих элементов в отсортированном массиве и неотсортированном, используя библиотеку chrono.
    //
    clockStart = chrono::high_resolution_clock::now();
    cout << "Max: " << mainArray[N-1] << " || Min: " << mainArray[0] << "\n";
    clockStop = chrono::high_resolution_clock::now();
    cout << "Elapsed microseconds (for Task 3, sorted array): " << (chrono::duration_cast<chrono::microseconds>(clockStop - clockStart).count()) << "us\n\n";

    clockStart = chrono::high_resolution_clock::now();
    maxx = Max_Min_Search(unsortedArray, false), minn = Max_Min_Search(unsortedArray, true);
    cout << "Max: " << maxx << " || Min: " << minn << "\n";
    clockStop = chrono::high_resolution_clock::now();
    cout << "Elapsed microseconds (for Task 3, unsorted array): " << (chrono::duration_cast<chrono::microseconds>(clockStop - clockStart).count()) << "us\n";
}

void Task4() {
    //
    // Пункт 4. Выведем среднее значение (если необходимо, число округлим) максимального и минимального значения в отсортированном и неотсортированном. Выведем индексы всех элементов, которые равны этому значению, и их количество
    //
    clockStart = chrono::high_resolution_clock::now();
    int avg = (mainArray[N-1] + mainArray[0]) / 2;
    cout << "Average of maximum and minimum values (sorted array): " << avg << "\n";
    short int k = 0;
    for (short int i = 0; i < N; i++)
    {
        if (mainArray[i] == (avg)) {
            printf("%d|", i); k++;
        }
    } cout << "\nAmount: " << k << "\n";
    clockStop = chrono::high_resolution_clock::now();
    cout << "Elapsed microseconds (for Task 4, sorted array): " << (chrono::duration_cast<chrono::microseconds>(clockStop - clockStart).count()) << "us\n\n";

    clockStart = chrono::high_resolution_clock::now();
    maxx = Max_Min_Search(unsortedArray, false), minn = Max_Min_Search(unsortedArray, true);
    cout << "Average of maximum and minimum values (unsorted array): " << (maxx + minn) / 2 << "\n";
    k = 0;
    for (short int i = 0; i < N; i++)
    {
        if (unsortedArray[i] == (maxx + minn) / 2) {
            printf("%d|", i); k++;
        }
    } cout << "\nAmount: " << k << "\n";
    clockStop = chrono::high_resolution_clock::now();
    cout << "Elapsed microseconds (for Task 4, unsorted array): " << (chrono::duration_cast<chrono::microseconds>(clockStop - clockStart).count()) << "us\n";
}

void Task5() {
    //
    // Пункт 5. Выводем количество элементов в отсортированном массиве, которые меньше числа a, которое инициализируется пользователем.
    //
    short int a;
    cout << "Enter a number to show the quantity of integers in the array that are less than the specified one:\n";
    cin >> a;
    short int k = 0;
    for (short int i = 0; i < N; i++) {
        if (mainArray[i] < a) {
            k++;
        }
        else { break; }
    }
    cout << "\nQuantity: " << k << "\n";
}

void Task6() {
    //
    // Пункт 6. Выводем количество элементов в отсортированном массиве, которые больше числа b, которое инициализируется пользователем.
    //
    short int a;
    cout << "Enter a number to show the quantity of integers in the array that are bigger than the specified one:\n";
    cin >> a;
    short int k = 0;
    for (short int i = 0; i < N; i++) {
        if (mainArray[i] > a) k++;
    }
    cout << "\nQuantity: " << k << "\n";
}

short int permanentc;
void Task7() {
    //
    // Пункт 7(*). Выведем информацию о том, есть ли введенное пользователем число в отсортированном массиве. Реализуем алгоритм бинарного поиска. Сравним скорость его работы с обычным перебором.
    //
    short int c;
    cout << "Enter a number to get it's index in a sorted array:\n";
    cin >> c;
    permanentc = c;
    /*__asm {
        mov  eax, [c]
        mov[permanentc], eax
    }*/
    clockStart = chrono::high_resolution_clock::now();
    c = Binary_Search(mainArray, c, 0, N-1);
    if (c == -1) { cout << "[BS]Specified number doesnt present in the array"; }    // BS AKA binary search, BF AKA bruteforce
    else { cout << "[BS]Specified number does present in the array. Index of that number is: " << c; }
    clockStop = chrono::high_resolution_clock::now();
    cout << "\nElapsed microseconds (for Task 7, binary search): " << (chrono::duration_cast<chrono::microseconds>(clockStop - clockStart).count()) << "us\n";

    clockStart = chrono::high_resolution_clock::now();
    short int i;
    for (i = 0; i < N; i++) {
        if (mainArray[i] == permanentc) {
            cout << "\n[BF]Specified number does present in the array. Index of that number is: " << i; i=102;
        }
        
    }
    if (i == N) {
        cout << "\n[BF]Specified number doesnt present in the array";}
    clockStop = chrono::high_resolution_clock::now();
    cout << "\nElapsed microseconds (for Task 7, bruteforce): " << (chrono::duration_cast<chrono::microseconds>(clockStop - clockStart).count()) << "us\n";
}

void Task8(){
    //
    // Пункт 8. Поменяем местами элементы массива, индексы которых вводит пользователь. Выведем скорость обмена, используя библиотеку chrono.
    //
    short int x, y;
    cout << "Enter the indexes of the numbers X and Y:\n";
    cin >> x >> y;
    clockStart = chrono::high_resolution_clock::now();
    cout << "X = " << mainArray[x] << " Y = " << mainArray[y] << "\nChanging places...\n";
    short int buf;
    buf = mainArray[x];
    mainArray[x] = mainArray[y];
    mainArray[y] = buf;
    cout << "X = " << mainArray[x] << " Y = " << mainArray[y] << "\n";
    clockStop = chrono::high_resolution_clock::now();
    cout << "\nElapsed microseconds: " << (chrono::duration_cast<chrono::microseconds>(clockStop - clockStart).count()) << "us\n";
}
int main() {
    short int MenuPick;
    __asm {menupick:};
    cout << "\n1. Task 1\n2. Task 2\n3. Task 3\n4. Task 4\n5. Task 5\n6. Task 6\n7. Task 7\n8. Task 8\n0. Exit\n\n";
    //cin >> MenuPick; // Чтобы раскомментировать это, следует внести изменения в следующий switch, в частности, с '1' на 1 и закомментить _getch
    MenuPick = _getch();
    switch (MenuPick) {
    case('1'):
        system("cls"); Task1(); system("cls"); cout << "Task 1 done. Going back to menu.\n"; __asm {jmp menupick};
    case('2'):
        system("cls"); cout << "---Task 2---\n\n"; Task2(); __asm {jmp menupick};
    case('3'):
        system("cls"); cout << "---Task 3---\n\n"; Task3(); __asm {jmp menupick};
    case('4'):
        system("cls"); cout << "---Task 4---\n\n"; Task4(); __asm {jmp menupick};
    case('5'):
        system("cls"); cout << "---Task 5---\n\n"; Task5(); __asm{jmp menupick};
    case('6'):
        system("cls"); cout << "---Task 6---\n\n"; Task6(); __asm{jmp menupick};
    case('7'):
        system("cls"); cout << "---Task 7---\n\n"; Task7(); __asm{jmp menupick};
    case('8'):
        system("cls"); cout << "---Task 8---\n\n"; Task8(); __asm{jmp menupick};
    case('0'):
        system("cls"); exit(0);
    default:
        system("cls"); __asm {jmp menupick};
    }
}
