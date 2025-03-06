import sys
print(sys.executable)
print(sys.version)

import numpy as np
from PIL import Image

# Загрузка изображения с использованием библиотеки Pillow (т.к. numpy не умеет загружать изображения)
# Pillow нужна для преобразования изображения в массив numpy и обратно.
img = Image.open("cats.jpg")
img_array = np.array(img)


# --- Шаг 1: Определение цветов фона. ---

# У нас желтый и оранжевый фон.  Получим соответствующие RGB значения.
# Важно: смотрим цвета *в массиве numpy*, а не на исходном изображении,
# т.к. сжатие может немного изменить цвета.

# Находим размеры изображения, чтобы разделить его на 4 квадранта
height, width, _ = img_array.shape
half_height = height // 2
half_width = width // 2

# Извлекаем 4 квадранта
quadrant1 = img_array[:half_height, :half_width]
quadrant2 = img_array[:half_height, half_width:]
quadrant3 = img_array[half_height:, :half_width]
quadrant4 = img_array[half_height:, half_width:]
# print("q1:", quadrant1[0,0,:])  # Значения пикселей
# print("q2:",quadrant2[0,0,:])  # для каждого квадранта
# print("q3:",quadrant3[0,0,:])
# print("q4:",quadrant4[0,0,:])


# Определяем цвета фона (после ручного просмотра img_array)
yellow_bg = np.array([252, 207, 57])
orange_bg = np.array([241, 147, 45])



# --- Шаг 2: Создание масок для фона и переднего плана. ---

# Определяем допуск (насколько цвет может отличаться и все еще считаться фоном)
tolerance = 55  # Увеличенный допуск важен для обработки сглаживания и небольших цветовых вариаций.

# Создаем маски для каждого цвета фона. Используем np.abs и .all(axis=2) для
# сравнения RGB значений, а затем объединяем их.
yellow_mask = np.all(np.abs(img_array - yellow_bg) <= tolerance, axis=2)
orange_mask = np.all(np.abs(img_array - orange_bg) <= tolerance, axis=2)
background_mask = yellow_mask | orange_mask

# --- Шаг 3: Применение маски для создания прозрачности фона. ---

# Преобразуем в RGBA (если еще нет), чтобы работать с прозрачностью. Pillow хорошо это делает.
if img_array.shape[2] == 3:  # Проверяем, есть ли уже альфа-канал
    img_rgba = np.concatenate([img_array, np.full((img_array.shape[0], img_array.shape[1], 1), 255, dtype=np.uint8)], axis=2)
else:
	img_rgba = img_array

# Применяем маску: устанавливаем альфа-канал в 0, где маска фона True.
img_rgba[background_mask, 3] = 0


# --- Шаг 4: Сохранение или отображение результата. ---
# Преобразуем обратно в объект Image из Pillow для сохранения/отображения.
result_image = Image.fromarray(img_rgba)
result_image.save("cats_transparent.png")  # Сохраняем как PNG для поддержки прозрачности
result_image.show()  # Отображаем изображение (необязательно)

print("Удаление фона завершено. Сохранено как cats_transparent.png")