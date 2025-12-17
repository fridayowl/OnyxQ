#include "onyxq.h"
#include <oqs/oqs.h>
#include <stdio.h>
#include <string.h>

static int initialized = 0;

int oq_init(void) {
    if (initialized) {
        return 0;
    }
    printf("OnyxQ v0.1.0 - Unbreakable by Design\n");
    printf("Initializing post-quantum cryptography...\n");
    initialized = 1;
    return 0;
}

void oq_cleanup(void) {
    if (!initialized) {
        return;
    }
    printf("OnyxQ cleanup complete.\n");
    initialized = 0;
}

int oq_keypair(uint8_t *public_key, uint8_t *secret_key) {
    if (!initialized) {
        fprintf(stderr, "Error: OnyxQ not initialized. Call oq_init() first.\n");
        return -1;
    }
    
    if (public_key == NULL || secret_key == NULL) {
        return -1;
    }
    
    OQS_KEM *kem = OQS_KEM_new(OQS_KEM_alg_kyber_768);
    if (kem == NULL) {
        return -1;
    }
    
    OQS_STATUS status = OQS_KEM_keypair(kem, public_key, secret_key);
    OQS_KEM_free(kem);
    
    return (status == OQS_SUCCESS) ? 0 : -1;
}

int oq_encapsulate(uint8_t *ciphertext, uint8_t *shared_secret, 
                   const uint8_t *public_key) {
    if (!initialized) {
        fprintf(stderr, "Error: OnyxQ not initialized. Call oq_init() first.\n");
        return -1;
    }
    
    if (ciphertext == NULL || shared_secret == NULL || public_key == NULL) {
        return -1;
    }
    
    OQS_KEM *kem = OQS_KEM_new(OQS_KEM_alg_kyber_768);
    if (kem == NULL) {
        return -1;
    }
    
    OQS_STATUS status = OQS_KEM_encaps(kem, ciphertext, shared_secret, public_key);
    OQS_KEM_free(kem);
    
    return (status == OQS_SUCCESS) ? 0 : -1;
}

int oq_decapsulate(uint8_t *shared_secret, const uint8_t *ciphertext,
                   const uint8_t *secret_key) {
    if (!initialized) {
        fprintf(stderr, "Error: OnyxQ not initialized. Call oq_init() first.\n");
        return -1;
    }
    
    if (shared_secret == NULL || ciphertext == NULL || secret_key == NULL) {
        return -1;
    }
    
    OQS_KEM *kem = OQS_KEM_new(OQS_KEM_alg_kyber_768);
    if (kem == NULL) {
        return -1;
    }
    
    OQS_STATUS status = OQS_KEM_decaps(kem, shared_secret, ciphertext, secret_key);
    OQS_KEM_free(kem);
    
    return (status == OQS_SUCCESS) ? 0 : -1;
}
