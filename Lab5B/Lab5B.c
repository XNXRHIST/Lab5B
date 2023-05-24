#include <stdio.h>//Підкллючаємо необхідні для роботи бібліотеки
#include <stdlib.h>
#include <time.h>

void inputArray(int* array, int size) {//Функція для введення елементів масиву з клавіатури
    printf("Введіть елементи масиву:\n");
    for (int i = 0; i < size; i++) {
        printf("a[%d] = ", i + 1);
        scanf_s("%d", &array[i]);
    }
}
void generateRandomArray(int* array, int size) {//Функція для заповнення масиву випадковими числами
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        printf("a[%d] = ", i + 1);
        array[i] = rand() % 201 - 100;
        printf("%d\n", array[i]);
    }
}
int findMaxElementIndex(int* array, int size) {//Функція для знаходження індексу максимального елемента в масиві
    int maxIndex = 0;
    for (int i = 1; i < size; i++) {
        if (array[i] > array[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}
int computeSumBetweenZeros(int* array, int size) {//Функція для обчислення суми додатніх елементів між першим і останнім нульовими елементами масиву
    int firstZeroIndex = -1;
    int lastZeroIndex = -1;

    for (int i = 0; i < size; i++) {//Знаходження індексів першого і останнього нульових елементів
        if (array[i] == 0) {
            if (firstZeroIndex == -1) {
                firstZeroIndex = i;
            }
            else {
                lastZeroIndex = i;
                break;
            }
        }
    }

    printf("firstZeroIndex: %d\n", firstZeroIndex);//Виводить на екран юзера інформацію про нульові індекси 
    printf("lastZeroIndex: %d\n", lastZeroIndex);

    if (firstZeroIndex != -1 && lastZeroIndex != -1) {//Якщо знайдено індекси першого і останнього нульових елементів
        int sum = 0;
        int start, end;
        if (firstZeroIndex < lastZeroIndex) {
            start = firstZeroIndex + 1;
            end = lastZeroIndex;
        }
        else {
            start = lastZeroIndex + 1;
            end = firstZeroIndex;
        }

        for (int i = start; i < end; i++) {//Обчислення суми додатніх елементів між першим і останнім нульовими елементами
            if (array[i] > 0) {
                sum += abs(array[i]);
            }
        }

        return sum;
    }

    return 0;
}
int main() {
    int n;
    printf("Введіть розмір масиву: ");//задання розміру масиву з клавіатури юзера
    scanf_s("%d", &n);

    int* array = (int*)malloc(n * sizeof(int));
    if (array == NULL) {
        printf("Помилка виділення пам'яті\n");
        return 1;
    }

    int option;
    printf("Виберіть спосіб заповнення масиву:\n");//Вибір способу заповнення масиву
    printf("1. Введення з клавіатури\n");
    printf("2. Заповнення випадковими числами\n");
    printf("Ваш вибір: ");
    scanf_s("%d", &option);

    switch (option) {
    case 1:
        inputArray(array, n);
        break;
    case 2:
        generateRandomArray(array, n);
        break;
    default:
        printf("Неправильний вибір\n");//вивід помилки на екран юзера у випадку неправильного вибору способу заповнення масиву
        free(array);
        return 1;
    }

    int maxIndex = findMaxElementIndex(array, n);//Знаходження індексу максимального елемента
    int sumBetweenZeros = computeSumBetweenZeros(array, n);//Обчислення суми додатніх елементів між першим і останнім нульовими елементами
    
    //Виведення результатів на екран юзера
    printf("Номер максимального елемента: %d\n", maxIndex + 1);
    
    if (sumBetweenZeros) {
        printf("Сума додатніх елементів між першим і останнім нульовими елементами: ");

        int firstZeroIndex = -1;
        int lastZeroIndex = -1;

        for (int i = 0; i < n; i++) {
            if (array[i] == 0) {
                if (firstZeroIndex == -1) {
                    firstZeroIndex = i;
                }
                else {
                    lastZeroIndex = i;
                    break;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            if (i == firstZeroIndex + 1) {
                printf("\x1b[33m"); // Встановлюємо жовтий колір
            }
            else if (i == lastZeroIndex) {
                printf("\x1b[0m"); // Повертаємо до стандартного кольору
            }

            printf("%d ", array[i]);
        }

        printf("\n");
        printf("Сума: %d\n", sumBetweenZeros);
    }
    else {
        printf("Немає елементів нульового індекса...\n");
    }
    free(array);//Звільнення пам'яті, виділеної для масиву
    return 0;//Кінець програми
}
