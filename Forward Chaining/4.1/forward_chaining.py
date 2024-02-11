def readFile():
    file1 = open("rule.txt", "r")
    file2 = open("hypothesis.txt", "r")
    file3 = open("conclusion.txt", "r")

    conclusion = []

    rule = file1.readlines()
    fact = file2.readlines()
    temp = file3.readlines()
    for line in temp:
        conclusion.append(int(line.strip()))

    file1.close()
    file2.close()
    file3.close()

    return rule, fact, conclusion


def createRules(rule, fact):
    set = []
    m = len(rule)

    for i in range(m):
        clause = []
        temp = rule[i].split()
        hypothesis = []
        for j in range(len(temp) - 1):
            hypothesis.append(int(temp[j]))
        clause.append(hypothesis)

        conclusion = [int(temp[len(temp) - 1])]
        clause.append(conclusion)

        set.append(clause)

    hypothesis = []
    n = len(fact)
    for i in range(n):
        temp = fact[i].split()
        hypothesis.append(int(temp[0]))

    return set, hypothesis


def isSubset(A, B):
    if len(A) <= len(B):
        for element in A:
            if not (element in B):
                return 0
        return 1
    return 0

"""
def forwardChaining(rule, hypothesis, conclusion):
    known = hypothesis
    guide = []
    answer = [known[:]]
    flag = 1
    while (flag == 1):
        flag = 0
        for i in range(len(rule)):
            if not (rule[i][1][0] in known) and isSubset(rule[i][0], known) == 1:
                flag = 1
                known.append(rule[i][1][0])
                guide.append(i)
                answer.append(known[:])
            if isSubset(conclusion, known) == 1:
                break
    return guide, answer


if __name__ == '__main__':
    clause, fact, conclusion = readFile()
    print(conclusion)
    rule, hypothesis = createRules(clause, fact)
    guide, answer = forwardChaining(rule, hypothesis, conclusion)
    if isSubset(conclusion, answer[-1]) != 1:
        print('Khong tim duoc')
    else:
        for i in range(len(guide)):
            print('Ap dung luat thu {}, ta co:'.format(guide[i]))
            print('{} -> {}'.format(answer[i], answer[i + 1]))
    print('Xong')
"""

def forwardChaining(rule, hypothesis, conclusion):
    known = conclusion
    #guide = []
    #answer = [known[:]]
    pos = 0
    while pos < len(known):
        for i in range(len(rule)):
            if not (isSubset(rule[i][0], known)) and known[pos] == rule[i][1][0]:
                known.append(rule[i][0])
                #guide.append(i)
                #answer.append(known[:])mylist = list(dict.fromkeys(mylist))
                known = list(dict.fromkeys(known))
        if isSubset(hypothesis, known) == 1:
            break
        pos += 1
        print(known)
    return known#guide, answer


if __name__ == '__main__':
    clause, fact, conclusion = readFile()
    print(conclusion)
    rule, hypothesis = createRules(clause, fact)
    known = forwardChaining(rule, hypothesis, conclusion)
    print(known)