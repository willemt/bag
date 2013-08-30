
typedef struct {
    void **array;
    int size;
    int count;
} bag_t;

bag_t *bag_new();

void bag_free(bag_t * b);

void bag_put(bag_t * b, void* i);

void *bag_take(bag_t * b);

int bag_count(bag_t * b);
