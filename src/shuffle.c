/*
    Fisher-Yates shuffle による方法
    配列の要素をランダムシャッフルする
*/
void random_shuffle(unsigned short *array, size_t size)
{
    for (size_t i = size; i > 1; --i)
    {
        size_t a = i - 1;
        size_t b = rand() % i;
        SWAP(unsigned int, array[a], array[b]);
    }
}
