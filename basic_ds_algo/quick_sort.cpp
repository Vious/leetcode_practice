#include <vector>
#include <iostream>
#include <random>


int partition(std::vector<int> &nums, int low, int high) {
    int pivot = nums[high];
    int left = low - 1;

    for (int right = low; right < high; right++) {
        if (nums[right] < pivot) {
            left++;
            std::swap(nums[left], nums[right]);
        }
    }
    std::swap(nums[left + 1], nums[high]);
    return left + 1;
}


void quickSort(std::vector<int> &nums, int low, int high) {
    if (low < high) {
        int index = partition(nums, low, high);
        quickSort(nums, low, index - 1);
        quickSort(nums, index + 1, high);
    }
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    int maxNum = 500;
    std::uniform_int_distribution<> dis(1, maxNum);
    std::vector<int> nums;
    for (int i = 0; i < maxNum; i++) {
        nums.emplace_back(dis(gen));
    }
    std::cout << "Random nums: ";
    for (auto ele : nums) {
        std::cout << ele << " ";
    }
    std::cout << std::endl;
    quickSort(nums, 0, nums.size() - 1);
    std::cout << "Sorted: ";
    for (auto ele : nums) {
        std::cout << ele << " ";
    }
    std::cout << std::endl;

    return 0;
}