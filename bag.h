#ifndef BAG_H
#define BAG_H

typedef struct sbag tbag;

/**
 * Init a bag and return it. Malloc space for it.
 * @return initialised bag */
tbag *bag_new(void);

/**
 * Free memory held by bag */
void bag_free(tbag * b);

int bag_put(tbag * b, void* i);

/**
 * Remove one random item.
 * @return one random item */
void *bag_take(tbag * b);

int bag_count(tbag * b);

#endif /* BAG_H */
