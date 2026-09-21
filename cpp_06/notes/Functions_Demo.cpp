#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <string>

void demonstrateStrtod() {
    std::cout << "=== STRTOD FUNCTION DEMONSTRATION ===" << std::endl;
    std::cout << "Converts string to double with error detection" << std::endl;
    
    std::string inputs[] = {"42", "3.14", "3.14f", "42abc", "abc", "", "  123  "};
    
    for (const std::string& input : inputs) {
        std::cout << "\nInput: \"" << input << "\"" << std::endl;
        
        char* endptr;
        double result = std::strtod(input.c_str(), &endptr);
        
        std::cout << "  Result: " << result << std::endl;
        std::cout << "  End pointer: ";
        
        if (*endptr == '\0') {
            std::cout << "SUCCESS (reached end)" << std::endl;
        } else {
            std::cout << "ERROR (stopped at '" << *endptr << "')" << std::endl;
        }
    }
}

void demonstrateIsNan() {
    std::cout << "\n=== ISNAN FUNCTION DEMONSTRATION ===" << std::endl;
    std::cout << "Checks if a value is NaN (Not a Number)" << std::endl;
    
    // Create different values
    double values[] = {
        42.5,                                    // Normal number
        0.0,                                     // Zero
        1.0 / 0.0,                              // Positive infinity  
        -1.0 / 0.0,                             // Negative infinity
        0.0 / 0.0,                              // NaN
        std::sqrt(-1.0),                        // NaN from sqrt
        std::numeric_limits<double>::quiet_NaN() // Direct NaN
    };
    
    std::string descriptions[] = {
        "42.5 (normal)",
        "0.0 (zero)", 
        "1.0/0.0 (inf)",
        "-1.0/0.0 (-inf)",
        "0.0/0.0 (nan)",
        "sqrt(-1) (nan)",
        "quiet_NaN (nan)"
    };
    
    for (size_t i = 0; i < 7; ++i) {
        std::cout << "\n" << descriptions[i] << ":" << std::endl;
        std::cout << "  Value: " << values[i] << std::endl;
        std::cout << "  isnan(): " << (std::isnan(values[i]) ? "TRUE" : "FALSE") << std::endl;
        std::cout << "  isinf(): " << (std::isinf(values[i]) ? "TRUE" : "FALSE") << std::endl;
        std::cout << "  == itself: " << (values[i] == values[i] ? "TRUE" : "FALSE") << std::endl;
    }
    
    std::cout << "\nNOTE: Only NaN returns FALSE for == itself!" << std::endl;
}

void demonstrateFormatting() {
    std::cout << "\n=== FORMATTING DEMONSTRATION ===" << std::endl;
    std::cout << "std::fixed and std::setprecision control output format" << std::endl;
    
    double values[] = {3.14159265, 42.0, 1234.5678, 0.001234, 999.999};
    
    std::cout << "\nValue\t\tDefault\t\tFixed(0)\tFixed(1)\tFixed(3)" << std::endl;
    std::cout << "-----\t\t-------\t\t--------\t--------\t--------" << std::endl;
    
    for (double val : values) {
        std::cout << val << "\t";
        
        // Default (reset formatting first)
        std::cout << std::defaultfloat << std::setprecision(6);
        std::cout << val << "\t";
        
        // Fixed with 0 decimals
        std::cout << std::fixed << std::setprecision(0) << val << "\t\t";
        
        // Fixed with 1 decimal
        std::cout << std::fixed << std::setprecision(1) << val << "\t\t";
        
        // Fixed with 3 decimals
        std::cout << std::fixed << std::setprecision(3) << val << std::endl;
    }
    
    std::cout << "\nFormatting affects ALL subsequent output until changed!" << std::endl;
}

void demonstrateYourCodeLogic() {
    std::cout << "\n=== YOUR SCALARCONVERTER LOGIC DEMO ===" << std::endl;
    
    std::string testInputs[] = {"3.14f", "42", "abc", "nan", "300"};
    
    for (const std::string& literal : testInputs) {
        std::cout << "\nProcessing: \"" << literal << "\"" << std::endl;
        
        double value;
        
        // Step 1: Handle special values
        if (literal == "nan" || literal == "nanf") {
            std::cout << "  → Special case: NaN" << std::endl;
            continue;
        }
        
        // Step 2: Remove 'f' suffix if needed
        std::string modified_literal = literal;
        if (literal.find('.') != std::string::npos && 
            literal.length() > 0 && literal[literal.length() - 1] == 'f') {
            modified_literal = literal.substr(0, literal.length() - 1);
            std::cout << "  → Removed 'f': \"" << modified_literal << "\"" << std::endl;
        }
        
        // Step 3: Parse with strtod
        char *endptr;
        value = std::strtod(modified_literal.c_str(), &endptr);
        
        if (*endptr != '\0') {
            std::cout << "  → Parsing failed at: '" << *endptr << "'" << std::endl;
            continue;
        }
        
        std::cout << "  → Parsed value: " << value << std::endl;
        
        // Step 4: Generate outputs
        std::cout << "  → Outputs:" << std::endl;
        
        // Char conversion
        if (value < -128 || value > 127 || std::isnan(value)) {
            std::cout << "    char: impossible" << std::endl;
        } else if (!std::isprint(static_cast<char>(value))) {
            std::cout << "    char: Non displayable" << std::endl;
        } else {
            std::cout << "    char: '" << static_cast<char>(value) << "'" << std::endl;
        }
        
        // Int conversion  
        if (value < -2147483648.0 || value > 2147483647.0 || std::isnan(value)) {
            std::cout << "    int: impossible" << std::endl;
        } else {
            std::cout << "    int: " << static_cast<int>(value) << std::endl;
        }
        
        // Float and double with formatting
        std::cout << "    float: " << std::fixed << std::setprecision(1)
                  << static_cast<float>(value) << "f" << std::endl;
        std::cout << "    double: " << std::fixed << std::setprecision(1)
                  << value << std::endl;
    }
}

int main() {
    demonstrateStrtod();
    demonstrateIsNan(); 
    demonstrateFormatting();
    demonstrateYourCodeLogic();
    
    std::cout << "\n=== SUMMARY ===" << std::endl;
    std::cout << "strtod(): Converts string to double safely" << std::endl;
    std::cout << "isnan(): Checks for NaN values" << std::endl;
    std::cout << "fixed + setprecision(): Controls output formatting" << std::endl;
    std::cout << "Together: Robust string parsing and consistent output!" << std::endl;
    
    return 0;
}