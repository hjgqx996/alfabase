#ifndef ADDRESSES_H
#define ADDRESSES_H

#include "iota_types.h"

int add_index_to_seed(trit_t trits[], uint32_t index);

// int generate_private_key(const trit_t seed_trits[], const uint32_t index, trit_t private_key[]);
// int generate_public_address(const trit_t private_key[], trit_t address_out[], void (*progress_callback)(uint32_t));

int generate_private_key(trit_t *seed_trits, uint32_t index, trint_t *private_key);
int generate_public_address(const trit_t private_key[], trit_t address_out[]);

int generate_private_key_half(trint_t *seed_trints, uint32_t index,
                              trint_t *private_key, uint8_t level);
int generate_public_address_half(trint_t *private_key,
                                 trint_t *address_out, uint8_t level);

#endif // ADDRESSES_H
