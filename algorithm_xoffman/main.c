#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100

// Структура хэш-таблицы
typedef struct
{
    char key;
    char data[256];
} Hash_table;

Hash_table *table;
int counter_of_table = 0;

// Структура узла в двоичном дереве
struct MinHeapNode
{
    char data;
    unsigned frequency;
    struct MinHeapNode *left, *right;
};

// Структура мин-кучи
typedef struct
{
    unsigned size;
    unsigned capacity;
    struct MinHeapNode **array;
} MinHeap;

// Создание хэш-таблицы
void create_hash_table(const int size)
{
    table = (Hash_table *)malloc(sizeof(Hash_table) * size);
}

// Удаление хэш-таблицы
void delete_hash_table(const int size)
{
    free(table);
}

// Создание нового узла в двоичном дереве
struct MinHeapNode *newNode(char data, unsigned frequency)
{
    struct MinHeapNode *node = (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));
    node->left = node->right = NULL;
    node->data = data;
    node->frequency = frequency;
    return node;
}

// Создание мин-кучи
MinHeap *createMinHeap(unsigned capacity)
{
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode **)malloc(minHeap->capacity * sizeof(struct MinHeapNode *));
    return minHeap;
}

// Обмен двух узлов в мин-куче
void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b)
{
    struct MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

// Просеивание узла вниз в мин-куче
void minHeapify(MinHeap *minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;
    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;
    if (smallest != idx)
    {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Проверка, имеет ли куча размер 1
int isSizeOne(MinHeap *minHeap)
{
    return (minHeap->size == 1);
}

// Извлечение узла с минимальной частотой из мин-кучи
struct MinHeapNode *extractMin(MinHeap *minHeap)
{
    struct MinHeapNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// Вставка нового узла в мин-кучу
void insertMinHeap(MinHeap *minHeap, struct MinHeapNode *minHeapNode)
{
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->frequency < minHeap->array[(i - 1) / 2]->frequency)
    {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// Построение мин-кучи и инициализация узлов
MinHeap *buildMinHeap(char data[], int frequency[], int size)
{
    MinHeap *minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], frequency[i]);
    minHeap->size = size;
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
    return minHeap;
}

// Проверка, является ли узел листом
int isLeaf(struct MinHeapNode *root)
{
    return !(root->left) && !(root->right);
}

// Построение дерева Хаффмана
struct MinHeapNode *buildHuffmanTree(char data[], int frequency[], int size)
{
    struct MinHeapNode *left, *right, *top;
    MinHeap *minHeap = buildMinHeap(data, frequency, size);
    while (!isSizeOne(minHeap))
    {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

// Печать кодов Хаффмана от корня дерева до текущего узла
void printCodes(struct MinHeapNode *root, int arr[], int top)
{
    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (isLeaf(root))
    {
        table[counter_of_table].key = root->data;
        printf("%c: ", root->data);
        for (int i = 0; i < top; ++i)
        {
            printf("%d", arr[i]);
            table[counter_of_table].data[i] = arr[i] + '0';
        }
        printf("\n");
        table[counter_of_table].data[top] = '\0';
        counter_of_table++;
    }
}

// Построение дерева Хаффмана и вывод кодов для каждого символа
void HuffmanCodes(char data[], int frequency[], int size)
{
    struct MinHeapNode *root = buildHuffmanTree(data, frequency, size);
    int arr[MAX_TREE_HT], top = 0;
    printCodes(root, arr, top);
}

// Возвращаем символы и количество каждого
void chars_count(int **frequency, char **data, char *string, int count)
{
    int t = 0;
    char *symbols = (char *)malloc(sizeof(char) * count);
    for (int i = 0; i < strlen(string); i++)
    {
        if (strchr(symbols, string[i]) == NULL)
        {
            (*data)[t] = string[i];
            symbols[t] = string[i];
            (*frequency)[t++] = 1;
        }
        else
        {
            for (int j = 0; j < t; j++)
            {
                if ((*data)[j] == string[i])
                {
                    (*frequency)[j]++;
                }
            }
        }
    }
    free(symbols);
}

// Считаем количество символов
int count_of_distinct_symbols(char *str)
{
    int count = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        count++;
        for (int j = 0; j < i; j++)
        {
            if (str[i] == str[j])
            {
                count--;
                break;
            }
        }
    }
    return count;
}

void writeToFile(const char *filename, const char *data, int flag)
{
    FILE *file;
    if (flag == 0)
        file = fopen(filename, "w");
    else
        file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("Error open the file!\n");
        return;
    }

    if (flag)
    {
        fprintf(file, "\n");
    }

    fprintf(file, "%s ", data);
    fclose(file);
    printf("Data write down to file!\n");
}

void code_string(const char *string_to_code, const int size)
{
    char finall_string[2048];
    size_t counter = 0;
    for (int i = 0; i < strlen(string_to_code); i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (string_to_code[i] == table[j].key)
            {
                for (int k = 0; k < strlen(table[j].data); k++)
                {
                    finall_string[counter++] = table[j].data[k];
                }
                finall_string[counter++] = ' ';
                break;
            }
        }
    }
    finall_string[counter] = '\0';
    printf("\n\n%s\n\n", finall_string);
    writeToFile("output.txt", finall_string, 0);
}

void decode_string(const char *encoded_string, const Hash_table *table, int table_size)
{
    int encoded_length = strlen(encoded_string);
    char *decoded_string = (char *)malloc(sizeof(char) * (encoded_length + 1));
    int decoded_length = 0;

    char temp[256];
    int t = 0;

    for (int i = 0; i < encoded_length; i++)
    {
        if (encoded_string[i] == ' ')
        {
            temp[t] = '\0';
            for (int j = 0; j < table_size; j++)
            {
                if (strlen(table[j].data) == strlen(temp) && strcmp(table[j].data, temp) == 0)
                {
                    decoded_string[decoded_length++] = table[j].key;
                    temp[t] = ' ';
                    t = 0;
                    memset(temp, 0, sizeof(temp));
                    break;
                }
            }
        }
        else
        {
            temp[t++] = encoded_string[i];
        }
    }

    decoded_string[decoded_length] = '\0';
    printf("\nDecoded string: %s\n", decoded_string);
    writeToFile("output.txt", decoded_string, 1);
    free(decoded_string);
}

int main()
{
    char *str = "hello world this programm is huffmans comprassing";
    char buffer[2048];
    const int size = count_of_distinct_symbols(str);

    create_hash_table(size);

    char *data = (char *)malloc(sizeof(char) * size);
    int *frequency = (int *)malloc(sizeof(int) * size);

    chars_count(&frequency, &data, str, size);

    /* for (int i = 0; i < size; i++)
    {
        printf("%c - %d\n", data[i], frequency[i]);
    }

    printf("\n"); */

    HuffmanCodes(data, frequency, size);

    for (int i = 0; i < size; i++)
    {
        printf("%c: %s\n", table[i].key, table[i].data);
    }

    code_string(str, size);

    FILE *file;
    file = fopen("output.txt", "r");
    if (file == NULL)
    {
        printf("Ошибка открытия файла\n");
    }

    fgets(buffer, 2048, file);

    printf("\n%s\n", str);

    decode_string(buffer, table, size);

    fclose(file);
    free(data);
    free(str);
    free(frequency);
    delete_hash_table(size);

    return 0;
}