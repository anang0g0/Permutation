#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "global.h"
#include "fy.h"

extern unsigned long xor128();
int array_is_unique(const unsigned int *array, size_t size);

/*
    Fisher-Yates shuffle による方法
    配列の要素をランダムシャッフルする
*/
void random_shuffle(unsigned int *array, size_t size)
{
    for (size_t i = size; i > 1; --i)
    {
        size_t a = i - 1;
        size_t b = rand() % i;
        SWAP(int, array[a], array[b]);
    }
}

void merge(unsigned short A[], unsigned short B[], unsigned short left, unsigned short mid, unsigned short right)
{
    unsigned short i = left;
    unsigned short j = mid;
    unsigned short k = 0;
    unsigned short l;
    while (i < mid && j < right)
    {
        if (A[i] <= A[j])
        {
            B[k++] = A[i++];
        }
        else
        {
            B[k++] = A[j++];
        }
    }
    if (i == mid)
    { /* i側のAをBに移動し尽くしたので、j側も順番にBに入れていく */
        while (j < right)
        {
            B[k++] = A[j++];
        }
    }
    else
    {
        while (i < mid)
        { /* j側のAをBに移動し尽くしたので、i側も順番にBに入れていく */
            B[k++] = A[i++];
        }
    }
    for (l = 0; l < k; l++)
    {
        A[left + l] = B[l];
    }
}
void merge_sort(unsigned short A[], unsigned short B[], unsigned short left, unsigned short right)
{
    unsigned short mid;
    if (left == right || left == right - 1)
    {
        return;
    }
    mid = (left + right) / 2;
    merge_sort(A, B, left, mid);
    merge_sort(A, B, mid, right);
    merge(A, B, left, mid, right);
}

/* マージソート */
void merge_sort2(unsigned short array[], int left, int right)
{
    int i, j, k, mid;
    int work[65535]; // 作業用配列
    if (left < right)
    {
        mid = (left + right) / 2;           // 真ん中
        merge_sort2(array, left, mid);      // 左を整列
        merge_sort2(array, mid + 1, right); // 右を整列
        for (i = mid; i >= left; i--)
        {
            work[i] = array[i];
        } // 左半分
        for (j = mid + 1; j <= right; j++)
        {
            work[right - (j - (mid + 1))] = array[j]; // 右半分を逆順
        }
        i = left;
        j = right;
        for (k = left; k <= right; k++)
        {
            if (work[i] < work[j])
            {
                array[k] = work[i++];
            }
            else
            {
                array[k] = work[j--];
            }
        }
    }
}

void merge_sortA();
void merge_sortW();

typedef unsigned int d_type; // ソートするキーの型
#define SWAP0(a, b)      \
    {                    \
        d_type work = a; \
        a = b;           \
        b = work;        \
    }
#define COMPSWAP(a, b)  \
    {                   \
        if ((b) < (a))  \
            SWAP0(a, b) \
    }

#define MIN_TO_WORK               \
    {                             \
        d_type temp;              \
        if (*array_i <= *array_j) \
        {                         \
            temp = *(array_i++);  \
        }                         \
        else                      \
        {                         \
            temp = *(array_j++);  \
        }                         \
        *(work_k++) = temp;       \
    }

#define MAX_TO_WORK              \
    {                            \
        d_type temp;             \
        if (*array_x > *array_y) \
        {                        \
            temp = *(array_x--); \
        }                        \
        else                     \
        {                        \
            temp = *(array_y--); \
        }                        \
        *(work_z--) = temp;      \
    }

void merge1(d_type array[], d_type work[], int left, int mid, int right)
{
    d_type *array_i = array + left, *array_j = array + mid, *work_k = work + left;
    d_type *array_x = array + (mid - 1), *array_y = array + (right - 1), *work_z = work + (right - 1);
    int kosuu = right - left, c;
    for (c = kosuu / 2; c > 0; c--)
    {
        MIN_TO_WORK
        MAX_TO_WORK
    }
    if (kosuu % 2)
    { //データ数が奇数のとき
        if (array_i == array_x)
            *work_k = *array_i;
        else
            *work_k = *array_j;
    }
}

