#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

struct ClauseNode {
    int literal;
    struct ClauseNode *next;
};

class Clause {
public:
    ClauseNode *head,*tail;
    Clause() {
        head = NULL;
        tail = NULL;
    }
    void addNode(int literal) {
        ClauseNode *tmp = new ClauseNode;
        tmp->literal = literal;
        tmp->next = NULL;

        if(head == NULL) {
            head = tmp;
            tail = tmp;
        } else {
            tail->next = tmp;
            tail = tail->next;
        }
    }
};

bool isSatisfied(bool* solution, int numClauses, Clause *clauses) {
    for(int i = 0; i < numClauses; i++) {
        // cout << "Checking clause " << i << endl;
        bool isClauseSatisfied = false;
        ClauseNode *node = clauses[i].head;
        while(true) {
            if(node->literal > 0) {
                if(solution[node->literal - 1]) {
                    isClauseSatisfied = true;
                    break;
                }
            } else {
                if(!solution[-node->literal - 1]) {
                    isClauseSatisfied = true;
                    break;
                }
            }
            // cout << "Checking literal " << node->literal << endl;
            if(node == clauses[i].tail) break;
            node = node->next;
        }
        if(!isClauseSatisfied) return false;
    }
    return true;
}

void printSolution(int numVariables, bool* solution) {
    for(int i = 0; i < numVariables; i++) {
        cout << solution[i];
    }
    cout << endl;
}

// Recursive solve
int _solve(bool* solution, int numVariables, int numClauses, Clause *clauses, int n) {
    if(n >= numVariables) {
        // printSolution(numVariables, solution);
        if(isSatisfied(solution, numClauses, clauses)) return 1;
        return 0;
    }

    solution[n] = false;
    bool s1 = _solve(solution, numVariables, numClauses, clauses, n + 1);

    solution[n] = true;
    bool s2 = _solve(solution, numVariables, numClauses, clauses, n + 1);


    return s1 || s2;
}

int solve(int numVariables, int numClauses, Clause *clauses) {
    
    bool solution[numVariables] = {false};
    
    bool isSAT = _solve(solution, numVariables, numClauses, clauses, 0);
    
    return isSAT;
}

int main(int argc, char** argv) {

    if (argc != 2) {
        cout << "Solver requires a single file path argument" << endl;
        return -1;
    }

    string filename(argv[1]);
    ifstream file;

    file.open(filename);

    if(!file) {
        std::cout << "Unable to open file: " << filename << std::endl;
        return -1;
    }

    int numVariables = 0;
    int numClauses = 0;

    Clause* clauses = NULL;
    int clauseIndex = -1;
    
    

    for(string line; getline(file, line) && clauseIndex < numClauses;) {
        // Skip comments
        if(line.rfind("c", 0) == 0) continue;
        
        // Define the initialization
        smatch match;
        regex_match(line, match, regex("p +cnf +([0-9]+) +([0-9]+)"));
        if(match.size() == 3) {
            numVariables = atoi(match.str(1).c_str());
            numClauses = atoi(match.str(2).c_str());
            clauses = new Clause[numClauses];
            continue;
        }

        // Match a clause line
        clauseIndex++;
        string literalStr = "";
        for(int i = 0; line[i] != '\0'; i++) {
            if(line[i] == '-' || isdigit(line[i])) {
                literalStr += line[i];
            } else {
                if(literalStr.length() > 0) {
                    if(literalStr == "0") break;
                    // cout << "Add " << literalStr << " to " << clauseIndex << endl;
                    clauses[clauseIndex].addNode(atoi(literalStr.c_str()));
                    literalStr = "";
                }
            }
        }
        if(literalStr.length() > 0 && literalStr != "0") {
            // cout << "Add final " << literalStr << " to " << clauseIndex << endl;
            clauses[clauseIndex].addNode(atoi(literalStr.c_str()));
            literalStr = "";
        }
    }
    file.close();
    
    if(!numVariables || !numClauses) {
        cout << "Number of variables or clauses is undefined." << endl;
        return -1;
    }

    bool isSAT = solve(numVariables, numClauses, clauses);

    if(isSAT) {
        cout << "SAT instance is satifiable." << endl;
    } else {
        cout << "SAT instance is unsatifiable." << endl;
    }

    

    return 0;
}
