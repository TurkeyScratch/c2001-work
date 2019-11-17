"""
:author:     James Jefferson Luu
:id:         30632749
:assignment: FIT1045 Assignment 1, Task 2 (Semester 1 2019)
:purpose:    Runs a one or two player game of Reversi.
:created:    2019-11-13 (remade within 4 hours)
:updated:    2019-11-17 (documentation)

This assignment task has since been replaced as of 2019-11-17.
"""
from copy import deepcopy


def new_board():
    # returns a zeroed 8 * 8 board representing a Reversi board
    board = [[0] * 8 for _ in range(8)]
    board[3][4] = board[4][3] = 1
    board[3][3] = board[4][4] = 2
    return board


def print_board(board):
    """
    This function takes a nested list of numbers representing a Reversi
    board and prints a human-readable form of the board with grid coordinates.
    
    :param board:   nested list of integers that represent a Reversi board
    :returns:       None, see description
    :pre-condition: board must be a nested list of numbers (should be 8 * 8)
    :raises:        TypeError/IndexError, if pre-condition is not true
    """
    alpha_row = ' | '.join([chr(97+i) for i in range(8)])
    between_rows = "\n---|---|---|---|---|---|---|---|---\n"
    for i, row in enumerate(board, start=1):
        row_str = ' | '.join(map(str, row))
        row_str = row_str.replace("0", " ").replace("1", "B").replace("2", "W")
        print(" {} | {}".format(i, row_str), end=between_rows)
    print("   | {}".format(alpha_row))
    

def score(board):
    """
    This function takes a nested list of numbers representing a Reversi
    board and returns the score of player 1 and 2 out of that board.
    
    :param board:   nested list of integers that represent a Reversi board
    :returns:       a tuple (s1, s2) representing the points of player 1 and 2
    :pre-condition: board must be a nested list of numbers (should be 8 * 8)
    :raises:        TypeError, if pre-condition is not true
    """    
    s1, s2 = 0, 0
    for row in board:
        s1 += row.count(1)
        s2 += row.count(2)
    return s1, s2


def enclosing(board, player, pos, direct):
    # base case
    if board[pos[0]][pos[1]] > 0:
        return False
    next_pos = add_pos(pos, direct)
    first_pass = False
    # loop goes through until it reaches the end in respect to pos and direct
    while pos_valid_range(next_pos):
        at_pos = access_pos(board, next_pos)
        if at_pos == player:
            return first_pass
        elif at_pos == 0:
            break
        else:
            next_pos = add_pos(next_pos, direct)
            first_pass = True
    return False
    
    
def add_pos(pos, direct):
    return pos[0]+direct[0], pos[1]+direct[1]


def access_pos(board, pos):
    return board[pos[0]][pos[1]]


def mutate_pos(board, player, pos):
    board[pos[0]][pos[1]] = player


def pos_valid_range(pos):
    return (0 <= pos[0] <= 7 and 0 <= pos[1] <= 7)


def valid_moves(board, player, get_directions=False):
    positions = board_positions(board)
    directions = board_directions()
    result = set([pos for pos in positions for direct in directions
                  if enclosing(board, player, pos, direct) is True])
    if get_directions:
        return sorted(result), directions
    else:
        return sorted(result)
    

def board_positions(board):
    n = len(board)
    return [(r, c) for r in range(n) for c in range(n) if board[r][c] == 0]


def board_directions():
    section = range(-1, 2)
    return [(r, c) for r in section for c in section if (r, c) != (0, 0)]
    
    
def next_state(board, player, pos):
    next_board = deepcopy(board)
    valid_moves_lst, directions = valid_moves(board, player, True)
    if pos not in valid_moves_lst:
        return board, player
        
    mutate_pos(next_board, player, pos)
    for direct in directions:
        if enclosing(board, player, pos, direct):
            fill_board(next_board, player, pos, direct)
            
    next_player = 2 if player == 1 else 1
    if board == next_board:
        next_player = player
    elif not valid_moves(next_board, next_player):
        next_player = 0
        
    return next_board, next_player
                
                
