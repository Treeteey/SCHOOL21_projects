## EX00

### ВАЖНО   
 `py setup.py install` - устарела команда, поэтому буду делать модуль по-другому

---

1) `py .\setup.py build_ext --inplace` - собрать расширение в текущей папке
2) `py`
    ```python
    import calculator

    print(calculator.add(14, 21))
    print(calculator.sub(14, 21))
    print(calculator.mul(14, 21))
    print(calculator.div(14, 7))
    ```
3) `python setup.py clean --all` - удалить библиотеку


## EX01

1) `py monotonic.py`



## EX02

1) `pip install cython`
2) `python setup.py build_ext --inplace`
3) `py test_mul_perf.py` - запустить тесты на сравнение скорости выполнения
4) `python setup.py clean --all` - удалить библиотеку