"""
OnyxQ - Post-Quantum Cryptography Library
Unbreakable by Design

Python bindings for the OnyxQ C library.
"""

import os
import sys
from cffi import FFI

ffi = FFI()

# Define C interface
ffi.cdef("""
    int oq_init(void);
    void oq_cleanup(void);
    int oq_keypair(uint8_t *public_key, uint8_t *secret_key);
    int oq_encapsulate(uint8_t *ciphertext, uint8_t *shared_secret, 
                       const uint8_t *public_key);
    int oq_decapsulate(uint8_t *shared_secret, const uint8_t *ciphertext,
                       const uint8_t *secret_key);
""")

# Load library
if sys.platform == "darwin":
    lib_ext = ".dylib"
else:
    lib_ext = ".so"

lib_path = os.path.join(os.path.dirname(__file__), f'../build/libonyxq{lib_ext}')
lib = ffi.dlopen(lib_path)

class OnyxQ:
    """Python wrapper for OnyxQ post-quantum cryptography"""
    
    def __init__(self):
        """Initialize the OnyxQ library"""
        if lib.oq_init() != 0:
            raise RuntimeError("Failed to initialize OnyxQ")
    
    def __del__(self):
        """Cleanup the library"""
        lib.oq_cleanup()
    
    def keypair(self):
        """
        Generate a Kyber-768 keypair
        
        Returns:
            tuple: (public_key: bytes, secret_key: bytes)
        """
        public_key = ffi.new("uint8_t[1184]")
        secret_key = ffi.new("uint8_t[2400]")
        
        if lib.oq_keypair(public_key, secret_key) != 0:
            raise RuntimeError("Failed to generate keypair")
        
        return bytes(ffi.buffer(public_key)), bytes(ffi.buffer(secret_key))
    
    def encapsulate(self, public_key):
        """
        Encapsulate a shared secret using a public key
        
        Args:
            public_key (bytes): Public key (1184 bytes)
        
        Returns:
            tuple: (ciphertext: bytes, shared_secret: bytes)
        """
        if len(public_key) != 1184:
            raise ValueError("Public key must be 1184 bytes")
        
        ciphertext = ffi.new("uint8_t[1088]")
        shared_secret = ffi.new("uint8_t[32]")
        pk = ffi.new("uint8_t[]", public_key)
        
        if lib.oq_encapsulate(ciphertext, shared_secret, pk) != 0:
            raise RuntimeError("Failed to encapsulate")
        
        return bytes(ffi.buffer(ciphertext)), bytes(ffi.buffer(shared_secret))
    
    def decapsulate(self, ciphertext, secret_key):
        """
        Decapsulate a shared secret using a secret key
        
        Args:
            ciphertext (bytes): Ciphertext (1088 bytes)
            secret_key (bytes): Secret key (2400 bytes)
        
        Returns:
            bytes: Shared secret (32 bytes)
        """
        if len(ciphertext) != 1088:
            raise ValueError("Ciphertext must be 1088 bytes")
        if len(secret_key) != 2400:
            raise ValueError("Secret key must be 2400 bytes")
        
        shared_secret = ffi.new("uint8_t[32]")
        ct = ffi.new("uint8_t[]", ciphertext)
        sk = ffi.new("uint8_t[]", secret_key)
        
        if lib.oq_decapsulate(shared_secret, ct, sk) != 0:
            raise RuntimeError("Failed to decapsulate")
        
        return bytes(ffi.buffer(shared_secret))


if __name__ == "__main__":
    print("\n" + "="*50)
    print("  OnyxQ Python Demo")
    print("  Unbreakable by Design")
    print("="*50 + "\n")
    
    # Initialize
    oq = OnyxQ()
    print()
    
    # Generate keypair
    print("1. Generating keypair...")
    public_key, secret_key = oq.keypair()
    print(f"   Public key: {public_key[:16].hex()}... ({len(public_key)} bytes)")
    print(f"   Secret key: {secret_key[:16].hex()}... ({len(secret_key)} bytes)")
    
    # Encapsulate
    print("\n2. Bob encapsulating shared secret...")
    ciphertext, shared_secret_bob = oq.encapsulate(public_key)
    print(f"   Ciphertext: {ciphertext[:16].hex()}... ({len(ciphertext)} bytes)")
    print(f"   Bob's secret: {shared_secret_bob.hex()}")
    
    # Decapsulate
    print("\n3. Alice decapsulating...")
    shared_secret_alice = oq.decapsulate(ciphertext, secret_key)
    print(f"   Alice's secret: {shared_secret_alice.hex()}")
    
    # Verify
    print("\n4. Verifying secrets match...")
    if shared_secret_alice == shared_secret_bob:
        print("   ✓✓✓ SUCCESS! Quantum-safe key exchange complete!\n")
    else:
        print("   ✗✗✗ FAILURE! Secrets don't match!\n")
    
    print("="*50 + "\n")
