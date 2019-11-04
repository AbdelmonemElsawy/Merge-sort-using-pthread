#include <iostream>
#include <pthread.h>
#include <string>
#include <stdio.h>

using namespace std;

#define MAX 1000
int nums[MAX];
int res[MAX];
int n;
const char * file = "input.txt";
typedef struct
{
    int high, low;
}  arrayData;

void mergeArray(int low, int mid, int high)
{
    int i = low;
    int j = mid + 1;
    int k = 0;
    while(i != mid + 1 && j != high + 1)
    {
        if(nums[i] < nums[j])
        {
            res[k++] = nums[i++];
        }
        else
        {
            res[k++] = nums[j++];
        }
    }
    while(i != mid + 1)
    {
        res[k++] = nums[i++];
    }
    while(j != high + 1)
    {
        res[k++] = nums[j++];
    }

    for(i = 0; i < high - low + 1; i++)
    {
        nums[low + i] = res[i];
    }
}

void * mergeSort(void * data)
{
    arrayData* temp = (arrayData *) data;
    int high = temp->high;
    int low = temp->low;
    pthread_t thread1, thread2;
    int mid = (high + low) / 2;
    if(low < high)
    {
        arrayData data1, data2;
        //first half.
        data1.low = low;
        data1.high = mid;
        //second half.
        data2.low = mid + 1;
        data2.high = high;
        pthread_create(&thread1, NULL, mergeSort,(void *) &data1);
        pthread_create(&thread2, NULL, mergeSort,(void *) &data2);

        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
        mergeArray(low, mid, high);
    }
}
int main()
{
    freopen(file, "r", stdin);
    cin >> n;
    for(int i= 0; i < n; i++)
    {
        cin >> nums[i];
    }

    arrayData d1;
    d1.low = 0;
    d1.high = n - 1;

    // main thread.
    pthread_t thread;
    pthread_create(&thread, NULL, mergeSort, (void *)&d1);
    pthread_join(thread, NULL);
    //mergeArray(0, (n - 1)/2, n - 1);
    for(int i = 0; i < n; i++)
    {
        cout << nums[i] << " ";
    }
    cout << endl;
    return 0;
}
