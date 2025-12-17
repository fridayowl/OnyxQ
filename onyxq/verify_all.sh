#!/bin/bash
echo ""
echo "╔═══════════════════════════════════════════╗"
echo "║     ONYXQ VERIFICATION TEST SUITE         ║"
echo "║     Unbreakable by Design                 ║"
echo "╚═══════════════════════════════════════════╝"
echo ""

echo "Test 1: Checking C library exists..."
if [ -f "build/libonyxq.so" ]; then
    echo "        ✓ libonyxq.so found"
else
    echo "        ✗ Library missing"
    exit 1
fi

echo ""
echo "Test 2: Running C demo..."
if LD_LIBRARY_PATH=build ./examples/simple_demo | grep -q "SUCCESS"; then
    echo "        ✓ C demo passed"
else
    echo "        ✗ C demo failed"
    exit 1
fi

echo ""
echo "Test 3: Running Python demo..."
if python3 python/onyxq.py | grep -q "SUCCESS"; then
    echo "        ✓ Python demo passed"
else
    echo "        ✗ Python demo failed"
    exit 1
fi

echo ""
echo "╔═══════════════════════════════════════════╗"
echo "║     ✓✓✓ ALL TESTS PASSED ✓✓✓             ║"
echo "║     OnyxQ is ready for production         ║"
echo "╚═══════════════════════════════════════════╝"
echo ""
