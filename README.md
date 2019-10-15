Lem_in
===

## What is Lem-in?

This project is about coding an ant farm manager. Your ant colony must move from on point to another. How do you do it in the shortest time possible? This project will get you acquainted with ```graph traversal algorithms```: your program will have to intelligently select paths and precise movements used by the ants.

---

## Our algorithm 

An ant farm is composed of rooms which can contain only one ant at a time (except room "start" and "end"), and tunnels linking thoses rooms. The goal is to move all ants from the room "start" to the room "end" in the minimum of moves possible.

To do so we developped an algorithm which searchs for all compatible paths (meaning paths not crossing each others). Using a loop of Breadth-First Search which put rooms from the new path as "invisible" for the next loop, and a system of backtracking when no more paths can be found, to make sure we will discover every combination of paths.

We will then select the most optimized set of paths depending on the number of ants send by the user:

![Screen Shot 2019-10-15 at 3 44 25 PM](https://user-images.githubusercontent.com/45974214/66837063-affdf380-ef62-11e9-9a5e-cf2ca34727ff.png)

We then calculate how many ants to send to each path in the set and print the result, such as:

![Screen Shot 2019-10-15 at 4 08 33 PM](https://user-images.githubusercontent.com/45974214/66839042-12a4be80-ef66-11e9-8cf4-d50adf8deeb9.png)

---

## The visualisator

As the result of Lem-in can be pretty confusing, a visualisator in python was made in plus.
It recquires networkX and matplotlib, install them with:
```shell
pip install networkx
pip install matplotlib
```
Launch visualisator:
```shell
make && ./lem-in < tests/ex3.map | python visual/visualisator.py
```

![Screen Shot 2019-10-15 at 3 58 03 PM](https://user-images.githubusercontent.com/45974214/66838220-98c00580-ef64-11e9-85c6-daee8e57fc37.png)

Authors: Kinstelle & lgaultie
