#include <stdio.h>
#include <time.h>
#include "binary_tree.h"

int main() {
    // Expression to evaluate
    char expression[] = "2+3-4";
    printf("Expression: %s\n", expression);

    // Measure CPU time before expression evaluation
    clock_t start = clock();

    // Evaluate expression
    int result = evaluate(buildTree(expression));

    // Measure CPU time after expression evaluation
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Display result and CPU time
    printf("Result: %d\n", result);
    printf("CPU Time used: %f seconds\n", cpu_time_used);

    return 0;
}
