//1. 11. Container With Most Water
#include <vector>
#include <algorithm> // Для std::min и std::max

class Solution {
public:
    int maxArea(std::vector<int>& height) {
        int left = 0;                // Левый указатель
        int right = height.size() - 1; // Правый указатель
        int max_area = 0;            // Максимальная площадь

        while (left < right) {
            // Ширина контейнера
            int width = right - left;
            // Высота контейнера
            int current_height = std::min(height[left], height[right]);
            // Текущая площадь
            int current_area = width * current_height;
            // Обновляем максимальную площадь
            max_area = std::max(max_area, current_area);

            // Жадный выбор: двигаем указатель на меньшую высоту
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }

        return max_area;
    }
};
//Асимптотика: O(n): есть один цикл while, который в худшем случае выполняется n-1 раз, 
//где n — длина входного вектора height.

//Память: O(1): используем константное количество дополнительных переменных, 
//е зависящее от размера входного вектора.


//2. 55. Jump Game
#include <vector>
#include <algorithm>

class Solution {
public:
    bool canJump(std::vector<int>& nums) {
        int max_reach = 0; // Максимальный индекс, до которого можем допрыгнуть

        for (int i = 0; i < nums.size(); ++i) {
            // Если текущий индекс недостижим
            if (i > max_reach) {
                return false; // Мы не можем до него допрыгнуть
            }

            // Обновляем max_reach
            max_reach = std::max(max_reach, i + nums[i]);

            // Если достигли конца
            if (max_reach >= nums.size() - 1) {
                return true; // Можем допрыгнуть до конца
            }
        }

        return false; // Если прошли весь цикл и не достигли конца
    }
};

//Асимптотика (по времени): O(n): есть один цикл for, который выполняется n раз, 
//где n — длина входного вектора nums.
//Память: O(1): используем константное количество дополнительных переменных.