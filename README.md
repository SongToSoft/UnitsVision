# UnitsVision
Данная программа работает с множеством юнитов, каждый юнит характеризуется своей позицией на 2D поле и направлением куда он смотрит.
Исходя из данных характеристик программа проверяет сколько других унитов видит каждый из них.
Область видимости юнита определяется, как сектор круга, с центром в направлении взгляда юнита.
Каждый такой конус помимо направления характеризуется едиными для всех юнитов параметрами радиусом и углом обзора.

Для того, что бы проверить видит ли юнит1 юнита2 надо определить попадает ли юнит2 в сектор видимости юнита1.
Что бы это сделать надо определить два основных условия:
1) Находится ли юнит2 достаточно близко к юниту1.
    Для определения этого просто проверяется входит ли позиция юнита2 в окружность в центре позиции юнита1 и с заранее определенным радиусом.
2) Хватает ли угла видимости юниту1, что бы заметить юнита2 рядом с собой.
    Для этого условия определяется угол между двумя векторами: (позиция юнита1)->(центр сектора видимости) и (позиция юнита1->позиция юнита2).
    Если данный угол меньше или равен половины угла сектора видимости, то позиция юнита2 попадает в этот сектор.
Данные условия проверяется между всеми юнитами относительно друг-друга. Так и определяется сколько других юнитов видит каждый из них.

Для примера определили шесть юнитов со своими позициями и направлениями. На рисунке представлено примерное расположене юнитов ввиде окружностей и секторами, в которые могут попадать другие юниты.

```
View Distance: 2, View Sector Angle: 135.5
Unit[0] Position: [1, 1], Direction: [0, 1]
Unit[1] Position: [1, 2], Direction: [1, 0]
Unit[2] Position: [-5, -1], Direction: [0.707, 0.707]
Unit[3] Position: [1, -1], Direction: [-0.4, 0.5]
Unit[4] Position: [0, 0], Direction: [0, 1]
Unit[5] Position: [0, -5], Direction: [-1, 0]
Unit[6] Position: [-4, -1], Direction: [-1, -1]

Angle between center sector Unit[0] and Unit[1]: 0
Unit[0] see Unit[1]
Angle between center sector Unit[0] and Unit[3]: 180
Angle between center sector Unit[0] and Unit[4]: 135
Unit[0] see: 1 in area
Angle between center sector Unit[1] and Unit[0]: 90
Unit[1] see: 0 in area
Angle between center sector Unit[2] and Unit[6]: 45
Unit[2] see Unit[6]
Unit[2] see: 1 in area
Angle between center sector Unit[3] and Unit[0]: 38.6598
Unit[3] see Unit[0]
Angle between center sector Unit[3] and Unit[4]: 6.34021
Unit[3] see Unit[4]
Unit[3] see: 2 in area
Angle between center sector Unit[4] and Unit[0]: 45
Unit[4] see Unit[0]
Angle between center sector Unit[4] and Unit[3]: 135
Unit[4] see: 1 in area
Unit[5] see: 0 in area
Angle between center sector Unit[6] and Unit[2]: 45
Unit[6] see Unit[2]
Unit[6] see: 1 in area
```
![screen](https://github.com/SongToSoft/UnitsVision/blob/main/Images/image.png)

Так же в программе есть пример работы данной программы с многопоточностью через std::thread из стандартной библиотеки и сравнение на большом количестве юнитов того, как многопоточность ускоряет работу программы.
```
Elapsed time with multi-thread: 4030 for 5041 units
Elapsed time in one thread: 12304 for 5041 units
```
