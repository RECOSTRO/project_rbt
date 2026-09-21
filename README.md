# Red-Black Tree (RBT) Implementation in C++ 🌳

[![Language](https://img.shields.io/badge/language-C++-blue.svg)](https://isocpp.org/)

*[Read this in Russian / Читать на русском](#красно-черное-дерево-red-black-tree-на-c)*

## Description
This project features a custom, template-based implementation of a **Red-Black Tree (RBT)** in C++. A Red-Black Tree is a self-balancing binary search tree that ensures $O(\log n)$ time complexity for search, insertion, and deletion operations, making it highly efficient for dynamic data storage.

## Features
- **Template-based:** Can store any custom data type (`mytypel`) alongside an integer key.
- **Self-balancing:** Automatically handles left/right rotations and recoloring during insertions and deletions to maintain RBT properties.
- **Memory Management:** Includes a dedicated function for safe, recursive memory deallocation to prevent memory leaks.
- **Overloaded Initialization:** Supports initializing the tree node-by-node or in bulk from an array of data.

## API / Functions

The following core operations are provided:

* `make_tree`: Initializes the root of the tree (supports single element or array initialization).
* `insert`: Inserts a new node by key and rebalances the tree.
* `delete_node`: Removes a node by its key and rebalances the tree.
* `search`: Finds and returns a pointer to a node by its key.
* `search_max` / `search_min`: Finds the node with the maximum or minimum key (successor/predecessor).
* `freel`: Recursively deletes all nodes and frees up allocated memory.

## Usage Structure
The implementation uses a template model where the source code (`struct_rbt.cpp`) is included directly at the end of the header (`struct_rbt.hpp`). To use it, simply include the header in your project:
```cpp
#include "struct_rbt.hpp"
```

---
---

# Красно-черное дерево (Red-Black Tree) на C++ 🌳

## Описание
Данный проект представляет собой шаблонную реализацию структуры данных **Красно-черное дерево (КЧД)** на языке C++. Это самобалансирующееся двоичное дерево поиска, которое гарантирует логарифмическую сложность $O(\log n)$ для операций поиска, вставки и удаления, что делает его крайне эффективным для работы с динамическими наборами данных.

## Особенности
- **Шаблонизация (Templates):** Дерево может хранить любой пользовательский тип данных (`mytypel`), привязанный к целочисленному ключу.
- **Самобалансировка:** Автоматически выполняет левые/правые повороты и перекрашивание узлов при вставке и удалении для сохранения свойств КЧД.
- **Управление памятью:** Включает рекурсивную функцию для безопасного освобождения выделенной памяти и предотвращения утечек.
- **Удобная инициализация:** Поддерживает создание дерева как из одного элемента, так и массовую загрузку из массива данных (перегрузка функции).

## Доступные функции (API)

В проекте реализованы следующие основные функции:

* `make_tree`: Инициализация корня дерева (поддерживает создание из одного элемента или массива).
* `insert`: Вставка нового узла по ключу с последующей балансировкой.
* `delete_node`: Удаление узла по заданному ключу с восстановлением баланса дерева.
* `search`: Поиск и возврат указателя на узел по его ключу.
* `search_max` / `search_min`: Поиск узлов с максимальным и минимальным ключами (поиск предшественника/последователя).
* `freel`: Рекурсивная очистка дерева и освобождение памяти.

## Структура и использование
Реализация использует подход, при котором файл с кодом (`struct_rbt.cpp`) подключается в конце заголовочного файла (`struct_rbt.hpp`), что необходимо для корректной работы шаблонов (templates) при компиляции. 

Для использования просто подключите заголовочный файл в ваш проект:
```cpp
#include "struct_rbt.hpp"
```