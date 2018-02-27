/*************************/
/* Client-side interface */
/*************************/

// typedef ______* elem;
typedef void* elem;
typedef int compare_fn(elem e1, elem e2)
  /*@requires e1 != NULL && e2 != NULL; @*/
  /*@ensures -1 <= \result && \result <= 1; @*/ ;

typedef void free_fn(elem e)
  /*@requires e != NULL @*/ ;

/*********************/
/* Library interface */
/*********************/

// typedef ______* bst_t;
typedef struct bst_header* bst_t;

bst_t bst_new(compare_fn* compare)
  /*@requires compare != NULL; @*/
  /*@ensures \result != NULL; @*/ ;

void bst_insert(bst_t B, elem e)
  /*@requires B != NULL && e != NULL; @*/ ;

void bst_free(bst_t B)
  /*@requires B != NULL; @*/;
