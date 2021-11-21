class Sudoku:
    def __init__(self, board = None):
        if(board == None): self.getInput()
        else: self.board = board
        self.initCheck()
        
    @staticmethod
    def getBox(r, c):
        return (r//3)*3 + c//3
    
    def getInput(self):
        self.board = []
        for i in range(9):
            self.board.append(list(map(int, input().split())))
        
    def initCheck(self):
        self.rCheck = [[False for _ in range(10)] for _ in range(9)]
        self.cCheck = [[False for _ in range(10)] for _ in range(9)]
        self.bCheck = [[False for _ in range(10)] for _ in range(9)]

        for r in range(9):
            for c in range(9):
                self.rCheck[r][self.board[r][c]] = True
                self.cCheck[c][self.board[r][c]] = True
                self.bCheck[Sudoku.getBox(r, c)][self.board[r][c]] = True

    def isValid(self, r, c, b):
        return not (self.rCheck[r][b] or self.cCheck[c][b] or self.bCheck[Sudoku.getBox(r, c)][b])
    
    def update(self, r, c, b, d):
        self.rCheck[r][b] = d
        self.cCheck[c][b] = d
        self.bCheck[Sudoku.getBox(r, c)][b] = d

        if d: self.board[r][c] = b
        else: self.board[r][c] = 0
    
    def solve(self, r=0, c=0):
        if r >= 9: return True
        if c >= 9: return self.solve(r+1, 0)

        if(self.board[r][c] != 0): return self.solve(r, c+1)

        for i in range(1, 10):
            if self.isValid(r, c, i):
                self.update(r, c, i, True)
                if self.solve(r, c+1):
                    return True
                self.update(r, c, i, False)
        
        return False

    def printBoard(self):
        for row in self.board:
            print(*row, sep = ' ')


if __name__ == "__main__":
    s = Sudoku()
    s.solve()
    s.printBoard()

