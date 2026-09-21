#include <iostream>
#include <string>
#include <iomanip>

// Simplified version of your ScalarConverter with detailed explanations
class ScalarConverterDemo {
public:
    static void explainConversion(const std::string& input) {
        std::cout << "\n" << std::string(50, '=') << std::endl;
        std::cout << "ANALYZING INPUT: \"" << input << "\"" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        
        // Step 1: Empty check
        std::cout << "\nSTEP 1: Empty Check" << std::endl;
        if (input.empty()) {
            std::cout << "❌ Input is empty - ERROR!" << std::endl;
            return;
        }
        std::cout << "✅ Input has " << input.length() << " character(s)" << std::endl;
        
        // Step 2: Special values check  
        std::cout << "\nSTEP 2: Special Values Check" << std::endl;
        if (input == "nan" || input == "nanf") {
            std::cout << "🔍 Detected: NaN (Not a Number)" << std::endl;
            std::cout << "   char: impossible (NaN can't be a character)" << std::endl;
            std::cout << "   int: impossible (NaN can't be an integer)" << std::endl;
            std::cout << "   float: nanf" << std::endl;
            std::cout << "   double: nan" << std::endl;
            return;
        }
        else if (input == "inf" || input == "+inf" || input == "inff" || input == "+inff") {
            std::cout << "🔍 Detected: Positive Infinity" << std::endl;
            std::cout << "   char: impossible (infinity can't be a character)" << std::endl;
            std::cout << "   int: impossible (infinity can't be an integer)" << std::endl;
            std::cout << "   float: inff" << std::endl;
            std::cout << "   double: inf" << std::endl;
            return;
        }
        else if (input == "-inf" || input == "-inff") {
            std::cout << "🔍 Detected: Negative Infinity" << std::endl;
            std::cout << "   char: impossible" << std::endl;
            std::cout << "   int: impossible" << std::endl;
            std::cout << "   float: -inff" << std::endl;
            std::cout << "   double: -inf" << std::endl;
            return;
        }
        std::cout << "✅ Not a special value, continue processing..." << std::endl;
        
        double value;
        
        // Step 3: Single character check
        std::cout << "\nSTEP 3: Single Character Check" << std::endl;
        std::cout << "   Length: " << input.length() << std::endl;
        if (input.length() == 1) {
            std::cout << "   Is digit? " << (std::isdigit(input[0]) ? "YES" : "NO") << std::endl;
            if (!std::isdigit(input[0])) {
                char ch = input[0];
                value = static_cast<double>(ch);
                std::cout << "🔄 Converting single character to double:" << std::endl;
                std::cout << "   Character: '" << ch << "'" << std::endl;
                std::cout << "   ASCII value: " << static_cast<int>(ch) << std::endl;
                std::cout << "   As double: " << value << std::endl;
                
                generateOutputs(value);
                return;
            }
        }
        std::cout << "✅ Not a single non-digit character, parse as number..." << std::endl;
        
        // Step 4: Float suffix handling
        std::cout << "\nSTEP 4: Float Suffix Handling" << std::endl;
        std::string modified_input = input;
        bool hasDecimal = (input.find('.') != std::string::npos);
        bool endsWithF = (!input.empty() && input[input.length() - 1] == 'f');
        
        std::cout << "   Has decimal point? " << (hasDecimal ? "YES" : "NO") << std::endl;
        std::cout << "   Ends with 'f'? " << (endsWithF ? "YES" : "NO") << std::endl;
        
        if (hasDecimal && endsWithF) {
            modified_input = input.substr(0, input.length() - 1);
            std::cout << "🔄 Removing 'f' suffix:" << std::endl;
            std::cout << "   Original: \"" << input << "\"" << std::endl;
            std::cout << "   Modified: \"" << modified_input << "\"" << std::endl;
        } else {
            std::cout << "✅ No modification needed" << std::endl;
        }
        
        // Step 5: String to double parsing
        std::cout << "\nSTEP 5: String to Double Parsing" << std::endl;
        char* endptr;
        value = std::strtod(modified_input.c_str(), &endptr);
        
        std::cout << "   Input string: \"" << modified_input << "\"" << std::endl;
        std::cout << "   Parsed value: " << value << std::endl;
        std::cout << "   End pointer: " << ((*endptr == '\\0') ? "Points to end (GOOD)" : "Points to invalid char (ERROR)") << std::endl;
        
        if (*endptr != '\\0') {
            std::cout << "❌ Parsing failed - invalid character found: '" << *endptr << "'" << std::endl;
            return;
        }
        std::cout << "✅ Successfully parsed as double: " << value << std::endl;
        
        // Step 6: Generate outputs
        generateOutputs(value);
    }
    
private:
    static void generateOutputs(double value) {
        std::cout << "\nSTEP 6: Generate Outputs for All Types" << std::endl;
        std::cout << "Original double value: " << value << std::endl;
        
        // Char conversion
        std::cout << "\n📝 CHAR CONVERSION:" << std::endl;
        std::cout << "   Range check: CHAR_MIN(-128) <= " << value << " <= CHAR_MAX(127)?" << std::endl;
        
        if (value < -128 || value > 127 || std::isnan(value)) {
            std::cout << "   ❌ Out of range or NaN" << std::endl;
            std::cout << "   Output: char: impossible" << std::endl;
        } else {
            char charValue = static_cast<char>(value);
            std::cout << "   ✅ In range, static_cast<char>(" << value << ") = " << static_cast<int>(charValue) << std::endl;
            
            if (!std::isprint(charValue)) {
                std::cout << "   ❌ Not printable (ASCII < 32 or > 126)" << std::endl;
                std::cout << "   Output: char: Non displayable" << std::endl;
            } else {
                std::cout << "   ✅ Printable character" << std::endl;
                std::cout << "   Output: char: '" << charValue << "'" << std::endl;
            }
        }
        
        // Int conversion
        std::cout << "\n📝 INT CONVERSION:" << std::endl;
        std::cout << "   Range check: INT_MIN(-2147483648) <= " << value << " <= INT_MAX(2147483647)?" << std::endl;
        
        if (value < -2147483648.0 || value > 2147483647.0 || std::isnan(value)) {
            std::cout << "   ❌ Out of range or NaN" << std::endl;
            std::cout << "   Output: int: impossible" << std::endl;
        } else {
            int intValue = static_cast<int>(value);
            std::cout << "   ✅ In range, static_cast<int>(" << value << ") = " << intValue << std::endl;
            std::cout << "   Output: int: " << intValue << std::endl;
        }
        
        // Float conversion
        std::cout << "\n📝 FLOAT CONVERSION:" << std::endl;
        float floatValue = static_cast<float>(value);
        std::cout << "   static_cast<float>(" << value << ") = " << floatValue << std::endl;
        std::cout << "   Formatted with 1 decimal place: " << std::fixed << std::setprecision(1) << floatValue << "f" << std::endl;
        std::cout << "   Output: float: " << floatValue << "f" << std::endl;
        
        // Double output
        std::cout << "\n📝 DOUBLE OUTPUT:" << std::endl;
        std::cout << "   Original value: " << value << std::endl;
        std::cout << "   Formatted with 1 decimal place: " << std::fixed << std::setprecision(1) << value << std::endl;
        std::cout << "   Output: double: " << value << std::endl;
        
        std::cout << "\n" << std::string(50, '-') << std::endl;
        std::cout << "FINAL OUTPUT:" << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        
        // Final output (same as your original code)
        if (value < -128 || value > 127 || std::isnan(value))
            std::cout << "char: impossible" << std::endl;
        else if (!std::isprint(static_cast<char>(value)))
            std::cout << "char: Non displayable" << std::endl;
        else
            std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;

        if (value < -2147483648.0 || value > 2147483647.0 || std::isnan(value))
            std::cout << "int: impossible" << std::endl;
        else
            std::cout << "int: " << static_cast<int>(value) << std::endl;

        std::cout << "float: " << std::fixed << std::setprecision(1)
                  << static_cast<float>(value) << "f" << std::endl;

        std::cout << "double: " << std::fixed << std::setprecision(1)
                  << value << std::endl;
    }
};

int main() {
    std::cout << "SCALARCONVERTER STEP-BY-STEP ANALYSIS" << std::endl;
    std::cout << "======================================" << std::endl;
    
    // Test different types of inputs
    std::string testInputs[] = {
        "A",        // Single character
        "65",       // Integer
        "3.14f",    // Float with suffix
        "3.14",     // Double
        "300",      // Large number (char overflow)
        "nan",      // NaN
        "inf",      // Infinity
        "-42.5",    // Negative decimal
        "abc",      // Invalid input
        ""          // Empty input
    };
    
    for (const std::string& input : testInputs) {
        ScalarConverterDemo::explainConversion(input);
        
        // Pause between examples
        std::cout << "\nPress Enter to continue to next example...";
        std::cin.get();
    }
    
    return 0;
}