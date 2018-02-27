/* C0VM abnormal termination 
 * 15-122 Principles of Imperative Computation
 * Rob Simmons 
 */

void c0_user_error(char *err);        // for calls to error() in C0
void c0_assertion_failure(char *err); // for failled assertions in C0
void c0_memory_error(char *err);      // for memory-related errors
void c0_arith_error(char *err);       // for arithmetic-related errors
