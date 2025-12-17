#ifndef ONYXQ_H
#define ONYXQ_H

#include <stdint.h>
#include <stddef.h>

// Kyber-768 constants
#define OQ_PUBLIC_KEY_BYTES 1184
#define OQ_SECRET_KEY_BYTES 2400
#define OQ_CIPHERTEXT_BYTES 1088
#define OQ_SHARED_SECRET_BYTES 32

/**
 * @brief Initialize OnyxQ library
 * @return 0 on success, -1 on failure
 */
int oq_init(void);

/**
 * @brief Cleanup OnyxQ library
 */
void oq_cleanup(void);

/**
 * @brief Generate Kyber-768 keypair
 * @param public_key Output buffer for public key (1184 bytes)
 * @param secret_key Output buffer for secret key (2400 bytes)
 * @return 0 on success, -1 on failure
 */
int oq_keypair(uint8_t *public_key, uint8_t *secret_key);

/**
 * @brief Encapsulate shared secret using public key
 * @param ciphertext Output buffer for ciphertext (1088 bytes)
 * @param shared_secret Output buffer for shared secret (32 bytes)
 * @param public_key Input public key (1184 bytes)
 * @return 0 on success, -1 on failure
 */
int oq_encapsulate(uint8_t *ciphertext, uint8_t *shared_secret, 
                   const uint8_t *public_key);

/**
 * @brief Decapsulate shared secret using secret key
 * @param shared_secret Output buffer for shared secret (32 bytes)
 * @param ciphertext Input ciphertext (1088 bytes)
 * @param secret_key Input secret key (2400 bytes)
 * @return 0 on success, -1 on failure
 */
int oq_decapsulate(uint8_t *shared_secret, const uint8_t *ciphertext,
                   const uint8_t *secret_key);

#endif // ONYXQ_H
