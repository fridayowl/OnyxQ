# OnyxQ - Post-Quantum Cryptography Library
**Unbreakable by Design**

OnyxQ provides high-performance post-quantum cryptographic protocols for secure networking.

## Features
- Kyber-768 key encapsulation
- Dilithium-3 digital signatures
- SPHINCS+ long-term signatures
- Hybrid classical+PQC modes

## Quick Start
```bash
# Build library
mkdir build && cd build
cmake ..
make

# Run demo
LD_LIBRARY_PATH=build ./examples/simple_demo
```

## License
MIT
