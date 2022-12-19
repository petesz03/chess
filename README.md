Chess engine:

Part 1: Implement board, legal moving, checkmating, and player vs player functionality

Part 2: Implement bot with strategies.

To update to git:
1. git add [the files you have changed and want to upload]
2. git commit -m [message]
3. git push

If there are conflicts:
1. git stash
2. git pull
3. git add [the files you have changed and want to upload]
4. git commit -m [message]
5. git push


To do:
1. Implement the move function for Queen... (Try to not have repetitive code, maybe move some code to methods...)
2. Check over the logic in board, make sure there is no problem
3. Check in to see if hard code is the way to go in order to not have any memory issue...
4. Implement main
5. Compile the board and try to take pieces, etc...
6. Implement endgame conditions and checkmating!
7. Compile the board and make sure all the game logic flow smoothly.



Problems:
1. With less memory, there will be more hard code leading to more time.
2. However, if we increase memory, the memory needed will increase exponentially which might lead to problem...
