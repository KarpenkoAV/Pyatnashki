Pyatnashki (barley-brick)
==========
barley-brick, invented in 1878 Noah Chapman. Is a set of 15 identical square tiles with printed numbers, enclosed in square box in a carton blank one square box. The goal of the game - moving the knuckle on the box, to achieve ordering them by number, preferably made as small as possible displacements.
Tag represent a classic task for the simulation heuristic algorithms. Usually the task is solved through a number of movements and the search for Manhattan distance between each tile and its position in the assembled puzzle. For solutions used algorithms like A*algorithm.
Based on the mathematical description is that exactly half of all possible 20 922 789 888 000 (=16!) the initial positions of the tag cannot lead to a collected mind.
Now, having some free time I decided to write a C++ program that implements the addition of the tag (the location of items is randomly generated) in the automatic mode.
The algorithm is based on the movement of empty cells to that element which we must move, and is positioned on the side in which you want to shift the cage. Once we have established a cell next to the item we like, we do the exchange (swap) the contents of the cells. The exchange can be done only with the adjacent existing cells only horizontally and vertically. To move the blank cells using algorithm A*.
