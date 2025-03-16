#include <iostream>
#include <vector>

using namespace std;

// 冒泡排序函数，用于对数组进行排序
void bubbleSort(vector<int> &arr) {
    // 数组的长度
    int n = arr.size();

    // 外层循环控制需要比较的轮数
    for (int i = 0; i < n - 1; i++) {
        // 内层循环控制每轮比较的次数
        for (int j = 0; j < n - i - 1; j++) {
            // 如果当前元素比后面的元素大，则交换位置
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    // 待排序的数组
    vector<int> arr = {5, 2, 4, 6, 1, 3};

    // 调用冒泡排序函数进行排序
    bubbleSort(arr);

    // 输出排序后的数组
    for (int i : arr) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
