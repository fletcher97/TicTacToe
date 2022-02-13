# TicTacToe

This is the classic TicTacToe game but with a twist. The game consiste of 9
small TicTacToe that form a big one.

```
       ||       ||
  | |  ||  | |  ||  | |
 -+-+- || -+-+- || -+-+-
  | |  ||  | |  ||  | |
 -+-+- || -+-+- || -+-+-
  | |  ||  | |  ||  | |
       ||       ||
-------++-------++-------
-------++-------++-------
       ||       ||
  | |  ||  | |  ||  | |
 -+-+- || -+-+- || -+-+-
  | |  ||  | |  ||  | |
 -+-+- || -+-+- || -+-+-
  | |  ||  | |  ||  | |
       ||       ||
-------++-------++-------
-------++-------++-------
       ||       ||
  | |  ||  | |  ||  | |
 -+-+- || -+-+- || -+-+-
  | |  ||  | |  ||  | |
 -+-+- || -+-+- || -+-+-
  | |  ||  | |  ||  | |
       ||       ||
```

# Objective

The objective is to win the "big" board. To place your symbol on one of the
cells a player must win the "small" game of that cell. Once completed the small
board will be replaced by the corresponding symbol or in case of a draw an
equals sign will be desplayed.
```
++-------++-------++
++-------++-------++
||       ||       ||
|| \   / ||  ___  ||
||  \ /  || /   \ ||
||   X   || |   | ||
||  / \  || |   | ||
|| /   \ || \___/ ||
||       ||       ||
++-------++-------++
++-------++-------++
```

The game ends when one player manages to win the big board.
```
       ||       ||
  ___  || \   / || O|X|O
 /   \ ||  \ /  || -+-+-
 |   | ||   X   ||  |X|X
 |   | ||  / \  || -+-+-
 \___/ || /   \ || O| |X
       ||       ||
-------++-------++-------
-------++-------++-------
       ||       ||
  ___  || \   / || X| |X
 /   \ ||  \ /  || -+-+-
 |   | ||   X   || X|O|X
 |   | ||  / \  || -+-+-
 \___/ || /   \ || O| |
       ||       ||
-------++-------++-------
-------++-------++-------
       ||       ||
 X| |  || \   / || \   /
 -+-+- ||  \ /  ||  \ /
  |X|O ||   X   ||   X
 -+-+- ||  / \  ||  / \
  | |O || /   \ || /   \
       ||       ||
```

# Rules

Both the small and big board's index are represented as so:

```
1|2|3
-+-+-
4|5|6
-+-+-
7|8|9
```

The first player will be assigned 'O'. They choose the board they choose to
start from.

The players will place their symbol one after the other on the small boards. The
place on the small board where a player places their symbol represents the place
on the big board where the opponent will have to play. If a player places their
symbol on the cell 1 then the next player will have to play on the 1st board.
If a player places their symbol on the cell 5 the the next player will have to
play on the center board.

Example: If player X plays on a cell 4, player O will have to play anywhere on
the 4th board

```
       ||       ||
  | |  ||  | |  ||  | |
 -+-+- || -+-+- || -+-+-
  | |  || X| |  ||  | |
 -+-+- || -+-+- || -+-+-
  | |  ||  | |  ||  | |
       ||       ||
-------++-------++-------
-------++-------++-------
       ||       ||
  | |  ||  | |  ||  | |
 -+-+- || -+-+- || -+-+-
  | |  ||  | |  ||  | |
 -+-+- || -+-+- || -+-+-
  | |  ||  | |  ||  | |
       ||       ||
-------++-------++-------
-------++-------++-------
       ||       ||
  | |  ||  | |  ||  | |
 -+-+- || -+-+- || -+-+-
  | |  ||  | |  ||  | |
 -+-+- || -+-+- || -+-+-
  | |  ||  | |  ||  | |
       ||       ||

    ||
    ||
  \ || /
   \||/
    \/

       ||       ||
  | |  ||  | |  ||  | |
 -+-+- || -+-+- || -+-+-
  | |  || X| |  ||  | |
 -+-+- || -+-+- || -+-+-
  | |  ||  | |  ||  | |
       ||       ||
-------++-------++-------
-------++-------++-------
       ||       ||
 O|O|O ||  | |  ||  | |
 -+-+- || -+-+- || -+-+-
 O|O|O ||  | |  ||  | |
 -+-+- || -+-+- || -+-+-
 O|O|O ||  | |  ||  | |
       ||       ||
-------++-------++-------
-------++-------++-------
       ||       ||
  | |  ||  | |  ||  | |
 -+-+- || -+-+- || -+-+-
  | |  ||  | |  ||  | |
 -+-+- || -+-+- || -+-+-
  | |  ||  | |  ||  | |
       ||       ||
```

If a player's move obliges the opponent to play on a complete board, he needs to
choose a playable board for the opponent.

```
       ||       ||
  | |  ||  | |  ||  | |
 -+-+- || -+-+- || -+-+-
  | |  || X| |  ||  | |
 -+-+- || -+-+- || -+-+-
  | |  ||  | |  ||  | |
       ||       ||
-------++-------++-------
-------++-------++-------
       ||       ||
  ___  ||  | |  ||  | |
 /   \ || -+-+- || -+-+-
 |   | ||  | |  ||  | |
 |   | || -+-+- || -+-+-
 \___/ ||  | |  ||  | |
       ||       ||
-------++-------++-------
-------++-------++-------
       ||       ||
  | |  ||  | |  ||  | |
 -+-+- || -+-+- || -+-+-
  | |  ||  | |  ||  | |
 -+-+- || -+-+- || -+-+-
  | |  ||  | |  ||  | |
       ||       ||

    ||
    ||
  \ || /
   \||/
    \/

Player 'X', enter an index for your opponnent (1-9):
```
