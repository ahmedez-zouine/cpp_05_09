#include <iostream>
#include <iomanip>
#include <cstdint>

struct Data {
    int id;
    double value;
    
    Data(int i, double v) : id(i), value(v) {}
    
    void print() const {
        std::cout << "Data{id: " << id << ", value: " << value << "}" << std::endl;
    }
};

void explainReinterpretCast() {
    std::cout << "=== REINTERPRET_CAST DETAILED EXPLANATION ===" << std::endl;
    
    // 1. Create an object and get its pointer
    std::cout << "\n1. Creating Data object:" << std::endl;
    Data* originalData = new Data(42, 3.14159);
    originalData->print();
    
    // 2. Show the pointer value (memory address)
    std::cout << "\n2. Pointer information:" << std::endl;
    std::cout << "Pointer address (as pointer): " << originalData << std::endl;
    std::cout << "Pointer address (with void*): " << static_cast<void*>(originalData) << std::endl;
    
    // 3. Convert pointer to integer using reinterpret_cast
    std::cout << "\n3. Converting pointer to integer:" << std::endl;
    uintptr_t serializedPtr = reinterpret_cast<uintptr_t>(originalData);
    
    std::cout << "As uintptr_t (decimal): " << serializedPtr << std::endl;
    std::cout << "As uintptr_t (hex):     0x" << std::hex << serializedPtr << std::dec << std::endl;
    
    // 4. Convert back to pointer
    std::cout << "\n4. Converting integer back to pointer:" << std::endl;
    Data* deserializedPtr = reinterpret_cast<Data*>(serializedPtr);
    
    std::cout << "Restored pointer: " << deserializedPtr << std::endl;
    std::cout << "Pointers match: " << (originalData == deserializedPtr ? "YES" : "NO") << std::endl;
    
    // 5. Verify the object is still valid
    std::cout << "\n5. Accessing restored object:" << std::endl;
    deserializedPtr->print();
    
    // 6. Show memory layout
    std::cout << "\n6. Memory layout analysis:" << std::endl;
    std::cout << "sizeof(Data*):    " << sizeof(Data*) << " bytes" << std::endl;
    std::cout << "sizeof(uintptr_t): " << sizeof(uintptr_t) << " bytes" << std::endl;
    std::cout << "sizeof(Data):     " << sizeof(Data) << " bytes" << std::endl;
    
    delete originalData; // Clean up
}

void demonstrateReinterpretCastUses() {
    std::cout << "\n=== PRACTICAL USES OF REINTERPRET_CAST ===" << std::endl;
    
    // USE CASE 1: Serialization (saving pointers to files/network)
    std::cout << "\n1. SERIALIZATION - Saving pointer values:" << std::endl;
    Data* obj1 = new Data(100, 2.718);
    Data* obj2 = new Data(200, 1.414);
    
    // Convert pointers to integers for storage
    uintptr_t addr1 = reinterpret_cast<uintptr_t>(obj1);
    uintptr_t addr2 = reinterpret_cast<uintptr_t>(obj2);
    
    std::cout << "Object 1 address: 0x" << std::hex << addr1 << std::dec << std::endl;
    std::cout << "Object 2 address: 0x" << std::hex << addr2 << std::dec << std::endl;
    
    // Simulate saving to file (just print the integers)
    std::cout << "Saved addresses: " << addr1 << ", " << addr2 << std::endl;
    
    // Later, restore pointers from integers
    Data* restored1 = reinterpret_cast<Data*>(addr1);
    Data* restored2 = reinterpret_cast<Data*>(addr2);
    
    std::cout << "Restored objects:" << std::endl;
    restored1->print();
    restored2->print();
    
    // USE CASE 2: Hash table implementation
    std::cout << "\n2. HASH FUNCTION - Using pointer as hash key:" << std::endl;
    size_t hash1 = reinterpret_cast<uintptr_t>(obj1) % 1000;  // Simple hash
    size_t hash2 = reinterpret_cast<uintptr_t>(obj2) % 1000;
    
    std::cout << "Hash of obj1: " << hash1 << std::endl;
    std::cout << "Hash of obj2: " << hash2 << std::endl;
    
    // USE CASE 3: Low-level memory access
    std::cout << "\n3. MEMORY INSPECTION - Looking at raw bytes:" << std::endl;
    int number = 0x41424344;  // ASCII: 'ABCD'
    char* bytes = reinterpret_cast<char*>(&number);
    
    std::cout << "Integer: 0x" << std::hex << number << std::dec << " (" << number << ")" << std::endl;
    std::cout << "As bytes: ";
    for (size_t i = 0; i < sizeof(int); ++i) {
        if (bytes[i] >= 32 && bytes[i] <= 126) {
            std::cout << "'" << bytes[i] << "' ";
        } else {
            std::cout << "0x" << std::hex << (unsigned char)bytes[i] << std::dec << " ";
        }
    }
    std::cout << std::endl;
    
    delete obj1;
    delete obj2;
}

