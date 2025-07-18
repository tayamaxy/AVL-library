# AVL Tree Library & Demo – Coursework Project

Second-year university project – modern C++ implementation
This repository provides a small, self-contained C++17 library that implements an AVL (Adelson-Velskii–Landis) self-balancing binary-search tree together with a console demo.
An AVL tree stores ordered keys and guarantees O(log n) inserts, deletes and look-ups by ensuring that, for every node, the heights of the left and right sub-trees differ by at most 1.
Although the code was originally written as a second-year assignment, it follows solid software-engineering practices and can serve as a learning reference or a lightweight drop-in for small projects.

> 📝 The included documentation (`dokumentation.pdf`, `user_manual.pdf`) is written in Czech, as it was created for a university submission.

## 🧠 Features

- Complete public API – insert, del, find, findMin, findMax, next (in-order iterator) and show for ASCII visualisation.
- Automatic rebalancing – single & double rotations (left_rotation, right_rotation, b_left_rotation, b_right_rotation) performed transparently after any structural change. 
- Header-only linked list helper for pretty printing (see Linked_list.h). 
- Zero external dependencies: standard C++ headers only.

## 🛠️ Technologies

- Language: C++17
- Style: Object-Oriented Programming (OOP)
- Main class: AVL_node
- Helper class: Linked_list (for tree visualisation)

## ▶️ How to Run

Compile and run with any modern C++ compiler. For example:
```bash
g++ -std=c++17 -Wall -Wextra -pedantic AVL.cpp -o avl_tree
./avl_tree
```

## 📚 Documentation

For full Czech-language documentation, open user_manual.pdf (end-user focused) and dokumentation.pdf (developer focused). 


## 📄 License

This project is licensed under the MIT License – see the LICENSE file for details.

Happy coding & balanced trees!

## 👤 Author

Name: Taisiia Starchenko
[LinkedIn](https://www.linkedin.com/in/tayamaxy)