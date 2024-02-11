from re import *

def readFile():
    file1 = open("knowledge_base.txt", "r")
    file2 = open("hypothesis.txt", "r")

    knowledge_base = []
    fact = []

    temp1 = file1.readlines()
    for line in temp1:
        knowledge_base.append(line.strip())
    temp2 = file2.readlines()
    for line in temp2:
        fact.append(line.strip())

    file1.close()
    file2.close()

    return knowledge_base, fact

def createRules(knowledge_base, fact):
    set = []
    m = len(knowledge_base)

    for i in range(m):
        clause = []
        temp = split(' \+ | ', knowledge_base[i])
        hypothesis = []
        conclusion = []
        pos = 0
        for element in temp:
            if element == '->':
                pos = temp.index(element)
                break
        for j in range(pos):
            hypothesis.append(temp[j])
        clause.append(hypothesis)

        for j in range(pos + 1, len(temp)):
            conclusion.append(temp[j])
        clause.append(conclusion)

        set.append(clause)

    hypothesis = fact[0].split(' -> ')

    return set, hypothesis

def isSubstring(A, B):
    for element in B:
        pos = 0
        while element[pos].isdigit() == True:
            pos += 1
        if A == element[pos:]:
            return 1
    return 0

def printEquation(equation):
    print(equation[0][0], end='')
    for i in range(1, len(equation[0])):
        print(' +', equation[0][i], end='')
    print(' -> ', end='')
    print(equation[1][0], end='')
    for i in range(1, len(equation[1])):
        print(' +', equation[1][i], end='')
    print()

def forwardChaining(knowledge_base, fact):
    for i in range(1, len(fact)):
        print('({}). '.format(i), end='')
        for j in range(len(knowledge_base)):
            if isSubstring(fact[i - 1], knowledge_base[j][0]) == 1 and isSubstring(fact[i], knowledge_base[j][1]) == 1:
                printEquation(knowledge_base[j])
                break
        else:
            print('Khong ton tai phuong trinh')

if __name__ == '__main__':
    knowledge_base, fact = readFile()
    knowledge_base, fact = createRules(knowledge_base, fact)
    print(fact)
    forwardChaining(knowledge_base, fact)