void demonstrateDangerousReinterpretCast() {
    std::cout << "\n=== DANGEROUS USES - WHAT NOT TO DO ===" << std::endl;
    
    // DANGER 1: Casting between incompatible pointer types
    std::cout << "\n1. DANGEROUS: Incompatible pointer types" << std::endl;
    int integer = 42;
    double* doublePtr = reinterpret_cast<double*>(&integer);
    
    std::cout << "Original int: " << integer << std::endl;
    std::cout << "Same memory as double: " << *doublePtr << " (GARBAGE!)" << std::endl;
    // *doublePtr = 3.14;  // DON'T DO THIS! Undefined behavior
    
    // DANGER 2: Platform-dependent behavior
    std::cout << "\n2. PLATFORM DEPENDENT: Pointer size assumptions" << std::endl;
    void* ptr = &integer;
    
    // This might fail on 64-bit systems if you assume pointers fit in 32-bit int
    // int badCast = reinterpret_cast<int>(ptr);  // DON'T DO THIS!
    
    // Use uintptr_t instead (guaranteed to fit any pointer)
    uintptr_t goodCast = reinterpret_cast<uintptr_t>(ptr);
    std::cout << "Pointer as uintptr_t: 0x" << std::hex << goodCast << std::dec << std::endl;
    
    // DANGER 3: Alignment issues
    std::cout << "\n3. ALIGNMENT ISSUES:" << std::endl;
    char buffer[16];
    
    // This might fail if buffer is not properly aligned for double
    double* alignedDouble = reinterpret_cast<double*>(buffer);
    std::cout << "Buffer address: " << static_cast<void*>(buffer) << std::endl;
    std::cout << "Alignment check: " << (reinterpret_cast<uintptr_t>(buffer) % sizeof(double) == 0 ? "OK" : "BAD") << std::endl;
    
    // Safer approach: use aligned storage or placement new
}

void comparisonWithOtherCasts() {
    std::cout << "\n=== REINTERPRET_CAST vs OTHER CASTS ===" << std::endl;
    
    double value = 3.14159;
    
    std::cout << "\nOriginal double: " << value << std::endl;
    
    // static_cast: Performs conversion
    int staticResult = static_cast<int>(value);
    std::cout << "static_cast<int>: " << staticResult << " (converted value)" << std::endl;
    
    // reinterpret_cast: Reinterprets bits
    int* reinterpretResult = reinterpret_cast<int*>(&value);
    std::cout << "reinterpret_cast<int*>: " << *reinterpretResult << " (raw bits as int)" << std::endl;
    
    std::cout << "\nKey difference:" << std::endl;
    std::cout << "- static_cast CONVERTS the value (3.14159 -> 3)" << std::endl;
    std::cout << "- reinterpret_cast REINTERPRETS the bits (double bits as int bits)" << std::endl;
}

// Example: Simple serialization system
class SimpleSerializer {
public:
    static uintptr_t serialize(void* ptr) {
        return reinterpret_cast<uintptr_t>(ptr);
    }
    
    static void* deserialize(uintptr_t value) {
        return reinterpret_cast<void*>(value);
    }
    
    template<typename T>
    static T* deserializeAs(uintptr_t value) {
        return reinterpret_cast<T*>(value);
    }
};

void serialization_example() {
    std::cout << "\n=== SERIALIZATION EXAMPLE ===" << std::endl;
    
    Data* original = new Data(999, 2.71828);
    std::cout << "Original object: ";
    original->print();
    
    // Serialize pointer
    uintptr_t serialized = SimpleSerializer::serialize(original);
    std::cout << "Serialized as: 0x" << std::hex << serialized << std::dec << std::endl;
    
    // Deserialize pointer
    Data* restored = SimpleSerializer::deserializeAs<Data>(serialized);
    std::cout << "Restored object: ";
    restored->print();
    
    std::cout << "Success: " << (original == restored ? "YES" : "NO") << std::endl;
    
    delete original;
}

int main() {
    explainReinterpretCast();
    demonstrateReinterpretCastUses();
    demonstrateDangerousReinterpretCast();
    comparisonWithOtherCasts();
    serialization_example();
    
    std::cout << "\n=== SUMMARY ===" << std::endl;
    std::cout << "reinterpret_cast:" << std::endl;
    std::cout << "✓ Use for: Pointer ↔ integer conversion" << std::endl;
    std::cout << "✓ Use for: Serialization/deserialization" << std::endl;
    std::cout << "✓ Use for: Low-level memory operations" << std::endl;
    std::cout << "✗ Avoid: Converting between incompatible types" << std::endl;
    std::cout << "✗ Avoid: When other casts would work safely" << std::endl;
    std::cout << "⚠️  Always: Check alignment and platform compatibility" << std::endl;
    
    return 0;
}