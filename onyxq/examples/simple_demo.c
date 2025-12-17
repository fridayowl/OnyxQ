#include <stdio.h>
#include <string.h>
#include "onyxq.h"

void print_hex(const char *label, const uint8_t *data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < 16 && i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("... (%zu bytes)\n", len);
}

int main(void) {
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║         OnyxQ Demo Program             ║\n");
    printf("║    Unbreakable by Design               ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("\n");
    
    // Initialize
    if (oq_init() != 0) {
        fprintf(stderr, "✗ Failed to initialize OnyxQ\n");
        return 1;
    }
    printf("\n");
    
    // Allocate buffers
    uint8_t public_key[OQ_PUBLIC_KEY_BYTES];
    uint8_t secret_key[OQ_SECRET_KEY_BYTES];
    uint8_t ciphertext[OQ_CIPHERTEXT_BYTES];
    uint8_t secret_alice[OQ_SHARED_SECRET_BYTES];
    uint8_t secret_bob[OQ_SHARED_SECRET_BYTES];
    
    // Step 1: Generate keypair
    printf("Step 1: Alice generates keypair\n");
    printf("────────────────────────────────────────\n");
    if (oq_keypair(public_key, secret_key) != 0) {
        fprintf(stderr, "✗ Failed to generate keypair\n");
        return 1;
    }
    print_hex("Public key", public_key, OQ_PUBLIC_KEY_BYTES);
    print_hex("Secret key", secret_key, OQ_SECRET_KEY_BYTES);
    printf("✓ Keypair generated successfully\n\n");
    
    // Step 2: Encapsulate
    printf("Step 2: Bob encapsulates shared secret\n");
    printf("────────────────────────────────────────\n");
    if (oq_encapsulate(ciphertext, secret_bob, public_key) != 0) {
        fprintf(stderr, "✗ Failed to encapsulate\n");
        return 1;
    }
    print_hex("Ciphertext", ciphertext, OQ_CIPHERTEXT_BYTES);
    print_hex("Bob's secret", secret_bob, OQ_SHARED_SECRET_BYTES);
    printf("✓ Encapsulation complete\n\n");
    
    // Step 3: Decapsulate
    printf("Step 3: Alice decapsulates\n");
    printf("────────────────────────────────────────\n");
    if (oq_decapsulate(secret_alice, ciphertext, secret_key) != 0) {
        fprintf(stderr, "✗ Failed to decapsulate\n");
        return 1;
    }
    print_hex("Alice's secret", secret_alice, OQ_SHARED_SECRET_BYTES);
    printf("✓ Decapsulation complete\n\n");
    
    // Step 4: Verify
    printf("Step 4: Verification\n");
    printf("────────────────────────────────────────\n");
    if (memcmp(secret_alice, secret_bob, OQ_SHARED_SECRET_BYTES) == 0) {
        printf("✓✓✓ SUCCESS! Both parties share the same secret!\n");
        printf("    Quantum-safe key exchange complete.\n");
    } else {
        printf("✗✗✗ FAILURE! Secrets don't match!\n");
        return 1;
    }
    
    // Cleanup
    printf("\n");
    oq_cleanup();
    
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║         Demo Complete                  ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("\n");
    
    return 0;
}
