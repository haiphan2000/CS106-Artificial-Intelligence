from collections import deque


class State:
    def __init__(self, trieu_phu, ke_cuop, vt_thuyen):
        self.trieu_phu = trieu_phu
        self.ke_cuop = ke_cuop
        self.vt_thuyen = vt_thuyen

    def getSuccessors(self):
        if self.vt_thuyen == 1:
            check = -1
            direction = "tu bo ta ngan sang bo huu ngan."
        else:
            check = 1
            direction = "tu bo huu ngan sang bo ta ngan."
        for m in range(3):
            for c in range(3):
                newState = State(self.trieu_phu + check * m, self.ke_cuop + check * c, self.vt_thuyen + check * 1);
                if m + c in [1, 2] and newState.isValidState():
                    action = "Cho {} trieu phu and {} ke cuop {} {}".format(m, c, direction, newState)
                    yield action, newState

    def isValidState(self):
        if not (0 <= self.trieu_phu <= 3) or not (0 <= self.ke_cuop <= 3) or (self.vt_thuyen not in [0, 1]):
            return False
        if self.ke_cuop > self.trieu_phu > 0:
            return False
        if self.ke_cuop < self.trieu_phu < 3:
            return False
        return True

    def isGoalState(self):
        return self.ke_cuop == 0 and self.trieu_phu == 0 and self.vt_thuyen == 0

    def __repr__(self):
        return "<Trang thai hien tai: ({}, {}, {})>".format(self.trieu_phu, self.ke_cuop, self.vt_thuyen)


class Node:
    def __init__(self, parent_node, state, action):
        self.parent_node = parent_node
        self.state = state
        self.action = action

    def expand(self):
        for (action, succ_state) in self.state.getSuccessors():
            succ_node = Node(parent_node=self, state=succ_state, action=action)
            yield succ_node

    def extractSolution(self):
        solution = []
        node = self
        while node.parent_node is not None:
            solution.append(node.action)
            node = node.parent_node
        solution.reverse()
        return solution

def breadthFirstSearch(initial_state):
    initial_node = Node(parent_node = None, state = initial_state, action=None)
    temp = deque([initial_node])
    while True:
        if not temp:
            return None
        node = temp.popleft()
        if node.state.isGoalState():
            solution = node.extractSolution()
            return solution
        temp.extend(node.expand())


if __name__ == "__main__":
    initial_state = State(3, 3, 1)
    solution = breadthFirstSearch(initial_state)
    if solution is None:
        print("Bai toan khong ton tai loi giai.")
    else:
        print("Loi giai cua bai toan la: (gom {} buoc)".format(len(solution)))
        for i in range(len(solution)):
            print("Buoc {}.".format(i + 1), solution[i])