void insertion_sortA(d_type array[], int right)
{
    COMPSWAP(array[0], array[1]) //高速化のため
    int i;
    for (i = 2; i < right; i++)
    {
        int temp = array[i];
        if (array[i - 1] > temp)
        {
            int j = i;
            do
            {
                array[j] = array[j - 1];
                j--;
            } while (j > 0 && array[j - 1] > temp);
            array[j] = temp;
        }
    }
}

void insertion_sortW(d_type *array, d_type *work, int right)
{
    if (array[0] <= array[1])
    { //高速化のため
        work[0] = array[0];
        work[1] = array[1];
    }
    else
    {
        work[0] = array[1];
        work[1] = array[0];
    }
    int i;
    for (i = 2; i < right; i++)
    {
        if (work[i - 1] > array[i])
        {
            int j = i;
            do
            {
                work[j] = work[j - 1];
                j--;
            } while (j > 0 && work[j - 1] > array[i]);
            work[j] = array[i];
        }
        else
            work[i] = array[i];
    }
}

#define UTIKIRI 7
void merge_sortA(d_type array[], d_type work[], int left, int right)
{
    int kosuu = right - left;
    if (kosuu <= UTIKIRI)
    {
        insertion_sortA(array + left, kosuu);
        return;
    }
    int mid = left + kosuu / 2;
    merge_sortW(array, work, left, mid);
    merge_sortW(array, work, mid, right);
    merge1(work, array, left, mid, right);
}

void merge_sortW(d_type array[], d_type work[], int left, int right)
{
    int kosuu = right - left;
    if (kosuu <= UTIKIRI)
    {
        insertion_sortW(array + left, work + left, kosuu);
        return;
    }
    int mid = left + kosuu / 2;
    merge_sortA(array, work, left, mid);
    merge_sortA(array, work, mid, right);
    merge1(array, work, left, mid, right);
}

#define MIN_TO_ARRAY             \
    {                            \
        d_type temp;             \
        if (work[j] <= array[i]) \
        {                        \
            temp = work[j++];    \
        }                        \
        else                     \
        {                        \
            temp = array[i++];   \
        }                        \
        array[k++] = temp;       \
    }

void merge0(d_type array[], d_type work[], int mid, int right)
{
    int i = mid, j = 0, k = 0;
    if (work[mid - 1] <= array[right - 1])
    {
        while (j < mid)
            MIN_TO_ARRAY
    }
    else
    {
        while (i < right)
            MIN_TO_ARRAY
        while (j < mid)
            array[k++] = work[j++];
    }
}

//追加の作業記憶領域を，データの記憶領域のほぼ1/2に抑えた
void sorta(d_type array[], int right)
{
    if (right <= 3)
    {
        if (right >= 2)
            insertion_sortA(array, right);
        return;
    }
    int mid = (right + 1) / 2;
    d_type *work = malloc(mid * sizeof(d_type));
    merge_sortA(array + mid, work, 0, right - mid);
    merge_sortW(array, work, 0, mid);
    merge0(array, work, mid, right);
    free(work);
}

/* キーは0からMまでの範囲の整数 */
#define M2 8192

/*
分布数え上げソート
配列aを整列する。結果は配列bが保持する。

@param int a ソート対象の配列
@param int b 作業用の配列
@param int n ソート対象の配列の要素数
*/
void counting_sort(unsigned int a[], unsigned short b[], int n)
{
    int i;
    /* キーの分布を数え上げるための配列 */
    int count[M2 + 1];

    /* カウンタ(キーの出現回数)を初期化 */
    for (i = 0; i <= M2; i++)
        count[i] = 0;

    /* キーの出現回数 */
    for (i = 0; i < n; i++)
        count[a[i]]++;

    /* 数え上げたキーの累積度数分布 */
    for (i = 0; i < M2; i++)
    {
        count[i + 1] += count[i];
    }

    /* 度数分布に従ってデータを配列aから配列bにコピーする */
    for (i = n - 1; i >= 0; i--)
    {
        b[--count[a[i]]] = a[i];
    }
}

