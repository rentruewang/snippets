// The 2 SAT problem
// (A -> B) & (B -> A) & (C -> -B)
// has two possible assignments,
// [A, B, C] = [1, 1, 0] or [0, 1, 1]
// Now, given these conditions,
// design an algorithm to maximize the maximum true elements.
// NOTE:
// Here, for simplicity purposes, I'm going to assume there are
// no negations on the left hand side. Only negation on the right.

/**
 * Variable represents a token in the original 2-SAT problem.
 */
class Variable {
  /**
   * The name of the variable.
   */
  readonly token: string;

  /**
   * Whether there is negation on the variable.
   */
  readonly neg: boolean;

  constructor(name: string, neg: boolean) {
    this.token = name;
    this.neg = neg;
  }

  toString(this: this) {
    if (this.neg) {
      return `-${this.token}`;
    } else {
      return this.token;
    }
  }

  static fromString(repr: string): Variable {
    let neg = false;
    if (repr.startsWith("-")) {
      neg = true;
      repr = repr.substring(1);
    }

    return new Variable(repr, neg);
  }
}

/**
 * This shows a condition (a clause or term) in the original 2-SAT problem.
 */
class Condition {
  /**
   * The left hand side of a clause. A if the clause is (A -> -B).
   */
  readonly left: Variable;
  /**
   * The right hand side of a clause. -B if the clause is (A -> -B).
   */
  readonly right: Variable;

  constructor(left: Variable, right: Variable) {
    this.left = left;
    this.right = right;
  }

  toString(this: this): string {
    return `(${this.left.toString()} -> ${this.right.toString()})`;
  }
}

class TwoSat {
  clauses: Condition[];

  constructor(...clauses: Condition[]) {
    this.clauses = clauses;
  }
}

/**
 *
 * @param twosat The 2 SAT instance to solve.
 * @returns The number of possible correct assignments. 0 for impossible.
 */
function twoSatSolver(twosat: TwoSat): number {
  // Check if there are negations to the left.
  // This solver assumes that it never happens for simplicity.
  for (let { left, right: _ } of twosat.clauses) {
    console.assert(!left.neg);
  }

  // Create an adjacency list.
  let adjList = createAdjList(twosat);

  console.log(adjList);

  return 0;
}

function twoSatAdjSolver(
  adjList: Map<string, string[]>,
  forceOnes: Set<string>
): number {
  // Recursively solve 2 SAT problem.

  // TODO: Check if this solution is valid.

  let possibleCount = 0;
  // Since any order would do, use the given order.
  for (let { left, right } of twosat.clauses) {
    const adj = adjList.get(left.toString())!;
    const exists = adjList.delete(left.toString());
    console.assert(exists);

    // Try assigning to 0
    // Assigninging to 0 has no effect because the left hand side clauses are never negated.
    possibleCount += twoSatAdjSolver(adjList, new Set());

    // Try assigning to 1
    possibleCount += twoSatAdjSolver(adjList, adj);
  }

  return 0;
}

/**
 * Create the adjacency list from an edge list.
 *
 * @param twosat The edge list, which represents the conditions in the original 2-SAT.
 * @returns A map from variable name (defined by Variable.token to a list of variables).
 */
function createAdjList(twosat: TwoSat): Map<string, string[]> {
  let adjList: Map<string, string[]> = new Map();

  for (let cond of twosat.clauses) {
    let { left, right } = cond;
    let leftKey = left.toString();

    if (!adjList.has(leftKey)) {
      adjList.set(leftKey, []);
    }

    let list = adjList.get(leftKey)!;
    list.push(right.toString());
  }

  return adjList;
}

// Main part
// (A -> B) & (B -> A) & (C -> -B) & (C -> -A)
let twosat = new TwoSat(
  new Condition(new Variable("A", false), new Variable("B", false)),
  new Condition(new Variable("B", false), new Variable("A", false)),
  new Condition(new Variable("C", false), new Variable("B", true)),
  new Condition(new Variable("C", false), new Variable("A", true))
);

twoSatSolver(twosat);
