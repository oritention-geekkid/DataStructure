#include <stdio.h>
#include <stdlib.h>

void swap(int *arr, int index1, int index2);
void _percDown(int *arr, int root, int n);
void _mSort(int *arr, int start, int end, int *tmp);
void _qSort(int *arr, int left, int right);

void bubbleSort(int *arr, int length);
void insertionSort(int *arr, int length);
void shellSort(int *arr, int length);
void selectionSort(int *arr, int length);
void heapSort(int *arr, int length);
void mergeSort(int *arr, int length);
void quickSort(int *arr, int length);
void countingSort_instable(int *arr, int length);
void countingSort_stable(int *arr, int length);
void bucketSort(int *arr, int length);
void radixSort(int *arr, int length);

void swap(int *arr, int index1, int index2) {
    int tmp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = tmp;
}
/* 冒泡排序 */
void bubbleSort(int *arr, int length) {
    int ifChanged = 0;
    for (int i=0; i<length; i++) {
        for (int j=0; j<length-i-1;j++) {
            if (arr[j]>arr[j+1]) {
                swap(arr,j,j+1);
                ifChanged = 1;
            }
        }
        if (!ifChanged) return;
    }
    return;
}
/* 插入排序 */
void insertionSort(int *arr, int length) {
    for (int i=1; i<length; i++) {
        int tmp = arr[i];
        int j=i;
        for(;(j>0)&&(arr[j-1]>tmp); j--) {
            arr[j] = arr[j-1];
        }
        arr[j] = tmp;
    }
}
/* 希尔排序 - 使用{1,3,5,7}增量序列 */
void shellSort(int *arr, int length) {
    int increasement[4] = {7,5,3,1};
    int increaseIndex = 0;
    for (int i=increasement[increaseIndex]; increaseIndex<4; i=increasement[++increaseIndex]) {
        for (int j=i; j<length; j++) {
            int tmp = arr[j];
            int k=j;
            for (;k>=i&&arr[k-i]>tmp; k-=i) {
                arr[k] = arr[k-i];
            }
            arr[k] = tmp;
        }
    }
}
/* 选择排序 */
void selectionSort(int *arr, int length) {
    for (int i=0; i<length; i++) {
        int min = i;
        for (int j=i;j<length;j++) {
            if(arr[j]<arr[min]) {
                min = j;
            }
        }
        swap(arr,i,min);
    }
}
/* 堆排序 */
void _percDown(int *arr, int root, int n) {
    // arr==待排数组，root==需要调整的根节点，n==需要调整为最大堆的长度
    int P,maxC;
    int rootValue = arr[root];
    for (P=root;P*2+1<n;P=maxC) {
        maxC = P*2+1;
        if ((maxC!=n-1)&&(arr[maxC]<arr[maxC+1])) {
            maxC++;
        }
        if (rootValue>=arr[maxC]) {
            break;
        } else {
            swap(arr,P,maxC);
        }
    }
    arr[P] = rootValue;
}
void heapSort(int *arr, int length) {
    for (int i=length/2-1; i>=0; i--) {
        _percDown(arr,i,length);
    }
    for (int i=length-1; i>0; i--) {
        swap(arr,0,i);
        _percDown(arr,0,i);
    }

}
/* 归并排序 */
void _mSort(int *arr, int start, int end, int *tmp) {
    int center;
    if (start<end) {
        center = (start+end)/2;
        _mSort(arr, start, center, tmp);
        _mSort(arr, center+1, end, tmp);
        int currentIndex = start;
        int L = start;
        int R = center+1;
        while (L<=center&&R<=end) {
            if (arr[L]<=arr[R]) {
                tmp[currentIndex++] = arr[L++];
            } else {
                tmp[currentIndex++] = arr[R++];
            }
        }
        while (L<=center) {
            tmp[currentIndex++] = arr[L++];
        }
        while (R<=end) {
            tmp[currentIndex++] = arr[R++];
        }
        
        for (int i=start;i<=end;i++) {
            arr[i] = tmp[i];
        }
    }
}
void mergeSort(int *arr, int length) {
    int *tmp;
    tmp = (int *)malloc(length*sizeof(int));
    if (tmp != NULL) {
        _mSort(arr,0,length-1,tmp);
        free(tmp);
    }
    else printf("Error! There is not enough space.");
}
/* 快速排序 */
void _qSort(int *arr, int left, int right) {
    if (left<right) {
        int center = (left+right)/2;
        if (arr[left]>arr[center]) {
            swap(arr,left,center);
        }
        if (arr[left]>arr[right]) {
            swap(arr,left,right);
        }
        if (arr[center]>arr[right]) {
            swap(arr,center,right);
        }
        int key = arr[center];
        swap(arr,center,right-1);  // 将key藏至右边，比较只需考虑left+1~right-2
        int low = left;
        int high = right-1;
        while (1) {
            while (arr[++low]<key);
            while (arr[--high]>key);
            if (low<high) swap(arr,low,high);
            else break;
        }
        if (right-left!=1) {  // 防止当待排序列只有2个数字时，已排好的序列被交换
            swap(arr,low,right-1);  // 将key还回正确位置
        }
        _qSort(arr,left,low-1);
        _qSort(arr,low+1,right);
    }
}
void quickSort(int *arr, int length) {
    _qSort(arr,0,length-1);
}
/* 计数排序 (只能进行正整数的排序) */
#define MAXSIZE_FOR_COUNTINGSORT 100
void countingSort_instable(int *arr, int length) {
    int *countArr = (int *)malloc(MAXSIZE_FOR_COUNTINGSORT*sizeof(int));
    for (int i=0; i<MAXSIZE_FOR_COUNTINGSORT; i++) {
        countArr[i] = 0;
    }
    for (int j=0; j<length; j++) {
        countArr[arr[j]]++;
    }
    int currentIndex = 0;
    for (int k=0; k<length; k++) {
        while (countArr[k]-- > 0) {
            arr[currentIndex++] = k; 
        }
    }
    free(countArr);
}
void countingSort_stable(int *arr, int length) {
    int *countArr = (int *)malloc(MAXSIZE_FOR_COUNTINGSORT*sizeof(int));
    int *sortArr = (int *)malloc((length+1)*sizeof(int)); 
    for (int i=0; i<MAXSIZE_FOR_COUNTINGSORT; i++) {
        countArr[i] = 0;
    }
    for (int j=0; j<length; j++) {
        countArr[arr[j]]++;
    }
    for (int k=1; k<MAXSIZE_FOR_COUNTINGSORT; k++) {
        countArr[k] += countArr[k-1];
    }
    for (int l=length-1; l>=0; l--) {
        sortArr[--countArr[arr[l]]] = arr[l];
    }
    for (int m=0; m<length; m++) {
        arr[m] = sortArr[m];
    }
    free(countArr);
    free(sortArr);
}
/* 桶排序 */
#define MAXSIZE_FOR_BUCKET 100
void bucketSort(int *arr, int length) {
    int *bucket = (int *)malloc(MAXSIZE_FOR_BUCKET*sizeof(int));
    for (int i=0; i<MAXSIZE_FOR_BUCKET; i++) {
        bucket[i] = 0;
    }
    for (int j=0; j<length; j++) {
        bucket[arr[j]]++;
    }
    int currentIndex = 0;
    for(int k=0; k<MAXSIZE_FOR_BUCKET; k++) {
        for (;bucket[k]!=0; bucket[k]--) {
            arr[currentIndex++] = k;
        }
    }
    free(bucket);
}
/* 基数排序 */
#define MAXDIGIT_FOR_RADIXSORT 2
#define RADIX_FOR_RADIXSORT 10

