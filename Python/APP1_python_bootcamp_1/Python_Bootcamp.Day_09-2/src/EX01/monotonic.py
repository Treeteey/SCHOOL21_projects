import os
import sys
import ctypes

# Для Windows
if os.name == 'nt':
    # Загружаем библиотеку kernel32, которая предоставляет функции для работы с временем
    _time = ctypes.windll.kernel32

    # Проверяем, доступна ли функция GetTickCount64 (поддерживается начиная с Windows Vista)
    if hasattr(_time, 'GetTickCount64'):
        # Определяем функцию monotonic, возвращающую время в миллисекундах, преобразованных в секунды
        def monotonic():
            return _time.GetTickCount64() * 1e-3  # Переводим миллисекунды в секунды
    else:
        # Для старых версий Windows, где доступна только GetTickCount
        def monotonic():
            ticks = _time.GetTickCount()  # Получаем текущее количество миллисекунд
            if ticks < monotonic.last:  # Проверяем переполнение 32-битного счетчика
                monotonic.delta += 2**32  # Увеличиваем дельту на максимальное значение счетчика
            monotonic.last = ticks  # Обновляем последнее значение
            return (ticks + monotonic.delta) * 1e-3  # Возвращаем время в секундах
        
        # Инициализируем вспомогательные переменные для обработки переполнения
        # хранит значения между вызовами функциями
        # АТРИБУТЫ ФУНКЦИИ - как атрибуты класса
        # как static в c++
        monotonic.last = 0
        monotonic.delta = 0

# Для macOS
elif sys.platform == 'darwin':
    # Загружаем библиотеку libc (стандартная библиотека на macOS)
    libc = ctypes.CDLL('libc.dylib')

    # Описание структуры TimebaseInfo, которая хранит множитель и делитель для перевода времени
    class TimebaseInfo(ctypes.Structure):
        _fields_ = [("numer", ctypes.c_uint32),  # Множитель
                    ("denom", ctypes.c_uint32)]  # Делитель

    # Определяем функцию monotonic для macOS
    def monotonic():
        if monotonic.factor is None:  # Если фактор еще не инициализирован
            timebase = TimebaseInfo()
            libc.mach_timebase_info(ctypes.byref(timebase))  # Заполняем структуру множителя и делителя
            monotonic.factor = timebase.numer / timebase.denom * 1e-9  # Вычисляем фактор перевода в секунды
        return libc.mach_absolute_time() * monotonic.factor  # Возвращаем время в секундах
    
    # Инициализация фактора (изначально None)
    monotonic.factor = None

# Для Linux
elif sys.platform.startswith('linux'):
    # Константа CLOCK_MONOTONIC из заголовка <time.h>
    CLOCK_MONOTONIC = 1

    # Описание структуры Timespec, которая используется для работы с clock_gettime
    class Timespec(ctypes.Structure):
        _fields_ = [("tv_sec", ctypes.c_long),  # Секунды
                    ("tv_nsec", ctypes.c_long)]  # Наносекунды

    # Загружаем библиотеку libc (стандартная библиотека на Linux)
    libc = ctypes.CDLL('libc.so.6')

    # Определяем функцию monotonic для Linux
    def monotonic():
        timespec = Timespec()  # Создаем экземпляр структуры Timespec
        # Вызываем функцию clock_gettime для получения времени с использованием CLOCK_MONOTONIC
        if libc.clock_gettime(CLOCK_MONOTONIC, ctypes.byref(timespec)) != 0:
            raise OSError("clock_gettime failed")  # Если функция вернула ошибку
        # Возвращаем время в секундах, преобразуя наносекунды в дробную часть
        return timespec.tv_sec + timespec.tv_nsec * 1e-9

# Если платформа не поддерживается
else:
    raise NotImplementedError("Unsupported platform")

# Если скрипт запускается напрямую
if __name__ == "__main__":
    print(monotonic())  # Вызываем функцию monotonic и выводим результат