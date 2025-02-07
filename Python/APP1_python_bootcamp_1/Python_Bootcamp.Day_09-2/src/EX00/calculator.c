/*


https://github.com/dm-fedorov/python-modules/blob/master/c-api.md




*/


#define PY_SSIZE_T_CLEAN
#include <Python.h>

// PyObject - стандартный тип для любого объекта Python

static PyObject *method_add(PyObject *self, PyObject *args) {
    PyObject *arg1, *arg2;

    // парсинг аргументов в arg1 и arg2
    // проверка на наличие двух аргументов
    if (!PyArg_ParseTuple(args, "OO", &arg1, &arg2)) {
        PyErr_SetString(PyExc_TypeError, "Expected two arguments");
        return NULL;
    }

    // проверка типов
    if (PyLong_Check(arg1) && PyLong_Check(arg2)) {
        // оба аргумента являются целыми
        long a = PyLong_AsLong(arg1);
        long b = PyLong_AsLong(arg2);
        return PyLong_FromLong(a + b);
    } else if ((PyLong_Check(arg1) || PyFloat_Check(arg1)) && 
               (PyLong_Check(arg2) || PyFloat_Check(arg2))) {
        // хотя бы один из аргументов float
        double a = PyFloat_AsDouble(arg1);
        double b = PyFloat_AsDouble(arg2);
        return PyFloat_FromDouble(a + b);
    } else {
        // неверный тип аргумента (строка и тп)
        PyErr_SetString(PyExc_TypeError, "Arguments must be int or float");
        return NULL;
    }
}

static PyObject *method_sub(PyObject *self, PyObject *args) {
    PyObject *arg1, *arg2;

    // парсинг аргументов в arg1 и arg2
    // проверка на наличие двух аргументов
    if (!PyArg_ParseTuple(args, "OO", &arg1, &arg2)) {
        PyErr_SetString(PyExc_TypeError, "Expected two arguments");
        return NULL;
    }

    // проверка типов
    if (PyLong_Check(arg1) && PyLong_Check(arg2)) {
        // оба аргумента являются целыми
        long a = PyLong_AsLong(arg1);
        long b = PyLong_AsLong(arg2);
        return PyLong_FromLong(a - b);
    } else if ((PyLong_Check(arg1) || PyFloat_Check(arg1)) && 
               (PyLong_Check(arg2) || PyFloat_Check(arg2))) {
        // хотя бы один из аргументов float
        double a = PyFloat_AsDouble(arg1);
        double b = PyFloat_AsDouble(arg2);
        return PyFloat_FromDouble(a - b);
    } else {
        // неверный тип аргумента (строка и тп)
        PyErr_SetString(PyExc_TypeError, "Arguments must be int or float");
        return NULL;
    }
}

static PyObject *method_div(PyObject *self, PyObject *args) {
    PyObject *arg1, *arg2;

    // парсинг аргументов в arg1 и arg2
    // проверка на наличие двух аргументов
    if (!PyArg_ParseTuple(args, "OO", &arg1, &arg2)) {
        PyErr_SetString(PyExc_TypeError, "Expected two arguments");
        return NULL;
    }

    // проверка типов
    if (PyLong_Check(arg1) && PyLong_Check(arg2)) {
        // оба аргумента являются целыми
        long a = PyLong_AsLong(arg1);
        long b = PyLong_AsLong(arg2);
        if (b == 0) {
            PyErr_SetString(PyExc_ZeroDivisionError, "Cannot divide by zero");
            return NULL;
        }
        return PyLong_FromLong(a / b);
    } else if ((PyLong_Check(arg1) || PyFloat_Check(arg1)) && 
               (PyLong_Check(arg2) || PyFloat_Check(arg2))) {
        // хотя бы один из аргументов float
        double a = PyFloat_AsDouble(arg1);
        double b = PyFloat_AsDouble(arg2);
        if (b == 0.0) {
            PyErr_SetString(PyExc_ZeroDivisionError, "Cannot divide by zero");
            return NULL;
        }
        return PyFloat_FromDouble(a / b);
    } else {
        // неверный тип аргумента (строка и тп)
        PyErr_SetString(PyExc_TypeError, "Arguments must be int or float");
        return NULL;
    }
}

static PyObject *method_mul(PyObject *self, PyObject *args) {
    PyObject *arg1, *arg2;

    // парсинг аргументов в arg1 и arg2
    // проверка на наличие двух аргументов
    if (!PyArg_ParseTuple(args, "OO", &arg1, &arg2)) {
        PyErr_SetString(PyExc_TypeError, "Expected two arguments");
        return NULL;
    }

    // проверка типов
    if (PyLong_Check(arg1) && PyLong_Check(arg2)) {
        // оба аргумента являются целыми
        long a = PyLong_AsLong(arg1);
        long b = PyLong_AsLong(arg2);
        return PyLong_FromLong(a * b);
    } else if ((PyLong_Check(arg1) || PyFloat_Check(arg1)) && 
               (PyLong_Check(arg2) || PyFloat_Check(arg2))) {
        // хотя бы один из аргументов float
        double a = PyFloat_AsDouble(arg1);
        double b = PyFloat_AsDouble(arg2);
        return PyFloat_FromDouble(a * b);
    } else {
        // неверный тип аргумента (строка и тп)
        PyErr_SetString(PyExc_TypeError, "Arguments must be int or float");
        return NULL;
    }
}



// определения функций модуля, чтобы сообщить интерпретатору Питона
// о том, какие функции он должен импортировать
static PyMethodDef CalculatorMethods[] = {
    {"add", method_add, METH_VARARGS, "Python interface for add C library function"}, // для add метода
    {"sub", method_sub, METH_VARARGS, "Python interface for sub C library function"}, // для sub метода
    {"mul", method_mul, METH_VARARGS, "Python interface for mul C library function"}, // для mul метода
    {"div", method_div, METH_VARARGS, "Python interface for div C library function"}, // для div метода 
    {NULL, NULL, 0, NULL} // просто разделитель
};
/*
"add" - это имя, которое напишет пользователь для вызова функции из кода на Python.
method_add - это имя C функции для вызова.
METH_VARARGS - это флаг, который сообщает интерпретатору, что функция будет 
            принимать два аргумента типа PyObject *:
            self - это объект модуля.
            args - это кортеж, содержащий фактические аргументы вашей функции. 
Последняя строка представляет собой значение, представляющее метод docstring.

*/

// определение самого модуля
static struct PyModuleDef calculatormodule = {
    PyModuleDef_HEAD_INIT,
    "calculator",
    "Python interface for calculator C library function",
    -1,
    CalculatorMethods
};
/*

"calculator" - это название вашего модуля расширения Python C.
Строка - это значение, представляющее строку документации вашего модуля
-1 - объем памяти, необходимый для хранения состояния вашей программы. 
    Это полезно, когда ваш модуль используется в нескольких суб-интерпретаторах, 
    и может иметь следующие значения:
FputsMethods - это ссылка на таблицу методов. Это массив структур PyMethodDef, 
    которые вы определили ранее.
*/


/*
Теперь, когда вы определили свой модуль расширения Python и структуры методов, 
пришло время использовать их. Когда программа Python импортирует ваш модуль 
в первый раз, она вызовет PyInit_fputs():
*/

PyMODINIT_FUNC PyInit_calculator(void){
    return PyModule_Create(&calculatormodule);
}