typedef struct Element *ptrToElement;
struct Element {
    int key;
    ptrToElement next;
};
typedef struct BucketHead Bucket;
struct BucketHead {
    ptrToElement head;
    ptrToElement tail;
};
void radixSort(int *arr, int length) {
    Bucket bucket[RADIX_FOR_RADIXSORT];
    for (int i=0; i<RADIX_FOR_RADIXSORT; i++) {
        bucket[i].head = bucket[i].tail = NULL;
    }
    ptrToElement tempNode, tempList = NULL;
    for (int j=0; j<=length-1; j++) {
        tempNode = (ptrToElement)malloc(sizeof(struct Element));
        tempNode->key = arr[j];
        tempNode->next = tempList;
        tempList = tempNode;
    }
    for (int k=1; k<=MAXDIGIT_FOR_RADIXSORT; k++) {
        int di;
        while (tempList) {
            int tmp = tempList->key;
            for (int l=1; l<=k; l++) {
                di = tmp % RADIX_FOR_RADIXSORT;
                tmp /= RADIX_FOR_RADIXSORT;
            }
            tempNode = tempList;
            tempList = tempList->next;
            tempNode->next = NULL;
            if (bucket[di].head == NULL) {
                bucket[di].head = bucket[di].tail = tempNode;
            }
            else {
                bucket[di].tail->next = tempNode;
                bucket[di].tail = tempNode;
            }
        }
        tempList = NULL;
        for  (di=RADIX_FOR_RADIXSORT-1; di>=0; di--) {
            if (bucket[di].head) {
                bucket[di].tail->next = tempList;
                tempList = bucket[di].head;
                bucket[di].head = bucket[di].tail = NULL;
            }
        }
    }
    for (int m=0; m<length; m++) {
        tempNode = tempList;
        arr[m] = tempNode->key;
        tempList = tempList->next;
        free(tempNode);
    }
}