void countSort(unsigned int array[], int array_size)
{

    int sorted_array[array_size];

    // calculate how many elements should be prepared
    int max = array[0];
    for (int i = 1; i < array_size; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }

    // prepare array for counting
    int count[max + 1];
    for (int i = 0; i < max + 1; i++)
    {
        count[i] = 0;
    }

    // couting
    for (int i = 0; i < array_size; i++)
    {
        count[array[i]]++;
    }

    // make a hash to output sorted index
    for (int i = 1; i < max + 1; i++)
    {
        count[i] += count[i - 1];
    }

    // sorting
    for (int i = 0; i < array_size; i++)
    {
        sorted_array[count[array[i]] - 1] = array[i];
        count[array[i]]--;
    }

    // copy sorted elements to the original array
    for (int i = 0; i < array_size; i++)
    {
        array[i] = sorted_array[i];
    }
}

#define SIZE_OF_ARRAY2(array) (sizeof(array) / sizeof(array[0]))
/*
int compareInt(const void* a, const void* b)
{
    int aNum = *(int*)a;
    int bNum = *(int*)b;

    return aNum - bNum;
}
*/

/*
    配列内に値の重複がないかどうかを返す

    ※ソート済みでなければならない

    引数
        array: 対象の配列
        size:  array の要素数
    戻り値
        重複がなければ true、重複があれば false
*/
int array_is_unique(const unsigned int *array, size_t size)
{
    for (size_t i = 0; i < size - 1; ++i)
    {
        if (array[i] == array[i + 1])
        {
            printf("@@@@@ %lu %d\n", i, array[i]);
            return 0;
        }
    }

    return 1;
}

// y: シード値（32ビット整数）
unsigned int yy;
// 32ビット版xorshift (xorshift32) のメイン処理
unsigned int xorshift32()
{
    yy = yy ^ (yy << 13);
    yy = yy ^ (yy >> 17);
    yy = yy ^ (yy << 15);
    return yy;
}

uint16_t xor16()
{
    static uint16_t x = 1, y = 1;
    uint16_t t = (x ^ (x << 5));
    x = y;
    return y = (y ^ (y >> 1)) ^ (t ^ (t >> 3));
}

void merge_rand(unsigned int *a, int n)
{
    unsigned short c[N] = {0};
    unsigned short b[N] = {0};
    int i,cc=0,count=0;
    time_t t;
// srand(clock());

    
    yy = time(&t);
    //for (i = 0; i < n; i++){
    while(count!=N)
    {
    cc = xorshift32() % N;
    if(a[cc]==0){
        a[cc]=count++;
    }
    }
    /*
    for (i = 0; i < n; i++)
    {
        c[a[i]] = i;
    }

    {
        
        // memcpy(w,a,sizeof(a));
        // random_shuffle(a, N);
        // merge_sort(a, b, 0, n);
         sorta(a, N);
        // counting_sort(a,b,n);
        //countSort(a, N);
        */
        /*
        if (array_is_unique(a, N) == 0)
        {
            memset(a, 0, N);
            yy = time(&t);
            for (i = 0; i < n; i++)
                a[i] = xorshift32() % 1000000;
            for (i = 0; i < n; i++)
            {
                c[a[i]] = i;
            }
        }
        */
//    }

  //  for (i = 0; i < n; i++)
  //      a[i] = c[a[i]];
    // for (i = 0; i < n; i++)
    //     a[i] = b[i];
}
