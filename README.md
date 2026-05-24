# Slingshot Physics Library

A modern C++20 library for simulating slingshot mechanics and projectile motion with high precision.

## 🚀 Features

- **Accurate Physics**: Simulates trajectory based on band stiffness, efficiency, and mass.
- **Unit Support**: Native support for both Degrees and Radians.
- **Directional Launch**: Simulate launches in both positive and negative X directions.
- **Modern Docs**: Clean, responsive documentation powered by Doxygen Awesome.
- **100% Verified**: Exhaustive unit test suite with full code coverage.

## 🛠 Building

The project uses CMake and requires a C++20 compatible compiler.

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

## 🧪 Testing

We use GoogleTest for our test suite. To run tests:

```bash
cd build
ctest --output-on-failure
```

## 📖 Documentation

The latest API documentation is automatically published to GitHub Pages:
[View Documentation](https://r82-labs.github.io/r82labs-learn-with-physics/)

---
*Created by r82-labs*
