# sample_automat_watering_flow

## Sample automat watering room flow

## Пример автомата полива комнатных цветов

  Полив производится в дневное время
  в течении 3 секунд (агумент функции poliw)

  Датчиком освещенности служит светодиод АЛ307.

  Датчик влажности выполнен из провода ПЭВ диаметром 1мм
  длиной 2х100мм с залуженными рабочими поверхностями.
  Для исключения гальванического эффекта напряжение
  на датчик подается только на время измерения.

  Сигнальный светодиод led подает следующие сигналы:

      - первый:
          * длинный (ночь) : полив запрещен,
          * короткий (день): полив разрешен;

      - второй :
          * длинный (влажно): полив запрещен,
          * короткий (сухо): полив разрешен.

  При аварийной ситуации (нет воды в баке, обрыв шлангов и пр.)
  светодиод led подает сигнал Морзе SOS.

  Если не нужна экономия энергии библиотеку Narcoleptic 
  можно не использовать.

  Применяется плата UNO