def fill_board(board, player, pos, direct):
    next_pos = add_pos(pos, direct)
    at_pos = access_pos(board, next_pos)
    while at_pos != player:
        mutate_pos(board, player, next_pos)
        next_pos = add_pos(next_pos, direct)
        at_pos = access_pos(board, next_pos)


def position(string):
    if len(string) > 2 or not (type(string) == str and string[1].isdigit()):
        return None
    r = int(string[1]) - 1
    c = ord(string[0]) - 97
    return (r, c) if pos_valid_range((r, c)) else None


def run_reversi(computer: bool):
    board = new_board()
    player = 1
    while player > 0:
        if computer is True and player == 2:
            board, player = computer_turn(board, player)
        else:
            board, player = player_turn(board, player)
    return results(board)
    

def run_two_players():
    return run_reversi(False)
    
    
def run_single_player():
    return run_reversi(True)


def player_turn(board, player):
    print_title()
    print_board(board)
    print("Player 1 (B): {}, Player 2 (W): {}".format(*score(board)))
    act = input("Player {}, please place a marker (e.g. a1, h8) or [q]uit: ".format(player))
    if act.lower() == 'q':
        player = 0
    else:
        pos = position(act)
        if pos is not None:
            board, player = next_state(board, player, pos)
    return board, player
    

def computer_turn(board, player):        
    r, c = cpu_pos = get_best_pos(board, player)
    cpu_pos_string = "{}{}".format(chr(c+97), r+1)
    board, player = next_state(board, player, cpu_pos)
    print_title()
    print_board(board)
    print("Player 1 (B): {}, Player 2 (W): {}".format(*score(board)))
    print("Player 2 has placed their marker on {}.".format(cpu_pos_string))
    input("Press ENTER to continue...")
    return board, player
   
    
def get_best_pos(board, player):
    valid_moves_lst = valid_moves(board, player)
    simulated_score_lst = []
    for pos in valid_moves_lst:
        simmed_board, next_player = next_state(deepcopy(board), player, pos)
        simmed_score = score(simmed_board)
        score_diff = simmed_score[player-1] - simmed_score[next_player-1] 
        simulated_score_lst.append((score_diff, pos))
    return max(simulated_score_lst)[1]


def results(board):
    print_title()
    print_board(board)
    final_score = score(board)
    print("Player 1 (B): {}, Player 2 (W): {}".format(*final_score))
    if final_score[0] == final_score[1]:
        print("Tie!")
    else:
        winner = final_score.index(max(final_score)) + 1
        print("Player {} wins!".format(winner))
    return None
    

def print_title():
    print("\n:{}:".format("~" * 33))
    print("|         Mario's Reversi         |")
    print(":{}:".format("~" * 33))


if __name__=="__main__":
    print_board(new_board())
    assert score(new_board()) == (2, 2)
    assert enclosing(new_board(), 1, (4, 5), (0, -1)) is True
    assert enclosing(new_board(), 1, (4, 5), (1, 1)) is False
    assert valid_moves(new_board(), 1) == [(2, 3), (3, 2), (4, 5), (5, 4)]
    a = next_state(new_board(), 1, (4, 5))
    print_board(a[0])
    assert a[1] == 2
    assert valid_moves(next_state(new_board(), 1, (4, 5))[0], 2) == [(3, 5), (5, 3), (5, 5)]
    assert position("e3") == (2, 4)
    assert position("l1") is None
    assert position("a0") is None
    assert position("Genghis Khan") is None
    
    print("No errors. All assert test cases were successful.\n")
    
    print("Enter 1 or 2 to play One Player or Two Player Reversi...")
    players = input()
    if players.isdigit() and int(players) == 2:
        run_two_players()
    else:
        run_single_player()
    